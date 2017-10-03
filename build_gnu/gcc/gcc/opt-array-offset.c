/* Optimizing array element access
   Copyright (C) 2011
   Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

GCC is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */


/* This is a GIMPLE pass over basic block which coverts the stmts:
        
        a = b +/- c1;
	c = a * c2;
        
   to:
   
        a = b * c2;
        c = a +/- c1 * c2;

   in effect expanding the multiplication across addition/substraction.

   Motivating example:
   Consider the following simple integer array access:
   
        a[i] = c;
        a[i + 1] = c;

   The following GIMPLE equivalent will be generated:

        off_1 = i * 4;
        a_i = a + off_1;
	*a_i = c;

	off_1 = i + 1;
	off_2 = off_1 * 4;
	a_i1 = a + off_2;
	*a_i1 = c;

   Notice that a_i1 could simply be a_i + 4. But the calcuation of i+1
   is preventing CSE to perform. This pass will essentially convert the
   second expr into:

        off_1 = i * 4;
        off_2 = off_1 + 4;
        a_i1 = a + off_2;
        ....

   Thus allowing the previous index i calculation to be reuse. off_1 + 4
   would also be combined into a_i if offset addressing mode is available.
   This also have side effect of avoiding redundant sign extension on
   i+1 for LP64 model where native integer size is different from pointer size.

   The algorithm iterates through all the basic blocks looking for
   the above pattern. Care is taken to make sure off_1 only
   has the single use otherwise the transformation cannot be perform.
*/

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"

#include "tree.h"
#include "gimple-pretty-print.h"
#include "basic-block.h"
#include "tree-ssa-alias.h"
#include "internal-fn.h"
#include "gimple-expr.h"
#include "is-a.h"
#include "gimple.h"
#include "gimple-iterator.h"
#include "gimple-ssa.h"
#include "tree-phinodes.h"
#include "ssa-iterators.h"
#include "tree-pass.h"
#include "flags.h"

#include "alloc-pool.h"
#include "target.h"
#include "tree-pretty-print.h"

/*
  We are looking for:
  a = b +/- c1
  c = a * c2 (stmt incoming)
  d = &arr + c
*/
static bool
is_candidate (gimple stmt)
{
  tree mul_result = gimple_get_lhs (stmt);
  tree rhs1, rhs2;
  gimple rhs1_stmt, use_stmt;
  use_operand_p use_p;
  imm_use_iterator imm_iter;

  /* check for a * c2 */
  if (gimple_assign_rhs_code (stmt) != MULT_EXPR)
    return false;

  rhs1 = gimple_assign_rhs1 (stmt);
  rhs2 = gimple_assign_rhs2 (stmt);

  if (TREE_CODE (rhs2) != INTEGER_CST)
    return false;
  
  /* check for b + c1 */
  if (TREE_CODE (rhs1) == SSA_NAME)
    {
      rhs1_stmt = SSA_NAME_DEF_STMT (rhs1);
      if (is_gimple_assign (rhs1_stmt))
	{
	  tree rhs1_2;
	  tree plusminus_result;

	  if (gimple_assign_rhs_code (rhs1_stmt) != PLUS_EXPR
	      && gimple_assign_rhs_code (rhs1_stmt) != MINUS_EXPR)
	    return false;

	  rhs1_2 = gimple_assign_rhs2 (rhs1_stmt);
	  if (TREE_CODE (rhs1_2) != INTEGER_CST)
	    return false;

	  /* make sure there are no other uses of a 
	     e.g. if a is used as an indcution variable 
	     we cannot modified it
	  */
	  plusminus_result = gimple_get_lhs (rhs1_stmt);
	  FOR_EACH_IMM_USE_FAST (use_p, imm_iter, plusminus_result)
	    {
	      use_stmt = USE_STMT (use_p);
	      
	      /* ignore PHI node */
	      if (is_gimple_assign (use_stmt) &&
		  (gimple_code (use_stmt) == GIMPLE_PHI))
		continue;
	      if (use_stmt != stmt)
		return false;
	    }

#if 0
	  if (gimple_bb(rhs1_stmt) != gimple_bb(stmt))
	    return false;
#endif
        }
      else
	return false;
    }
  else
    return false;

  /* now look for uses of c that is a pointer use */
  FOR_EACH_IMM_USE_FAST (use_p, imm_iter, mul_result)
    {
      enum tree_code use_code;

      use_stmt = USE_STMT (use_p);
      
      if (is_gimple_debug (use_stmt))
	continue;
      
      if (gimple_bb (use_stmt) != gimple_bb (stmt))
	return false;

      if (!is_gimple_assign (use_stmt))
	return false;

      use_code = gimple_assign_rhs_code (use_stmt);
      if (use_code != POINTER_PLUS_EXPR)
	return false;
    }

  if (dump_file)
    {
      fprintf (dump_file, "Found candidate:\n");
      print_gimple_stmt (dump_file, rhs1_stmt, 0, TDF_SLIM);
      print_gimple_stmt (dump_file, stmt, 0, TDF_SLIM);
      print_gimple_stmt (dump_file, use_stmt, 0, TDF_SLIM);
    }

  return true;
}

/* Do the actual transformation:
  a = b + c1 ==> a = b * c2
  c = a * c2 ==> c = a + c1*c2
*/
static bool
expand_plusminus_mult (gimple stmt)
{
  tree c1, c2, mul_result;
  gimple rhs1_stmt;

  /* get c2 */
  c2 = gimple_assign_rhs2 (stmt);

  /* get c1 */
  rhs1_stmt = SSA_NAME_DEF_STMT (gimple_assign_rhs1 (stmt));
  c1 = gimple_assign_rhs2 (rhs1_stmt);

  /* form c1 * c2 */
  mul_result = double_int_to_tree (TREE_TYPE(c2), 
		      (tree_to_double_int (c1) * tree_to_double_int (c2)));

  /* a = b + c1 ==> a = b * c2 */
  gimple_assign_set_rhs2 (rhs1_stmt, c2);
  gimple_assign_set_rhs_code (rhs1_stmt, MULT_EXPR);
  update_stmt (rhs1_stmt);

  /* c = a * c2 ==> c = a + c1*c2 */
  gimple_assign_set_rhs2 (stmt, mul_result);
  /* MINUS_EXPR has already been embedded into c1*c2 */
  gimple_assign_set_rhs_code (stmt, PLUS_EXPR);
  update_stmt (stmt);

  return true;
}

static bool
gate_opt_array_offset (void)
{
  return flag_opt_array_offset && optimize;
}

static unsigned int
execute_opt_array_offset ()
{
  basic_block bb;

  FOR_EACH_BB_FN (bb, cfun)
    {
      gimple_stmt_iterator gsi;

      for (gsi = gsi_after_labels (bb); !gsi_end_p (gsi); gsi_next(&gsi))
      {
        gimple stmt = gsi_stmt (gsi);
	//tree lhs,rhs1,rhs2,rhs3;
        //enum tree_code code;
	  
        /* only interested in assign statement */
        if (is_gimple_assign (stmt))
        {
	   /* find stmts calculating array offset */
	  if (is_candidate (stmt))
	    /* convert stmt */
	    expand_plusminus_mult(stmt);
	    
        }
      }
    }

  return 0;
}

namespace {

const pass_data pass_data_opt_array_offset =
{
  GIMPLE_PASS,				/* type */
  "opt_array_offset",			/* name */
  OPTGROUP_NONE,			/* optinfo_flags */
  true,					/* has_gate */
  true,					/* has_execute */
  TV_NONE,				/* tv_id */
  PROP_ssa,				/* properties_required */
  0,					/* properties_provided */
  0,					/* properties_destroyed */
  0,					/* todo_flags_start */
  ( TODO_verify_ssa
  | TODO_verify_stmts
  | TODO_update_ssa ),                 /* todo_flags_finish */
};

class pass_opt_array_offset : public gimple_opt_pass
{
public:
  pass_opt_array_offset (gcc::context *ctxt)
    : gimple_opt_pass (pass_data_opt_array_offset, ctxt)
  {}

  /* opt_pass methods: */
  bool gate () { return gate_opt_array_offset (); }
  unsigned int execute () { return execute_opt_array_offset (); }

}; // class pass_tracer

} // anon namespace

gimple_opt_pass *
make_pass_opt_array_offset (gcc::context *ctxt)
{
  return new pass_opt_array_offset (ctxt);
}
