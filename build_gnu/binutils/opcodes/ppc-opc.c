/* ppc-opc.c -- PowerPC opcode list
   Copyright (C) 1994-2014 Free Software Foundation, Inc.
   Written by Ian Lance Taylor, Cygnus Support

   This file is part of the GNU opcodes library.

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this file; see the file COPYING.  If not, write to the
   Free Software Foundation, 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#include "sysdep.h"
#include <stdio.h>
#include "opcode/ppc.h"
#include "opintl.h"

/* This file holds the PowerPC opcode table.  The opcode table
   includes almost all of the extended instruction mnemonics.  This
   permits the disassembler to use them, and simplifies the assembler
   logic, at the cost of increasing the table size.  The table is
   strictly constant data, so the compiler should be able to put it in
   the .text section.

   This file also holds the operand table.  All knowledge about
   inserting operands into instructions and vice-versa is kept in this
   file.  */

/* Local insertion and extraction functions.  */

static unsigned long insert_arx (unsigned long, long, ppc_cpu_t, const char **);
static long extract_arx (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_ary (unsigned long, long, ppc_cpu_t, const char **);
static long extract_ary (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_bat (unsigned long, long, ppc_cpu_t, const char **);
static long extract_bat (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_bba (unsigned long, long, ppc_cpu_t, const char **);
static long extract_bba (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_bdm (unsigned long, long, ppc_cpu_t, const char **);
static long extract_bdm (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_bdp (unsigned long, long, ppc_cpu_t, const char **);
static long extract_bdp (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_bo (unsigned long, long, ppc_cpu_t, const char **);
static long extract_bo (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_boe (unsigned long, long, ppc_cpu_t, const char **);
static long extract_boe (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_fxm (unsigned long, long, ppc_cpu_t, const char **);
static long extract_fxm (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_li20 (unsigned long, long, ppc_cpu_t, const char **);
static long extract_li20 (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_ls (unsigned long, long, ppc_cpu_t, const char **);
static unsigned long insert_mbe (unsigned long, long, ppc_cpu_t, const char **);
static long extract_mbe (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_mb6 (unsigned long, long, ppc_cpu_t, const char **);
static long extract_mb6 (unsigned long, ppc_cpu_t, int *);
static long extract_nb (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_nbi (unsigned long, long, ppc_cpu_t, const char **);
static unsigned long insert_nsi (unsigned long, long, ppc_cpu_t, const char **);
static long extract_nsi (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_oimm (unsigned long, long, ppc_cpu_t, const char **);
static long extract_oimm (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_ral (unsigned long, long, ppc_cpu_t, const char **);
static unsigned long insert_ram (unsigned long, long, ppc_cpu_t, const char **);
static unsigned long insert_raq (unsigned long, long, ppc_cpu_t, const char **);
static unsigned long insert_ras (unsigned long, long, ppc_cpu_t, const char **);
static unsigned long insert_rbs (unsigned long, long, ppc_cpu_t, const char **);
static long extract_rbs (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_rbx (unsigned long, long, ppc_cpu_t, const char **);
static unsigned long insert_rx (unsigned long, long, ppc_cpu_t, const char **);
static long extract_rx (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_ry (unsigned long, long, ppc_cpu_t, const char **);
static long extract_ry (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_sh6 (unsigned long, long, ppc_cpu_t, const char **);
static long extract_sh6 (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_sci8 (unsigned long, long, ppc_cpu_t, const char **);
static long extract_sci8 (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_sci8n (unsigned long, long, ppc_cpu_t, const char **);
static long extract_sci8n (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_sd4h (unsigned long, long, ppc_cpu_t, const char **);
static long extract_sd4h (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_sd4w (unsigned long, long, ppc_cpu_t, const char **);
static long extract_sd4w (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_spr (unsigned long, long, ppc_cpu_t, const char **);
static long extract_spr (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_sprg (unsigned long, long, ppc_cpu_t, const char **);
static long extract_sprg (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_tbr (unsigned long, long, ppc_cpu_t, const char **);
static long extract_tbr (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_xt6 (unsigned long, long, ppc_cpu_t, const char **);
static long extract_xt6 (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_xa6 (unsigned long, long, ppc_cpu_t, const char **);
static long extract_xa6 (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_xb6 (unsigned long, long, ppc_cpu_t, const char **);
static long extract_xb6 (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_xb6s (unsigned long, long, ppc_cpu_t, const char **);
static long extract_xb6s (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_xc6 (unsigned long, long, ppc_cpu_t, const char **);
static long extract_xc6 (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_dm (unsigned long, long, ppc_cpu_t, const char **);
static long extract_dm (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_vlesi (unsigned long, long, ppc_cpu_t, const char **);
static long extract_vlesi (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_vlensi (unsigned long, long, ppc_cpu_t, const char **);
static long extract_vlensi (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_vleui (unsigned long, long, ppc_cpu_t, const char **);
static long extract_vleui (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_vleil (unsigned long, long, ppc_cpu_t, const char **);
static long extract_vleil (unsigned long, ppc_cpu_t, int *);
static unsigned long insert_off_spe2 (unsigned long, long, ppc_cpu_t, const char **);
static unsigned long insert_Ddd (unsigned long, long, ppc_cpu_t, const char **);



/* Auxiliary functions from GCC MD for RS6000 */
#define TARGET_32BIT 1
#define HOST_WIDE_INT long
typedef unsigned char bool;
#define true (1==1)
#define false (!true)

/* from predicates.md */
static bool vle_reg_operand (HOST_WIDE_INT reg);

/* from rs6000.c */
static bool valid_sci8_immediate (HOST_WIDE_INT ival);

/* from constarints.md */
static bool satisfies_constraint_I (HOST_WIDE_INT ival);
static bool satisfies_constraint_K (HOST_WIDE_INT ival);
static bool satisfies_constraint_L (HOST_WIDE_INT ival);
static bool satisfies_constraint_kli20 (HOST_WIDE_INT ival);
static bool satisfies_constraint_kmsd4 (HOST_WIDE_INT ival);
static bool satisfies_constraint_kmmd8 (HOST_WIDE_INT ival);
static bool satisfies_constraint_koim5 (HOST_WIDE_INT ival);
static bool satisfies_constraint_ksci8 (HOST_WIDE_INT ival);
#if 0
static bool satisfies_constraint_kscp8 (HOST_WIDE_INT ival);
static bool satisfies_constraint_kscI8 (HOST_WIDE_INT ival);
#endif
static bool  satisfies_constraint_kuim5(HOST_WIDE_INT ival);
static bool  satisfies_constraint_kuim7(HOST_WIDE_INT ival);

/* Translation functions. */
static int translate_addi (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_addic (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_addis (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_andi_dot (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_andis_dot (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_b (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_bc (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_bcl (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_blr (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_cmpi (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_cmpli (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_crxxx (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_isync (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_lbz (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_lbzu (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_lha (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_lhau (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_lhz (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_lhzu (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_li (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_lis (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_lmw (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_lwz (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_lwzu (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_mcrf (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_mfdec (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_mulli (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_mr (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_mtdec (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_nop (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_or (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_ori (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_oris (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_rfci (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_rfdi (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_rfi (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_rfmci (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_rlwimi (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_rlwinm (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_rlwnm (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_sc (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_stb (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_stbu (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_sth (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_sthu (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_stmw (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_stw (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_stwu (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_subi (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_subic (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_subis (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_subfic (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);
static int translate_xori (unsigned long, const struct powerpc_opcode *, const char **, char *, const char **);



/* The operands table.

   The fields are bitm, shift, insert, extract, flags.

   We used to put parens around the various additions, like the one
   for BA just below.  However, that caused trouble with feeble
   compilers with a limit on depth of a parenthesized expression, like
   (reportedly) the compiler in Microsoft Developer Studio 5.  So we
   omit the parens, since the macros are never used in a context where
   the addition will be ambiguous.  */

const struct powerpc_operand powerpc_operands[] =
{
  /* The zero index is used to indicate the end of the list of
     operands.  */
#define UNUSED 0
  { 0, 0, NULL, NULL, 0 },

  /* The BA field in an XL form instruction.  */
#define BA UNUSED + 1
  /* The BI field in a B form or XL form instruction.  */
#define BI BA
#define BI_MASK (0x1f << 16)
  { 0x1f, 16, NULL, NULL, PPC_OPERAND_CR_BIT },

  /* The BA field in an XL form instruction when it must be the same
     as the BT field in the same instruction.  */
#define BAT BA + 1
  { 0x1f, 16, insert_bat, extract_bat, PPC_OPERAND_FAKE },

  /* The BB field in an XL form instruction.  */
#define BB BAT + 1
#define BB_MASK (0x1f << 11)
  { 0x1f, 11, NULL, NULL, PPC_OPERAND_CR_BIT },

  /* The BB field in an XL form instruction when it must be the same
     as the BA field in the same instruction.  */
#define BBA BB + 1
  /* The VB field in a VX form instruction when it must be the same
     as the VA field in the same instruction.  */
#define VBA BBA
  { 0x1f, 11, insert_bba, extract_bba, PPC_OPERAND_FAKE },

  /* The BD field in a B form instruction.  The lower two bits are
     forced to zero.  */
#define BD BBA + 1
  { 0xfffc, 0, NULL, NULL, PPC_OPERAND_RELATIVE | PPC_OPERAND_SIGNED },

  /* The BD field in a B form instruction when absolute addressing is
     used.  */
#define BDA BD + 1
  { 0xfffc, 0, NULL, NULL, PPC_OPERAND_ABSOLUTE | PPC_OPERAND_SIGNED },

  /* The BD field in a B form instruction when the - modifier is used.
     This sets the y bit of the BO field appropriately.  */
#define BDM BDA + 1
  { 0xfffc, 0, insert_bdm, extract_bdm,
      PPC_OPERAND_RELATIVE | PPC_OPERAND_SIGNED },

  /* The BD field in a B form instruction when the - modifier is used
     and absolute address is used.  */
#define BDMA BDM + 1
  { 0xfffc, 0, insert_bdm, extract_bdm,
      PPC_OPERAND_ABSOLUTE | PPC_OPERAND_SIGNED },

  /* The BD field in a B form instruction when the + modifier is used.
     This sets the y bit of the BO field appropriately.  */
#define BDP BDMA + 1
  { 0xfffc, 0, insert_bdp, extract_bdp,
      PPC_OPERAND_RELATIVE | PPC_OPERAND_SIGNED },

  /* The BD field in a B form instruction when the + modifier is used
     and absolute addressing is used.  */
#define BDPA BDP + 1
  { 0xfffc, 0, insert_bdp, extract_bdp,
      PPC_OPERAND_ABSOLUTE | PPC_OPERAND_SIGNED },

  /* The BF field in an X or XL form instruction.  */
#define BF BDPA + 1
  /* The CRFD field in an X form instruction.  */
#define CRFD BF
  /* The CRD field in an XL form instruction.  */
#define CRD BF
  { 0x7, 23, NULL, NULL, PPC_OPERAND_CR_REG },

  /* The BF field in an X or XL form instruction.  */
#define BFF BF + 1
  { 0x7, 23, NULL, NULL, 0 },

  /* An optional BF field.  This is used for comparison instructions,
     in which an omitted BF field is taken as zero.  */
#define OBF BFF + 1
  { 0x7, 23, NULL, NULL, PPC_OPERAND_CR_REG | PPC_OPERAND_OPTIONAL },

  /* The BFA field in an X or XL form instruction.  */
#define BFA OBF + 1
  { 0x7, 18, NULL, NULL, PPC_OPERAND_CR_REG },

  /* The BO field in a B form instruction.  Certain values are
     illegal.  */
#define BO BFA + 1
#define BO_MASK (0x1f << 21)
  { 0x1f, 21, insert_bo, extract_bo, 0 },

  /* The BO field in a B form instruction when the + or - modifier is
     used.  This is like the BO field, but it must be even.  */
#define BOE BO + 1
  { 0x1e, 21, insert_boe, extract_boe, 0 },

#define BH BOE + 1
  { 0x3, 11, NULL, NULL, PPC_OPERAND_OPTIONAL },

  /* The BT field in an X or XL form instruction.  */
#define BT BH + 1
  { 0x1f, 21, NULL, NULL, PPC_OPERAND_CR_BIT },

  /* The BI16 field in a BD8 form instruction.  */
#define BI16 BT + 1
  { 0x3, 8, NULL, NULL, PPC_OPERAND_CR_BIT },

  /* The BI32 field in a BD15 form instruction.  */
#define BI32 BI16 + 1
  { 0xf, 16, NULL, NULL, PPC_OPERAND_CR_BIT },

  /* The BO32 field in a BD15 form instruction.  */
#define BO32 BI32 + 1
  { 0x3, 20, NULL, NULL, 0 },

  /* The B8 field in a BD8 form instruction.  */
#define B8 BO32 + 1
  { 0x1fe, -1, NULL, NULL, PPC_OPERAND_RELATIVE | PPC_OPERAND_SIGNED },

  /* The B15 field in a BD15 form instruction.  The lowest bit is
     forced to zero.  */
#define B15 B8 + 1
  { 0xfffe, 0, NULL, NULL, PPC_OPERAND_RELATIVE | PPC_OPERAND_SIGNED },

  /* The B24 field in a BD24 form instruction.  The lowest bit is
     forced to zero.  */
#define B24 B15 + 1
  { 0x1fffffe, 0, NULL, NULL, PPC_OPERAND_RELATIVE | PPC_OPERAND_SIGNED },

  /* The condition register number portion of the BI field in a B form
     or XL form instruction.  This is used for the extended
     conditional branch mnemonics, which set the lower two bits of the
     BI field.  This field is optional.  */
#define CR B24 + 1
  { 0x7, 18, NULL, NULL, PPC_OPERAND_CR_REG | PPC_OPERAND_OPTIONAL },

  /* The CRB field in an X form instruction.  */
#define CRB CR + 1
  /* The MB field in an M form instruction.  */
#define MB CRB
#define MB_MASK (0x1f << 6)
  { 0x1f, 6, NULL, NULL, 0 },

  /* The CRD32 field in an XL form instruction.  */
#define CRD32 CRB + 1
  { 0x3, 21, NULL, NULL, PPC_OPERAND_CR_REG },

  /* The CRFS field in an X form instruction.  */
#define CRFS CRD32 + 1
  { 0x7, 0, NULL, NULL, PPC_OPERAND_CR_REG },

#define CRS CRFS + 1
  { 0x3, 18, NULL, NULL, PPC_OPERAND_CR_REG | PPC_OPERAND_OPTIONAL },

  /* The CT field in an X form instruction.  */
#define CT CRS + 1
  /* The MO field in an mbar instruction.  */
#define MO CT
  { 0x1f, 21, NULL, NULL, PPC_OPERAND_OPTIONAL },

  /* The D field in a D form instruction.  This is a displacement off
     a register, and implies that the next operand is a register in
     parentheses.  */
#define D CT + 1
  { 0xffff, 0, NULL, NULL, PPC_OPERAND_PARENS | PPC_OPERAND_SIGNED },

  /* The D8 field in a D form instruction.  This is a displacement off
     a register, and implies that the next operand is a register in
     parentheses.  */
#define D8 D + 1
  { 0xff, 0, NULL, NULL, PPC_OPERAND_PARENS | PPC_OPERAND_SIGNED },

  /* The DQ field in a DQ form instruction.  This is like D, but the
     lower four bits are forced to zero. */
#define DQ D8 + 1
  { 0xfff0, 0, NULL, NULL,
    PPC_OPERAND_PARENS | PPC_OPERAND_SIGNED | PPC_OPERAND_DQ },

  /* The DS field in a DS form instruction.  This is like D, but the
     lower two bits are forced to zero.  */
#define DS DQ + 1
  { 0xfffc, 0, NULL, NULL,
    PPC_OPERAND_PARENS | PPC_OPERAND_SIGNED | PPC_OPERAND_DS },

  /* The DUIS or BHRBE fields in a XFX form instruction, 10 bits
     unsigned imediate */
#define DUIS DS + 1
#define BHRBE DUIS
  { 0x3ff, 11, NULL, NULL, 0 },

  /* The E field in a wrteei instruction.  */
  /* And the W bit in the pair singles instructions.  */
  /* And the ST field in a VX form instruction.  */
#define E DUIS + 1
#define PSW E
#define ST E
  { 0x1, 15, NULL, NULL, 0 },

  /* The FL1 field in a POWER SC form instruction.  */
#define FL1 E + 1
  /* The U field in an X form instruction.  */
#define U FL1
  { 0xf, 12, NULL, NULL, 0 },

  /* The FL2 field in a POWER SC form instruction.  */
#define FL2 FL1 + 1
  { 0x7, 2, NULL, NULL, 0 },

  /* The FLM field in an XFL form instruction.  */
#define FLM FL2 + 1
  { 0xff, 17, NULL, NULL, 0 },

  /* The FRA field in an X or A form instruction.  */
#define FRA FLM + 1
#define FRA_MASK (0x1f << 16)
  { 0x1f, 16, NULL, NULL, PPC_OPERAND_FPR },

  /* The FRAp field of DFP instructions.  */
#define FRAp FRA + 1
  { 0x1e, 16, NULL, NULL, PPC_OPERAND_FPR },

  /* The FRB field in an X or A form instruction.  */
#define FRB FRAp + 1
#define FRB_MASK (0x1f << 11)
  { 0x1f, 11, NULL, NULL, PPC_OPERAND_FPR },

  /* The FRBp field of DFP instructions.  */
#define FRBp FRB + 1
  { 0x1e, 11, NULL, NULL, PPC_OPERAND_FPR },

  /* The FRC field in an A form instruction.  */
#define FRC FRBp + 1
#define FRC_MASK (0x1f << 6)
  { 0x1f, 6, NULL, NULL, PPC_OPERAND_FPR },

  /* The FRS field in an X form instruction or the FRT field in a D, X
     or A form instruction.  */
#define FRS FRC + 1
#define FRT FRS
  { 0x1f, 21, NULL, NULL, PPC_OPERAND_FPR },

  /* The FRSp field of stfdp or the FRTp field of lfdp and DFP
     instructions.  */
#define FRSp FRS + 1
#define FRTp FRSp
  { 0x1e, 21, NULL, NULL, PPC_OPERAND_FPR },

  /* The FXM field in an XFX instruction.  */
#define FXM FRSp + 1
  { 0xff, 12, insert_fxm, extract_fxm, 0 },

  /* Power4 version for mfcr.  */
#define FXM4 FXM + 1
  { 0xff, 12, insert_fxm, extract_fxm, PPC_OPERAND_OPTIONAL },

  /* The IMM20 field in an LI instruction.  */
#define IMM20 FXM4 + 1
  { 0xfffff, PPC_OPSHIFT_INV, insert_li20, extract_li20, PPC_OPERAND_SIGNED},

  /* The L field in a D or X form instruction.  */
#define L IMM20 + 1
  /* The R field in a HTM X form instruction.  */
#define HTM_R L
  { 0x1, 21, NULL, NULL, PPC_OPERAND_OPTIONAL },

  /* The LEV field in a POWER SVC form instruction.  */
#define SVC_LEV L + 1
  { 0x7f, 5, NULL, NULL, 0 },

  /* The LEV field in an SC form instruction.  */
#define LEV SVC_LEV + 1
  { 0x7f, 5, NULL, NULL, PPC_OPERAND_OPTIONAL },

  /* The LI field in an I form instruction.  The lower two bits are
     forced to zero.  */
#define LI LEV + 1
  { 0x3fffffc, 0, NULL, NULL, PPC_OPERAND_RELATIVE | PPC_OPERAND_SIGNED },

  /* The LI field in an I form instruction when used as an absolute
     address.  */
#define LIA LI + 1
  { 0x3fffffc, 0, NULL, NULL, PPC_OPERAND_ABSOLUTE | PPC_OPERAND_SIGNED },

  /* The LS or WC field in an X (sync or wait) form instruction.  */
#define LS LIA + 1
#define WC LS
  { 0x3, 21, NULL, NULL, PPC_OPERAND_OPTIONAL },

  /* The ME field in an M form instruction.  */
#define ME LS + 1
#define ME_MASK (0x1f << 1)
  { 0x1f, 1, NULL, NULL, 0 },

  /* The MB and ME fields in an M form instruction expressed a single
     operand which is a bitmask indicating which bits to select.  This
     is a two operand form using PPC_OPERAND_NEXT.  See the
     description in opcode/ppc.h for what this means.  */
#define MBE ME + 1
  { 0x1f, 6, NULL, NULL, PPC_OPERAND_OPTIONAL | PPC_OPERAND_NEXT },
  { -1, 0, insert_mbe, extract_mbe, 0 },

  /* The MB or ME field in an MD or MDS form instruction.  The high
     bit is wrapped to the low end.  */
#define MB6 MBE + 2
#define ME6 MB6
#define MB6_MASK (0x3f << 5)
  { 0x3f, 5, insert_mb6, extract_mb6, 0 },

  /* The NB field in an X form instruction.  The value 32 is stored as
     0.  */
#define NB MB6 + 1
  { 0x1f, 11, NULL, extract_nb, PPC_OPERAND_PLUS1 },

  /* The NBI field in an lswi instruction, which has special value
     restrictions.  The value 32 is stored as 0.  */
#define NBI NB + 1
  { 0x1f, 11, insert_nbi, extract_nb, PPC_OPERAND_PLUS1 },

  /* The NSI field in a D form instruction.  This is the same as the
     SI field, only negated.  */
#define NSI NBI + 1
  { 0xffff, 0, insert_nsi, extract_nsi,
      PPC_OPERAND_NEGATIVE | PPC_OPERAND_SIGNED },

  /* The RA field in an D, DS, DQ, X, XO, M, or MDS form instruction.  */
#define RA NSI + 1
#define RA_MASK (0x1f << 16)
  { 0x1f, 16, NULL, NULL, PPC_OPERAND_GPR },

  /* As above, but 0 in the RA field means zero, not r0.  */
#define RA0 RA + 1
  { 0x1f, 16, NULL, NULL, PPC_OPERAND_GPR_0 },

  /* The RA field in the DQ form lq or an lswx instruction, which have special
     value restrictions.  */
#define RAQ RA0 + 1
#define RAX RAQ
  { 0x1f, 16, insert_raq, NULL, PPC_OPERAND_GPR_0 },

  /* The RA field in a D or X form instruction which is an updating
     load, which means that the RA field may not be zero and may not
     equal the RT field.  */
#define RAL RAQ + 1
  { 0x1f, 16, insert_ral, NULL, PPC_OPERAND_GPR_0 },

  /* The RA field in an lmw instruction, which has special value
     restrictions.  */
#define RAM RAL + 1
  { 0x1f, 16, insert_ram, NULL, PPC_OPERAND_GPR_0 },

  /* The RA field in a D or X form instruction which is an updating
     store or an updating floating point load, which means that the RA
     field may not be zero.  */
#define RAS RAM + 1
  { 0x1f, 16, insert_ras, NULL, PPC_OPERAND_GPR_0 },

  /* The RA field of the tlbwe, dccci and iccci instructions,
     which are optional.  */
#define RAOPT RAS + 1
  { 0x1f, 16, NULL, NULL, PPC_OPERAND_GPR | PPC_OPERAND_OPTIONAL },

  /* The RB field in an X, XO, M, or MDS form instruction.  */
#define RB RAOPT + 1
#define RB_MASK (0x1f << 11)
  { 0x1f, 11, NULL, NULL, PPC_OPERAND_GPR },

  /* The RB field in an X form instruction when it must be the same as
     the RS field in the instruction.  This is used for extended
     mnemonics like mr.  */
#define RBS RB + 1
  { 0x1f, 11, insert_rbs, extract_rbs, PPC_OPERAND_FAKE },

  /* The RB field in an lswx instruction, which has special value
     restrictions.  */
#define RBX RBS + 1
  { 0x1f, 11, insert_rbx, NULL, PPC_OPERAND_GPR },

  /* The RB field of the dccci and iccci instructions, which are optional.  */
#define RBOPT RBX + 1
  { 0x1f, 11, NULL, NULL, PPC_OPERAND_GPR | PPC_OPERAND_OPTIONAL },

  /* The RS field in a D, DS, X, XFX, XS, M, MD or MDS form
     instruction or the RT field in a D, DS, X, XFX or XO form
     instruction.  */
#define RS RBOPT + 1
#define RT RS
#define RT_MASK (0x1f << 21)
#define RD RS
  { 0x1f, 21, NULL, NULL, PPC_OPERAND_GPR },

  /* The RS and RT fields of the DS form stq and DQ form lq instructions,
     which have special value restrictions.  */
#define RSQ RS + 1
#define RTQ RSQ
  { 0x1e, 21, NULL, NULL, PPC_OPERAND_GPR },

  /* The RS field of the tlbwe instruction, which is optional.  */
#define RSO RSQ + 1
#define RTO RSO
  { 0x1f, 21, NULL, NULL, PPC_OPERAND_GPR | PPC_OPERAND_OPTIONAL },

  /* The RX field of the SE_RR form instruction.  */
#define RX RSO + 1
  { 0x1f, PPC_OPSHIFT_INV, insert_rx, extract_rx, PPC_OPERAND_GPR },

  /* The ARX field of the SE_RR form instruction.  */
#define ARX RX + 1
  { 0x1f, PPC_OPSHIFT_INV, insert_arx, extract_arx, PPC_OPERAND_GPR },

  /* The RY field of the SE_RR form instruction.  */
#define RY ARX + 1
#define RZ RY
  { 0x1f, PPC_OPSHIFT_INV, insert_ry, extract_ry, PPC_OPERAND_GPR },

  /* The ARY field of the SE_RR form instruction.  */
#define ARY RY + 1
  { 0x1f, PPC_OPSHIFT_INV, insert_ary, extract_ary, PPC_OPERAND_GPR },

  /* The SCLSCI8 field in a D form instruction.  */
#define SCLSCI8 ARY + 1
  { 0xffffffff, PPC_OPSHIFT_INV, insert_sci8, extract_sci8, 0 },

  /* The SCLSCI8N field in a D form instruction.  This is the same as the
     SCLSCI8 field, only negated.  */
#define SCLSCI8N SCLSCI8 + 1
  { 0xffffffff, PPC_OPSHIFT_INV, insert_sci8n, extract_sci8n,
      PPC_OPERAND_NEGATIVE | PPC_OPERAND_SIGNED },

  /* The SD field of the SD4 form instruction.  */
#define SE_SD SCLSCI8N + 1
  { 0xf, 8, NULL, NULL, PPC_OPERAND_PARENS },

  /* The SD field of the SD4 form instruction, for halfword.  */
#define SE_SDH SE_SD + 1
  { 0x1e, PPC_OPSHIFT_INV, insert_sd4h, extract_sd4h, PPC_OPERAND_PARENS },

  /* The SD field of the SD4 form instruction, for word.  */
#define SE_SDW SE_SDH + 1
  { 0x3c, PPC_OPSHIFT_INV, insert_sd4w, extract_sd4w, PPC_OPERAND_PARENS },

  /* The SH field in an X or M form instruction.  */
#define SH SE_SDW + 1
#define SH_MASK (0x1f << 11)
  /* The other UIMM field in a EVX form instruction.  */
#define EVUIMM SH
  { 0x1f, 11, NULL, NULL, 0 },

  /* The SI field in a HTM X form instruction.  */
#define HTM_SI SH + 1
  { 0x1f, 11, NULL, NULL, PPC_OPERAND_SIGNED },

  /* The SH field in an MD form instruction.  This is split.  */
#define SH6 HTM_SI + 1
#define SH6_MASK ((0x1f << 11) | (1 << 1))
  { 0x3f, PPC_OPSHIFT_INV, insert_sh6, extract_sh6, 0 },

  /* The SH field of the tlbwe instruction, which is optional.  */
#define SHO SH6 + 1
  /* The ELEV field in an ESC form instruction.  */
#define ELEV SHO
  { 0x1f, 11, NULL, NULL, PPC_OPERAND_OPTIONAL },

  /* The SI field in a D form instruction.  */
#define SI SHO + 1
  { 0xffff, 0, NULL, NULL, PPC_OPERAND_SIGNED },

  /* The SI field in a D form instruction when we accept a wide range
     of positive values.  */
#define SISIGNOPT SI + 1
  { 0xffff, 0, NULL, NULL, PPC_OPERAND_SIGNED | PPC_OPERAND_SIGNOPT },

  /* The SI8 field in a D form instruction.  */
#define SI8 SISIGNOPT + 1
  { 0xff, 0, NULL, NULL, PPC_OPERAND_SIGNED },

  /* The SPR field in an XFX form instruction.  This is flipped--the
     lower 5 bits are stored in the upper 5 and vice- versa.  */
#define SPR SI8 + 1
#define PMR SPR
#define TMR SPR
#define SPR_MASK (0x3ff << 11)
  { 0x3ff, 11, insert_spr, extract_spr, 0 },

  /* The BAT index number in an XFX form m[ft]ibat[lu] instruction.  */
#define SPRBAT SPR + 1
#define SPRBAT_MASK (0x3 << 17)
  { 0x3, 17, NULL, NULL, 0 },

  /* The SPRG register number in an XFX form m[ft]sprg instruction.  */
#define SPRG SPRBAT + 1
  { 0x1f, 16, insert_sprg, extract_sprg, 0 },

  /* The SR field in an X form instruction.  */
#define SR SPRG + 1
  /* The 4-bit UIMM field in a VX form instruction.  */
#define UIMM4 SR
  { 0xf, 16, NULL, NULL, 0 },

  /* The STRM field in an X AltiVec form instruction.  */
#define STRM SR + 1
  /* The T field in a tlbilx form instruction.  */
#define T STRM
  { 0x3, 21, NULL, NULL, 0 },

  /* The ESYNC field in an X (sync) form instruction.  */
#define ESYNC STRM + 1
  { 0xf, 16, insert_ls, NULL, PPC_OPERAND_OPTIONAL },

  /* The SV field in a POWER SC form instruction.  */
#define SV ESYNC + 1
  { 0x3fff, 2, NULL, NULL, 0 },

  /* The TBR field in an XFX form instruction.  This is like the SPR
     field, but it is optional.  */
#define TBR SV + 1
  { 0x3ff, 11, insert_tbr, extract_tbr, PPC_OPERAND_OPTIONAL },

  /* The TO field in a D or X form instruction.  */
#define TO TBR + 1
#define DUI TO
#define TO_MASK (0x1f << 21)
  { 0x1f, 21, NULL, NULL, 0 },

  /* The UI field in a D form instruction.  */
#define UI TO + 1
  { 0xffff, 0, NULL, NULL, 0 },

#define UISIGNOPT UI + 1
  { 0xffff, 0, NULL, NULL, PPC_OPERAND_SIGNOPT },

  /* The IMM field in an SE_IM5 instruction.  */
#define UI5 UISIGNOPT + 1
  { 0x1f, 4, NULL, NULL, 0 },

  /* The OIMM field in an SE_OIM5 instruction.  */
#define OIMM5 UI5 + 1
  { 0x1f, PPC_OPSHIFT_INV, insert_oimm, extract_oimm, PPC_OPERAND_PLUS1 },

  /* The UI7 field in an SE_LI instruction.  */
#define UI7 OIMM5 + 1
  { 0x7f, 4, NULL, NULL, 0 },

  /* The VA field in a VA, VX or VXR form instruction.  */
#define VA UI7 + 1
  { 0x1f, 16, NULL, NULL, PPC_OPERAND_VR },

  /* The VB field in a VA, VX or VXR form instruction.  */
#define VB VA + 1
  { 0x1f, 11, NULL, NULL, PPC_OPERAND_VR },

  /* The VC field in a VA form instruction.  */
#define VC VB + 1
  { 0x1f, 6, NULL, NULL, PPC_OPERAND_VR },

  /* The VD or VS field in a VA, VX, VXR or X form instruction.  */
#define VD VC + 1
#define VS VD
  { 0x1f, 21, NULL, NULL, PPC_OPERAND_VR },

  /* The SIMM field in a VX form instruction, and TE in Z form.  */
#define SIMM VD + 1
#define TE SIMM
  { 0x1f, 16, NULL, NULL, PPC_OPERAND_SIGNED},

  /* The UIMM field in a VX form instruction.  */
#define UIMM SIMM + 1
#define DCTL UIMM
  { 0x1f, 16, NULL, NULL, 0 },

  /* The 3-bit UIMM field in a VX form instruction.  */
#define UIMM3 UIMM + 1
  { 0x7, 16, NULL, NULL, 0 },

  /* The SIX field in a VX form instruction.  */
#define SIX UIMM3 + 1
  /* The MMMM field in a VX form instruction for SPE2  */
#define MMMM SIX
  { 0xf, 11, NULL, NULL, 0 },

  /* The PS field in a VX form instruction.  */
#define PS SIX + 1
  { 0x1, 9, NULL, NULL, 0 },

  /* The SHB field in a VA form instruction.  */
#define SHB PS + 1
  { 0xf, 6, NULL, NULL, 0 },

  /* The other UIMM field in a half word EVX form instruction.  */
#define EVUIMM_2 SHB + 1
  { 0x3e, 10, NULL, NULL, PPC_OPERAND_PARENS },

  /* The other UIMM field in a word EVX form instruction.  */
#define EVUIMM_4 EVUIMM_2 + 1
  { 0x7c, 9, NULL, NULL, PPC_OPERAND_PARENS },

  /* The other UIMM field in a double EVX form instruction.  */
#define EVUIMM_8 EVUIMM_4 + 1
  { 0xf8, 8, NULL, NULL, PPC_OPERAND_PARENS },

  /* The WS field.  */
#define WS EVUIMM_8 + 1
  /* The NNN field in a VX form instruction for SPE2  */
#define NNN WS
  { 0x7, 11, NULL, NULL, 0 },

  /* PowerPC paired singles extensions.  */
  /* W bit in the pair singles instructions for x type instructions.  */
#define PSWM WS + 1
  /* The BO16 field in a BD8 form instruction.  */
#define BO16 PSWM
  {  0x1, 10, 0, 0, 0 },

  /* IDX bits for quantization in the pair singles instructions.  */
#define PSQ PSWM + 1
  {  0x7, 12, 0, 0, 0 },

  /* IDX bits for quantization in the pair singles x-type instructions.  */
#define PSQM PSQ + 1
  {  0x7, 7, 0, 0, 0 },

  /* Smaller D field for quantization in the pair singles instructions.  */
#define PSD PSQM + 1
  {  0xfff, 0, 0, 0,  PPC_OPERAND_PARENS | PPC_OPERAND_SIGNED },

#define A_L PSD + 1
#define W A_L
#define MTMSRD_L W
  { 0x1, 16, NULL, NULL, PPC_OPERAND_OPTIONAL },

#define RMC MTMSRD_L + 1
  { 0x3, 9, NULL, NULL, 0 },

#define R RMC + 1
  { 0x1, 16, NULL, NULL, 0 },

#define SP R + 1
  { 0x3, 19, NULL, NULL, 0 },

#define S SP + 1
  { 0x1, 20, NULL, NULL, 0 },

  /* The S field in a XL form instruction.  */
#define SXL S + 1
  { 0x1, 11, NULL, NULL, PPC_OPERAND_OPTIONAL },

  /* SH field starting at bit position 16.  */
#define SH16 SXL + 1
  /* The DCM and DGM fields in a Z form instruction.  */
#define DCM SH16
#define DGM DCM
  { 0x3f, 10, NULL, NULL, 0 },

  /* The EH field in larx instruction.  */
#define EH SH16 + 1
  { 0x1, 0, NULL, NULL, PPC_OPERAND_OPTIONAL },

  /* The L field in an mtfsf or XFL form instruction.  */
  /* The A field in a HTM X form instruction.  */
#define XFL_L EH + 1
#define HTM_A XFL_L
  { 0x1, 25, NULL, NULL, PPC_OPERAND_OPTIONAL},

  /* Xilinx APU related masks and macros */
#define FCRT XFL_L + 1
#define FCRT_MASK (0x1f << 21)
  { 0x1f, 21, 0, 0, PPC_OPERAND_FCR },

  /* Xilinx FSL related masks and macros */  
#define FSL FCRT + 1
#define FSL_MASK (0x1f << 11)
  { 0x1f, 11, 0, 0, PPC_OPERAND_FSL },  

  /* Xilinx UDI related masks and macros */  
#define URT FSL + 1
  { 0x1f, 21, 0, 0, PPC_OPERAND_UDI },

#define URA URT + 1
  { 0x1f, 16, 0, 0, PPC_OPERAND_UDI },

#define URB URA + 1
  { 0x1f, 11, 0, 0, PPC_OPERAND_UDI },

#define URC URB + 1
  { 0x1f, 6, 0, 0, PPC_OPERAND_UDI },

  /* The VLESIMM field in a D form instruction.  */
#define VLESIMM URC + 1
  { 0xffff, PPC_OPSHIFT_INV, insert_vlesi, extract_vlesi,
      PPC_OPERAND_SIGNED | PPC_OPERAND_SIGNOPT },

  /* The VLENSIMM field in a D form instruction.  */
#define VLENSIMM VLESIMM + 1
  { 0xffff, PPC_OPSHIFT_INV, insert_vlensi, extract_vlensi,
      PPC_OPERAND_NEGATIVE | PPC_OPERAND_SIGNED | PPC_OPERAND_SIGNOPT },

  /* The VLEUIMM field in a D form instruction.  */
#define VLEUIMM VLENSIMM + 1
  { 0xffff, PPC_OPSHIFT_INV, insert_vleui, extract_vleui, 0 },

  /* The VLEUIMML field in a D form instruction.  */
#define VLEUIMML VLEUIMM + 1
  { 0xffff, PPC_OPSHIFT_INV, insert_vleil, extract_vleil, 0 },

  /* The XT and XS fields in an XX1 or XX3 form instruction.  This is split.  */
#define XS6 VLEUIMML + 1
#define XT6 XS6
  { 0x3f, PPC_OPSHIFT_INV, insert_xt6, extract_xt6, PPC_OPERAND_VSR },

  /* The XA field in an XX3 form instruction.  This is split.  */
#define XA6 XT6 + 1
  { 0x3f, PPC_OPSHIFT_INV, insert_xa6, extract_xa6, PPC_OPERAND_VSR },

  /* The XB field in an XX2 or XX3 form instruction.  This is split.  */
#define XB6 XA6 + 1
  { 0x3f, PPC_OPSHIFT_INV, insert_xb6, extract_xb6, PPC_OPERAND_VSR },

  /* The XB field in an XX3 form instruction when it must be the same as
     the XA field in the instruction.  This is used in extended mnemonics
     like xvmovdp.  This is split.  */
#define XB6S XB6 + 1
  { 0x3f, PPC_OPSHIFT_INV, insert_xb6s, extract_xb6s, PPC_OPERAND_FAKE },

  /* The XC field in an XX4 form instruction.  This is split.  */
#define XC6 XB6S + 1
  { 0x3f, PPC_OPSHIFT_INV, insert_xc6, extract_xc6, PPC_OPERAND_VSR },

  /* The DM or SHW field in an XX3 form instruction.  */
#define DM XC6 + 1
#define SHW DM
  { 0x3, 8, NULL, NULL, 0 },

  /* The DM field in an extended mnemonic XX3 form instruction.  */
#define DMEX DM + 1
  { 0x3, 8, insert_dm, extract_dm, 0 },

  /* The UIM field in an XX2 form instruction.  */
#define UIM DMEX + 1
  /* The 2-bit UIMM field in a VX form instruction.  */
#define UIMM2 UIM
  { 0x3, 16, NULL, NULL, 0 },

#define ERAT_T UIM + 1
  { 0x7, 21, NULL, NULL, 0 },

#define VX_OFF ERAT_T + 1
  { 0x3, 0, NULL, NULL, 0 },
  
#define VX_OFF_SPE2 VX_OFF + 1
  { 0x7, 0, insert_off_spe2, NULL, 0 },

#define BBB VX_OFF_SPE2 + 1
  { 0x7, 13, NULL, NULL, 0 },
  
#define DDD BBB + 1
  { 0x3, 11, insert_Ddd, NULL, 0 },  

#define DD DDD + 1
  { 0x3, 11, NULL, NULL, 0 },

#define HH DD + 1
  { 0x3, 13, NULL, NULL, 0 },  
  
};

const unsigned int num_powerpc_operands = (sizeof (powerpc_operands)
					   / sizeof (powerpc_operands[0]));

/* The functions used to insert and extract complicated operands.  */

/* The ARX, ARY, RX and RY operands are alternate encodings of GPRs.  */

static unsigned long
insert_arx (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value >= 8 && value < 24)
    return insn | ((value - 8) & 0xf);
  else
    {
      *errmsg = _("invalid register");
      return 0;
    }
}

static long
extract_arx (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid ATTRIBUTE_UNUSED)
{ 
  return (insn & 0xf) + 8;
}

static unsigned long
insert_ary (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value >= 8 && value < 24)
    return insn | (((value - 8) & 0xf) << 4);
  else
    {
      *errmsg = _("invalid register");
      return 0;
    }
}

static long
extract_ary (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid ATTRIBUTE_UNUSED)
{
  return ((insn >> 4) & 0xf) + 8;
}

static unsigned long
insert_rx (unsigned long insn,
	   long value,
	   ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	   const char **errmsg)
{
  if (value >= 0 && value < 8)
    return insn | value;
  else if (value >= 24 && value <= 31)
    return insn | (value - 16);
  else
    {
      *errmsg = _("invalid register");
      return 0;
    }
}

static long
extract_rx (unsigned long insn,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    int *invalid ATTRIBUTE_UNUSED)
{
  int value = insn & 0xf;
  if (value >= 0 && value < 8)
    return value;
  else
    return value + 16;
}

static unsigned long
insert_ry (unsigned long insn,
	   long value,
	   ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	   const char **errmsg)
{
  if (value >= 0 && value < 8)
    return insn | (value << 4);
  else if (value >= 24 && value <= 31)
    return insn | ((value - 16) << 4);
  else
    {
      *errmsg = _("invalid register");
      return 0;
    }
}

static long
extract_ry (unsigned long insn,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    int *invalid ATTRIBUTE_UNUSED)
{
  int value = (insn >> 4) & 0xf;
  if (value >= 0 && value < 8)
    return value;
  else
    return value + 16;
}

/* The BA field in an XL form instruction when it must be the same as
   the BT field in the same instruction.  This operand is marked FAKE.
   The insertion function just copies the BT field into the BA field,
   and the extraction function just checks that the fields are the
   same.  */

static unsigned long
insert_bat (unsigned long insn,
	    long value ATTRIBUTE_UNUSED,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | (((insn >> 21) & 0x1f) << 16);
}

static long
extract_bat (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid)
{
  if (((insn >> 21) & 0x1f) != ((insn >> 16) & 0x1f))
    *invalid = 1;
  return 0;
}

/* The BB field in an XL form instruction when it must be the same as
   the BA field in the same instruction.  This operand is marked FAKE.
   The insertion function just copies the BA field into the BB field,
   and the extraction function just checks that the fields are the
   same.  */

static unsigned long
insert_bba (unsigned long insn,
	    long value ATTRIBUTE_UNUSED,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | (((insn >> 16) & 0x1f) << 11);
}

static long
extract_bba (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid)
{
  if (((insn >> 16) & 0x1f) != ((insn >> 11) & 0x1f))
    *invalid = 1;
  return 0;
}

/* The BD field in a B form instruction when the - modifier is used.
   This modifier means that the branch is not expected to be taken.
   For chips built to versions of the architecture prior to version 2
   (ie. not Power4 compatible), we set the y bit of the BO field to 1
   if the offset is negative.  When extracting, we require that the y
   bit be 1 and that the offset be positive, since if the y bit is 0
   we just want to print the normal form of the instruction.
   Power4 compatible targets use two bits, "a", and "t", instead of
   the "y" bit.  "at" == 00 => no hint, "at" == 01 => unpredictable,
   "at" == 10 => not taken, "at" == 11 => taken.  The "t" bit is 00001
   in BO field, the "a" bit is 00010 for branch on CR(BI) and 01000
   for branch on CTR.  We only handle the taken/not-taken hint here.
   Note that we don't relax the conditions tested here when
   disassembling with -Many because insns using extract_bdm and
   extract_bdp always occur in pairs.  One or the other will always
   be valid.  */

#define ISA_V2 (PPC_OPCODE_POWER4 | PPC_OPCODE_E500MC | PPC_OPCODE_TITAN)

static unsigned long
insert_bdm (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  if ((dialect & ISA_V2) == 0)
    {
      if ((value & 0x8000) != 0)
	insn |= 1 << 21;
    }
  else
    {
      if ((insn & (0x14 << 21)) == (0x04 << 21))
	insn |= 0x02 << 21;
      else if ((insn & (0x14 << 21)) == (0x10 << 21))
	insn |= 0x08 << 21;
    }
  return insn | (value & 0xfffc);
}

static long
extract_bdm (unsigned long insn,
	     ppc_cpu_t dialect,
	     int *invalid)
{
  if ((dialect & ISA_V2) == 0)
    {
      if (((insn & (1 << 21)) == 0) != ((insn & (1 << 15)) == 0))
	*invalid = 1;
    }
  else
    {
      if ((insn & (0x17 << 21)) != (0x06 << 21)
	  && (insn & (0x1d << 21)) != (0x18 << 21))
	*invalid = 1;
    }

  return ((insn & 0xfffc) ^ 0x8000) - 0x8000;
}

/* The BD field in a B form instruction when the + modifier is used.
   This is like BDM, above, except that the branch is expected to be
   taken.  */

static unsigned long
insert_bdp (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  if ((dialect & ISA_V2) == 0)
    {
      if ((value & 0x8000) == 0)
	insn |= 1 << 21;
    }
  else
    {
      if ((insn & (0x14 << 21)) == (0x04 << 21))
	insn |= 0x03 << 21;
      else if ((insn & (0x14 << 21)) == (0x10 << 21))
	insn |= 0x09 << 21;
    }
  return insn | (value & 0xfffc);
}

static long
extract_bdp (unsigned long insn,
	     ppc_cpu_t dialect,
	     int *invalid)
{
  if ((dialect & ISA_V2) == 0)
    {
      if (((insn & (1 << 21)) == 0) == ((insn & (1 << 15)) == 0))
	*invalid = 1;
    }
  else
    {
      if ((insn & (0x17 << 21)) != (0x07 << 21)
	  && (insn & (0x1d << 21)) != (0x19 << 21))
	*invalid = 1;
    }

  return ((insn & 0xfffc) ^ 0x8000) - 0x8000;
}

static inline int
valid_bo_pre_v2 (long value)
{
  /* Certain encodings have bits that are required to be zero.
     These are (z must be zero, y may be anything):
	 0000y 
	 0001y 
	 001zy
	 0100y 
	 0101y 
	 011zy
	 1z00y
	 1z01y
	 1z1zz
  */
  if ((value & 0x14) == 0)
    return 1;
  else if ((value & 0x14) == 0x4)
    return (value & 0x2) == 0;
  else if ((value & 0x14) == 0x10)
    return (value & 0x8) == 0;
  else
    return value == 0x14;
}

static inline int
valid_bo_post_v2 (long value)
{
  /* Certain encodings have bits that are required to be zero.
     These are (z must be zero, a & t may be anything):
	 0000z
	 0001z
	 001at
	 0100z
	 0101z
	 011at
	 1a00t
	 1a01t
	 1z1zz
  */
  if ((value & 0x14) == 0)
    return (value & 0x1) == 0;
  else if ((value & 0x14) == 0x14)
    return value == 0x14;
  else
    return 1;
}

/* Check for legal values of a BO field.  */

static int
valid_bo (long value, ppc_cpu_t dialect, int extract)
{
  int valid_y = valid_bo_pre_v2 (value);
  int valid_at = valid_bo_post_v2 (value);

  /* When disassembling with -Many, accept either encoding on the
     second pass through opcodes.  */
  if (extract && dialect == ~(ppc_cpu_t) PPC_OPCODE_ANY)
    return valid_y || valid_at;
  if ((dialect & ISA_V2) == 0)
    return valid_y;
  else
    return valid_at;
}

/* The BO field in a B form instruction.  Warn about attempts to set
   the field to an illegal value.  */

static unsigned long
insert_bo (unsigned long insn,
	   long value,
	   ppc_cpu_t dialect,
	   const char **errmsg)
{
  if (!valid_bo (value, dialect, 0))
    *errmsg = _("invalid conditional option");
  else if (PPC_OP (insn) == 19 && (insn & 0x400) && ! (value & 4))
    *errmsg = _("invalid counter access");
  return insn | ((value & 0x1f) << 21);
}

static long
extract_bo (unsigned long insn,
	    ppc_cpu_t dialect,
	    int *invalid)
{
  long value;

  value = (insn >> 21) & 0x1f;
  if (!valid_bo (value, dialect, 1))
    *invalid = 1;
  return value;
}

/* The BO field in a B form instruction when the + or - modifier is
   used.  This is like the BO field, but it must be even.  When
   extracting it, we force it to be even.  */

static unsigned long
insert_boe (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect,
	    const char **errmsg)
{
  if (!valid_bo (value, dialect, 0))
    *errmsg = _("invalid conditional option");
  else if (PPC_OP (insn) == 19 && (insn & 0x400) && ! (value & 4))
    *errmsg = _("invalid counter access");
  else if ((value & 1) != 0)
    *errmsg = _("attempt to set y bit when using + or - modifier");

  return insn | ((value & 0x1f) << 21);
}

static long
extract_boe (unsigned long insn,
	     ppc_cpu_t dialect,
	     int *invalid)
{
  long value;

  value = (insn >> 21) & 0x1f;
  if (!valid_bo (value, dialect, 1))
    *invalid = 1;
  return value & 0x1e;
}

/* FXM mask in mfcr and mtcrf instructions.  */

static unsigned long
insert_fxm (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect,
	    const char **errmsg)
{
  /* If we're handling the mfocrf and mtocrf insns ensure that exactly
     one bit of the mask field is set.  */
  if ((insn & (1 << 20)) != 0)
    {
      if (value == 0 || (value & -value) != value)
	{
	  *errmsg = _("invalid mask field");
	  value = 0;
	}
    }

  /* If the optional field on mfcr is missing that means we want to use
     the old form of the instruction that moves the whole cr.  In that
     case we'll have VALUE zero.  There doesn't seem to be a way to
     distinguish this from the case where someone writes mfcr %r3,0.  */
  else if (value == 0)
    ;

  /* If only one bit of the FXM field is set, we can use the new form
     of the instruction, which is faster.  Unlike the Power4 branch hint
     encoding, this is not backward compatible.  Do not generate the
     new form unless -mpower4 has been given, or -many and the two
     operand form of mfcr was used.  */
  else if ((value & -value) == value
	   && ((dialect & PPC_OPCODE_POWER4) != 0
	       || ((dialect & PPC_OPCODE_ANY) != 0
		   && (insn & (0x3ff << 1)) == 19 << 1)))
    insn |= 1 << 20;

  /* Any other value on mfcr is an error.  */
  else if ((insn & (0x3ff << 1)) == 19 << 1)
    {
      *errmsg = _("ignoring invalid mfcr mask");
      value = 0;
    }

  return insn | ((value & 0xff) << 12);
}

static long
extract_fxm (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid)
{
  long mask = (insn >> 12) & 0xff;

  /* Is this a Power4 insn?  */
  if ((insn & (1 << 20)) != 0)
    {
      /* Exactly one bit of MASK should be set.  */
      if (mask == 0 || (mask & -mask) != mask)
	*invalid = 1;
    }

  /* Check that non-power4 form of mfcr has a zero MASK.  */
  else if ((insn & (0x3ff << 1)) == 19 << 1)
    {
      if (mask != 0)
	*invalid = 1;
    }

  return mask;
}

static unsigned long
insert_li20 (unsigned long insn,
	     long value,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | ((value & 0xf0000) >> 5) | ((value & 0x0f800) << 5) | (value & 0x7ff);
}

static long
extract_li20 (unsigned long insn,
	      ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	      int *invalid ATTRIBUTE_UNUSED)
{
  long ext = ((insn & 0x4000) == 0x4000) ? 0xfff00000 : 0x00000000;

  return ext
         | (((insn >> 11) & 0xf) << 16)
         | (((insn >> 17) & 0xf) << 12)
         | (((insn >> 16) & 0x1) << 11)
         | (insn & 0x7ff);
}

/* The LS field in a sync instruction that accepts 2 operands
   Values 2 and 3 are reserved,
     must be treated as 0 for future compatibility
   Values 0 and 1 can be accepted, if field ESYNC is zero
   Otherwise L = complement of ESYNC-bit2 (1<<18) */

static unsigned long
insert_ls (unsigned long insn,
	   long value,
	   ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	   const char **errmsg ATTRIBUTE_UNUSED)
{
  unsigned long ls;

  ls = (insn >> 21) & 0x03;
  if (value == 0)
    {
      if (ls > 1)
	return insn & ~(0x3 << 21);
      return insn;
    }
  if ((value & 0x2) != 0)
    return (insn & ~(0x3 << 21)) | ((value & 0xf) << 16);
  return (insn & ~(0x3 << 21)) | (0x1 << 21) | ((value & 0xf) << 16);
}

/* The MB and ME fields in an M form instruction expressed as a single
   operand which is itself a bitmask.  The extraction function always
   marks it as invalid, since we never want to recognize an
   instruction which uses a field of this type.  */

static unsigned long
insert_mbe (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg)
{
  unsigned long uval, mask;
  int mb, me, mx, count, last;

  uval = value;

  if (uval == 0)
    {
      *errmsg = _("illegal bitmask");
      return insn;
    }

  mb = 0;
  me = 32;
  if ((uval & 1) != 0)
    last = 1;
  else
    last = 0;
  count = 0;

  /* mb: location of last 0->1 transition */
  /* me: location of last 1->0 transition */
  /* count: # transitions */

  for (mx = 0, mask = 1L << 31; mx < 32; ++mx, mask >>= 1)
    {
      if ((uval & mask) && !last)
	{
	  ++count;
	  mb = mx;
	  last = 1;
	}
      else if (!(uval & mask) && last)
	{
	  ++count;
	  me = mx;
	  last = 0;
	}
    }
  if (me == 0)
    me = 32;

  if (count != 2 && (count != 0 || ! last))
    *errmsg = _("illegal bitmask");

  return insn | (mb << 6) | ((me - 1) << 1);
}

static long
extract_mbe (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid)
{
  long ret;
  int mb, me;
  int i;

  *invalid = 1;

  mb = (insn >> 6) & 0x1f;
  me = (insn >> 1) & 0x1f;
  if (mb < me + 1)
    {
      ret = 0;
      for (i = mb; i <= me; i++)
	ret |= 1L << (31 - i);
    }
  else if (mb == me + 1)
    ret = ~0;
  else /* (mb > me + 1) */
    {
      ret = ~0;
      for (i = me + 1; i < mb; i++)
	ret &= ~(1L << (31 - i));
    }
  return ret;
}

/* The MB or ME field in an MD or MDS form instruction.  The high bit
   is wrapped to the low end.  */

static unsigned long
insert_mb6 (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | ((value & 0x1f) << 6) | (value & 0x20);
}

static long
extract_mb6 (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid ATTRIBUTE_UNUSED)
{
  return ((insn >> 6) & 0x1f) | (insn & 0x20);
}

/* The NB field in an X form instruction.  The value 32 is stored as
   0.  */

static long
extract_nb (unsigned long insn,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    int *invalid ATTRIBUTE_UNUSED)
{
  long ret;

  ret = (insn >> 11) & 0x1f;
  if (ret == 0)
    ret = 32;
  return ret;
}

/* The NB field in an lswi instruction, which has special value
   restrictions.  The value 32 is stored as 0.  */

static unsigned long
insert_nbi (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  long rtvalue = (insn & RT_MASK) >> 21;
  long ravalue = (insn & RA_MASK) >> 16;

  if (value == 0)
    value = 32;
  if (rtvalue + (value + 3) / 4 > (rtvalue > ravalue ? ravalue + 32
						     : ravalue))
    *errmsg = _("address register in load range");
  return insn | ((value & 0x1f) << 11);
}

/* The NSI field in a D form instruction.  This is the same as the SI
   field, only negated.  The extraction function always marks it as
   invalid, since we never want to recognize an instruction which uses
   a field of this type.  */

static unsigned long
insert_nsi (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | (-value & 0xffff);
}

static long
extract_nsi (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid)
{
  *invalid = 1;
  return -(((insn & 0xffff) ^ 0x8000) - 0x8000);
}

/* The RA field in a D or X form instruction which is an updating
   load, which means that the RA field may not be zero and may not
   equal the RT field.  */

static unsigned long
insert_ral (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg)
{
  if (value == 0
      || (unsigned long) value == ((insn >> 21) & 0x1f))
    *errmsg = "invalid register operand when updating";
  return insn | ((value & 0x1f) << 16);
}

/* The RA field in an lmw instruction, which has special value
   restrictions.  */

static unsigned long
insert_ram (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg)
{
  if ((unsigned long) value >= ((insn >> 21) & 0x1f))
    *errmsg = _("index register in load range");
  return insn | ((value & 0x1f) << 16);
}

/* The RA field in the DQ form lq or an lswx instruction, which have special
   value restrictions.  */

static unsigned long
insert_raq (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg)
{
  long rtvalue = (insn & RT_MASK) >> 21;

  if (value == rtvalue)
    *errmsg = _("source and target register operands must be different");
  return insn | ((value & 0x1f) << 16);
}

/* The RA field in a D or X form instruction which is an updating
   store or an updating floating point load, which means that the RA
   field may not be zero.  */

static unsigned long
insert_ras (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg)
{
  if (value == 0)
    *errmsg = _("invalid register operand when updating");
  return insn | ((value & 0x1f) << 16);
}

/* The RB field in an X form instruction when it must be the same as
   the RS field in the instruction.  This is used for extended
   mnemonics like mr.  This operand is marked FAKE.  The insertion
   function just copies the BT field into the BA field, and the
   extraction function just checks that the fields are the same.  */

static unsigned long
insert_rbs (unsigned long insn,
	    long value ATTRIBUTE_UNUSED,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | (((insn >> 21) & 0x1f) << 11);
}

static long
extract_rbs (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid)
{
  if (((insn >> 21) & 0x1f) != ((insn >> 11) & 0x1f))
    *invalid = 1;
  return 0;
}

/* The RB field in an lswx instruction, which has special value
   restrictions.  */

static unsigned long
insert_rbx (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg)
{
  long rtvalue = (insn & RT_MASK) >> 21;

  if (value == rtvalue)
    *errmsg = _("source and target register operands must be different");
  return insn | ((value & 0x1f) << 11);
}

/* The SCI8 field is made up of SCL and {U,N}I8 fields.  */
static unsigned long
insert_sci8 (unsigned long insn,
	     long value,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     const char **errmsg)
{
  unsigned int fill_scale = 0;
  unsigned long ui8 = value;

  if ((ui8 & 0xffffff00) == 0)
    ;
  else if ((ui8 & 0xffffff00) == 0xffffff00)
    fill_scale = 0x400;
  else if ((ui8 & 0xffff00ff) == 0)
    {
      fill_scale = 1 << 8;
      ui8 >>= 8;
    }
  else if ((ui8 & 0xffff00ff) == 0xffff00ff)
    {
      fill_scale = 0x400 | (1 << 8);
      ui8 >>= 8;
    }
  else if ((ui8 & 0xff00ffff) == 0)
    {
      fill_scale = 2 << 8;
      ui8 >>= 16;
    }
  else if ((ui8 & 0xff00ffff) == 0xff00ffff)
    {
      fill_scale = 0x400 | (2 << 8);
      ui8 >>= 16;
    }
  else if ((ui8 & 0x00ffffff) == 0)
    {
      fill_scale = 3 << 8;
      ui8 >>= 24;
    }
  else if ((ui8 & 0x00ffffff) == 0x00ffffff)
    {
      fill_scale = 0x400 | (3 << 8);
      ui8 >>= 24;
    }
  else
    {
      *errmsg = _("illegal immediate value");
      ui8 = 0;
    }

  return insn | fill_scale | (ui8 & 0xff);
}

static long
extract_sci8 (unsigned long insn,
	      ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	      int *invalid ATTRIBUTE_UNUSED)
{
  int fill = insn & 0x400;
  int scale_factor = (insn & 0x300) >> 5;
  long value = (insn & 0xff) << scale_factor;

  if (fill != 0)
    value |= ~((long) 0xff << scale_factor);
  return value;
}

static unsigned long
insert_sci8n (unsigned long insn,
	      long value,
	      ppc_cpu_t dialect,
	      const char **errmsg)
{
  return insert_sci8 (insn, -value, dialect, errmsg);
}

static long
extract_sci8n (unsigned long insn,
	       ppc_cpu_t dialect,
	       int *invalid)
{
  return -extract_sci8 (insn, dialect, invalid);
}

static unsigned long
insert_sd4h (unsigned long insn,
	     long value,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | ((value & 0x1e) << 7);
}

static long
extract_sd4h (unsigned long insn,
	      ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	      int *invalid ATTRIBUTE_UNUSED)
{
  return ((insn >> 8) & 0xf) << 1;
}

static unsigned long
insert_sd4w (unsigned long insn,
	     long value,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | ((value & 0x3c) << 6);
}

static long
extract_sd4w (unsigned long insn,
	      ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	      int *invalid ATTRIBUTE_UNUSED)
{
  return ((insn >> 8) & 0xf) << 2;
}

static unsigned long
insert_oimm (unsigned long insn,
	     long value,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | (((value - 1) & 0x1f) << 4);
}

static long
extract_oimm (unsigned long insn,
	      ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	      int *invalid ATTRIBUTE_UNUSED)
{
  return ((insn >> 4) & 0x1f) + 1;
}

/* The SH field in an MD form instruction.  This is split.  */

static unsigned long
insert_sh6 (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | ((value & 0x1f) << 11) | ((value & 0x20) >> 4);
}

static long
extract_sh6 (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid ATTRIBUTE_UNUSED)
{
  return ((insn >> 11) & 0x1f) | ((insn << 4) & 0x20);
}

/* The SPR field in an XFX form instruction.  This is flipped--the
   lower 5 bits are stored in the upper 5 and vice- versa.  */

static unsigned long
insert_spr (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | ((value & 0x1f) << 16) | ((value & 0x3e0) << 6);
}

static long
extract_spr (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid ATTRIBUTE_UNUSED)
{
  return ((insn >> 16) & 0x1f) | ((insn >> 6) & 0x3e0);
}

/* Some dialects have 8 SPRG registers instead of the standard 4.  */
#define ALLOW8_SPRG (PPC_OPCODE_BOOKE | PPC_OPCODE_405 | PPC_OPCODE_VLE)

static unsigned long
insert_sprg (unsigned long insn,
	     long value,
	     ppc_cpu_t dialect,
	     const char **errmsg)
{
  if (value > 7
      || (value > 3 && (dialect & ALLOW8_SPRG) == 0))
    *errmsg = _("invalid sprg number");

  /* If this is mfsprg4..7 then use spr 260..263 which can be read in
     user mode.  Anything else must use spr 272..279.  */
  if (value <= 3 || (insn & 0x100) != 0)
    value |= 0x10;

  return insn | ((value & 0x17) << 16);
}

static long
extract_sprg (unsigned long insn,
	      ppc_cpu_t dialect,
	      int *invalid)
{
  unsigned long val = (insn >> 16) & 0x1f;

  /* mfsprg can use 260..263 and 272..279.  mtsprg only uses spr 272..279
     If not BOOKE, 405 or VLE, then both use only 272..275.  */
  if ((val - 0x10 > 3 && (dialect & ALLOW8_SPRG) == 0)
      || (val - 0x10 > 7 && (insn & 0x100) != 0)
      || val <= 3
      || (val & 8) != 0)
    *invalid = 1;
  return val & 7;
}

/* The TBR field in an XFX instruction.  This is just like SPR, but it
   is optional.  When TBR is omitted, it must be inserted as 268 (the
   magic number of the TB register).  These functions treat 0
   (indicating an omitted optional operand) as 268.  This means that
   ``mftb 4,0'' is not handled correctly.  This does not matter very
   much, since the architecture manual does not define mftb as
   accepting any values other than 268 or 269.  */

#define TB (268)

static unsigned long
insert_tbr (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  if (value == 0)
    value = TB;
  return insn | ((value & 0x1f) << 16) | ((value & 0x3e0) << 6);
}

static long
extract_tbr (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid ATTRIBUTE_UNUSED)
{
  long ret;

  ret = ((insn >> 16) & 0x1f) | ((insn >> 6) & 0x3e0);
  if (ret == TB)
    ret = 0;
  return ret;
}

/* The XT and XS fields in an XX1 or XX3 form instruction.  This is split.  */

static unsigned long
insert_xt6 (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | ((value & 0x1f) << 21) | ((value & 0x20) >> 5);
}

static long
extract_xt6 (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid ATTRIBUTE_UNUSED)
{
  return ((insn << 5) & 0x20) | ((insn >> 21) & 0x1f);
}

/* The XA field in an XX3 form instruction.  This is split.  */

static unsigned long
insert_xa6 (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | ((value & 0x1f) << 16) | ((value & 0x20) >> 3);
}

static long
extract_xa6 (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid ATTRIBUTE_UNUSED)
{
  return ((insn << 3) & 0x20) | ((insn >> 16) & 0x1f);
}

/* The XB field in an XX3 form instruction.  This is split.  */

static unsigned long
insert_xb6 (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | ((value & 0x1f) << 11) | ((value & 0x20) >> 4);
}

static long
extract_xb6 (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid ATTRIBUTE_UNUSED)
{
  return ((insn << 4) & 0x20) | ((insn >> 11) & 0x1f);
}

/* The XB field in an XX3 form instruction when it must be the same as
   the XA field in the instruction.  This is used for extended
   mnemonics like xvmovdp.  This operand is marked FAKE.  The insertion
   function just copies the XA field into the XB field, and the
   extraction function just checks that the fields are the same.  */

static unsigned long
insert_xb6s (unsigned long insn,
	    long value ATTRIBUTE_UNUSED,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | (((insn >> 16) & 0x1f) << 11) | (((insn >> 2) & 0x1) << 1);
}

static long
extract_xb6s (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid)
{
  if ((((insn >> 16) & 0x1f) != ((insn >> 11) & 0x1f))
      || (((insn >> 2) & 0x1) != ((insn >> 1) & 0x1)))
    *invalid = 1;
  return 0;
}

/* The XC field in an XX4 form instruction.  This is split.  */

static unsigned long
insert_xc6 (unsigned long insn,
	    long value,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | ((value & 0x1f) << 6) | ((value & 0x20) >> 2);
}

static long
extract_xc6 (unsigned long insn,
	     ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	     int *invalid ATTRIBUTE_UNUSED)
{
  return ((insn << 2) & 0x20) | ((insn >> 6) & 0x1f);
}

static unsigned long
insert_dm (unsigned long insn,
	   long value,
	   ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	   const char **errmsg)
{
  if (value != 0 && value != 1)
    *errmsg = _("invalid constant");
  return insn | (((value) ? 3 : 0) << 8);
}

static long
extract_dm (unsigned long insn,
	    ppc_cpu_t dialect ATTRIBUTE_UNUSED,
	    int *invalid)
{
  long value;

  value = (insn >> 8) & 3;
  if (value != 0 && value != 3)
    *invalid = 1;
  return (value) ? 1 : 0;
}
/* The VLESIMM field in an I16A form instruction.  This is split.  */

static unsigned long
insert_vlesi (unsigned long insn,
            long value,
            ppc_cpu_t dialect ATTRIBUTE_UNUSED,
            const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | ((value & 0xf800) << 10) | (value & 0x7ff);
}

static long
extract_vlesi (unsigned long insn,
             ppc_cpu_t dialect ATTRIBUTE_UNUSED,
             int *invalid ATTRIBUTE_UNUSED)
{
  long value = ((insn >> 10) & 0xf800) | (insn & 0x7ff);
  value = (value ^ 0x8000) - 0x8000;
  return value;
}

static unsigned long
insert_vlensi (unsigned long insn,
            long value,
            ppc_cpu_t dialect ATTRIBUTE_UNUSED,
            const char **errmsg ATTRIBUTE_UNUSED)
{
  value = -value;
  return insn | ((value & 0xf800) << 10) | (value & 0x7ff);
}
static long
extract_vlensi (unsigned long insn,
             ppc_cpu_t dialect ATTRIBUTE_UNUSED,
             int *invalid ATTRIBUTE_UNUSED)
{
  long value = ((insn >> 10) & 0xf800) | (insn & 0x7ff);
  value = (value ^ 0x8000) - 0x8000;
  /* Don't use for disassembly.  */
  *invalid = 1;
  return -value;
}

/* The VLEUIMM field in an I16A form instruction.  This is split.  */

static unsigned long
insert_vleui (unsigned long insn,
            long value,
            ppc_cpu_t dialect ATTRIBUTE_UNUSED,
            const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | ((value & 0xf800) << 10) | (value & 0x7ff);
}

static long
extract_vleui (unsigned long insn,
             ppc_cpu_t dialect ATTRIBUTE_UNUSED,
             int *invalid ATTRIBUTE_UNUSED)
{
  return ((insn >> 10) & 0xf800) | (insn & 0x7ff);
}

/* The VLEUIMML field in an I16L form instruction.  This is split.  */

static unsigned long
insert_vleil (unsigned long insn,
            long value,
            ppc_cpu_t dialect ATTRIBUTE_UNUSED,
            const char **errmsg ATTRIBUTE_UNUSED)
{
  return insn | ((value & 0xf800) << 5) | (value & 0x7ff);
}

static long
extract_vleil (unsigned long insn,
             ppc_cpu_t dialect ATTRIBUTE_UNUSED,
             int *invalid ATTRIBUTE_UNUSED)
{
  return ((insn >> 5) & 0xf800) | (insn & 0x7ff);
}

static unsigned long
insert_off_spe2 (unsigned long insn,
           long value,
           ppc_cpu_t dialect ATTRIBUTE_UNUSED,
           const char **errmsg)
{
  if (value > 0 && value <= 0x7)
    return insn | (value & 0x7);
  else
    {
    *errmsg = _("invalid offset");
    return 0;
    }
}

static unsigned long
insert_Ddd (unsigned long insn,
           long value,
           ppc_cpu_t dialect ATTRIBUTE_UNUSED,
           const char **errmsg)
{
  if (value >= 0 && value <= 0x7)
    return insn | ((value & 0x2) << 11) | ((value & 0x4) >> 2);
  else
    {
    *errmsg = _("invalid Ddd value");
    return 0;
    }
}



/* Auxiliary functions */
static bool
vle_reg_operand (HOST_WIDE_INT reg)
{
  if((reg >= 0 && reg <= 7) || (reg >= 24 && reg <= 31))
    return true;
  else
    return false;
}



/* Check if IVAL can be SCI8-encoded.  According to VLEPEM immediates
   such encoded are 32-bit words, hence we allow zero-extended 32-bit
   values universally and then sign-extended 32-bit values on 32-bit
   targets only as they will truncate the operation performed to 32
   bits anyway.  */

static bool
valid_sci8_immediate (HOST_WIDE_INT ival)
{
  if ((ival & ~(unsigned HOST_WIDE_INT) 0xffffffff) == 0
      || (TARGET_32BIT
	  && ((ival & ~(unsigned HOST_WIDE_INT) 0x7fffffff)
	      == ~(unsigned HOST_WIDE_INT) 0x7fffffff)))
    {
      unsigned int ival32 = ival & 0xffffffff;

      if ((ival32 & 0x000000ff) == ival32)
	return true;
      if ((ival32 & 0x0000ff00) == ival32)
	return true;
      if ((ival32 & 0x00ff0000) == ival32)
	return true;
      if ((ival32 & 0xff000000) == ival32)
	return true;

      if ((ival32 | 0xffffff00) == ival32)
	return true;
      if ((ival32 | 0xffff00ff) == ival32)
	return true;
      if ((ival32 | 0xff00ffff) == ival32)
	return true;
      if ((ival32 | 0x00ffffff) == ival32)
	return true;
    }

  return false;
}


static bool
satisfies_constraint_I (HOST_WIDE_INT ival)
{
  /* "A signed 16-bit constant" */
  if((unsigned HOST_WIDE_INT) (ival + 0x8000) < 0x10000)
    return true;
  else
    return false;

}

static bool
satisfies_constraint_K (HOST_WIDE_INT ival)
{
  /* low-order 16 bits nonzero */ 
  if((ival & (~ (HOST_WIDE_INT) 0xffff)) == 0)
    return true;
   else
    return false; 
}

static bool
satisfies_constraint_L (HOST_WIDE_INT ival)
{
  /* "signed 16-bit constant shifted left 16 bits" */
  if ((ival & 0xffff) == 0 && 
      (ival >> 31 == -1 || ival >> 31 == 0))
    {
    return true;
    }
  else
    return false;
  
}

static bool
satisfies_constraint_kli20 (HOST_WIDE_INT ival)
{
  /* "A signed 20-bit immediate" */
  if (ival >= -524288 && ival <= 524287)
    return true;
  else
    return false;
}

static bool
satisfies_constraint_kmsd4 (HOST_WIDE_INT ival)
{
  if ((ival & (~(HOST_WIDE_INT)0xf)) == 0)
    return true;
  else
    return false;
}


static bool
satisfies_constraint_kmmd8 (HOST_WIDE_INT ival)
{
  /* "An 8-bit signed immediate" */
  if (ival >= -128 && ival < 128)
    return true;
  else
    return false;
}


static bool
satisfies_constraint_koim5 (HOST_WIDE_INT ival)
{
  /* "A constant in the range 1-32" */
  if (ival >= 1 && ival <= 32)
    return true;
  else
    return false;
}

static bool
satisfies_constraint_ksci8 (HOST_WIDE_INT ival)
{
  /* "An eight bit immediate constant shifted left by 0, 1, 2 or 3 bytes" */ 
  if (valid_sci8_immediate(ival))
    return true;
  else
    return false; 
}

#if 0
static bool
satisfies_constraint_kscp8 (HOST_WIDE_INT ival)
{
  /* "A constant whose negation is an eight bit immediate shifted left by 0, 1, 2 or 3 bytes" */
  if (valid_sci8_immediate(-ival))
    return true;
  else
    return false; 
}

static bool
satisfies_constraint_kscI8 (HOST_WIDE_INT ival)
{
  /* "An immediate constant that matches the ksci8 or I constraint if making VLE or non-VLE code respectively" */
  if (satisfies_constraint_ksci8(ival) || satisfies_constraint_L(ival))
    return true;
  else
    return false; 
}
#endif

static bool
satisfies_constraint_kuim5(HOST_WIDE_INT ival)
{
  /* "A constant in the range 0-31" */
  if (ival >= 0 && ival <= 31)
    return true;
  else
    return false;
}

static bool
satisfies_constraint_kuim7(HOST_WIDE_INT ival)
{
  /* "A constant in the range 0-127" */
  if (ival >= 0 && ival <= 127)
    return true;
  else
    return false;
}


/* Translation functions */

static int translate_addi (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RT_op, RA_op;
  short SI_op;

  /* addi RT, RA0, SI */
  operand = &powerpc_operands[opcode->operands[0]];
  RT_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[1]];
  RA_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[2]];
  SI_op = (short)(insn >> operand->shift) & operand->bitm;

  if (RT_op == RA_op && vle_reg_operand(RT_op) && satisfies_constraint_koim5(SI_op))
    {
      /* se_addi RX, OIMM5
       * where RT -> RX, SI -> OIMM5  */
      sprintf(output_string, "se_addi %s,%s", literal_operands[RT], literal_operands[SI]);
      n_new_lines = 1;
    }
  else if ( satisfies_constraint_ksci8(SI_op) )
    {
      /* e_addi RT, RA, SCLSCI8
       * where RT -> RT, RA0 -> RA, SI -> SCLSCI8 */
      sprintf(output_string, "e_addi %s,%s,%s", literal_operands[RT],
              literal_operands[RA0], literal_operands[SI]);
      n_new_lines = 1;
    }
  else if (satisfies_constraint_I(SI_op))
   {
      /* e_add16i RT, RA, SI
       * where RT -> RT, RA0 -> RA, SI -> SI */
      sprintf(output_string, "e_add16i %s,%s,%s", literal_operands[RT],
              literal_operands[RA0], literal_operands[SI]);
      n_new_lines = 1;
   }

  return n_new_lines;
}

static int translate_addic (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RT_op ATTRIBUTE_UNUSED, RA_op ATTRIBUTE_UNUSED;
  short SI_op;

  /* addic RT, RA, SI */
  /* addic. RT, RA, SI */
  operand = &powerpc_operands[opcode->operands[0]];
  RT_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[1]];
  RA_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[2]];
  SI_op = (short)(insn >> operand->shift) & operand->bitm;

  if (satisfies_constraint_ksci8(SI_op))
    {
      if (strcmp (opcode->name, "addic") == 0)
	{
	  /* e_addic RT, RA, SCLSCI8
	  * where RT -> RT, RA -> RA, SI -> SCLSCI8 */
	  sprintf(output_string, "e_addic %s,%s,%s", literal_operands[RT],
		  literal_operands[RA], literal_operands[SI]);
	}
      else /* addic. */
	{
	  /* e_addic. RT, RA, SCLSCI8
	  * where RT -> RT, RA -> RA, SI -> SCLSCI8 */
	  sprintf(output_string, "e_addic. %s,%s,%s", literal_operands[RT],
		  literal_operands[RA], literal_operands[SI]);
	}
      n_new_lines = 1;
    }

  return n_new_lines;
}

static int translate_addis (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RT_op, RA_op;
  short SI_op;

  /* addis RT, RA0, SISIGNOPT */
  operand = &powerpc_operands[opcode->operands[0]];
  RT_op = (insn >> operand->shift) & operand->bitm;
  
  operand = &powerpc_operands[opcode->operands[1]];
  RA_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[2]];
  SI_op = (short)(insn >> operand->shift) & operand->bitm;

  if (RT_op == RA_op && satisfies_constraint_L((int)SI_op << 16))
    {
      /* e_add2is RA, VLESIMM
       * where RA0 -> RA, SISIGNOPT -> VLESIMM */
      sprintf(output_string, "e_add2is %s,%s", literal_operands[RA0],
              literal_operands[SISIGNOPT]);
      n_new_lines = 1;
    }
  else if (valid_sci8_immediate((int)SI_op << 16))
    {
      /* e_addi RT, RA, SCLSCI8
       * where RT -> RT, RA0 -> RA, SISIGNOPT -> SCLSCI8 */
      sprintf(output_string, "e_addi %s,%s,%d", literal_operands[RT],
              literal_operands[RA0], (int)(SI_op << 16));
      n_new_lines = 1;
    }

  return n_new_lines;
}

static int translate_andi_dot (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RS_op, UI_op, RA_op;

  /* andi. RA, RS, UI */ 
  operand = &powerpc_operands[opcode->operands[0]];
  RA_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[1]];
  RS_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[2]];
  UI_op = (insn >> operand->shift) & operand->bitm;

  if (satisfies_constraint_ksci8(UI_op))
    {
      /* e_andi. RA, RS, SCLSCI8
       * where RA -> RA, RS -> RS, UI -> SCLSCI8 */
      sprintf(output_string, "e_andi. %s,%s,%s", literal_operands[RA],
	      literal_operands[RS], literal_operands[UI]);
      n_new_lines = 1;
    }
  else if (RS_op == RA_op && satisfies_constraint_K(UI_op))
    {
      /* e_and2i. RD, VLEUIMML 
         where RA -> RD, UI -> VLEUIMML */
      sprintf(output_string, "e_and2i. %s,%s", literal_operands[RA], literal_operands[UI]);
      n_new_lines = 1;
    }
  
  return n_new_lines;  
}

static int translate_andis_dot (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RS_op, UI_op, RA_op; 
  
  /* andis. RA, RS, UI */
  operand = &powerpc_operands[opcode->operands[0]];
  RA_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[1]];
  RS_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[2]];
  UI_op = (insn >> operand->shift) & operand->bitm;
  
  if (RS_op == RA_op && satisfies_constraint_L(UI_op << 16))
      {
      /* e_and2is. RD, VLEUIMML 
         where RA -> RD, UI -> VLEUIMML */
      sprintf(output_string, "e_and2is. %s,%s", literal_operands[RA], literal_operands[UI]);
      n_new_lines = 1;
    }

  return n_new_lines;  
}

static int translate_b (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  
  /* b LI */
  
  if (strcmp (opcode->name, "b") == 0)
    {
      /* e_b B24 */
      sprintf(output_string, "e_b %s", literal_operands[LI]);
      n_new_lines = 1;
    }
  else if (strcmp (opcode->name, "bl") == 0)
    {
      /* e_bl B24 */
      sprintf(output_string, "e_bl %s", literal_operands[LI]);
      n_new_lines = 1; 
    }
   
  return n_new_lines;
}

static int translate_bc (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long CR_op, BD_op ATTRIBUTE_UNUSED; 
 
  if (strcmp (opcode->name, "bc") == 0 || strcmp (opcode->name, "bc+") == 0 || strcmp (opcode->name, "bc-") == 0)
    {
      /* bc BO, BI, BD */
      sprintf(output_string, "e_bc %s,%s,%s", literal_operands[BO], literal_operands[BI], literal_operands[BD]);
      n_new_lines = 1;
    }
  else if (strcmp (opcode->name, "bt") == 0)
    {
      sprintf(output_string, "e_bt %s", literal_operands[BD]);
      n_new_lines = 1;
    }
  else if (strcmp (opcode->name, "bf") == 0)
    {
      sprintf(output_string, "e_bf %s", literal_operands[BD]);
      n_new_lines = 1;
    }     
  else if (strcmp (opcode->name, "bdnz") == 0)
    {
      sprintf(output_string, "e_bdnz %s", literal_operands[BD]);
      n_new_lines = 1;
    }
  else if (strcmp (opcode->name, "bdz") == 0)
    {
      sprintf(output_string, "e_bdz %s", literal_operands[BD]);
      n_new_lines = 1;
    }    
  else
    {
    /* b** CR, BD */
    operand = &powerpc_operands[opcode->operands[0]];
    CR_op = (insn >> operand->shift) & operand->bitm; 
    
    operand = &powerpc_operands[opcode->operands[1]];
    BD_op = (insn >> operand->shift) & operand->bitm;      
      
    /* bc extended mnemonics */
    if ((strcmp (opcode->name, "blt") == 0 || strcmp (opcode->name, "blt+") == 0 || strcmp (opcode->name, "blt-") == 0))
      {
        if (CR_op == 0)
          sprintf(output_string, "se_blt %s", literal_operands[BD]);
        else
          sprintf(output_string, "e_blt %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1;         
      }
    else if (strcmp (opcode->name, "ble") == 0 || strcmp (opcode->name, "ble+") == 0 || strcmp (opcode->name, "ble-") == 0)
      {
        if (CR_op == 0)
          sprintf(output_string, "se_ble %s", literal_operands[BD]);
        else
          sprintf(output_string, "e_ble %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    else if (strcmp (opcode->name, "beq") == 0 || strcmp (opcode->name, "beq+") == 0 || strcmp (opcode->name, "beq-") == 0)
      {
        if (CR_op == 0)
          sprintf(output_string, "se_beq %s", literal_operands[BD]);
        else
          sprintf(output_string, "e_beq %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }   
    else if (strcmp (opcode->name, "bge") == 0 || strcmp (opcode->name, "bge+") == 0 || strcmp (opcode->name, "bge-") == 0)
      {
        if (CR_op == 0)
          sprintf(output_string, "se_bge %s", literal_operands[BD]);
        else
          sprintf(output_string, "e_bge %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      } 
    else if (strcmp (opcode->name, "bgt") == 0 || strcmp (opcode->name, "bgt+") == 0 || strcmp (opcode->name, "bgt-") == 0)
      {
        if (CR_op == 0)
          sprintf(output_string, "se_bgt %s", literal_operands[BD]);
        else
          sprintf(output_string, "e_bgt %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    else if (strcmp (opcode->name, "bnl") == 0 || strcmp (opcode->name, "bnl+") == 0 || strcmp (opcode->name, "bnl-") == 0)
      {
        if (CR_op == 0)
          sprintf(output_string, "se_bnl %s", literal_operands[BD]);
        else
          sprintf(output_string, "e_bnl %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    else if (strcmp (opcode->name, "bne") == 0 || strcmp (opcode->name, "bne+") == 0 || strcmp (opcode->name, "bne-") == 0)
      {
        if (CR_op == 0)
          sprintf(output_string, "se_bne %s", literal_operands[BD]);
        else
          sprintf(output_string, "e_bne %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    else if (strcmp (opcode->name, "bng") == 0 || strcmp (opcode->name, "bng+") == 0 || strcmp (opcode->name, "bng-") == 0)
      {
        if (CR_op == 0)
          sprintf(output_string, "se_bng %s", literal_operands[BD]);
        else
          sprintf(output_string, "e_bng %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    else if (strcmp (opcode->name, "bso") == 0 || strcmp (opcode->name, "bso+") == 0 || strcmp (opcode->name, "bso-") == 0)
      {
        if (CR_op == 0)
          sprintf(output_string, "se_bso %s", literal_operands[BD]);
        else
          sprintf(output_string, "e_bso %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    else if (strcmp (opcode->name, "bns") == 0 || strcmp (opcode->name, "bns+") == 0 || strcmp (opcode->name, "bns-") == 0)
      {
        if (CR_op == 0)
          sprintf(output_string, "se_bns %s", literal_operands[BD]);
        else
          sprintf(output_string, "e_bns %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    else if (strcmp (opcode->name, "bun") == 0 || strcmp (opcode->name, "bun+") == 0 || strcmp (opcode->name, "bun-") == 0)
      {
        if (CR_op == 0)
          sprintf(output_string, "se_bun %s", literal_operands[BD]);
        else
          sprintf(output_string, "e_bun %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    else if (strcmp (opcode->name, "bnu") == 0 || strcmp (opcode->name, "bnu+") == 0 || strcmp (opcode->name, "bnu-") == 0)
      {
        if (CR_op == 0)
          sprintf(output_string, "se_bnu %s", literal_operands[BD]);
        else
          sprintf(output_string, "e_bnu %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    }
  
  return n_new_lines;
}

static int translate_bcl (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
 
  if (strcmp (opcode->name, "bcl") == 0 || strcmp (opcode->name, "bcl+") == 0 || strcmp (opcode->name, "bcl-") == 0)
    {
      /* bcl BO, BI, BD */
      sprintf(output_string, "e_bcl %s,%s,%s", literal_operands[BO], literal_operands[BI], literal_operands[BD]);
      n_new_lines = 1;
    }
  else if (strcmp (opcode->name, "btl") == 0)
    {
      sprintf(output_string, "e_btl %s", literal_operands[BD]);
      n_new_lines = 1;
    }
  else if (strcmp (opcode->name, "bfl") == 0)
    {
      sprintf(output_string, "e_bfl %s", literal_operands[BD]);
      n_new_lines = 1;
    }     
  else if (strcmp (opcode->name, "bdnzl") == 0)
    {
      sprintf(output_string, "e_bdnzl %s", literal_operands[BD]);
      n_new_lines = 1;
    }
  else if (strcmp (opcode->name, "bdzl") == 0)
    {
      sprintf(output_string, "e_bdzl %s", literal_operands[BD]);
      n_new_lines = 1;
    }     
  else
    {
    /* bl** CR, BD */

    /* bl extended mnemonics */
    if ((strcmp (opcode->name, "bltl") == 0 || strcmp (opcode->name, "bltl+") == 0 || strcmp (opcode->name, "bltl-") == 0))
      {
        sprintf(output_string, "e_bltl %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1;         
      }
    else if (strcmp (opcode->name, "blel") == 0 || strcmp (opcode->name, "blel+") == 0 || strcmp (opcode->name, "blel-") == 0)
      {
        sprintf(output_string, "e_blel %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    else if (strcmp (opcode->name, "beql") == 0 || strcmp (opcode->name, "beql+") == 0 || strcmp (opcode->name, "beql-") == 0)
      {
        sprintf(output_string, "e_beql %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }   
    else if (strcmp (opcode->name, "bgel") == 0 || strcmp (opcode->name, "bgel+") == 0 || strcmp (opcode->name, "bgel-") == 0)
      {
        sprintf(output_string, "e_bgel %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      } 
    else if (strcmp (opcode->name, "bgtl") == 0 || strcmp (opcode->name, "bgtl+") == 0 || strcmp (opcode->name, "bgtl-") == 0)
      {
        sprintf(output_string, "e_bgtl %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    else if (strcmp (opcode->name, "bnll") == 0 || strcmp (opcode->name, "bnll+") == 0 || strcmp (opcode->name, "bnll-") == 0)
      {
        sprintf(output_string, "e_bnll %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    else if (strcmp (opcode->name, "bnel") == 0 || strcmp (opcode->name, "bnel+") == 0 || strcmp (opcode->name, "bnel-") == 0)
      {
        sprintf(output_string, "e_bnel %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    else if (strcmp (opcode->name, "bngl") == 0 || strcmp (opcode->name, "bngl+") == 0 || strcmp (opcode->name, "bngl-") == 0)
      {
        sprintf(output_string, "e_bngl %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    else if (strcmp (opcode->name, "bsol") == 0 || strcmp (opcode->name, "bsol+") == 0 || strcmp (opcode->name, "bsol-") == 0)
      {
        sprintf(output_string, "e_bsol %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    else if (strcmp (opcode->name, "bnsl") == 0 || strcmp (opcode->name, "bnsl+") == 0 || strcmp (opcode->name, "bnsl-") == 0)
      {
        sprintf(output_string, "e_bnsl %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    else if (strcmp (opcode->name, "bunl") == 0 || strcmp (opcode->name, "bunl+") == 0 || strcmp (opcode->name, "bunl-") == 0)
      {
        sprintf(output_string, "e_bunl %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    else if (strcmp (opcode->name, "bnul") == 0 || strcmp (opcode->name, "bnul+") == 0 || strcmp (opcode->name, "bnul-") == 0)
      {
        sprintf(output_string, "e_bnul %s,%s", literal_operands[CR], literal_operands[BD]);
        n_new_lines = 1; 
      }
    } 
  
  return n_new_lines;
}

static int translate_bctr (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode, const char **literal_operands ATTRIBUTE_UNUSED, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0; 
  
  if (strcmp (opcode->name, "bctr") == 0)
    {
      sprintf(output_string, "se_bctr");
      n_new_lines = 1; 
    }
  else if (strcmp (opcode->name, "bctrl") == 0)
    {
      sprintf(output_string, "se_bctrl");
      n_new_lines = 1;   
    }
    
  return n_new_lines;    
}

static int translate_blr (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode ATTRIBUTE_UNUSED, const char **literal_operands ATTRIBUTE_UNUSED, char * output_string ATTRIBUTE_UNUSED, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0; 
  
  if (strcmp (opcode->name, "blr") == 0)
    {
      sprintf(output_string, "se_blr");
      n_new_lines = 1; 
    }
  else if (strcmp (opcode->name, "blrl") == 0)
    {
      sprintf(output_string, "se_blrl");
      n_new_lines = 1;   
    }
    
  return n_new_lines; 
}

static int translate_cmpi (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long OBF_op, L_op ATTRIBUTE_UNUSED, RA_op;
  short SI_op;
  int BF_field = UNUSED;
  
  if (strcmp (opcode->name, "cmpi") == 0)
    {
      /* cmpi BF, L, RA, SI */
      operand = &powerpc_operands[opcode->operands[0]];
      OBF_op = (insn >> operand->shift) & operand->bitm;
      
      BF_field = BF;
      
      operand = &powerpc_operands[opcode->operands[1]];
      L_op = (insn >> operand->shift) & operand->bitm;
      
      operand = &powerpc_operands[opcode->operands[2]];
      RA_op = (insn >> operand->shift) & operand->bitm;
      
      operand = &powerpc_operands[opcode->operands[3]];
      SI_op = (short)(insn >> operand->shift) & operand->bitm;
    }
  else if (strcmp (opcode->name, "cmpwi") == 0)
    {
      /* cmpwi OBF, RA, SI */
      operand = &powerpc_operands[opcode->operands[0]];
      OBF_op = (insn >> operand->shift) & operand->bitm;
      
      BF_field = OBF;
      
      operand = &powerpc_operands[opcode->operands[1]];
      RA_op = (insn >> operand->shift) & operand->bitm;
      
      operand = &powerpc_operands[opcode->operands[2]];
      SI_op = (short)(insn >> operand->shift) & operand->bitm;
    }
  else
    {
      *errmsg = _("Unrecognized 'cmpi' mnemonic");
      return 0;
    }    

  if (OBF_op == 0)
    {
      if (vle_reg_operand(RA_op) && satisfies_constraint_kuim5(SI_op))
        {
          /* se_cmpi RX, UI5 */
          sprintf(output_string, "se_cmpi %s,%s", literal_operands[RA],
                  literal_operands[SI]);
          n_new_lines = 1;
        }
      else if (satisfies_constraint_I(SI_op))
        {
          /* e_cmp16i RA, VLESIMM
          * where RA -> RA, SI -> VLESIMM */
          sprintf(output_string, "e_cmp16i %s,%s", literal_operands[RA],
                  literal_operands[SI]);
          n_new_lines = 1;
        }
    }
  else if (satisfies_constraint_ksci8(SI_op))
    {
      /* e_cmpi CRD32, RA, SCLSCI8 
      * where BF -> CRD32, RA -> RA, SI -> SCLSCI8 */
      sprintf(output_string, "e_cmpi %s,%s,%s", literal_operands[BF_field],
              literal_operands[RA], literal_operands[SI]);
      n_new_lines = 1;
    }

 
  return n_new_lines;
}

static int translate_cmpli (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long BF_op, OBF_op, L_op ATTRIBUTE_UNUSED, RA_op, UISIGNOPT_op;
  
  
  if (strcmp (opcode->name, "cmpli") == 0)
    {
      /* cmpli BF, L, RA, UISIGNOPT */
      operand = &powerpc_operands[opcode->operands[0]];
      BF_op = (insn >> operand->shift) & operand->bitm;
      
      operand = &powerpc_operands[opcode->operands[1]];
      L_op = (insn >> operand->shift) & operand->bitm;
      
      operand = &powerpc_operands[opcode->operands[2]];
      RA_op = (insn >> operand->shift) & operand->bitm;
      
      operand = &powerpc_operands[opcode->operands[3]];
      UISIGNOPT_op = (insn >> operand->shift) & operand->bitm;
      
      if (BF_op == 0 && vle_reg_operand(RA_op) && satisfies_constraint_koim5(UISIGNOPT_op))
        {
          /* se_cmpli RX, OIMM5
          * where RA -> RX, UISIGNOPT -> OIMM5 */
          sprintf(output_string, "se_cmpli %s,%s", literal_operands[RA], literal_operands[UISIGNOPT]);
          n_new_lines = 1;
        } 
      else if (satisfies_constraint_ksci8(UISIGNOPT_op))
        {
          /* e_cmpli CRD32, RA, SCLSCI8
          * where BF -> CRD32, RA -> RA, SI -> SCLSCI8 */
          sprintf(output_string, "e_cmpli %s,%s,%s", literal_operands[BF],
                  literal_operands[RA], literal_operands[UISIGNOPT]);
          n_new_lines = 1;
        }      
    }
  else if (strcmp (opcode->name, "cmplwi") == 0)
    {
      /* cmplwi OBF, RA, UISIGNOPT */
      operand = &powerpc_operands[opcode->operands[0]];
      OBF_op = (insn >> operand->shift) & operand->bitm;
      
      operand = &powerpc_operands[opcode->operands[1]];
      RA_op = (insn >> operand->shift) & operand->bitm;
      
      operand = &powerpc_operands[opcode->operands[2]];
      UISIGNOPT_op = (insn >> operand->shift) & operand->bitm;
      
      /* check optional BF field */
      if (OBF_op == 0)
        {
           if (vle_reg_operand(RA_op) && satisfies_constraint_koim5(UISIGNOPT_op))
            {
              /* se_cmpli RX, OIMM5 */
              sprintf(output_string, "se_cmpli %s,%s", literal_operands[RA],
                      literal_operands[UISIGNOPT]);
              n_new_lines = 1;
            }
          else if (satisfies_constraint_I(UISIGNOPT_op))
            {
              /* e_cmpl16i RA, VLEUIMM
              * where RA -> RA, SI -> VLESIMM */
              sprintf(output_string, "e_cmpl16i %s,%s", literal_operands[RA],
                      literal_operands[UISIGNOPT]);
              n_new_lines = 1;
            }
        }
      else if (satisfies_constraint_ksci8(UISIGNOPT_op))
        {
          /* e_cmpli CRD32, RA, SCLSCI8 
          * where OBF -> CRD32, RA -> RA, SI -> SCLSCI8 */
          sprintf(output_string, "e_cmpli %s,%s,%s", literal_operands[OBF],
                  literal_operands[RA], literal_operands[UISIGNOPT]);
          n_new_lines = 1;
        }
    }
 
  return n_new_lines;
}

static int translate_crxxx (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long BT_op, BA_op, BB_op;
  
  /* crand   BT, BA, BB    */
  /* crandc  BT, BA, BB    */
  /* creqv   BT, BA, BB    */
  /* crset   BT, BAT, BBA  */
  /* crnand  BT, BA, BB    */
  /* crnor   BT, BA, BB    */
  /* cror    BT, BA, BB    */
  /* crmove  BT, BA, BBA   */
  /* crorc   BT, BA, BBA   */
  /* crxor   BT, BA, BB    */
  /* crclr   BT, BAT, BBA  */
  operand = &powerpc_operands[opcode->operands[0]];
  BT_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[1]];
  BA_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[2]];
  BB_op = (insn >> operand->shift) & operand->bitm;
  
    
  if (strcmp (opcode->name, "crand") == 0)
    {
      /* e_crand BT, BA, BB */
      sprintf(output_string, "e_crand %s,%s,%s", literal_operands[BT], literal_operands[BA], literal_operands[BB]);
      n_new_lines = 1;
    }
  else if (strcmp (opcode->name, "crandc") == 0)
    {
      /* e_crandc BT, BA, BB */
      sprintf(output_string, "e_crandc %s,%s,%s", literal_operands[BT], literal_operands[BA], literal_operands[BB]);
      n_new_lines = 1;
    }
  else if (strcmp (opcode->name, "creqv") == 0)
    {
      if (BT_op == BA_op && BA_op == BB_op)
	{
	  /* e_crset  BT */
	  sprintf(output_string, "e_crset %s", literal_operands[BT]);
	}
      else
	{
	  /* e_creqv BT, BA, BB */
	  sprintf(output_string, "e_creqv %s,%s,%s", literal_operands[BT], literal_operands[BA], literal_operands[BB]);
	}  
      n_new_lines = 1;
    }   
  else if (strcmp (opcode->name, "crset") == 0)
    {
      /* e_crset  BT */
      sprintf(output_string, "e_crset %s", literal_operands[BT]);
      n_new_lines = 1;
    }     
  else if (strcmp (opcode->name, "crnand") == 0)
    {
      /* e_crnand BT, BA, BB  */
      sprintf(output_string, "e_crnand %s,%s,%s", literal_operands[BT], literal_operands[BA], literal_operands[BB]);
      n_new_lines = 1;
    } 
  else if (strcmp (opcode->name, "crnor") == 0)
    {
      /* e_crnor BT, BA, BB  */
      sprintf(output_string, "e_crnor %s,%s,%s", literal_operands[BT], literal_operands[BA], literal_operands[BB]);
      n_new_lines = 1;
    }  
  else if (strcmp (opcode->name, "crnot") == 0)
    {
      /* e_crnor BT, BA, BB  */
      sprintf(output_string, "e_crnor %s,%s,%s", literal_operands[BT], literal_operands[BA], literal_operands[BA]);
      n_new_lines = 1;
    }    
  else if (strcmp (opcode->name, "cror") == 0)
    {
      /* e_cror BT, BA, BB  */
      sprintf(output_string, "e_cror %s,%s,%s", literal_operands[BT], literal_operands[BA], literal_operands[BB]);
      n_new_lines = 1;
    } 
  else if (strcmp (opcode->name, "crmove") == 0)
    {
      /* e_cror BT, BA, BB  */
      sprintf(output_string, "e_cror %s,%s,%s", literal_operands[BT], literal_operands[BA], literal_operands[BA]);
      n_new_lines = 1;
    }
  else if (strcmp (opcode->name, "crorc") == 0)
    {
      /* e_crorc BT, BA, BB  */
      sprintf(output_string, "e_crorc %s,%s,%s", literal_operands[BT], literal_operands[BA], literal_operands[BB]);
      n_new_lines = 1;
    }
  else if (strcmp (opcode->name, "crxor") == 0)
    {
      /* e_crxor BT, BA, BB  */
      sprintf(output_string, "e_crxor %s,%s,%s", literal_operands[BT], literal_operands[BA], literal_operands[BB]);
      n_new_lines = 1;
    }
  else if (strcmp (opcode->name, "crclr") == 0)
    {
      /* e_crxor BT, BA, BB  */
      sprintf(output_string, "e_crxor %s,%s,%s", literal_operands[BT], literal_operands[BT], literal_operands[BT]);
      n_new_lines = 1;
    }   
   
  return n_new_lines;
}

static int translate_isync (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode ATTRIBUTE_UNUSED, const char **literal_operands ATTRIBUTE_UNUSED, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  sprintf(output_string, "se_isync");
  
  return 1;  
}

static int translate_lbz (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RT_op, RA_op;
  short D_op;
  
  /* lbz RT, D, RA0 */
  operand = &powerpc_operands[opcode->operands[0]];
  RT_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[1]];
  D_op = (short)(insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[2]];
  RA_op = (insn >> operand->shift) & operand->bitm;
  
  if (satisfies_constraint_kmsd4(D_op) && vle_reg_operand(RT_op) && vle_reg_operand(RA_op))
    {
      /* se_lbz RZ, SE_SD, RX
       * where RT -> RZ, D -> SE_SD,  RA0 -> RX */
      sprintf(output_string, "se_lbz %s,%s(%s)", literal_operands[RT],
              literal_operands[D], literal_operands[RA0]);
      n_new_lines = 1;
    }
  else if (satisfies_constraint_I(D_op))
    {
      /* e_lbz RT, D, RA0
       * where RT -> RT, D -> D, RA0 -> RA0 */
      sprintf(output_string, "e_lbz %s,%s(%s)", literal_operands[RT],
              literal_operands[D], literal_operands[RA0]);
      n_new_lines = 1;
    }
  
  
  return n_new_lines;  
}

static int translate_lbzu (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RT_op ATTRIBUTE_UNUSED, RAL_op ATTRIBUTE_UNUSED;
  short D_op;

  /* lbzu RT, D, RAL */
  operand = &powerpc_operands[opcode->operands[0]];
  RT_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[1]];
  D_op = (short)(insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[2]];
  RAL_op = (insn >> operand->shift) & operand->bitm;

  if (satisfies_constraint_kmmd8(D_op))
    {/* e_lbzu RT, D8, RA0
      * where RT -> RT, D -> D8, RAL -> RA0 */
      sprintf(output_string, "e_lbzu %s,%s(%s)", literal_operands[RT],
              literal_operands[D], literal_operands[RAL]);
      n_new_lines = 1;
    }
  else
    {
    *errmsg = _("Cant convert 'lbzu': operand D out of range");
    }    
  
  return n_new_lines;  
}

static int translate_lha (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode ATTRIBUTE_UNUSED, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  /* lha RT, D, RA0 */

  /* e_lha RT, D, RA0 */
  sprintf(output_string, "e_lha %s,%s(%s)", literal_operands[RT], literal_operands[D], literal_operands[RA0]);

  return 1;
}

static int translate_lhau (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  short D_op;

  /* lhau RT, D, RAL */
  operand = &powerpc_operands[opcode->operands[1]];
  D_op = (short)(insn >> operand->shift) & operand->bitm;
  
  if (satisfies_constraint_kmmd8(D_op))
    {/* e_lhau RT, D8, RA0 
      * where RT -> RT, D -> D8, RAL -> RA0 */
      sprintf(output_string, "e_lhau %s,%s(%s)", literal_operands[RT],
              literal_operands[D], literal_operands[RAL]);
      n_new_lines = 1;
    }
  else
    {
    *errmsg = _("Cant convert 'lhau': operand D out of range");
    }
    
  return n_new_lines;
}

static int translate_lhz (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RT_op, D_op, RA_op;  

  /* lhz RT, D, RA0 */
  operand = &powerpc_operands[opcode->operands[0]];
  RT_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[1]];
  D_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[2]];
  RA_op = (insn >> operand->shift) & operand->bitm;
  
  
  if (satisfies_constraint_kmsd4(D_op >> 1) && ((D_op & 0x1) == 0) && vle_reg_operand(RT_op) && vle_reg_operand(RA_op))
    {/* se_lhz RZ, SE_SDH, RX
      * where RT -> RZ, D -> SE_SDH,  RA0 -> RX */
      sprintf(output_string, "se_lhz %s,%s(%s)", literal_operands[RT],
              literal_operands[D], literal_operands[RA0]);
      n_new_lines = 1;
    }
  else
    {
      /* e_lhz RT, D, RA0 */
      sprintf(output_string, "e_lhz %s,%s(%s)", literal_operands[RT], literal_operands[D], literal_operands[RA0]);
      n_new_lines = 1;
    }

  return n_new_lines;
}

static int translate_lhzu (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  short D_op;
  
  /* lhzu RT, D, RAL */
  operand = &powerpc_operands[opcode->operands[1]];
  D_op = (short)(insn >> operand->shift) & operand->bitm;
  
  
  if (satisfies_constraint_kmmd8(D_op))
    {/* e_lhzu RT, D8, RA0 
      * where RT -> RT, D -> D8, RAL -> RA0 */
      sprintf(output_string, "e_lhzu %s,%s(%s)", literal_operands[RT],
              literal_operands[D], literal_operands[RAL]);
      n_new_lines = 1;
    }
  else
    {
    *errmsg = _("Cant convert 'lhzu': operand D out of range");
    }
    
  return n_new_lines;
}

static int translate_li (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RT_op;  
  short SI_op;

  /* li RT, SI */
  operand = &powerpc_operands[opcode->operands[0]];
  RT_op = (insn >> operand->shift) & operand->bitm;
  
  operand = &powerpc_operands[opcode->operands[1]];
  SI_op = (short)(insn >> operand->shift) & operand->bitm;    

  if (vle_reg_operand(RT_op) && satisfies_constraint_kuim7(SI_op))
    {
      /* se_li RX, UI7 
       * where RT -> RX, SI -> UI7 */
      sprintf(output_string, "se_li %s,%s", literal_operands[RT], literal_operands[SI]);
      n_new_lines = 1;
    }
   else if (satisfies_constraint_kli20(SI_op))
    {/* e_li RT, IMM20 
      * where RT -> RT, SI -> IMM20 */
      sprintf(output_string, "e_li %s,%s", literal_operands[RT], literal_operands[SI]);
      n_new_lines = 1;
    }
  else
    {
    *errmsg = _("Cant convert 'li': operand SI out of range");
    }    
  
  return n_new_lines;
}

static int translate_lis (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;  
  short SI_op;

  /* lis RT, SISIGNOPT */
  operand = &powerpc_operands[opcode->operands[1]];
  SI_op = (short)(insn >> operand->shift) & operand->bitm;

  if (satisfies_constraint_L((int)SI_op << 16))
    {/* e_lis RD, VLEUIMML
      * where RT -> RT, SISIGNOPT -> VLEUIMML */
      sprintf(output_string, "e_lis %s,%s", literal_operands[RT], literal_operands[SISIGNOPT]);
      n_new_lines = 1;
    }
  else
    {
    *errmsg = _("Cant convert 'lis': operand SI out of range");
    }     
  
  return n_new_lines;
}


static int translate_lmw (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode ATTRIBUTE_UNUSED, const char **literal_operands ATTRIBUTE_UNUSED, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;  
  /* lmw RT, D, RAM */
  

    {/* e_lmw RT, D8, RA0 */
      sprintf(output_string, "e_lmw %s,%s(%s)", literal_operands[RT], literal_operands[D], literal_operands[RAM]);
      n_new_lines = 1;
    }
  
  return n_new_lines;
}

static int translate_lwz (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RT_op, RA_op;
  short D_op;

  /* lwz RT, D, RA0 */
  operand = &powerpc_operands[opcode->operands[0]];
  RT_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[1]];
  D_op = (short)(insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[2]];
  RA_op = (insn >> operand->shift) & operand->bitm;

  if (satisfies_constraint_kmsd4(D_op >> 2) && ((D_op & 0x3) == 0) && vle_reg_operand(RT_op) && vle_reg_operand(RA_op))
    {/* se_lwz RZ, SE_SDW, RX
      * where RT -> RZ, D -> SE_SDW, RA0 -> RX */
      sprintf(output_string, "se_lwz %s,%s(%s)", literal_operands[RT], literal_operands[D], literal_operands[RA0]);
      n_new_lines = 1;
    }
  else
    {/* e_lwz RT, D, RA0 */
      sprintf(output_string, "e_lwz %s,%s(%s)", literal_operands[RT], literal_operands[D], literal_operands[RA0]);
      n_new_lines = 1;
    }
  
  return n_new_lines;
}

static int translate_lwzu (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode ATTRIBUTE_UNUSED, const char **literal_operands ATTRIBUTE_UNUSED, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  
  /* lwzu RT, D, RAL */

    {/* e_lwzu RT, D8, RA0 */
      sprintf(output_string, "e_lwzu %s,%s(%s)", literal_operands[RT], literal_operands[D], literal_operands[RAL]);
      n_new_lines = 1;
    }
  
  
  return n_new_lines;
}

static int translate_mcrf (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode ATTRIBUTE_UNUSED, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  /* mcrf BF, BFA */
 
  /* e_mcrf CRD, CR */
  sprintf(output_string, "e_mcrf %s,%s", literal_operands[BF], literal_operands[BFA]);
  
  return 1;
}

static int translate_mfdec (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode ATTRIBUTE_UNUSED, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  /* mfdec RT */
  sprintf(output_string, "mfspr %s,22", literal_operands[RT]);
  return 1;
}

static int translate_mulli (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RT_op, RA_op;
  short SI_op;

  /* mulli RT, RA, SI */
  operand = &powerpc_operands[opcode->operands[0]];
  RT_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[1]];
  RA_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[2]];
  SI_op = (short)(insn >> operand->shift) & operand->bitm; 
  
  if (satisfies_constraint_ksci8(SI_op))
    {
      /* e_mulli RT, RA, SCLSCI8
       * where RT -> RT, RA0 -> RA, SI -> SCLSCI8 */
      sprintf(output_string, "e_mulli %s,%s,%s", literal_operands[RT],
              literal_operands[RA], literal_operands[SI]);
      n_new_lines = 1;
    }
  else if (RT_op == RA_op && satisfies_constraint_I(SI_op))
    {
      /* e_mull2i RA, VLESIMM
       * where RA -> RA, SISIGNOPT -> VLESIMM */
      sprintf(output_string, "e_mull2i %s,%s", literal_operands[RA],
              literal_operands[SI]);
      n_new_lines = 1;      
    }    

  return n_new_lines;
}

static int translate_mr (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RA_op, RS_op;
  
  /* mr RA, RS, RBS */
  operand = &powerpc_operands[opcode->operands[0]];
  RA_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[1]];
  RS_op = (insn >> operand->shift) & operand->bitm; 
  
  if (vle_reg_operand(RA_op) && vle_reg_operand(RS_op))
    {
      /* se_mr RX, RY */
      sprintf(output_string, "se_mr %s,%s", literal_operands[RA], literal_operands[RS]);
      n_new_lines = 1;
    }
  else if (vle_reg_operand(RA_op))
    {
      /* se_mfar RX, ARY  */
      sprintf(output_string, "se_mfar %s,%s", literal_operands[RA], literal_operands[RS]);
      n_new_lines = 1;
    }
  else if (vle_reg_operand(RS_op))
    {
      /* se_mtar ARX, RY  */
      sprintf(output_string, "se_mtar %s,%s", literal_operands[RA], literal_operands[RS]);
      n_new_lines = 1;
    }
  else
    { /* keep mr instruction while it VLE */
      /* mr RA, RS, RBS */
      sprintf(output_string, "mr %s,%s", literal_operands[RA], literal_operands[RS]);
      n_new_lines = 1;
    }

  return n_new_lines;
}

static int translate_mtdec (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode ATTRIBUTE_UNUSED, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  /* mtdec RS */
  sprintf(output_string, "mtspr 22,%s", literal_operands[RS]);
  return 1;
}

static int translate_nop (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode ATTRIBUTE_UNUSED, const char **literal_operands ATTRIBUTE_UNUSED, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  sprintf(output_string, "se_nop");
  return 1;
}

static int translate_or (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RA_op, RS_op, RB_op;
  
  /* or RA, RS, RB */
  operand = &powerpc_operands[opcode->operands[0]];
  RA_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[1]];
  RS_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[2]];
  RB_op = (insn >> operand->shift) & operand->bitm;
  
  if (RA_op == 0 && RS_op == 0 && RB_op == 0)
    {
      /* se_nop */     
      sprintf(output_string, "se_nop");
      n_new_lines = 1;  
    }
  else if (RA_op == RS_op && vle_reg_operand(RA_op) && vle_reg_operand(RS_op) && vle_reg_operand(RB_op))
    {
      /* se_or RX, RY */
      sprintf(output_string, "se_or %s,%s", literal_operands[RA], literal_operands[RB]);
      n_new_lines = 1;
    }
  else if (RB_op == RS_op)
    {
      /* mr RA, RS, RBS */
      sprintf(output_string, "mr %s,%s", literal_operands[RA], literal_operands[RB]);
      n_new_lines = 1;
    }
  else
    {
      /* keep or instruction while it VLE */
      /* or RA, RS, RB */
      sprintf(output_string, "or %s,%s,%s", literal_operands[RA], literal_operands[RS], literal_operands[RB]);
      n_new_lines = 1;
    }
  
  return n_new_lines;
}

static int translate_ori (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RA_op, RS_op, UI_op;
  
  /* ori RA, RS, UI */
  operand = &powerpc_operands[opcode->operands[0]];
  RA_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[1]];
  RS_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[2]];
  UI_op = (insn >> operand->shift) & operand->bitm;
  
  if (RA_op == 0 && RA_op == RS_op && UI_op == 0)
    {
      /* e_nop */      
      sprintf(output_string, "e_nop");
      n_new_lines = 1;  
    }
  else if (satisfies_constraint_ksci8(UI_op))
    {
      /* e_ori RA, RS, SCLSCI8
       * where RA -> RA, RS -> RS, UI -> SCLSCI8 */
      sprintf(output_string, "e_ori %s,%s,%s", literal_operands[RA], 
	      literal_operands[RS], literal_operands[UI]);
      n_new_lines = 1;
    }    
  else if (RA_op == RS_op && satisfies_constraint_K(UI_op))
    {
      /* e_or2i RD, VLEUIMML 
         where RA -> RD, UI -> VLEUIMML */
      sprintf(output_string, "e_or2i %s,%s", literal_operands[RA], literal_operands[UI]);
      n_new_lines = 1;
    }    
  
  return n_new_lines;
}

static int translate_oris (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RA_op, RS_op, UI_op;
  
  /* oris RA, RS, UI */
  operand = &powerpc_operands[opcode->operands[0]];
  RA_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[1]];
  RS_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[2]];
  UI_op = (insn >> operand->shift) & operand->bitm;  

  if (RA_op == RS_op && satisfies_constraint_K(UI_op))
    {
      /* e_or2is RD, VLEUIMML 
         where RA -> RD, UI -> VLEUIMML */
      sprintf(output_string, "e_or2is %s,%s", literal_operands[RA], literal_operands[UI]);
      n_new_lines = 1;
    }  
  else if (satisfies_constraint_ksci8(UI_op << 16))
    {
      /* e_ori RA, RS, SCLSCI8
       * where RA -> RA, RS -> RS, UI -> SCLSCI8 */
      sprintf(output_string, "e_ori %s,%s,%d", literal_operands[RA], 
	      literal_operands[RS], (unsigned int)(UI_op << 16));
      n_new_lines = 1;
    }
  
  return n_new_lines;
}

static int translate_rfci (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode ATTRIBUTE_UNUSED, const char **literal_operands ATTRIBUTE_UNUSED, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  sprintf(output_string, "se_rfci");
  return 1;
}

static int translate_rfdi (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode ATTRIBUTE_UNUSED, const char **literal_operands ATTRIBUTE_UNUSED, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  sprintf(output_string, "se_rfdi");
  return 1;
}

static int translate_rfi (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode ATTRIBUTE_UNUSED, const char **literal_operands ATTRIBUTE_UNUSED, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  sprintf(output_string, "se_rfi");
  return 1;
}

static int translate_rfmci (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode ATTRIBUTE_UNUSED, const char **literal_operands ATTRIBUTE_UNUSED, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  sprintf(output_string, "se_rfmci");
  return 1;
}

static int translate_rlwimi (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode ATTRIBUTE_UNUSED, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  /* rlwimi RA, RS, SH, MBE, ME */
  
  /* e_rlwimi RA, RS, SH, MB, ME */
  sprintf(output_string, "e_rlwimi %s,%s,%s,%s,%s", literal_operands[RA], literal_operands[RS],
          literal_operands[SH], literal_operands[MBE], literal_operands[ME]);
  
  return 1;
}

static int translate_rlwnm (unsigned long insn ATTRIBUTE_UNUSED, const struct powerpc_opcode * opcode ATTRIBUTE_UNUSED, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  
  /* rlwnm RA, RS, RB, MBE, ME */
  
  if (strcmp (opcode->name, "rotlw") == 0)
    {
      /* rotlw RA, RS, RB ->  e_rlw RA, RS, RB */
      sprintf(output_string, "e_rlw %s,%s,%s", literal_operands[RA], literal_operands[RS],
          literal_operands[RB]);
      n_new_lines = 1;
    }
  else if (strcmp (opcode->name, "rotlw.") == 0)
    {
      /* rotlw. RA, RS, RB ->  e_rlw. RA, RS, RB */
      sprintf(output_string, "e_rlw. %s,%s,%s", literal_operands[RA], literal_operands[RS],
          literal_operands[RB]);
      n_new_lines = 1;
    }

  return n_new_lines;
}

static int translate_rlwinm (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RA_op, RS_op, SH_op, MBE_op ATTRIBUTE_UNUSED, ME_op ATTRIBUTE_UNUSED;
  int use_se = 0;
  
  /* rlwinm RA, RS, SH, MBE, ME */
  operand = &powerpc_operands[opcode->operands[0]];
  RA_op = (insn >> operand->shift) & operand->bitm;
  
  operand = &powerpc_operands[opcode->operands[1]];
  RS_op = (insn >> operand->shift) & operand->bitm;
  
  operand = &powerpc_operands[opcode->operands[2]];
  SH_op = (insn >> operand->shift) & operand->bitm;
  
  operand = &powerpc_operands[opcode->operands[3]];
  MBE_op = (insn >> operand->shift) & operand->bitm;
    
  operand = &powerpc_operands[opcode->operands[4]];
  ME_op = (insn >> operand->shift) & operand->bitm;
  
   
  use_se = RA_op == RS_op && vle_reg_operand(RA_op) && vle_reg_operand(RS_op);
  
  /* NOTE: slwi and srwi instructions defined by macro and source name is provided to us via 'output_string' as workaround */
  if (strcmp (output_string, "slwi") == 0)
    {
      /* slwi */
      if (use_se && satisfies_constraint_kuim5(SH_op))
        {
          /* se_slwi RX, UI5 */
          sprintf(output_string, "se_slwi %s,%s", literal_operands[RA],  literal_operands[SH]);
          n_new_lines = 1;
        }
      else
        {
          /* e_slwi RA, RS, SH */
          sprintf(output_string, "e_slwi %s,%s,%s", literal_operands[RA], literal_operands[RS], literal_operands[SH]);
          n_new_lines = 1;
        }
    }
  else if (strcmp (output_string, "srwi") == 0)
    {
      /* srwi */
      if (use_se && satisfies_constraint_kuim5(SH_op))
        {
          /* se_srwi RX, UI5 */
          sprintf(output_string, "se_srwi %s,%d", literal_operands[RA], (int)((SH_op == 0)?(0):(32-SH_op)));
          n_new_lines = 1;
        }
      else
        {
          /* e_srwi RA, RS, SH */
          sprintf(output_string, "e_srwi %s,%s,%d", literal_operands[RA], literal_operands[RS], (int)((SH_op == 0)?(0):(32-SH_op)));
          n_new_lines = 1;
        }
    }
  else if (strcmp (opcode->name, "rotlwi") == 0)
    {
      /* rotlwi   RA, RS, SH        */
      /* e_rlwinm RA, RT, SH, 0, 31 */
      sprintf(output_string, "e_rlwinm %s,%s,%s,0,31", literal_operands[RA], literal_operands[RS],
              literal_operands[SH]);
      n_new_lines = 1;
    }
  else if (strcmp (opcode->name, "clrlwi") == 0)
    {
      /* clrlwi   RA, RS,     MB     */
      /* e_rlwinm RA, RT, 0, MBE, 31 */      
      sprintf(output_string, "e_rlwinm %s,%s,0,%s,31", literal_operands[RA], literal_operands[RS],
              literal_operands[MB]);
      n_new_lines = 1;      
    }
  else
    {
      /* e_rlwinm RA, RT, SH, MBE, ME */
      sprintf(output_string, "e_rlwinm %s,%s,%s,%s,%s", literal_operands[RA], literal_operands[RS],
              literal_operands[SH], literal_operands[MBE], literal_operands[ME]);
      n_new_lines = 1;
    }
  
  return n_new_lines;
}

static int translate_sc (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands ATTRIBUTE_UNUSED, char * output_string, const char **errmsg)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long LEV_op;

  /* sc LEV */
  operand = &powerpc_operands[opcode->operands[0]];
  LEV_op = (insn >> operand->shift) & operand->bitm;
  
  if (LEV_op == 0)
    {
      sprintf(output_string, "se_sc");
      n_new_lines = 1;
    } 
  else if (LEV_op == 1)
    {
      sprintf(output_string, "e_sc %s", literal_operands[LEV]);
      n_new_lines = 1;
    }
  else
    {
      *errmsg = _("Cant convert 'sc': LEV value not supported");
    }
  
  return n_new_lines;  
}

static int translate_stb (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RS_op, RA_op;
  short D_op;
  
  /* stb RS, D, RA0 */
  operand = &powerpc_operands[opcode->operands[0]];
  RS_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[1]];
  D_op = (short)(insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[2]];
  RA_op = (insn >> operand->shift) & operand->bitm;
  
  if (satisfies_constraint_kmsd4(D_op) && vle_reg_operand(RS_op) && vle_reg_operand(RA_op))
    {/* se_stb RZ, SE_SD, RX
      * where RS -> RZ, D -> SE_SD,  RA0 -> RX */
      sprintf(output_string, "se_stb %s,%s(%s)", literal_operands[RS],
              literal_operands[D], literal_operands[RA0]);
      n_new_lines = 1;
    }
  else if (satisfies_constraint_I(D_op))
    {
      /* e_stb RT, D, RA0
       * where RS -> RT, D -> D, RA0 -> RA0 */
      sprintf(output_string, "e_stb %s,%s(%s)", literal_operands[RS],
              literal_operands[D], literal_operands[RA0]);
      n_new_lines = 1;
    }
 
  return n_new_lines; 
}

static int translate_stbu (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RS_op ATTRIBUTE_UNUSED, RAS_op ATTRIBUTE_UNUSED;
  short D_op;
  
  /* stbu RS, D, RAS */
  operand = &powerpc_operands[opcode->operands[0]];
  RS_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[1]];
  D_op = (short)(insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[2]];
  RAS_op = (insn >> operand->shift) & operand->bitm;
  
  if (satisfies_constraint_kmmd8(D_op))
    {/* e_stbu RT, D8, RA0
      * where RS -> RT, D -> D8, RAS -> RA0 */
      sprintf(output_string, "e_stbu %s,%s(%s)", literal_operands[RS],
              literal_operands[D], literal_operands[RAS]);
      n_new_lines = 1;
    }
  else
    {
    *errmsg = _("Cant convert 'stbu': operand D out of range");
    }  
  
  return n_new_lines;  
}

static int translate_sth (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RS_op, RA_op;
  short D_op;
  
  /* sth RS, D, RA0 */
  operand = &powerpc_operands[opcode->operands[0]];
  RS_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[1]];
  D_op = (short)(insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[2]];
  RA_op = (insn >> operand->shift) & operand->bitm;
  
  if (satisfies_constraint_kmsd4(D_op >> 1) && ((D_op & 0x1) == 0) && vle_reg_operand(RS_op) && vle_reg_operand(RA_op))
    {/* se_sth RZ, SE_SDH, RX
      * where RS -> RZ, D -> SE_SDH,  RA0 -> RX */
      sprintf(output_string, "se_sth %s,%s(%s)", literal_operands[RS],
              literal_operands[D], literal_operands[RA0]);
      n_new_lines = 1;
    }
  else if (satisfies_constraint_I(D_op))
    {
      /* e_stb RT, D, RA0
       * where RS -> RT, D -> D, RA0 -> RA0 */
      sprintf(output_string, "e_sth %s,%s(%s)", literal_operands[RS],
              literal_operands[D], literal_operands[RA0]);
      n_new_lines = 1;
    }
 
  return n_new_lines;
}

static int translate_sthu (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RS_op ATTRIBUTE_UNUSED, RAS_op ATTRIBUTE_UNUSED;
  short D_op;
  
  /* sthu RS, D, RAS */
  operand = &powerpc_operands[opcode->operands[0]];
  RS_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[1]];
  D_op = (short)(insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[2]];
  RAS_op = (insn >> operand->shift) & operand->bitm;

  if (satisfies_constraint_kmmd8(D_op))
    {/* e_sthu RT, D8, RA0
      * where RS -> RT, D -> D8, RAS -> RA0 */
      sprintf(output_string, "e_sthu %s,%s(%s)", literal_operands[RS],
              literal_operands[D], literal_operands[RAS]);
      n_new_lines = 1;
    }
  else
    {
    *errmsg = _("Cant convert 'sthu': operand D out of range");
    }  

  return n_new_lines;
}

static int translate_stmw (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RS_op ATTRIBUTE_UNUSED, RA_op ATTRIBUTE_UNUSED;
  short D_op;

  /* stmw RS, D, RA0 */
  operand = &powerpc_operands[opcode->operands[0]];
  RS_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[1]];
  D_op = (short)(insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[2]];
  RA_op = (insn >> operand->shift) & operand->bitm; 
  
  if (satisfies_constraint_kmmd8(D_op))
    {/* e_stmw RT, D8, RA0
      * where RS -> RT, D -> D8, RA0 -> RA0 */
      sprintf(output_string, "e_stmw %s,%s(%s)", literal_operands[RS],
              literal_operands[D], literal_operands[RA0]);
      n_new_lines = 1;
    }
  else
    {
    *errmsg = _("Cant convert 'stmw': operand D out of range");
    } 
  
  return n_new_lines;
}

static int translate_stw (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RS_op, RA_op;
  short D_op;

  /* stw RS, D, RA0 */
  operand = &powerpc_operands[opcode->operands[0]];
  RS_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[1]];
  D_op = (short)(insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[2]];
  RA_op = (insn >> operand->shift) & operand->bitm;

  if (satisfies_constraint_kmsd4(D_op >> 2) && ((D_op & 0x3) == 0) && vle_reg_operand(RS_op) && vle_reg_operand(RA_op))
    {/* se_stw RZ, SE_SDW(RX)
      * where RS -> RZ, D -> SE_SDW,  RA0 -> RX */
      sprintf(output_string, "se_stw %s,%s(%s)", literal_operands[RS],
              literal_operands[D], literal_operands[RA0]);
      n_new_lines = 1;
    }
  else if (satisfies_constraint_I(D_op))
    {
      /* e_stw RT, D(RA0)
       * where RS -> RT, D -> D, RA0 -> RA0 */
      sprintf(output_string, "e_stw %s,%s(%s)", literal_operands[RS],
              literal_operands[D], literal_operands[RA0]);
      n_new_lines = 1;
    }

  return n_new_lines;
}

static int translate_stwu (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RS_op ATTRIBUTE_UNUSED, RAS_op ATTRIBUTE_UNUSED;
  short D_op;
  
  /* stwu RS, D, RAS */
  operand = &powerpc_operands[opcode->operands[0]];
  RS_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[1]];
  D_op = (short)(insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[2]];
  RAS_op = (insn >> operand->shift) & operand->bitm;

  if (satisfies_constraint_kmmd8(D_op))
    {/* e_stwu RT, D8, RA0
      * where RS -> RT, D -> D8, RAS -> RA0 */
      sprintf(output_string, "e_stwu %s,%s(%s)", literal_operands[RS],
              literal_operands[D], literal_operands[RAS]);
      n_new_lines = 1;
    }
  else
    {
    *errmsg = _("Cant convert 'stwu': operand D out of range");
    }

  return n_new_lines;
}

static int translate_subi (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RT_op, RA_op;
  short NSI_op;

  /* subi RT, RA0, NSI */
  operand = &powerpc_operands[opcode->operands[0]];
  RT_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[1]];
  RA_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[2]];
  NSI_op = (short)(insn >> operand->shift) & operand->bitm;
  
  if (RT_op == RA_op && vle_reg_operand(RT_op) && satisfies_constraint_koim5(-NSI_op))
    {
      /* se_subi RX, OIMM5
       * where RT -> RX, NSI -> OIMM5 */
      sprintf(output_string, "se_subi %s,%s", literal_operands[RT], literal_operands[NSI]);
      n_new_lines = 1;
    }
  else if ( satisfies_constraint_ksci8(NSI_op) )
    {
      /* e_addi RT, RA, SCLSCI8
       * where RT -> RT, RA0 -> RA, SI -> SCLSCI8 */
      sprintf(output_string, "e_addi %s,%s,%d", literal_operands[RT],
              literal_operands[RA0], NSI_op);
      n_new_lines = 1;
    }    
  else if (satisfies_constraint_I(NSI_op))
   {
      /* e_add16i RT, RA, SI
       * where RT -> RT, RA0 -> RA, NSI -> SI */
      sprintf(output_string, "e_add16i %s,%s,%d", literal_operands[RT],
              literal_operands[RA0], NSI_op);
      n_new_lines = 1;
   }    

  return n_new_lines;
}

static int translate_subic (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RT_op ATTRIBUTE_UNUSED, RA_op ATTRIBUTE_UNUSED;
  short NSI_op;

  /* subic RT, RA, NSI */
  /* subic. RT, RA, NSI */
  operand = &powerpc_operands[opcode->operands[0]];
  RT_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[1]];
  RA_op = (insn >> operand->shift) & operand->bitm;

  operand = &powerpc_operands[opcode->operands[2]];
  NSI_op = (short)(insn >> operand->shift) & operand->bitm;

   
  if (satisfies_constraint_ksci8(NSI_op))
    {
      if (strcmp (opcode->name, "subic") == 0)
        {
          /* e_addic RT, RA, SCLSCI8
          * where RT -> RT, RA -> RA, NSI -> SCLSCI8 */
          sprintf(output_string, "e_addic %s,%s,%d", literal_operands[RT],
                  literal_operands[RA], NSI_op);
          n_new_lines = 1;
        }
     else /* subic. */
        {
          /* e_addic. RT, RA, SCLSCI8
          * where RT -> RT, RA -> RA, NSI -> SCLSCI8 */
          sprintf(output_string, "e_addic. %s,%s,%d", literal_operands[RT],
                  literal_operands[RA], NSI_op);
          n_new_lines = 1;
        }
    }

return n_new_lines;
}

static int translate_subis (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RT_op, RA_op;
  short NSI_op;
  
  /* subis RT, RA0, NSI */
  operand = &powerpc_operands[opcode->operands[0]];
  RT_op = (insn >> operand->shift) & operand->bitm;
  
  operand = &powerpc_operands[opcode->operands[1]];
  RA_op = (insn >> operand->shift) & operand->bitm;
  
  operand = &powerpc_operands[opcode->operands[2]];
  NSI_op = (short)(insn >> operand->shift) & operand->bitm;

  if (RT_op == RA_op && satisfies_constraint_L((int)NSI_op << 16))
    {
      /* e_add2is RA, VLESIMM
       * where RA0 -> RA, SISIGNOPT -> VLESIMM */
      sprintf(output_string, "e_add2is %s,%d", literal_operands[RA0], NSI_op);
      n_new_lines = 1;
    }
  else if (satisfies_constraint_ksci8((int)NSI_op << 16))
    {
      /* e_addi RT, RA, SCLSCI8
       * where RT -> RT, RA0 -> RA, SISIGNOPT -> SCLSCI8 */
      sprintf(output_string, "e_addi %s,%s,%d", literal_operands[RT],
              literal_operands[RA0], (int)NSI_op << 16);
      n_new_lines = 1;
    }  
 
  return n_new_lines;
}

static int translate_subfic (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RT_op ATTRIBUTE_UNUSED, RA_op ATTRIBUTE_UNUSED;
  short SI_op;

  /* subfic RT, RA, SI*/
  operand = &powerpc_operands[opcode->operands[0]];
  RT_op = (insn >> operand->shift) & operand->bitm;
  
  operand = &powerpc_operands[opcode->operands[1]];
  RA_op = (insn >> operand->shift) & operand->bitm;
  
  operand = &powerpc_operands[opcode->operands[2]];
  SI_op = (short)(insn >> operand->shift) & operand->bitm;

  if (satisfies_constraint_ksci8(SI_op))
    {
      /* e_subfic RT, RA, SCLSCI8
       * where RT -> RT, RA -> RA, SI -> SCLSCI8 */
      sprintf(output_string, "e_subfic %s,%s,%s", literal_operands[RT],
	      literal_operands[RA], literal_operands[SI]);
      n_new_lines = 1;
    }

  return n_new_lines;
}

static int translate_xori (unsigned long insn, const struct powerpc_opcode * opcode, const char **literal_operands, char * output_string, const char **errmsg ATTRIBUTE_UNUSED)
{
  int n_new_lines = 0;
  const struct powerpc_operand *operand;
  unsigned long RA_op ATTRIBUTE_UNUSED, RS_op ATTRIBUTE_UNUSED, UI_op;

  /* xori RA, RS, UI */
  operand = &powerpc_operands[opcode->operands[0]];
  RA_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[1]];
  RS_op = (insn >> operand->shift) & operand->bitm; 
  
  operand = &powerpc_operands[opcode->operands[2]];
  UI_op = (insn >> operand->shift) & operand->bitm;

  if (strcmp (opcode->name, "xnop") == 0)
    {
      sprintf(output_string, "e_xori 0,0,0");
      n_new_lines = 1;
    }
  else if (satisfies_constraint_ksci8(UI_op))
    {
      /* e_xori RA, RS, SCLSCI8
       * where RA -> RA, RS -> RS, UI -> SCLSCI8 */
      sprintf(output_string, "e_xori %s,%s,%s", literal_operands[RA],
	      literal_operands[RS], literal_operands[UI]);
      n_new_lines = 1;
    }

  return n_new_lines;
}




/* Macros used to form opcodes.  */

/* The main opcode.  */
#define OP(x) ((((unsigned long)(x)) & 0x3f) << 26)
#define OP_MASK OP (0x3f)

/* The main opcode combined with a trap code in the TO field of a D
   form instruction.  Used for extended mnemonics for the trap
   instructions.  */
#define OPTO(x,to) (OP (x) | ((((unsigned long)(to)) & 0x1f) << 21))
#define OPTO_MASK (OP_MASK | TO_MASK)

/* The main opcode combined with a comparison size bit in the L field
   of a D form or X form instruction.  Used for extended mnemonics for
   the comparison instructions.  */
#define OPL(x,l) (OP (x) | ((((unsigned long)(l)) & 1) << 21))
#define OPL_MASK OPL (0x3f,1)

/* The main opcode combined with an update code in D form instruction.
   Used for extended mnemonics for VLE memory instructions.  */
#define OPVUP(x,vup) (OP (x) | ((((unsigned long)(vup)) & 0xff) << 8))
#define OPVUP_MASK OPVUP (0x3f,  0xff)

/* An A form instruction.  */
#define A(op, xop, rc) (OP (op) | ((((unsigned long)(xop)) & 0x1f) << 1) | (((unsigned long)(rc)) & 1))
#define A_MASK A (0x3f, 0x1f, 1)

/* An A_MASK with the FRB field fixed.  */
#define AFRB_MASK (A_MASK | FRB_MASK)

/* An A_MASK with the FRC field fixed.  */
#define AFRC_MASK (A_MASK | FRC_MASK)

/* An A_MASK with the FRA and FRC fields fixed.  */
#define AFRAFRC_MASK (A_MASK | FRA_MASK | FRC_MASK)

/* An AFRAFRC_MASK, but with L bit clear.  */
#define AFRALFRC_MASK (AFRAFRC_MASK & ~((unsigned long) 1 << 16))

/* A B form instruction.  */
#define B(op, aa, lk) (OP (op) | ((((unsigned long)(aa)) & 1) << 1) | ((lk) & 1))
#define B_MASK B (0x3f, 1, 1)

/* A BD8 form instruction.  This is a 16-bit instruction.  */
#define BD8(op, aa, lk) (((((unsigned long)(op)) & 0x3f) << 10) | (((aa) & 1) << 9) | (((lk) & 1) << 8))
#define BD8_MASK BD8 (0x3f, 1, 1)

/* Another BD8 form instruction.  This is a 16-bit instruction.  */
#define BD8IO(op) ((((unsigned long)(op)) & 0x1f) << 11)
#define BD8IO_MASK BD8IO (0x1f)

/* A BD8 form instruction for simplified mnemonics.  */
#define EBD8IO(op, bo, bi) (BD8IO ((op)) | ((bo) << 10) | ((bi) << 8))
/* A mask that excludes BO32 and BI32.  */
#define EBD8IO1_MASK 0xf800
/* A mask that includes BO32 and excludes BI32.  */
#define EBD8IO2_MASK 0xfc00
/* A mask that include BO32 AND BI32.  */
#define EBD8IO3_MASK 0xff00

/* A BD15 form instruction.  */
#define BD15(op, aa, lk) (OP (op) | ((((unsigned long)(aa)) & 0xf) << 22) | ((lk) & 1))
#define BD15_MASK BD15 (0x3f, 0xf, 1)

/* A BD15 form instruction for extended conditional branch mnemonics.  */
#define EBD15(op, aa, bo, lk) (((op) & 0x3f) << 26) | (((aa) & 0xf) << 22) | (((bo) & 0x3) << 20) | ((lk) & 1)
#define EBD15_MASK 0xfff00001

/* A BD15 form instruction for extended conditional branch mnemonics with BI.  */
#define EBD15BI(op, aa, bo, bi, lk) (((op) & 0x3f) << 26) \
                                    | (((aa) & 0xf) << 22) \
                                    | (((bo) & 0x3) << 20) \
                                    | (((bi) & 0x3) << 16) \
                                    | ((lk) & 1)
#define EBD15BI_MASK  0xfff30001

/* A ESC form instruction.  */
#define ESC(op, elev, xop) (OP (op) | ((((unsigned long)(elev)) & 0x1f) << 11) | ((((unsigned long)(xop)) & 0x3ff) << 1))
#define ESC_MASK (OP_MASK | (((unsigned long)0x3ff) << 16) | (((unsigned long)0x3ff) << 1) | 1)


/* A BD24 form instruction.  */
#define BD24(op, aa, lk) (OP (op) | ((((unsigned long)(aa)) & 1) << 25) | ((lk) & 1))
#define BD24_MASK BD24 (0x3f, 1, 1)

/* A B form instruction setting the BO field.  */
#define BBO(op, bo, aa, lk) (B ((op), (aa), (lk)) | ((((unsigned long)(bo)) & 0x1f) << 21))
#define BBO_MASK BBO (0x3f, 0x1f, 1, 1)

/* A BBO_MASK with the y bit of the BO field removed.  This permits
   matching a conditional branch regardless of the setting of the y
   bit.  Similarly for the 'at' bits used for power4 branch hints.  */
#define Y_MASK	 (((unsigned long) 1) << 21)
#define AT1_MASK (((unsigned long) 3) << 21)
#define AT2_MASK (((unsigned long) 9) << 21)
#define BBOY_MASK  (BBO_MASK &~ Y_MASK)
#define BBOAT_MASK (BBO_MASK &~ AT1_MASK)

/* A B form instruction setting the BO field and the condition bits of
   the BI field.  */
#define BBOCB(op, bo, cb, aa, lk) \
  (BBO ((op), (bo), (aa), (lk)) | ((((unsigned long)(cb)) & 0x3) << 16))
#define BBOCB_MASK BBOCB (0x3f, 0x1f, 0x3, 1, 1)

/* A BBOCB_MASK with the y bit of the BO field removed.  */
#define BBOYCB_MASK (BBOCB_MASK &~ Y_MASK)
#define BBOATCB_MASK (BBOCB_MASK &~ AT1_MASK)
#define BBOAT2CB_MASK (BBOCB_MASK &~ AT2_MASK)

/* A BBOYCB_MASK in which the BI field is fixed.  */
#define BBOYBI_MASK (BBOYCB_MASK | BI_MASK)
#define BBOATBI_MASK (BBOAT2CB_MASK | BI_MASK)

/* A VLE C form instruction.  */
#define C_LK(x, lk) (((((unsigned long)(x)) & 0x7fff) << 1) | ((lk) & 1))
#define C_LK_MASK C_LK(0x7fff, 1)
#define C(x) ((((unsigned long)(x)) & 0xffff))
#define C_MASK C(0xffff)

/* An Context form instruction.  */
#define CTX(op, xop)   (OP (op) | (((unsigned long)(xop)) & 0x7))
#define CTX_MASK CTX(0x3f, 0x7)

/* An User Context form instruction.  */
#define UCTX(op, xop)  (OP (op) | (((unsigned long)(xop)) & 0x1f))
#define UCTX_MASK UCTX(0x3f, 0x1f)

/* The main opcode mask with the RA field clear.  */
#define DRA_MASK (OP_MASK | RA_MASK)

/* A DS form instruction.  */
#define DSO(op, xop) (OP (op) | ((xop) & 0x3))
#define DS_MASK DSO (0x3f, 3)

/* An EVSEL form instruction.  */
#define EVSEL(op, xop) (OP (op) | (((unsigned long)(xop)) & 0xff) << 3)
#define EVSEL_MASK EVSEL(0x3f, 0xff)

/* An IA16 form instruction.  */
#define IA16(op, xop) (OP (op) | (((unsigned long)(xop)) & 0x1f) << 11)
#define IA16_MASK IA16(0x3f, 0x1f)

/* An I16A form instruction.  */
#define I16A(op, xop) (OP (op) | (((unsigned long)(xop)) & 0x1f) << 11)
#define I16A_MASK I16A(0x3f, 0x1f)

/* An I16L form instruction.  */
#define I16L(op, xop) (OP (op) | (((unsigned long)(xop)) & 0x1f) << 11)
#define I16L_MASK I16L(0x3f, 0x1f)

/* An IM7 form instruction.  */
#define IM7(op) ((((unsigned long)(op)) & 0x1f) << 11)
#define IM7_MASK IM7(0x1f)

/* An M form instruction.  */
#define M(op, rc) (OP (op) | ((rc) & 1))
#define M_MASK M (0x3f, 1)

/* An LI20 form instruction.  */
#define LI20(op, xop) (OP (op) | (((unsigned long)(xop)) & 0x1) << 15)
#define LI20_MASK LI20(0x3f, 0x1)

/* An M form instruction with the ME field specified.  */
#define MME(op, me, rc) (M ((op), (rc)) | ((((unsigned long)(me)) & 0x1f) << 1))

/* An M_MASK with the MB and ME fields fixed.  */
#define MMBME_MASK (M_MASK | MB_MASK | ME_MASK)

/* An M_MASK with the SH and ME fields fixed.  */
#define MSHME_MASK (M_MASK | SH_MASK | ME_MASK)

/* An MD form instruction.  */
#define MD(op, xop, rc) (OP (op) | ((((unsigned long)(xop)) & 0x7) << 2) | ((rc) & 1))
#define MD_MASK MD (0x3f, 0x7, 1)

/* An MD_MASK with the MB field fixed.  */
#define MDMB_MASK (MD_MASK | MB6_MASK)

/* An MD_MASK with the SH field fixed.  */
#define MDSH_MASK (MD_MASK | SH6_MASK)

/* An MDS form instruction.  */
#define MDS(op, xop, rc) (OP (op) | ((((unsigned long)(xop)) & 0xf) << 1) | ((rc) & 1))
#define MDS_MASK MDS (0x3f, 0xf, 1)

/* An MDS_MASK with the MB field fixed.  */
#define MDSMB_MASK (MDS_MASK | MB6_MASK)

/* An SC form instruction.  */
#define SC(op, sa, lk) (OP (op) | ((((unsigned long)(sa)) & 1) << 1) | ((lk) & 1))
#define SC_MASK (OP_MASK | (((unsigned long)0x3ff) << 16) | (((unsigned long)1) << 1) | 1)

/* An SCI8 form instruction.  */
#define SCI8(op, xop) (OP (op) | ((((unsigned long)(xop)) & 0x1f) << 11))
#define SCI8_MASK SCI8(0x3f, 0x1f)

/* An SCI8 form instruction.  */
#define SCI8BF(op, fop, xop) (OP (op) | ((((unsigned long)(xop)) & 0x1f) << 11) | (((fop) & 7) << 23))
#define SCI8BF_MASK SCI8BF(0x3f, 7, 0x1f)

/* An SD4 form instruction.  This is a 16-bit instruction.  */
#define SD4(op) ((((unsigned long)(op)) & 0xf) << 12) 
#define SD4_MASK SD4(0xf)

/* An SE_IM5 form instruction.  This is a 16-bit instruction.  */
#define SE_IM5(op, xop) (((((unsigned long)(op)) & 0x3f) << 10) | (((xop) & 0x1) << 9))
#define SE_IM5_MASK SE_IM5(0x3f, 1)

/* An SE_R form instruction.  This is a 16-bit instruction.  */
#define SE_R(op, xop) (((((unsigned long)(op)) & 0x3f) << 10) | (((xop) & 0x3f) << 4))
#define SE_R_MASK SE_R(0x3f, 0x3f)

/* An SE_RR form instruction.  This is a 16-bit instruction.  */
#define SE_RR(op, xop) (((((unsigned long)(op)) & 0x3f) << 10) | (((xop) & 0x3) << 8))
#define SE_RR_MASK SE_RR(0x3f, 3)

/* A VX form instruction.  */
#define VX(op, xop) (OP (op) | (((unsigned long)(xop)) & 0x7ff))

/* The mask for an VX form instruction.  */
#define VX_MASK	VX(0x3f, 0x7ff)

/* A VX LSP form instruction.  */
#define VX_LSP(op, xop) (OP (op) | (((unsigned long)(xop)) & 0xffff))

/* The mask for an VX LSP form instruction.  */
#define VX_LSP_MASK	VX_LSP(0x3f, 0xffff)
#define VX_LSP_OFF_MASK	VX_LSP(0x3f, 0x7fc)

/* Additional format of VX SPE2 form instruction.   */
#define VX_RA_CONST(op, xop, bits11_15) (OP (op) | (((unsigned long)(bits11_15) & 0x1f) << 16) | (((unsigned long)(xop)) & 0x7ff))
#define VX_RA_CONST_MASK VX_RA_CONST(0x3f, 0x7ff, 0x1f)

#define VX_RB_CONST(op, xop, bits16_20) (OP (op) | (((unsigned long)(bits16_20) & 0x1f) << 11) | (((unsigned long)(xop)) & 0x7ff))
#define VX_RB_CONST_MASK VX_RB_CONST(0x3f, 0x7ff, 0x1f)

#define VX_OFF_SPE2_MASK VX(0x3f, 0x7f8)

#define VX_SPE_CRFD(op, xop, bits9_10) (OP (op) | (((unsigned long)(bits9_10) & 0x3) << 21) | (((unsigned long)(xop)) & 0x7ff))
#define VX_SPE_CRFD_MASK VX_SPE_CRFD(0x3f, 0x7ff, 0x3)

#define VX_SPE2_CLR(op, xop, bit16) (OP (op) | (((unsigned long)(bit16) & 0x1) << 15) | (((unsigned long)(xop)) & 0x7ff))
#define VX_SPE2_CLR_MASK VX_SPE2_CLR(0x3f, 0x7ff, 0x1)

#define VX_SPE2_SPLATB(op, xop, bits19_20) (OP (op) | (((unsigned long)(bits19_20) & 0x3) << 11) | (((unsigned long)(xop)) & 0x7ff))
#define VX_SPE2_SPLATB_MASK VX_SPE2_SPLATB(0x3f, 0x7ff, 0x3)

#define VX_SPE2_OCTET(op, xop, bits16_17) (OP (op) | (((unsigned long)(bits16_17) & 0x3) << 14) | (((unsigned long)(xop)) & 0x7ff))
#define VX_SPE2_OCTET_MASK VX_SPE2_OCTET(0x3f, 0x7ff, 0x7)

#define VX_SPE2_DDHH(op, xop, bit16) (OP (op) | (((unsigned long)(bit16) & 0x1) << 15) | (((unsigned long)(xop)) & 0x7ff))
#define VX_SPE2_DDHH_MASK VX_SPE2_DDHH(0x3f, 0x7ff, 0x1)

#define VX_SPE2_HH(op, xop, bit16, bits19_20) (OP (op) |(((unsigned long)(bit16) & 0x1) << 15) |  (((unsigned long)(bits19_20) & 0x3) << 11) | (((unsigned long)(xop)) & 0x7ff))
#define VX_SPE2_HH_MASK VX_SPE2_HH(0x3f, 0x7ff, 0x1, 0x3)


#define VX_SPE2_EVMAR(op, xop) (OP (op) | ((unsigned long)(0x1) << 11) | (((unsigned long)(xop)) & 0x7ff))
#define VX_SPE2_EVMAR_MASK (VX_SPE2_EVMAR(0x3f, 0x7ff) | ((unsigned long)(0x1) << 11))

/* A VX_MASK with the VA field fixed.  */
#define VXVA_MASK (VX_MASK | (0x1f << 16))

/* A VX_MASK with the VB field fixed.  */
#define VXVB_MASK (VX_MASK | (0x1f << 11))

/* A VX_MASK with the VA and VB fields fixed.  */
#define VXVAVB_MASK (VX_MASK | (0x1f << 16) | (0x1f << 11))

/* A VX_MASK with the VD and VA fields fixed.  */
#define VXVDVA_MASK (VX_MASK | (0x1f << 21) | (0x1f << 16))

/* A VX_MASK with a UIMM4 field.  */
#define VXUIMM4_MASK (VX_MASK | (0x1 << 20))

/* A VX_MASK with a UIMM3 field.  */
#define VXUIMM3_MASK (VX_MASK | (0x3 << 19))

/* A VX_MASK with a UIMM2 field.  */
#define VXUIMM2_MASK (VX_MASK | (0x7 << 18))

/* A VX_MASK with a PS field.  */
#define VXPS_MASK (VX_MASK & ~(0x1 << 9))

/* A VA form instruction.  */
#define VXA(op, xop) (OP (op) | (((unsigned long)(xop)) & 0x03f))

/* The mask for an VA form instruction.  */
#define VXA_MASK VXA(0x3f, 0x3f)

/* A VXA_MASK with a SHB field.  */
#define VXASHB_MASK (VXA_MASK | (1 << 10))

/* A VXR form instruction.  */
#define VXR(op, xop, rc) (OP (op) | (((rc) & 1) << 10) | (((unsigned long)(xop)) & 0x3ff))

/* The mask for a VXR form instruction.  */
#define VXR_MASK VXR(0x3f, 0x3ff, 1)

/* An X form instruction.  */
#define X(op, xop) (OP (op) | ((((unsigned long)(xop)) & 0x3ff) << 1))

/* An EX form instruction.  */
#define EX(op, xop) (OP (op) | (((unsigned long)(xop)) & 0x7ff))

/* The mask for an EX form instruction.  */
#define EX_MASK EX (0x3f, 0x7ff)

/* An XX2 form instruction.  */
#define XX2(op, xop) (OP (op) | ((((unsigned long)(xop)) & 0x1ff) << 2))

/* An XX3 form instruction.  */
#define XX3(op, xop) (OP (op) | ((((unsigned long)(xop)) & 0xff) << 3))

/* An XX3 form instruction with the RC bit specified.  */
#define XX3RC(op, xop, rc) (OP (op) | (((rc) & 1) << 10) | ((((unsigned long)(xop)) & 0x7f) << 3))

/* An XX4 form instruction.  */
#define XX4(op, xop) (OP (op) | ((((unsigned long)(xop)) & 0x3) << 4))

/* A Z form instruction.  */
#define Z(op, xop) (OP (op) | ((((unsigned long)(xop)) & 0x1ff) << 1))

/* An X form instruction with the RC bit specified.  */
#define XRC(op, xop, rc) (X ((op), (xop)) | ((rc) & 1))

/* A Z form instruction with the RC bit specified.  */
#define ZRC(op, xop, rc) (Z ((op), (xop)) | ((rc) & 1))

/* The mask for an X form instruction.  */
#define X_MASK XRC (0x3f, 0x3ff, 1)

/* An X form wait instruction with everything filled in except the WC field.  */
#define XWC_MASK (XRC (0x3f, 0x3ff, 1) | (7 << 23) | RA_MASK | RB_MASK)

/* The mask for an XX1 form instruction.  */
#define XX1_MASK X (0x3f, 0x3ff)

/* An XX1_MASK with the RB field fixed.  */
#define XX1RB_MASK (XX1_MASK | RB_MASK)

/* The mask for an XX2 form instruction.  */
#define XX2_MASK (XX2 (0x3f, 0x1ff) | (0x1f << 16))

/* The mask for an XX2 form instruction with the UIM bits specified.  */
#define XX2UIM_MASK (XX2 (0x3f, 0x1ff) | (7 << 18))

/* The mask for an XX2 form instruction with the BF bits specified.  */
#define XX2BF_MASK (XX2_MASK | (3 << 21) | (1))

/* The mask for an XX3 form instruction.  */
#define XX3_MASK XX3 (0x3f, 0xff)

/* The mask for an XX3 form instruction with the BF bits specified.  */
#define XX3BF_MASK (XX3 (0x3f, 0xff) | (3 << 21) | (1))

/* The mask for an XX3 form instruction with the DM or SHW bits specified.  */
#define XX3DM_MASK (XX3 (0x3f, 0x1f) | (1 << 10))
#define XX3SHW_MASK XX3DM_MASK

/* The mask for an XX4 form instruction.  */
#define XX4_MASK XX4 (0x3f, 0x3)

/* An X form wait instruction with everything filled in except the WC field.  */
#define XWC_MASK (XRC (0x3f, 0x3ff, 1) | (7 << 23) | RA_MASK | RB_MASK)

/* The mask for a Z form instruction.  */
#define Z_MASK ZRC (0x3f, 0x1ff, 1)
#define Z2_MASK ZRC (0x3f, 0xff, 1)

/* An X_MASK with the RA field fixed.  */
#define XRA_MASK (X_MASK | RA_MASK)

/* An XRA_MASK with the W field clear.  */
#define XWRA_MASK (XRA_MASK & ~((unsigned long) 1 << 16))

/* An X_MASK with the RB field fixed.  */
#define XRB_MASK (X_MASK | RB_MASK)

/* An X_MASK with the RT field fixed.  */
#define XRT_MASK (X_MASK | RT_MASK)

/* An XRT_MASK mask with the L bits clear.  */
#define XLRT_MASK (XRT_MASK & ~((unsigned long) 0x3 << 21))

/* An X_MASK with the RA and RB fields fixed.  */
#define XRARB_MASK (X_MASK | RA_MASK | RB_MASK)

/* An XRARB_MASK, but with the L bit clear.  */
#define XRLARB_MASK (XRARB_MASK & ~((unsigned long) 1 << 16))

/* An X_MASK with the RT and RA fields fixed.  */
#define XRTRA_MASK (X_MASK | RT_MASK | RA_MASK)

/* An X_MASK with the RT and RB fields fixed.  */
#define XRTRB_MASK (X_MASK | RT_MASK | RB_MASK)

/* An XRTRA_MASK, but with L bit clear.  */
#define XRTLRA_MASK (XRTRA_MASK & ~((unsigned long) 1 << 21))

/* An X_MASK with the RT, RA and RB fields fixed.  */
#define XRTRARB_MASK (X_MASK | RT_MASK | RA_MASK | RB_MASK)

/* An XRTRARB_MASK, but with L bit clear.  */
#define XRTLRARB_MASK (XRTRARB_MASK & ~((unsigned long) 1 << 21))

/* An XRTRARB_MASK, but with A bit clear.  */
#define XRTARARB_MASK (XRTRARB_MASK & ~((unsigned long) 1 << 25))

/* An XRTRARB_MASK, but with BF bits clear.  */
#define XRTBFRARB_MASK (XRTRARB_MASK & ~((unsigned long) 7 << 23))

/* An X form instruction with the L bit specified.  */
#define XOPL(op, xop, l) (X ((op), (xop)) | ((((unsigned long)(l)) & 1) << 21))

/* An X form instruction with the L bits specified.  */
#define XOPL2(op, xop, l) (X ((op), (xop)) | ((((unsigned long)(l)) & 3) << 21))

/* An X form instruction with the L bit and RC bit specified.  */
#define XRCL(op, xop, l, rc) (XRC ((op), (xop), (rc)) | ((((unsigned long)(l)) & 1) << 21))

/* An X form instruction with RT fields specified */
#define XRT(op, xop, rt) (X ((op), (xop)) \
        | ((((unsigned long)(rt)) & 0x1f) << 21))

/* An X form instruction with RT and RA fields specified */
#define XRTRA(op, xop, rt, ra) (X ((op), (xop)) \
        | ((((unsigned long)(rt)) & 0x1f) << 21) \
        | ((((unsigned long)(ra)) & 0x1f) << 16))

/* The mask for an X form comparison instruction.  */
#define XCMP_MASK (X_MASK | (((unsigned long)1) << 22))

/* The mask for an X form comparison instruction with the L field
   fixed.  */
#define XCMPL_MASK (XCMP_MASK | (((unsigned long)1) << 21))

/* An X form trap instruction with the TO field specified.  */
#define XTO(op, xop, to) (X ((op), (xop)) | ((((unsigned long)(to)) & 0x1f) << 21))
#define XTO_MASK (X_MASK | TO_MASK)

/* An X form tlb instruction with the SH field specified.  */
#define XTLB(op, xop, sh) (X ((op), (xop)) | ((((unsigned long)(sh)) & 0x1f) << 11))
#define XTLB_MASK (X_MASK | SH_MASK)

/* An X form sync instruction.  */
#define XSYNC(op, xop, l) (X ((op), (xop)) | ((((unsigned long)(l)) & 3) << 21))

/* An X form sync instruction with everything filled in except the LS field.  */
#define XSYNC_MASK (0xff9fffff)

/* An X form sync instruction with everything filled in except the L and E fields.  */
#define XSYNCLE_MASK (0xff90ffff)

/* An X_MASK, but with the EH bit clear.  */
#define XEH_MASK (X_MASK & ~((unsigned long )1))

/* An X form AltiVec dss instruction.  */
#define XDSS(op, xop, a) (X ((op), (xop)) | ((((unsigned long)(a)) & 1) << 25))
#define XDSS_MASK XDSS(0x3f, 0x3ff, 1)

/* An XFL form instruction.  */
#define XFL(op, xop, rc) (OP (op) | ((((unsigned long)(xop)) & 0x3ff) << 1) | (((unsigned long)(rc)) & 1))
#define XFL_MASK XFL (0x3f, 0x3ff, 1)

/* An X form isel instruction.  */
#define XISEL(op, xop)	(OP (op) | ((((unsigned long)(xop)) & 0x1f) << 1))
#define XISEL_MASK	XISEL(0x3f, 0x1f)

/* An XL form instruction with the LK field set to 0.  */
#define XL(op, xop) (OP (op) | ((((unsigned long)(xop)) & 0x3ff) << 1))

/* An XL form instruction which uses the LK field.  */
#define XLLK(op, xop, lk) (XL ((op), (xop)) | ((lk) & 1))

/* The mask for an XL form instruction.  */
#define XL_MASK XLLK (0x3f, 0x3ff, 1)

/* An XL_MASK with the RT, RA and RB fields fixed, but S bit clear.  */
#define XLS_MASK ((XL_MASK | RT_MASK | RA_MASK | RB_MASK) & ~(1 << 11))

/* An XL form instruction which explicitly sets the BO field.  */
#define XLO(op, bo, xop, lk) \
  (XLLK ((op), (xop), (lk)) | ((((unsigned long)(bo)) & 0x1f) << 21))
#define XLO_MASK (XL_MASK | BO_MASK)

/* An XL form instruction which explicitly sets the y bit of the BO
   field.  */
#define XLYLK(op, xop, y, lk) (XLLK ((op), (xop), (lk)) | ((((unsigned long)(y)) & 1) << 21))
#define XLYLK_MASK (XL_MASK | Y_MASK)

/* An XL form instruction which sets the BO field and the condition
   bits of the BI field.  */
#define XLOCB(op, bo, cb, xop, lk) \
  (XLO ((op), (bo), (xop), (lk)) | ((((unsigned long)(cb)) & 3) << 16))
#define XLOCB_MASK XLOCB (0x3f, 0x1f, 0x3, 0x3ff, 1)

/* An XL_MASK or XLYLK_MASK or XLOCB_MASK with the BB field fixed.  */
#define XLBB_MASK (XL_MASK | BB_MASK)
#define XLYBB_MASK (XLYLK_MASK | BB_MASK)
#define XLBOCBBB_MASK (XLOCB_MASK | BB_MASK)

/* A mask for branch instructions using the BH field.  */
#define XLBH_MASK (XL_MASK | (0x1c << 11))

/* An XL_MASK with the BO and BB fields fixed.  */
#define XLBOBB_MASK (XL_MASK | BO_MASK | BB_MASK)

/* An XL_MASK with the BO, BI and BB fields fixed.  */
#define XLBOBIBB_MASK (XL_MASK | BO_MASK | BI_MASK | BB_MASK)

/* An X form mbar instruction with MO field.  */
#define XMBAR(op, xop, mo) (X ((op), (xop)) | ((((unsigned long)(mo)) & 1) << 21))

/* An XO form instruction.  */
#define XO(op, xop, oe, rc) \
  (OP (op) | ((((unsigned long)(xop)) & 0x1ff) << 1) | ((((unsigned long)(oe)) & 1) << 10) | (((unsigned long)(rc)) & 1))
#define XO_MASK XO (0x3f, 0x1ff, 1, 1)

/* An XO_MASK with the RB field fixed.  */
#define XORB_MASK (XO_MASK | RB_MASK)

/* An XOPS form instruction for paired singles.  */
#define XOPS(op, xop, rc) \
  (OP (op) | ((((unsigned long)(xop)) & 0x3ff) << 1) | (((unsigned long)(rc)) & 1))
#define XOPS_MASK XOPS (0x3f, 0x3ff, 1)


/* An XS form instruction.  */
#define XS(op, xop, rc) (OP (op) | ((((unsigned long)(xop)) & 0x1ff) << 2) | (((unsigned long)(rc)) & 1))
#define XS_MASK XS (0x3f, 0x1ff, 1)

/* A mask for the FXM version of an XFX form instruction.  */
#define XFXFXM_MASK (X_MASK | (1 << 11) | (1 << 20))

/* An XFX form instruction with the FXM field filled in.  */
#define XFXM(op, xop, fxm, p4) \
  (X ((op), (xop)) | ((((unsigned long)(fxm)) & 0xff) << 12) \
   | ((unsigned long)(p4) << 20))

/* An XFX form instruction with the SPR field filled in.  */
#define XSPR(op, xop, spr) \
  (X ((op), (xop)) | ((((unsigned long)(spr)) & 0x1f) << 16) | ((((unsigned long)(spr)) & 0x3e0) << 6))
#define XSPR_MASK (X_MASK | SPR_MASK)

/* An XFX form instruction with the SPR field filled in except for the
   SPRBAT field.  */
#define XSPRBAT_MASK (XSPR_MASK &~ SPRBAT_MASK)

/* An XFX form instruction with the SPR field filled in except for the
   SPRG field.  */
#define XSPRG_MASK (XSPR_MASK & ~(0x1f << 16))

/* An X form instruction with everything filled in except the E field.  */
#define XE_MASK (0xffff7fff)

/* An X form user context instruction.  */
#define XUC(op, xop)  (OP (op) | (((unsigned long)(xop)) & 0x1f))
#define XUC_MASK      XUC(0x3f, 0x1f)

/* An XW form instruction.  */
#define XW(op, xop, rc) (OP (op) | ((((unsigned long)(xop)) & 0x3f) << 1) | ((rc) & 1))
/* The mask for a G form instruction. rc not supported at present.  */
#define XW_MASK XW (0x3f, 0x3f, 0)

/* An APU form instruction.  */
#define APU(op, xop, rc) (OP (op) | (((unsigned long)(xop)) & 0x3ff) << 1 | ((rc) & 1))

/* The mask for an APU form instruction.  */
#define APU_MASK APU (0x3f, 0x3ff, 1)
#define APU_RT_MASK (APU_MASK | RT_MASK)
#define APU_RA_MASK (APU_MASK | RA_MASK)

/* A LSP form instruction.  */
#define LSP(op, xop) (OP (op) | (((unsigned long)(xop)) & 0x7fful))

/* A VLE Interrupt handler instruction */

#define OP_VINT_D8(op, xop, yop) (OP (op) | ((((unsigned long)(xop)) & 0x1f) << 21) | ((((unsigned long)(yop)) & 0xff) << 8))
#define OP_VINT_D8_MASK OP_VINT_D8(0x3F,0x1F,0xFF)

/* The BO encodings used in extended conditional branch mnemonics.  */
#define BODNZF	(0x0)
#define BODNZFP	(0x1)
#define BODZF	(0x2)
#define BODZFP	(0x3)
#define BODNZT	(0x8)
#define BODNZTP	(0x9)
#define BODZT	(0xa)
#define BODZTP	(0xb)

#define BOF	(0x4)
#define BOFP	(0x5)
#define BOFM4	(0x6)
#define BOFP4	(0x7)
#define BOT	(0xc)
#define BOTP	(0xd)
#define BOTM4	(0xe)
#define BOTP4	(0xf)

#define BODNZ	(0x10)
#define BODNZP	(0x11)
#define BODZ	(0x12)
#define BODZP	(0x13)
#define BODNZM4 (0x18)
#define BODNZP4 (0x19)
#define BODZM4	(0x1a)
#define BODZP4	(0x1b)

#define BOU	(0x14)

/* The BO16 encodings used in extended VLE conditional branch mnemonics.  */
#define BO16F   (0x0)
#define BO16T   (0x1)

/* The BO32 encodings used in extended VLE conditional branch mnemonics.  */
#define BO32F   (0x0)
#define BO32T   (0x1)
#define BO32DNZ (0x2)
#define BO32DZ  (0x3)

/* The BI condition bit encodings used in extended conditional branch
   mnemonics.  */
#define CBLT	(0)
#define CBGT	(1)
#define CBEQ	(2)
#define CBSO	(3)

/* The TO encodings used in extended trap mnemonics.  */
#define TOLGT	(0x1)
#define TOLLT	(0x2)
#define TOEQ	(0x4)
#define TOLGE	(0x5)
#define TOLNL	(0x5)
#define TOLLE	(0x6)
#define TOLNG	(0x6)
#define TOGT	(0x8)
#define TOGE	(0xc)
#define TONL	(0xc)
#define TOLT	(0x10)
#define TOLE	(0x14)
#define TONG	(0x14)
#define TONE	(0x18)
#define TOU	(0x1f)

/* Smaller names for the flags so each entry in the opcodes table will
   fit on a single line.  */
#define PPCNONE	0
#undef	PPC
#define PPC	PPC_OPCODE_PPC
#define PPCCOM	PPC_OPCODE_PPC | PPC_OPCODE_COMMON
#define POWER4	PPC_OPCODE_POWER4
#define POWER5	PPC_OPCODE_POWER5
#define POWER6	PPC_OPCODE_POWER6
#define POWER7	PPC_OPCODE_POWER7
#define POWER8	PPC_OPCODE_POWER8
#define CELL	PPC_OPCODE_CELL
#define PPC64	PPC_OPCODE_64 | PPC_OPCODE_64_BRIDGE
#define NON32	(PPC_OPCODE_64 | PPC_OPCODE_POWER4	\
		 | PPC_OPCODE_EFS | PPC_OPCODE_E500MC | PPC_OPCODE_TITAN)
#define PPC403	PPC_OPCODE_403
#define PPC405	PPC_OPCODE_405
#define PPC440	PPC_OPCODE_440
#define PPC464	PPC440
#define PPC476	PPC_OPCODE_476
#define PPC750	PPC
#define PPC7450 PPC
#define PPC860	PPC
#define PPCPS	PPC_OPCODE_PPCPS
#define PPCVEC	PPC_OPCODE_ALTIVEC
#define PPCVEC2	PPC_OPCODE_ALTIVEC2
#define PPCVSX	PPC_OPCODE_VSX
#define PPCVSX2	PPC_OPCODE_VSX
#define POWER	PPC_OPCODE_POWER
#define POWER2	PPC_OPCODE_POWER | PPC_OPCODE_POWER2
#define PWR2COM PPC_OPCODE_POWER | PPC_OPCODE_POWER2 | PPC_OPCODE_COMMON
#define PPCPWR2 PPC_OPCODE_PPC | PPC_OPCODE_POWER | PPC_OPCODE_POWER2 | PPC_OPCODE_COMMON
#define COM	PPC_OPCODE_POWER | PPC_OPCODE_PPC | PPC_OPCODE_COMMON
#define M601	PPC_OPCODE_POWER | PPC_OPCODE_601
#define PWRCOM	PPC_OPCODE_POWER | PPC_OPCODE_601 | PPC_OPCODE_COMMON
#define MFDEC1	PPC_OPCODE_POWER
#define MFDEC2	PPC_OPCODE_PPC | PPC_OPCODE_601 | PPC_OPCODE_BOOKE | PPC_OPCODE_TITAN
#define BOOKE	PPC_OPCODE_BOOKE
#define NO371	PPC_OPCODE_BOOKE | PPC_OPCODE_PPCPS | PPC_OPCODE_EFS | PPC_OPCODE_VLE
#define PPCE300 PPC_OPCODE_E300
#define PPCSPE	PPC_OPCODE_SPE | PPC_OPCODE_VLE
#define PPCSPE2 PPC_OPCODE_SPE2
#define PPCISEL PPC_OPCODE_ISEL | PPC_OPCODE_VLE
#define PPCEFS	PPC_OPCODE_EFS | PPC_OPCODE_VLE
#define PPCEFS2 PPC_OPCODE_EFS | PPC_OPCODE_VLE
#define PPCBRLK PPC_OPCODE_BRLOCK
#define PPCPMR	PPC_OPCODE_PMR
#define PPCTMR  PPC_OPCODE_TMR
#define PPCCHLK PPC_OPCODE_CACHELCK
#define PPCRFMCI	PPC_OPCODE_RFMCI
#define E500MC  PPC_OPCODE_E500MC
#define PPCA2	PPC_OPCODE_A2
#define TITAN   PPC_OPCODE_TITAN  
#define MULHW   PPC_OPCODE_405 | PPC_OPCODE_440 | TITAN | PPC_OPCODE_VLE
#define E500	PPC_OPCODE_E500
#define E6500	PPC_OPCODE_E6500
#define PPCVLE  PPC_OPCODE_VLE
#define PPCLSP  PPC_OPCODE_LSP
#define E5500  PPC_OPCODE_E5500
#define PPCHTM  PPC_OPCODE_HTM

/* The opcode table.

   The format of the opcode table is:

   NAME		OPCODE		MASK	     FLAGS	ANTI		{OPERANDS}

   NAME is the name of the instruction.
   OPCODE is the instruction opcode.
   MASK is the opcode mask; this is used to tell the disassembler
     which bits in the actual opcode must match OPCODE.
   FLAGS are flags indicating which processors support the instruction.
   ANTI indicates which processors don't support the instruction.
   OPERANDS is the list of operands.

   The disassembler reads the table in order and prints the first
   instruction which matches, so this table is sorted to put more
   specific instructions before more general instructions.

   This table must be sorted by major opcode.  Please try to keep it
   vaguely sorted within major opcode too, except of course where
   constrained otherwise by disassembler operation.  */

const struct powerpc_opcode powerpc_opcodes[] = {
{"attn",	X(0,256),	X_MASK,   POWER4|PPCA2,	PPC476,		{UNUSED},	NULL},
{"tdlgti",	OPTO(2,TOLGT),	OPTO_MASK,   PPC64,	PPCNONE,	{RA, SI},	NULL},
{"tdllti",	OPTO(2,TOLLT),	OPTO_MASK,   PPC64,	PPCNONE,	{RA, SI},	NULL},
{"tdeqi",	OPTO(2,TOEQ),	OPTO_MASK,   PPC64,	PPCNONE,	{RA, SI},	NULL},
{"tdlgei",	OPTO(2,TOLGE),	OPTO_MASK,   PPC64,	PPCNONE,	{RA, SI},	NULL},
{"tdlnli",	OPTO(2,TOLNL),	OPTO_MASK,   PPC64,	PPCNONE,	{RA, SI},	NULL},
{"tdllei",	OPTO(2,TOLLE),	OPTO_MASK,   PPC64,	PPCNONE,	{RA, SI},	NULL},
{"tdlngi",	OPTO(2,TOLNG),	OPTO_MASK,   PPC64,	PPCNONE,	{RA, SI},	NULL},
{"tdgti",	OPTO(2,TOGT),	OPTO_MASK,   PPC64,	PPCNONE,	{RA, SI},	NULL},
{"tdgei",	OPTO(2,TOGE),	OPTO_MASK,   PPC64,	PPCNONE,	{RA, SI},	NULL},
{"tdnli",	OPTO(2,TONL),	OPTO_MASK,   PPC64,	PPCNONE,	{RA, SI},	NULL},
{"tdlti",	OPTO(2,TOLT),	OPTO_MASK,   PPC64,	PPCNONE,	{RA, SI},	NULL},
{"tdlei",	OPTO(2,TOLE),	OPTO_MASK,   PPC64,	PPCNONE,	{RA, SI},	NULL},
{"tdngi",	OPTO(2,TONG),	OPTO_MASK,   PPC64,	PPCNONE,	{RA, SI},	NULL},
{"tdnei",	OPTO(2,TONE),	OPTO_MASK,   PPC64,	PPCNONE,	{RA, SI},	NULL},
{"tdui",	OPTO(2,TOU),	OPTO_MASK,   PPC64,	PPCNONE,	{RA, SI},	NULL},
{"tdi",		OP(2),		OP_MASK,     PPC64,	PPCNONE,	{TO, RA, SI},	NULL},

{"twlgti",	OPTO(3,TOLGT),	OPTO_MASK,   PPCCOM,	PPCNONE,	{RA, SI},	NULL},
{"tlgti",	OPTO(3,TOLGT),	OPTO_MASK,   PWRCOM,	PPCNONE,	{RA, SI},	NULL},
{"twllti",	OPTO(3,TOLLT),	OPTO_MASK,   PPCCOM,	PPCNONE,	{RA, SI},	NULL},
{"tllti",	OPTO(3,TOLLT),	OPTO_MASK,   PWRCOM,	PPCNONE,	{RA, SI},	NULL},
{"tweqi",	OPTO(3,TOEQ),	OPTO_MASK,   PPCCOM,	PPCNONE,	{RA, SI},	NULL},
{"teqi",	OPTO(3,TOEQ),	OPTO_MASK,   PWRCOM,	PPCNONE,	{RA, SI},	NULL},
{"twlgei",	OPTO(3,TOLGE),	OPTO_MASK,   PPCCOM,	PPCNONE,	{RA, SI},	NULL},
{"tlgei",	OPTO(3,TOLGE),	OPTO_MASK,   PWRCOM,	PPCNONE,	{RA, SI},	NULL},
{"twlnli",	OPTO(3,TOLNL),	OPTO_MASK,   PPCCOM,	PPCNONE,	{RA, SI},	NULL},
{"tlnli",	OPTO(3,TOLNL),	OPTO_MASK,   PWRCOM,	PPCNONE,	{RA, SI},	NULL},
{"twllei",	OPTO(3,TOLLE),	OPTO_MASK,   PPCCOM,	PPCNONE,	{RA, SI},	NULL},
{"tllei",	OPTO(3,TOLLE),	OPTO_MASK,   PWRCOM,	PPCNONE,	{RA, SI},	NULL},
{"twlngi",	OPTO(3,TOLNG),	OPTO_MASK,   PPCCOM,	PPCNONE,	{RA, SI},	NULL},
{"tlngi",	OPTO(3,TOLNG),	OPTO_MASK,   PWRCOM,	PPCNONE,	{RA, SI},	NULL},
{"twgti",	OPTO(3,TOGT),	OPTO_MASK,   PPCCOM,	PPCNONE,	{RA, SI},	NULL},
{"tgti",	OPTO(3,TOGT),	OPTO_MASK,   PWRCOM,	PPCNONE,	{RA, SI},	NULL},
{"twgei",	OPTO(3,TOGE),	OPTO_MASK,   PPCCOM,	PPCNONE,	{RA, SI},	NULL},
{"tgei",	OPTO(3,TOGE),	OPTO_MASK,   PWRCOM,	PPCNONE,	{RA, SI},	NULL},
{"twnli",	OPTO(3,TONL),	OPTO_MASK,   PPCCOM,	PPCNONE,	{RA, SI},	NULL},
{"tnli",	OPTO(3,TONL),	OPTO_MASK,   PWRCOM,	PPCNONE,	{RA, SI},	NULL},
{"twlti",	OPTO(3,TOLT),	OPTO_MASK,   PPCCOM,	PPCNONE,	{RA, SI},	NULL},
{"tlti",	OPTO(3,TOLT),	OPTO_MASK,   PWRCOM,	PPCNONE,	{RA, SI},	NULL},
{"twlei",	OPTO(3,TOLE),	OPTO_MASK,   PPCCOM,	PPCNONE,	{RA, SI},	NULL},
{"tlei",	OPTO(3,TOLE),	OPTO_MASK,   PWRCOM,	PPCNONE,	{RA, SI},	NULL},
{"twngi",	OPTO(3,TONG),	OPTO_MASK,   PPCCOM,	PPCNONE,	{RA, SI},	NULL},
{"tngi",	OPTO(3,TONG),	OPTO_MASK,   PWRCOM,	PPCNONE,	{RA, SI},	NULL},
{"twnei",	OPTO(3,TONE),	OPTO_MASK,   PPCCOM,	PPCNONE,	{RA, SI},	NULL},
{"tnei",	OPTO(3,TONE),	OPTO_MASK,   PWRCOM,	PPCNONE,	{RA, SI},	NULL},
{"twui",	OPTO(3,TOU),	OPTO_MASK,   PPCCOM,	PPCNONE,	{RA, SI},	NULL},
{"tui",		OPTO(3,TOU),	OPTO_MASK,   PWRCOM,	PPCNONE,	{RA, SI},	NULL},
{"twi",		OP(3),		OP_MASK,     PPCCOM,	PPCNONE,	{TO, RA, SI},	NULL},
{"ti",		OP(3),		OP_MASK,     PWRCOM,	PPCNONE,	{TO, RA, SI},	NULL},

{"ps_cmpu0",	X  (4,	 0), X_MASK|(3<<21), PPCPS,	PPCNONE,	{BF, FRA, FRB},	NULL},
{"vaddubm",	VX (4,	 0),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vmaxub",	VX (4,	 2),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vrlb",	VX (4,	 4),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpequb",	VXR(4,	 6,0),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vmuloub",	VX (4,	 8),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vaddfp",	VX (4,	10),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"psq_lx",	XW (4,	 6,0),	XW_MASK,     PPCPS,	PPCNONE,	{FRT,RA,RB,PSWM,PSQM},	NULL},
{"vmrghb",	VX (4,	12),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"psq_stx",	XW (4,	 7,0),	XW_MASK,     PPCPS,	PPCNONE,	{FRS,RA,RB,PSWM,PSQM},	NULL},
{"vpkuhum",	VX (4,	14),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"mulhhwu",	XRC(4,	 8,0),	X_MASK,      MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"mulhhwu.",	XRC(4,	 8,1),	X_MASK,      MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"ps_sum0",	A  (4,	10,0),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"ps_sum0.",	A  (4,	10,1),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"ps_sum1",	A  (4,	11,0),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"ps_sum1.",	A  (4,	11,1),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"ps_muls0",	A  (4,	12,0),	AFRB_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRC},	NULL},
{"machhwu",	XO (4,	12,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"ps_muls0.",	A  (4,	12,1),	AFRB_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRC},	NULL},
{"machhwu.",	XO (4,	12,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"ps_muls1",	A  (4,	13,0),	AFRB_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRC},	NULL},
{"ps_muls1.",	A  (4,	13,1),	AFRB_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRC},	NULL},
{"ps_madds0",	A  (4,	14,0),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"ps_madds0.",	A  (4,	14,1),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"ps_madds1",	A  (4,	15,0),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"ps_madds1.",	A  (4,	15,1),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"vmhaddshs",	VXA(4,	32),	VXA_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB, VC},	NULL},
{"vmhraddshs",	VXA(4,	33),	VXA_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB, VC},	NULL},
{"vmladduhm",	VXA(4,	34),	VXA_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB, VC},	NULL},
{"ps_div",	A  (4,	18,0),	AFRC_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"vmsumubm",	VXA(4,	36),	VXA_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB, VC},	NULL},
{"ps_div.",	A  (4,	18,1),	AFRC_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"vmsummbm",	VXA(4,	37),	VXA_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB, VC},	NULL},
{"vmsumuhm",	VXA(4,	38),	VXA_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB, VC},	NULL},
{"vmsumuhs",	VXA(4,	39),	VXA_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB, VC},	NULL},
{"ps_sub",	A  (4,	20,0),	AFRC_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"vmsumshm",	VXA(4,	40),	VXA_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB, VC},	NULL},
{"ps_sub.",	A  (4,	20,1),	AFRC_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"vmsumshs",	VXA(4,	41),	VXA_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB, VC},	NULL},
{"ps_add",	A  (4,	21,0),	AFRC_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"vsel",	VXA(4,	42),	VXA_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB, VC},	NULL},
{"ps_add.",	A  (4,	21,1),	AFRC_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"vperm",	VXA(4,	43),	VXA_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB, VC},	NULL},
{"vsldoi",	VXA(4,	44),	VXASHB_MASK, PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB, SHB},	NULL},
{"ps_sel",	A  (4,	23,0),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"vpermxor",	VXA(4,	45),	VXA_MASK,    PPCVEC2,	PPCNONE,	{VD, VA, VB, VC},	NULL},
{"vmaddfp",	VXA(4,	46),	VXA_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VC, VB},	NULL},
{"ps_sel.",	A  (4,	23,1),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"vnmsubfp",	VXA(4,	47),	VXA_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VC, VB},	NULL},
{"ps_res",	A  (4,	24,0), AFRAFRC_MASK, PPCPS,	PPCNONE,	{FRT, FRB},	NULL},
{"ps_res.",	A  (4,	24,1), AFRAFRC_MASK, PPCPS,	PPCNONE,	{FRT, FRB},	NULL},
{"ps_mul",	A  (4,	25,0), AFRB_MASK,    PPCPS,	PPCNONE,	{FRT, FRA, FRC},	NULL},
{"ps_mul.",	A  (4,	25,1),	AFRB_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRC},	NULL},
{"ps_rsqrte",	A  (4,	26,0), AFRAFRC_MASK, PPCPS,	PPCNONE,	{FRT, FRB},	NULL},
{"ps_rsqrte.",	A  (4,	26,1), AFRAFRC_MASK, PPCPS,	PPCNONE,	{FRT, FRB},	NULL},
{"ps_msub",	A  (4,	28,0),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"ps_msub.",	A  (4,	28,1),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"ps_madd",	A  (4,	29,0),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"ps_madd.",	A  (4,	29,1),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"ps_nmsub",	A  (4,	30,0),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"ps_nmsub.",	A  (4,	30,1),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"ps_nmadd",	A  (4,	31,0),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"ps_nmadd.",	A  (4,	31,1),	A_MASK,      PPCPS,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"ps_cmpo0",	X  (4,	32), X_MASK|(3<<21), PPCPS,	PPCNONE,	{BF, FRA, FRB},	NULL},
{"vaddeuqm",	VXA(4,	60),	VXA_MASK,    PPCVEC2,	PPCNONE,	{VD, VA, VB, VC},	NULL},
{"vaddecuq",	VXA(4,	61),	VXA_MASK,    PPCVEC2,	PPCNONE,	{VD, VA, VB, VC},	NULL},
{"vsubeuqm",	VXA(4,	62),	VXA_MASK,    PPCVEC2,	PPCNONE,	{VD, VA, VB, VC},	NULL},
{"vsubecuq",	VXA(4,	63),	VXA_MASK,    PPCVEC2,	PPCNONE,	{VD, VA, VB, VC},	NULL},
{"vadduhm",	VX (4,	64),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vmaxuh",	VX (4,	66),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vrlh",	VX (4,	68),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpequh",	VXR(4,	70,0),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vmulouh",	VX (4,	72),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vsubfp",	VX (4,	74),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"psq_lux",	XW (4,	38,0),	XW_MASK,     PPCPS,	PPCNONE,	{FRT,RA,RB,PSWM,PSQM},	NULL},
{"vmrghh",	VX (4,	76),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"psq_stux",	XW (4,	39,0),	XW_MASK,     PPCPS,	PPCNONE,	{FRS,RA,RB,PSWM,PSQM},	NULL},
{"vpkuwum",	VX (4,	78),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"ps_neg",	XRC(4,	40,0),	XRA_MASK,    PPCPS,	PPCNONE,	{FRT, FRB},	NULL},
{"mulhhw",	XRC(4,	40,0),	X_MASK,      MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"ps_neg.",	XRC(4,	40,1),	XRA_MASK,    PPCPS,	PPCNONE,	{FRT, FRB},	NULL},
{"mulhhw.",	XRC(4,	40,1),	X_MASK,      MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"machhw",	XO (4,	44,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"machhw.",	XO (4,	44,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmachhw",	XO (4,	46,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmachhw.",	XO (4,	46,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"ps_cmpu1",	X  (4,	64), X_MASK|(3<<21), PPCPS,	PPCNONE,	{BF, FRA, FRB},	NULL},
{"vadduwm",	VX (4,	128),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vmaxuw",	VX (4,	130),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vrlw",	VX (4,	132),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpequw",	VXR(4,	134,0), VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vmulouw",	VX (4,  136),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"vmuluwm",	VX (4,  137),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"vmrghw",	VX (4,	140),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vpkuhus",	VX (4,	142),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"ps_mr",	XRC(4,	72,0),	XRA_MASK,    PPCPS,	PPCNONE,	{FRT, FRB},	NULL},
{"ps_mr.",	XRC(4,	72,1),	XRA_MASK,    PPCPS,	PPCNONE,	{FRT, FRB},	NULL},
{"machhwsu",	XO (4,	76,0,0),XO_MASK,     MULHW|PPCVLE,  PPCNONE,	{RT, RA, RB},	NULL},
{"machhwsu.",	XO (4,	76,0,1),XO_MASK,     MULHW|PPCVLE,  PPCNONE,	{RT, RA, RB},	NULL},
{"ps_cmpo1",	X  (4,	96), X_MASK|(3<<21), PPCPS,	PPCNONE,	{BF, FRA, FRB},	NULL},
{"vaddudm",	VX (4, 192),	VX_MASK,     PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"vmaxud",	VX (4, 194),	VX_MASK,     PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"vrld",	VX (4, 196),	VX_MASK,     PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpeqfp",	VXR(4, 198,0),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpequd",	VXR(4, 199,0),	VXR_MASK,    PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"vpkuwus",	VX (4, 206),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"machhws",	XO (4, 108,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"machhws.",	XO (4, 108,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmachhws",	XO (4, 110,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmachhws.",	XO (4, 110,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"vadduqm",	VX (4, 256),	VX_MASK,     PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"vmaxsb",	VX (4, 258),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vslb",	VX (4, 260),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vmulosb",	VX (4, 264),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vrefp",	VX (4, 266),	VXVA_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, VB},	NULL},
{"vmrglb",	VX (4, 268),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vpkshus",	VX (4, 270),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"ps_nabs",	XRC(4, 136,0),	XRA_MASK,    PPCPS,	PPCNONE,	{FRT, FRB},	NULL},
{"mulchwu",	XRC(4, 136,0),	X_MASK,      MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"ps_nabs.",	XRC(4, 136,1),	XRA_MASK,    PPCPS,	PPCNONE,	{FRT, FRB},	NULL},
{"mulchwu.",	XRC(4, 136,1),	X_MASK,      MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"macchwu",	XO (4, 140,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"macchwu.",	XO (4, 140,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"vaddcuq",	VX (4, 320),	VX_MASK,     PPCVEC2,      PPCNONE,	{VD, VA, VB},	NULL},
{"vmaxsh",	VX (4, 322),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vslh",	VX (4, 324),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vmulosh",	VX (4, 328),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vrsqrtefp",	VX (4, 330),	VXVA_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, VB},	NULL},
{"vmrglh",	VX (4, 332),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vpkswus",	VX (4, 334),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"mulchw",	XRC(4, 168,0),	X_MASK,      MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"mulchw.",	XRC(4, 168,1),	X_MASK,      MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"macchw",	XO (4, 172,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"macchw.",	XO (4, 172,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmacchw",	XO (4, 174,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmacchw.",	XO (4, 174,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"vaddcuw",	VX (4, 384),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vmaxsw",	VX (4, 386),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vslw",	VX (4, 388),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vmulosw",	VX (4, 392),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"vexptefp",	VX (4, 394),	VXVA_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, VB},	NULL},
{"vmrglw",	VX (4, 396),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vpkshss",	VX (4, 398),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"macchwsu",	XO (4, 204,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"macchwsu.",	XO (4, 204,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"vmaxsd",	VX (4, 450),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"vsl",		VX (4, 452),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpgefp",	VXR(4, 454,0),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vlogefp",	VX (4, 458),	VXVA_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, VB},	NULL},
{"vpkswss",	VX (4, 462),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"macchws",	XO (4, 236,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"macchws.",	XO (4, 236,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmacchws",	XO (4, 238,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmacchws.",	XO (4, 238,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"evaddw",	VX (4, 512),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vaddubs",	VX (4, 512),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evaddiw",	VX (4, 514),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RB, UIMM},	NULL},
{"vminub",	VX (4, 514),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evsubfw",	VX (4, 516),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evsubw",	VX (4, 516),	VX_MASK,     PPCSPE,	PPCNONE,	{RS, RB, RA},	NULL},
{"vsrb",	VX (4, 516),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evsubifw",	VX (4, 518),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, UIMM, RB},	NULL},
{"evsubiw",	VX (4, 518),	VX_MASK,     PPCSPE,	PPCNONE,	{RS, RB, UIMM},	NULL},
{"vcmpgtub",	VXR(4, 518,0),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evabs",	VX_RB_CONST(4, 520, 0),	VX_RB_CONST_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"vmuleub",	VX (4, 520),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evneg",	VX_RB_CONST(4, 521, 0),	VX_RB_CONST_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"evextsb",	VX_RB_CONST(4, 522, 0),	VX_RB_CONST_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"vrfin",	VX (4, 522),	VXVA_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, VB},	NULL},
{"evextsh",	VX_RB_CONST(4, 523, 0),	VX_RB_CONST_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"evrndw",	VX (4, 524),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"vspltb",	VX (4, 524),	VXUIMM4_MASK,PPCVEC|PPCVLE, PPCNONE,	{VD, VB, UIMM4},	NULL},
{"evcntlzw",	VX_RB_CONST(4, 525, 0),	VX_RB_CONST_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"evcntlsw",	VX_RB_CONST(4, 526, 0),	VX_RB_CONST_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"vupkhsb",	VX (4, 526),	VXVA_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, VB},	NULL},
{"brinc",	VX (4, 527),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"ps_abs",	XRC(4, 264,0),	XRA_MASK,    PPCPS,	PPCNONE,	{FRT, FRB},	NULL},
{"ps_abs.",	XRC(4, 264,1),	XRA_MASK,    PPCPS,	PPCNONE,	{FRT, FRB},	NULL},
{"evand",	VX (4, 529),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evandc",	VX (4, 530),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evxor",	VX (4, 534),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmr",	VX (4, 535),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, BBA},	NULL},
{"evor",	VX (4, 535),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evnor",	VX (4, 536),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evnot",	VX (4, 536),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, BBA},	NULL},
{"get",		APU(4, 268,0),	APU_RA_MASK, PPC405,	PPCNONE,	{RT, FSL},	NULL},
{"eveqv",	VX (4, 537),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evorc",	VX (4, 539),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evnand",	VX (4, 542),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evsrwu",	VX (4, 544),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evsrws",	VX (4, 545),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evsrwiu",	VX (4, 546),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, EVUIMM},	NULL},
{"evsrwis",	VX (4, 547),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, EVUIMM},	NULL},
{"evslw",	VX (4, 548),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evslwi",	VX (4, 550),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, EVUIMM},	NULL},
{"evrlw",	VX (4, 552),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evsplati",	VX_RB_CONST(4, 553, 0),	VX_RB_CONST_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, SIMM},	NULL},
{"evrlwi",	VX (4, 554),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, EVUIMM},	NULL},
{"evsplatfi",	VX_RB_CONST(4, 555, 0),	VX_RB_CONST_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, SIMM},	NULL},
{"evmergehi",	VX (4, 556),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmergelo",	VX (4, 557),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmergehilo",	VX (4, 558),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmergelohi",	VX (4, 559),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evcmpgtu",	VX_SPE_CRFD (4, 560, 0), VX_SPE_CRFD_MASK, PPCSPE|PPCVLE, PPCNONE, {CRFD, RA, RB}, NULL},
{"evcmpgts",	VX_SPE_CRFD (4, 561, 0), VX_SPE_CRFD_MASK, PPCSPE|PPCVLE, PPCNONE, {CRFD, RA, RB}, NULL},
{"evcmpltu",	VX_SPE_CRFD (4, 562, 0), VX_SPE_CRFD_MASK, PPCSPE|PPCVLE, PPCNONE, {CRFD, RA, RB}, NULL},
{"evcmplts",	VX_SPE_CRFD (4, 563, 0), VX_SPE_CRFD_MASK, PPCSPE|PPCVLE, PPCNONE, {CRFD, RA, RB}, NULL},
{"evcmpeq",	VX_SPE_CRFD (4, 564, 0), VX_SPE_CRFD_MASK, PPCSPE|PPCVLE, PPCNONE, {CRFD, RA, RB}, NULL},
{"cget",	APU(4, 284,0),	APU_RA_MASK, PPC405,	PPCNONE,	{RT, FSL},	NULL},
{"vadduhs",	VX (4, 576),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vminuh",	VX (4, 578),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vsrh",	VX (4, 580),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpgtuh",	VXR(4, 582,0),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vmuleuh",	VX (4, 584),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vrfiz",	VX (4, 586),	VXVA_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, VB},	NULL},
{"vsplth",	VX (4, 588),	VXUIMM3_MASK,PPCVEC|PPCVLE, PPCNONE,	{VD, VB, UIMM3},	NULL},
{"vupkhsh",	VX (4, 590),	VXVA_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, VB},	NULL},
{"nget",	APU(4, 300,0),	APU_RA_MASK, PPC405,	PPCNONE,	{RT, FSL},	NULL},
{"evsel",	EVSEL(4,79),	EVSEL_MASK,  PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB, CRFS},	NULL},
{"ncget",	APU(4, 316,0),	APU_RA_MASK, PPC405,	PPCNONE,	{RT, FSL},	NULL},
{"evfsadd",	VX (4, 640),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vadduws",	VX (4, 640),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evfssub",	VX (4, 641),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evfsmadd",	VX (4, 642),    VX_MASK,     PPCSPE|PPCVLE, PPCNONE,    {RS, RA, RB},   NULL},
{"vminuw",	VX (4, 642),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evfsmsub",	VX (4, 643),    VX_MASK,     PPCSPE|PPCVLE, PPCNONE,    {RS, RA, RB},   NULL},
{"evfsabs",	VX (4, 644),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"vsrw",	VX (4, 644),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evfsnabs",	VX (4, 645),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"evfsneg",	VX (4, 646),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"vcmpgtuw",	VXR(4, 646,0),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vmuleuw",	VX (4, 648),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"evfsmul",	VX (4, 648),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evfsdiv",	VX (4, 649),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evfsnmadd",	VX (4, 650),    VX_MASK,     PPCSPE|PPCVLE, PPCNONE,    {RS, RA, RB},   NULL},
{"vrfip",	VX (4, 650),	VXVA_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, VB},	NULL},
{"evfsnmsub",	VX (4, 651),    VX_MASK,     PPCSPE|PPCVLE, PPCNONE,    {RS, RA, RB},   NULL},
{"evfscmpgt",	VX (4, 652),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"vspltw",	VX (4, 652),	VXUIMM2_MASK,PPCVEC|PPCVLE, PPCNONE,	{VD, VB, UIMM2},	NULL},
{"evfscmplt",	VX (4, 653),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"evfscmpeq",	VX (4, 654),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"vupklsb",	VX (4, 654),	VXVA_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, VB},	NULL},
{"evfscfui",	VX (4, 656),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"evfscfsi",	VX (4, 657),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"evfscfuf",	VX (4, 658),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"evfscfsf",	VX (4, 659),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"evfsctui",	VX (4, 660),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"evfsctsi",	VX (4, 661),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"evfsctuf",	VX (4, 662),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"evfsctsf",	VX (4, 663),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"evfsctuiz",	VX (4, 664),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"put",		APU(4, 332,0),	APU_RT_MASK, PPC405,	PPCNONE,	{RA, FSL},	NULL},
{"evfsctsiz",	VX (4, 666),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"evfststgt",	VX (4, 668),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"evfststlt",	VX (4, 669),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"evfststeq",	VX (4, 670),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"cput",	APU(4, 348,0),	APU_RT_MASK, PPC405,	PPCNONE,	{RA, FSL},	NULL},
{"efsmax",      VX (4, 688),    VX_MASK,     PPCEFS2|PPCVLE, PPCNONE,   {RD, RA, RB},   NULL},
{"efsmin",      VX (4, 689),    VX_MASK,     PPCEFS2|PPCVLE, PPCNONE,   {RD, RA, RB},   NULL},
{"efdmax",      VX (4, 696),    VX_MASK,     PPCEFS2|PPCVLE, PPCNONE,   {RD, RA, RB},   NULL},
{"efdmin",      VX (4, 697),    VX_MASK,     PPCEFS2|PPCVLE, PPCNONE,   {RD, RA, RB},   NULL},
{"efsadd",	VX (4, 704),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"efssub",	VX (4, 705),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"efsmadd",	VX (4, 706),    VX_MASK,     PPCEFS|PPCVLE, PPCNONE,    {RS, RA, RB},   NULL},
{"vminud",	VX (4, 706),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"efsmsub",	VX (4, 707),    VX_MASK,     PPCEFS|PPCVLE, PPCNONE,    {RS, RA, RB},   NULL},
{"efsabs",	VX (4, 708),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"vsr",		VX (4, 708),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"efsnabs",	VX (4, 709),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"efsneg",	VX (4, 710),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"vcmpgtfp",	VXR(4, 710,0),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpgtud",	VXR(4, 711,0),	VXR_MASK,    PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"efssqrt",  VX_RB_CONST(4, 711, 0),    VX_RB_CONST_MASK,     PPCEFS2|PPCVLE, PPCNONE,   {RD, RA},       NULL},
{"efsmul",	VX (4, 712),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"efsdiv",	VX (4, 713),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"efsnmadd",    VX (4, 714),    VX_MASK,     PPCEFS|PPCVLE, PPCNONE,    {RS, RA, RB},   NULL},
{"vrfim",	VX (4, 714),	VXVA_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, VB},	NULL},
{"efsnmsub",    VX (4, 715),    VX_MASK,     PPCEFS|PPCVLE, PPCNONE,    {RS, RA, RB},   NULL},
{"efscmpgt",	VX (4, 716),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"efscmplt",	VX (4, 717),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"efscmpeq",	VX (4, 718),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"vupklsh",	VX (4, 718),	VXVA_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, VB},	NULL},
{"efscfd",	VX (4, 719),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"efscfui",	VX (4, 720),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"efscfsi",	VX_RA_CONST(4, 721, 0), VX_RA_CONST_MASK,  PPCEFS|PPCVLE, PPCNONE, {RS, RB}, NULL},
{"efscfh", 	VX_RA_CONST(4, 721, 4), VX_RA_CONST_MASK, PPCEFS2|PPCVLE, PPCNONE, {RD, RB}, NULL},
{"efscfuf",	VX (4, 722),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"efscfsf",	VX (4, 723),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"efsctui",	VX (4, 724),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"efsctsi",	VX_RA_CONST(4, 725, 0), VX_RA_CONST_MASK,  PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"efscth",	VX_RA_CONST(4, 725, 4), VX_RA_CONST_MASK, PPCEFS2|PPCVLE, PPCNONE, {RD, RB}, NULL},
{"efsctuf",	VX (4, 726),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"efsctsf",	VX (4, 727),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"efsctuiz",	VX (4, 728),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"nput",	APU(4, 364,0),	APU_RT_MASK, PPC405,	PPCNONE,	{RA, FSL},	NULL},
{"efsctsiz",	VX (4, 730),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"efststgt",	VX (4, 732),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"efststlt",	VX (4, 733),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"efststeq",	VX (4, 734),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"efdadd",	VX (4, 736),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"efdsub",	VX (4, 737),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
//{"efdcfuid",	VX (4, 738),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL}, //moved to 752
{"efdmadd",     VX (4, 738),    VX_MASK,     PPCEFS|PPCVLE, PPCNONE,    {RD, RA, RB},   NULL},
//{"efdcfsid",	VX (4, 739),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL}, //moved to 753
{"efdmsub",     VX (4, 739),    VX_MASK,     PPCEFS|PPCVLE, PPCNONE,    {RD, RA, RB},   NULL},
{"efdabs",	VX (4, 740),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"efdnabs",	VX (4, 741),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"efdneg",	VX (4, 742),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"efdsqrt",	VX_RB_CONST(4, 743, 0), VX_RB_CONST_MASK, PPCEFS2|PPCVLE, PPCNONE, {RD, RA}, NULL},
{"efdmul",	VX (4, 744),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"efddiv",	VX (4, 745),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
//{"efdctuidz",	VX (4, 746),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL}, //moved to 760
{"efdnmadd",    VX (4, 746),    VX_MASK,     PPCEFS|PPCVLE, PPCNONE,    {RD, RA, RB},   NULL},
//{"efdctsidz",	VX (4, 747),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL}, //moved to 762
{"efdnmsub",    VX (4, 747),    VX_MASK,     PPCEFS|PPCVLE, PPCNONE,    {RD, RA, RB},   NULL},
{"efdcmpgt",	VX (4, 748),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"efdcmplt",	VX (4, 749),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"efdcmpeq",	VX (4, 750),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"efdcfs",	VX (4, 751),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"efdcfui",	VX_RA_CONST(4, 752, 0),	VX_RA_CONST_MASK,     PPCEFS|PPCVLE, PPCNONE, {RS, RB},	NULL},
{"efdcfuid",	VX_RA_CONST(4, 752, 1), VX_RA_CONST_MASK,     PPCEFS|PPCVLE, PPCNONE, {RS, RB},	NULL}, //in acc EFP2_rev.1.4_spec
{"efdcfsi",	VX_RA_CONST(4, 753, 0), VX_RA_CONST_MASK, PPCEFS|PPCVLE, PPCNONE, {RS, RB}, NULL},
{"efdcfsid",	VX_RA_CONST(4, 753, 1),	VX_RA_CONST_MASK, PPCEFS|PPCVLE, PPCNONE, {RS, RB}, NULL }, //in acc EFP2_rev.1.4_spec
{"efdcfh",	VX_RA_CONST(4, 753, 4), VX_RA_CONST_MASK, PPCEFS2|PPCVLE, PPCNONE, {RD, RB}, NULL},
{"efdcfuf",	VX (4, 754),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"efdcfsf",	VX (4, 755),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"efdctui",	VX (4, 756),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"efdctsi",	VX_RA_CONST(4, 757, 0), VX_RA_CONST_MASK, PPCEFS|PPCVLE, PPCNONE, {RS, RB}, NULL},
{"efdcth",	VX_RA_CONST(4, 757, 4), VX_RA_CONST_MASK, PPCEFS2|PPCVLE, PPCNONE, {RD, RB}, NULL},
{"efdctuf",	VX (4, 758),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"efdctsf",	VX (4, 759),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{RS, RB},	NULL},
{"efdctuiz",	VX_RA_CONST(4, 760, 0),	VX_RA_CONST_MASK,     PPCEFS|PPCVLE, PPCNONE, {RS, RB},	NULL},
{"efdctuidz",	VX_RA_CONST(4, 760, 1),	VX_RA_CONST_MASK,     PPCEFS|PPCVLE, PPCNONE, {RS, RB},	NULL }, //in acc EFP2_rev.1.4_spec
{"ncput",	APU(4, 380,0),	APU_RT_MASK, PPC405,	PPCNONE,	{RA, FSL},	NULL},
{"efdctsiz",	VX_RA_CONST(4, 762, 0),	VX_RA_CONST_MASK,     PPCEFS|PPCVLE, PPCNONE, {RS, RB},	NULL},
{"efdctsidz",	VX_RA_CONST(4, 762, 1),	VX_RA_CONST_MASK,     PPCEFS|PPCVLE, PPCNONE, {RS, RB},	NULL }, //in acc EFP2_rev.1.4_spec
{"efdtstgt",	VX (4, 764),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"efdtstlt",	VX (4, 765),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"efdtsteq",	VX (4, 766),	VX_MASK,     PPCEFS|PPCVLE, PPCNONE,	{CRFD, RA, RB},	NULL},
{"evlddx",	VX (4, 768),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vaddsbs",	VX (4, 768),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evldd",	VX (4, 769),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_8, RA},	NULL},
{"evldwx",	VX (4, 770),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vminsb",	VX (4, 770),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evldw",	VX (4, 771),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_8, RA},	NULL},
{"evldhx",	VX (4, 772),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vsrab",	VX (4, 772),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evldh",	VX (4, 773),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_8, RA},	NULL},
{"vcmpgtsb",	VXR(4, 774,0),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evlhhesplatx",VX (4, 776),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vmulesb",	VX (4, 776),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evlhhesplat",	VX (4, 777),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_2, RA},	NULL},
{"vcfux",	VX (4, 778),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VB, UIMM},	NULL},
{"vcuxwfp",	VX (4, 778),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VB, UIMM},	NULL},
{"evlhhousplatx",VX(4, 780),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vspltisb",	VX (4, 780),	VXVB_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, SIMM},	NULL},
{"evlhhousplat",VX (4, 781),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_2, RA},	NULL},
{"evlhhossplatx",VX(4, 782),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vpkpx",	VX (4, 782),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evlhhossplat",VX (4, 783),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_2, RA},	NULL},
{"mullhwu",	XRC(4, 392,0),	X_MASK,      MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"evlwhex",	VX (4, 784),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"mullhwu.",	XRC(4, 392,1),	X_MASK,      MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"evlwhe",	VX (4, 785),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_4, RA},	NULL},
{"evlwhoux",	VX (4, 788),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evlwhou",	VX (4, 789),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_4, RA},	NULL},
{"evlwhosx",	VX (4, 790),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evlwhos",	VX (4, 791),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_4, RA},	NULL},
{"maclhwu",	XO (4, 396,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"evlwwsplatx",	VX (4, 792),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"maclhwu.",	XO (4, 396,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"evlwwsplat",	VX (4, 793),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_4, RA},	NULL},
{"evlwhsplatx",	VX (4, 796),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evlwhsplat",	VX (4, 797),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_4, RA},	NULL},
{"evstddx",	VX (4, 800),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evstdd",	VX (4, 801),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_8, RA},	NULL},
{"evstdwx",	VX (4, 802),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evstdw",	VX (4, 803),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_8, RA},	NULL},
{"evstdhx",	VX (4, 804),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evstdh",	VX (4, 805),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_8, RA},	NULL},
{"evstwhex",	VX (4, 816),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evstwhe",	VX (4, 817),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_4, RA},	NULL},
{"evstwhox",	VX (4, 820),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evstwho",	VX (4, 821),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_4, RA},	NULL},
{"evstwwex",	VX (4, 824),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evstwwe",	VX (4, 825),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_4, RA},	NULL},
{"evstwwox",	VX (4, 828),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evstwwo",	VX (4, 829),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, EVUIMM_4, RA},	NULL},
{"vaddshs",	VX (4, 832),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vminsh",	VX (4, 834),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vsrah",	VX (4, 836),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpgtsh",	VXR(4, 838,0),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vmulesh",	VX (4, 840),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vcfsx",	VX (4, 842),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VB, UIMM},	NULL},
{"vcsxwfp",	VX (4, 842),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VB, UIMM},	NULL},
{"vspltish",	VX (4, 844),	VXVB_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, SIMM},	NULL},
{"vupkhpx",	VX (4, 846),	VXVA_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, VB},	NULL},
{"mullhw",	XRC(4, 424,0),	X_MASK,      MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"mullhw.",	XRC(4, 424,1),	X_MASK,      MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"maclhw",	XO (4, 428,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"maclhw.",	XO (4, 428,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmaclhw",	XO (4, 430,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmaclhw.",	XO (4, 430,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"vaddsws",	VX (4, 896),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vminsw",	VX (4, 898),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vsraw",	VX (4, 900),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpgtsw",	VXR(4, 902,0),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vmulesw",	VX (4, 904),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"vctuxs",	VX (4, 906),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VB, UIMM},	NULL},
{"vcfpuxws",	VX (4, 906),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VB, UIMM},	NULL},
{"vspltisw",	VX (4, 908),	VXVB_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, SIMM},	NULL},
{"maclhwsu",	XO (4, 460,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"maclhwsu.",	XO (4, 460,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"vminsd",	VX (4, 962),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"vsrad",	VX (4, 964),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpbfp",	VXR(4, 966,0),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpgtsd",	VXR(4, 967,0),	VXR_MASK,    PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"vctsxs",	VX (4, 970),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VB, UIMM},	NULL},
{"vcfpsxws",	VX (4, 970),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VB, UIMM},	NULL},
{"vupklpx",	VX (4, 974),	VXVA_MASK,   PPCVEC|PPCVLE, PPCNONE,	{VD, VB},	NULL},
{"maclhws",	XO (4, 492,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"maclhws.",	XO (4, 492,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmaclhws",	XO (4, 494,0,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmaclhws.",	XO (4, 494,0,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"vsububm",	VX (4,1024),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"bcdadd.",	VX (4,1025),	VXPS_MASK,   PPCVEC2,	    PPCNONE,	{VD, VA, VB, PS},	NULL},
{"vavgub",	VX (4,1026),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vabsdub",	VX (4,1027),	VX_MASK,     PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"evmhessf",	VX (4,1027),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vand",	VX (4,1028),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpequb.",	VXR(4,	 6,1),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"udi0fcm.",	APU(4, 515,0), APU_MASK, PPC405|PPC440, PPC476,		{URT, URA, URB},	NULL},
{"udi0fcm",	APU(4, 515,1), APU_MASK, PPC405|PPC440, PPC476,		{URT, URA, URB},	NULL},
{"evmhossf",	VX (4,1031),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vpmsumb",	VX (4,1032),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"evmheumi",	VX (4,1032),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhesmi",	VX (4,1033),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vmaxfp",	VX (4,1034),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evmhesmf",	VX (4,1035),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhoumi",	VX (4,1036),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vslo",	VX (4,1036),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evmhosmi",	VX (4,1037),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhosmf",	VX (4,1039),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"machhwuo",	XO (4,	12,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"machhwuo.",	XO (4,	12,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"ps_merge00",	XOPS(4,528,0),	XOPS_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"ps_merge00.",	XOPS(4,528,1),	XOPS_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"evmhessfa",	VX (4,1059),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhossfa",	VX (4,1063),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmheumia",	VX (4,1064),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhesmia",	VX (4,1065),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhesmfa",	VX (4,1067),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhoumia",	VX (4,1068),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhosmia",	VX (4,1069),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhosmfa",	VX (4,1071),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vsubuhm",	VX (4,1088),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"bcdsub.",	VX (4,1089),	VXPS_MASK,   PPCVEC2,	    PPCNONE,	{VD, VA, VB, PS},	NULL},
{"vavguh",	VX (4,1090),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vabsduh",	VX (4,1091),	VX_MASK,     PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"evmwlssf",  VX(4, 1091), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"vandc",	VX (4,1092),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpequh.",	VXR(4,	70,1),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"udi1fcm.",	APU(4, 547,0), APU_MASK, PPC405|PPC440, PPC476,		{URT, URA, URB},	NULL},
{"udi1fcm",	APU(4, 547,1), APU_MASK, PPC405|PPC440, PPC476,		{URT, URA, URB},	NULL},   
{"evmwhssf",	VX (4,1095),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vpmsumh",	VX (4,1096),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"evmwlumi",	VX (4,1096),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vminfp",	VX (4,1098),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evmwlsmf",  VX(4, 1099), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"evmwhumi",	VX (4,1100),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vsro",	VX (4,1100),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evmwhsmi",	VX (4,1101),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vpkudum",	VX (4,1102),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"evmwhsmf",	VX (4,1103),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwssf",	VX (4,1107),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"machhwo",	XO (4,	44,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"evmwumi",	VX (4,1112),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"machhwo.",	XO (4,	44,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"evmwsmi",	VX (4,1113),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwsmf",	VX (4,1115),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"nmachhwo",	XO (4,	46,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmachhwo.",	XO (4,	46,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"ps_merge01",	XOPS(4,560,0),	XOPS_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"ps_merge01.",	XOPS(4,560,1),	XOPS_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"evmwlssfa", VX(4, 1123), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"evmwhssfa",	VX (4,1127),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwlumia",	VX (4,1128),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwlsmfa", VX(4, 1131),	VX_MASK,	   PPCSPE|PPCVLE, PPCNONE,	{RD, RA, RB}, NULL},
{"evmwhumia",	VX (4,1132),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwhsmia",	VX (4,1133),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwhsmfa",	VX (4,1135),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwssfa",	VX (4,1139),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwumia",	VX (4,1144),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwsmia",	VX (4,1145),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwsmfa",	VX (4,1147),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vsubuwm",	VX (4,1152),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vavguw",	VX (4,1154),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vabsduw",	VX (4,1155),	VX_MASK,     PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"vmr",		VX (4,1156),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VBA},	NULL},
{"vor",		VX (4,1156),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vpmsumw",	VX (4,1160),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpequw.",	VXR(4, 134,1),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"udi2fcm.",	APU(4, 579,0), APU_MASK, PPC405|PPC440, PPC476,		{URT, URA, URB},	NULL},
{"udi2fcm",	APU(4, 579,1), APU_MASK, PPC405|PPC440, PPC476,		{URT, URA, URB},	NULL},   
{"machhwsuo",	XO (4,	76,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"machhwsuo.",	XO (4,	76,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"ps_merge10",	XOPS(4,592,0),	XOPS_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"ps_merge10.",	XOPS(4,592,1),	XOPS_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"vsubudm",	VX (4,1216),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"evaddusiaaw",	VX (4,1216),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"evaddssiaaw",	VX (4,1217),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"evsubfusiaaw",VX (4,1218),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"evsubfssiaaw",VX (4,1219),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"evmra",	VX (4,1220),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"vxor",	VX (4,1220),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evdivws",	VX (4,1222),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vcmpeqfp.",	VXR(4, 198,1),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"udi3fcm.",	APU(4, 611,0), APU_MASK, PPC405|PPC440, PPC476,		{URT, URA, URB},	NULL},
{"vcmpequd.",	VXR(4, 199,1),	VXR_MASK,    PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"udi3fcm",	APU(4, 611,1), APU_MASK, PPC405|PPC440, PPC476,		{URT, URA, URB},	NULL},   
{"evdivwu",	VX (4,1223),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vpmsumd",	VX (4,1224),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"evaddumiaaw",	VX (4,1224),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"evaddsmiaaw",	VX (4,1225),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"evsubfumiaaw",VX (4,1226),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"evsubfsmiaaw",VX (4,1227),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA},	NULL},
{"vpkudus",	VX (4,1230),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"machhwso",	XO (4, 108,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"machhwso.",	XO (4, 108,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmachhwso",	XO (4, 110,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmachhwso.",	XO (4, 110,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"ps_merge11",	XOPS(4,624,0),	XOPS_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"ps_merge11.",	XOPS(4,624,1),	XOPS_MASK,   PPCPS,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"vsubuqm",	VX (4,1280),	VX_MASK,     PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"evmheusiaaw",	VX (4,1280),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhessiaaw",	VX (4,1281),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vavgsb",	VX (4,1282),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evmhessfaaw",	VX (4,1283),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhousiaaw",	VX (4,1284),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vnot",	VX (4,1284),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VBA},	NULL},
{"vnor",	VX (4,1284),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evmhossiaaw",	VX (4,1285),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"udi4fcm.",	APU(4, 643,0), APU_MASK, PPC405|PPC440, PPC476,		{URT, URA, URB},	NULL},
{"udi4fcm",	APU(4, 643,1), APU_MASK, PPC405|PPC440, PPC476,		{URT, URA, URB},	NULL},
{"evmhossfaaw",	VX (4,1287),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmheumiaaw",	VX (4,1288),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vcipher",	VX (4,1288),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"vcipherlast",	VX (4,1289),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"evmhesmiaaw",	VX (4,1289),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhesmfaaw",	VX (4,1291),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vgbbd",	VX (4,1292),	VXVA_MASK,   PPCVEC2,	    PPCNONE,	{VD, VB},	NULL},
{"evmhoumiaaw",	VX (4,1292),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhosmiaaw",	VX (4,1293),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhosmfaaw",	VX (4,1295),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"macchwuo",	XO (4, 140,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"macchwuo.",	XO (4, 140,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"evmhegumiaa",	VX (4,1320),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhegsmiaa",	VX (4,1321),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhegsmfaa",	VX (4,1323),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhogumiaa",	VX (4,1324),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhogsmiaa",	VX (4,1325),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhogsmfaa",	VX (4,1327),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vsubcuq",	VX (4,1344),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"evmwlusiaaw",	VX (4,1344),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwlssiaaw",	VX (4,1345),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vavgsh",	VX (4,1346),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evmwlssfaaw", VX(4, 1347), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"vorc",	VX (4,1348),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"evmwhusiaa", VX(4, 1348), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"evmwhssmaa", VX(4, 1349), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"udi5fcm.",	APU(4, 675,0), APU_MASK, PPC405|PPC440, PPC476,		{URT, URA, URB},	NULL},
{"udi5fcm",	APU(4, 675,1), APU_MASK, PPC405|PPC440, PPC476,		{URT, URA, URB},	NULL},
{"evmwhssfaa",	VX(4, 1351), 	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RD, RA, RB}, 	NULL},
{"vncipher",	VX (4,1352),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"evmwlumiaaw",	VX (4,1352),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vncipherlast",VX (4,1353),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"evmwlsmiaaw",	VX (4,1353),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwlsmfaaw", VX(4, 1355), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"vbpermq",	VX (4,1356),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"evmwhumiaa", VX(4, 1356), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"evmwhsmiaa", VX(4, 1357), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"vpksdus",	VX (4,1358),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"evmwhsmfaa", VX(4, 1359), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"evmwssfaa",	VX (4,1363),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"macchwo",	XO (4, 172,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"evmwumiaa",	VX (4,1368),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"macchwo.",	XO (4, 172,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"evmwsmiaa",	VX (4,1369),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwsmfaa",	VX (4,1371),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwhgumiaa", VX(4, 1380), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"evmwhgsmiaa", VX(4, 1381), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"evmwhgssfaa", VX(4, 1383), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"evmwhgsmfaa", VX(4, 1391), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"nmacchwo",	XO (4, 174,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmacchwo.",	XO (4, 174,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"evmheusianw",	VX (4,1408),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vsubcuw",	VX (4,1408),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evmhessianw",	VX (4,1409),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vavgsw",	VX (4,1410),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"evmhessfanw",	VX (4,1411),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"vnand",	VX (4,1412),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"evmhousianw",	VX (4,1412),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhossianw",	VX (4,1413),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"udi6fcm.",	APU(4, 707,0), APU_MASK, PPC405|PPC440, PPC476,		{URT, URA, URB},	NULL},
{"udi6fcm",	APU(4, 707,1), APU_MASK, PPC405|PPC440, PPC476,		{URT, URA, URB},	NULL},
{"evmhossfanw",	VX (4,1415),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmheumianw",	VX (4,1416),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhesmianw",	VX (4,1417),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhesmfanw",	VX (4,1419),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhoumianw",	VX (4,1420),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhosmianw",	VX (4,1421),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhosmfanw",	VX (4,1423),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"macchwsuo",	XO (4, 204,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"macchwsuo.",	XO (4, 204,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"evmhegumian",	VX (4,1448),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhegsmian",	VX (4,1449),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhegsmfan",	VX (4,1451),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhogumian",	VX (4,1452),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhogsmian",	VX (4,1453),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmhogsmfan",	VX (4,1455),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwlusianw",	VX (4,1472),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwlssianw",	VX (4,1473),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwlssfanw", VX(4, 1475), VX_MASK, PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"vsld",	VX (4,1476),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"evmwhusian", VX(4, 1476), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"evmwhssian", VX(4, 1477), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"vcmpgefp.",	VXR(4, 454,1),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"udi7fcm.",	APU(4, 739,0), APU_MASK, PPC405|PPC440, PPC476,		{URT, URA, URB},	NULL},
{"udi7fcm",	APU(4, 739,1), APU_MASK, PPC405|PPC440, PPC476,		{URT, URA, URB},	NULL},
{"evmwhssfan", VX(4, 1479), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"vsbox",	VX (4,1480),	VXVB_MASK,   PPCVEC2,	    PPCNONE,	{VD, VA},	NULL},
{"evmwlumianw",	VX (4,1480),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwlsmianw",	VX (4,1481),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwlsmfanw", VX(4, 1483), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"evmwhumian", VX(4, 1484), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"evmwhsmian", VX(4, 1485), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"vpksdss",	VX (4,1486),	VX_MASK,     PPCVEC2,	    PPCNONE,	{VD, VA, VB},	NULL},
{"evmwhsmfan", VX(4, 1487), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"evmwssfan",	VX (4,1491),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"macchwso",	XO (4, 236,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"evmwumian",	VX (4,1496),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"macchwso.",	XO (4, 236,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"evmwsmian",	VX (4,1497),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwsmfan",	VX (4,1499),	VX_MASK,     PPCSPE|PPCVLE, PPCNONE,	{RS, RA, RB},	NULL},
{"evmwhgumian", VX(4, 1508), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"evmwhgsmian", VX(4, 1509), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"evmwhgssfan", VX(4, 1511), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"evmwhgsmfan", VX(4, 1519), VX_MASK,	PPCSPE|PPCVLE, PPCNONE, {RD, RA, RB}, NULL},
{"nmacchwso",	XO (4, 238,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmacchwso.",	XO (4, 238,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"vsububs",	VX (4,1536),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"mfvscr",	VX (4,1540),	VXVAVB_MASK, PPCVEC|PPCVLE, PPCNONE,	{VD},	NULL},
{"vcmpgtub.",	VXR(4, 518,1),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"udi8fcm.",	APU(4, 771,0),	APU_MASK,    PPC440,	PPC476,		{URT, URA, URB},	NULL},
{"udi8fcm",	APU(4, 771,1),	APU_MASK,    PPC440,	PPC476,		{URT, URA, URB},	NULL},
{"vsum4ubs",	VX (4,1544),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vsubuhs",	VX (4,1600),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"mtvscr",	VX (4,1604),	VXVDVA_MASK, PPCVEC|PPCVLE, PPCNONE,	{VB},	NULL},
{"vcmpgtuh.",	VXR(4, 582,1),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vsum4shs",	VX (4,1608),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"udi9fcm.",	APU(4, 804,0),	APU_MASK,    PPC440,	PPC476,		{URT, URA, URB},	NULL},
{"udi9fcm",	APU(4, 804,1),	APU_MASK,    PPC440,	PPC476,		{URT, URA, URB},	NULL},
{"vupkhsw",	VX (4,1614),	VXVA_MASK,   PPCVEC2,	    PPCNONE,	{VD, VB},	NULL},
{"vsubuws",	VX (4,1664),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vshasigmaw",	VX (4,1666),	VX_MASK,     PPCVEC2,	PPCNONE,	{VD, VA, ST, SIX},	NULL},
{"veqv",	VX (4,1668),	VX_MASK,     PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpgtuw.",	VXR(4, 646,1),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"udi10fcm.",	APU(4, 835,0),	APU_MASK,    PPC440,	PPC476,		{URT, URA, URB},	NULL},
{"udi10fcm",	APU(4, 835,1),	APU_MASK,    PPC440,	PPC476,		{URT, URA, URB},	NULL},
{"vsum2sws",	VX (4,1672),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vmrgow",	VX (4,1676),	VX_MASK,     PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"vshasigmad",	VX (4,1730),	VX_MASK,     PPCVEC2,	PPCNONE,	{VD, VA, ST, SIX},	NULL},
{"vsrd",	VX (4,1732),	VX_MASK,     PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"vcmpgtfp.",	VXR(4, 710,1),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"udi11fcm.",	APU(4, 867,0),	APU_MASK,    PPC440,	PPC476,		{URT, URA, URB},	NULL},
{"vcmpgtud.",	VXR(4, 711,1),	VXR_MASK,    PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"udi11fcm",	APU(4, 867,1),	APU_MASK,    PPC440,	PPC476,		{URT, URA, URB},	NULL},
{"vupklsw",	VX (4,1742),	VXVA_MASK,   PPCVEC2,	PPCNONE,	{VD, VB},	NULL},
{"vsubsbs",	VX (4,1792),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vclzb",	VX (4,1794),	VXVA_MASK,   PPCVEC2,	PPCNONE,	{VD, VB},	NULL},
{"vpopcntb",	VX (4,1795),	VXVA_MASK,   PPCVEC2,	PPCNONE,	{VD, VB},	NULL},
{"vcmpgtsb.",	VXR(4, 774,1),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"udi12fcm.",	APU(4, 899,0),	APU_MASK,    PPC440,	PPC476,		{URT, URA, URB},	NULL},
{"udi12fcm",	APU(4, 899,1),	APU_MASK,    PPC440,	PPC476,		{URT, URA, URB},	NULL},
{"vsum4sbs",	VX (4,1800),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"maclhwuo",	XO (4, 396,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"maclhwuo.",	XO (4, 396,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"vsubshs",	VX (4,1856),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vclzh",	VX (4,1858),	VXVA_MASK,   PPCVEC2,	PPCNONE,	{VD, VB},	NULL},
{"vpopcnth",	VX (4,1859),	VXVA_MASK,   PPCVEC2,	PPCNONE,	{VD, VB},	NULL},
{"vcmpgtsh.",	VXR(4, 838,1),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"udi13fcm.",	APU(4, 931,0),	APU_MASK,    PPC440,	PPC476,		{URT, URA, URB},	NULL},
{"udi13fcm",	APU(4, 931,1),	APU_MASK,    PPC440,	PPC476,		{URT, URA, URB},	NULL},
{"maclhwo",	XO (4, 428,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"maclhwo.",	XO (4, 428,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmaclhwo",	XO (4, 430,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmaclhwo.",	XO (4, 430,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"vsubsws",	VX (4,1920),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vclzw",	VX (4,1922),	VXVA_MASK,   PPCVEC2,	PPCNONE,	{VD, VB},	NULL},
{"vpopcntw",	VX (4,1923),	VXVA_MASK,   PPCVEC2,	PPCNONE,	{VD, VB},	NULL},
{"vcmpgtsw.",	VXR(4, 902,1),	VXR_MASK,    PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"udi14fcm.",	APU(4, 963,0),	APU_MASK,    PPC440,	PPC476,		{URT, URA, URB},	NULL},
{"udi14fcm",	APU(4, 963,1),	APU_MASK,    PPC440,	PPC476,		{URT, URA, URB},	NULL},
{"vsumsws",	VX (4,1928),	VX_MASK,     PPCVEC|PPCVLE, PPCNONE,	{VD, VA, VB},	NULL},
{"vmrgew",	VX (4,1932),	VX_MASK,     PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"maclhwsuo",	XO (4, 460,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"maclhwsuo.",	XO (4, 460,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"vclzd",	VX (4,1986),	VXVA_MASK,   PPCVEC2,	PPCNONE,	{VD, VB},	NULL},
{"vpopcntd",	VX (4,1987),	VXVA_MASK,   PPCVEC2,	PPCNONE,	{VD, VB},	NULL},
{"vcmpbfp.",	VXR(4, 966,1),	VXR_MASK,    PPCVEC|PPCVLE,	PPCNONE,	{VD, VA, VB},	NULL},
{"udi15fcm.",	APU(4, 995,0),	APU_MASK,    PPC440,	PPC476,		{URT, URA, URB},	NULL},
{"vcmpgtsd.",	VXR(4, 967,1),	VXR_MASK,    PPCVEC2,	PPCNONE,	{VD, VA, VB},	NULL},
{"udi15fcm",	APU(4, 995,1),	APU_MASK,    PPC440,	PPC476,		{URT, URA, URB},	NULL},
{"maclhwso",	XO (4, 492,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"maclhwso.",	XO (4, 492,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmaclhwso",	XO (4, 494,1,0),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"nmaclhwso.",	XO (4, 494,1,1),XO_MASK,     MULHW|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"dcbz_l",	X  (4,1014),	XRT_MASK,    PPCPS,	PPCNONE,	{RA, RB},	NULL},

{"mulli",	OP(7),		OP_MASK,     PPCCOM,	PPCNONE,	{RT, RA, SI},	translate_mulli},
{"muli",	OP(7),		OP_MASK,     PWRCOM,	PPCNONE,	{RT, RA, SI},	NULL},

{"subfic",	OP(8),		OP_MASK,     PPCCOM,	PPCNONE,	{RT, RA, SI},	translate_subfic},
{"sfi",		OP(8),		OP_MASK,     PWRCOM,	PPCNONE,	{RT, RA, SI},	NULL},

{"dozi",	OP(9),		OP_MASK,     M601,	PPCNONE,	{RT, RA, SI},	NULL},

{"cmplwi",	OPL(10,0),	OPL_MASK,    PPCCOM,	PPCNONE,	{OBF, RA, UISIGNOPT},	translate_cmpli},
{"cmpldi",	OPL(10,1),	OPL_MASK,    PPC64,	PPCNONE,	{OBF, RA, UISIGNOPT},	NULL},
{"cmpli",	OP(10),		OP_MASK,     PPC,	PPCNONE,	{BF, L, RA, UISIGNOPT},	translate_cmpli},
{"cmpli",	OP(10),		OP_MASK,     PWRCOM,	PPC,		{BF, RA, UISIGNOPT},	NULL},

{"cmpwi",	OPL(11,0),	OPL_MASK,    PPCCOM,	PPCNONE,	{OBF, RA, SI},	translate_cmpi},
{"cmpdi",	OPL(11,1),	OPL_MASK,    PPC64,	PPCNONE,	{OBF, RA, SI},	NULL},
{"cmpi",	OP(11),		OP_MASK,     PPC,	PPCNONE,	{BF, L, RA, SI},	translate_cmpi},
{"cmpi",	OP(11),		OP_MASK,     PWRCOM,	PPC,		{BF, RA, SI},	NULL},

{"addic",	OP(12),		OP_MASK,     PPCCOM,	PPCNONE,	{RT, RA, SI},	translate_addic},
{"ai",		OP(12),		OP_MASK,     PWRCOM,	PPCNONE,	{RT, RA, SI},	NULL},
{"subic",	OP(12),		OP_MASK,     PPCCOM,	PPCNONE,	{RT, RA, NSI},	translate_subic},

{"addic.",	OP(13),		OP_MASK,     PPCCOM,	PPCNONE,	{RT, RA, SI},	translate_addic},
{"ai.",		OP(13),		OP_MASK,     PWRCOM,	PPCNONE,	{RT, RA, SI},	NULL},
{"subic.",	OP(13),		OP_MASK,     PPCCOM,	PPCNONE,	{RT, RA, NSI},	translate_subic},

{"li",		OP(14),		DRA_MASK,    PPCCOM,	PPCNONE,	{RT, SI},	translate_li},
{"lil",		OP(14),		DRA_MASK,    PWRCOM,	PPCNONE,	{RT, SI},	NULL},
{"addi",	OP(14),		OP_MASK,     PPCCOM,	PPCNONE,	{RT, RA0, SI},	translate_addi},
{"cal",		OP(14),		OP_MASK,     PWRCOM,	PPCNONE,	{RT, D, RA0},	NULL},
{"subi",	OP(14),		OP_MASK,     PPCCOM,	PPCNONE,	{RT, RA0, NSI},	translate_subi},
{"la",		OP(14),		OP_MASK,     PPCCOM,	PPCNONE,	{RT, D, RA0},	NULL},

{"lis",		OP(15),		DRA_MASK,    PPCCOM,	PPCNONE,	{RT, SISIGNOPT},	translate_lis},
{"liu",		OP(15),		DRA_MASK,    PWRCOM,	PPCNONE,	{RT, SISIGNOPT},	NULL},
{"addis",	OP(15),		OP_MASK,     PPCCOM,	PPCNONE,	{RT, RA0, SISIGNOPT},	translate_addis},
{"cau",		OP(15),		OP_MASK,     PWRCOM,	PPCNONE,	{RT, RA0, SISIGNOPT},	NULL},
{"subis",	OP(15),		OP_MASK,     PPCCOM,	PPCNONE,	{RT, RA0, NSI},	translate_subis},

{"bdnz-",    BBO(16,BODNZ,0,0),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDM},	NULL},
{"bdnz+",    BBO(16,BODNZ,0,0),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDP},	NULL},
{"bdnz",     BBO(16,BODNZ,0,0),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BD},	translate_bc},
{"bdn",      BBO(16,BODNZ,0,0),		BBOATBI_MASK,  PWRCOM,	 PPCNONE,	{BD},	NULL},
{"bdnzl-",   BBO(16,BODNZ,0,1),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDM},	NULL},
{"bdnzl+",   BBO(16,BODNZ,0,1),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDP},	NULL},
{"bdnzl",    BBO(16,BODNZ,0,1),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BD},	translate_bcl},
{"bdnl",     BBO(16,BODNZ,0,1),		BBOATBI_MASK,  PWRCOM,	 PPCNONE,	{BD},	translate_bcl},
{"bdnza-",   BBO(16,BODNZ,1,0),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDMA},	NULL},
{"bdnza+",   BBO(16,BODNZ,1,0),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDPA},	NULL},
{"bdnza",    BBO(16,BODNZ,1,0),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDA},	NULL},
{"bdna",     BBO(16,BODNZ,1,0),		BBOATBI_MASK,  PWRCOM,	 PPCNONE,	{BDA},	NULL},
{"bdnzla-",  BBO(16,BODNZ,1,1),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDMA},	NULL},
{"bdnzla+",  BBO(16,BODNZ,1,1),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDPA},	NULL},
{"bdnzla",   BBO(16,BODNZ,1,1),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDA},	NULL},
{"bdnla",    BBO(16,BODNZ,1,1),		BBOATBI_MASK,  PWRCOM,	 PPCNONE,	{BDA},	NULL},
{"bdz-",     BBO(16,BODZ,0,0),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDM},	NULL},
{"bdz+",     BBO(16,BODZ,0,0),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDP},	NULL},
{"bdz",      BBO(16,BODZ,0,0),		BBOATBI_MASK,  COM,	 PPCNONE,	{BD},	translate_bc},
{"bdzl-",    BBO(16,BODZ,0,1),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDM},	NULL},
{"bdzl+",    BBO(16,BODZ,0,1),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDP},	NULL},
{"bdzl",     BBO(16,BODZ,0,1),		BBOATBI_MASK,  COM,	 PPCNONE,	{BD},	translate_bcl},
{"bdza-",    BBO(16,BODZ,1,0),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDMA},	NULL},
{"bdza+",    BBO(16,BODZ,1,0),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDPA},	NULL},
{"bdza",     BBO(16,BODZ,1,0),		BBOATBI_MASK,  COM,	 PPCNONE,	{BDA},	NULL},
{"bdzla-",   BBO(16,BODZ,1,1),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDMA},	NULL},
{"bdzla+",   BBO(16,BODZ,1,1),		BBOATBI_MASK,  PPCCOM,	 PPCNONE,	{BDPA},	NULL},
{"bdzla",    BBO(16,BODZ,1,1),		BBOATBI_MASK,  COM,	 PPCNONE,	{BDA},	NULL},

{"bge-",     BBOCB(16,BOF,CBLT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bc},
{"bge+",     BBOCB(16,BOF,CBLT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bc},
{"bge",      BBOCB(16,BOF,CBLT,0,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bc},
{"bnl-",     BBOCB(16,BOF,CBLT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bc},
{"bnl+",     BBOCB(16,BOF,CBLT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bc},
{"bnl",      BBOCB(16,BOF,CBLT,0,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bc},
{"bgel-",    BBOCB(16,BOF,CBLT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bcl},
{"bgel+",    BBOCB(16,BOF,CBLT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bcl},
{"bgel",     BBOCB(16,BOF,CBLT,0,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bcl},
{"bnll-",    BBOCB(16,BOF,CBLT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bcl},
{"bnll+",    BBOCB(16,BOF,CBLT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bcl},
{"bnll",     BBOCB(16,BOF,CBLT,0,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bcl},
{"bgea-",    BBOCB(16,BOF,CBLT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bgea+",    BBOCB(16,BOF,CBLT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bgea",     BBOCB(16,BOF,CBLT,1,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"bnla-",    BBOCB(16,BOF,CBLT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bnla+",    BBOCB(16,BOF,CBLT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bnla",     BBOCB(16,BOF,CBLT,1,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"bgela-",   BBOCB(16,BOF,CBLT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bgela+",   BBOCB(16,BOF,CBLT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bgela",    BBOCB(16,BOF,CBLT,1,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"bnlla-",   BBOCB(16,BOF,CBLT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bnlla+",   BBOCB(16,BOF,CBLT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bnlla",    BBOCB(16,BOF,CBLT,1,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"ble-",     BBOCB(16,BOF,CBGT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bc},
{"ble+",     BBOCB(16,BOF,CBGT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bc},
{"ble",      BBOCB(16,BOF,CBGT,0,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bc},
{"bng-",     BBOCB(16,BOF,CBGT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bc},
{"bng+",     BBOCB(16,BOF,CBGT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bc},
{"bng",      BBOCB(16,BOF,CBGT,0,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bc},
{"blel-",    BBOCB(16,BOF,CBGT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bcl},
{"blel+",    BBOCB(16,BOF,CBGT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bcl},
{"blel",     BBOCB(16,BOF,CBGT,0,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bcl},
{"bngl-",    BBOCB(16,BOF,CBGT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bcl},
{"bngl+",    BBOCB(16,BOF,CBGT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bcl},
{"bngl",     BBOCB(16,BOF,CBGT,0,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bcl},
{"blea-",    BBOCB(16,BOF,CBGT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"blea+",    BBOCB(16,BOF,CBGT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"blea",     BBOCB(16,BOF,CBGT,1,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"bnga-",    BBOCB(16,BOF,CBGT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bnga+",    BBOCB(16,BOF,CBGT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bnga",     BBOCB(16,BOF,CBGT,1,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"blela-",   BBOCB(16,BOF,CBGT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"blela+",   BBOCB(16,BOF,CBGT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"blela",    BBOCB(16,BOF,CBGT,1,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"bngla-",   BBOCB(16,BOF,CBGT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bngla+",   BBOCB(16,BOF,CBGT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bngla",    BBOCB(16,BOF,CBGT,1,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"bne-",     BBOCB(16,BOF,CBEQ,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bc},
{"bne+",     BBOCB(16,BOF,CBEQ,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bc},
{"bne",      BBOCB(16,BOF,CBEQ,0,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bc},
{"bnel-",    BBOCB(16,BOF,CBEQ,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bcl},
{"bnel+",    BBOCB(16,BOF,CBEQ,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bcl},
{"bnel",     BBOCB(16,BOF,CBEQ,0,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bcl},
{"bnea-",    BBOCB(16,BOF,CBEQ,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bnea+",    BBOCB(16,BOF,CBEQ,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bnea",     BBOCB(16,BOF,CBEQ,1,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"bnela-",   BBOCB(16,BOF,CBEQ,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bnela+",   BBOCB(16,BOF,CBEQ,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bnela",    BBOCB(16,BOF,CBEQ,1,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"bns-",     BBOCB(16,BOF,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bc},
{"bns+",     BBOCB(16,BOF,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bc},
{"bns",      BBOCB(16,BOF,CBSO,0,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bc},
{"bnu-",     BBOCB(16,BOF,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bc},
{"bnu+",     BBOCB(16,BOF,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bc},
{"bnu",      BBOCB(16,BOF,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BD},	translate_bc},
{"bnsl-",    BBOCB(16,BOF,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bcl},
{"bnsl+",    BBOCB(16,BOF,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bcl},
{"bnsl",     BBOCB(16,BOF,CBSO,0,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bcl},
{"bnul-",    BBOCB(16,BOF,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bcl},
{"bnul+",    BBOCB(16,BOF,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bcl},
{"bnul",     BBOCB(16,BOF,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BD},	translate_bcl},
{"bnsa-",    BBOCB(16,BOF,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bnsa+",    BBOCB(16,BOF,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bnsa",     BBOCB(16,BOF,CBSO,1,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"bnua-",    BBOCB(16,BOF,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bnua+",    BBOCB(16,BOF,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bnua",     BBOCB(16,BOF,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDA},	NULL},
{"bnsla-",   BBOCB(16,BOF,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bnsla+",   BBOCB(16,BOF,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bnsla",    BBOCB(16,BOF,CBSO,1,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"bnula-",   BBOCB(16,BOF,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bnula+",   BBOCB(16,BOF,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bnula",    BBOCB(16,BOF,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDA},	NULL},

{"blt-",     BBOCB(16,BOT,CBLT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bc},
{"blt+",     BBOCB(16,BOT,CBLT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bc},
{"blt",      BBOCB(16,BOT,CBLT,0,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bc},
{"bltl-",    BBOCB(16,BOT,CBLT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bcl},
{"bltl+",    BBOCB(16,BOT,CBLT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bcl},
{"bltl",     BBOCB(16,BOT,CBLT,0,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bcl},
{"blta-",    BBOCB(16,BOT,CBLT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"blta+",    BBOCB(16,BOT,CBLT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"blta",     BBOCB(16,BOT,CBLT,1,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"bltla-",   BBOCB(16,BOT,CBLT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bltla+",   BBOCB(16,BOT,CBLT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bltla",    BBOCB(16,BOT,CBLT,1,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"bgt-",     BBOCB(16,BOT,CBGT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bc},
{"bgt+",     BBOCB(16,BOT,CBGT,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bc},
{"bgt",      BBOCB(16,BOT,CBGT,0,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bc},
{"bgtl-",    BBOCB(16,BOT,CBGT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bcl},
{"bgtl+",    BBOCB(16,BOT,CBGT,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bcl},
{"bgtl",     BBOCB(16,BOT,CBGT,0,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bcl},
{"bgta-",    BBOCB(16,BOT,CBGT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bgta+",    BBOCB(16,BOT,CBGT,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bgta",     BBOCB(16,BOT,CBGT,1,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"bgtla-",   BBOCB(16,BOT,CBGT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bgtla+",   BBOCB(16,BOT,CBGT,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bgtla",    BBOCB(16,BOT,CBGT,1,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"beq-",     BBOCB(16,BOT,CBEQ,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bc},
{"beq+",     BBOCB(16,BOT,CBEQ,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bc},
{"beq",      BBOCB(16,BOT,CBEQ,0,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bc},
{"beql-",    BBOCB(16,BOT,CBEQ,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bcl},
{"beql+",    BBOCB(16,BOT,CBEQ,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bcl},
{"beql",     BBOCB(16,BOT,CBEQ,0,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bcl},
{"beqa-",    BBOCB(16,BOT,CBEQ,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"beqa+",    BBOCB(16,BOT,CBEQ,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"beqa",     BBOCB(16,BOT,CBEQ,1,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"beqla-",   BBOCB(16,BOT,CBEQ,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"beqla+",   BBOCB(16,BOT,CBEQ,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"beqla",    BBOCB(16,BOT,CBEQ,1,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"bso-",     BBOCB(16,BOT,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bc},
{"bso+",     BBOCB(16,BOT,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bc},
{"bso",      BBOCB(16,BOT,CBSO,0,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bc},
{"bun-",     BBOCB(16,BOT,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bc},
{"bun+",     BBOCB(16,BOT,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bc},
{"bun",      BBOCB(16,BOT,CBSO,0,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BD},	translate_bc},
{"bsol-",    BBOCB(16,BOT,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bcl},
{"bsol+",    BBOCB(16,BOT,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bcl},
{"bsol",     BBOCB(16,BOT,CBSO,0,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BD},	translate_bcl},
{"bunl-",    BBOCB(16,BOT,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDM},	translate_bcl},
{"bunl+",    BBOCB(16,BOT,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDP},	translate_bcl},
{"bunl",     BBOCB(16,BOT,CBSO,0,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BD},	translate_bcl},
{"bsoa-",    BBOCB(16,BOT,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bsoa+",    BBOCB(16,BOT,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bsoa",     BBOCB(16,BOT,CBSO,1,0),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"buna-",    BBOCB(16,BOT,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"buna+",    BBOCB(16,BOT,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"buna",     BBOCB(16,BOT,CBSO,1,0),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDA},	NULL},
{"bsola-",   BBOCB(16,BOT,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bsola+",   BBOCB(16,BOT,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bsola",    BBOCB(16,BOT,CBSO,1,1),	BBOATCB_MASK,  COM,	 PPCNONE,	{CR, BDA},	NULL},
{"bunla-",   BBOCB(16,BOT,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDMA},	NULL},
{"bunla+",   BBOCB(16,BOT,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDPA},	NULL},
{"bunla",    BBOCB(16,BOT,CBSO,1,1),	BBOATCB_MASK,  PPCCOM,	 PPCNONE,	{CR, BDA},	NULL},

{"bdnzf-",   BBO(16,BODNZF,0,0),	BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDM},	NULL},
{"bdnzf+",   BBO(16,BODNZF,0,0),	BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDP},	NULL},
{"bdnzf",    BBO(16,BODNZF,0,0),	BBOY_MASK,     PPCCOM,	 PPCNONE,	{BI, BD},	NULL},
{"bdnzfl-",  BBO(16,BODNZF,0,1),	BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDM},	NULL},
{"bdnzfl+",  BBO(16,BODNZF,0,1),	BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDP},	NULL},
{"bdnzfl",   BBO(16,BODNZF,0,1),	BBOY_MASK,     PPCCOM,	 PPCNONE,	{BI, BD},	NULL},
{"bdnzfa-",  BBO(16,BODNZF,1,0),	BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDMA},	NULL},
{"bdnzfa+",  BBO(16,BODNZF,1,0),	BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDPA},	NULL},
{"bdnzfa",   BBO(16,BODNZF,1,0),	BBOY_MASK,     PPCCOM,	 PPCNONE,	{BI, BDA},	NULL},
{"bdnzfla-", BBO(16,BODNZF,1,1),	BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDMA},	NULL},
{"bdnzfla+", BBO(16,BODNZF,1,1),	BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDPA},	NULL},
{"bdnzfla",  BBO(16,BODNZF,1,1),	BBOY_MASK,     PPCCOM,	 PPCNONE,	{BI, BDA},	NULL},
{"bdzf-",    BBO(16,BODZF,0,0),		BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDM},	NULL},
{"bdzf+",    BBO(16,BODZF,0,0),		BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDP},	NULL},
{"bdzf",     BBO(16,BODZF,0,0),		BBOY_MASK,     PPCCOM,	 PPCNONE,	{BI, BD},	NULL},
{"bdzfl-",   BBO(16,BODZF,0,1),		BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDM},	NULL},
{"bdzfl+",   BBO(16,BODZF,0,1),		BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDP},	NULL},
{"bdzfl",    BBO(16,BODZF,0,1),		BBOY_MASK,     PPCCOM,	 PPCNONE,	{BI, BD},	NULL},
{"bdzfa-",   BBO(16,BODZF,1,0),		BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDMA},	NULL},
{"bdzfa+",   BBO(16,BODZF,1,0),		BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDPA},	NULL},
{"bdzfa",    BBO(16,BODZF,1,0),		BBOY_MASK,     PPCCOM,	 PPCNONE,	{BI, BDA},	NULL},
{"bdzfla-",  BBO(16,BODZF,1,1),		BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDMA},	NULL},
{"bdzfla+",  BBO(16,BODZF,1,1),		BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDPA},	NULL},
{"bdzfla",   BBO(16,BODZF,1,1),		BBOY_MASK,     PPCCOM,	 PPCNONE,	{BI, BDA},	NULL},

{"bf-",      BBO(16,BOF,0,0),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDM},	NULL},
{"bf+",      BBO(16,BOF,0,0),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDP},	NULL},
{"bf",	     BBO(16,BOF,0,0),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BD},	translate_bc},
{"bbf",      BBO(16,BOF,0,0),		BBOAT_MASK,    PWRCOM,	 PPCNONE,	{BI, BD},	NULL},
{"bfl-",     BBO(16,BOF,0,1),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDM},	NULL},
{"bfl+",     BBO(16,BOF,0,1),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDP},	NULL},
{"bfl",      BBO(16,BOF,0,1),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BD},	translate_bcl},
{"bbfl",     BBO(16,BOF,0,1),		BBOAT_MASK,    PWRCOM,	 PPCNONE,	{BI, BD},	NULL},
{"bfa-",     BBO(16,BOF,1,0),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDMA},	NULL},
{"bfa+",     BBO(16,BOF,1,0),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDPA},	NULL},
{"bfa",      BBO(16,BOF,1,0),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDA},	NULL},
{"bbfa",     BBO(16,BOF,1,0),		BBOAT_MASK,    PWRCOM,	 PPCNONE,	{BI, BDA},	NULL},
{"bfla-",    BBO(16,BOF,1,1),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDMA},	NULL},
{"bfla+",    BBO(16,BOF,1,1),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDPA},	NULL},
{"bfla",     BBO(16,BOF,1,1),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDA},	NULL},
{"bbfla",    BBO(16,BOF,1,1),		BBOAT_MASK,    PWRCOM,	 PPCNONE,	{BI, BDA},	NULL},

{"bdnzt-",   BBO(16,BODNZT,0,0),	BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDM},	NULL},
{"bdnzt+",   BBO(16,BODNZT,0,0),	BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDP},	NULL},
{"bdnzt",    BBO(16,BODNZT,0,0),	BBOY_MASK,     PPCCOM,	 PPCNONE,	{BI, BD},	NULL},
{"bdnztl-",  BBO(16,BODNZT,0,1),	BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDM},	NULL},
{"bdnztl+",  BBO(16,BODNZT,0,1),	BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDP},	NULL},
{"bdnztl",   BBO(16,BODNZT,0,1),	BBOY_MASK,     PPCCOM,	 PPCNONE,	{BI, BD},	NULL},
{"bdnzta-",  BBO(16,BODNZT,1,0),	BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDMA},	NULL},
{"bdnzta+",  BBO(16,BODNZT,1,0),	BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDPA},	NULL},
{"bdnzta",   BBO(16,BODNZT,1,0),	BBOY_MASK,     PPCCOM,	 PPCNONE,	{BI, BDA},	NULL},
{"bdnztla-", BBO(16,BODNZT,1,1),	BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDMA},	NULL},
{"bdnztla+", BBO(16,BODNZT,1,1),	BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDPA},	NULL},
{"bdnztla",  BBO(16,BODNZT,1,1),	BBOY_MASK,     PPCCOM,	 PPCNONE,	{BI, BDA},	NULL},
{"bdzt-",    BBO(16,BODZT,0,0),		BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDM},	NULL},
{"bdzt+",    BBO(16,BODZT,0,0),		BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDP},	NULL},
{"bdzt",     BBO(16,BODZT,0,0),		BBOY_MASK,     PPCCOM,	 PPCNONE,	{BI, BD},	NULL},
{"bdztl-",   BBO(16,BODZT,0,1),		BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDM},	NULL},
{"bdztl+",   BBO(16,BODZT,0,1),		BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDP},	NULL},
{"bdztl",    BBO(16,BODZT,0,1),		BBOY_MASK,     PPCCOM,	 PPCNONE,	{BI, BD},	NULL},
{"bdzta-",   BBO(16,BODZT,1,0),		BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDMA},	NULL},
{"bdzta+",   BBO(16,BODZT,1,0),		BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDPA},	NULL},
{"bdzta",    BBO(16,BODZT,1,0),		BBOY_MASK,     PPCCOM,	 PPCNONE,	{BI, BDA},	NULL},
{"bdztla-",  BBO(16,BODZT,1,1),		BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDMA},	NULL},
{"bdztla+",  BBO(16,BODZT,1,1),		BBOY_MASK,     PPCCOM,   ISA_V2,	{BI, BDPA},	NULL},
{"bdztla",   BBO(16,BODZT,1,1),		BBOY_MASK,     PPCCOM,	 PPCNONE,	{BI, BDA},	NULL},

{"bt-",      BBO(16,BOT,0,0),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDM},	NULL},
{"bt+",      BBO(16,BOT,0,0),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDP},	NULL},
{"bt",	     BBO(16,BOT,0,0),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BD},	translate_bc},
{"bbt",      BBO(16,BOT,0,0),		BBOAT_MASK,    PWRCOM,	 PPCNONE,	{BI, BD},	NULL},
{"btl-",     BBO(16,BOT,0,1),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDM},	NULL},
{"btl+",     BBO(16,BOT,0,1),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDP},	NULL},
{"btl",      BBO(16,BOT,0,1),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BD},	translate_bcl},
{"bbtl",     BBO(16,BOT,0,1),		BBOAT_MASK,    PWRCOM,	 PPCNONE,	{BI, BD},	NULL},
{"bta-",     BBO(16,BOT,1,0),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDMA},	NULL},
{"bta+",     BBO(16,BOT,1,0),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDPA},	NULL},
{"bta",      BBO(16,BOT,1,0),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDA},	NULL},
{"bbta",     BBO(16,BOT,1,0),		BBOAT_MASK,    PWRCOM,	 PPCNONE,	{BI, BDA},	NULL},
{"btla-",    BBO(16,BOT,1,1),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDMA},	NULL},
{"btla+",    BBO(16,BOT,1,1),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDPA},	NULL},
{"btla",     BBO(16,BOT,1,1),		BBOAT_MASK,    PPCCOM,	 PPCNONE,	{BI, BDA},	NULL},
{"bbtla",    BBO(16,BOT,1,1),		BBOAT_MASK,    PWRCOM,	 PPCNONE,	{BI, BDA},	NULL},

{"bc-",		B(16,0,0),	B_MASK,      PPCCOM,	PPCNONE,	{BOE, BI, BDM},	translate_bc},
{"bc+",		B(16,0,0),	B_MASK,      PPCCOM,	PPCNONE,	{BOE, BI, BDP},	translate_bc},
{"bc",		B(16,0,0),	B_MASK,      COM,	PPCNONE,	{BO, BI, BD},	translate_bc},
{"bcl-",	B(16,0,1),	B_MASK,      PPCCOM,	PPCNONE,	{BOE, BI, BDM},	translate_bcl},
{"bcl+",	B(16,0,1),	B_MASK,      PPCCOM,	PPCNONE,	{BOE, BI, BDP},	translate_bcl},
{"bcl",		B(16,0,1),	B_MASK,      COM,	PPCNONE,	{BO, BI, BD},	translate_bcl},
{"bca-",	B(16,1,0),	B_MASK,      PPCCOM,	PPCNONE,	{BOE, BI, BDMA},	NULL},
{"bca+",	B(16,1,0),	B_MASK,      PPCCOM,	PPCNONE,	{BOE, BI, BDPA},	NULL},
{"bca",		B(16,1,0),	B_MASK,      COM,	PPCNONE,	{BO, BI, BDA},	NULL},
{"bcla-",	B(16,1,1),	B_MASK,      PPCCOM,	PPCNONE,	{BOE, BI, BDMA},	NULL},
{"bcla+",	B(16,1,1),	B_MASK,      PPCCOM,	PPCNONE,	{BOE, BI, BDPA},	NULL},
{"bcla",	B(16,1,1),	B_MASK,      COM,	PPCNONE,	{BO, BI, BDA},	NULL},

{"svc",		SC(17,0,0),	SC_MASK,     POWER,	PPCNONE,	{SVC_LEV, FL1, FL2},	NULL},
{"svcl",	SC(17,0,1),	SC_MASK,     POWER,	PPCNONE,	{SVC_LEV, FL1, FL2},	NULL},
{"sc",		SC(17,1,0),	SC_MASK,     PPC,	PPCNONE,	{LEV},	translate_sc},
{"svca",	SC(17,1,0),	SC_MASK,     PWRCOM,	PPCNONE,	{SV},	NULL},
{"svcla",	SC(17,1,1),	SC_MASK,     POWER,	PPCNONE,	{SV},	NULL},

{"b",		B(18,0,0),	B_MASK,      COM,	PPCNONE,	{LI},	translate_b},
{"bl",		B(18,0,1),	B_MASK,      COM,	PPCNONE,	{LI},	translate_b},
{"ba",		B(18,1,0),	B_MASK,      COM,	PPCNONE,	{LIA},	NULL},
{"bla",		B(18,1,1),	B_MASK,      COM,	PPCNONE,	{LIA},	NULL},

{"mcrf",      XL(19,0), XLBB_MASK|(3<<21)|(3<<16), COM,	PPCNONE,	{BF, BFA},	translate_mcrf},

{"bdnzlr",   XLO(19,BODNZ,16,0),	XLBOBIBB_MASK, PPCCOM,	 PPCNONE,	{UNUSED},	NULL},
{"bdnzlr-",  XLO(19,BODNZ,16,0),	XLBOBIBB_MASK, PPCCOM,   ISA_V2,	{UNUSED},	NULL},
{"bdnzlrl",  XLO(19,BODNZ,16,1),	XLBOBIBB_MASK, PPCCOM,	 PPCNONE,	{UNUSED},	NULL},
{"bdnzlrl-", XLO(19,BODNZ,16,1),	XLBOBIBB_MASK, PPCCOM,   ISA_V2,	{UNUSED},	NULL},
{"bdnzlr+",  XLO(19,BODNZP,16,0),	XLBOBIBB_MASK, PPCCOM,   ISA_V2,	{UNUSED},	NULL},
{"bdnzlrl+", XLO(19,BODNZP,16,1),	XLBOBIBB_MASK, PPCCOM,   ISA_V2,	{UNUSED},	NULL},
{"bdzlr",    XLO(19,BODZ,16,0),		XLBOBIBB_MASK, PPCCOM,	 PPCNONE,	{UNUSED},	NULL},
{"bdzlr-",   XLO(19,BODZ,16,0),		XLBOBIBB_MASK, PPCCOM,   ISA_V2,	{UNUSED},	NULL},
{"bdzlrl",   XLO(19,BODZ,16,1),		XLBOBIBB_MASK, PPCCOM,	 PPCNONE,	{UNUSED},	NULL},
{"bdzlrl-",  XLO(19,BODZ,16,1),		XLBOBIBB_MASK, PPCCOM,   ISA_V2,	{UNUSED},	NULL},
{"bdzlr+",   XLO(19,BODZP,16,0),	XLBOBIBB_MASK, PPCCOM,   ISA_V2,	{UNUSED},	NULL},
{"bdzlrl+",  XLO(19,BODZP,16,1),	XLBOBIBB_MASK, PPCCOM,   ISA_V2,	{UNUSED},	NULL},
{"blr",      XLO(19,BOU,16,0),		XLBOBIBB_MASK, PPCCOM,	 PPCNONE,	{UNUSED},	translate_blr},
{"br",	     XLO(19,BOU,16,0),		XLBOBIBB_MASK, PWRCOM,	 PPCNONE,	{UNUSED},	NULL},
{"blrl",     XLO(19,BOU,16,1),		XLBOBIBB_MASK, PPCCOM,	 PPCNONE,	{UNUSED},	NULL},
{"brl",      XLO(19,BOU,16,1),		XLBOBIBB_MASK, PWRCOM,	 PPCNONE,	{UNUSED},	translate_blr},
{"bdnzlr-",  XLO(19,BODNZM4,16,0),	XLBOBIBB_MASK, ISA_V2,	 PPCNONE,	{UNUSED},	NULL},
{"bdnzlrl-", XLO(19,BODNZM4,16,1),	XLBOBIBB_MASK, ISA_V2,	 PPCNONE,	{UNUSED},	NULL},
{"bdnzlr+",  XLO(19,BODNZP4,16,0),	XLBOBIBB_MASK, ISA_V2,	 PPCNONE,	{UNUSED},	NULL},
{"bdnzlrl+", XLO(19,BODNZP4,16,1),	XLBOBIBB_MASK, ISA_V2,	 PPCNONE,	{UNUSED},	NULL},
{"bdzlr-",   XLO(19,BODZM4,16,0),	XLBOBIBB_MASK, ISA_V2,	 PPCNONE,	{UNUSED},	NULL},
{"bdzlrl-",  XLO(19,BODZM4,16,1),	XLBOBIBB_MASK, ISA_V2,	 PPCNONE,	{UNUSED},	NULL},
{"bdzlr+",   XLO(19,BODZP4,16,0),	XLBOBIBB_MASK, ISA_V2,	 PPCNONE,	{UNUSED},	NULL},
{"bdzlrl+",  XLO(19,BODZP4,16,1),	XLBOBIBB_MASK, ISA_V2,	 PPCNONE,	{UNUSED},	NULL},

{"bgelr",    XLOCB(19,BOF,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bgelr-",   XLOCB(19,BOF,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bger",     XLOCB(19,BOF,CBLT,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"bnllr",    XLOCB(19,BOF,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnllr-",   XLOCB(19,BOF,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnlr",     XLOCB(19,BOF,CBLT,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"bgelrl",   XLOCB(19,BOF,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bgelrl-",  XLOCB(19,BOF,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bgerl",    XLOCB(19,BOF,CBLT,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"bnllrl",   XLOCB(19,BOF,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnllrl-",  XLOCB(19,BOF,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnlrl",    XLOCB(19,BOF,CBLT,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"blelr",    XLOCB(19,BOF,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"blelr-",   XLOCB(19,BOF,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bler",     XLOCB(19,BOF,CBGT,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"bnglr",    XLOCB(19,BOF,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnglr-",   XLOCB(19,BOF,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bngr",     XLOCB(19,BOF,CBGT,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"blelrl",   XLOCB(19,BOF,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"blelrl-",  XLOCB(19,BOF,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"blerl",    XLOCB(19,BOF,CBGT,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"bnglrl",   XLOCB(19,BOF,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnglrl-",  XLOCB(19,BOF,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bngrl",    XLOCB(19,BOF,CBGT,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"bnelr",    XLOCB(19,BOF,CBEQ,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnelr-",   XLOCB(19,BOF,CBEQ,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bner",     XLOCB(19,BOF,CBEQ,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"bnelrl",   XLOCB(19,BOF,CBEQ,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnelrl-",  XLOCB(19,BOF,CBEQ,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnerl",    XLOCB(19,BOF,CBEQ,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"bnslr",    XLOCB(19,BOF,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnslr-",   XLOCB(19,BOF,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnsr",     XLOCB(19,BOF,CBSO,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"bnulr",    XLOCB(19,BOF,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnulr-",   XLOCB(19,BOF,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnslrl",   XLOCB(19,BOF,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnslrl-",  XLOCB(19,BOF,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnsrl",    XLOCB(19,BOF,CBSO,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"bnulrl",   XLOCB(19,BOF,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnulrl-",  XLOCB(19,BOF,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bgelr+",   XLOCB(19,BOFP,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnllr+",   XLOCB(19,BOFP,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bgelrl+",  XLOCB(19,BOFP,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnllrl+",  XLOCB(19,BOFP,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"blelr+",   XLOCB(19,BOFP,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnglr+",   XLOCB(19,BOFP,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"blelrl+",  XLOCB(19,BOFP,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnglrl+",  XLOCB(19,BOFP,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnelr+",   XLOCB(19,BOFP,CBEQ,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnelrl+",  XLOCB(19,BOFP,CBEQ,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnslr+",   XLOCB(19,BOFP,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnulr+",   XLOCB(19,BOFP,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnslrl+",  XLOCB(19,BOFP,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnulrl+",  XLOCB(19,BOFP,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bgelr-",   XLOCB(19,BOFM4,CBLT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnllr-",   XLOCB(19,BOFM4,CBLT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bgelrl-",  XLOCB(19,BOFM4,CBLT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnllrl-",  XLOCB(19,BOFM4,CBLT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"blelr-",   XLOCB(19,BOFM4,CBGT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnglr-",   XLOCB(19,BOFM4,CBGT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"blelrl-",  XLOCB(19,BOFM4,CBGT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnglrl-",  XLOCB(19,BOFM4,CBGT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnelr-",   XLOCB(19,BOFM4,CBEQ,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnelrl-",  XLOCB(19,BOFM4,CBEQ,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnslr-",   XLOCB(19,BOFM4,CBSO,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnulr-",   XLOCB(19,BOFM4,CBSO,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnslrl-",  XLOCB(19,BOFM4,CBSO,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnulrl-",  XLOCB(19,BOFM4,CBSO,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bgelr+",   XLOCB(19,BOFP4,CBLT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnllr+",   XLOCB(19,BOFP4,CBLT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bgelrl+",  XLOCB(19,BOFP4,CBLT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnllrl+",  XLOCB(19,BOFP4,CBLT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"blelr+",   XLOCB(19,BOFP4,CBGT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnglr+",   XLOCB(19,BOFP4,CBGT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"blelrl+",  XLOCB(19,BOFP4,CBGT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnglrl+",  XLOCB(19,BOFP4,CBGT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnelr+",   XLOCB(19,BOFP4,CBEQ,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnelrl+",  XLOCB(19,BOFP4,CBEQ,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnslr+",   XLOCB(19,BOFP4,CBSO,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnulr+",   XLOCB(19,BOFP4,CBSO,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnslrl+",  XLOCB(19,BOFP4,CBSO,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnulrl+",  XLOCB(19,BOFP4,CBSO,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bltlr",    XLOCB(19,BOT,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bltlr-",   XLOCB(19,BOT,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bltr",     XLOCB(19,BOT,CBLT,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"bltlrl",   XLOCB(19,BOT,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bltlrl-",  XLOCB(19,BOT,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bltrl",    XLOCB(19,BOT,CBLT,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"bgtlr",    XLOCB(19,BOT,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bgtlr-",   XLOCB(19,BOT,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bgtr",     XLOCB(19,BOT,CBGT,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"bgtlrl",   XLOCB(19,BOT,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bgtlrl-",  XLOCB(19,BOT,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bgtrl",    XLOCB(19,BOT,CBGT,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"beqlr",    XLOCB(19,BOT,CBEQ,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"beqlr-",   XLOCB(19,BOT,CBEQ,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"beqr",     XLOCB(19,BOT,CBEQ,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"beqlrl",   XLOCB(19,BOT,CBEQ,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"beqlrl-",  XLOCB(19,BOT,CBEQ,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"beqrl",    XLOCB(19,BOT,CBEQ,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"bsolr",    XLOCB(19,BOT,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bsolr-",   XLOCB(19,BOT,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bsor",     XLOCB(19,BOT,CBSO,16,0),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"bunlr",    XLOCB(19,BOT,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bunlr-",   XLOCB(19,BOT,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bsolrl",   XLOCB(19,BOT,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bsolrl-",  XLOCB(19,BOT,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bsorl",    XLOCB(19,BOT,CBSO,16,1),	XLBOCBBB_MASK, PWRCOM,	 PPCNONE,	{CR},	NULL},
{"bunlrl",   XLOCB(19,BOT,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bunlrl-",  XLOCB(19,BOT,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bltlr+",   XLOCB(19,BOTP,CBLT,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bltlrl+",  XLOCB(19,BOTP,CBLT,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bgtlr+",   XLOCB(19,BOTP,CBGT,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bgtlrl+",  XLOCB(19,BOTP,CBGT,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"beqlr+",   XLOCB(19,BOTP,CBEQ,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"beqlrl+",  XLOCB(19,BOTP,CBEQ,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bsolr+",   XLOCB(19,BOTP,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bunlr+",   XLOCB(19,BOTP,CBSO,16,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bsolrl+",  XLOCB(19,BOTP,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bunlrl+",  XLOCB(19,BOTP,CBSO,16,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bltlr-",   XLOCB(19,BOTM4,CBLT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bltlrl-",  XLOCB(19,BOTM4,CBLT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bgtlr-",   XLOCB(19,BOTM4,CBGT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bgtlrl-",  XLOCB(19,BOTM4,CBGT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"beqlr-",   XLOCB(19,BOTM4,CBEQ,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"beqlrl-",  XLOCB(19,BOTM4,CBEQ,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bsolr-",   XLOCB(19,BOTM4,CBSO,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bunlr-",   XLOCB(19,BOTM4,CBSO,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bsolrl-",  XLOCB(19,BOTM4,CBSO,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bunlrl-",  XLOCB(19,BOTM4,CBSO,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bltlr+",   XLOCB(19,BOTP4,CBLT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bltlrl+",  XLOCB(19,BOTP4,CBLT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bgtlr+",   XLOCB(19,BOTP4,CBGT,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bgtlrl+",  XLOCB(19,BOTP4,CBGT,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"beqlr+",   XLOCB(19,BOTP4,CBEQ,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"beqlrl+",  XLOCB(19,BOTP4,CBEQ,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bsolr+",   XLOCB(19,BOTP4,CBSO,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bunlr+",   XLOCB(19,BOTP4,CBSO,16,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bsolrl+",  XLOCB(19,BOTP4,CBSO,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bunlrl+",  XLOCB(19,BOTP4,CBSO,16,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},

{"bdnzflr",  XLO(19,BODNZF,16,0),	XLBOBB_MASK,   PPCCOM,	 PPCNONE,	{BI},	NULL},
{"bdnzflr-", XLO(19,BODNZF,16,0),	XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bdnzflrl", XLO(19,BODNZF,16,1),	XLBOBB_MASK,   PPCCOM,	 PPCNONE,	{BI},	NULL},
{"bdnzflrl-",XLO(19,BODNZF,16,1),	XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bdnzflr+", XLO(19,BODNZFP,16,0),	XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bdnzflrl+",XLO(19,BODNZFP,16,1),	XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bdzflr",   XLO(19,BODZF,16,0),	XLBOBB_MASK,   PPCCOM,	 PPCNONE,	{BI},	NULL},
{"bdzflr-",  XLO(19,BODZF,16,0),	XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bdzflrl",  XLO(19,BODZF,16,1),	XLBOBB_MASK,   PPCCOM,	 PPCNONE,	{BI},	NULL},
{"bdzflrl-", XLO(19,BODZF,16,1),	XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bdzflr+",  XLO(19,BODZFP,16,0),	XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bdzflrl+", XLO(19,BODZFP,16,1),	XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bflr",     XLO(19,BOF,16,0),		XLBOBB_MASK,   PPCCOM,	 PPCNONE,	{BI},	NULL},
{"bflr-",    XLO(19,BOF,16,0),		XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bbfr",     XLO(19,BOF,16,0),		XLBOBB_MASK,   PWRCOM,	 PPCNONE,	{BI},	NULL},
{"bflrl",    XLO(19,BOF,16,1),		XLBOBB_MASK,   PPCCOM,	 PPCNONE,	{BI},	NULL},
{"bflrl-",   XLO(19,BOF,16,1),		XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bbfrl",    XLO(19,BOF,16,1),		XLBOBB_MASK,   PWRCOM,	 PPCNONE,	{BI},	NULL},
{"bflr+",    XLO(19,BOFP,16,0),		XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bflrl+",   XLO(19,BOFP,16,1),		XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bflr-",    XLO(19,BOFM4,16,0),	XLBOBB_MASK,   ISA_V2,	 PPCNONE,	{BI},	NULL},
{"bflrl-",   XLO(19,BOFM4,16,1),	XLBOBB_MASK,   ISA_V2,	 PPCNONE,	{BI},	NULL},
{"bflr+",    XLO(19,BOFP4,16,0),	XLBOBB_MASK,   ISA_V2,	 PPCNONE,	{BI},	NULL},
{"bflrl+",   XLO(19,BOFP4,16,1),	XLBOBB_MASK,   ISA_V2,	 PPCNONE,	{BI},	NULL},
{"bdnztlr",  XLO(19,BODNZT,16,0),	XLBOBB_MASK,   PPCCOM,	 PPCNONE,	{BI},	NULL},
{"bdnztlr-", XLO(19,BODNZT,16,0),	XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bdnztlrl", XLO(19,BODNZT,16,1),	XLBOBB_MASK,   PPCCOM,	 PPCNONE,	{BI},	NULL},
{"bdnztlrl-",XLO(19,BODNZT,16,1),	XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bdnztlr+", XLO(19,BODNZTP,16,0),	XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bdnztlrl+",XLO(19,BODNZTP,16,1),	XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bdztlr",   XLO(19,BODZT,16,0),	XLBOBB_MASK,   PPCCOM,	 PPCNONE,	{BI},	NULL},
{"bdztlr-",  XLO(19,BODZT,16,0),	XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bdztlrl",  XLO(19,BODZT,16,1),	XLBOBB_MASK,   PPCCOM,	 PPCNONE,	{BI},	NULL},
{"bdztlrl-", XLO(19,BODZT,16,1),	XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bdztlr+",  XLO(19,BODZTP,16,0),	XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bdztlrl+", XLO(19,BODZTP,16,1),	XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"btlr",     XLO(19,BOT,16,0),		XLBOBB_MASK,   PPCCOM,	 PPCNONE,	{BI},	NULL},
{"btlr-",    XLO(19,BOT,16,0),		XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bbtr",     XLO(19,BOT,16,0),		XLBOBB_MASK,   PWRCOM,	 PPCNONE,	{BI},	NULL},
{"btlrl",    XLO(19,BOT,16,1),		XLBOBB_MASK,   PPCCOM,	 PPCNONE,	{BI},	NULL},
{"btlrl-",   XLO(19,BOT,16,1),		XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bbtrl",    XLO(19,BOT,16,1),		XLBOBB_MASK,   PWRCOM,	 PPCNONE,	{BI},	NULL},
{"btlr+",    XLO(19,BOTP,16,0),		XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"btlrl+",   XLO(19,BOTP,16,1),		XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"btlr-",    XLO(19,BOTM4,16,0),	XLBOBB_MASK,   ISA_V2,	 PPCNONE,	{BI},	NULL},
{"btlrl-",   XLO(19,BOTM4,16,1),	XLBOBB_MASK,   ISA_V2,	 PPCNONE,	{BI},	NULL},
{"btlr+",    XLO(19,BOTP4,16,0),	XLBOBB_MASK,   ISA_V2,	 PPCNONE,	{BI},	NULL},
{"btlrl+",   XLO(19,BOTP4,16,1),	XLBOBB_MASK,   ISA_V2,	 PPCNONE,	{BI},	NULL},

{"bclr-",    XLYLK(19,16,0,0),		XLYBB_MASK,    PPCCOM,	 PPCNONE,	{BOE, BI},	NULL},
{"bclrl-",   XLYLK(19,16,0,1),		XLYBB_MASK,    PPCCOM,	 PPCNONE,	{BOE, BI},	NULL},
{"bclr+",    XLYLK(19,16,1,0),		XLYBB_MASK,    PPCCOM,	 PPCNONE,	{BOE, BI},	NULL},
{"bclrl+",   XLYLK(19,16,1,1),		XLYBB_MASK,    PPCCOM,	 PPCNONE,	{BOE, BI},	NULL},
{"bclr",     XLLK(19,16,0),		XLBH_MASK,     PPCCOM,	 PPCNONE,	{BO, BI, BH},	NULL},
{"bcr",      XLLK(19,16,0),		XLBB_MASK,     PWRCOM,	 PPCNONE,	{BO, BI},	NULL},
{"bclrl",    XLLK(19,16,1),		XLBH_MASK,     PPCCOM,	 PPCNONE,	{BO, BI, BH},	NULL},
{"bcrl",     XLLK(19,16,1),		XLBB_MASK,     PWRCOM,	 PPCNONE,	{BO, BI},	NULL},

{"rfid",	XL(19,18),	0xffffffff,  PPC64,	PPCNONE,	{UNUSED},	NULL},

{"crnot",	XL(19,33),	XL_MASK,     PPCCOM,	PPCNONE,	{BT, BA, BBA},	translate_crxxx},
{"crnor",	XL(19,33),	XL_MASK,     COM,	PPCNONE,	{BT, BA, BB},	translate_crxxx},
{"rfmci",	X(19,38),   0xffffffff, PPCRFMCI|PPCA2|PPC476, PPCNONE,	{UNUSED},	translate_rfmci},

{"rfdi",	XL(19,39),	0xffffffff,  E500MC,	PPCNONE,	{UNUSED},	translate_rfdi},
{"rfi",		XL(19,50),	0xffffffff,  COM,	PPCNONE,	{UNUSED},	translate_rfi},
{"rfci",	XL(19,51), 0xffffffff, PPC403|BOOKE|PPCE300|PPCA2|PPC476, PPCNONE, {UNUSED},	translate_rfci},

{"rfsvc",	XL(19,82),	0xffffffff,  POWER,	PPCNONE,	{UNUSED},	NULL},

{"rfgi",	XL(19,102),   0xffffffff, E500MC|PPCA2,	PPCNONE,	{UNUSED},	NULL},

{"crandc",	XL(19,129),	XL_MASK,     COM,	PPCNONE,	{BT, BA, BB},	translate_crxxx},

{"rfebb",	XL(19,146),	XLS_MASK,    POWER8,	PPCNONE,	{SXL},	NULL},

{"isync",	XL(19,150),	0xffffffff,  PPCCOM,	PPCNONE,	{UNUSED},	translate_isync},
{"ics",		XL(19,150),	0xffffffff,  PWRCOM,	PPCNONE,	{UNUSED},	NULL},

{"crclr",	XL(19,193),	XL_MASK,     PPCCOM,	PPCNONE,	{BT, BAT, BBA},	translate_crxxx},
{"crxor",	XL(19,193),	XL_MASK,     COM,	PPCNONE,	{BT, BA, BB},	translate_crxxx},

{"dnh",		X(19,198),	X_MASK,      E500MC,	PPCNONE,	{DUI, DUIS},	NULL},

{"crnand",	XL(19,225),	XL_MASK,     COM,	PPCNONE,	{BT, BA, BB},	translate_crxxx},

{"crand",	XL(19,257),	XL_MASK,     COM,	PPCNONE,	{BT, BA, BB},	translate_crxxx},

{"hrfid",	XL(19,274),	0xffffffff, POWER5|CELL, PPC476,	{UNUSED},	NULL},

{"crset",	XL(19,289),	XL_MASK,     PPCCOM,	PPCNONE,	{BT, BAT, BBA},	translate_crxxx},
{"creqv",	XL(19,289),	XL_MASK,     COM,	PPCNONE,	{BT, BA, BB},	translate_crxxx},

{"doze",	XL(19,402),	0xffffffff,  POWER6,	PPCNONE,	{UNUSED},	NULL},

{"crorc",	XL(19,417),	XL_MASK,     COM,	PPCNONE,	{BT, BA, BB},	translate_crxxx},

{"nap",		XL(19,434),	0xffffffff,  POWER6,	PPCNONE,	{UNUSED},	NULL},

{"crmove",	XL(19,449),	XL_MASK,     PPCCOM,	PPCNONE,	{BT, BA, BBA},	translate_crxxx},
{"cror",	XL(19,449),	XL_MASK,     COM,	PPCNONE,	{BT, BA, BB},	translate_crxxx},

{"sleep",	XL(19,466),	0xffffffff,  POWER6,	PPCNONE,	{UNUSED},	NULL},
{"rvwinkle",	XL(19,498),	0xffffffff,  POWER6,	PPCNONE,	{UNUSED},	NULL},

{"bctr",    XLO(19,BOU,528,0),		XLBOBIBB_MASK, COM,	 PPCNONE,	{UNUSED},	translate_bctr},
{"bctrl",   XLO(19,BOU,528,1),		XLBOBIBB_MASK, COM,	 PPCNONE,	{UNUSED},	translate_bctr},

{"bgectr",  XLOCB(19,BOF,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bgectr-", XLOCB(19,BOF,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnlctr",  XLOCB(19,BOF,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnlctr-", XLOCB(19,BOF,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bgectrl", XLOCB(19,BOF,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bgectrl-",XLOCB(19,BOF,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnlctrl", XLOCB(19,BOF,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnlctrl-",XLOCB(19,BOF,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"blectr",  XLOCB(19,BOF,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"blectr-", XLOCB(19,BOF,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bngctr",  XLOCB(19,BOF,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bngctr-", XLOCB(19,BOF,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"blectrl", XLOCB(19,BOF,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"blectrl-",XLOCB(19,BOF,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bngctrl", XLOCB(19,BOF,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bngctrl-",XLOCB(19,BOF,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnectr",  XLOCB(19,BOF,CBEQ,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnectr-", XLOCB(19,BOF,CBEQ,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnectrl", XLOCB(19,BOF,CBEQ,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnectrl-",XLOCB(19,BOF,CBEQ,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnsctr",  XLOCB(19,BOF,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnsctr-", XLOCB(19,BOF,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnuctr",  XLOCB(19,BOF,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnuctr-", XLOCB(19,BOF,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnsctrl", XLOCB(19,BOF,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnsctrl-",XLOCB(19,BOF,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnuctrl", XLOCB(19,BOF,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bnuctrl-",XLOCB(19,BOF,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bgectr+", XLOCB(19,BOFP,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnlctr+", XLOCB(19,BOFP,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bgectrl+",XLOCB(19,BOFP,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnlctrl+",XLOCB(19,BOFP,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"blectr+", XLOCB(19,BOFP,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bngctr+", XLOCB(19,BOFP,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"blectrl+",XLOCB(19,BOFP,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bngctrl+",XLOCB(19,BOFP,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnectr+", XLOCB(19,BOFP,CBEQ,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnectrl+",XLOCB(19,BOFP,CBEQ,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnsctr+", XLOCB(19,BOFP,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnuctr+", XLOCB(19,BOFP,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnsctrl+",XLOCB(19,BOFP,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bnuctrl+",XLOCB(19,BOFP,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bgectr-", XLOCB(19,BOFM4,CBLT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnlctr-", XLOCB(19,BOFM4,CBLT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bgectrl-",XLOCB(19,BOFM4,CBLT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnlctrl-",XLOCB(19,BOFM4,CBLT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"blectr-", XLOCB(19,BOFM4,CBGT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bngctr-", XLOCB(19,BOFM4,CBGT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"blectrl-",XLOCB(19,BOFM4,CBGT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bngctrl-",XLOCB(19,BOFM4,CBGT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnectr-", XLOCB(19,BOFM4,CBEQ,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnectrl-",XLOCB(19,BOFM4,CBEQ,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnsctr-", XLOCB(19,BOFM4,CBSO,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnuctr-", XLOCB(19,BOFM4,CBSO,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnsctrl-",XLOCB(19,BOFM4,CBSO,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnuctrl-",XLOCB(19,BOFM4,CBSO,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bgectr+", XLOCB(19,BOFP4,CBLT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnlctr+", XLOCB(19,BOFP4,CBLT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bgectrl+",XLOCB(19,BOFP4,CBLT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnlctrl+",XLOCB(19,BOFP4,CBLT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"blectr+", XLOCB(19,BOFP4,CBGT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bngctr+", XLOCB(19,BOFP4,CBGT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"blectrl+",XLOCB(19,BOFP4,CBGT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bngctrl+",XLOCB(19,BOFP4,CBGT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnectr+", XLOCB(19,BOFP4,CBEQ,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnectrl+",XLOCB(19,BOFP4,CBEQ,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnsctr+", XLOCB(19,BOFP4,CBSO,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnuctr+", XLOCB(19,BOFP4,CBSO,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnsctrl+",XLOCB(19,BOFP4,CBSO,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bnuctrl+",XLOCB(19,BOFP4,CBSO,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bltctr",  XLOCB(19,BOT,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bltctr-", XLOCB(19,BOT,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bltctrl", XLOCB(19,BOT,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bltctrl-",XLOCB(19,BOT,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bgtctr",  XLOCB(19,BOT,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bgtctr-", XLOCB(19,BOT,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bgtctrl", XLOCB(19,BOT,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bgtctrl-",XLOCB(19,BOT,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"beqctr",  XLOCB(19,BOT,CBEQ,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"beqctr-", XLOCB(19,BOT,CBEQ,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"beqctrl", XLOCB(19,BOT,CBEQ,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"beqctrl-",XLOCB(19,BOT,CBEQ,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bsoctr",  XLOCB(19,BOT,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bsoctr-", XLOCB(19,BOT,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bunctr",  XLOCB(19,BOT,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bunctr-", XLOCB(19,BOT,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bsoctrl", XLOCB(19,BOT,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bsoctrl-",XLOCB(19,BOT,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bunctrl", XLOCB(19,BOT,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,	 PPCNONE,	{CR},	NULL},
{"bunctrl-",XLOCB(19,BOT,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bltctr+", XLOCB(19,BOTP,CBLT,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bltctrl+",XLOCB(19,BOTP,CBLT,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bgtctr+", XLOCB(19,BOTP,CBGT,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bgtctrl+",XLOCB(19,BOTP,CBGT,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"beqctr+", XLOCB(19,BOTP,CBEQ,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"beqctrl+",XLOCB(19,BOTP,CBEQ,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bsoctr+", XLOCB(19,BOTP,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bunctr+", XLOCB(19,BOTP,CBSO,528,0),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bsoctrl+",XLOCB(19,BOTP,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bunctrl+",XLOCB(19,BOTP,CBSO,528,1),	XLBOCBBB_MASK, PPCCOM,   ISA_V2,	{CR},	NULL},
{"bltctr-", XLOCB(19,BOTM4,CBLT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bltctrl-",XLOCB(19,BOTM4,CBLT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bgtctr-", XLOCB(19,BOTM4,CBGT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bgtctrl-",XLOCB(19,BOTM4,CBGT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"beqctr-", XLOCB(19,BOTM4,CBEQ,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"beqctrl-",XLOCB(19,BOTM4,CBEQ,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bsoctr-", XLOCB(19,BOTM4,CBSO,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bunctr-", XLOCB(19,BOTM4,CBSO,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bsoctrl-",XLOCB(19,BOTM4,CBSO,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bunctrl-",XLOCB(19,BOTM4,CBSO,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bltctr+", XLOCB(19,BOTP4,CBLT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bltctrl+",XLOCB(19,BOTP4,CBLT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bgtctr+", XLOCB(19,BOTP4,CBGT,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bgtctrl+",XLOCB(19,BOTP4,CBGT,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"beqctr+", XLOCB(19,BOTP4,CBEQ,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"beqctrl+",XLOCB(19,BOTP4,CBEQ,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bsoctr+", XLOCB(19,BOTP4,CBSO,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bunctr+", XLOCB(19,BOTP4,CBSO,528,0),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bsoctrl+",XLOCB(19,BOTP4,CBSO,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},
{"bunctrl+",XLOCB(19,BOTP4,CBSO,528,1),	XLBOCBBB_MASK, ISA_V2,	 PPCNONE,	{CR},	NULL},

{"bfctr",   XLO(19,BOF,528,0),		XLBOBB_MASK,   PPCCOM,	 PPCNONE,	{BI},	NULL},
{"bfctr-",  XLO(19,BOF,528,0),		XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bfctrl",  XLO(19,BOF,528,1),		XLBOBB_MASK,   PPCCOM,	 PPCNONE,	{BI},	NULL},
{"bfctrl-", XLO(19,BOF,528,1),		XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bfctr+",  XLO(19,BOFP,528,0),		XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bfctrl+", XLO(19,BOFP,528,1),		XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"bfctr-",  XLO(19,BOFM4,528,0),	XLBOBB_MASK,   ISA_V2,	 PPCNONE,	{BI},	NULL},
{"bfctrl-", XLO(19,BOFM4,528,1),	XLBOBB_MASK,   ISA_V2,	 PPCNONE,	{BI},	NULL},
{"bfctr+",  XLO(19,BOFP4,528,0),	XLBOBB_MASK,   ISA_V2,	 PPCNONE,	{BI},	NULL},
{"bfctrl+", XLO(19,BOFP4,528,1),	XLBOBB_MASK,   ISA_V2,	 PPCNONE,	{BI},	NULL},
{"btctr",   XLO(19,BOT,528,0),		XLBOBB_MASK,   PPCCOM,	 PPCNONE,	{BI},	NULL},
{"btctr-",  XLO(19,BOT,528,0),		XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"btctrl",  XLO(19,BOT,528,1),		XLBOBB_MASK,   PPCCOM,	 PPCNONE,	{BI},	NULL},
{"btctrl-", XLO(19,BOT,528,1),		XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"btctr+",  XLO(19,BOTP,528,0),		XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"btctrl+", XLO(19,BOTP,528,1),		XLBOBB_MASK,   PPCCOM,   ISA_V2,	{BI},	NULL},
{"btctr-",  XLO(19,BOTM4,528,0),	XLBOBB_MASK,   ISA_V2,	 PPCNONE,	{BI},	NULL},
{"btctrl-", XLO(19,BOTM4,528,1),	XLBOBB_MASK,   ISA_V2,	 PPCNONE,	{BI},	NULL},
{"btctr+",  XLO(19,BOTP4,528,0),	XLBOBB_MASK,   ISA_V2,	 PPCNONE,	{BI},	NULL},
{"btctrl+", XLO(19,BOTP4,528,1),	XLBOBB_MASK,   ISA_V2,	 PPCNONE,	{BI},	NULL},

{"bcctr-",  XLYLK(19,528,0,0),		XLYBB_MASK,    PPCCOM,	 PPCNONE,	{BOE, BI},	NULL},
{"bcctrl-", XLYLK(19,528,0,1),		XLYBB_MASK,    PPCCOM,	 PPCNONE,	{BOE, BI},	NULL},
{"bcctr+",  XLYLK(19,528,1,0),		XLYBB_MASK,    PPCCOM,	 PPCNONE,	{BOE, BI},	NULL},
{"bcctrl+", XLYLK(19,528,1,1),		XLYBB_MASK,    PPCCOM,	 PPCNONE,	{BOE, BI},	NULL},
{"bcctr",   XLLK(19,528,0),		XLBH_MASK,     PPCCOM,	 PPCNONE,	{BO, BI, BH},	NULL},
{"bcc",     XLLK(19,528,0),		XLBB_MASK,     PWRCOM,	 PPCNONE,	{BO, BI},	NULL},
{"bcctrl",  XLLK(19,528,1),		XLBH_MASK,     PPCCOM,	 PPCNONE,	{BO, BI, BH},	NULL},
{"bccl",    XLLK(19,528,1),		XLBB_MASK,     PWRCOM,	 PPCNONE,	{BO, BI},	NULL},

{"bctar-",  XLYLK(19,560,0,0),		XLYBB_MASK,    POWER8,	 PPCNONE,	{BOE, BI},	NULL},
{"bctarl-", XLYLK(19,560,0,1),		XLYBB_MASK,    POWER8,	 PPCNONE,	{BOE, BI},	NULL},
{"bctar+",  XLYLK(19,560,1,0),		XLYBB_MASK,    POWER8,	 PPCNONE,	{BOE, BI},	NULL},
{"bctarl+", XLYLK(19,560,1,1),		XLYBB_MASK,    POWER8,	 PPCNONE,	{BOE, BI},	NULL},
{"bctar",   XLLK(19,560,0),		XLBH_MASK,     POWER8,	 PPCNONE,	{BO, BI, BH},	NULL},
{"bctarl",  XLLK(19,560,1),		XLBH_MASK,     POWER8,	 PPCNONE,	{BO, BI, BH},	NULL},

{"rlwimi",	M(20,0),	M_MASK,      PPCCOM,	PPCNONE,	{RA, RS, SH, MBE, ME},	translate_rlwimi},
{"rlimi",	M(20,0),	M_MASK,      PWRCOM,	PPCNONE,	{RA, RS, SH, MBE, ME},	NULL},

{"rlwimi.",	M(20,1),	M_MASK,      PPCCOM,	PPCNONE,	{RA, RS, SH, MBE, ME},	NULL},
{"rlimi.",	M(20,1),	M_MASK,      PWRCOM,	PPCNONE,	{RA, RS, SH, MBE, ME},	NULL},

{"rotlwi",	MME(21,31,0),	MMBME_MASK,  PPCCOM,	PPCNONE,	{RA, RS, SH},	translate_rlwinm},
{"clrlwi",	MME(21,31,0),	MSHME_MASK,  PPCCOM,	PPCNONE,	{RA, RS, MB},	translate_rlwinm},
{"rlwinm",	M(21,0),	M_MASK,      PPCCOM,	PPCNONE,	{RA, RS, SH, MBE, ME},	translate_rlwinm},
{"rlinm",	M(21,0),	M_MASK,      PWRCOM,	PPCNONE,	{RA, RS, SH, MBE, ME},	NULL},
{"rotlwi.",	MME(21,31,1),	MMBME_MASK,  PPCCOM,	PPCNONE,	{RA, RS, SH},	NULL},
{"clrlwi.",	MME(21,31,1),	MSHME_MASK,  PPCCOM,	PPCNONE,	{RA, RS, MB},	NULL},
{"rlwinm.",	M(21,1),	M_MASK,      PPCCOM,	PPCNONE,	{RA, RS, SH, MBE, ME},	NULL},
{"rlinm.",	M(21,1),	M_MASK,      PWRCOM,	PPCNONE,	{RA, RS, SH, MBE, ME},	NULL},

{"rlmi",	M(22,0),	M_MASK,      M601,	PPCNONE,	{RA, RS, RB, MBE, ME},	NULL},
{"rlmi.",	M(22,1),	M_MASK,      M601,	PPCNONE,	{RA, RS, RB, MBE, ME},	NULL},

{"rotlw",	MME(23,31,0),	MMBME_MASK,  PPCCOM,	PPCNONE,	{RA, RS, RB},	translate_rlwnm},
{"rlwnm",	M(23,0),	M_MASK,      PPCCOM,	PPCNONE,	{RA, RS, RB, MBE, ME},	translate_rlwnm},
{"rlnm",	M(23,0),	M_MASK,      PWRCOM,	PPCNONE,	{RA, RS, RB, MBE, ME},	NULL},
{"rotlw.",	MME(23,31,1),	MMBME_MASK,  PPCCOM,	PPCNONE,	{RA, RS, RB},	translate_rlwnm},
{"rlwnm.",	M(23,1),	M_MASK,      PPCCOM,	PPCNONE,	{RA, RS, RB, MBE, ME},	NULL},
{"rlnm.",	M(23,1),	M_MASK,      PWRCOM,	PPCNONE,	{RA, RS, RB, MBE, ME},	NULL},

{"nop",		OP(24),		0xffffffff,  PPCCOM,	PPCNONE,	{UNUSED},	translate_nop},
{"ori",		OP(24),		OP_MASK,     PPCCOM,	PPCNONE,	{RA, RS, UI},	translate_ori},
{"oril",	OP(24),		OP_MASK,     PWRCOM,	PPCNONE,	{RA, RS, UI},	NULL},

{"oris",	OP(25),		OP_MASK,     PPCCOM,	PPCNONE,	{RA, RS, UI},	translate_oris},
{"oriu",	OP(25),		OP_MASK,     PWRCOM,	PPCNONE,	{RA, RS, UI},	NULL},

{"xnop",	OP(26),		0xffffffff,  PPCCOM,	PPCNONE,	{UNUSED},	translate_xori},
{"xori",	OP(26),		OP_MASK,     PPCCOM,	PPCNONE,	{RA, RS, UI},	translate_xori},
{"xoril",	OP(26),		OP_MASK,     PWRCOM,	PPCNONE,	{RA, RS, UI},	NULL},

{"xoris",	OP(27),		OP_MASK,     PPCCOM,	PPCNONE,	{RA, RS, UI},	NULL},
{"xoriu",	OP(27),		OP_MASK,     PWRCOM,	PPCNONE,	{RA, RS, UI},	NULL},

{"andi.",	OP(28),		OP_MASK,     PPCCOM,	PPCNONE,	{RA, RS, UI},	translate_andi_dot},
{"andil.",	OP(28),		OP_MASK,     PWRCOM,	PPCNONE,	{RA, RS, UI},	NULL},

{"andis.",	OP(29),		OP_MASK,     PPCCOM,	PPCNONE,	{RA, RS, UI},	translate_andis_dot},
{"andiu.",	OP(29),		OP_MASK,     PWRCOM,	PPCNONE,	{RA, RS, UI},	NULL},

{"rotldi",	MD(30,0,0),	MDMB_MASK,   PPC64,	PPCNONE,	{RA, RS, SH6},	NULL},
{"clrldi",	MD(30,0,0),	MDSH_MASK,   PPC64,	PPCNONE,	{RA, RS, MB6},	NULL},
{"rldicl",	MD(30,0,0),	MD_MASK,     PPC64,	PPCNONE,	{RA, RS, SH6, MB6},	NULL},
{"rotldi.",	MD(30,0,1),	MDMB_MASK,   PPC64,	PPCNONE,	{RA, RS, SH6},	NULL},
{"clrldi.",	MD(30,0,1),	MDSH_MASK,   PPC64,	PPCNONE,	{RA, RS, MB6},	NULL},
{"rldicl.",	MD(30,0,1),	MD_MASK,     PPC64,	PPCNONE,	{RA, RS, SH6, MB6},	NULL},

{"rldicr",	MD(30,1,0),	MD_MASK,     PPC64,	PPCNONE,	{RA, RS, SH6, ME6},	NULL},
{"rldicr.",	MD(30,1,1),	MD_MASK,     PPC64,	PPCNONE,	{RA, RS, SH6, ME6},	NULL},

{"rldic",	MD(30,2,0),	MD_MASK,     PPC64,	PPCNONE,	{RA, RS, SH6, MB6},	NULL},
{"rldic.",	MD(30,2,1),	MD_MASK,     PPC64,	PPCNONE,	{RA, RS, SH6, MB6},	NULL},

{"rldimi",	MD(30,3,0),	MD_MASK,     PPC64,	PPCNONE,	{RA, RS, SH6, MB6},	NULL},
{"rldimi.",	MD(30,3,1),	MD_MASK,     PPC64,	PPCNONE,	{RA, RS, SH6, MB6},	NULL},

{"rotld",	MDS(30,8,0),	MDSMB_MASK,  PPC64,	PPCNONE,	{RA, RS, RB},	NULL},
{"rldcl",	MDS(30,8,0),	MDS_MASK,    PPC64,	PPCNONE,	{RA, RS, RB, MB6},	NULL},
{"rotld.",	MDS(30,8,1),	MDSMB_MASK,  PPC64,	PPCNONE,	{RA, RS, RB},	NULL},
{"rldcl.",	MDS(30,8,1),	MDS_MASK,    PPC64,	PPCNONE,	{RA, RS, RB, MB6},	NULL},

{"rldcr",	MDS(30,9,0),	MDS_MASK,    PPC64,	PPCNONE,	{RA, RS, RB, ME6},	NULL},
{"rldcr.",	MDS(30,9,1),	MDS_MASK,    PPC64,	PPCNONE,	{RA, RS, RB, ME6},	NULL},

{"cmpw",	XOPL(31,0,0),	XCMPL_MASK,  PPCCOM|PPCVLE,	PPCNONE,	{OBF, RA, RB},	NULL},
{"cmpd",	XOPL(31,0,1),	XCMPL_MASK,  PPC64,	PPCNONE,	{OBF, RA, RB},	NULL},
{"cmp",		X(31,0),	XCMP_MASK,   PPC|PPCVLE, PPCNONE,	{BF, L, RA, RB},	NULL},
{"cmp",		X(31,0),	XCMPL_MASK,  PWRCOM,	PPC,		{BF, RA, RB},	NULL},

{"evlddepx",    VX (31, (799 << 1)),    VX_MASK,     PPCSPE|PPCVLE, PPCNONE,    {RT, RA, RB},   NULL},
{"evstddepx",   VX (31, (927 << 1)),    VX_MASK,     PPCSPE|PPCVLE, PPCNONE,    {RT, RA, RB},   NULL},

{"twlgt",	XTO(31,4,TOLGT), XTO_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RA, RB},	NULL},
{"tlgt",	XTO(31,4,TOLGT), XTO_MASK,   PWRCOM,	PPCNONE,	{RA, RB},	NULL},
{"twllt",	XTO(31,4,TOLLT), XTO_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RA, RB},	NULL},
{"tllt",	XTO(31,4,TOLLT), XTO_MASK,   PWRCOM,	PPCNONE,	{RA, RB},	NULL},
{"tweq",	XTO(31,4,TOEQ),	 XTO_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RA, RB},	NULL},
{"teq",		XTO(31,4,TOEQ),	 XTO_MASK,   PWRCOM,	PPCNONE,	{RA, RB},	NULL},
{"twlge",	XTO(31,4,TOLGE), XTO_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RA, RB},	NULL},
{"tlge",	XTO(31,4,TOLGE), XTO_MASK,   PWRCOM,	PPCNONE,	{RA, RB},	NULL},
{"twlnl",	XTO(31,4,TOLNL), XTO_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RA, RB},	NULL},
{"tlnl",	XTO(31,4,TOLNL), XTO_MASK,   PWRCOM,	PPCNONE,	{RA, RB},	NULL},
{"twlle",	XTO(31,4,TOLLE), XTO_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RA, RB},	NULL},
{"tlle",	XTO(31,4,TOLLE), XTO_MASK,   PWRCOM,	PPCNONE,	{RA, RB},	NULL},
{"twlng",	XTO(31,4,TOLNG), XTO_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RA, RB},	NULL},
{"tlng",	XTO(31,4,TOLNG), XTO_MASK,   PWRCOM,	PPCNONE,	{RA, RB},	NULL},
{"twgt",	XTO(31,4,TOGT),	 XTO_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RA, RB},	NULL},
{"tgt",		XTO(31,4,TOGT),	 XTO_MASK,   PWRCOM,	PPCNONE,	{RA, RB},	NULL},
{"twge",	XTO(31,4,TOGE),	 XTO_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RA, RB},	NULL},
{"tge",		XTO(31,4,TOGE),	 XTO_MASK,   PWRCOM,	PPCNONE,	{RA, RB},	NULL},
{"twnl",	XTO(31,4,TONL),	 XTO_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RA, RB},	NULL},
{"tnl",		XTO(31,4,TONL),	 XTO_MASK,   PWRCOM,	PPCNONE,	{RA, RB},	NULL},
{"twlt",	XTO(31,4,TOLT),	 XTO_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RA, RB},	NULL},
{"tlt",		XTO(31,4,TOLT),	 XTO_MASK,   PWRCOM,	PPCNONE,	{RA, RB},	NULL},
{"twle",	XTO(31,4,TOLE),	 XTO_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RA, RB},	NULL},
{"tle",		XTO(31,4,TOLE),	 XTO_MASK,   PWRCOM,	PPCNONE,	{RA, RB},	NULL},
{"twng",	XTO(31,4,TONG),	 XTO_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RA, RB},	NULL},
{"tng",		XTO(31,4,TONG),	 XTO_MASK,   PWRCOM,	PPCNONE,	{RA, RB},	NULL},
{"twne",	XTO(31,4,TONE),	 XTO_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RA, RB},	NULL},
{"tne",		XTO(31,4,TONE),	 XTO_MASK,   PWRCOM,	PPCNONE,	{RA, RB},	NULL},
{"trap",	XTO(31,4,TOU),	 0xffffffff, PPCCOM|PPCVLE, PPCNONE,	{UNUSED},	NULL},
{"twu",		XTO(31,4,TOU),	 XTO_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RA, RB},	NULL},
{"tu",		XTO(31,4,TOU),	 XTO_MASK,   PWRCOM,	PPCNONE,	{RA, RB},	NULL},
{"tw",		X(31,4),	 X_MASK, PPCCOM|PPCVLE, PPCNONE,	{TO, RA, RB},	NULL},
{"t",		X(31,4),	 X_MASK,     PWRCOM,	PPCNONE,	{TO, RA, RB},	NULL},

{"lvsl",	X(31,6),	X_MASK,      PPCVEC|PPCVLE, PPCNONE,	{VD, RA0, RB},	NULL},
{"lvebx",	X(31,7),	X_MASK,      PPCVEC|PPCVLE, PPCNONE,	{VD, RA0, RB},	NULL},
{"lbfcmx",	APU(31,7,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"subfc",	XO(31,8,0,0),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"sf",		XO(31,8,0,0),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},
{"subc",	XO(31,8,0,0),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RB, RA},	NULL},
{"subfc.",	XO(31,8,0,1),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"sf.",		XO(31,8,0,1),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},
{"subc.",	XO(31,8,0,1),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RB, RA},	NULL},
 
{"mulhdu",	XO(31,9,0,0),	XO_MASK,     PPC64|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"mulhdu.",	XO(31,9,0,1),	XO_MASK,     PPC64|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
 
{"addc",	XO(31,10,0,0),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"a",		XO(31,10,0,0),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},
{"addc.",	XO(31,10,0,1),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"a.",		XO(31,10,0,1),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},

{"mulhwu",	XO(31,11,0,0),	XO_MASK,     PPC|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"mulhwu.",	XO(31,11,0,1),	XO_MASK,     PPC|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},

{"lxsiwzx",	X(31,12),	XX1_MASK,    PPCVSX2,	PPCNONE,	{XT6, RA0, RB},	NULL},

{"isellt",	X(31,15),	X_MASK,      PPCISEL|PPCVLE,	PPCNONE,	{RT, RA0, RB},	NULL},

{"tlbilxlpid",	XTO(31,18,0),	XTO_MASK, E500MC|PPCA2,	PPCNONE,	{UNUSED},	NULL},
{"tlbilxpid",	XTO(31,18,1),	XTO_MASK, E500MC|PPCA2,	PPCNONE,	{UNUSED},	NULL},
{"tlbilxva",	XTO(31,18,3),	XTO_MASK, E500MC|PPCA2,	PPCNONE,	{RA0, RB},	NULL},
{"tlbilx",	X(31,18),	X_MASK,   E500MC|PPCA2,	PPCNONE,	{T, RA0, RB},	NULL},

{"mfcr",	XFXM(31,19,0,0), XFXFXM_MASK, POWER4,	PPCNONE,	{RT, FXM4},	NULL},
{"mfcr",	XFXM(31,19,0,0), XRARB_MASK, COM|PPCVLE, POWER4,	{RT},	NULL},
{"mfocrf",	XFXM(31,19,0,1), XFXFXM_MASK, COM|PPCVLE, PPCNONE,	{RT, FXM},	NULL},

{"lwarx",	X(31,20),	XEH_MASK,    PPC|PPCVLE, PPCNONE,	{RT, RA0, RB, EH},	NULL},
 
{"ldx",		X(31,21),	X_MASK,	     PPC64|PPCVLE, PPCNONE,	{RT, RA0, RB},	NULL},
 
{"icbt",	X(31,22),	X_MASK,	     BOOKE|PPCE300|PPCA2|PPC476|PPCVLE, PPCNONE, {CT, RA0, RB},	NULL},
 
{"lwzx",	X(31,23),	X_MASK,	     PPCCOM|PPCVLE, PPCNONE,	{RT, RA0, RB},	NULL},
{"lx",		X(31,23),	X_MASK,      PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},

{"slw",		XRC(31,24,0),	X_MASK,	     PPCCOM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},
{"sl",		XRC(31,24,0),	X_MASK,      PWRCOM,	PPCNONE,	{RA, RS, RB},	NULL},
{"slw.",	XRC(31,24,1),	X_MASK,	     PPCCOM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},
{"sl.",		XRC(31,24,1),	X_MASK,      PWRCOM,	PPCNONE,	{RA, RS, RB},	NULL},

{"cntlzw",	XRC(31,26,0),	XRB_MASK,    PPCCOM|PPCVLE, PPCNONE,	{RA, RS},	NULL},
{"cntlz",	XRC(31,26,0),	XRB_MASK,    PWRCOM,	PPCNONE,	{RA, RS},	NULL},
{"cntlzw.",	XRC(31,26,1),	XRB_MASK,    PPCCOM|PPCVLE, PPCNONE,	{RA, RS},	NULL},
{"cntlz.",	XRC(31,26,1),	XRB_MASK,    PWRCOM,	PPCNONE,	{RA, RS},	NULL},

{"sld",		XRC(31,27,0),	X_MASK,      PPC64|PPCVLE,	PPCNONE,	{RA, RS, RB},	NULL},
{"sld.",	XRC(31,27,1),	X_MASK,      PPC64|PPCVLE,	PPCNONE,	{RA, RS, RB},	NULL},

{"and",		XRC(31,28,0),	X_MASK,      COM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},
{"and.",	XRC(31,28,1),	X_MASK,	     COM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},

{"maskg",	XRC(31,29,0),	X_MASK,      M601,	PPCA2,		{RA, RS, RB},	NULL},
{"maskg.",	XRC(31,29,1),	X_MASK,      M601,	PPCA2,		{RA, RS, RB},	NULL},

{"ldepx",	X(31,29),	X_MASK,      E500MC|PPCA2|PPCVLE, PPCNONE, {RT, RA0, RB},	NULL},

{"waitasec",	X(31,30),	XRTRARB_MASK,POWER8,	PPCNONE,	{UNUSED},	NULL},

{"lwepx",	X(31,31),	X_MASK,	     E500MC|PPCA2|PPCVLE, PPCNONE, {RT, RA0, RB},	NULL},

{"cmplw",	XOPL(31,32,0),	XCMPL_MASK,  PPCCOM|PPCVLE, PPCNONE,	{OBF, RA, RB},	NULL},
{"cmpld",	XOPL(31,32,1),	XCMPL_MASK,  PPC64,	PPCNONE,	{OBF, RA, RB},	NULL},
{"cmpl",	X(31,32),	XCMP_MASK,   PPC|PPCVLE, PPCNONE,	{BF, L, RA, RB},	NULL},
{"cmpl",	X(31,32),	XCMPL_MASK,  PWRCOM,	PPC,		{BF, RA, RB},	NULL},

{"lvsr",	X(31,38),	X_MASK,      PPCVEC|PPCVLE, PPCNONE,	{VD, RA0, RB},	NULL},
{"lvehx",	X(31,39),	X_MASK,      PPCVEC|PPCVLE, PPCNONE,	{VD, RA0, RB},	NULL},
{"lhfcmx",	APU(31,39,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"mviwsplt",	X(31,46),	X_MASK,      PPCVEC2,	PPCNONE,	{VD, RA, RB},	NULL},

{"iselgt",	X(31,47),	X_MASK,      PPCISEL|PPCVLE,	PPCNONE,	{RT, RA0, RB},	NULL},

{"lvewx",	X(31,71),	X_MASK,      PPCVEC|PPCVLE, PPCNONE,	{VD, RA0, RB},	NULL},

{"addg6s",	XO(31,74,0,0),	XO_MASK,     POWER6,	PPCNONE,	{RT, RA, RB},	NULL},

{"lxsiwax",	X(31,76),	XX1_MASK,    PPCVSX2,	PPCNONE,	{XT6, RA0, RB},	NULL},

{"iseleq",	X(31,79),	X_MASK,      PPCISEL|PPCVLE,	PPCNONE,	{RT, RA0, RB},	NULL},

{"isel",	XISEL(31,15), XISEL_MASK, PPCISEL|TITAN|PPCVLE, PPCNONE, {RT, RA0, RB, CRB},	NULL},

{"subf",	XO(31,40,0,0),	XO_MASK,     PPC|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"sub",		XO(31,40,0,0),	XO_MASK,     PPC|PPCVLE, PPCNONE,	{RT, RB, RA},	NULL},
{"subf.",	XO(31,40,0,1),	XO_MASK,     PPC|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"sub.",	XO(31,40,0,1),	XO_MASK,     PPC|PPCVLE, PPCNONE,	{RT, RB, RA},	NULL},

{"mfvsrd",	X(31,51),	XX1RB_MASK,   PPCVSX2,	PPCNONE,	{RA, XS6},	NULL},
{"mffprd",	X(31,51),	XX1RB_MASK|1, PPCVSX2,	PPCNONE,	{RA, FRS},	NULL},
{"mfvrd",	X(31,51)|1,	XX1RB_MASK|1, PPCVSX2,	PPCNONE,	{RA, VS},	NULL},
{"eratilx",	X(31,51),	X_MASK,	     PPCA2,	PPCNONE,	{ERAT_T, RA, RB},	NULL},

{"lbarx",	X(31,52),	XEH_MASK,    POWER7|PPCVLE, PPCNONE,	{RT, RA0, RB, EH},	NULL},

{"ldux",	X(31,53),	X_MASK,      PPC64|PPCVLE, PPCNONE,	{RT, RAL, RB},	NULL},
 
{"dcbst",	X(31,54),	XRT_MASK,    PPC|PPCVLE, PPCNONE,	{RA0, RB},	NULL},
 
{"lwzux",	X(31,55),	X_MASK,	     PPCCOM|PPCVLE, PPCNONE,	{RT, RAL, RB},	NULL},
{"lux",		X(31,55),	X_MASK,      PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},

{"cntlzd",	XRC(31,58,0),	XRB_MASK,    PPC64|PPCVLE, PPCNONE,	{RA, RS},	NULL},
{"cntlzd.",	XRC(31,58,1),	XRB_MASK,    PPC64|PPCVLE, PPCNONE,	{RA, RS},	NULL},

{"andc",	XRC(31,60,0),	X_MASK,	     COM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},
{"andc.",	XRC(31,60,1),	X_MASK,	     COM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},

{"waitrsv",	X(31,62)|(1<<21), 0xffffffff, POWER7|E500MC|PPCA2, PPCNONE, {UNUSED},	NULL},
{"waitimpl",	X(31,62)|(2<<21), 0xffffffff, POWER7|E500MC|PPCA2, PPCNONE, {UNUSED},	NULL},
{"wait",	X(31,62),	XWC_MASK,    POWER7|E500MC|PPCA2|PPCVLE, PPCNONE, {WC},	NULL},
 
{"dcbstep",	XRT(31,63,0),	XRT_MASK,    E500MC|PPCA2|PPCVLE, PPCNONE, {RA0, RB},	NULL},

{"tdlgt",	XTO(31,68,TOLGT), XTO_MASK,  PPC64,	PPCNONE,	{RA, RB},	NULL},
{"tdllt",	XTO(31,68,TOLLT), XTO_MASK,  PPC64,	PPCNONE,	{RA, RB},	NULL},
{"tdeq",	XTO(31,68,TOEQ),  XTO_MASK,  PPC64,	PPCNONE,	{RA, RB},	NULL},
{"tdlge",	XTO(31,68,TOLGE), XTO_MASK,  PPC64,	PPCNONE,	{RA, RB},	NULL},
{"tdlnl",	XTO(31,68,TOLNL), XTO_MASK,  PPC64,	PPCNONE,	{RA, RB},	NULL},
{"tdlle",	XTO(31,68,TOLLE), XTO_MASK,  PPC64,	PPCNONE,	{RA, RB},	NULL},
{"tdlng",	XTO(31,68,TOLNG), XTO_MASK,  PPC64,	PPCNONE,	{RA, RB},	NULL},
{"tdgt",	XTO(31,68,TOGT),  XTO_MASK,  PPC64,	PPCNONE,	{RA, RB},	NULL},
{"tdge",	XTO(31,68,TOGE),  XTO_MASK,  PPC64,	PPCNONE,	{RA, RB},	NULL},
{"tdnl",	XTO(31,68,TONL),  XTO_MASK,  PPC64,	PPCNONE,	{RA, RB},	NULL},
{"tdlt",	XTO(31,68,TOLT),  XTO_MASK,  PPC64,	PPCNONE,	{RA, RB},	NULL},
{"tdle",	XTO(31,68,TOLE),  XTO_MASK,  PPC64,	PPCNONE,	{RA, RB},	NULL},
{"tdng",	XTO(31,68,TONG),  XTO_MASK,  PPC64,	PPCNONE,	{RA, RB},	NULL},
{"tdne",	XTO(31,68,TONE),  XTO_MASK,  PPC64,	PPCNONE,	{RA, RB},	NULL},
{"tdu",		XTO(31,68,TOU),   XTO_MASK,  PPC64,	PPCNONE,	{RA, RB},	NULL},
{"td",		X(31,68),	X_MASK,      PPC64|PPCVLE, PPCNONE,	{TO, RA, RB},	NULL},

{"lwfcmx",	APU(31,71,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},
{"mulhd",	XO(31,73,0,0),	XO_MASK,     PPC64|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"mulhd.",	XO(31,73,0,1),	XO_MASK,     PPC64|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
 
{"mulhw",	XO(31,75,0,0),	XO_MASK,     PPC|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"mulhw.",	XO(31,75,0,1),	XO_MASK,     PPC|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},

{"dlmzb",	XRC(31,78,0), X_MASK, PPC403|PPC440|TITAN|PPCVLE, PPCNONE, {RA, RS, RB},	NULL},
{"dlmzb.",	XRC(31,78,1), X_MASK, PPC403|PPC440|TITAN|PPCVLE, PPCNONE, {RA, RS, RB},	NULL},

{"mtsrd",	X(31,82),  XRB_MASK|(1<<20), PPC64,	PPCNONE,	{SR, RS},	NULL},

{"mfmsr",	X(31,83),	XRARB_MASK,  COM|PPCVLE, PPCNONE,	{RT},	NULL},
 
{"ldarx",	X(31,84),	XEH_MASK,    PPC64|PPCVLE, PPCNONE,	{RT, RA0, RB, EH},	NULL},

{"dcbfl",	XOPL(31,86,1),	XRT_MASK,    POWER5,	PPC476,		{RA0, RB},	NULL},
{"dcbf",	X(31,86),	XLRT_MASK,   PPC|PPCVLE, PPCNONE,	{RA0, RB, L},	NULL},

{"lbzx",	X(31,87),	X_MASK,	     COM|PPCVLE, PPCNONE,	{RT, RA0, RB},	NULL},
 
{"lbepx",	X(31,95),	X_MASK,	     E500MC|PPCA2|PPCVLE, PPCNONE, {RT, RA0, RB},	NULL},

{"dni",		XRC(31,97,1),	XRB_MASK,    E6500,	PPCNONE,	{DUI, DCTL},	NULL},

{"lvx",		X(31,103),	X_MASK,      PPCVEC|PPCVLE, PPCNONE,	{VD, RA0, RB},	NULL},
{"lqfcmx",	APU(31,103,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"neg",		XO(31,104,0,0),	XORB_MASK,   COM|PPCVLE, PPCNONE,	{RT, RA},	NULL},
{"neg.",	XO(31,104,0,1),	XORB_MASK,   COM|PPCVLE, PPCNONE,	{RT, RA},	NULL},

{"mul",		XO(31,107,0,0),	XO_MASK,     M601,	PPCNONE,	{RT, RA, RB},	NULL},
{"mul.",	XO(31,107,0,1),	XO_MASK,     M601,	PPCNONE,	{RT, RA, RB},	NULL},

{"mvidsplt",	X(31,110),	X_MASK,      PPCVEC2,	PPCNONE,	{VD, RA, RB},	NULL},

{"mtsrdin",	X(31,114),	XRA_MASK,    PPC64,	PPCNONE,	{RS, RB},	NULL},

{"mffprwz",	X(31,115),	XX1RB_MASK|1, PPCVSX2,	PPCNONE,	{RA, FRS},	NULL},
{"mfvrwz",	X(31,115)|1,	XX1RB_MASK|1, PPCVSX2,	PPCNONE,	{RA, VS},	NULL},
{"mfvsrwz",	X(31,115),	XX1RB_MASK,   PPCVSX2,	PPCNONE,	{RA, XS6},	NULL},

{"lharx",	X(31,116),	XEH_MASK,    POWER7|PPCVLE, PPCNONE,	{RT, RA0, RB, EH},	NULL},

{"clf",		X(31,118),	XTO_MASK,    POWER,	PPCNONE,	{RA, RB},	NULL},

{"lbzux",	X(31,119),	X_MASK,	     COM|PPCVLE, PPCNONE,	{RT, RAL, RB},	NULL},
 
{"popcntb",	X(31,122),	XRB_MASK,    POWER5|PPCVLE, PPCNONE,	{RA, RS},	NULL},

{"not",		XRC(31,124,0),	X_MASK,      COM|PPCVLE,	PPCNONE,	{RA, RS, RBS},	NULL},
{"nor",		XRC(31,124,0),	X_MASK,	     COM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},
{"not.",	XRC(31,124,1),	X_MASK,      COM,	PPCNONE,	{RA, RS, RBS},	NULL},
{"nor.",	XRC(31,124,1),	X_MASK,      COM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},

{"dcbfep",	XRT(31,127,0),	XRT_MASK,    E500MC|PPCA2|PPCVLE, PPCNONE, {RA0, RB},	NULL},
 
{"wrtee",	X(31,131),	XRARB_MASK,  PPC403|BOOKE|PPCA2|PPC476|PPCVLE, PPCNONE, {RS},	NULL},
 
{"dcbtstls",	X(31,134),	X_MASK,	     PPCCHLK|PPC476|TITAN|PPCVLE, PPCNONE, {CT, RA0, RB},	NULL},

{"stvebx",	X(31,135),	X_MASK,      PPCVEC|PPCVLE,	PPCNONE,	{VS, RA0, RB},	NULL},
{"stbfcmx",	APU(31,135,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"subfe",	XO(31,136,0,0),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"sfe",		XO(31,136,0,0),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},
{"subfe.",	XO(31,136,0,1),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"sfe.",	XO(31,136,0,1),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},

{"adde",	XO(31,138,0,0),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"ae",		XO(31,138,0,0),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},
{"adde.",	XO(31,138,0,1),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"ae.",		XO(31,138,0,1),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},

{"stxsiwx",	X(31,140),	XX1_MASK,    PPCVSX2,	PPCNONE,	{XS6, RA0, RB},	NULL},

{"msgsndp",	XRTRA(31,142,0,0), XRTRA_MASK, POWER8,	PPCNONE,	{RB},	NULL},
{"dcbtstlse",	X(31,142),	X_MASK,      PPCCHLK,	E500MC,		{CT, RA0, RB},	NULL},

{"mtcr",	XFXM(31,144,0xff,0), XRARB_MASK, COM|PPCVLE,	PPCNONE,	{RS},	NULL},
{"mtcrf",	XFXM(31,144,0,0), XFXFXM_MASK, COM|PPCVLE, PPCNONE,	{FXM, RS},	NULL},
{"mtocrf",	XFXM(31,144,0,1), XFXFXM_MASK, COM|PPCVLE, PPCNONE,	{FXM, RS},	NULL},

{"mtmsr",	X(31,146),	XRLARB_MASK, COM|PPCVLE, PPCNONE,	{RS, A_L},	NULL},

{"mtsle",	X(31,147),    XRTLRARB_MASK, POWER8,	PPCNONE,	{L},	NULL},

{"eratsx",	XRC(31,147,0),	X_MASK,	     PPCA2,	PPCNONE,	{RT, RA0, RB},	NULL},
{"eratsx.",	XRC(31,147,1),	X_MASK,	     PPCA2,	PPCNONE,	{RT, RA0, RB},	NULL},

{"stdx",	X(31,149),	X_MASK,      PPC64|PPCVLE, PPCNONE,	{RS, RA0, RB},	NULL},
 
{"stwcx.",	XRC(31,150,1),	X_MASK,	     PPC|PPCVLE, PPCNONE,	{RS, RA0, RB},	NULL},
 
{"stwx",	X(31,151),	X_MASK,      PPCCOM|PPCVLE, PPCNONE,	{RS, RA0, RB},	NULL},
{"stx",		X(31,151),	X_MASK,      PWRCOM,	PPCNONE,	{RS, RA, RB},	NULL},

{"slq",		XRC(31,152,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},
{"slq.",	XRC(31,152,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},

{"sle",		XRC(31,153,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},
{"sle.",	XRC(31,153,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},

{"prtyw",	X(31,154),	XRB_MASK, POWER6|PPCA2|PPC476, PPCNONE,	{RA, RS},	NULL},

{"stdepx",	X(31,157),	X_MASK,	     E500MC|PPCA2|PPCVLE, PPCNONE, {RS, RA0, RB},	NULL},
 
{"stwepx",	X(31,159),	X_MASK,	     E500MC|PPCA2|PPCVLE, PPCNONE, {RS, RA0, RB},	NULL},
 
{"wrteei",	X(31,163),	XE_MASK,     PPC403|BOOKE|PPCA2|PPC476|PPCVLE, PPCNONE, {E},	NULL},
 
{"dcbtls",	X(31,166),	X_MASK,	     PPCCHLK|PPC476|TITAN|PPCVLE, PPCNONE, {CT, RA0, RB},	NULL},

{"stvehx",	X(31,167),	X_MASK,      PPCVEC|PPCVLE,	PPCNONE,	{VS, RA0, RB},	NULL},
{"sthfcmx",	APU(31,167,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"msgclrp",	XRTRA(31,174,0,0), XRTRA_MASK, POWER8,	PPCNONE,	{RB},	NULL},
{"dcbtlse",	X(31,174),	X_MASK,      PPCCHLK,	E500MC,		{CT, RA0, RB},	NULL},

{"mtmsrd",	X(31,178),	XRLARB_MASK, PPC64,	PPCNONE,	{RS, A_L},	NULL},

{"mtvsrd",	X(31,179),	XX1RB_MASK,   PPCVSX2,	PPCNONE,	{XT6, RA},	NULL},
{"mtfprd",	X(31,179),	XX1RB_MASK|1, PPCVSX2,	PPCNONE,	{FRT, RA},	NULL},
{"mtvrd",	X(31,179)|1,	XX1RB_MASK|1, PPCVSX2,	PPCNONE,	{VD, RA},	NULL},
{"eratre",	X(31,179),	X_MASK,	     PPCA2,	PPCNONE,	{RT, RA, WS},	NULL},

{"stdux",	X(31,181),	X_MASK,      PPC64|PPCVLE, PPCNONE,	{RS, RAS, RB},	NULL},

{"stqcx.",	XRC(31,182,1),	X_MASK,      POWER8,	PPCNONE,	{RSQ, RA0, RB},	NULL},
{"wchkall",	X(31,182),	X_MASK,      PPCA2,	PPCNONE,	{OBF},	NULL},

{"stwux",	X(31,183),	X_MASK,      PPCCOM|PPCVLE, PPCNONE,	{RS, RAS, RB},	NULL},
{"stux",	X(31,183),	X_MASK,      PWRCOM,	PPCNONE,	{RS, RA0, RB},	NULL},

{"sliq",	XRC(31,184,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, SH},	NULL},
{"sliq.",	XRC(31,184,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, SH},	NULL},

{"prtyd",	X(31,186),	XRB_MASK, POWER6|PPCA2,	PPCNONE,	{RA, RS},	NULL},

{"icblq.",	XRC(31,198,1),	X_MASK,      E6500,	PPCNONE,	{CT, RA0, RB},	NULL},

{"stvewx",	X(31,199),	X_MASK,      PPCVEC|PPCVLE,	PPCNONE,	{VS, RA0, RB},	NULL},
{"stwfcmx",	APU(31,199,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"subfze",	XO(31,200,0,0),	XORB_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RT, RA},	NULL},
{"sfze",	XO(31,200,0,0),	XORB_MASK,   PWRCOM,	PPCNONE,	{RT, RA},	NULL},
{"subfze.",	XO(31,200,0,1),	XORB_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RT, RA},	NULL},
{"sfze.",	XO(31,200,0,1),	XORB_MASK,   PWRCOM,	PPCNONE,	{RT, RA},	NULL},

{"addze",	XO(31,202,0,0),	XORB_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RT, RA},	NULL},
{"aze",		XO(31,202,0,0),	XORB_MASK,   PWRCOM,	PPCNONE,	{RT, RA},	NULL},
{"addze.",	XO(31,202,0,1),	XORB_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RT, RA},	NULL},
{"aze.",	XO(31,202,0,1),	XORB_MASK,   PWRCOM,	PPCNONE,	{RT, RA},	NULL},

{"msgsnd",	XRTRA(31,206,0,0), XRTRA_MASK, E500MC|PPCA2|PPCVLE, PPCNONE, {RB},	NULL},

{"mtsr",	X(31,210), XRB_MASK|(1<<20), COM,	NON32,  	{SR, RS},	NULL},

{"mtfprwa",	X(31,211),	XX1RB_MASK|1, PPCVSX2,	PPCNONE,	{FRT, RA},	NULL},
{"mtvrwa",	X(31,211)|1,	XX1RB_MASK|1, PPCVSX2,	PPCNONE,	{VD, RA},	NULL},
{"mtvsrwa",	X(31,211),	XX1RB_MASK,   PPCVSX2,	PPCNONE,	{XT6, RA},	NULL},
{"eratwe",	X(31,211),	X_MASK,	     PPCA2,	PPCNONE,	{RS, RA, WS},	NULL},

{"ldawx.",	XRC(31,212,1),	X_MASK,	     PPCA2,	PPCNONE,	{RT, RA0, RB},	NULL},

{"stdcx.",	XRC(31,214,1),	X_MASK,      PPC64|PPCVLE, PPCNONE,	{RS, RA0, RB},	NULL},
 
{"stbx",	X(31,215),	X_MASK,	     COM|PPCVLE, PPCNONE,	{RS, RA0, RB},	NULL},

{"sllq",	XRC(31,216,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},
{"sllq.",	XRC(31,216,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},

{"sleq",	XRC(31,217,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},
{"sleq.",	XRC(31,217,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},

{"stbepx",	X(31,223),	X_MASK,      E500MC|PPCA2|PPCVLE, PPCNONE, {RS, RA0, RB},	NULL},
 
{"icblc",	X(31,230),	X_MASK,	PPCCHLK|PPC476|TITAN|PPCVLE, PPCNONE, {CT, RA0, RB},	NULL},

{"stvx",	X(31,231),	X_MASK,      PPCVEC|PPCVLE, PPCNONE,	{VS, RA0, RB},	NULL},
{"stqfcmx",	APU(31,231,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"subfme",	XO(31,232,0,0),	XORB_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RT, RA},	NULL},
{"sfme",	XO(31,232,0,0),	XORB_MASK,   PWRCOM,	PPCNONE,	{RT, RA},	NULL},
{"subfme.",	XO(31,232,0,1),	XORB_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RT, RA},	NULL},
{"sfme.",	XO(31,232,0,1),	XORB_MASK,   PWRCOM,	PPCNONE,	{RT, RA},	NULL},

{"mulld",	XO(31,233,0,0),	XO_MASK,     PPC64|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"mulld.",	XO(31,233,0,1),	XO_MASK,     PPC64|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
 
{"addme",	XO(31,234,0,0),	XORB_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RT, RA},	NULL},
{"ame",		XO(31,234,0,0),	XORB_MASK,   PWRCOM,	PPCNONE,	{RT, RA},	NULL},
{"addme.",	XO(31,234,0,1),	XORB_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RT, RA},	NULL},
{"ame.",	XO(31,234,0,1),	XORB_MASK,   PWRCOM,	PPCNONE,	{RT, RA},	NULL},

{"mullw",	XO(31,235,0,0),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"muls",	XO(31,235,0,0),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},
{"mullw.",	XO(31,235,0,1),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"muls.",	XO(31,235,0,1),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},

{"icblce",	X(31,238),	X_MASK,      PPCCHLK,	E500MC|PPCA2,	{CT, RA, RB},	NULL},
{"msgclr",	XRTRA(31,238,0,0),XRTRA_MASK, E500MC|PPCA2|PPCVLE, PPCNONE, {RB},	NULL},
{"mtsrin",	X(31,242),	XRA_MASK,    PPC,	NON32,  	{RS, RB},	NULL},
{"mtsri",	X(31,242),	XRA_MASK,    POWER,	NON32,		{RS, RB},	NULL},

{"mtfprwz",	X(31,243),	XX1RB_MASK|1, PPCVSX2,	PPCNONE,	{FRT, RA},	NULL},
{"mtvrwz",	X(31,243)|1,	XX1RB_MASK|1, PPCVSX2,	PPCNONE,	{VD, RA},	NULL},
{"mtvsrwz",	X(31,243),	XX1RB_MASK,   PPCVSX2,	PPCNONE,	{XT6, RA},	NULL},

{"dcbtstt",	XRT(31,246,0x10), XRT_MASK,  POWER7,	PPCNONE,	{RA0, RB},	NULL},
{"dcbtst",	X(31,246),	X_MASK,      POWER4,	E5500|E6500,	{RA0, RB, CT},	NULL},
{"dcbtst",	X(31,246),	X_MASK,      E5500|E6500, PPCNONE,	{CT, RA0, RB},	NULL},
{"dcbtst",	X(31,246),	X_MASK,      PPC|PPCVLE, POWER4,	{CT, RA0, RB},	NULL},
 
{"stbux",	X(31,247),	X_MASK,	     COM|PPCVLE, PPCNONE,	{RS, RAS, RB},	NULL},

{"slliq",	XRC(31,248,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, SH},	NULL},
{"slliq.",	XRC(31,248,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, SH},	NULL},

{"bpermd",	X(31,252),	X_MASK,   POWER7|PPCA2,	PPCNONE,	{RA, RS, RB},	NULL},

{"dcbtstep",	XRT(31,255,0),	X_MASK,   E500MC|PPCA2|PPCVLE, PPCNONE,	{RT, RA0, RB},	NULL},

{"mfdcrx",	X(31,259),	X_MASK, BOOKE|PPCA2|PPC476|PPCVLE, TITAN, {RS, RA},	NULL},
{"mfdcrx.",	XRC(31,259,1),	X_MASK,      PPCA2,	PPCNONE,	{RS, RA},	NULL},

{"lvexbx",	X(31,261),	X_MASK,      PPCVEC2,	PPCNONE,	{VD, RA0, RB},	NULL},

{"icbt",	X(31,262),	XRT_MASK,    PPC403,	PPCNONE,	{RA, RB},	NULL},

{"lvepxl",	X(31,263),	X_MASK,      PPCVEC2|PPCVLE, PPCNONE,	{VD, RA0, RB},	NULL},

{"ldfcmx",	APU(31,263,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},
{"doz",		XO(31,264,0,0),	XO_MASK,     M601,	PPCNONE,	{RT, RA, RB},	NULL},
{"doz.",	XO(31,264,0,1),	XO_MASK,     M601,	PPCNONE,	{RT, RA, RB},	NULL},

{"add",		XO(31,266,0,0),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"cax",		XO(31,266,0,0),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},
{"add.",	XO(31,266,0,1),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"cax.",	XO(31,266,0,1),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},

{"ehpriv",	X(31,270),	0xffffffff, E500MC|PPCA2|PPCVLE, PPCNONE, {UNUSED},	NULL},

{"tlbiel",	X(31,274),	XRTLRA_MASK, POWER4,	PPC476,		{RB, L},	NULL},

{"mfapidi",	X(31,275),	X_MASK,      BOOKE,	TITAN,  	{RT, RA},	NULL},

{"lqarx",	X(31,276),	XEH_MASK,    POWER8,	PPCNONE,	{RTQ, RAX, RBX, EH},	NULL},

{"lscbx",	XRC(31,277,0),	X_MASK,      M601,	PPCNONE,	{RT, RA, RB},	NULL},
{"lscbx.",	XRC(31,277,1),	X_MASK,      M601,	PPCNONE,	{RT, RA, RB},	NULL},

{"dcbtt",	XRT(31,278,0x10), XRT_MASK,  POWER7,	PPCNONE,	{RA0, RB},	NULL},
{"dcbt",	X(31,278),	X_MASK,      POWER4,	E5500|E6500,	{RA0, RB, CT},	NULL},
{"dcbt",	X(31,278),	X_MASK,      E5500|E6500, PPCNONE,	{CT, RA0, RB},	NULL},
{"dcbt",	X(31,278),	X_MASK,      PPC|PPCVLE, POWER4,	{CT, RA0, RB},	NULL},
 
{"lhzx",	X(31,279),	X_MASK,      COM|PPCVLE, PPCNONE,	{RT, RA0, RB},	NULL},

{"cdtbcd",	X(31,282),	XRB_MASK,    POWER6,	PPCNONE,	{RA, RS},	NULL},

{"eqv",		XRC(31,284,0),	X_MASK,      COM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},
{"eqv.",	XRC(31,284,1),	X_MASK,	     COM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},

{"lhepx",	X(31,287),	X_MASK,   E500MC|PPCA2|PPCVLE, PPCNONE,	{RT, RA0, RB},	NULL},

{"mfdcrux",	X(31,291),	X_MASK,      PPC464|PPCVLE, PPCNONE,	{RS, RA},	NULL},

{"lvexhx",	X(31,293),	X_MASK,      PPCVEC2,	PPCNONE,	{VD, RA0, RB},	NULL},
{"lvepx",	X(31,295),	X_MASK,      PPCVEC2|PPCVLE, PPCNONE,	{VD, RA0, RB},	NULL},

{"mfbhrbe",	X(31,302),	X_MASK,      POWER8,	PPCNONE,	{RT, BHRBE},	NULL},

{"tlbie",	X(31,306),	XRTLRA_MASK, PPC,	TITAN,  	{RB, L},	NULL},
{"tlbi",	X(31,306),	XRT_MASK,    POWER,	PPCNONE,	{RA0, RB},	NULL},

{"eciwx",	X(31,310),	X_MASK,      PPC,	TITAN,  	{RT, RA0, RB},	NULL},

{"lhzux",	X(31,311),	X_MASK,      COM|PPCVLE, PPCNONE,	{RT, RAL, RB},	NULL},

{"cbcdtd",	X(31,314),	XRB_MASK,    POWER6,	PPCNONE,	{RA, RS},	NULL},

{"xor",		XRC(31,316,0),	X_MASK,      COM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},
{"xor.",	XRC(31,316,1),	X_MASK,	     COM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},

{"dcbtep",	XRT(31,319,0),	X_MASK,   E500MC|PPCA2|PPCVLE, PPCNONE,	{RT, RA0, RB},	NULL},

{"mfexisr",	XSPR(31,323, 64), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfexier",	XSPR(31,323, 66), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfbr0",	XSPR(31,323,128), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfbr1",	XSPR(31,323,129), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfbr2",	XSPR(31,323,130), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfbr3",	XSPR(31,323,131), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfbr4",	XSPR(31,323,132), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfbr5",	XSPR(31,323,133), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfbr6",	XSPR(31,323,134), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfbr7",	XSPR(31,323,135), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfbear",	XSPR(31,323,144), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfbesr",	XSPR(31,323,145), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfiocr",	XSPR(31,323,160), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmacr0",	XSPR(31,323,192), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmact0",	XSPR(31,323,193), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmada0",	XSPR(31,323,194), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmasa0",	XSPR(31,323,195), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmacc0",	XSPR(31,323,196), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmacr1",	XSPR(31,323,200), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmact1",	XSPR(31,323,201), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmada1",	XSPR(31,323,202), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmasa1",	XSPR(31,323,203), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmacc1",	XSPR(31,323,204), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmacr2",	XSPR(31,323,208), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmact2",	XSPR(31,323,209), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmada2",	XSPR(31,323,210), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmasa2",	XSPR(31,323,211), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmacc2",	XSPR(31,323,212), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmacr3",	XSPR(31,323,216), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmact3",	XSPR(31,323,217), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmada3",	XSPR(31,323,218), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmasa3",	XSPR(31,323,219), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmacc3",	XSPR(31,323,220), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdmasr",	XSPR(31,323,224), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdcr",	X(31,323), X_MASK, PPC403|BOOKE|PPCA2|PPC476|PPCVLE, TITAN, {RT, SPR},	NULL},
{"mfdcr.",	XRC(31,323,1),	X_MASK,      PPCA2,	PPCNONE,	{RT, SPR},	NULL},

{"lvexwx",	X(31,325),	X_MASK,      PPCVEC2,	PPCNONE,	{VD, RA0, RB},	NULL},

{"dcread",	X(31,326),	X_MASK,  PPC476|TITAN,	PPCNONE,	{RT, RA0, RB},	NULL},

{"div",		XO(31,331,0,0),	XO_MASK,     M601,	PPCNONE,	{RT, RA, RB},	NULL},
{"div.",	XO(31,331,0,1),	XO_MASK,     M601,	PPCNONE,	{RT, RA, RB},	NULL},

{"lxvdsx",	X(31,332),	XX1_MASK,    PPCVSX,	PPCNONE,	{XT6, RA0, RB},	NULL},

{"mfpmr",	X(31,334),	X_MASK, PPCPMR|PPCE300|PPCVLE, PPCNONE,	{RT, PMR},	NULL},
{"mftmr",	X(31,366),	X_MASK,	PPCTMR|E6500,	PPCNONE,	{RT, TMR},	NULL},

{"mfmq",	XSPR(31,339,  0), XSPR_MASK, M601,	PPCNONE,	{RT},	NULL},
{"mfxer",	XSPR(31,339,  1), XSPR_MASK, COM|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfrtcu",	XSPR(31,339,  4), XSPR_MASK, COM,	TITAN,  	{RT},	NULL},
{"mfrtcl",	XSPR(31,339,  5), XSPR_MASK, COM,	TITAN,  	{RT},	NULL},
{"mfdec",	XSPR(31,339,  6), XSPR_MASK, MFDEC1,	PPCNONE,	{RT},	NULL},
{"mflr",	XSPR(31,339,  8), XSPR_MASK, COM|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfctr",	XSPR(31,339,  9), XSPR_MASK, COM|PPCVLE, PPCNONE,	{RT},	NULL},
{"mftid",	XSPR(31,339, 17), XSPR_MASK, POWER,	PPCNONE,	{RT},	NULL},
{"mfdsisr",	XSPR(31,339, 18), XSPR_MASK, COM,	TITAN,  	{RT},	NULL},
{"mfdar",	XSPR(31,339, 19), XSPR_MASK, COM,	TITAN,  	{RT},	NULL},
{"mfdec",	XSPR(31,339, 22), XSPR_MASK, MFDEC2,	MFDEC1,		{RT},	translate_mfdec},
{"mfsdr0",	XSPR(31,339, 24), XSPR_MASK, POWER,	PPCNONE,	{RT},	NULL},
{"mfsdr1",	XSPR(31,339, 25), XSPR_MASK, COM,	TITAN,  	{RT},	NULL},
{"mfsrr0",	XSPR(31,339, 26), XSPR_MASK, COM|PPCVLE,	PPCNONE,	{RT},	NULL},
{"mfsrr1",	XSPR(31,339, 27), XSPR_MASK, COM|PPCVLE,	PPCNONE,	{RT},	NULL},
{"mfcfar",	XSPR(31,339, 28), XSPR_MASK, POWER6,	PPCNONE,	{RT},	NULL},
{"mfpid",	XSPR(31,339, 48), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfcsrr0",	XSPR(31,339, 58), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfcsrr1",	XSPR(31,339, 59), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfdear",	XSPR(31,339, 61), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfesr",	XSPR(31,339, 62), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivpr",	XSPR(31,339, 63), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfcmpa",	XSPR(31,339,144), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfcmpb",	XSPR(31,339,145), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfcmpc",	XSPR(31,339,146), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfcmpd",	XSPR(31,339,147), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mficr",	XSPR(31,339,148), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfder",	XSPR(31,339,149), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfcounta",	XSPR(31,339,150), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfcountb",	XSPR(31,339,151), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfcmpe",	XSPR(31,339,152), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfcmpf",	XSPR(31,339,153), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfcmpg",	XSPR(31,339,154), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfcmph",	XSPR(31,339,155), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mflctrl1",	XSPR(31,339,156), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mflctrl2",	XSPR(31,339,157), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfictrl",	XSPR(31,339,158), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfbar",	XSPR(31,339,159), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfvrsave",	XSPR(31,339,256), XSPR_MASK, PPCVEC,	PPCNONE,	{RT},	NULL},
{"mfusprg0",	XSPR(31,339,256), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfsprg",	XSPR(31,339,256), XSPRG_MASK, PPC|PPCVLE, PPCNONE,	{RT, SPRG},	NULL},
{"mfsprg4",	XSPR(31,339,260), XSPR_MASK, PPC405|BOOKE|PPCVLE, PPCNONE, {RT},	NULL},
{"mfsprg5",	XSPR(31,339,261), XSPR_MASK, PPC405|BOOKE|PPCVLE, PPCNONE, {RT},	NULL},
{"mfsprg6",	XSPR(31,339,262), XSPR_MASK, PPC405|BOOKE|PPCVLE, PPCNONE, {RT},	NULL},
{"mfsprg7",	XSPR(31,339,263), XSPR_MASK, PPC405|BOOKE|PPCVLE, PPCNONE, {RT},	NULL},
{"mftb",	XSPR(31,339,268), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mftbl",	XSPR(31,339,268), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mftbu",	XSPR(31,339,269), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfsprg0",	XSPR(31,339,272), XSPR_MASK, PPC|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfsprg1",	XSPR(31,339,273), XSPR_MASK, PPC|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfsprg2",	XSPR(31,339,274), XSPR_MASK, PPC|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfsprg3",	XSPR(31,339,275), XSPR_MASK, PPC|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfasr",	XSPR(31,339,280), XSPR_MASK, PPC64,	PPCNONE,	{RT},	NULL},
{"mfear",	XSPR(31,339,282), XSPR_MASK, PPC,	TITAN,  	{RT},	NULL},
{"mfpir",	XSPR(31,339,286), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfpvr",	XSPR(31,339,287), XSPR_MASK, PPC|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfdbsr",	XSPR(31,339,304), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfdbcr0",	XSPR(31,339,308), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfdbcr1",	XSPR(31,339,309), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfdbcr2",	XSPR(31,339,310), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfiac1",	XSPR(31,339,312), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfiac2",	XSPR(31,339,313), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfiac3",	XSPR(31,339,314), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfiac4",	XSPR(31,339,315), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfdac1",	XSPR(31,339,316), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfdac2",	XSPR(31,339,317), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfdvc1",	XSPR(31,339,318), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfdvc2",	XSPR(31,339,319), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mftsr",	XSPR(31,339,336), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mftcr",	XSPR(31,339,340), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivor0",	XSPR(31,339,400), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivor1",	XSPR(31,339,401), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivor2",	XSPR(31,339,402), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivor3",	XSPR(31,339,403), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivor4",	XSPR(31,339,404), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivor5",	XSPR(31,339,405), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivor6",	XSPR(31,339,406), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivor7",	XSPR(31,339,407), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivor8",	XSPR(31,339,408), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivor9",	XSPR(31,339,409), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivor10",	XSPR(31,339,410), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivor11",	XSPR(31,339,411), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivor12",	XSPR(31,339,412), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivor13",	XSPR(31,339,413), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivor14",	XSPR(31,339,414), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfivor15",	XSPR(31,339,415), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RT},	NULL},
{"mfspefscr",	XSPR(31,339,512), XSPR_MASK, PPCSPE,	PPCNONE,	{RT},	NULL},
{"mfbbear",	XSPR(31,339,513), XSPR_MASK, PPCBRLK,	PPCNONE,	{RT},	NULL},
{"mfbbtar",	XSPR(31,339,514), XSPR_MASK, PPCBRLK,	PPCNONE,	{RT},	NULL},
{"mfivor32",	XSPR(31,339,528), XSPR_MASK, PPCSPE,	PPCNONE,	{RT},	NULL},
{"mfibatu",	XSPR(31,339,528), XSPRBAT_MASK, PPC,	TITAN,  	{RT, SPRBAT},	NULL},
{"mfivor33",	XSPR(31,339,529), XSPR_MASK, PPCSPE,	PPCNONE,	{RT},	NULL},
{"mfibatl",	XSPR(31,339,529), XSPRBAT_MASK, PPC,	TITAN,  	{RT, SPRBAT},	NULL},
{"mfivor34",	XSPR(31,339,530), XSPR_MASK, PPCSPE,	PPCNONE,	{RT},	NULL},
{"mfivor35",	XSPR(31,339,531), XSPR_MASK, PPCPMR,	PPCNONE,	{RT},	NULL},
{"mfdbatu",	XSPR(31,339,536), XSPRBAT_MASK, PPC,	TITAN,  	{RT, SPRBAT},	NULL},
{"mfdbatl",	XSPR(31,339,537), XSPRBAT_MASK, PPC,	TITAN,  	{RT, SPRBAT},	NULL},
{"mfic_cst",	XSPR(31,339,560), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfic_adr",	XSPR(31,339,561), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfic_dat",	XSPR(31,339,562), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfdc_cst",	XSPR(31,339,568), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfdc_adr",	XSPR(31,339,569), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfdc_dat",	XSPR(31,339,570), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmcsrr0",	XSPR(31,339,570), XSPR_MASK, PPCRFMCI,	PPCNONE,	{RT},	NULL},
{"mfmcsrr1",	XSPR(31,339,571), XSPR_MASK, PPCRFMCI,	PPCNONE,	{RT},	NULL},
{"mfmcsr",	XSPR(31,339,572), XSPR_MASK, PPCRFMCI|PPCVLE,	PPCNONE,	{RT},	NULL},
{"mfmcar",	XSPR(31,339,573), XSPR_MASK, PPCRFMCI|PPCVLE,	TITAN,  	{RT},	NULL},
{"mfdpdr",	XSPR(31,339,630), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfdpir",	XSPR(31,339,631), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfimmr",	XSPR(31,339,638), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmi_ctr",	XSPR(31,339,784), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmi_ap",	XSPR(31,339,786), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmi_epn",	XSPR(31,339,787), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmi_twc",	XSPR(31,339,789), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmi_rpn",	XSPR(31,339,790), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmd_ctr",	XSPR(31,339,792), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfm_casid",	XSPR(31,339,793), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmd_ap",	XSPR(31,339,794), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmd_epn",	XSPR(31,339,795), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmd_twb",	XSPR(31,339,796), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmd_twc",	XSPR(31,339,797), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmd_rpn",	XSPR(31,339,798), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfm_tw",	XSPR(31,339,799), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmi_dbcam",	XSPR(31,339,816), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmi_dbram0",	XSPR(31,339,817), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmi_dbram1",	XSPR(31,339,818), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmd_dbcam",	XSPR(31,339,824), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmd_dbram0",	XSPR(31,339,825), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfmd_dbram1",	XSPR(31,339,826), XSPR_MASK, PPC860,	PPCNONE,	{RT},	NULL},
{"mfivndx",	XSPR(31,339,880), XSPR_MASK, TITAN,	PPCNONE,	{RT},	NULL},
{"mfdvndx",	XSPR(31,339,881), XSPR_MASK, TITAN,	PPCNONE,	{RT},	NULL},
{"mfivlim",	XSPR(31,339,882), XSPR_MASK, TITAN,	PPCNONE,	{RT},	NULL},
{"mfdvlim",	XSPR(31,339,883), XSPR_MASK, TITAN,	PPCNONE,	{RT},	NULL},
{"mfclcsr",	XSPR(31,339,884), XSPR_MASK, TITAN,	PPCNONE,	{RT},	NULL},
{"mfccr1",	XSPR(31,339,888), XSPR_MASK, TITAN,	PPCNONE,	{RT},	NULL},
{"mfppr",	XSPR(31,339,896), XSPR_MASK, POWER7,	PPCNONE,	{RT},	NULL},
{"mfppr32",	XSPR(31,339,898), XSPR_MASK, POWER7,	PPCNONE,	{RT},	NULL},
{"mfrstcfg",	XSPR(31,339,923), XSPR_MASK, TITAN,	PPCNONE,	{RT},	NULL},
{"mfdcdbtrl",	XSPR(31,339,924), XSPR_MASK, TITAN,	PPCNONE,	{RT},	NULL},
{"mfdcdbtrh",	XSPR(31,339,925), XSPR_MASK, TITAN,	PPCNONE,	{RT},	NULL},
{"mficdbtr",	XSPR(31,339,927), XSPR_MASK, TITAN,	PPCNONE,	{RT},	NULL},
{"mfummcr0",	XSPR(31,339,936), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfupmc1",	XSPR(31,339,937), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfupmc2",	XSPR(31,339,938), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfusia",	XSPR(31,339,939), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfummcr1",	XSPR(31,339,940), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfupmc3",	XSPR(31,339,941), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfupmc4",	XSPR(31,339,942), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfzpr",	XSPR(31,339,944), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfpid",	XSPR(31,339,945), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfmmucr",	XSPR(31,339,946), XSPR_MASK, TITAN,	PPCNONE,	{RT},	NULL},
{"mfccr0",	XSPR(31,339,947), XSPR_MASK, PPC405|TITAN, PPCNONE,	{RT},	NULL},
{"mfiac3",	XSPR(31,339,948), XSPR_MASK, PPC405,	PPCNONE,	{RT},	NULL},
{"mfiac4",	XSPR(31,339,949), XSPR_MASK, PPC405,	PPCNONE,	{RT},	NULL},
{"mfdvc1",	XSPR(31,339,950), XSPR_MASK, PPC405,	PPCNONE,	{RT},	NULL},
{"mfdvc2",	XSPR(31,339,951), XSPR_MASK, PPC405,	PPCNONE,	{RT},	NULL},
{"mfmmcr0",	XSPR(31,339,952), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfpmc1",	XSPR(31,339,953), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfsgr",	XSPR(31,339,953), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdcwr",	XSPR(31,339,954), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfpmc2",	XSPR(31,339,954), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfsia",	XSPR(31,339,955), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfsler",	XSPR(31,339,955), XSPR_MASK, PPC405,	PPCNONE,	{RT},	NULL},
{"mfmmcr1",	XSPR(31,339,956), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfsu0r",	XSPR(31,339,956), XSPR_MASK, PPC405,	PPCNONE,	{RT},	NULL},
{"mfdbcr1",	XSPR(31,339,957), XSPR_MASK, PPC405,	PPCNONE,	{RT},	NULL},
{"mfpmc3",	XSPR(31,339,957), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfpmc4",	XSPR(31,339,958), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mficdbdr",	XSPR(31,339,979), XSPR_MASK, PPC403|TITAN, PPCNONE,	{RT},	NULL},
{"mfesr",	XSPR(31,339,980), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdear",	XSPR(31,339,981), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfevpr",	XSPR(31,339,982), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfcdbcr",	XSPR(31,339,983), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mftsr",	XSPR(31,339,984), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mftcr",	XSPR(31,339,986), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfpit",	XSPR(31,339,987), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mftbhi",	XSPR(31,339,988), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mftblo",	XSPR(31,339,989), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfsrr2",	XSPR(31,339,990), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfsrr3",	XSPR(31,339,991), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdbsr",	XSPR(31,339,1008), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdbcr0",	XSPR(31,339,1010), XSPR_MASK, PPC405,	PPCNONE,	{RT},	NULL},
{"mfdbdr",	XSPR(31,339,1011), XSPR_MASK, TITAN,	PPCNONE,	{RS},	NULL},
{"mfiac1",	XSPR(31,339,1012), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfiac2",	XSPR(31,339,1013), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdac1",	XSPR(31,339,1014), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfdac2",	XSPR(31,339,1015), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfl2cr",	XSPR(31,339,1017), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfdccr",	XSPR(31,339,1018), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mficcr",	XSPR(31,339,1019), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfictc",	XSPR(31,339,1019), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfpbl1",	XSPR(31,339,1020), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfthrm1",	XSPR(31,339,1020), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfpbu1",	XSPR(31,339,1021), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfthrm2",	XSPR(31,339,1021), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfpbl2",	XSPR(31,339,1022), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfthrm3",	XSPR(31,339,1022), XSPR_MASK, PPC750,	PPCNONE,	{RT},	NULL},
{"mfpbu2",	XSPR(31,339,1023), XSPR_MASK, PPC403,	PPCNONE,	{RT},	NULL},
{"mfspr",	X(31,339),	X_MASK,      COM|PPCVLE, PPCNONE,	{RT, SPR},	NULL},
 
{"lwax",	X(31,341),	X_MASK,      PPC64|PPCVLE, PPCNONE,	{RT, RA0, RB},	NULL},

{"dst",		XDSS(31,342,0),	XDSS_MASK,   PPCVEC,	PPCNONE,	{RA, RB, STRM},	NULL},

{"lhax",	X(31,343),	X_MASK,      COM|PPCVLE, PPCNONE,	{RT, RA0, RB},	NULL},

{"lvxl",	X(31,359),	X_MASK,      PPCVEC|PPCVLE, PPCNONE,	{VD, RA0, RB},	NULL},

{"abs",		XO(31,360,0,0),	XORB_MASK,   M601,	PPCNONE,	{RT, RA},	NULL},
{"abs.",	XO(31,360,0,1),	XORB_MASK,   M601,	PPCNONE,	{RT, RA},	NULL},

{"divs",	XO(31,363,0,0),	XO_MASK,     M601,	PPCNONE,	{RT, RA, RB},	NULL},
{"divs.",	XO(31,363,0,1),	XO_MASK,     M601,	PPCNONE,	{RT, RA, RB},	NULL},

{"tlbia",	X(31,370),	0xffffffff,  PPC,	TITAN,  	{UNUSED},	NULL},

{"mftbl",	XSPR(31,371,268), XSPR_MASK, PPC,	NO371,		{RT},	NULL},
{"mftbu",	XSPR(31,371,269), XSPR_MASK, PPC,	NO371,		{RT},	NULL},
{"mftb",	X(31,371),	X_MASK,      PPC|PPCA2,	NO371|POWER7,	{RT, TBR},	NULL},

{"lwaux",	X(31,373),	X_MASK,      PPC64|PPCVLE, PPCNONE,	{RT, RAL, RB},	NULL},

{"dstst",	XDSS(31,374,0),	XDSS_MASK,   PPCVEC,	PPCNONE,	{RA, RB, STRM},	NULL},

{"lhaux",	X(31,375),	X_MASK,      COM|PPCVLE, PPCNONE,	{RT, RAL, RB},	NULL},

{"popcntw",	X(31,378),	XRB_MASK, POWER7|PPCA2,	PPCNONE,	{RA, RS},	NULL},

{"mtdcrx",	X(31,387),	X_MASK, BOOKE|PPCA2|PPC476|PPCVLE, TITAN, {RA, RS},	NULL},
{"mtdcrx.",	XRC(31,387,1),	X_MASK,	     PPCA2,	PPCNONE,	{RA, RS},	NULL},

{"stvexbx",	X(31,389),	X_MASK,      PPCVEC2,	PPCNONE,	{VS, RA0, RB},	NULL},

{"dcblc",	X(31,390),	X_MASK, PPCCHLK|PPC476|TITAN|PPCVLE, PPCNONE, {CT, RA0, RB},	NULL},
{"stdfcmx",	APU(31,391,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"divdeu",	XO(31,393,0,0),	XO_MASK,  POWER7|PPCA2,	PPCNONE,	{RT, RA, RB},	NULL},
{"divdeu.",	XO(31,393,0,1),	XO_MASK,  POWER7|PPCA2,	PPCNONE,	{RT, RA, RB},	NULL},
{"divweu",	XO(31,395,0,0),	XO_MASK,  POWER7|PPCA2,	PPCNONE,	{RT, RA, RB},	NULL},
{"divweu.",	XO(31,395,0,1),	XO_MASK,  POWER7|PPCA2,	PPCNONE,	{RT, RA, RB},	NULL},

{"dcblce",	X(31,398),	X_MASK,      PPCCHLK,	E500MC,		{CT, RA, RB},	NULL},

{"slbmte",	X(31,402),	XRA_MASK,    PPC64,	PPCNONE,	{RS, RB},	NULL},

{"pbt.",	XRC(31,404,1),	X_MASK,      POWER8,	PPCNONE,	{RS, RA0, RB},	NULL},

{"icswx",	XRC(31,406,0),	X_MASK,   POWER7|PPCA2,	PPCNONE,	{RS, RA, RB},	NULL},
{"icswx.",	XRC(31,406,1),	X_MASK,   POWER7|PPCA2,	PPCNONE,	{RS, RA, RB},	NULL},

{"sthx",	X(31,407),	X_MASK,      COM|PPCVLE, PPCNONE,	{RS, RA0, RB},	NULL},

{"orc",		XRC(31,412,0),	X_MASK,      COM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},
{"orc.",	XRC(31,412,1),	X_MASK,      COM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},

{"sthepx",	X(31,415),	X_MASK,      E500MC|PPCA2|PPCVLE, PPCNONE, {RS, RA0, RB},	NULL},

{"mtdcrux",	X(31,419),	X_MASK,      PPC464|PPCVLE, PPCNONE,	{RA, RS},	NULL},

{"stvexhx",	X(31,421),	X_MASK,      PPCVEC2,	PPCNONE,	{VS, RA0, RB},	NULL},

{"dcblq.",	XRC(31,422,1),	X_MASK,      E6500,	PPCNONE,	{CT, RA0, RB},	NULL},

{"divde",	XO(31,425,0,0),	XO_MASK,  POWER7|PPCA2,	PPCNONE,	{RT, RA, RB},	NULL},
{"divde.",	XO(31,425,0,1),	XO_MASK,  POWER7|PPCA2,	PPCNONE,	{RT, RA, RB},	NULL},
{"divwe",	XO(31,427,0,0),	XO_MASK,  POWER7|PPCA2,	PPCNONE,	{RT, RA, RB},	NULL},
{"divwe.",	XO(31,427,0,1),	XO_MASK,  POWER7|PPCA2,	PPCNONE,	{RT, RA, RB},	NULL},

{"clrbhrb",	X(31,430),	0xffffffff,  POWER8,	PPCNONE,	{UNUSED},	NULL},

{"slbie",	X(31,434),	XRTRA_MASK,  PPC64,	PPCNONE,	{RB},	NULL},

{"ecowx",	X(31,438),	X_MASK,      PPC,	TITAN,  	{RT, RA0, RB},	NULL},

{"sthux",	X(31,439),	X_MASK,      COM|PPCVLE, PPCNONE,	{RS, RAS, RB},	NULL},

{"mdors",	0x7f9ce378,	0xffffffff,  E500MC,	PPCNONE,	{UNUSED},	NULL},

{"miso",	0x7f5ad378,	0xffffffff,  E6500,	PPCNONE,	{UNUSED},	NULL},

/* The "yield", "mdoio" and "mdoom" instructions are extended mnemonics for
   "or rX,rX,rX", with rX being r27, r29 and r30 respectively.  */
{"yield",	0x7f7bdb78,	0xffffffff,  POWER7,	 PPCNONE,	{UNUSED},	NULL},
{"mdoio",	0x7fbdeb78,	0xffffffff,  POWER7,	 PPCNONE,	{UNUSED},	NULL},
{"mdoom",	0x7fdef378,	0xffffffff,  POWER7,	 PPCNONE,	{UNUSED},	NULL},
{"mr",		XRC(31,444,0),	X_MASK,      COM|PPCVLE, PPCNONE,	{RA, RS, RBS},	translate_mr},
{"or",		XRC(31,444,0),	X_MASK,      COM|PPCVLE, PPCNONE,	{RA, RS, RB},	translate_or},
{"mr.",		XRC(31,444,1),	X_MASK,      COM|PPCVLE, PPCNONE,	{RA, RS, RBS},	NULL},
{"or.",		XRC(31,444,1),	X_MASK,      COM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},

{"mtexisr",	XSPR(31,451, 64), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtexier",	XSPR(31,451, 66), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtbr0",	XSPR(31,451,128), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtbr1",	XSPR(31,451,129), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtbr2",	XSPR(31,451,130), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtbr3",	XSPR(31,451,131), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtbr4",	XSPR(31,451,132), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtbr5",	XSPR(31,451,133), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtbr6",	XSPR(31,451,134), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtbr7",	XSPR(31,451,135), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtbear",	XSPR(31,451,144), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtbesr",	XSPR(31,451,145), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtiocr",	XSPR(31,451,160), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmacr0",	XSPR(31,451,192), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmact0",	XSPR(31,451,193), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmada0",	XSPR(31,451,194), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmasa0",	XSPR(31,451,195), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmacc0",	XSPR(31,451,196), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmacr1",	XSPR(31,451,200), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmact1",	XSPR(31,451,201), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmada1",	XSPR(31,451,202), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmasa1",	XSPR(31,451,203), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmacc1",	XSPR(31,451,204), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmacr2",	XSPR(31,451,208), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmact2",	XSPR(31,451,209), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmada2",	XSPR(31,451,210), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmasa2",	XSPR(31,451,211), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmacc2",	XSPR(31,451,212), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmacr3",	XSPR(31,451,216), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmact3",	XSPR(31,451,217), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmada3",	XSPR(31,451,218), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmasa3",	XSPR(31,451,219), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmacc3",	XSPR(31,451,220), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdmasr",	XSPR(31,451,224), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdcr",	X(31,451), X_MASK, PPC403|BOOKE|PPCA2|PPC476|PPCVLE, TITAN, {SPR, RS},	NULL},
{"mtdcr.",	XRC(31,451,1), X_MASK,       PPCA2,	PPCNONE,	{SPR, RS},	NULL},

{"stvexwx",	X(31,453),	X_MASK,      PPCVEC2,	PPCNONE,	{VS, RA0, RB},	NULL},

{"dccci",	X(31,454), XRT_MASK, PPC403|PPC440|TITAN|PPCA2|PPCVLE, PPCNONE, {RAOPT, RBOPT},	NULL},
{"dci",		X(31,454),	XRARB_MASK, PPCA2|PPC476|PPCVLE, PPCNONE, {CT},	NULL},
 
{"divdu",	XO(31,457,0,0),	XO_MASK,  PPC64|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"divdu.",	XO(31,457,0,1),	XO_MASK,  PPC64|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},

{"divwu",	XO(31,459,0,0),	XO_MASK,  PPC|PPCVLE,	PPCNONE,	{RT, RA, RB},	NULL},
{"divwu.",	XO(31,459,0,1),	XO_MASK,  PPC|PPCVLE,	PPCNONE,	{RT, RA, RB},	NULL},

{"mtpmr",	X(31,462),	X_MASK, PPCPMR|PPCE300|PPCVLE, PPCNONE,	{PMR, RS},	NULL},
{"mttmr",	X(31,494),	X_MASK,	PPCTMR|E6500,	PPCNONE,	{TMR, RS},	NULL},

{"mtmq",	XSPR(31,467,  0), XSPR_MASK, M601,	PPCNONE,	{RS},	NULL},
{"mtxer",	XSPR(31,467,  1), XSPR_MASK, COM|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtlr",	XSPR(31,467,  8), XSPR_MASK, COM|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtctr", 	XSPR(31,467,  9), XSPR_MASK, COM|PPCVLE, PPCNONE,	{RS},	NULL},
{"mttid",	XSPR(31,467, 17), XSPR_MASK, POWER,	PPCNONE,	{RS},	NULL},
{"mtdsisr",	XSPR(31,467, 18), XSPR_MASK, COM,	TITAN,  	{RS},	NULL},
{"mtdar",	XSPR(31,467, 19), XSPR_MASK, COM,	TITAN,  	{RS},	NULL},
{"mtrtcu",	XSPR(31,467, 20), XSPR_MASK, COM,	TITAN,  	{RS},	NULL},
{"mtrtcl",	XSPR(31,467, 21), XSPR_MASK, COM,	TITAN,  	{RS},	NULL},
{"mtdec",	XSPR(31,467, 22), XSPR_MASK, COM,	PPCNONE,	{RS},	translate_mtdec},
{"mtsdr0",	XSPR(31,467, 24), XSPR_MASK, POWER,	PPCNONE,	{RS},	NULL},
{"mtsdr1",	XSPR(31,467, 25), XSPR_MASK, COM,	TITAN,  	{RS},	NULL},
{"mtsrr0",	XSPR(31,467, 26), XSPR_MASK, COM|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtsrr1",	XSPR(31,467, 27), XSPR_MASK, COM|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtcfar",	XSPR(31,467, 28), XSPR_MASK, POWER6,	PPCNONE,	{RS},	NULL},
{"mtpid",	XSPR(31,467, 48), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtdecar",	XSPR(31,467, 54), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtcsrr0",	XSPR(31,467, 58), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtcsrr1",	XSPR(31,467, 59), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtdear",	XSPR(31,467, 61), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtesr",	XSPR(31,467, 62), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivpr",	XSPR(31,467, 63), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtcmpa",	XSPR(31,467,144), XSPR_MASK, PPC860,	PPCNONE,	{RS},	NULL},
{"mtcmpb",	XSPR(31,467,145), XSPR_MASK, PPC860,	PPCNONE,	{RS},	NULL},
{"mtcmpc",	XSPR(31,467,146), XSPR_MASK, PPC860,	PPCNONE,	{RS},	NULL},
{"mtcmpd",	XSPR(31,467,147), XSPR_MASK, PPC860,	PPCNONE,	{RS},	NULL},
{"mticr",	XSPR(31,467,148), XSPR_MASK, PPC860,	PPCNONE,	{RS},	NULL},
{"mtder",	XSPR(31,467,149), XSPR_MASK, PPC860,	PPCNONE,	{RS},	NULL},
{"mtcounta",	XSPR(31,467,150), XSPR_MASK, PPC860,	PPCNONE,	{RS},	NULL},
{"mtcountb",	XSPR(31,467,151), XSPR_MASK, PPC860,	PPCNONE,	{RS},	NULL},
{"mtcmpe",	XSPR(31,467,152), XSPR_MASK, PPC860,	PPCNONE,	{RS},	NULL},
{"mtcmpf",	XSPR(31,467,153), XSPR_MASK, PPC860,	PPCNONE,	{RS},	NULL},
{"mtcmpg",	XSPR(31,467,154), XSPR_MASK, PPC860,	PPCNONE,	{RS},	NULL},
{"mtcmph",	XSPR(31,467,155), XSPR_MASK, PPC860,	PPCNONE,	{RS},	NULL},
{"mtlctrl1",	XSPR(31,467,156), XSPR_MASK, PPC860,	PPCNONE,	{RS},	NULL},
{"mtlctrl2",	XSPR(31,467,157), XSPR_MASK, PPC860,	PPCNONE,	{RS},	NULL},
{"mtictrl",	XSPR(31,467,158), XSPR_MASK, PPC860,	PPCNONE,	{RS},	NULL},
{"mtbar",	XSPR(31,467,159), XSPR_MASK, PPC860,	PPCNONE,	{RS},	NULL},
{"mtvrsave",	XSPR(31,467,256), XSPR_MASK, PPCVEC,	PPCNONE,	{RS},	NULL},
{"mtusprg0",	XSPR(31,467,256), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtsprg",	XSPR(31,467,256), XSPRG_MASK, PPC|PPCVLE, PPCNONE,	{SPRG, RS},	NULL},
{"mtsprg0",	XSPR(31,467,272), XSPR_MASK, PPC|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtsprg1",	XSPR(31,467,273), XSPR_MASK, PPC|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtsprg2",	XSPR(31,467,274), XSPR_MASK, PPC|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtsprg3",	XSPR(31,467,275), XSPR_MASK, PPC|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtsprg4",	XSPR(31,467,276), XSPR_MASK, PPC405|BOOKE|PPCVLE, PPCNONE, {RS},	NULL},
{"mtsprg5",	XSPR(31,467,277), XSPR_MASK, PPC405|BOOKE|PPCVLE, PPCNONE, {RS},	NULL},
{"mtsprg6",	XSPR(31,467,278), XSPR_MASK, PPC405|BOOKE|PPCVLE, PPCNONE, {RS},	NULL},
{"mtsprg7",	XSPR(31,467,279), XSPR_MASK, PPC405|BOOKE|PPCVLE, PPCNONE, {RS},	NULL},
{"mtasr",	XSPR(31,467,280), XSPR_MASK, PPC64,	PPCNONE,	{RS},	NULL},
{"mtear",	XSPR(31,467,282), XSPR_MASK, PPC,	TITAN,  	{RS},	NULL},
{"mttbl",	XSPR(31,467,284), XSPR_MASK, PPC,	PPCNONE,	{RS},	NULL},
{"mttbu",	XSPR(31,467,285), XSPR_MASK, PPC,	PPCNONE,	{RS},	NULL},
{"mtdbsr",	XSPR(31,467,304), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtdbcr0",	XSPR(31,467,308), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtdbcr1",	XSPR(31,467,309), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtdbcr2",	XSPR(31,467,310), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtiac1",	XSPR(31,467,312), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtiac2",	XSPR(31,467,313), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtiac3",	XSPR(31,467,314), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtiac4",	XSPR(31,467,315), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtdac1",	XSPR(31,467,316), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtdac2",	XSPR(31,467,317), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtdvc1",	XSPR(31,467,318), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtdvc2",	XSPR(31,467,319), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mttsr",	XSPR(31,467,336), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mttcr",	XSPR(31,467,340), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivor0",	XSPR(31,467,400), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivor1",	XSPR(31,467,401), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivor2",	XSPR(31,467,402), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivor3",	XSPR(31,467,403), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivor4",	XSPR(31,467,404), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivor5",	XSPR(31,467,405), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivor6",	XSPR(31,467,406), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivor7",	XSPR(31,467,407), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivor8",	XSPR(31,467,408), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivor9",	XSPR(31,467,409), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivor10",	XSPR(31,467,410), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivor11",	XSPR(31,467,411), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivor12",	XSPR(31,467,412), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivor13",	XSPR(31,467,413), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivor14",	XSPR(31,467,414), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtivor15",	XSPR(31,467,415), XSPR_MASK, BOOKE|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtspefscr",	XSPR(31,467,512), XSPR_MASK, PPCSPE,	PPCNONE,	{RS},	NULL},
{"mtbbear",	XSPR(31,467,513), XSPR_MASK, PPCBRLK,	PPCNONE,	{RS},	NULL},
{"mtbbtar",	XSPR(31,467,514), XSPR_MASK, PPCBRLK,	PPCNONE,	{RS},	NULL},
{"mtivor32",	XSPR(31,467,528), XSPR_MASK, PPCSPE,	PPCNONE,	{RS},	NULL},
{"mtibatu",	XSPR(31,467,528), XSPRBAT_MASK, PPC,	TITAN,  	{SPRBAT, RS},	NULL},
{"mtivor33",	XSPR(31,467,529), XSPR_MASK, PPCSPE,	PPCNONE,	{RS},	NULL},
{"mtibatl",	XSPR(31,467,529), XSPRBAT_MASK, PPC,	TITAN,  	{SPRBAT, RS},	NULL},
{"mtivor34",	XSPR(31,467,530), XSPR_MASK, PPCSPE,	PPCNONE,	{RS},	NULL},
{"mtivor35",	XSPR(31,467,531), XSPR_MASK, PPCPMR,	PPCNONE,	{RS},	NULL},
{"mtdbatu",	XSPR(31,467,536), XSPRBAT_MASK, PPC,	TITAN,  	{SPRBAT, RS},	NULL},
{"mtdbatl",	XSPR(31,467,537), XSPRBAT_MASK, PPC,	TITAN,  	{SPRBAT, RS},	NULL},
{"mtmcsrr0",	XSPR(31,467,570), XSPR_MASK, PPCRFMCI|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtmcsrr1",	XSPR(31,467,571), XSPR_MASK, PPCRFMCI|PPCVLE, PPCNONE,	{RS},	NULL},
{"mtmcsr",	XSPR(31,467,572), XSPR_MASK, PPCRFMCI|PPCVLE,	PPCNONE,	{RS},	NULL},
{"mtivndx",	XSPR(31,467,880), XSPR_MASK, TITAN,	PPCNONE,	{RS},	NULL},
{"mtdvndx",	XSPR(31,467,881), XSPR_MASK, TITAN,	PPCNONE,	{RS},	NULL},
{"mtivlim",	XSPR(31,467,882), XSPR_MASK, TITAN,	PPCNONE,	{RS},	NULL},
{"mtdvlim",	XSPR(31,467,883), XSPR_MASK, TITAN,	PPCNONE,	{RS},	NULL},
{"mtclcsr",	XSPR(31,467,884), XSPR_MASK, TITAN,	PPCNONE,	{RS},	NULL},
{"mtccr1",	XSPR(31,467,888), XSPR_MASK, TITAN,	PPCNONE,	{RS},	NULL},
{"mtppr",	XSPR(31,467,896), XSPR_MASK, POWER7,	PPCNONE,	{RS},	NULL},
{"mtppr32",	XSPR(31,467,898), XSPR_MASK, POWER7,	PPCNONE,	{RS},	NULL},
{"mtummcr0",	XSPR(31,467,936), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtupmc1",	XSPR(31,467,937), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtupmc2",	XSPR(31,467,938), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtusia",	XSPR(31,467,939), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtummcr1",	XSPR(31,467,940), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtupmc3",	XSPR(31,467,941), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtupmc4",	XSPR(31,467,942), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtzpr",	XSPR(31,467,944), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtpid",	XSPR(31,467,945), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtrmmucr",	XSPR(31,467,946), XSPR_MASK, TITAN,	PPCNONE,	{RS},	NULL},
{"mtccr0",	XSPR(31,467,947), XSPR_MASK, PPC405|TITAN, PPCNONE,	{RS},	NULL},
{"mtiac3",	XSPR(31,467,948), XSPR_MASK, PPC405,	PPCNONE,	{RS},	NULL},
{"mtiac4",	XSPR(31,467,949), XSPR_MASK, PPC405,	PPCNONE,	{RS},	NULL},
{"mtdvc1",	XSPR(31,467,950), XSPR_MASK, PPC405,	PPCNONE,	{RS},	NULL},
{"mtdvc2",	XSPR(31,467,951), XSPR_MASK, PPC405,	PPCNONE,	{RS},	NULL},
{"mtmmcr0",	XSPR(31,467,952), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtpmc1",	XSPR(31,467,953), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtsgr",	XSPR(31,467,953), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdcwr",	XSPR(31,467,954), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtpmc2",	XSPR(31,467,954), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtsia",	XSPR(31,467,955), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtsler",	XSPR(31,467,955), XSPR_MASK, PPC405,	PPCNONE,	{RS},	NULL},
{"mtmmcr1",	XSPR(31,467,956), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtsu0r",	XSPR(31,467,956), XSPR_MASK, PPC405,	PPCNONE,	{RS},	NULL},
{"mtdbcr1",	XSPR(31,467,957), XSPR_MASK, PPC405,	PPCNONE,	{RS},	NULL},
{"mtpmc3",	XSPR(31,467,957), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtpmc4",	XSPR(31,467,958), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mticdbdr",	XSPR(31,467,979), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtesr",	XSPR(31,467,980), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdear",	XSPR(31,467,981), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtevpr",	XSPR(31,467,982), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtcdbcr",	XSPR(31,467,983), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mttsr",	XSPR(31,467,984), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mttcr",	XSPR(31,467,986), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtpit",	XSPR(31,467,987), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mttbhi",	XSPR(31,467,988), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mttblo",	XSPR(31,467,989), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtsrr2",	XSPR(31,467,990), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtsrr3",	XSPR(31,467,991), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdbsr",	XSPR(31,467,1008), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdbdr",	XSPR(31,467,1011), XSPR_MASK, TITAN,	PPCNONE,	{RS},	NULL},
{"mtdbcr0",	XSPR(31,467,1010), XSPR_MASK, PPC405,	PPCNONE,	{RS},	NULL},
{"mtiac1",	XSPR(31,467,1012), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtiac2",	XSPR(31,467,1013), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdac1",	XSPR(31,467,1014), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtdac2",	XSPR(31,467,1015), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtl2cr",	XSPR(31,467,1017), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtdccr",	XSPR(31,467,1018), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mticcr",	XSPR(31,467,1019), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtictc",	XSPR(31,467,1019), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtpbl1",	XSPR(31,467,1020), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtthrm1",	XSPR(31,467,1020), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtpbu1",	XSPR(31,467,1021), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtthrm2",	XSPR(31,467,1021), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtpbl2",	XSPR(31,467,1022), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtthrm3",	XSPR(31,467,1022), XSPR_MASK, PPC750,	PPCNONE,	{RS},	NULL},
{"mtpbu2",	XSPR(31,467,1023), XSPR_MASK, PPC403,	PPCNONE,	{RS},	NULL},
{"mtspr",	X(31,467),	X_MASK,      COM|PPCVLE, PPCNONE,	{SPR, RS},	NULL},
 
{"dcbi",	X(31,470),	XRT_MASK,    PPC|PPCVLE, PPCNONE,	{RA0, RB},	NULL},

{"nand",	XRC(31,476,0),	X_MASK,      COM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},
{"nand.",	XRC(31,476,1),	X_MASK,      COM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},

{"dsn", 	X(31,483),	XRT_MASK,    E500MC|PPCVLE, PPCNONE,	{RA, RB},	NULL},

{"dcread",	X(31,486),	X_MASK,  PPC403|PPC440|PPCVLE, PPCA2|PPC476, {RT, RA0, RB},	NULL},

{"icbtls",	X(31,486),	X_MASK, PPCCHLK|PPC476|TITAN|PPCVLE, PPCNONE, {CT, RA0, RB},	NULL},

{"stvxl",	X(31,487),	X_MASK,      PPCVEC|PPCVLE, PPCNONE,	{VS, RA0, RB},	NULL},

{"nabs",	XO(31,488,0,0),	XORB_MASK,   M601,	PPCNONE,	{RT, RA},	NULL},
{"nabs.",	XO(31,488,0,1),	XORB_MASK,   M601,	PPCNONE,	{RT, RA},	NULL},

{"divd",	XO(31,489,0,0),	XO_MASK,     PPC64|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"divd.",	XO(31,489,0,1),	XO_MASK,     PPC64|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},

{"divw",	XO(31,491,0,0),	XO_MASK,     PPC|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"divw.",	XO(31,491,0,1),	XO_MASK,     PPC|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},

{"icbtlse",	X(31,494),	X_MASK,      PPCCHLK,	E500MC,		{CT, RA, RB},	NULL},

{"slbia",	X(31,498),	0xffffffff,  PPC64,	PPCNONE,	{UNUSED},	NULL},

{"cli",		X(31,502),	XRB_MASK,    POWER,	PPCNONE,	{RT, RA},	NULL},

{"popcntd",	X(31,506),	XRB_MASK, POWER7|PPCA2,	PPCNONE,	{RA, RS},	NULL},

{"cmpb",	X(31,508),	X_MASK, POWER6|PPCA2|PPC476, PPCNONE,	{RA, RS, RB},	NULL},

{"mcrxr",	X(31,512), XRARB_MASK|(3<<21), COM|PPCVLE, POWER7,	{BF},	NULL},

{"lbdx",	X(31,515),	X_MASK,      E500MC|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},

{"bblels",	X(31,518),	X_MASK,      PPCBRLK,	PPCNONE,	{UNUSED},	NULL},

{"lvlx",	X(31,519),	X_MASK,      CELL,	PPCNONE,	{VD, RA0, RB},	NULL},
{"lbfcmux",	APU(31,519,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"subfco",	XO(31,8,1,0),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"sfo",		XO(31,8,1,0),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},
{"subco",	XO(31,8,1,0),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RB, RA},	NULL},
{"subfco.",	XO(31,8,1,1),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"sfo.",	XO(31,8,1,1),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},
{"subco.",	XO(31,8,1,1),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RB, RA},	NULL},
 
{"addco",	XO(31,10,1,0),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"ao",		XO(31,10,1,0),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},
{"addco.",	XO(31,10,1,1),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"ao.",		XO(31,10,1,1),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},

{"lxsspx",	X(31,524),	XX1_MASK,    PPCVSX2,	PPCNONE,	{XT6, RA0, RB},	NULL},

{"clcs",	X(31,531),	XRB_MASK,    M601,	PPCNONE,	{RT, RA},	NULL},

{"ldbrx",	X(31,532),	X_MASK, CELL|POWER7|PPCA2, PPCNONE,	{RT, RA0, RB},	NULL},

{"lswx",	X(31,533),	X_MASK,  PPCCOM|PPCVLE, E500|E500MC,	{RT, RAX, RBX},	NULL},
{"lsx",		X(31,533),	X_MASK,      PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},

{"lwbrx",	X(31,534),	X_MASK,  PPCCOM|PPCVLE, PPCNONE,	{RT, RA0, RB},	NULL},
{"lbrx",	X(31,534),	X_MASK,      PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},

{"lfsx",	X(31,535),	X_MASK,      COM,	PPCEFS,		{FRT, RA0, RB},	NULL},

{"srw",		XRC(31,536,0),	X_MASK,  PPCCOM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},
{"sr",		XRC(31,536,0),	X_MASK,      PWRCOM,	PPCNONE,	{RA, RS, RB},	NULL},
{"srw.",	XRC(31,536,1),	X_MASK,  PPCCOM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},
{"sr.",		XRC(31,536,1),	X_MASK,      PWRCOM,	PPCNONE,	{RA, RS, RB},	NULL},

{"rrib",	XRC(31,537,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},
{"rrib.",	XRC(31,537,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},

{"srd",		XRC(31,539,0),	X_MASK,      PPC64|PPCVLE,	PPCNONE,	{RA, RS, RB},	NULL},
{"srd.",	XRC(31,539,1),	X_MASK,      PPC64|PPCVLE,	PPCNONE,	{RA, RS, RB},	NULL},

{"maskir",	XRC(31,541,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},
{"maskir.",	XRC(31,541,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},

{"lhdx",	X(31,547),	X_MASK,      E500MC|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},

{"lvtrx",	X(31,549),	X_MASK,      PPCVEC2,	PPCNONE,	{VD, RA0, RB},	NULL},

{"bbelr",	X(31,550),	X_MASK,      PPCBRLK,	PPCNONE,	{UNUSED},	NULL},

{"lvrx",	X(31,551),	X_MASK,      CELL,	PPCNONE,	{VD, RA0, RB},	NULL},
{"lhfcmux",	APU(31,551,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"subfo",	XO(31,40,1,0),	XO_MASK,     PPC|PPCVLE,	PPCNONE,	{RT, RA, RB},	NULL},
{"subo",	XO(31,40,1,0),	XO_MASK,     PPC|PPCVLE,	PPCNONE,	{RT, RB, RA},	NULL},
{"subfo.",	XO(31,40,1,1),	XO_MASK,     PPC|PPCVLE,	PPCNONE,	{RT, RA, RB},	NULL},
{"subo.",	XO(31,40,1,1),	XO_MASK,     PPC|PPCVLE,	PPCNONE,	{RT, RB, RA},	NULL},

{"tlbsync",	X(31,566),	0xffffffff, PPC|PPCVLE, PPCNONE,	{UNUSED},	NULL},

{"lfsux",	X(31,567),	X_MASK,      COM,	PPCEFS,		{FRT, RAS, RB},	NULL},

{"lwdx",	X(31,579),	X_MASK,      E500MC|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},

{"lvtlx",	X(31,581),	X_MASK,      PPCVEC2,	PPCNONE,	{VD, RA0, RB},	NULL},

{"lwfcmux",	APU(31,583,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"lxsdx",	X(31,588),	XX1_MASK,    PPCVSX,	PPCNONE,	{XT6, RA0, RB},	NULL},

{"mfsr",	X(31,595), XRB_MASK|(1<<20), COM,	NON32,  	{RT, SR},	NULL},

{"lswi",	X(31,597),	X_MASK,  PPCCOM|PPCVLE, E500|E500MC,	{RT, RAX, NBI},	NULL},
{"lsi",		X(31,597),	X_MASK,      PWRCOM,	PPCNONE,	{RT, RA0, NB},	NULL},

{"lwsync",	XSYNC(31,598,1), 0xffffffff, PPC,	E500,		{UNUSED},	NULL},
{"ptesync",	XSYNC(31,598,2), 0xffffffff, PPC64,	PPCNONE,	{UNUSED},	NULL},
{"sync",	X(31,598),	XSYNCLE_MASK,E6500,	PPCNONE,	{LS, ESYNC},	NULL},
{"sync",	X(31,598),	XSYNC_MASK, PPCCOM|PPCVLE, BOOKE|PPC476, {LS},	NULL},
{"msync",	X(31,598),	XSYNC_MASK, PPCVLE,      BOOKE|PPC476, {LS},	NULL},
{"msync",	X(31,598),	0xffffffff, BOOKE|PPCA2|PPC476, PPCNONE, {UNUSED},	NULL},
{"sync",	X(31,598),	0xffffffff, BOOKE|PPC476, E6500,	{UNUSED},	NULL},
{"lwsync",	X(31,598),	0xffffffff, E500,	PPCNONE,	{UNUSED},	NULL},
{"dcs",		X(31,598),	0xffffffff,  PWRCOM,	PPCNONE,	{UNUSED},	NULL},

{"lfdx",	X(31,599),	X_MASK,      COM,	PPCEFS,		{FRT, RA0, RB},	NULL},

{"mffgpr",	XRC(31,607,0),	XRA_MASK,    POWER6,	POWER7,		{FRT, RB},	NULL},
{"lfdepx",	X(31,607),	X_MASK,   E500MC|PPCA2|PPCVLE, PPCNONE, {FRT, RA0, RB},	NULL},

{"lddx",	X(31,611),	X_MASK,      E500MC|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},

{"lvswx",	X(31,613),	X_MASK,      PPCVEC2,	PPCNONE,	{VD, RA0, RB},	NULL},

{"lqfcmux",	APU(31,615,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"nego",	XO(31,104,1,0),	XORB_MASK,   COM|PPCVLE, PPCNONE,	{RT, RA},	NULL},
{"nego.",	XO(31,104,1,1),	XORB_MASK,   COM|PPCVLE, PPCNONE,	{RT, RA},	NULL},

{"mulo",	XO(31,107,1,0),	XO_MASK,     M601,	PPCNONE,	{RT, RA, RB},	NULL},
{"mulo.",	XO(31,107,1,1),	XO_MASK,     M601,	PPCNONE,	{RT, RA, RB},	NULL},

{"mfsri",	X(31,627),	X_MASK,      M601,	PPCNONE,	{RT, RA, RB},	NULL},

{"dclst",	X(31,630),	XRB_MASK,    M601,	PPCNONE,	{RS, RA},	NULL},

{"lfdux",	X(31,631),	X_MASK,      COM,	PPCEFS,		{FRT, RAS, RB},	NULL},

{"stbdx",	X(31,643),	X_MASK,      E500MC|PPCVLE,	PPCNONE,	{RS, RA, RB},	NULL},

{"stvlx",	X(31,647),	X_MASK,      CELL,	PPCNONE,	{VS, RA0, RB},	NULL},
{"stbfcmux",	APU(31,647,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"stxsspx",	X(31,652),	XX1_MASK,    PPCVSX2,	PPCNONE,	{XS6, RA0, RB},	NULL},

{"tbegin.",	XRC(31,654,1), XRTLRARB_MASK,PPCHTM,	PPCNONE,	{HTM_R},	NULL},

{"subfeo",	XO(31,136,1,0),	XO_MASK, PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"sfeo",	XO(31,136,1,0),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},
{"subfeo.",	XO(31,136,1,1),	XO_MASK, PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"sfeo.",	XO(31,136,1,1),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},

{"addeo",	XO(31,138,1,0),	XO_MASK, PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"aeo",		XO(31,138,1,0),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},
{"addeo.",	XO(31,138,1,1),	XO_MASK, PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"aeo.",	XO(31,138,1,1),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},

{"mfsrin",	X(31,659),	XRA_MASK,    PPC,	NON32,  	{RT, RB},	NULL},

{"stdbrx",	X(31,660),	X_MASK, CELL|POWER7|PPCA2, PPCNONE,	{RS, RA0, RB},	NULL},

{"stswx",	X(31,661),	X_MASK, PPCCOM|PPCVLE,	E500|E500MC,	{RS, RA0, RB},	NULL},
{"stsx",	X(31,661),	X_MASK,      PWRCOM,	PPCNONE,	{RS, RA0, RB},	NULL},

{"stwbrx",	X(31,662),	X_MASK, PPCCOM|PPCVLE,	PPCNONE,	{RS, RA0, RB},	NULL},
{"stbrx",	X(31,662),	X_MASK,      PWRCOM,	PPCNONE,	{RS, RA0, RB},	NULL},

{"stfsx",	X(31,663),	X_MASK,      COM,	PPCEFS,		{FRS, RA0, RB},	NULL},

{"srq",		XRC(31,664,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},
{"srq.",	XRC(31,664,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},

{"sre",		XRC(31,665,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},
{"sre.",	XRC(31,665,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},

{"sthdx",	X(31,675),	X_MASK,      E500MC|PPCVLE,	PPCNONE,	{RS, RA, RB},	NULL},

{"stvfrx",	X(31,677),	X_MASK,      PPCVEC2,	PPCNONE,	{VS, RA0, RB},	NULL},

{"stvrx",	X(31,679),	X_MASK,      CELL,	PPCNONE,	{VS, RA0, RB},	NULL},
{"sthfcmux",	APU(31,679,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"tendall.",	XRC(31,686,1)|(1<<25), XRTRARB_MASK, PPCHTM, PPCNONE,	{UNUSED},	NULL},
{"tend.",	XRC(31,686,1), XRTARARB_MASK, PPCHTM,	PPCNONE,	{HTM_A},	NULL},

{"stbcx.",	XRC(31,694,1),	X_MASK,      POWER7|PPCVLE,	PPCNONE,	{RS, RA0, RB},	NULL},

{"stfsux",	X(31,695),	X_MASK,      COM,	PPCEFS,		{FRS, RAS, RB},	NULL},

{"sriq",	XRC(31,696,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, SH},	NULL},
{"sriq.",	XRC(31,696,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, SH},	NULL},

{"stwdx",	X(31,707),	X_MASK,      E500MC|PPCVLE,	PPCNONE,	{RS, RA, RB},	NULL},

{"stvflx",	X(31,709),	X_MASK,      PPCVEC2,	PPCNONE,	{VS, RA0, RB},	NULL},

{"stwfcmux",	APU(31,711,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"stxsdx",	X(31,716),	XX1_MASK,    PPCVSX,	PPCNONE,	{XS6, RA0, RB},	NULL},

{"tcheck",	X(31,718),   XRTBFRARB_MASK, PPCHTM,	PPCNONE,	{BF},	NULL},

{"subfzeo",	XO(31,200,1,0),	XORB_MASK, PPCCOM|PPCVLE, PPCNONE,	{RT, RA},	NULL},
{"sfzeo",	XO(31,200,1,0),	XORB_MASK,   PWRCOM,	PPCNONE,	{RT, RA},	NULL},
{"subfzeo.",	XO(31,200,1,1),	XORB_MASK, PPCCOM|PPCVLE, PPCNONE,	{RT, RA},	NULL},
{"sfzeo.",	XO(31,200,1,1),	XORB_MASK,   PWRCOM,	PPCNONE,	{RT, RA},	NULL},

{"addzeo",	XO(31,202,1,0),	XORB_MASK, PPCCOM|PPCVLE, PPCNONE,	{RT, RA},	NULL},
{"azeo",	XO(31,202,1,0),	XORB_MASK,   PWRCOM,	PPCNONE,	{RT, RA},	NULL},
{"addzeo.",	XO(31,202,1,1),	XORB_MASK, PPCCOM|PPCVLE, PPCNONE,	{RT, RA},	NULL},
{"azeo.",	XO(31,202,1,1),	XORB_MASK,   PWRCOM,	PPCNONE,	{RT, RA},	NULL},

{"stswi",	X(31,725),	X_MASK, PPCCOM|PPCVLE,	E500|E500MC,	{RS, RA0, NB},	NULL},
{"stsi",	X(31,725),	X_MASK,      PWRCOM,	PPCNONE,	{RS, RA0, NB},	NULL},

{"sthcx.",	XRC(31,726,1),	X_MASK,      POWER7|PPCVLE,	PPCNONE,	{RS, RA0, RB},	NULL},

{"stfdx",	X(31,727),	X_MASK,      COM,	PPCEFS,		{FRS, RA0, RB},	NULL},

{"srlq",	XRC(31,728,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},
{"srlq.",	XRC(31,728,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},

{"sreq",	XRC(31,729,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},
{"sreq.",	XRC(31,729,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},

{"mftgpr",	XRC(31,735,0),	XRA_MASK,    POWER6,	POWER7,		{RT, FRB},	NULL},
{"stfdepx",	X(31,735),	X_MASK, E500MC|PPCA2|PPCVLE, PPCNONE,	{FRS, RA0, RB},	NULL},

{"stddx",	X(31,739),	X_MASK,      E500MC|PPCVLE,	PPCNONE,	{RS, RA, RB},	NULL},

{"stvswx",	X(31,741),	X_MASK,      PPCVEC2,	PPCNONE,	{VS, RA0, RB},	NULL},

{"stqfcmux",	APU(31,743,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"subfmeo",	XO(31,232,1,0),	XORB_MASK,   PPCCOM|PPCVLE,	PPCNONE,	{RT, RA},	NULL},
{"sfmeo",	XO(31,232,1,0),	XORB_MASK,   PWRCOM,	PPCNONE,	{RT, RA},	NULL},
{"subfmeo.",	XO(31,232,1,1),	XORB_MASK,   PPCCOM|PPCVLE,	PPCNONE,	{RT, RA},	NULL},
{"sfmeo.",	XO(31,232,1,1),	XORB_MASK,   PWRCOM,	PPCNONE,	{RT, RA},	NULL},

{"mulldo",	XO(31,233,1,0),	XO_MASK,  PPC64|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"mulldo.",	XO(31,233,1,1),	XO_MASK,  PPC64|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},

{"addmeo",	XO(31,234,1,0),	XORB_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RT, RA},	NULL},
{"ameo",	XO(31,234,1,0),	XORB_MASK,   PWRCOM,	PPCNONE,	{RT, RA},	NULL},
{"addmeo.",	XO(31,234,1,1),	XORB_MASK,   PPCCOM|PPCVLE, PPCNONE,	{RT, RA},	NULL},
{"ameo.",	XO(31,234,1,1),	XORB_MASK,   PWRCOM,	PPCNONE,	{RT, RA},	NULL},

{"mullwo",	XO(31,235,1,0),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"mulso",	XO(31,235,1,0),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},
{"mullwo.",	XO(31,235,1,1),	XO_MASK,     PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"mulso.",	XO(31,235,1,1),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},

{"tsuspend.",	XRCL(31,750,0,1), XRTRARB_MASK,PPCHTM,	PPCNONE,	{UNUSED},	NULL},
{"tresume.",	XRCL(31,750,1,1), XRTRARB_MASK,PPCHTM,	PPCNONE,	{UNUSED},	NULL},
{"tsr.",	XRC(31,750,1),    XRTLRARB_MASK,PPCHTM,	PPCNONE,	{L},	NULL},

{"dcba",	X(31,758), XRT_MASK, PPC405|PPC7450|BOOKE|PPCA2|PPC476|PPCVLE, PPCNONE, {RA0, RB},	NULL},
{"dcbal",	XOPL(31,758,1), XRT_MASK,    E500MC,	PPCNONE,	{RA0, RB},	NULL},

{"stfdux",	X(31,759),	X_MASK,      COM,	PPCEFS,		{FRS, RAS, RB},	NULL},

{"srliq",	XRC(31,760,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, SH},	NULL},
{"srliq.",	XRC(31,760,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, SH},	NULL},

{"lvsm",	X(31,773),	X_MASK,      PPCVEC2,	PPCNONE,	{VD, RA0, RB},	NULL},
{"stvepxl",	X(31,775),	X_MASK,      PPCVEC2|PPCVLE,	PPCNONE,	{VS, RA0, RB},	NULL},
{"lvlxl",	X(31,775),	X_MASK,      CELL,	PPCNONE,	{VD, RA0, RB},	NULL},
{"ldfcmux",	APU(31,775,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"dozo",	XO(31,264,1,0),	XO_MASK,     M601,	PPCNONE,	{RT, RA, RB},	NULL},
{"dozo.",	XO(31,264,1,1),	XO_MASK,     M601,	PPCNONE,	{RT, RA, RB},	NULL},

{"addo",	XO(31,266,1,0),	XO_MASK, PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"caxo",	XO(31,266,1,0),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},
{"addo.",	XO(31,266,1,1),	XO_MASK, PPCCOM|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"caxo.",	XO(31,266,1,1),	XO_MASK,     PWRCOM,	PPCNONE,	{RT, RA, RB},	NULL},

{"lxvw4x",	X(31,780),	XX1_MASK,    PPCVSX,	PPCNONE,	{XT6, RA0, RB},	NULL},

{"tabortwc.",	XRC(31,782,1),	X_MASK,      PPCHTM,	PPCNONE,	{TO, RA, RB},	NULL},

{"tlbivax",	X(31,786),	XRT_MASK, BOOKE|PPCA2|PPC476|PPCVLE, PPCNONE, {RA0, RB},	NULL},

{"lwzcix",	X(31,789),	X_MASK,      POWER6,	PPCNONE,	{RT, RA0, RB},	NULL},

{"lhbrx",	X(31,790),	X_MASK,      COM|PPCVLE, PPCNONE,	{RT, RA0, RB},	NULL},

{"lfdpx",	X(31,791),	X_MASK,      POWER6,	POWER7,		{FRTp, RA0, RB},	NULL},
{"lfqx",	X(31,791),	X_MASK,      POWER2,	PPCNONE,	{FRT, RA, RB},	NULL},

{"sraw",	XRC(31,792,0),	X_MASK,  PPCCOM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},
{"sra",		XRC(31,792,0),	X_MASK,      PWRCOM,	PPCNONE,	{RA, RS, RB},	NULL},
{"sraw.",	XRC(31,792,1),	X_MASK,	 PPCCOM|PPCVLE, PPCNONE,	{RA, RS, RB},	NULL},
{"sra.",	XRC(31,792,1),	X_MASK,      PWRCOM,	PPCNONE,	{RA, RS, RB},	NULL},

{"srad",	XRC(31,794,0),	X_MASK,      PPC64|PPCVLE,	PPCNONE,	{RA, RS, RB},	NULL},
{"srad.",	XRC(31,794,1),	X_MASK,      PPC64|PPCVLE,	PPCNONE,	{RA, RS, RB},	NULL},

{"lfddx",	X(31,803),	X_MASK,      E500MC|PPCVLE, PPCNONE,	{FRT, RA, RB},	NULL},

{"lvtrxl",	X(31,805),	X_MASK,      PPCVEC2,	PPCNONE,	{VD, RA0, RB},	NULL},
{"stvepx",	X(31,807),	X_MASK,      PPCVEC2|PPCVLE,	PPCNONE,	{VS, RA0, RB},	NULL},
{"lvrxl",	X(31,807),	X_MASK,      CELL,	PPCNONE,	{VD, RA0, RB},	NULL},

{"tabortdc.",	XRC(31,814,1),	X_MASK,      PPCHTM,	PPCNONE,	{TO, RA, RB},	NULL},

{"rac",		X(31,818),	X_MASK,      M601,	PPCNONE,	{RT, RA, RB},	NULL},

{"erativax",	X(31,819),	X_MASK,	     PPCA2,	PPCNONE,	{RS, RA0, RB},	NULL},

{"lhzcix",	X(31,821),	X_MASK,      POWER6,	PPCNONE,	{RT, RA0, RB},	NULL},

{"dss",		XDSS(31,822,0),	XDSS_MASK,   PPCVEC,	PPCNONE,	{STRM},	NULL},

{"lfqux",	X(31,823),	X_MASK,      POWER2,	PPCNONE,	{FRT, RA, RB},	NULL},

{"srawi",	XRC(31,824,0),	X_MASK,  PPCCOM|PPCVLE, PPCNONE,	{RA, RS, SH},	NULL},
{"srai",	XRC(31,824,0),	X_MASK,      PWRCOM,	PPCNONE,	{RA, RS, SH},	NULL},
{"srawi.",	XRC(31,824,1),	X_MASK,	 PPCCOM|PPCVLE, PPCNONE,	{RA, RS, SH},	NULL},
{"srai.",	XRC(31,824,1),	X_MASK,      PWRCOM,	PPCNONE,	{RA, RS, SH},	NULL},

{"sradi",	XS(31,413,0),	XS_MASK,     PPC64|PPCVLE, PPCNONE,	{RA, RS, SH6},	NULL},
{"sradi.",	XS(31,413,1),	XS_MASK,     PPC64|PPCVLE, PPCNONE,	{RA, RS, SH6},	NULL},

{"lvtlxl",	X(31,837),	X_MASK,      PPCVEC2,	PPCNONE,	{VD, RA0, RB},	NULL},

{"divo",	XO(31,331,1,0),	XO_MASK,     M601,	PPCNONE,	{RT, RA, RB},	NULL},
{"divo.",	XO(31,331,1,1),	XO_MASK,     M601,	PPCNONE,	{RT, RA, RB},	NULL},

{"lxvd2x",	X(31,844),	XX1_MASK,    PPCVSX,	PPCNONE,	{XT6, RA0, RB},	NULL},
{"lxvx",	X(31,844),	XX1_MASK,    PPCVSX,	PPCNONE,	{XT6, RA0, RB},	NULL},

{"tabortwci.",	XRC(31,846,1),	X_MASK,      PPCHTM,	PPCNONE,	{TO, RA, HTM_SI},	NULL},

{"tlbsrx.",	XRC(31,850,1),	XRT_MASK,    PPCA2,	PPCNONE,	{RA0, RB},	NULL},

{"slbmfev",	X(31,851),	XRA_MASK,    PPC64,	PPCNONE,	{RT, RB},	NULL},

{"lbzcix",	X(31,853),	X_MASK,      POWER6,	PPCNONE,	{RT, RA0, RB},	NULL},

{"eieio",	X(31,854),	0xffffffff,  PPC,   BOOKE|PPCA2|PPC476,	{UNUSED},	NULL},
{"mbar",	X(31,854),	X_MASK, BOOKE|PPCA2|PPC476|PPCVLE, PPCNONE, {MO},	NULL},
{"eieio",	XMBAR(31,854,1),0xffffffff,  E500,	PPCNONE,	{UNUSED},	NULL},
{"eieio",	X(31,854),	0xffffffff, PPCA2|PPC476, PPCNONE,	{UNUSED},	NULL},

{"lfiwax",	X(31,855),	X_MASK, POWER6|PPCA2|PPC476, PPCNONE,	{FRT, RA0, RB},	NULL},

{"lvswxl",	X(31,869),	X_MASK,      PPCVEC2,	PPCNONE,	{VD, RA0, RB},	NULL},

{"abso",	XO(31,360,1,0),	XORB_MASK,   M601,	PPCNONE,	{RT, RA},	NULL},
{"abso.",	XO(31,360,1,1),	XORB_MASK,   M601,	PPCNONE,	{RT, RA},	NULL},

{"divso",	XO(31,363,1,0),	XO_MASK,     M601,	PPCNONE,	{RT, RA, RB},	NULL},
{"divso.",	XO(31,363,1,1),	XO_MASK,     M601,	PPCNONE,	{RT, RA, RB},	NULL},

{"tabortdci.",	XRC(31,878,1),	X_MASK,      PPCHTM,	PPCNONE,	{TO, RA, HTM_SI},	NULL},

{"ldcix",	X(31,885),	X_MASK,      POWER6,	PPCNONE,	{RT, RA0, RB},	NULL},

{"lfiwzx",	X(31,887),	X_MASK,   POWER7|PPCA2,	PPCNONE,	{FRT, RA0, RB},	NULL},

{"stvlxl",	X(31,903),	X_MASK,      CELL,	PPCNONE,	{VS, RA0, RB},	NULL},
{"stdfcmux",	APU(31,903,0), 	APU_MASK,    PPC405,	PPCNONE,	{FCRT, RA, RB},	NULL},

{"divdeuo",	XO(31,393,1,0),	XO_MASK,  POWER7|PPCA2,	PPCNONE,	{RT, RA, RB},	NULL},
{"divdeuo.",	XO(31,393,1,1),	XO_MASK,  POWER7|PPCA2,	PPCNONE,	{RT, RA, RB},	NULL},
{"divweuo",	XO(31,395,1,0),	XO_MASK,  POWER7|PPCA2,	PPCNONE,	{RT, RA, RB},	NULL},
{"divweuo.",	XO(31,395,1,1),	XO_MASK,  POWER7|PPCA2,	PPCNONE,	{RT, RA, RB},	NULL},

{"stxvw4x",	X(31,908),	XX1_MASK,    PPCVSX,	PPCNONE,	{XS6, RA0, RB},	NULL},

{"tabort.",	XRC(31,910,1),	XRTRB_MASK,  PPCHTM,	PPCNONE,	{RA},	NULL},

{"tlbsx",	XRC(31,914,0),	X_MASK, PPC403|BOOKE|PPCA2|PPC476|PPCVLE, PPCNONE, {RTO, RA0, RB},	NULL},
{"tlbsx.",	XRC(31,914,1),	X_MASK, PPC403|BOOKE|PPCA2|PPC476, PPCNONE, {RTO, RA0, RB},	NULL},

{"slbmfee",	X(31,915),	XRA_MASK,    PPC64,	PPCNONE,	{RT, RB},	NULL},

{"stwcix",	X(31,917),	X_MASK,      POWER6,	PPCNONE,	{RS, RA0, RB},	NULL},

{"sthbrx",	X(31,918),	X_MASK,      COM|PPCVLE,	PPCNONE,	{RS, RA0, RB},	NULL},

{"stfdpx",	X(31,919),	X_MASK,      POWER6,	POWER7,		{FRSp, RA0, RB},	NULL},
{"stfqx",	X(31,919),	X_MASK,      POWER2,	PPCNONE,	{FRS, RA0, RB},	NULL},

{"sraq",	XRC(31,920,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},
{"sraq.",	XRC(31,920,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},

{"srea",	XRC(31,921,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},
{"srea.",	XRC(31,921,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, RB},	NULL},

{"extsh",	XRC(31,922,0),	XRB_MASK,    PPCCOM|PPCVLE, PPCNONE,	{RA, RS},	NULL},
{"exts",	XRC(31,922,0),	XRB_MASK,    PWRCOM,	PPCNONE,	{RA, RS},	NULL},
{"extsh.",	XRC(31,922,1),	XRB_MASK,    PPCCOM|PPCVLE, PPCNONE,	{RA, RS},	NULL},
{"exts.",	XRC(31,922,1),	XRB_MASK,    PWRCOM,	PPCNONE,	{RA, RS},	NULL},

{"stfddx",	X(31,931),	X_MASK,      E500MC|PPCVLE,	PPCNONE,	{FRS, RA, RB},	NULL},

{"stvfrxl",	X(31,933),	X_MASK,      PPCVEC2,	PPCNONE,	{VS, RA0, RB},	NULL},

{"wclrone",	XOPL2(31,934,2),XRT_MASK,    PPCA2,	PPCNONE,	{RA0, RB},	NULL},
{"wclrall",	X(31,934),	XRARB_MASK,  PPCA2,	PPCNONE,	{L},	NULL},
{"wclr",	X(31,934),	X_MASK,	     PPCA2,	PPCNONE,	{L, RA0, RB},	NULL},

{"stvrxl",	X(31,935),	X_MASK,      CELL,	PPCNONE,	{VS, RA0, RB},	NULL},

{"divdeo",	XO(31,425,1,0),	XO_MASK,  POWER7|PPCA2,	PPCNONE,	{RT, RA, RB},	NULL},
{"divdeo.",	XO(31,425,1,1),	XO_MASK,  POWER7|PPCA2,	PPCNONE,	{RT, RA, RB},	NULL},
{"divweo",	XO(31,427,1,0),	XO_MASK,  POWER7|PPCA2,	PPCNONE,	{RT, RA, RB},	NULL},
{"divweo.",	XO(31,427,1,1),	XO_MASK,  POWER7|PPCA2,	PPCNONE,	{RT, RA, RB},	NULL},

{"treclaim.",	XRC(31,942,1),	XRTRB_MASK,  PPCHTM,	PPCNONE,	{RA},	NULL},

{"tlbrehi",	XTLB(31,946,0),	XTLB_MASK,   PPC403,	PPCA2,		{RT, RA},	NULL},
{"tlbrelo",	XTLB(31,946,1),	XTLB_MASK,   PPC403,	PPCA2,		{RT, RA},	NULL},
{"tlbre",	X(31,946),	X_MASK, PPC403|BOOKE|PPCA2|PPC476|PPCVLE, PPCNONE, {RSO, RAOPT, SHO},	NULL},

{"sthcix",	X(31,949),	X_MASK,      POWER6,	PPCNONE,	{RS, RA0, RB},	NULL},

{"icswepx",	XRC(31,950,0),	X_MASK,      PPCA2,	PPCNONE,	{RS, RA, RB},	NULL},
{"icswepx.",	XRC(31,950,1),	X_MASK,      PPCA2,	PPCNONE,	{RS, RA, RB},	NULL},

{"stfqux",	X(31,951),	X_MASK,      POWER2,	PPCNONE,	{FRS, RA, RB},	NULL},

{"sraiq",	XRC(31,952,0),	X_MASK,      M601,	PPCNONE,	{RA, RS, SH},	NULL},
{"sraiq.",	XRC(31,952,1),	X_MASK,      M601,	PPCNONE,	{RA, RS, SH},	NULL},

{"extsb",	XRC(31,954,0),	XRB_MASK, PPC|PPCVLE,	PPCNONE,	{RA, RS},	NULL},
{"extsb.",	XRC(31,954,1),	XRB_MASK, PPC|PPCVLE,	PPCNONE,	{RA, RS},	NULL},

{"stvflxl",	X(31,965),	X_MASK,      PPCVEC2,	PPCNONE,	{VS, RA0, RB},	NULL},

{"iccci",	X(31,966), XRT_MASK, PPC403|PPC440|TITAN|PPCA2|PPCVLE, PPCNONE, {RAOPT, RBOPT},	NULL},
{"ici",		X(31,966),	XRARB_MASK,  PPCA2|PPC476|PPCVLE, PPCNONE, {CT},	NULL},
 
{"divduo",	XO(31,457,1,0),	XO_MASK,     PPC64|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"divduo.",	XO(31,457,1,1),	XO_MASK,     PPC64|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
 
{"divwuo",	XO(31,459,1,0),	XO_MASK,     PPC|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"divwuo.",	XO(31,459,1,1),	XO_MASK,     PPC|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},

{"stxvd2x",	X(31,972),	XX1_MASK,    PPCVSX,	PPCNONE,	{XS6, RA0, RB},	NULL},
{"stxvx",	X(31,972),	XX1_MASK,    PPCVSX,	PPCNONE,	{XS6, RA0, RB},	NULL},

{"tlbld",	X(31,978),	XRTRA_MASK,  PPC, PPC403|BOOKE|PPCA2|PPC476, {RB},	NULL},
{"tlbwehi",	XTLB(31,978,0),	XTLB_MASK,   PPC403,	PPCNONE,	{RT, RA},	NULL},
{"tlbwelo",	XTLB(31,978,1),	XTLB_MASK,   PPC403,	PPCNONE,	{RT, RA},	NULL},
{"tlbwe",	X(31,978),	X_MASK, PPC403|BOOKE|PPCA2|PPC476|PPCVLE, PPCNONE, {RSO, RAOPT, SHO},	NULL},

{"stbcix",	X(31,981),	X_MASK,      POWER6,	PPCNONE,	{RS, RA0, RB},	NULL},

{"icbi",	X(31,982),	XRT_MASK,    PPC|PPCVLE, PPCNONE,	{RA0, RB},	NULL},

{"stfiwx",	X(31,983),	X_MASK,      PPC,	PPCEFS,		{FRS, RA0, RB},	NULL},

{"extsw",	XRC(31,986,0),  XRB_MASK, PPC64|PPCVLE, PPCNONE,	{RA, RS},	NULL},
{"extsw.",	XRC(31,986,1),	XRB_MASK, PPC64|PPCVLE, PPCNONE,	{RA, RS},	NULL},

{"icbiep",	XRT(31,991,0),	XRT_MASK, E500MC|PPCA2|PPCVLE, PPCNONE, {RA0, RB},	NULL},

{"stvswxl",	X(31,997),	X_MASK,      PPCVEC2,	PPCNONE,	{VS, RA0, RB},	NULL},

{"icread",	X(31,998), XRT_MASK, PPC403|PPC440|PPC476|TITAN|PPCVLE, PPCNONE, {RA0, RB},	NULL},

{"nabso",	XO(31,488,1,0),	XORB_MASK,   M601,	PPCNONE,	{RT, RA},	NULL},
{"nabso.",	XO(31,488,1,1),	XORB_MASK,   M601,	PPCNONE,	{RT, RA},	NULL},

{"divdo",	XO(31,489,1,0),	XO_MASK,  PPC64|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
{"divdo.",	XO(31,489,1,1),	XO_MASK,  PPC64|PPCVLE, PPCNONE,	{RT, RA, RB},	NULL},
 
{"divwo",	XO(31,491,1,0),	XO_MASK,   PPC|PPCVLE,	PPCNONE,	{RT, RA, RB},	NULL},
{"divwo.",	XO(31,491,1,1),	XO_MASK,   PPC|PPCVLE,	PPCNONE,	{RT, RA, RB},	NULL},

{"trechkpt.",	XRC(31,1006,1),	XRTRARB_MASK,PPCHTM,	PPCNONE,	{UNUSED},	NULL},

{"tlbli",	X(31,1010),	XRTRA_MASK,  PPC,	TITAN,  	{RB},	NULL},

{"stdcix",	X(31,1013),	X_MASK,      POWER6,	PPCNONE,	{RS, RA0, RB},	NULL},

{"dcbz",	X(31,1014),	XRT_MASK,    PPC|PPCVLE, PPCNONE,	{RA0, RB},	NULL},
{"dclz",	X(31,1014),	XRT_MASK,    PPC,	PPCNONE,	{RA0, RB},	NULL},

{"dcbzep",	XRT(31,1023,0),	XRT_MASK, E500MC|PPCA2|PPCVLE, PPCNONE,	{RA0, RB},	NULL},

{"dcbzl",	XOPL(31,1014,1), XRT_MASK, POWER4|E500MC, PPC476,	{RA0, RB},	NULL},

{"cctpl",	0x7c210b78,	0xffffffff,  CELL,	PPCNONE,	{UNUSED},	NULL},
{"cctpm",	0x7c421378,	0xffffffff,  CELL,	PPCNONE,	{UNUSED},	NULL},
{"cctph",	0x7c631b78,	0xffffffff,  CELL,	PPCNONE,	{UNUSED},	NULL},

{"dstt",	XDSS(31,342,1),	XDSS_MASK,   PPCVEC,	PPCNONE,	{RA, RB, STRM},	NULL},
{"dststt",	XDSS(31,374,1),	XDSS_MASK,   PPCVEC,	PPCNONE,	{RA, RB, STRM},	NULL},
{"dssall",	XDSS(31,822,1),	XDSS_MASK,   PPCVEC,	PPCNONE,	{UNUSED},	NULL},

{"db8cyc",	0x7f9ce378,	0xffffffff,  CELL,	PPCNONE,	{UNUSED},	NULL},
{"db10cyc",	0x7fbdeb78,	0xffffffff,  CELL,	PPCNONE,	{UNUSED},	NULL},
{"db12cyc",	0x7fdef378,	0xffffffff,  CELL,	PPCNONE,	{UNUSED},	NULL},
{"db16cyc",	0x7ffffb78,	0xffffffff,  CELL,	PPCNONE,	{UNUSED},	NULL},

{"lwz",		OP(32),		OP_MASK,     PPCCOM,	PPCNONE,	{RT, D, RA0},	translate_lwz},
{"l",		OP(32),		OP_MASK,     PWRCOM,	PPCNONE,	{RT, D, RA0},	NULL},

{"lwzu",	OP(33),		OP_MASK,     PPCCOM,	PPCNONE,	{RT, D, RAL},	translate_lwzu},
{"lu",		OP(33),		OP_MASK,     PWRCOM,	PPCNONE,	{RT, D, RA0},	NULL},

{"lbz",		OP(34),		OP_MASK,     COM,	PPCNONE,	{RT, D, RA0},	translate_lbz},

{"lbzu",	OP(35),		OP_MASK,     COM,	PPCNONE,	{RT, D, RAL},	translate_lbzu},

{"stw",		OP(36),		OP_MASK,     PPCCOM,	PPCNONE,	{RS, D, RA0},	translate_stw},
{"st",		OP(36),		OP_MASK,     PWRCOM,	PPCNONE,	{RS, D, RA0},	NULL},

{"stwu",	OP(37),		OP_MASK,     PPCCOM,	PPCNONE,	{RS, D, RAS},	translate_stwu},
{"stu",		OP(37),		OP_MASK,     PWRCOM,	PPCNONE,	{RS, D, RA0},	NULL},

{"stb",		OP(38),		OP_MASK,     COM,	PPCNONE,	{RS, D, RA0},	translate_stb},

{"stbu",	OP(39),		OP_MASK,     COM,	PPCNONE,	{RS, D, RAS},	translate_stbu},

{"lhz",		OP(40),		OP_MASK,     COM,	PPCNONE,	{RT, D, RA0},	translate_lhz},

{"lhzu",	OP(41),		OP_MASK,     COM,	PPCNONE,	{RT, D, RAL},	translate_lhzu},

{"lha",		OP(42),		OP_MASK,     COM,	PPCNONE,	{RT, D, RA0},	translate_lha},

{"lhau",	OP(43),		OP_MASK,     COM,	PPCNONE,	{RT, D, RAL},	translate_lhau},

{"sth",		OP(44),		OP_MASK,     COM,	PPCNONE,	{RS, D, RA0},	translate_sth},

{"sthu",	OP(45),		OP_MASK,     COM,	PPCNONE,	{RS, D, RAS},	translate_sthu},

{"lmw",		OP(46),		OP_MASK,     PPCCOM,	PPCNONE,	{RT, D, RAM},	translate_lmw},
{"lm",		OP(46),		OP_MASK,     PWRCOM,	PPCNONE,	{RT, D, RA0},	NULL},

{"stmw",	OP(47),		OP_MASK,     PPCCOM,	PPCNONE,	{RS, D, RA0},	translate_stmw},
{"stm",		OP(47),		OP_MASK,     PWRCOM,	PPCNONE,	{RS, D, RA0},	NULL},

{"lfs",		OP(48),		OP_MASK,     COM,	PPCEFS,		{FRT, D, RA0},	NULL},

{"lfsu",	OP(49),		OP_MASK,     COM,	PPCEFS,		{FRT, D, RAS},	NULL},

{"lfd",		OP(50),		OP_MASK,     COM,	PPCEFS,		{FRT, D, RA0},	NULL},

{"lfdu",	OP(51),		OP_MASK,     COM,	PPCEFS,		{FRT, D, RAS},	NULL},

{"stfs",	OP(52),		OP_MASK,     COM,	PPCEFS,		{FRS, D, RA0},	NULL},

{"stfsu",	OP(53),		OP_MASK,     COM,	PPCEFS,		{FRS, D, RAS},	NULL},

{"stfd",	OP(54),		OP_MASK,     COM,	PPCEFS,		{FRS, D, RA0},	NULL},

{"stfdu",	OP(55),		OP_MASK,     COM,	PPCEFS,		{FRS, D, RAS},	NULL},

{"lq",		OP(56),		OP_MASK,     POWER4,	PPC476,		{RTQ, DQ, RAQ},	NULL},
{"psq_l",	OP(56),		OP_MASK,     PPCPS,	PPCNONE,	{FRT,PSD,RA,PSW,PSQ},	NULL},
{"lfq",		OP(56),		OP_MASK,     POWER2,	PPCNONE,	{FRT, D, RA0},	NULL},

{"lfdp",	OP(57),		OP_MASK,     POWER6,	POWER7,		{FRTp, DS, RA0},	NULL},
{"psq_lu",	OP(57),		OP_MASK,     PPCPS,	PPCNONE,	{FRT,PSD,RA,PSW,PSQ},	NULL},
{"lfqu",	OP(57),		OP_MASK,     POWER2,	PPCNONE,	{FRT, D, RA0},	NULL},

{"ld",		DSO(58,0),	DS_MASK,     PPC64,	PPCNONE,	{RT, DS, RA0},	NULL},
{"ldu",		DSO(58,1),	DS_MASK,     PPC64,	PPCNONE,	{RT, DS, RAL},	NULL},
{"lwa",		DSO(58,2),	DS_MASK,     PPC64,	PPCNONE,	{RT, DS, RA0},	NULL},

{"dadd",	XRC(59,2,0),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"dadd.",	XRC(59,2,1),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRA, FRB},	NULL},

{"dqua",	ZRC(59,3,0),	Z2_MASK,     POWER6,	PPCNONE,	{FRT,FRA,FRB,RMC},	NULL},
{"dqua.",	ZRC(59,3,1),	Z2_MASK,     POWER6,	PPCNONE,	{FRT,FRA,FRB,RMC},	NULL},

{"fdivs",	A(59,18,0),	AFRC_MASK,   PPC,	PPCEFS,		{FRT, FRA, FRB},	NULL},
{"fdivs.",	A(59,18,1),	AFRC_MASK,   PPC,	PPCEFS,		{FRT, FRA, FRB},	NULL},

{"fsubs",	A(59,20,0),	AFRC_MASK,   PPC,	PPCEFS,		{FRT, FRA, FRB},	NULL},
{"fsubs.",	A(59,20,1),	AFRC_MASK,   PPC,	PPCEFS,		{FRT, FRA, FRB},	NULL},

{"fadds",	A(59,21,0),	AFRC_MASK,   PPC,	PPCEFS,		{FRT, FRA, FRB},	NULL},
{"fadds.",	A(59,21,1),	AFRC_MASK,   PPC,	PPCEFS,		{FRT, FRA, FRB},	NULL},

{"fsqrts",	A(59,22,0),    AFRAFRC_MASK, PPC,	TITAN,  	{FRT, FRB},	NULL},
{"fsqrts.",	A(59,22,1),    AFRAFRC_MASK, PPC,	TITAN,  	{FRT, FRB},	NULL},

{"fres",	A(59,24,0),   AFRAFRC_MASK,  POWER7,	PPCNONE,	{FRT, FRB},	NULL},
{"fres",	A(59,24,0),   AFRALFRC_MASK, PPC,	POWER7,		{FRT, FRB, A_L},	NULL},
{"fres.",	A(59,24,1),   AFRAFRC_MASK,  POWER7,	PPCNONE,	{FRT, FRB},	NULL},
{"fres.",	A(59,24,1),   AFRALFRC_MASK, PPC,	POWER7,		{FRT, FRB, A_L},	NULL},

{"fmuls",	A(59,25,0),	AFRB_MASK,   PPC,	PPCEFS,		{FRT, FRA, FRC},	NULL},
{"fmuls.",	A(59,25,1),	AFRB_MASK,   PPC,	PPCEFS,		{FRT, FRA, FRC},	NULL},

{"frsqrtes",	A(59,26,0),   AFRAFRC_MASK,  POWER7,	PPCNONE,	{FRT, FRB},	NULL},
{"frsqrtes",	A(59,26,0),   AFRALFRC_MASK, POWER5,	POWER7,		{FRT, FRB, A_L},	NULL},
{"frsqrtes.",	A(59,26,1),   AFRAFRC_MASK,  POWER7,	PPCNONE,	{FRT, FRB},	NULL},
{"frsqrtes.",	A(59,26,1),   AFRALFRC_MASK, POWER5,	POWER7,		{FRT, FRB, A_L},	NULL},

{"fmsubs",	A(59,28,0),	A_MASK,      PPC,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},
{"fmsubs.",	A(59,28,1),	A_MASK,      PPC,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},

{"fmadds",	A(59,29,0),	A_MASK,      PPC,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},
{"fmadds.",	A(59,29,1),	A_MASK,      PPC,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},

{"fnmsubs",	A(59,30,0),	A_MASK,      PPC,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},
{"fnmsubs.",	A(59,30,1),	A_MASK,      PPC,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},

{"fnmadds",	A(59,31,0),	A_MASK,      PPC,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},
{"fnmadds.",	A(59,31,1),	A_MASK,      PPC,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},

{"dmul",	XRC(59,34,0),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"dmul.",	XRC(59,34,1),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRA, FRB},	NULL},

{"drrnd",	ZRC(59,35,0),	Z2_MASK,     POWER6,	PPCNONE,	{FRT, FRA, FRB, RMC},	NULL},
{"drrnd.",	ZRC(59,35,1),	Z2_MASK,     POWER6,	PPCNONE,	{FRT, FRA, FRB, RMC},	NULL},

{"dscli",	ZRC(59,66,0),	Z_MASK,      POWER6,	PPCNONE,	{FRT, FRA, SH16},	NULL},
{"dscli.",	ZRC(59,66,1),	Z_MASK,      POWER6,	PPCNONE,	{FRT, FRA, SH16},	NULL},

{"dquai",	ZRC(59,67,0),	Z2_MASK,     POWER6,	PPCNONE,	{TE, FRT,FRB,RMC},	NULL},
{"dquai.",	ZRC(59,67,1),	Z2_MASK,     POWER6,	PPCNONE,	{TE, FRT,FRB,RMC},	NULL},

{"dscri",	ZRC(59,98,0),	Z_MASK,      POWER6,	PPCNONE,	{FRT, FRA, SH16},	NULL},
{"dscri.",	ZRC(59,98,1),	Z_MASK,      POWER6,	PPCNONE,	{FRT, FRA, SH16},	NULL},

{"drintx",	ZRC(59,99,0),	Z2_MASK,     POWER6,	PPCNONE,	{R, FRT, FRB, RMC},	NULL},
{"drintx.",	ZRC(59,99,1),	Z2_MASK,     POWER6,	PPCNONE,	{R, FRT, FRB, RMC},	NULL},

{"dcmpo",	X(59,130),	X_MASK,      POWER6,	PPCNONE,	{BF,  FRA, FRB},	NULL},

{"dtstex",	X(59,162),	X_MASK,      POWER6,	PPCNONE,	{BF,  FRA, FRB},	NULL},
{"dtstdc",	Z(59,194),	Z_MASK,      POWER6,	PPCNONE,	{BF,  FRA, DCM},	NULL},
{"dtstdg",	Z(59,226),	Z_MASK,      POWER6,	PPCNONE,	{BF,  FRA, DGM},	NULL},

{"drintn",	ZRC(59,227,0),	Z2_MASK,     POWER6,	PPCNONE,	{R, FRT, FRB, RMC},	NULL},
{"drintn.",	ZRC(59,227,1),	Z2_MASK,     POWER6,	PPCNONE,	{R, FRT, FRB, RMC},	NULL},

{"dctdp",	XRC(59,258,0),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRB},	NULL},
{"dctdp.",	XRC(59,258,1),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRB},	NULL},

{"dctfix",	XRC(59,290,0),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRB},	NULL},
{"dctfix.",	XRC(59,290,1),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRB},	NULL},

{"ddedpd",	XRC(59,322,0),	X_MASK,      POWER6,	PPCNONE,	{SP, FRT, FRB},	NULL}, 
{"ddedpd.",	XRC(59,322,1),	X_MASK,      POWER6,	PPCNONE,	{SP, FRT, FRB},	NULL}, 

{"dxex",	XRC(59,354,0),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRB},	NULL},
{"dxex.",	XRC(59,354,1),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRB},	NULL},

{"dsub",	XRC(59,514,0),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"dsub.",	XRC(59,514,1),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRA, FRB},	NULL},

{"ddiv",	XRC(59,546,0),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"ddiv.",	XRC(59,546,1),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRA, FRB},	NULL},

{"dcmpu",	X(59,642),	X_MASK,      POWER6,	PPCNONE,	{BF,  FRA, FRB},	NULL},

{"dtstsf",	X(59,674),	X_MASK,      POWER6,	PPCNONE,	{BF,  FRA, FRB},	NULL},

{"drsp",	XRC(59,770,0),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRB},	NULL},
{"drsp.",	XRC(59,770,1),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRB},	NULL},

{"dcffix",	XRC(59,802,0), X_MASK|FRA_MASK, POWER7,	PPCNONE,	{FRT, FRB},	NULL},
{"dcffix.",	XRC(59,802,1), X_MASK|FRA_MASK, POWER7,	PPCNONE,	{FRT, FRB},	NULL},

{"denbcd",	XRC(59,834,0),	X_MASK,      POWER6,	PPCNONE,	{S, FRT, FRB},	NULL},
{"denbcd.",	XRC(59,834,1),	X_MASK,      POWER6,	PPCNONE,	{S, FRT, FRB},	NULL},

{"fcfids",	XRC(59,846,0),	XRA_MASK, POWER7|PPCA2,	PPCNONE,	{FRT, FRB},	NULL},
{"fcfids.",	XRC(59,846,1),	XRA_MASK, POWER7|PPCA2,	PPCNONE,	{FRT, FRB},	NULL},

{"diex",	XRC(59,866,0),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"diex.",	XRC(59,866,1),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRA, FRB},	NULL},

{"fcfidus",	XRC(59,974,0),	XRA_MASK, POWER7|PPCA2,	PPCNONE,	{FRT, FRB},	NULL},
{"fcfidus.",	XRC(59,974,1),	XRA_MASK, POWER7|PPCA2,	PPCNONE,	{FRT, FRB},	NULL},

{"xsaddsp",	XX3(60,0),	XX3_MASK,    PPCVSX2,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsmaddasp",	XX3(60,1),	XX3_MASK,    PPCVSX2,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xxsldwi",	XX3(60,2),	XX3SHW_MASK, PPCVSX,	PPCNONE,	{XT6, XA6, XB6, SHW},	NULL},
{"xxsel",	XX4(60,3),	XX4_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6, XC6},	NULL},
{"xssubsp",	XX3(60,8),	XX3_MASK,    PPCVSX2,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsmaddmsp",	XX3(60,9),	XX3_MASK,    PPCVSX2,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xxspltd",	XX3(60,10),	XX3DM_MASK,  PPCVSX,	PPCNONE,	{XT6, XA6, XB6S, DMEX},	NULL},
{"xxmrghd",	XX3(60,10),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xxswapd",	XX3(60,10)|(2<<8), XX3_MASK, PPCVSX,	PPCNONE,	{XT6, XA6, XB6S},	NULL},
{"xxmrgld",	XX3(60,10)|(3<<8), XX3_MASK, PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xxpermdi",	XX3(60,10),	XX3DM_MASK,  PPCVSX,	PPCNONE,	{XT6, XA6, XB6, DM},	NULL},
{"xsrsqrtesp",	XX2(60,10),	XX2_MASK,    PPCVSX2,	PPCNONE,	{XT6, XB6},	NULL},
{"xssqrtsp",	XX2(60,11),	XX2_MASK,    PPCVSX2,	PPCNONE,	{XT6, XB6},	NULL},
{"xsmulsp",	XX3(60,16),	XX3_MASK,    PPCVSX2,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsmsubasp",	XX3(60,17),	XX3_MASK,    PPCVSX2,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xxmrghw",	XX3(60,18),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsdivsp",	XX3(60,24),	XX3_MASK,    PPCVSX2,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsmsubmsp",	XX3(60,25),	XX3_MASK,    PPCVSX2,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsresp",	XX2(60,26),	XX2_MASK,    PPCVSX2,	PPCNONE,	{XT6, XB6},	NULL},
{"xsadddp",	XX3(60,32),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsmaddadp",	XX3(60,33),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xscmpudp",	XX3(60,35),	XX3BF_MASK,  PPCVSX,	PPCNONE,	{BF, XA6, XB6},	NULL},
{"xssubdp",	XX3(60,40),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsmaddmdp",	XX3(60,41),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xscmpodp",	XX3(60,43),	XX3BF_MASK,  PPCVSX,	PPCNONE,	{BF, XA6, XB6},	NULL},
{"xsmuldp",	XX3(60,48),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsmsubadp",	XX3(60,49),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xxmrglw",	XX3(60,50),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsdivdp",	XX3(60,56),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsmsubmdp",	XX3(60,57),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xstdivdp",	XX3(60,61),	XX3BF_MASK,  PPCVSX,	PPCNONE,	{BF, XA6, XB6},	NULL},
{"xvaddsp",	XX3(60,64),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvmaddasp",	XX3(60,65),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcmpeqsp",	XX3RC(60,67,0),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcmpeqsp.",	XX3RC(60,67,1),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvsubsp",	XX3(60,72),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xscvdpuxws",	XX2(60,72),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvmaddmsp",	XX3(60,73),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsrdpi",	XX2(60,73),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xsrsqrtedp",	XX2(60,74),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xssqrtdp",	XX2(60,75),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvcmpgtsp",	XX3RC(60,75,0),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcmpgtsp.",	XX3RC(60,75,1),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvmulsp",	XX3(60,80),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvmsubasp",	XX3(60,81),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcmpgesp",	XX3RC(60,83,0),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcmpgesp.",	XX3RC(60,83,1),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvdivsp",	XX3(60,88),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xscvdpsxws",	XX2(60,88),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvmsubmsp",	XX3(60,89),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsrdpiz",	XX2(60,89),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xsredp",	XX2(60,90),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvtdivsp",	XX3(60,93),	XX3BF_MASK,  PPCVSX,	PPCNONE,	{BF, XA6, XB6},	NULL},
{"xvadddp",	XX3(60,96),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvmaddadp",	XX3(60,97),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcmpeqdp",	XX3RC(60,99,0),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcmpeqdp.",	XX3RC(60,99,1),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvsubdp",	XX3(60,104),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvmaddmdp",	XX3(60,105),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsrdpip",	XX2(60,105),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xstsqrtdp",	XX2(60,106),	XX2BF_MASK,  PPCVSX,	PPCNONE,	{BF, XB6},	NULL},
{"xsrdpic",	XX2(60,107),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvcmpgtdp",	XX3RC(60,107,0), XX3_MASK,   PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcmpgtdp.",	XX3RC(60,107,1), XX3_MASK,   PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvmuldp",	XX3(60,112),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvmsubadp",	XX3(60,113),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcmpgedp",	XX3RC(60,115,0), XX3_MASK,   PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcmpgedp.",	XX3RC(60,115,1), XX3_MASK,   PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvdivdp",	XX3(60,120),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvmsubmdp",	XX3(60,121),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsrdpim",	XX2(60,121),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvtdivdp",	XX3(60,125),	XX3BF_MASK,  PPCVSX,	PPCNONE,	{BF, XA6, XB6},	NULL},
{"xsnmaddasp",	XX3(60,129),	XX3_MASK,    PPCVSX2,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xxland",	XX3(60,130),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcvspuxws",	XX2(60,136),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xsnmaddmsp",	XX3(60,137),	XX3_MASK,    PPCVSX2,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvrspi",	XX2(60,137),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xxlandc",	XX3(60,138),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvrsqrtesp",	XX2(60,138),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvsqrtsp",	XX2(60,139),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xsnmsubasp",	XX3(60,145),	XX3_MASK,    PPCVSX2,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xxlor",	XX3(60,146),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcvspsxws",	XX2(60,152),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xsnmsubmsp",	XX3(60,153),	XX3_MASK,    PPCVSX2,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvrspiz",	XX2(60,153),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xxlxor",	XX3(60,154),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvresp",	XX2(60,154),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xsmaxdp",	XX3(60,160),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsnmaddadp",	XX3(60,161),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xxlnor",	XX3(60,162),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xxspltw",	XX2(60,164),	XX2UIM_MASK, PPCVSX,	PPCNONE,	{XT6, XB6, UIM},	NULL},
{"xsmindp",	XX3(60,168),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcvuxwsp",	XX2(60,168),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xsnmaddmdp",	XX3(60,169),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvrspip",	XX2(60,169),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvtsqrtsp",	XX2(60,170),	XX2BF_MASK,  PPCVSX,	PPCNONE,	{BF, XB6},	NULL},
{"xxlorc",	XX3(60,170),	XX3_MASK,    PPCVSX2,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvrspic",	XX2(60,171),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xscpsgndp",	XX3(60,176),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xsnmsubadp",	XX3(60,177),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xxlnand",	XX3(60,178),	XX3_MASK,    PPCVSX2,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcvsxwsp",	XX2(60,184),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xsnmsubmdp",	XX3(60,185),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvrspim",	XX2(60,185),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xxleqv",	XX3(60,186),	XX3_MASK,    PPCVSX2,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvmaxsp",	XX3(60,192),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvnmaddasp",	XX3(60,193),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvminsp",	XX3(60,200),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcvdpuxws",	XX2(60,200),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvnmaddmsp",	XX3(60,201),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvrdpi",	XX2(60,201),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvrsqrtedp",	XX2(60,202),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvsqrtdp",	XX2(60,203),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvmovsp",	XX3(60,208),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6S},	NULL},
{"xvcpsgnsp",	XX3(60,208),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvnmsubasp",	XX3(60,209),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcvdpsxws",	XX2(60,216),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvnmsubmsp",	XX3(60,217),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvrdpiz",	XX2(60,217),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvredp",	XX2(60,218),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvmaxdp",	XX3(60,224),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvnmaddadp",	XX3(60,225),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvmindp",	XX3(60,232),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvnmaddmdp",	XX3(60,233),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcvuxwdp",	XX2(60,232),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvrdpip",	XX2(60,233),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvtsqrtdp",	XX2(60,234),	XX2BF_MASK,  PPCVSX,	PPCNONE,	{BF, XB6},	NULL},
{"xvrdpic",	XX2(60,235),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvmovdp",	XX3(60,240),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6S},	NULL},
{"xvcpsgndp",	XX3(60,240),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvnmsubadp",	XX3(60,241),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvcvsxwdp",	XX2(60,248),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvnmsubmdp",	XX3(60,249),	XX3_MASK,    PPCVSX,	PPCNONE,	{XT6, XA6, XB6},	NULL},
{"xvrdpim",	XX2(60,249),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xscvdpsp",	XX2(60,265),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xscvdpspn",	XX2(60,267),	XX2_MASK,    PPCVSX2,	PPCNONE,	{XT6, XB6},	NULL},
{"xsrsp",	XX2(60,281),	XX2_MASK,    PPCVSX2,	PPCNONE,	{XT6, XB6},	NULL},
{"xscvuxdsp",	XX2(60,296),	XX2_MASK,    PPCVSX2,	PPCNONE,	{XT6, XB6},	NULL},
{"xscvsxdsp",	XX2(60,312),	XX2_MASK,    PPCVSX2,	PPCNONE,	{XT6, XB6},	NULL},
{"xscvdpuxds",	XX2(60,328),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xscvspdp",	XX2(60,329),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xscvspdpn",	XX2(60,331),	XX2_MASK,    PPCVSX2,	PPCNONE,	{XT6, XB6},	NULL},
{"xscvdpsxds",	XX2(60,344),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xsabsdp",	XX2(60,345),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xscvuxddp",	XX2(60,360),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xsnabsdp",	XX2(60,361),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xscvsxddp",	XX2(60,376),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xsnegdp",	XX2(60,377),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvcvspuxds",	XX2(60,392),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvcvdpsp",	XX2(60,393),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvcvspsxds",	XX2(60,408),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvabssp",	XX2(60,409),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvcvuxdsp",	XX2(60,424),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvnabssp",	XX2(60,425),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvcvsxdsp",	XX2(60,440),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvnegsp",	XX2(60,441),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvcvdpuxds",	XX2(60,456),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvcvspdp",	XX2(60,457),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvcvdpsxds",	XX2(60,472),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvabsdp",	XX2(60,473),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvcvuxddp",	XX2(60,488),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvnabsdp",	XX2(60,489),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvcvsxddp",	XX2(60,504),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},
{"xvnegdp",	XX2(60,505),	XX2_MASK,    PPCVSX,	PPCNONE,	{XT6, XB6},	NULL},

{"psq_st",	OP(60),		OP_MASK,     PPCPS,	PPCNONE,	{FRS,PSD,RA,PSW,PSQ},	NULL},
{"stfq",	OP(60),		OP_MASK,     POWER2,	PPCNONE,	{FRS, D, RA},	NULL},

{"stfdp",	OP(61),		OP_MASK,     POWER6,	POWER7,		{FRSp, DS, RA0},	NULL},
{"psq_stu",	OP(61),		OP_MASK,     PPCPS,	PPCNONE,	{FRS,PSD,RA,PSW,PSQ},	NULL},
{"stfqu",	OP(61),		OP_MASK,     POWER2,	PPCNONE,	{FRS, D, RA},	NULL},

{"std",		DSO(62,0),	DS_MASK,     PPC64,	PPCNONE,	{RS, DS, RA0},	NULL},
{"stdu",	DSO(62,1),	DS_MASK,     PPC64,	PPCNONE,	{RS, DS, RAS},	NULL},
{"stq",		DSO(62,2),	DS_MASK,     POWER4,	PPC476,		{RSQ, DS, RA0},	NULL},

{"fcmpu",	X(63,0),     X_MASK|(3<<21), COM,	PPCEFS,		{BF, FRA, FRB},	NULL},

{"daddq",	XRC(63,2,0),	X_MASK,      POWER6,	PPCNONE,	{FRTp, FRAp, FRBp},	NULL},
{"daddq.",	XRC(63,2,1),	X_MASK,      POWER6,	PPCNONE,	{FRTp, FRAp, FRBp},	NULL},

{"dquaq",	ZRC(63,3,0),	Z2_MASK,     POWER6,	PPCNONE,	{FRTp, FRAp, FRBp, RMC},	NULL},
{"dquaq.",	ZRC(63,3,1),	Z2_MASK,     POWER6,	PPCNONE,	{FRTp, FRAp, FRBp, RMC},	NULL},

{"fcpsgn",	XRC(63,8,0),	X_MASK, POWER6|PPCA2|PPC476, PPCNONE,	{FRT, FRA, FRB},	NULL},
{"fcpsgn.",	XRC(63,8,1),	X_MASK, POWER6|PPCA2|PPC476, PPCNONE,	{FRT, FRA, FRB},	NULL},

{"frsp",	XRC(63,12,0),	XRA_MASK,    COM,	PPCEFS,		{FRT, FRB},	NULL},
{"frsp.",	XRC(63,12,1),	XRA_MASK,    COM,	PPCEFS,		{FRT, FRB},	NULL},

{"fctiw",	XRC(63,14,0),	XRA_MASK,    PPCCOM,	PPCEFS,		{FRT, FRB},	NULL},
{"fcir",	XRC(63,14,0),	XRA_MASK,    PWR2COM,	PPCNONE,	{FRT, FRB},	NULL},
{"fctiw.",	XRC(63,14,1),	XRA_MASK,    PPCCOM,	PPCEFS,		{FRT, FRB},	NULL},
{"fcir.",	XRC(63,14,1),	XRA_MASK,    PWR2COM,	PPCNONE,	{FRT, FRB},	NULL},

{"fctiwz",	XRC(63,15,0),	XRA_MASK,    PPCCOM,	PPCEFS,		{FRT, FRB},	NULL},
{"fcirz",	XRC(63,15,0),	XRA_MASK,    PWR2COM,	PPCNONE,	{FRT, FRB},	NULL},
{"fctiwz.",	XRC(63,15,1),	XRA_MASK,    PPCCOM,	PPCEFS,		{FRT, FRB},	NULL},
{"fcirz.",	XRC(63,15,1),	XRA_MASK,    PWR2COM,	PPCNONE,	{FRT, FRB},	NULL},

{"fdiv",	A(63,18,0),	AFRC_MASK,   PPCCOM,	PPCEFS,		{FRT, FRA, FRB},	NULL},
{"fd",		A(63,18,0),	AFRC_MASK,   PWRCOM,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"fdiv.",	A(63,18,1),	AFRC_MASK,   PPCCOM,	PPCEFS,		{FRT, FRA, FRB},	NULL},
{"fd.",		A(63,18,1),	AFRC_MASK,   PWRCOM,	PPCNONE,	{FRT, FRA, FRB},	NULL},

{"fsub",	A(63,20,0),	AFRC_MASK,   PPCCOM,	PPCEFS,		{FRT, FRA, FRB},	NULL},
{"fs",		A(63,20,0),	AFRC_MASK,   PWRCOM,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"fsub.",	A(63,20,1),	AFRC_MASK,   PPCCOM,	PPCEFS,		{FRT, FRA, FRB},	NULL},
{"fs.",		A(63,20,1),	AFRC_MASK,   PWRCOM,	PPCNONE,	{FRT, FRA, FRB},	NULL},

{"fadd",	A(63,21,0),	AFRC_MASK,   PPCCOM,	PPCEFS,		{FRT, FRA, FRB},	NULL},
{"fa",		A(63,21,0),	AFRC_MASK,   PWRCOM,	PPCNONE,	{FRT, FRA, FRB},	NULL},
{"fadd.",	A(63,21,1),	AFRC_MASK,   PPCCOM,	PPCEFS,		{FRT, FRA, FRB},	NULL},
{"fa.",		A(63,21,1),	AFRC_MASK,   PWRCOM,	PPCNONE,	{FRT, FRA, FRB},	NULL},

{"fsqrt",	A(63,22,0),    AFRAFRC_MASK, PPCPWR2,	TITAN,  	{FRT, FRB},	NULL},
{"fsqrt.",	A(63,22,1),    AFRAFRC_MASK, PPCPWR2,	TITAN,  	{FRT, FRB},	NULL},

{"fsel",	A(63,23,0),	A_MASK,      PPC,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},
{"fsel.",	A(63,23,1),	A_MASK,      PPC,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},

{"fre",		A(63,24,0),   AFRAFRC_MASK,  POWER7,	PPCNONE,	{FRT, FRB},	NULL},
{"fre",		A(63,24,0),   AFRALFRC_MASK, POWER5,	POWER7,		{FRT, FRB, A_L},	NULL},
{"fre.",	A(63,24,1),   AFRAFRC_MASK,  POWER7,	PPCNONE,	{FRT, FRB},	NULL},
{"fre.",	A(63,24,1),   AFRALFRC_MASK, POWER5,	POWER7,		{FRT, FRB, A_L},	NULL},

{"fmul",	A(63,25,0),	AFRB_MASK,   PPCCOM,	PPCEFS,		{FRT, FRA, FRC},	NULL},
{"fm",		A(63,25,0),	AFRB_MASK,   PWRCOM,	PPCNONE,	{FRT, FRA, FRC},	NULL},
{"fmul.",	A(63,25,1),	AFRB_MASK,   PPCCOM,	PPCEFS,		{FRT, FRA, FRC},	NULL},
{"fm.",		A(63,25,1),	AFRB_MASK,   PWRCOM,	PPCNONE,	{FRT, FRA, FRC},	NULL},

{"frsqrte",	A(63,26,0),   AFRAFRC_MASK,  POWER7,	PPCNONE,	{FRT, FRB},	NULL},
{"frsqrte",	A(63,26,0),   AFRALFRC_MASK, PPC,	POWER7,		{FRT, FRB, A_L},	NULL},
{"frsqrte.",	A(63,26,1),   AFRAFRC_MASK,  POWER7,	PPCNONE,	{FRT, FRB},	NULL},
{"frsqrte.",	A(63,26,1),   AFRALFRC_MASK, PPC,	POWER7,		{FRT, FRB, A_L},	NULL},

{"fmsub",	A(63,28,0),	A_MASK,      PPCCOM,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},
{"fms",		A(63,28,0),	A_MASK,      PWRCOM,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"fmsub.",	A(63,28,1),	A_MASK,      PPCCOM,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},
{"fms.",	A(63,28,1),	A_MASK,      PWRCOM,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},

{"fmadd",	A(63,29,0),	A_MASK,      PPCCOM,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},
{"fma",		A(63,29,0),	A_MASK,      PWRCOM,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"fmadd.",	A(63,29,1),	A_MASK,      PPCCOM,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},
{"fma.",	A(63,29,1),	A_MASK,      PWRCOM,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},

{"fnmsub",	A(63,30,0),	A_MASK,      PPCCOM,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},
{"fnms",	A(63,30,0),	A_MASK,      PWRCOM,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"fnmsub.",	A(63,30,1),	A_MASK,      PPCCOM,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},
{"fnms.",	A(63,30,1),	A_MASK,      PWRCOM,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},

{"fnmadd",	A(63,31,0),	A_MASK,      PPCCOM,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},
{"fnma",	A(63,31,0),	A_MASK,      PWRCOM,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},
{"fnmadd.",	A(63,31,1),	A_MASK,      PPCCOM,	PPCEFS,		{FRT, FRA, FRC, FRB},	NULL},
{"fnma.",	A(63,31,1),	A_MASK,      PWRCOM,	PPCNONE,	{FRT, FRA, FRC, FRB},	NULL},

{"fcmpo",	X(63,32),    X_MASK|(3<<21), COM,	PPCEFS,		{BF, FRA, FRB},	NULL},

{"dmulq",	XRC(63,34,0),	X_MASK,      POWER6,	PPCNONE,	{FRTp, FRAp, FRBp},	NULL},
{"dmulq.",	XRC(63,34,1),	X_MASK,      POWER6,	PPCNONE,	{FRTp, FRAp, FRBp},	NULL},

{"drrndq",	ZRC(63,35,0),	Z2_MASK,     POWER6,	PPCNONE,	{FRTp, FRA, FRBp, RMC},	NULL},
{"drrndq.",	ZRC(63,35,1),	Z2_MASK,     POWER6,	PPCNONE,	{FRTp, FRA, FRBp, RMC},	NULL},

{"mtfsb1",	XRC(63,38,0),	XRARB_MASK,  COM,	PPCNONE,	{BT},	NULL},
{"mtfsb1.",	XRC(63,38,1),	XRARB_MASK,  COM,	PPCNONE,	{BT},	NULL},

{"fneg",	XRC(63,40,0),	XRA_MASK,    COM,	PPCEFS,		{FRT, FRB},	NULL},
{"fneg.",	XRC(63,40,1),	XRA_MASK,    COM,	PPCEFS,		{FRT, FRB},	NULL},

{"mcrfs",      X(63,64), XRB_MASK|(3<<21)|(3<<16), COM,	PPCNONE,	{BF, BFA},	NULL},

{"dscliq",	ZRC(63,66,0),	Z_MASK,      POWER6,	PPCNONE,	{FRTp, FRAp, SH16},	NULL},
{"dscliq.",	ZRC(63,66,1),	Z_MASK,      POWER6,	PPCNONE,	{FRTp, FRAp, SH16},	NULL},

{"dquaiq",	ZRC(63,67,0),	Z2_MASK,     POWER6,	PPCNONE,	{TE, FRTp, FRBp, RMC},	NULL},
{"dquaiq.",	ZRC(63,67,1),	Z2_MASK,     POWER6,	PPCNONE,	{TE, FRTp, FRBp, RMC},	NULL},

{"mtfsb0",	XRC(63,70,0),	XRARB_MASK,  COM,	PPCNONE,	{BT},	NULL},
{"mtfsb0.",	XRC(63,70,1),	XRARB_MASK,  COM,	PPCNONE,	{BT},	NULL},

{"fmr",		XRC(63,72,0),	XRA_MASK,    COM,	PPCEFS,		{FRT, FRB},	NULL},
{"fmr.",	XRC(63,72,1),	XRA_MASK,    COM,	PPCEFS,		{FRT, FRB},	NULL},

{"dscriq",	ZRC(63,98,0),	Z_MASK,      POWER6,	PPCNONE,	{FRTp, FRAp, SH16},	NULL},
{"dscriq.",	ZRC(63,98,1),	Z_MASK,      POWER6,	PPCNONE,	{FRTp, FRAp, SH16},	NULL},

{"drintxq",	ZRC(63,99,0),	Z2_MASK,     POWER6,	PPCNONE,	{R, FRTp, FRBp, RMC},	NULL},
{"drintxq.",	ZRC(63,99,1),	Z2_MASK,     POWER6,	PPCNONE,	{R, FRTp, FRBp, RMC},	NULL},

{"ftdiv",	X(63,128),   X_MASK|(3<<21), POWER7,	PPCNONE,	{BF, FRA, FRB},	NULL},

{"dcmpoq",	X(63,130),	X_MASK,      POWER6,	PPCNONE,	{BF, FRAp, FRBp},	NULL},

{"mtfsfi",  XRC(63,134,0), XWRA_MASK|(3<<21)|(1<<11), POWER6|PPCA2|PPC476, PPCNONE, {BFF, U, W},	NULL},
{"mtfsfi",  XRC(63,134,0), XRA_MASK|(3<<21)|(1<<11), COM, POWER6|PPCA2|PPC476, {BFF, U},	NULL},
{"mtfsfi.", XRC(63,134,1), XWRA_MASK|(3<<21)|(1<<11), POWER6|PPCA2|PPC476, PPCNONE, {BFF, U, W},	NULL},
{"mtfsfi.", XRC(63,134,1), XRA_MASK|(3<<21)|(1<<11), COM, POWER6|PPCA2|PPC476, {BFF, U},	NULL},

{"fnabs",	XRC(63,136,0),	XRA_MASK,    COM,	PPCEFS,		{FRT, FRB},	NULL},
{"fnabs.",	XRC(63,136,1),	XRA_MASK,    COM,	PPCEFS,		{FRT, FRB},	NULL},

{"fctiwu",	XRC(63,142,0),	XRA_MASK,    POWER7,	PPCNONE,	{FRT, FRB},	NULL},
{"fctiwu.",	XRC(63,142,1),	XRA_MASK,    POWER7,	PPCNONE,	{FRT, FRB},	NULL},
{"fctiwuz",	XRC(63,143,0),	XRA_MASK,    POWER7,	PPCNONE,	{FRT, FRB},	NULL},
{"fctiwuz.",	XRC(63,143,1),	XRA_MASK,    POWER7,	PPCNONE,	{FRT, FRB},	NULL},

{"ftsqrt",	X(63,160), X_MASK|(3<<21|FRA_MASK), POWER7, PPCNONE,	{BF, FRB},	NULL},

{"dtstexq",	X(63,162),	X_MASK,      POWER6,	PPCNONE,	{BF, FRAp, FRBp},	NULL},
{"dtstdcq",	Z(63,194),	Z_MASK,      POWER6,	PPCNONE,	{BF, FRAp, DCM},	NULL},
{"dtstdgq",	Z(63,226),	Z_MASK,      POWER6,	PPCNONE,	{BF, FRAp, DGM},	NULL},

{"drintnq",	ZRC(63,227,0),	Z2_MASK,     POWER6,	PPCNONE,	{R, FRTp, FRBp, RMC},	NULL},
{"drintnq.",	ZRC(63,227,1),	Z2_MASK,     POWER6,	PPCNONE,	{R, FRTp, FRBp, RMC},	NULL},

{"dctqpq",	XRC(63,258,0),	X_MASK,      POWER6,	PPCNONE,	{FRTp, FRB},	NULL},
{"dctqpq.",	XRC(63,258,1),	X_MASK,      POWER6,	PPCNONE,	{FRTp, FRB},	NULL},

{"fabs",	XRC(63,264,0),	XRA_MASK,    COM,	PPCEFS,		{FRT, FRB},	NULL},
{"fabs.",	XRC(63,264,1),	XRA_MASK,    COM,	PPCEFS,		{FRT, FRB},	NULL},

{"dctfixq",	XRC(63,290,0),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRBp},	NULL},
{"dctfixq.",	XRC(63,290,1),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRBp},	NULL},

{"ddedpdq",	XRC(63,322,0),	X_MASK,      POWER6,	PPCNONE,	{SP, FRTp, FRBp},	NULL},
{"ddedpdq.",	XRC(63,322,1),	X_MASK,      POWER6,	PPCNONE,	{SP, FRTp, FRBp},	NULL},

{"dxexq",	XRC(63,354,0),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRBp},	NULL},
{"dxexq.",	XRC(63,354,1),	X_MASK,      POWER6,	PPCNONE,	{FRT, FRBp},	NULL},

{"frin",	XRC(63,392,0),	XRA_MASK,    POWER5,	PPCNONE,	{FRT, FRB},	NULL},
{"frin.",	XRC(63,392,1),	XRA_MASK,    POWER5,	PPCNONE,	{FRT, FRB},	NULL},
{"friz",	XRC(63,424,0),	XRA_MASK,    POWER5,	PPCNONE,	{FRT, FRB},	NULL},
{"friz.",	XRC(63,424,1),	XRA_MASK,    POWER5,	PPCNONE,	{FRT, FRB},	NULL},
{"frip",	XRC(63,456,0),	XRA_MASK,    POWER5,	PPCNONE,	{FRT, FRB},	NULL},
{"frip.",	XRC(63,456,1),	XRA_MASK,    POWER5,	PPCNONE,	{FRT, FRB},	NULL},
{"frim",	XRC(63,488,0),	XRA_MASK,    POWER5,	PPCNONE,	{FRT, FRB},	NULL},
{"frim.",	XRC(63,488,1),	XRA_MASK,    POWER5,	PPCNONE,	{FRT, FRB},	NULL},

{"dsubq",	XRC(63,514,0),	X_MASK,      POWER6,	PPCNONE,	{FRTp, FRAp, FRBp},	NULL},
{"dsubq.",	XRC(63,514,1),	X_MASK,      POWER6,	PPCNONE,	{FRTp, FRAp, FRBp},	NULL},

{"ddivq",	XRC(63,546,0),	X_MASK,      POWER6,	PPCNONE,	{FRTp, FRAp, FRBp},	NULL},
{"ddivq.",	XRC(63,546,1),	X_MASK,      POWER6,	PPCNONE,	{FRTp, FRAp, FRBp},	NULL},

{"mffs",	XRC(63,583,0),	XRARB_MASK,  COM,	PPCEFS,		{FRT},	NULL},
{"mffs.",	XRC(63,583,1),	XRARB_MASK,  COM,	PPCEFS,		{FRT},	NULL},

{"dcmpuq",	X(63,642),	X_MASK,      POWER6,	PPCNONE,	{BF, FRAp, FRBp},	NULL},

{"dtstsfq",	X(63,674),	X_MASK,      POWER6,	PPCNONE,	{BF, FRA, FRBp},	NULL},

{"mtfsf",	XFL(63,711,0),	XFL_MASK, POWER6|PPCA2|PPC476, PPCNONE,	{FLM, FRB, XFL_L, W},	NULL},
{"mtfsf",	XFL(63,711,0),	XFL_MASK,    COM, POWER6|PPCA2|PPC476|PPCEFS,	{FLM, FRB},	NULL},
{"mtfsf.",	XFL(63,711,1),	XFL_MASK, POWER6|PPCA2|PPC476, PPCNONE,	{FLM, FRB, XFL_L, W},	NULL},
{"mtfsf.",	XFL(63,711,1),	XFL_MASK,    COM, POWER6|PPCA2|PPC476|PPCEFS,	{FLM, FRB},	NULL},

{"drdpq",	XRC(63,770,0),	X_MASK,      POWER6,	PPCNONE,	{FRTp, FRBp},	NULL},
{"drdpq.",	XRC(63,770,1),	X_MASK,      POWER6,	PPCNONE,	{FRTp, FRBp},	NULL},

{"dcffixq",	XRC(63,802,0),	X_MASK,      POWER6,	PPCNONE,	{FRTp, FRB},	NULL},
{"dcffixq.",	XRC(63,802,1),	X_MASK,      POWER6,	PPCNONE,	{FRTp, FRB},	NULL},

{"fctid",	XRC(63,814,0),	XRA_MASK,    PPC64,	PPCNONE,	{FRT, FRB},	NULL},
{"fctid",	XRC(63,814,0),	XRA_MASK,    PPC476,	PPCNONE,	{FRT, FRB},	NULL},
{"fctid.",	XRC(63,814,1),	XRA_MASK,    PPC64,	PPCNONE,	{FRT, FRB},	NULL},
{"fctid.",	XRC(63,814,1),	XRA_MASK,    PPC476,	PPCNONE,	{FRT, FRB},	NULL},

{"fctidz",	XRC(63,815,0),	XRA_MASK,    PPC64,	PPCNONE,	{FRT, FRB},	NULL},
{"fctidz",	XRC(63,815,0),	XRA_MASK,    PPC476,	PPCNONE,	{FRT, FRB},	NULL},
{"fctidz.",	XRC(63,815,1),	XRA_MASK,    PPC64,	PPCNONE,	{FRT, FRB},	NULL},
{"fctidz.",	XRC(63,815,1),	XRA_MASK,    PPC476,	PPCNONE,	{FRT, FRB},	NULL},

{"denbcdq",	XRC(63,834,0),	X_MASK,      POWER6,	PPCNONE,	{S, FRTp, FRBp},	NULL},
{"denbcdq.",	XRC(63,834,1),	X_MASK,      POWER6,	PPCNONE,	{S, FRTp, FRBp},	NULL},

{"fmrgow",	X(63,838),	X_MASK,      PPCVSX2,	PPCNONE,	{FRT, FRA, FRB},	NULL},

{"fcfid",	XRC(63,846,0),	XRA_MASK,    PPC64,	PPCNONE,	{FRT, FRB},	NULL},
{"fcfid",	XRC(63,846,0),	XRA_MASK,    PPC476,	PPCNONE,	{FRT, FRB},	NULL},
{"fcfid.",	XRC(63,846,1),	XRA_MASK,    PPC64,	PPCNONE,	{FRT, FRB},	NULL},
{"fcfid.",	XRC(63,846,1),	XRA_MASK,    PPC476,	PPCNONE,	{FRT, FRB},	NULL},

{"diexq",	XRC(63,866,0),	X_MASK,      POWER6,	PPCNONE,	{FRTp, FRA, FRBp},	NULL},
{"diexq.",	XRC(63,866,1),	X_MASK,      POWER6,	PPCNONE,	{FRTp, FRA, FRBp},	NULL},

{"fctidu",	XRC(63,942,0),	XRA_MASK, POWER7|PPCA2,	PPCNONE,	{FRT, FRB},	NULL},
{"fctidu.",	XRC(63,942,1),	XRA_MASK, POWER7|PPCA2,	PPCNONE,	{FRT, FRB},	NULL},

{"fctiduz",	XRC(63,943,0),	XRA_MASK, POWER7|PPCA2,	PPCNONE,	{FRT, FRB},	NULL},
{"fctiduz.",	XRC(63,943,1),	XRA_MASK, POWER7|PPCA2,	PPCNONE,	{FRT, FRB},	NULL},

{"fmrgew",	X(63,966),	X_MASK,      PPCVSX2,	PPCNONE,	{FRT, FRA, FRB},	NULL},

{"fcfidu",	XRC(63,974,0),	XRA_MASK, POWER7|PPCA2,	PPCNONE,	{FRT, FRB},	NULL},
{"fcfidu.",	XRC(63,974,1),	XRA_MASK, POWER7|PPCA2,	PPCNONE,	{FRT, FRB},	NULL},
};

const int powerpc_num_opcodes =
  sizeof (powerpc_opcodes) / sizeof (powerpc_opcodes[0]);

/* The VLE opcode table.

   The format of this opcode table is the same as the main opcode table.  */

const struct powerpc_opcode vle_opcodes[] = {

{"se_illegal",	C(0),		C_MASK,		PPCVLE,	PPCNONE,	{UNUSED},	NULL},
{"se_isync",	C(1),		C_MASK,		PPCVLE,	PPCNONE,	{UNUSED},	NULL},
{"se_sc",	C(2),		C_MASK,		PPCVLE,	PPCNONE,	{UNUSED},	NULL},
{"se_blr",	C_LK(2,0),	C_LK_MASK,	PPCVLE,	PPCNONE,	{UNUSED},	NULL},
{"se_blrl",	C_LK(2,1),	C_LK_MASK,	PPCVLE,	PPCNONE,	{UNUSED},	NULL},
{"se_bctr",	C_LK(3,0),	C_LK_MASK,	PPCVLE,	PPCNONE,	{UNUSED},	NULL},
{"se_bctrl",	C_LK(3,1),	C_LK_MASK,	PPCVLE,	PPCNONE,	{UNUSED},	NULL},
{"se_rfi",	C(8),		C_MASK,		PPCVLE,	PPCNONE,	{UNUSED},	NULL},
{"se_rfci",	C(9),		C_MASK,		PPCVLE,	PPCNONE,	{UNUSED},	NULL},
{"se_rfdi",	C(10),		C_MASK,		PPCVLE,	PPCNONE,	{UNUSED},	NULL},
{"se_rfmci",	C(11),		C_MASK,		PPCVLE,	PPCNONE,	{UNUSED},	NULL},
{"se_rfgi",	C(12),		C_MASK,		PPCVLE,	PPCNONE,{ UNUSED },	NULL },
{"se_not",	SE_R(0,2),	SE_R_MASK,	PPCVLE,	PPCNONE,	{RX},	NULL},
{"se_neg",	SE_R(0,3),	SE_R_MASK,	PPCVLE,	PPCNONE,	{RX},	NULL},
{"se_mflr",	SE_R(0,8),	SE_R_MASK,	PPCVLE,	PPCNONE,	{RX},	NULL},
{"se_mtlr",	SE_R(0,9),	SE_R_MASK,	PPCVLE,	PPCNONE,	{RX},	NULL},
{"se_mfctr",	SE_R(0,10),	SE_R_MASK,	PPCVLE,	PPCNONE,	{RX},	NULL},
{"se_mtctr",	SE_R(0,11),	SE_R_MASK,	PPCVLE,	PPCNONE,	{RX},	NULL},
{"se_extzb",	SE_R(0,12),	SE_R_MASK,	PPCVLE,	PPCNONE,	{RX},	NULL},
{"se_extsb",	SE_R(0,13),	SE_R_MASK,	PPCVLE,	PPCNONE,	{RX},	NULL},
{"se_extzh",	SE_R(0,14),	SE_R_MASK,	PPCVLE,	PPCNONE,	{RX},	NULL},
{"se_extsh",	SE_R(0,15),	SE_R_MASK,	PPCVLE,	PPCNONE,	{RX},	NULL},
{"se_mr",	SE_RR(0,1),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, RY},	NULL},
{"se_mtar",	SE_RR(0,2),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{ARX, RY},	NULL},
{"se_mfar",	SE_RR(0,3),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, ARY},	NULL},
{"se_add",	SE_RR(1,0),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, RY},	NULL},
{"se_mullw",	SE_RR(1,1),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, RY},	NULL},
{"se_sub",	SE_RR(1,2),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, RY},	NULL},
{"se_subf",	SE_RR(1,3),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, RY},	NULL},
{"se_cmp",	SE_RR(3,0),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, RY},	NULL},
{"se_cmpl",	SE_RR(3,1),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, RY},	NULL},
{"se_cmph",	SE_RR(3,2),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, RY},	NULL},
{"se_cmphl",	SE_RR(3,3),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, RY},	NULL},

/* by major opcode */
{"zvaddih",            VX(4, 0x200), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zvsubifh",           VX(4, 0x201), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zvaddh",             VX(4, 0x204), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsubfh",            VX(4, 0x205), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvaddsubfh",         VX(4, 0x206), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsubfaddh",         VX(4, 0x207), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvaddhx",            VX(4, 0x20C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsubfhx",           VX(4, 0x20D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvaddsubfhx",        VX(4, 0x20E), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsubfaddhx",        VX(4, 0x20F), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zaddwus",            VX(4, 0x210), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zsubfwus",           VX(4, 0x211), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zaddwss",            VX(4, 0x212), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zsubfwss",           VX(4, 0x213), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvaddhus",           VX(4, 0x214), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsubfhus",          VX(4, 0x215), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvaddhss",           VX(4, 0x216), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsubfhss",          VX(4, 0x217), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvaddsubfhss",       VX(4, 0x21A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsubfaddhss",       VX(4, 0x21B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvaddhxss",          VX(4, 0x21C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsubfhxss",         VX(4, 0x21D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvaddsubfhxss",      VX(4, 0x21E), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsubfaddhxss",      VX(4, 0x21F), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zaddheuw",           VX(4, 0x220), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zsubfheuw",          VX(4, 0x221), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zaddhesw",           VX(4, 0x222), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zsubfhesw",          VX(4, 0x223), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zaddhouw",           VX(4, 0x224), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zsubfhouw",          VX(4, 0x225), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zaddhosw",           VX(4, 0x226), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zsubfhosw",          VX(4, 0x227), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmergehih",         VX(4, 0x22C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmergeloh",         VX(4, 0x22D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmergehiloh",       VX(4, 0x22E), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmergelohih",       VX(4, 0x22F), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvcmpgthu",          VX(4, 0x230), VX_MASK, PPCLSP, PPCNONE, {CRFD, RA, RB},	NULL},
{"zvcmpgths",          VX(4, 0x230), VX_MASK, PPCLSP, PPCNONE, {CRFD, RA, RB},	NULL},
{"zvcmplthu",          VX(4, 0x231), VX_MASK, PPCLSP, PPCNONE, {CRFD, RA, RB},	NULL},
{"zvcmplths",          VX(4, 0x231), VX_MASK, PPCLSP, PPCNONE, {CRFD, RA, RB},	NULL},
{"zvcmpeqh",           VX(4, 0x232), VX_MASK, PPCLSP, PPCNONE, {CRFD, RA, RB},	NULL},
{"zpkswgshfrs",        VX(4, 0x238), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zpkswgswfrs",        VX(4, 0x239), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvpkshgwshfrs",      VX(4, 0x23A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvpkswshfrs",        VX(4, 0x23B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvpkswuhs",          VX(4, 0x23C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvpkswshs",          VX(4, 0x23D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvpkuwuhs",          VX(4, 0x23E), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsplatih",          VX_LSP(4, 0x23F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, SIMM},	NULL},
{"zvsplatfih",         VX_LSP(4, 0xA3F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, SIMM},	NULL},
{"zcntlsw",            VX_LSP(4, 0x2A3F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zvcntlzh",           VX_LSP(4, 0x323F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zvcntlsh",           VX_LSP(4, 0x3A3F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"znegws",             VX_LSP(4, 0x4A3F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zvnegh",             VX_LSP(4, 0x523F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zvneghs",            VX_LSP(4, 0x5A3F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zvnegho",            VX_LSP(4, 0x623F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zvneghos",           VX_LSP(4, 0x6A3F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zrndwh",             VX_LSP(4, 0x823F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zrndwhss",           VX_LSP(4, 0x8A3F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zvabsh",             VX_LSP(4, 0xA23F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zvabshs",            VX_LSP(4, 0xAA3F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zabsw",              VX_LSP(4, 0xB23F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zabsws",             VX_LSP(4, 0xBA3F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zsatswuw",           VX_LSP(4, 0xC23F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zsatuwsw",           VX_LSP(4, 0xCA3F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zsatswuh",           VX_LSP(4, 0xD23F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zsatswsh",           VX_LSP(4, 0xDA3F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zvsatshuh",          VX_LSP(4, 0xE23F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zvsatuhsh",          VX_LSP(4, 0xEA3F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zsatuwuh",           VX_LSP(4, 0xF23F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zsatuwsh",           VX_LSP(4, 0xFA3F), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zsatsduw",           VX(4, 0x260), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zsatsdsw",           VX(4, 0x261), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zsatuduw",           VX(4, 0x262), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvselh",             VX(4, 0x264), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zxtrw",              VX(4, 0x264), VX_LSP_OFF_MASK, PPCLSP, PPCNONE, {RD, RA, RB, VX_OFF},	NULL},
{"zbrminc",            VX(4, 0x268), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zcircinc",           VX(4, 0x269), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zdivwsf",            VX(4, 0x26B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsrhu",             VX(4, 0x270), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsrhs",             VX(4, 0x271), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsrhiu",            VX(4, 0x272), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zvsrhis",            VX(4, 0x273), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zvslh",              VX(4, 0x274), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvrlh",              VX(4, 0x275), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvslhi",             VX(4, 0x276), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zvrlhi",             VX(4, 0x277), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zvslhus",            VX(4, 0x278), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvslhss",            VX(4, 0x279), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvslhius",           VX(4, 0x27A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zvslhiss",           VX(4, 0x27B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zslwus",             VX(4, 0x27C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zslwss",             VX(4, 0x27D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zslwius",            VX(4, 0x27E), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zslwiss",            VX(4, 0x27F), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zaddwgui",           VX(4, 0x460), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zsubfwgui",          VX(4, 0x461), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zaddd",              VX(4, 0x462), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zsubfd",             VX(4, 0x463), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvaddsubfw",         VX(4, 0x464), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsubfaddw",         VX(4, 0x465), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvaddw",             VX(4, 0x466), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsubfw",            VX(4, 0x467), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zaddwgsi",           VX(4, 0x468), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zsubfwgsi",          VX(4, 0x469), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zadddss",            VX(4, 0x46A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zsubfdss",           VX(4, 0x46B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvaddsubfwss",       VX(4, 0x46C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsubfaddwss",       VX(4, 0x46D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvaddwss",           VX(4, 0x46E), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsubfwss",          VX(4, 0x46F), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zaddwgsf",           VX(4, 0x470), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zsubfwgsf",          VX(4, 0x471), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zadddus",            VX(4, 0x472), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zsubfdus",           VX(4, 0x473), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvaddwus",           VX(4, 0x476), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvsubfwus",          VX(4, 0x477), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvunpkhgwsf",        VX_LSP(4, 0x478), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zvunpkhsf",          VX_LSP(4, 0xC78), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zvunpkhui",          VX_LSP(4, 0x1478), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zvunpkhsi",          VX_LSP(4, 0x1C78), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zunpkwgsf",          VX_LSP(4, 0x2478), VX_LSP_MASK, PPCLSP, PPCNONE, {RD, RA},	NULL},
{"zvdotphgwasmf",      VX(4, 0x488), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgwasmfr",     VX(4, 0x489), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgwasmfaa",    VX(4, 0x48A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgwasmfraa",   VX(4, 0x48B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgwasmfan",    VX(4, 0x48C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgwasmfran",   VX(4, 0x48D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulgwsmf",        VX(4, 0x490), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulgwsmfr",       VX(4, 0x491), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulgwsmfaa",      VX(4, 0x492), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulgwsmfraa",     VX(4, 0x493), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulgwsmfan",      VX(4, 0x494), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulgwsmfran",     VX(4, 0x495), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulgwsmfanp",     VX(4, 0x496), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulgwsmfranp",    VX(4, 0x497), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhegwsmf",          VX(4, 0x498), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhegwsmfr",         VX(4, 0x499), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhegwsmfaa",        VX(4, 0x49A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhegwsmfraa",       VX(4, 0x49B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhegwsmfan",        VX(4, 0x49C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhegwsmfran",       VX(4, 0x49D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgwasmf",     VX(4, 0x4A8), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgwasmfr",    VX(4, 0x4A9), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgwasmfaa",   VX(4, 0x4AA), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgwasmfraa",  VX(4, 0x4AB), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgwasmfan",   VX(4, 0x4AC), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgwasmfran",  VX(4, 0x4AD), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllgwsmf",        VX(4, 0x4B0), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllgwsmfr",       VX(4, 0x4B1), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllgwsmfaa",      VX(4, 0x4B2), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllgwsmfraa",     VX(4, 0x4B3), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllgwsmfan",      VX(4, 0x4B4), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllgwsmfran",     VX(4, 0x4B5), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllgwsmfanp",     VX(4, 0x4B6), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllgwsmfranp",    VX(4, 0x4B7), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheogwsmf",         VX(4, 0x4B8), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheogwsmfr",        VX(4, 0x4B9), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheogwsmfaa",       VX(4, 0x4BA), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheogwsmfraa",      VX(4, 0x4BB), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheogwsmfan",       VX(4, 0x4BC), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheogwsmfran",      VX(4, 0x4BD), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgwssmf",      VX(4, 0x4C8), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgwssmfr",     VX(4, 0x4C9), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgwssmfaa",    VX(4, 0x4CA), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgwssmfraa",   VX(4, 0x4CB), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgwssmfan",    VX(4, 0x4CC), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgwssmfran",   VX(4, 0x4CD), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuugwsmf",        VX(4, 0x4D0), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuugwsmfr",       VX(4, 0x4D1), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuugwsmfaa",      VX(4, 0x4D2), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuugwsmfraa",     VX(4, 0x4D3), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuugwsmfan",      VX(4, 0x4D4), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuugwsmfran",     VX(4, 0x4D5), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuugwsmfanp",     VX(4, 0x4D6), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuugwsmfranp",    VX(4, 0x4D7), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhogwsmf",          VX(4, 0x4D8), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhogwsmfr",         VX(4, 0x4D9), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhogwsmfaa",        VX(4, 0x4DA), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhogwsmfraa",       VX(4, 0x4DB), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhogwsmfan",        VX(4, 0x4DC), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhogwsmfran",       VX(4, 0x4DD), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlgwsmf",        VX(4, 0x4F0), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlgwsmfr",       VX(4, 0x4F1), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlgwsmfaa",      VX(4, 0x4F2), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlgwsmfraa",     VX(4, 0x4F3), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlgwsmfan",      VX(4, 0x4F4), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlgwsmfran",     VX(4, 0x4F5), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlgwsmfanp",     VX(4, 0x4F6), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlgwsmfranp",    VX(4, 0x4F7), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhegui",            VX(4, 0x500), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgaui",        VX(4, 0x501), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheguiaa",          VX(4, 0x502), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgauiaa",      VX(4, 0x503), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheguian",          VX(4, 0x504), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgauian",      VX(4, 0x505), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhegsi",            VX(4, 0x508), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgasi",        VX(4, 0x509), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhegsiaa",          VX(4, 0x50A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgasiaa",      VX(4, 0x50B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhegsian",          VX(4, 0x50C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgasian",      VX(4, 0x50D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhegsui",           VX(4, 0x510), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgasui",       VX(4, 0x511), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhegsuiaa",         VX(4, 0x512), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgasuiaa",     VX(4, 0x513), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhegsuian",         VX(4, 0x514), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgasuian",     VX(4, 0x515), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhegsmf",           VX(4, 0x518), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgasmf",       VX(4, 0x519), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhegsmfaa",         VX(4, 0x51A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgasmfaa",     VX(4, 0x51B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhegsmfan",         VX(4, 0x51C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgasmfan",     VX(4, 0x51D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheogui",           VX(4, 0x520), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgaui",       VX(4, 0x521), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheoguiaa",         VX(4, 0x522), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgauiaa",     VX(4, 0x523), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheoguian",         VX(4, 0x524), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgauian",     VX(4, 0x525), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheogsi",           VX(4, 0x528), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgasi",       VX(4, 0x529), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheogsiaa",         VX(4, 0x52A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgasiaa",     VX(4, 0x52B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheogsian",         VX(4, 0x52C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgasian",     VX(4, 0x52D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheogsui",          VX(4, 0x530), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgasui",      VX(4, 0x531), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheogsuiaa",        VX(4, 0x532), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgasuiaa",    VX(4, 0x533), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheogsuian",        VX(4, 0x534), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgasuian",    VX(4, 0x535), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheogsmf",          VX(4, 0x538), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgasmf",      VX(4, 0x539), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheogsmfaa",        VX(4, 0x53A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgasmfaa",    VX(4, 0x53B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheogsmfan",        VX(4, 0x53C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxgasmfan",    VX(4, 0x53D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhogui",            VX(4, 0x540), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgsui",        VX(4, 0x541), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhoguiaa",          VX(4, 0x542), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgsuiaa",      VX(4, 0x543), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhoguian",          VX(4, 0x544), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgsuian",      VX(4, 0x545), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhogsi",            VX(4, 0x548), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgssi",        VX(4, 0x549), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhogsiaa",          VX(4, 0x54A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgssiaa",      VX(4, 0x54B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhogsian",          VX(4, 0x54C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgssian",      VX(4, 0x54D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhogsui",           VX(4, 0x550), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgssui",       VX(4, 0x551), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhogsuiaa",         VX(4, 0x552), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgssuiaa",     VX(4, 0x553), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhogsuian",         VX(4, 0x554), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgssuian",     VX(4, 0x555), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhogsmf",           VX(4, 0x558), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgssmf",       VX(4, 0x559), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhogsmfaa",         VX(4, 0x55A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgssmfaa",     VX(4, 0x55B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhogsmfan",         VX(4, 0x55C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphgssmfan",     VX(4, 0x55D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgui",             VX(4, 0x560), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwguiaa",           VX(4, 0x562), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwguiaas",          VX(4, 0x563), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwguian",           VX(4, 0x564), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwguians",          VX(4, 0x565), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgsi",             VX(4, 0x568), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgsiaa",           VX(4, 0x56A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgsiaas",          VX(4, 0x56B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgsian",           VX(4, 0x56C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgsians",          VX(4, 0x56D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgsui",            VX(4, 0x570), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgsuiaa",          VX(4, 0x572), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgsuiaas",         VX(4, 0x573), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgsuian",          VX(4, 0x574), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgsuians",         VX(4, 0x575), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgsmf",            VX(4, 0x578), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgsmfr",           VX(4, 0x579), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgsmfaa",          VX(4, 0x57A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgsmfraa",         VX(4, 0x57B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgsmfan",          VX(4, 0x57C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwgsmfran",         VX(4, 0x57D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhului",           VX(4, 0x580), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuluiaa",         VX(4, 0x582), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuluiaas",        VX(4, 0x583), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuluian",         VX(4, 0x584), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuluians",        VX(4, 0x585), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuluianp",        VX(4, 0x586), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuluianps",       VX(4, 0x587), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsi",           VX(4, 0x588), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsiaa",         VX(4, 0x58A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsiaas",        VX(4, 0x58B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsian",         VX(4, 0x58C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsians",        VX(4, 0x58D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsianp",        VX(4, 0x58E), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsianps",       VX(4, 0x58F), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsui",          VX(4, 0x590), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsuiaa",        VX(4, 0x592), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsuiaas",       VX(4, 0x593), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsuian",        VX(4, 0x594), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsuians",       VX(4, 0x595), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsuianp",       VX(4, 0x596), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsuianps",      VX(4, 0x597), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsf",           VX(4, 0x598), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsfr",          VX(4, 0x599), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsfaas",        VX(4, 0x59A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsfraas",       VX(4, 0x59B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsfans",        VX(4, 0x59C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsfrans",       VX(4, 0x59D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsfanps",       VX(4, 0x59E), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhulsfranps",      VX(4, 0x59F), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllui",           VX(4, 0x5A0), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhlluiaa",         VX(4, 0x5A2), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhlluiaas",        VX(4, 0x5A3), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhlluian",         VX(4, 0x5A4), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhlluians",        VX(4, 0x5A5), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhlluianp",        VX(4, 0x5A6), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhlluianps",       VX(4, 0x5A7), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsi",           VX(4, 0x5A8), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsiaa",         VX(4, 0x5AA), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsiaas",        VX(4, 0x5AB), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsian",         VX(4, 0x5AC), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsians",        VX(4, 0x5AD), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsianp",        VX(4, 0x5AE), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsianps",       VX(4, 0x5AF), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsui",          VX(4, 0x5B0), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsuiaa",        VX(4, 0x5B2), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsuiaas",       VX(4, 0x5B3), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsuian",        VX(4, 0x5B4), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsuians",       VX(4, 0x5B5), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsuianp",       VX(4, 0x5B6), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsuianps",      VX(4, 0x5B7), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsf",           VX(4, 0x5B8), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsfr",          VX(4, 0x5B9), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsfaas",        VX(4, 0x5BA), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsfraas",       VX(4, 0x5BB), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsfans",        VX(4, 0x5BC), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsfrans",       VX(4, 0x5BD), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsfanps",       VX(4, 0x5BE), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhllsfranps",      VX(4, 0x5BF), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuuui",           VX(4, 0x5C0), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuuuiaa",         VX(4, 0x5C2), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuuuiaas",        VX(4, 0x5C3), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuuuian",         VX(4, 0x5C4), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuuuians",        VX(4, 0x5C5), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuuuianp",        VX(4, 0x5C6), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuuuianps",       VX(4, 0x5C7), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusi",           VX(4, 0x5C8), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusiaa",         VX(4, 0x5CA), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusiaas",        VX(4, 0x5CB), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusian",         VX(4, 0x5CC), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusians",        VX(4, 0x5CD), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusianp",        VX(4, 0x5CE), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusianps",       VX(4, 0x5CF), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusui",          VX(4, 0x5D0), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusuiaa",        VX(4, 0x5D2), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusuiaas",       VX(4, 0x5D3), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusuian",        VX(4, 0x5D4), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusuians",       VX(4, 0x5D5), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusuianp",       VX(4, 0x5D6), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusuianps",      VX(4, 0x5D7), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusf",           VX(4, 0x5D8), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusfr",          VX(4, 0x5D9), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusfaas",        VX(4, 0x5DA), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusfraas",       VX(4, 0x5DB), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusfans",        VX(4, 0x5DC), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusfrans",       VX(4, 0x5DD), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusfanps",       VX(4, 0x5DE), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuusfranps",      VX(4, 0x5DF), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlui",           VX(4, 0x5E0), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxluiaa",         VX(4, 0x5E2), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxluiaas",        VX(4, 0x5E3), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxluian",         VX(4, 0x5E4), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxluians",        VX(4, 0x5E5), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxluianp",        VX(4, 0x5E6), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxluianps",       VX(4, 0x5E7), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsi",           VX(4, 0x5E8), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsiaa",         VX(4, 0x5EA), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsiaas",        VX(4, 0x5EB), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsian",         VX(4, 0x5EC), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsians",        VX(4, 0x5ED), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsianp",        VX(4, 0x5EE), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsianps",       VX(4, 0x5EF), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsui",          VX(4, 0x5F0), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsuiaa",        VX(4, 0x5F2), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsuiaas",       VX(4, 0x5F3), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsuian",        VX(4, 0x5F4), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsuians",       VX(4, 0x5F5), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsuianp",       VX(4, 0x5F6), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsuianps",      VX(4, 0x5F7), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsf",           VX(4, 0x5F8), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsfr",          VX(4, 0x5F9), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsfaas",        VX(4, 0x5FA), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsfraas",       VX(4, 0x5FB), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsfans",        VX(4, 0x5FC), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsfrans",       VX(4, 0x5FD), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsfanps",       VX(4, 0x5FE), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhxlsfranps",      VX(4, 0x5FF), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheui",             VX(4, 0x600), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheuiaa",           VX(4, 0x602), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheuiaas",          VX(4, 0x603), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheuian",           VX(4, 0x604), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheuians",          VX(4, 0x605), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhesi",             VX(4, 0x608), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhesiaa",           VX(4, 0x60A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhesiaas",          VX(4, 0x60B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhesian",           VX(4, 0x60C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhesians",          VX(4, 0x60D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhesui",            VX(4, 0x610), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhesuiaa",          VX(4, 0x612), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhesuiaas",         VX(4, 0x613), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhesuian",          VX(4, 0x614), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhesuians",         VX(4, 0x615), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhesf",             VX(4, 0x618), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhesfr",            VX(4, 0x619), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhesfaas",          VX(4, 0x61A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhesfraas",         VX(4, 0x61B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhesfans",          VX(4, 0x61C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhesfrans",         VX(4, 0x61D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheoui",            VX(4, 0x620), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheouiaa",          VX(4, 0x622), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheouiaas",         VX(4, 0x623), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheouian",          VX(4, 0x624), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheouians",         VX(4, 0x625), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheosi",            VX(4, 0x628), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheosiaa",          VX(4, 0x62A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheosiaas",         VX(4, 0x62B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheosian",          VX(4, 0x62C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheosians",         VX(4, 0x62D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheosui",           VX(4, 0x630), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheosuiaa",         VX(4, 0x632), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheosuiaas",        VX(4, 0x633), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheosuian",         VX(4, 0x634), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheosuians",        VX(4, 0x635), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheosf",            VX(4, 0x638), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheosfr",           VX(4, 0x639), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheosfaas",         VX(4, 0x63A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheosfraas",        VX(4, 0x63B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheosfans",         VX(4, 0x63C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmheosfrans",        VX(4, 0x63D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhoui",             VX(4, 0x640), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhouiaa",           VX(4, 0x642), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhouiaas",          VX(4, 0x643), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhouian",           VX(4, 0x644), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhouians",          VX(4, 0x645), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhosi",             VX(4, 0x648), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhosiaa",           VX(4, 0x64A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhosiaas",          VX(4, 0x64B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhosian",           VX(4, 0x64C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhosians",          VX(4, 0x64D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhosui",            VX(4, 0x650), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhosuiaa",          VX(4, 0x652), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhosuiaas",         VX(4, 0x653), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhosuian",          VX(4, 0x654), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhosuians",         VX(4, 0x655), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhosf",             VX(4, 0x658), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhosfr",            VX(4, 0x659), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhosfaas",          VX(4, 0x65A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhosfraas",         VX(4, 0x65B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhosfans",          VX(4, 0x65C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmhosfrans",         VX(4, 0x65D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuih",            VX(4, 0x660), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuihs",           VX(4, 0x661), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuiaah",          VX(4, 0x662), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuiaahs",         VX(4, 0x663), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuianh",          VX(4, 0x664), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhuianhs",         VX(4, 0x665), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhsihs",           VX(4, 0x669), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhsiaahs",         VX(4, 0x66B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhsianhs",         VX(4, 0x66D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhsuihs",          VX(4, 0x671), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhsuiaahs",        VX(4, 0x673), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhsuianhs",        VX(4, 0x675), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhsfh",            VX(4, 0x678), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhsfrh",           VX(4, 0x679), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhsfaahs",         VX(4, 0x67A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhsfraahs",        VX(4, 0x67B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhsfanhs",         VX(4, 0x67C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvmhsfranhs",        VX(4, 0x67D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphaui",         VX(4, 0x680), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphauis",        VX(4, 0x681), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphauiaa",       VX(4, 0x682), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphauiaas",      VX(4, 0x683), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphauian",       VX(4, 0x684), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphauians",      VX(4, 0x685), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasi",         VX(4, 0x688), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasis",        VX(4, 0x689), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasiaa",       VX(4, 0x68A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasiaas",      VX(4, 0x68B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasian",       VX(4, 0x68C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasians",      VX(4, 0x68D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasui",        VX(4, 0x690), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasuis",       VX(4, 0x691), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasuiaa",      VX(4, 0x692), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasuiaas",     VX(4, 0x693), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasuian",      VX(4, 0x694), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasuians",     VX(4, 0x695), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasfs",        VX(4, 0x698), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasfrs",       VX(4, 0x699), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasfaas",      VX(4, 0x69A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasfraas",     VX(4, 0x69B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasfans",      VX(4, 0x69C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphasfrans",     VX(4, 0x69D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxaui",        VX(4, 0x6A0), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxauis",       VX(4, 0x6A1), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxauiaa",      VX(4, 0x6A2), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxauiaas",     VX(4, 0x6A3), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxauian",      VX(4, 0x6A4), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxauians",     VX(4, 0x6A5), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasi",        VX(4, 0x6A8), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasis",       VX(4, 0x6A9), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasiaa",      VX(4, 0x6AA), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasiaas",     VX(4, 0x6AB), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasian",      VX(4, 0x6AC), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasians",     VX(4, 0x6AD), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasui",       VX(4, 0x6B0), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasuis",      VX(4, 0x6B1), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasuiaa",     VX(4, 0x6B2), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasuiaas",    VX(4, 0x6B3), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasuian",     VX(4, 0x6B4), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasuians",    VX(4, 0x6B5), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasfs",       VX(4, 0x6B8), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasfrs",      VX(4, 0x6B9), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasfaas",     VX(4, 0x6BA), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasfraas",    VX(4, 0x6BB), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasfans",     VX(4, 0x6BC), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphxasfrans",    VX(4, 0x6BD), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphsui",         VX(4, 0x6C0), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphsuis",        VX(4, 0x6C1), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphsuiaa",       VX(4, 0x6C2), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphsuiaas",      VX(4, 0x6C3), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphsuian",       VX(4, 0x6C4), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphsuians",      VX(4, 0x6C5), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssi",         VX(4, 0x6C8), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssis",        VX(4, 0x6C9), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssiaa",       VX(4, 0x6CA), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssiaas",      VX(4, 0x6CB), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssian",       VX(4, 0x6CC), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssians",      VX(4, 0x6CD), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssui",        VX(4, 0x6D0), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssuis",       VX(4, 0x6D1), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssuiaa",      VX(4, 0x6D2), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssuiaas",     VX(4, 0x6D3), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssuian",      VX(4, 0x6D4), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssuians",     VX(4, 0x6D5), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssfs",        VX(4, 0x6D8), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssfrs",       VX(4, 0x6D9), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssfaas",      VX(4, 0x6DA), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssfraas",     VX(4, 0x6DB), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssfans",      VX(4, 0x6DC), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zvdotphssfrans",     VX(4, 0x6DD), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwluis",            VX(4, 0x6E1), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwluiaa",           VX(4, 0x6E2), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwluiaas",          VX(4, 0x6E3), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwluian",           VX(4, 0x6E4), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwluians",          VX(4, 0x6E5), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwlsis",            VX(4, 0x6E9), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwlsiaas",          VX(4, 0x6EB), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwlsians",          VX(4, 0x6ED), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwlsuis",           VX(4, 0x6F1), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwlsuiaas",         VX(4, 0x6F3), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwlsuians",         VX(4, 0x6F5), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwsf",              VX(4, 0x6F8), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwsfr",             VX(4, 0x6F9), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwsfaas",           VX(4, 0x6FA), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwsfraas",          VX(4, 0x6FB), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwsfans",           VX(4, 0x6FC), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zmwsfrans",          VX(4, 0x6FD), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlddx",              VX(4, 0x300), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zldd",               VX(4, 0x301), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zldwx",              VX(4, 0x302), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zldw",               VX(4, 0x303), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zldhx",              VX(4, 0x304), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zldh",               VX(4, 0x305), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwgsfdx",           VX(4, 0x308), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwgsfd",            VX(4, 0x309), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwwosdx",           VX(4, 0x30A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwwosd",            VX(4, 0x30B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwhsplatwdx",       VX(4, 0x30C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwhsplatwd",        VX(4, 0x30D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwhsplatdx",        VX(4, 0x30E), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwhsplatd",         VX(4, 0x30F), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwhgwsfdx",         VX(4, 0x310), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwhgwsfd",          VX(4, 0x311), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwhedx",            VX(4, 0x312), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwhed",             VX(4, 0x313), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwhosdx",           VX(4, 0x314), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwhosd",            VX(4, 0x315), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwhoudx",           VX(4, 0x316), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwhoud",            VX(4, 0x317), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwhx",              VX(4, 0x318), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwh",               VX(4, 0x319), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwwx",              VX(4, 0x31A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlww",               VX(4, 0x31B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlhgwsfx",           VX(4, 0x31C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlhgwsf",            VX(4, 0x31D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlhhsplatx",         VX(4, 0x31E), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlhhsplat",          VX(4, 0x31F), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zstddx",             VX(4, 0x320), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zstdd",              VX(4, 0x321), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zstdwx",             VX(4, 0x322), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zstdw",              VX(4, 0x323), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zstdhx",             VX(4, 0x324), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zstdh",              VX(4, 0x325), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zstwhedx",           VX(4, 0x328), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zstwhed",            VX(4, 0x329), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zstwhodx",           VX(4, 0x32A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zstwhod",            VX(4, 0x32B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlhhex",             VX(4, 0x330), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zlhhe",              VX(4, 0x331), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zlhhosx",            VX(4, 0x332), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zlhhos",             VX(4, 0x333), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zlhhoux",            VX(4, 0x334), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zlhhou",             VX(4, 0x335), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zsthex",             VX(4, 0x338), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zsthe",              VX(4, 0x339), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zsthox",             VX(4, 0x33A), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zstho",              VX(4, 0x33B), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zstwhx",             VX(4, 0x33C), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zstwh",              VX(4, 0x33D), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zstwwx",             VX(4, 0x33E), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zstww",              VX(4, 0x33F), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zlddmx",             VX(4, 0x340), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlddu",              VX(4, 0x341), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zldwmx",             VX(4, 0x342), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zldwu",              VX(4, 0x343), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zldhmx",             VX(4, 0x344), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zldhu",              VX(4, 0x345), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwgsfdmx",          VX(4, 0x348), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwgsfdu",           VX(4, 0x349), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwwosdmx",          VX(4, 0x34A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwwosdu",           VX(4, 0x34B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwhsplatwdmx",      VX(4, 0x34C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwhsplatwdu",       VX(4, 0x34D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwhsplatdmx",       VX(4, 0x34E), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwhsplatdu",        VX(4, 0x34F), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwhgwsfdmx",        VX(4, 0x350), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwhgwsfdu",         VX(4, 0x351), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwhedmx",           VX(4, 0x352), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwhedu",            VX(4, 0x353), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwhosdmx",          VX(4, 0x354), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwhosdu",           VX(4, 0x355), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwhoudmx",          VX(4, 0x356), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwhoudu",           VX(4, 0x357), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwhmx",             VX(4, 0x358), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwhu",              VX(4, 0x359), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlwwmx",             VX(4, 0x35A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlwwu",              VX(4, 0x35B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlhgwsfmx",          VX(4, 0x35C), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlhgwsfu",           VX(4, 0x35D), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlhhsplatmx",        VX(4, 0x35E), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zlhhsplatu",         VX(4, 0x35F), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zstddmx",            VX(4, 0x360), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zstddu",             VX(4, 0x361), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zstdwmx",            VX(4, 0x362), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zstdwu",             VX(4, 0x363), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zstdhmx",            VX(4, 0x364), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zstdhu",             VX(4, 0x365), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zstwhedmx",          VX(4, 0x368), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zstwhedu",           VX(4, 0x369), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zstwhodmx",          VX(4, 0x36A), VX_MASK, PPCLSP, PPCNONE, {RD, RA, RB},	NULL},
{"zstwhodu",           VX(4, 0x36B), VX_MASK, PPCLSP, PPCNONE, {RD, RA, EVUIMM},	NULL},
{"zlhhemx",            VX(4, 0x370), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zlhheu",             VX(4, 0x371), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zlhhosmx",           VX(4, 0x372), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zlhhosu",            VX(4, 0x373), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zlhhoumx",           VX(4, 0x374), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zlhhouu",            VX(4, 0x375), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zsthemx",            VX(4, 0x378), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zstheu",             VX(4, 0x379), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zsthomx",            VX(4, 0x37A), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zsthou",             VX(4, 0x37B), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zstwhmx",            VX(4, 0x37C), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zstwhu",             VX(4, 0x37D), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},
{"zstwwmx",            VX(4, 0x37E), VX_MASK, PPCLSP, PPCNONE, {RA, RB, RS},	NULL},
{"zstwwu",             VX(4, 0x37F), VX_MASK, PPCLSP, PPCNONE, {RA, RS, EVUIMM},	NULL},

{"e_cmpi",	SCI8BF(6,0,21),	SCI8BF_MASK,	PPCVLE,	PPCNONE,	{CRD32, RA, SCLSCI8},	NULL},
{"e_cmpli",	SCI8BF(6,1,21),	SCI8BF_MASK,	PPCVLE,	PPCNONE,	{CRD32, RA, SCLSCI8},	NULL},
{"e_addi",	SCI8(6,16),	SCI8_MASK,	PPCVLE,	PPCNONE,	{RT, RA, SCLSCI8},	NULL},
{"e_subi",	SCI8(6,16),	SCI8_MASK,	PPCVLE,	PPCNONE,	{RT, RA, SCLSCI8N},	NULL},
{"e_addi.",	SCI8(6,17),	SCI8_MASK,	PPCVLE,	PPCNONE,	{RT, RA, SCLSCI8},	NULL},
{"e_addic",	SCI8(6,18),	SCI8_MASK,	PPCVLE,	PPCNONE,	{RT, RA, SCLSCI8},	NULL},
{"e_subic",	SCI8(6,18),	SCI8_MASK,	PPCVLE,	PPCNONE,	{RT, RA, SCLSCI8N},	NULL},
{"e_addic.",	SCI8(6,19),	SCI8_MASK,	PPCVLE,	PPCNONE,	{RT, RA, SCLSCI8},	NULL},
{"e_subic.",	SCI8(6,19),	SCI8_MASK,	PPCVLE,	PPCNONE,	{RT, RA, SCLSCI8N},	NULL},
{"e_mulli",	SCI8(6,20),	SCI8_MASK,	PPCVLE,	PPCNONE,	{RT, RA, SCLSCI8},	NULL},
{"e_subfic",	SCI8(6,22),	SCI8_MASK,	PPCVLE,	PPCNONE,	{RT, RA, SCLSCI8},	NULL},
{"e_subfic.",	SCI8(6,23),	SCI8_MASK,	PPCVLE,	PPCNONE,	{RT, RA, SCLSCI8},	NULL},
{"e_andi",	SCI8(6,24),	SCI8_MASK,	PPCVLE,	PPCNONE,	{RA, RS, SCLSCI8},	NULL},
{"e_andi.",	SCI8(6,25),	SCI8_MASK,	PPCVLE,	PPCNONE,	{RA, RS, SCLSCI8},	NULL},
{"e_nop",	SCI8(6,26),	0xffffffff,	PPCVLE,	PPCNONE,	{UNUSED},	NULL},
{"e_ori",	SCI8(6,26),	SCI8_MASK,	PPCVLE,	PPCNONE,	{RA, RS, SCLSCI8},	NULL},
{"e_ori.",	SCI8(6,27),	SCI8_MASK,	PPCVLE,	PPCNONE,	{RA, RS, SCLSCI8},	NULL},
{"e_xori",	SCI8(6,28),	SCI8_MASK,	PPCVLE,	PPCNONE,	{RA, RS, SCLSCI8},	NULL},
{"e_xori.",	SCI8(6,29),	SCI8_MASK,	PPCVLE,	PPCNONE,	{RA, RS, SCLSCI8},	NULL},
{"e_lbzu",	OPVUP(6,0),	OPVUP_MASK,	PPCVLE,	PPCNONE,	{RT, D8, RA0},	NULL},
{"e_lhau",	OPVUP(6,3),	OPVUP_MASK,	PPCVLE,	PPCNONE,	{RT, D8, RA0},	NULL},
{"e_lhzu",	OPVUP(6,1),	OPVUP_MASK,	PPCVLE,	PPCNONE,	{RT, D8, RA0},	NULL},
{"e_lmw",	OPVUP(6,8),	OPVUP_MASK,	PPCVLE,	PPCNONE,	{RT, D8, RA0},	NULL},
{"e_lwzu",	OPVUP(6,2),	OPVUP_MASK,	PPCVLE,	PPCNONE,	{RT, D8, RA0},	NULL},
{"e_stbu",	OPVUP(6,4),	OPVUP_MASK,	PPCVLE,	PPCNONE,	{RT, D8, RA0},	NULL},
{"e_sthu",	OPVUP(6,5),	OPVUP_MASK,	PPCVLE,	PPCNONE,	{RT, D8, RA0},	NULL},
{"e_stwu",	OPVUP(6,6),	OPVUP_MASK,	PPCVLE,	PPCNONE,	{RT, D8, RA0},	NULL},
{"e_stmw",	OPVUP(6,9),	OPVUP_MASK,	PPCVLE,	PPCNONE,	{RT, D8, RA0},	NULL},

{"e_ldmvgprw",	OP_VINT_D8(6,0,0x10), OP_VINT_D8_MASK, PPCVLE, PPCNONE, {D8, RA},	NULL},
{"e_stmvgprw",	OP_VINT_D8(6,0,0x11), OP_VINT_D8_MASK, PPCVLE, PPCNONE, {D8, RA},	NULL},
{"e_ldmvsprw",	OP_VINT_D8(6,1,0x10), OP_VINT_D8_MASK, PPCVLE, PPCNONE, {D8, RA},	NULL},
{"e_stmvsprw",	OP_VINT_D8(6,1,0x11), OP_VINT_D8_MASK, PPCVLE, PPCNONE, {D8, RA},	NULL},
{"e_ldmvsrrw",	OP_VINT_D8(6,4,0x10), OP_VINT_D8_MASK, PPCVLE, PPCNONE, {D8, RA},	NULL},
{"e_stmvsrrw",	OP_VINT_D8(6,4,0x11), OP_VINT_D8_MASK, PPCVLE, PPCNONE, {D8, RA},	NULL},
{"e_ldmvcsrrw",	OP_VINT_D8(6,5,0x10), OP_VINT_D8_MASK, PPCVLE, PPCNONE, {D8, RA},	NULL},
{"e_stmvcsrrw",	OP_VINT_D8(6,5,0x11), OP_VINT_D8_MASK, PPCVLE, PPCNONE, {D8, RA},	NULL},
{"e_ldmvdsrrw",	OP_VINT_D8(6,6,0x10), OP_VINT_D8_MASK, PPCVLE, PPCNONE, {D8, RA},	NULL},
{"e_stmvdsrrw",	OP_VINT_D8(6,6,0x11), OP_VINT_D8_MASK, PPCVLE, PPCNONE, {D8, RA},	NULL},

{"e_add16i",	OP(7),		OP_MASK,	PPCVLE,	PPCNONE,	{RT, RA, SI},	NULL},
{"e_la",	OP(7),		OP_MASK,    	PPCVLE,	PPCNONE,	{RT, D, RA0},	NULL},
{"e_sub16i",	OP(7),		OP_MASK,	PPCVLE,	PPCNONE,	{RT, RA, NSI},	NULL},

{"se_addi",	SE_IM5(8,0),	SE_IM5_MASK,	PPCVLE,	PPCNONE,	{RX, OIMM5},	NULL},
{"se_cmpli",	SE_IM5(8,1),	SE_IM5_MASK,	PPCVLE,	PPCNONE,	{RX, OIMM5},	NULL},
{"se_subi",	SE_IM5(9,0),	SE_IM5_MASK,	PPCVLE,	PPCNONE,	{RX, OIMM5},	NULL},
{"se_subi.",	SE_IM5(9,1),	SE_IM5_MASK,	PPCVLE,	PPCNONE,	{RX, OIMM5},	NULL},
{"se_cmpi",	SE_IM5(10,1),	SE_IM5_MASK,	PPCVLE,	PPCNONE,	{RX, UI5},	NULL},
{"se_bmaski",	SE_IM5(11,0),	SE_IM5_MASK,	PPCVLE,	PPCNONE,	{RX, UI5},	NULL},
{"se_andi",	SE_IM5(11,1),	SE_IM5_MASK,	PPCVLE,	PPCNONE,	{RX, UI5},	NULL},

{"e_lbz",	OP(12),		OP_MASK,	PPCVLE,	PPCNONE,	{RT, D, RA0},	NULL},
{"e_stb",	OP(13),		OP_MASK,	PPCVLE,	PPCNONE,	{RT, D, RA0},	NULL},
{"e_lha",	OP(14),		OP_MASK,	PPCVLE,	PPCNONE,	{RT, D, RA0},	NULL},

{"se_srw",	SE_RR(16,0),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, RY},	NULL},
{"se_sraw",	SE_RR(16,1),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, RY},	NULL},
{"se_slw",	SE_RR(16,2),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, RY},	NULL},
{"se_nop",	SE_RR(17,0),	0xffff,		PPCVLE,	PPCNONE,	{UNUSED},	NULL},
{"se_or",	SE_RR(17,0),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, RY},	NULL},
{"se_andc",	SE_RR(17,1),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, RY},	NULL},
{"se_and",	SE_RR(17,2),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, RY},	NULL},
{"se_and.",	SE_RR(17,3),	SE_RR_MASK,	PPCVLE,	PPCNONE,	{RX, RY},	NULL},
{"se_li",	IM7(9),		IM7_MASK,	PPCVLE,	PPCNONE,	{RX, UI7},	NULL},

{"e_lwz",	OP(20),		OP_MASK,	PPCVLE,	PPCNONE,	{RT, D, RA0},	NULL},
{"e_stw",	OP(21),		OP_MASK,	PPCVLE,	PPCNONE,	{RT, D, RA0},	NULL},
{"e_lhz",	OP(22),		OP_MASK,	PPCVLE,	PPCNONE,	{RT, D, RA0},	NULL},
{"e_sth",	OP(23),		OP_MASK,	PPCVLE,	PPCNONE,	{RT, D, RA0},	NULL},

{"se_bclri",	SE_IM5(24,0),	SE_IM5_MASK,	PPCVLE,	PPCNONE,	{RX, UI5},	NULL},
{"se_bgeni",	SE_IM5(24,1),	SE_IM5_MASK,	PPCVLE,	PPCNONE,	{RX, UI5},	NULL},
{"se_bseti",	SE_IM5(25,0),	SE_IM5_MASK,	PPCVLE,	PPCNONE,	{RX, UI5},	NULL},
{"se_btsti",	SE_IM5(25,1),	SE_IM5_MASK,	PPCVLE,	PPCNONE,	{RX, UI5},	NULL},
{"se_srwi",	SE_IM5(26,0),	SE_IM5_MASK,	PPCVLE,	PPCNONE,	{RX, UI5},	NULL},
{"se_srawi",	SE_IM5(26,1),	SE_IM5_MASK,	PPCVLE,	PPCNONE,	{RX, UI5},	NULL},
{"se_slwi",	SE_IM5(27,0),	SE_IM5_MASK,	PPCVLE,	PPCNONE,	{RX, UI5},	NULL},

{"e_lis",	I16L(28,28),	I16L_MASK,	PPCVLE,	PPCNONE,	{RD, VLEUIMML},	NULL},
{"e_and2is.",	I16L(28,29),	I16L_MASK,	PPCVLE,	PPCNONE,	{RD, VLEUIMML},	NULL},
{"e_or2is",	I16L(28,26),	I16L_MASK,	PPCVLE,	PPCNONE,	{RD, VLEUIMML},	NULL},
{"e_and2i.",	I16L(28,25),	I16L_MASK,	PPCVLE,	PPCNONE,	{RD, VLEUIMML},	NULL},
{"e_or2i",	I16L(28,24),	I16L_MASK,	PPCVLE,	PPCNONE,	{RD, VLEUIMML},	NULL},
{"e_cmphl16i",	IA16(28,23),	IA16_MASK,	PPCVLE,	PPCNONE,	{RA, VLEUIMM},	NULL},
{"e_cmph16i",	IA16(28,22),	IA16_MASK,	PPCVLE,	PPCNONE,	{RA, VLESIMM},	NULL},
{"e_cmpl16i",	I16A(28,21),	I16A_MASK,	PPCVLE,	PPCNONE,	{RA, VLEUIMM},	NULL},
{"e_cmplwi",	I16A(28,21),	I16A_MASK,	PPCVLE,	PPCNONE,	{RA, VLESIMM},	NULL},
{"e_mull2i",	I16A(28,20),	I16A_MASK,	PPCVLE,	PPCNONE,	{RA, VLESIMM},	NULL},
{"e_cmp16i",	IA16(28,19),	IA16_MASK,	PPCVLE,	PPCNONE,	{RA, VLESIMM},	NULL},
{"e_cmpwi",	IA16(28,19),	IA16_MASK,	PPCVLE,	PPCNONE,	{RA, VLESIMM},	NULL},
{"e_sub2is",	I16A(28,18),	I16A_MASK,	PPCVLE,	PPCNONE,	{RA, VLENSIMM},	NULL},
{"e_add2is",	I16A(28,18),	I16A_MASK,	PPCVLE,	PPCNONE,	{RA, VLESIMM},	NULL},
{"e_sub2i.",	I16A(28,17),	I16A_MASK,	PPCVLE,	PPCNONE,	{RA, VLENSIMM},	NULL},
{"e_add2i.",	I16A(28,17),	I16A_MASK,	PPCVLE,	PPCNONE,	{RA, VLESIMM},	NULL},
{"e_li",	LI20(28,0),	LI20_MASK,	PPCVLE,	PPCNONE,	{RT, IMM20},	NULL},
{"e_rlwimi",	M(29,0),	M_MASK,		PPCVLE,	PPCNONE,	{RA, RS, SH, MB, ME},	NULL},
{"e_rlwinm",	M(29,1),	M_MASK,		PPCVLE,	PPCNONE,	{RA, RT, SH, MBE, ME},	NULL},
{"e_b",		BD24(30,0,0),	BD24_MASK,	PPCVLE,	PPCNONE,	{B24},	NULL},
{"e_bl",	BD24(30,0,1),	BD24_MASK,	PPCVLE,	PPCNONE,	{B24},	NULL},
{"e_bdnz",	EBD15(30,8,BO32DNZ,0),	EBD15_MASK, PPCVLE, PPCNONE,	{B15},	NULL},
{"e_bdnzl",	EBD15(30,8,BO32DNZ,1),	EBD15_MASK, PPCVLE, PPCNONE,	{B15},	NULL},
{"e_bdz",	EBD15(30,8,BO32DZ,0),	EBD15_MASK, PPCVLE, PPCNONE,	{B15},	NULL},
{"e_bdzl",	EBD15(30,8,BO32DZ,1),	EBD15_MASK, PPCVLE, PPCNONE,	{B15},	NULL},
{"e_bge",	EBD15BI(30,8,BO32F,CBLT,0), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bgel",	EBD15BI(30,8,BO32F,CBLT,1), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bnl",	EBD15BI(30,8,BO32F,CBLT,0), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bnll",	EBD15BI(30,8,BO32F,CBLT,1), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_blt",	EBD15BI(30,8,BO32T,CBLT,0), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bltl",	EBD15BI(30,8,BO32T,CBLT,1), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bgt",	EBD15BI(30,8,BO32T,CBGT,0), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bgtl",	EBD15BI(30,8,BO32T,CBGT,1), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_ble",	EBD15BI(30,8,BO32F,CBGT,0), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_blel",	EBD15BI(30,8,BO32F,CBGT,1), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bng",	EBD15BI(30,8,BO32F,CBGT,0), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bngl",	EBD15BI(30,8,BO32F,CBGT,1), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bne",	EBD15BI(30,8,BO32F,CBEQ,0), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bnel",	EBD15BI(30,8,BO32F,CBEQ,1), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_beq",	EBD15BI(30,8,BO32T,CBEQ,0), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_beql",	EBD15BI(30,8,BO32T,CBEQ,1), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bso",	EBD15BI(30,8,BO32T,CBSO,0), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bsol",	EBD15BI(30,8,BO32T,CBSO,1), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bun",	EBD15BI(30,8,BO32T,CBSO,0), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bunl",	EBD15BI(30,8,BO32T,CBSO,1), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bns",	EBD15BI(30,8,BO32F,CBSO,0), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bnsl",	EBD15BI(30,8,BO32F,CBSO,1), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bnu",	EBD15BI(30,8,BO32F,CBSO,0), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bnul",	EBD15BI(30,8,BO32F,CBSO,1), EBD15BI_MASK, PPCVLE, PPCNONE, {CRS,B15},	NULL},
{"e_bc",	BD15(30,8,0),	BD15_MASK,	PPCVLE,	PPCNONE,	{BO32, BI32, B15},	NULL},
{"e_bcl",	BD15(30,8,1),	BD15_MASK,	PPCVLE,	PPCNONE,	{BO32, BI32, B15},	NULL},

{"e_bf",	EBD15(30,8,BO32F,0), EBD15_MASK, PPCVLE, PPCNONE,	{BI32,B15},	NULL},
{"e_bfl",	EBD15(30,8,BO32F,1), EBD15_MASK, PPCVLE, PPCNONE,	{BI32,B15},	NULL},
{"e_bt",	EBD15(30,8,BO32T,0), EBD15_MASK, PPCVLE, PPCNONE,	{BI32,B15},	NULL},
{"e_btl",	EBD15(30,8,BO32T,1), EBD15_MASK, PPCVLE, PPCNONE,	{BI32,B15},	NULL},

{ "e_sc",       ESC(31,0,36),   ESC_MASK,   PPCVLE,     PPCNONE, {ELEV},        NULL },

{"e_cmph",	X(31,14),	X_MASK,		PPCVLE,	PPCNONE,	{CRD, RA, RB},	NULL},
{"e_cmphl",	X(31,46),	X_MASK,		PPCVLE,	PPCNONE,	{CRD, RA, RB},	NULL},
{"e_crandc",	XL(31,129),	XL_MASK,	PPCVLE,	PPCNONE,	{BT, BA, BB},	NULL},
{"e_crnand",	XL(31,225),	XL_MASK,	PPCVLE,	PPCNONE,	{BT, BA, BB},	NULL},
{"e_crnot",	XL(31,33),	XL_MASK,	PPCVLE,	PPCNONE,	{BT, BA, BBA},	NULL},
{"e_crnor",	XL(31,33),	XL_MASK,	PPCVLE,	PPCNONE,	{BT, BA, BB},	NULL},
{"e_crclr",	XL(31,193),	XL_MASK,	PPCVLE,	PPCNONE,	{BT, BAT, BBA},	NULL},
{"e_crxor",	XL(31,193),	XL_MASK,	PPCVLE,	PPCNONE,	{BT, BA, BB},	NULL},
{"e_mcrf",	XL(31,16),	XL_MASK,	PPCVLE,	PPCNONE,	{CRD, CR},	NULL},
{"e_slwi",	EX(31,112),	EX_MASK,	PPCVLE,	PPCNONE,	{RA, RS, SH},	NULL},
{"e_slwi.",	EX(31,113),	EX_MASK,	PPCVLE,	PPCNONE,	{RA, RS, SH},	NULL},

{"e_crand",	XL(31,257),	XL_MASK,	PPCVLE,	PPCNONE,	{BT, BA, BB},	NULL},

{"e_rlw",	EX(31,560),	EX_MASK,	PPCVLE,	PPCNONE,	{RA, RS, RB},	NULL},
{"e_rlw.",	EX(31,561),	EX_MASK,	PPCVLE,	PPCNONE,	{RA, RS, RB},	NULL},

{"e_crset",	XL(31,289),	XL_MASK,	PPCVLE,	PPCNONE,	{BT, BAT, BBA},	NULL},
{"e_creqv",	XL(31,289),	XL_MASK,	PPCVLE,	PPCNONE,	{BT, BA, BB},	NULL},

{"e_rlwi",	EX(31,624),	EX_MASK,	PPCVLE,	PPCNONE,	{RA, RS, SH},	NULL},
{"e_rlwi.",	EX(31,625),	EX_MASK,	PPCVLE,	PPCNONE,	{RA, RS, SH},	NULL},

{"e_crorc",	XL(31,417),	XL_MASK,	PPCVLE,	PPCNONE,	{BT, BA, BB},	NULL},

{"e_crmove",	XL(31,449),	XL_MASK,	PPCVLE,	PPCNONE,	{BT, BA, BBA},	NULL},
{"e_cror",	XL(31,449),	XL_MASK,	PPCVLE,	PPCNONE,	{BT, BA, BB},	NULL},

{"mtmas1",	XSPR(31,467,625), XSPR_MASK,	PPCVLE,	PPCNONE,	{RS},	NULL},

{"e_srwi",	EX(31,1136),	EX_MASK,	PPCVLE,	PPCNONE,	{RA, RS, SH},	NULL},
{"e_srwi.",	EX(31,1137),	EX_MASK,	PPCVLE,	PPCNONE,	{RA, RS, SH},	NULL},

{"se_lbz",	SD4(8),		SD4_MASK,	PPCVLE,	PPCNONE,	{RZ, SE_SD, RX},	NULL},

{"se_stb",	SD4(9),		SD4_MASK,	PPCVLE,	PPCNONE,	{RZ, SE_SD, RX},	NULL},

{"se_lhz",	SD4(10),	SD4_MASK,	PPCVLE,	PPCNONE,	{RZ, SE_SDH, RX},	NULL},

{"se_sth",	SD4(11),	SD4_MASK,	PPCVLE,	PPCNONE,	{RZ, SE_SDH, RX},	NULL},

{"se_lwz",	SD4(12),	SD4_MASK,	PPCVLE,	PPCNONE,	{RZ, SE_SDW, RX},	NULL},

{"se_stw",	SD4(13),	SD4_MASK,	PPCVLE,	PPCNONE,	{RZ, SE_SDW, RX},	NULL},

{"se_bge",	EBD8IO(28,0,0),	EBD8IO3_MASK,	PPCVLE,	PPCNONE,	{B8},	NULL},
{"se_bnl",	EBD8IO(28,0,0),	EBD8IO3_MASK,	PPCVLE,	PPCNONE,	{B8},	NULL},
{"se_ble",	EBD8IO(28,0,1),	EBD8IO3_MASK,	PPCVLE,	PPCNONE,	{B8},	NULL},
{"se_bng",	EBD8IO(28,0,1),	EBD8IO3_MASK,	PPCVLE,	PPCNONE,	{B8},	NULL},
{"se_bne",	EBD8IO(28,0,2),	EBD8IO3_MASK,	PPCVLE,	PPCNONE,	{B8},	NULL},
{"se_bns",	EBD8IO(28,0,3),	EBD8IO3_MASK,	PPCVLE,	PPCNONE,	{B8},	NULL},
{"se_bnu",	EBD8IO(28,0,3),	EBD8IO3_MASK,	PPCVLE,	PPCNONE,	{B8},	NULL},
{"se_bf",	EBD8IO(28,0,0),	EBD8IO2_MASK,	PPCVLE,	PPCNONE,	{BI16, B8},	NULL},
{"se_blt",	EBD8IO(28,1,0),	EBD8IO3_MASK,	PPCVLE,	PPCNONE,	{B8},	NULL},
{"se_bgt",	EBD8IO(28,1,1),	EBD8IO3_MASK,	PPCVLE,	PPCNONE,	{B8},	NULL},
{"se_beq",	EBD8IO(28,1,2),	EBD8IO3_MASK,	PPCVLE,	PPCNONE,	{B8},	NULL},
{"se_bso",	EBD8IO(28,1,3),	EBD8IO3_MASK,	PPCVLE,	PPCNONE,	{B8},	NULL},
{"se_bun",	EBD8IO(28,1,3),	EBD8IO3_MASK,	PPCVLE,	PPCNONE,	{B8},	NULL},
{"se_bt",	EBD8IO(28,1,0),	EBD8IO2_MASK,	PPCVLE,	PPCNONE,	{BI16, B8},	NULL},
{"se_bc",	BD8IO(28),	BD8IO_MASK,	PPCVLE,	PPCNONE,	{BO16, BI16, B8},	NULL},
{"se_b",	BD8(58,0,0),	BD8_MASK,	PPCVLE,	PPCNONE,	{B8},	NULL},
{"se_bl",	BD8(58,0,1),	BD8_MASK,	PPCVLE,	PPCNONE,	{B8},	NULL},

};

const int vle_num_opcodes =
  sizeof (vle_opcodes) / sizeof (vle_opcodes[0]);

/* The macro table.  This is only used by the assembler.  */

/* The expressions of the form (-x ! 31) & (x | 31) have the value 0
   when x=0; 32-x when x is between 1 and 31; are negative if x is
   negative; and are 32 or more otherwise.  This is what you want
   when, for instance, you are emulating a right shift by a
   rotate-left-and-mask, because the underlying instructions support
   shifts of size 0 but not shifts of size 32.  By comparison, when
   extracting x bits from some word you want to use just 32-x, because
   the underlying instructions don't support extracting 0 bits but do
   support extracting the whole word (32 bits in this case).  */

const struct powerpc_macro powerpc_macros[] = {
{"extldi",   4,	PPC64,	"rldicr %0,%1,%3,(%2)-1"},
{"extldi.",  4,	PPC64,	"rldicr. %0,%1,%3,(%2)-1"},
{"extrdi",   4,	PPC64,	"rldicl %0,%1,((%2)+(%3))&((%2)+(%3)<>64),64-(%2)"},
{"extrdi.",  4,	PPC64,	"rldicl. %0,%1,((%2)+(%3))&((%2)+(%3)<>64),64-(%2)"},
{"insrdi",   4,	PPC64,	"rldimi %0,%1,64-((%2)+(%3)),%3"},
{"insrdi.",  4,	PPC64,	"rldimi. %0,%1,64-((%2)+(%3)),%3"},
{"rotrdi",   3,	PPC64,	"rldicl %0,%1,(-(%2)!63)&((%2)|63),0"},
{"rotrdi.",  3,	PPC64,	"rldicl. %0,%1,(-(%2)!63)&((%2)|63),0"},
{"sldi",     3,	PPC64,	"rldicr %0,%1,%2,63-(%2)"},
{"sldi.",    3,	PPC64,	"rldicr. %0,%1,%2,63-(%2)"},
{"srdi",     3,	PPC64,	"rldicl %0,%1,(-(%2)!63)&((%2)|63),%2"},
{"srdi.",    3,	PPC64,	"rldicl. %0,%1,(-(%2)!63)&((%2)|63),%2"},
{"clrrdi",   3,	PPC64,	"rldicr %0,%1,0,63-(%2)"},
{"clrrdi.",  3,	PPC64,	"rldicr. %0,%1,0,63-(%2)"},
{"clrlsldi", 4,	PPC64,	"rldic %0,%1,%3,(%2)-(%3)"},
{"clrlsldi.",4, PPC64,	"rldic. %0,%1,%3,(%2)-(%3)"},

{"extlwi",   4,	PPCCOM,	"rlwinm %0,%1,%3,0,(%2)-1"},
{"extlwi.",  4,	PPCCOM,	"rlwinm. %0,%1,%3,0,(%2)-1"},
{"extrwi",   4,	PPCCOM,	"rlwinm %0,%1,((%2)+(%3))&((%2)+(%3)<>32),32-(%2),31"},
{"extrwi.",  4,	PPCCOM,	"rlwinm. %0,%1,((%2)+(%3))&((%2)+(%3)<>32),32-(%2),31"},
{"inslwi",   4,	PPCCOM,	"rlwimi %0,%1,(-(%3)!31)&((%3)|31),%3,(%2)+(%3)-1"},
{"inslwi.",  4,	PPCCOM,	"rlwimi. %0,%1,(-(%3)!31)&((%3)|31),%3,(%2)+(%3)-1"},
{"insrwi",   4,	PPCCOM,	"rlwimi %0,%1,32-((%2)+(%3)),%3,(%2)+(%3)-1"},
{"insrwi.",  4,	PPCCOM,	"rlwimi. %0,%1,32-((%2)+(%3)),%3,(%2)+(%3)-1"},
{"rotrwi",   3,	PPCCOM,	"rlwinm %0,%1,(-(%2)!31)&((%2)|31),0,31"},
{"rotrwi.",  3,	PPCCOM,	"rlwinm. %0,%1,(-(%2)!31)&((%2)|31),0,31"},
{"slwi",     3,	PPCCOM,	"rlwinm %0,%1,%2,0,31-(%2)"},
{"sli",      3,	PWRCOM,	"rlinm %0,%1,%2,0,31-(%2)"},
{"slwi.",    3,	PPCCOM,	"rlwinm. %0,%1,%2,0,31-(%2)"},
{"sli.",     3,	PWRCOM,	"rlinm. %0,%1,%2,0,31-(%2)"},
{"srwi",     3,	PPCCOM,	"rlwinm %0,%1,(-(%2)!31)&((%2)|31),%2,31"},
{"sri",      3,	PWRCOM,	"rlinm %0,%1,(-(%2)!31)&((%2)|31),%2,31"},
{"srwi.",    3,	PPCCOM,	"rlwinm. %0,%1,(-(%2)!31)&((%2)|31),%2,31"},
{"sri.",     3,	PWRCOM,	"rlinm. %0,%1,(-(%2)!31)&((%2)|31),%2,31"},
{"clrrwi",   3,	PPCCOM,	"rlwinm %0,%1,0,0,31-(%2)"},
{"clrrwi.",  3,	PPCCOM,	"rlwinm. %0,%1,0,0,31-(%2)"},
{"clrlslwi", 4,	PPCCOM,	"rlwinm %0,%1,%3,(%2)-(%3),31-(%3)"},
{"clrlslwi.",4, PPCCOM,	"rlwinm. %0,%1,%3,(%2)-(%3),31-(%3)"},

{"e_extlwi", 4,	PPCVLE, "e_rlwinm %0,%1,%3,0,(%2)-1"},
{"e_extrwi", 4,	PPCVLE, "e_rlwinm %0,%1,((%2)+(%3))&((%2)+(%3)<>32),32-(%2),31"},
{"e_inslwi", 4,	PPCVLE, "e_rlwimi %0,%1,(-(%3)!31)&((%3)|31),%3,(%2)+(%3)-1"},
{"e_insrwi", 4,	PPCVLE, "e_rlwimi %0,%1,32-((%2)+(%3)),%3,(%2)+(%3)-1"},
{"e_rotlwi", 3,	PPCVLE, "e_rlwinm %0,%1,%2,0,31"},
{"e_rotrwi", 3,	PPCVLE, "e_rlwinm %0,%1,(-(%2)!31)&((%2)|31),0,31"},
{"e_slwi",   3,	PPCVLE, "e_rlwinm %0,%1,%2,0,31-(%2)"},
{"e_srwi",   3,	PPCVLE, "e_rlwinm %0,%1,(-(%2)!31)&((%2)|31),%2,31"},
{"e_clrlwi", 3,	PPCVLE, "e_rlwinm %0,%1,0,%2,31"},
{"e_clrrwi", 3,	PPCVLE, "e_rlwinm %0,%1,0,0,31-(%2)"},
{"e_clrlslwi",4, PPCVLE, "e_rlwinm %0,%1,%3,(%2)-(%3),31-(%3)"},
{"nop",      0, PPCVLE, "se_nop"},

{"e_lmvgprw",	1, PPCVLE, "e_ldmvgprw %0"},
{"e_lmvsprw",	1, PPCVLE, "e_ldmvsprw %0"},
{"e_lmvsrrw",	1, PPCVLE, "e_ldmvsrrw %0"},
{"e_lmvcsrrw",	1, PPCVLE, "e_ldmvcsrrw %0"},
{"e_lmvdsrrw",	1, PPCVLE, "e_ldmvdsrrw %0"},

/* old SPE instructions have new names with the same opcodes */
{"evsadd",      3, PPCSPE|PPCVLE, "efsadd %0,%1,%2"},
{"evssub",      3, PPCSPE|PPCVLE, "efssub %0,%1,%2"},
{"evsabs",      2, PPCSPE|PPCVLE, "efsabs %0,%1"},
{"evsnabs",     2, PPCSPE|PPCVLE, "efsnabs %0,%1"},
{"evsneg",      2, PPCSPE|PPCVLE, "efsneg %0,%1"},
{"evsmul",	3, PPCSPE|PPCVLE, "efsmul %0,%1,%2"},
{"evsdiv",	3, PPCSPE|PPCVLE, "efsdiv %0,%1,%2"},
{"evscmpgt",	3, PPCSPE|PPCVLE, "efscmpgt %0,%1,%2"},
{"evsgmplt",	3, PPCSPE|PPCVLE, "efscmplt %0,%1,%2"},
{"evsgmpeq",    3, PPCSPE|PPCVLE, "efscmpeq %0,%1,%2"},
{"evscfui",     2, PPCSPE|PPCVLE, "efscfui %0,%1"},
{"evscfsi",     2, PPCSPE|PPCVLE, "efscfsi %0,%1"},
{"evscfuf",     2, PPCSPE|PPCVLE, "efscfuf %0,%1"},
{"evscfsf",     2, PPCSPE|PPCVLE, "efscfsf %0,%1"},
{"evsctui",     2, PPCSPE|PPCVLE, "efsctui %0,%1"},
{"evsctsi",     2, PPCSPE|PPCVLE, "efsctsi %0,%1"},
{"evsctuf",     2, PPCSPE|PPCVLE, "efsctuf %0,%1"},
{"evsctsf",     2, PPCSPE|PPCVLE, "efsctsf %0,%1"},
{"evsctuiz",    2, PPCSPE|PPCVLE, "efsctuiz %0,%1"},
{"evsctsiz",    2, PPCSPE|PPCVLE, "efsctsiz %0,%1"},
{"evststgt",    3, PPCSPE|PPCVLE, "efststgt %0,%1,%2"},
{"evststlt",    3, PPCSPE|PPCVLE, "efststlt %0,%1,%2"},
{"evststeq",    3, PPCSPE|PPCVLE, "efststeq %0,%1,%2"},

/* SPE2 instructions which just are mapped to SPE2 */
{"evdotphsssi",  3, PPCSPE2, "evdotphssmi %0,%1,%2"},
{"evdotphsssia", 3, PPCSPE2, "evdotphssmia %0,%1,%2"},
{"evdotpwsssi",  3, PPCSPE2, "evdotpwssmi %0,%1,%2"},
{"evdotpwsssia", 3, PPCSPE2, "evdotpwssmia %0,%1,%2"}

};

const int powerpc_num_macros =
  sizeof (powerpc_macros) / sizeof (powerpc_macros[0]);
  

/* SPE v2 instruction set from SPE2PIM Rev. 2 08/2011 */
const struct powerpc_opcode spe2_opcodes[] = {
{"evdotpwcssi",           VX (4, 128),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwcsmi",           VX (4, 129),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwcssfr",          VX (4, 130),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwcssf",           VX (4, 131),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwgasmf",          VX (4, 136),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwxgasmf",         VX (4, 137),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwgasmfr",         VX (4, 138),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwxgasmfr",        VX (4, 139),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwgssmf",          VX (4, 140),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwxgssmf",         VX (4, 141),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwgssmfr",         VX (4, 142),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwxgssmfr",        VX (4, 143),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwcssiaaw3",       VX (4, 144),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwcsmiaaw3",       VX (4, 145),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwcssfraaw3",      VX (4, 146),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwcssfaaw3",       VX (4, 147),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwgasmfaa3",       VX (4, 152),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwxgasmfaa3",      VX (4, 153),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwgasmfraa3",      VX (4, 154),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwxgasmfraa3",     VX (4, 155),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwgssmfaa3",       VX (4, 156),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwxgssmfaa3",      VX (4, 157),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwgssmfraa3",      VX (4, 158),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwxgssmfraa3",     VX (4, 159),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwcssia",          VX (4, 160),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwcsmia",          VX (4, 161),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwcssfra",         VX (4, 162),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwcssfa",          VX (4, 163),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwgasmfa",         VX (4, 168),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwxgasmfa",        VX (4, 169),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwgasmfra",        VX (4, 170),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwxgasmfra",       VX (4, 171),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwgssmfa",         VX (4, 172),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwxgssmfa",        VX (4, 173),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwgssmfra",        VX (4, 174),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwxgssmfra",       VX (4, 175),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwcssiaaw",        VX (4, 176),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwcsmiaaw",        VX (4, 177),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwcssfraaw",       VX (4, 178),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwcssfaaw",        VX (4, 179),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwgasmfaa",        VX (4, 184),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwxgasmfaa",       VX (4, 185),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwgasmfraa",       VX (4, 186),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwxgasmfraa",      VX (4, 187),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwgssmfaa",        VX (4, 188),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwxgssmfaa",       VX (4, 189),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwgssmfraa",       VX (4, 190),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwxgssmfraa",      VX (4, 191),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphihcssi",         VX (4, 256),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotplohcssi",         VX (4, 257),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphihcssf",         VX (4, 258),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotplohcssf",         VX (4, 259),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphihcsmi",         VX (4, 264),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotplohcsmi",         VX (4, 265),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphihcssfr",        VX (4, 266),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotplohcssfr",        VX (4, 267),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphihcssiaaw3",     VX (4, 272),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotplohcssiaaw3",     VX (4, 273),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphihcssfaaw3",     VX (4, 274),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotplohcssfaaw3",     VX (4, 275),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphihcsmiaaw3",     VX (4, 280),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotplohcsmiaaw3",     VX (4, 281),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphihcssfraaw3",    VX (4, 282),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotplohcssfraaw3",    VX (4, 283),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphihcssia",        VX (4, 288),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotplohcssia",        VX (4, 289),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphihcssfa",        VX (4, 290),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotplohcssfa",        VX (4, 291),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphihcsmia",        VX (4, 296),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotplohcsmia",        VX (4, 297),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphihcssfra",       VX (4, 298),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotplohcssfra",       VX (4, 299),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphihcssiaaw",      VX (4, 304),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotplohcssiaaw",      VX (4, 305),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphihcssfaaw",      VX (4, 306),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotplohcssfaaw",      VX (4, 307),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphihcsmiaaw",      VX (4, 312),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotplohcsmiaaw",      VX (4, 313),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphihcssfraaw",     VX (4, 314),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotplohcssfraaw",     VX (4, 315),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphausi",           VX (4, 320),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphassi",           VX (4, 321),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphasusi",          VX (4, 322),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphassf",           VX (4, 323),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphsssf",           VX (4, 327),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphaumi",           VX (4, 328),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphasmi",           VX (4, 329),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphasumi",          VX (4, 330),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphassfr",          VX (4, 331),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphssmi",           VX (4, 333),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphsssfr",          VX (4, 335),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphausiaaw3",       VX (4, 336),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphassiaaw3",       VX (4, 337),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphasusiaaw3",      VX (4, 338),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphassfaaw3",       VX (4, 339),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphsssiaaw3",       VX (4, 341),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphsssfaaw3",       VX (4, 343),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphaumiaaw3",       VX (4, 344),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphasmiaaw3",       VX (4, 345),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphasumiaaw3",      VX (4, 346),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphassfraaw3",      VX (4, 347),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphssmiaaw3",       VX (4, 349),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphsssfraaw3",      VX (4, 351),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphausia",          VX (4, 352),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphassia",          VX (4, 353),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphasusia",         VX (4, 354),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphassfa",          VX (4, 355),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphsssfa",          VX (4, 359),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphaumia",          VX (4, 360),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphasmia",          VX (4, 361),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphasumia",         VX (4, 362),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphassfra",         VX (4, 363),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphssmia",          VX (4, 365),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphsssfra",         VX (4, 367),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphausiaaw",        VX (4, 368),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphassiaaw",        VX (4, 369),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphasusiaaw",       VX (4, 370),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphassfaaw",        VX (4, 371),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphsssiaaw",        VX (4, 373),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphsssfaaw",        VX (4, 375),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphaumiaaw",        VX (4, 376),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphasmiaaw",        VX (4, 377),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphasumiaaw",       VX (4, 378),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphassfraaw",       VX (4, 379),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphssmiaaw",        VX (4, 381),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotphsssfraaw",       VX (4, 383),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgaumi",         VX (4, 384),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgasmi",         VX (4, 385),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgasumi",        VX (4, 386),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgasmf",         VX (4, 387),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgssmi",         VX (4, 388),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgssmf",         VX (4, 389),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hxgasmi",        VX (4, 390),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hxgasmf",        VX (4, 391),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpbaumi",           VX (4, 392),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpbasmi",           VX (4, 393),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpbasumi",          VX (4, 394),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hxgssmi",        VX (4, 398),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hxgssmf",        VX (4, 399),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgaumiaa3",      VX (4, 400),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgasmiaa3",      VX (4, 401),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgasumiaa3",     VX (4, 402),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgasmfaa3",      VX (4, 403),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgssmiaa3",      VX (4, 404),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgssmfaa3",      VX (4, 405),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hxgasmiaa3",     VX (4, 406),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hxgasmfaa3",     VX (4, 407),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpbaumiaaw3",       VX (4, 408),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpbasmiaaw3",       VX (4, 409),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpbasumiaaw3",      VX (4, 410),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hxgssmiaa3",     VX (4, 414),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hxgssmfaa3",     VX (4, 415),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgaumia",        VX (4, 416),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgasmia",        VX (4, 417),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgasumia",       VX (4, 418),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgasmfa",        VX (4, 419),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgssmia",        VX (4, 420),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgssmfa",        VX (4, 421),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hxgasmia",       VX (4, 422),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hxgasmfa",       VX (4, 423),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpbaumia",          VX (4, 424),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpbasmia",          VX (4, 425),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpbasumia",         VX (4, 426),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hxgssmia",       VX (4, 430),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hxgssmfa",       VX (4, 431),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgaumiaa",       VX (4, 432),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgasmiaa",       VX (4, 433),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgasumiaa",      VX (4, 434),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgasmfaa",       VX (4, 435),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgssmiaa",       VX (4, 436),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hgssmfaa",       VX (4, 437),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hxgasmiaa",      VX (4, 438),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hxgasmfaa",      VX (4, 439),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpbaumiaaw",        VX (4, 440),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpbasmiaaw",        VX (4, 441),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpbasumiaaw",       VX (4, 442),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hxgssmiaa",      VX (4, 446),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotp4hxgssmfaa",      VX (4, 447),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwausi",           VX (4, 448),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwassi",           VX (4, 449),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwasusi",          VX (4, 450),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwaumi",           VX (4, 456),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwasmi",           VX (4, 457),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwasumi",          VX (4, 458),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwssmi",           VX (4, 461),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwausiaa3",        VX (4, 464),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwassiaa3",        VX (4, 465),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwasusiaa3",       VX (4, 466),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwsssiaa3",        VX (4, 469),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwaumiaa3",        VX (4, 472),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwasmiaa3",        VX (4, 473),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwasumiaa3",       VX (4, 474),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwssmiaa3",        VX (4, 477),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwausia",          VX (4, 480),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwassia",          VX (4, 481),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwasusia",         VX (4, 482),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwaumia",          VX (4, 488),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwasmia",          VX (4, 489),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwasumia",         VX (4, 490),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwssmia",          VX (4, 493),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwausiaa",         VX (4, 496),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwassiaa",         VX (4, 497),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwasusiaa",        VX (4, 498),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwsssiaa",         VX (4, 501),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwaumiaa",         VX (4, 504),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwasmiaa",         VX (4, 505),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwasumiaa",        VX (4, 506),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdotpwssmiaa",         VX (4, 509),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddib",               VX (4, 515),   VX_MASK, PPCSPE2, PPCNONE, {RD, UIMM, RB},     NULL},
{"evaddih",               VX (4, 513),   VX_MASK, PPCSPE2, PPCNONE, {RD, UIMM, RB},     NULL},
{"evsubifh",              VX (4, 517),   VX_MASK, PPCSPE2, PPCNONE, {RD, UIMM, RB},     NULL},
{"evsubifb",              VX (4, 519),   VX_MASK, PPCSPE2, PPCNONE, {RD, UIMM, RB},     NULL},
{"evabsb",                VX_RB_CONST(4, 520, 2),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evabsh",                VX_RB_CONST(4, 520, 4),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evabsd",                VX_RB_CONST(4, 520, 6),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evabss",                VX_RB_CONST(4, 520, 8),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evabsbs",               VX_RB_CONST(4, 520, 10), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evabshs",               VX_RB_CONST(4, 520, 12), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evabsds",               VX_RB_CONST(4, 520, 14), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evnegwo",               VX_RB_CONST(4, 521, 1),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evnegb",                VX_RB_CONST(4, 521, 2),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evnegbo",               VX_RB_CONST(4, 521, 3),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evnegh",                VX_RB_CONST(4, 521, 4),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evnegho",               VX_RB_CONST(4, 521, 5),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evnegd",                VX_RB_CONST(4, 521, 6),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evnegs",                VX_RB_CONST(4, 521, 8),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evnegwos",              VX_RB_CONST(4, 521, 9),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evnegbs",               VX_RB_CONST(4, 521, 10), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evnegbos",              VX_RB_CONST(4, 521, 11), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evneghs",               VX_RB_CONST(4, 521, 12), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evneghos",              VX_RB_CONST(4, 521, 13), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evnegds",               VX_RB_CONST(4, 521, 14), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evextzb",               VX_RB_CONST(4, 522, 1),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evextsbh",              VX_RB_CONST(4, 522, 4),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evextsw",               VX_RB_CONST(4, 523, 6),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrndwh",               VX_RB_CONST(4, 524, 0),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrndhb",               VX_RB_CONST(4, 524, 4),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrnddw",               VX_RB_CONST(4, 524, 6),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrndwhus",             VX_RB_CONST(4, 524, 8),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrndwhss",             VX_RB_CONST(4, 524, 9),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrndhbus",             VX_RB_CONST(4, 524, 12), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrndhbss",             VX_RB_CONST(4, 524, 13), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrnddwus",             VX_RB_CONST(4, 524, 14), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrnddwss",             VX_RB_CONST(4, 524, 15), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrndwnh",              VX_RB_CONST(4, 524, 16), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrndhnb",              VX_RB_CONST(4, 524, 20), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrnddnw",              VX_RB_CONST(4, 524, 22), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrndwnhus",            VX_RB_CONST(4, 524, 24), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrndwnhss",            VX_RB_CONST(4, 524, 25), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrndhnbus",            VX_RB_CONST(4, 524, 28), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrndhnbss",            VX_RB_CONST(4, 524, 29), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrnddnwus",            VX_RB_CONST(4, 524, 30), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evrnddnwss",            VX_RB_CONST(4, 524, 31), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evcntlzh",              VX_RB_CONST(4, 525, 4),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evcntlsh",              VX_RB_CONST(4, 526, 4),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evpopcntb",             VX_RB_CONST(4, 526, 26), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"circinc",               VX (4, 528),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evunpkhibui",           VX_RB_CONST(4, 540, 0),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evunpkhibsi",           VX_RB_CONST(4, 540, 1),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evunpkhihui",           VX_RB_CONST(4, 540, 2),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evunpkhihsi",           VX_RB_CONST(4, 540, 3),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evunpklobui",           VX_RB_CONST(4, 540, 4),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evunpklobsi",           VX_RB_CONST(4, 540, 5),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evunpklohui",           VX_RB_CONST(4, 540, 6),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evunpklohsi",           VX_RB_CONST(4, 540, 7),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evunpklohf",            VX_RB_CONST(4, 540, 8),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evunpkhihf",            VX_RB_CONST(4, 540, 9),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evunpklowgsf",          VX_RB_CONST(4, 540, 12), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evunpkhiwgsf",          VX_RB_CONST(4, 540, 13), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsatsduw",             VX_RB_CONST(4, 540, 16), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsatsdsw",             VX_RB_CONST(4, 540, 17), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsatshub",             VX_RB_CONST(4, 540, 18), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsatshsb",             VX_RB_CONST(4, 540, 19), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsatuwuh",             VX_RB_CONST(4, 540, 20), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsatswsh",             VX_RB_CONST(4, 540, 21), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsatswuh",             VX_RB_CONST(4, 540, 22), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsatuhub",             VX_RB_CONST(4, 540, 23), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsatuduw",             VX_RB_CONST(4, 540, 24), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsatuwsw",             VX_RB_CONST(4, 540, 25), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsatshuh",             VX_RB_CONST(4, 540, 26), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsatuhsh",             VX_RB_CONST(4, 540, 27), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsatswuw",             VX_RB_CONST(4, 540, 28), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsatswgsdf",           VX_RB_CONST(4, 540, 29), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsatsbub",             VX_RB_CONST(4, 540, 30), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsatubsb",             VX_RB_CONST(4, 540, 31), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evmaxhpuw",             VX_RB_CONST(4, 541, 0),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evmaxhpsw",             VX_RB_CONST(4, 541, 1),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evmaxbpuh",             VX_RB_CONST(4, 541, 4),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evmaxbpsh",             VX_RB_CONST(4, 541, 5),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evmaxwpud",             VX_RB_CONST(4, 541, 6),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evmaxwpsd",             VX_RB_CONST(4, 541, 7),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evminhpuw",             VX_RB_CONST(4, 541, 8),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evminhpsw",             VX_RB_CONST(4, 541, 9),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evminbpuh",             VX_RB_CONST(4, 541, 12), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evminbpsh",             VX_RB_CONST(4, 541, 13), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evminwpud",             VX_RB_CONST(4, 541, 14), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evminwpsd",             VX_RB_CONST(4, 541, 15), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evmaxmagws",            VX (4, 543),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsl",                  VX (4, 549),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsli",                 VX (4, 551),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evsplatie",             VX_RB_CONST (4, 553, 1),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatib",             VX_RB_CONST (4, 553, 2),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatibe",            VX_RB_CONST (4, 553, 3),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatih",             VX_RB_CONST (4, 553, 4),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatihe",            VX_RB_CONST (4, 553, 5),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatid",             VX_RB_CONST (4, 553, 6),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatia",             VX_RB_CONST (4, 553, 16), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatiea",            VX_RB_CONST (4, 553, 17), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatiba",            VX_RB_CONST (4, 553, 18), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatibea",           VX_RB_CONST (4, 553, 19), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatiha",            VX_RB_CONST (4, 553, 20), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatihea",           VX_RB_CONST (4, 553, 21), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatida",            VX_RB_CONST (4, 553, 22), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatfio",            VX_RB_CONST (4, 555, 1),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatfib",            VX_RB_CONST (4, 555, 2),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatfibo",           VX_RB_CONST (4, 555, 3),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatfih",            VX_RB_CONST (4, 555, 4),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatfiho",           VX_RB_CONST (4, 555, 5),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatfid",            VX_RB_CONST (4, 555, 6),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatfia",            VX_RB_CONST (4, 555, 16), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatfioa",           VX_RB_CONST (4, 555, 17), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatfiba",           VX_RB_CONST (4, 555, 18), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatfiboa",          VX_RB_CONST (4, 555, 19), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatfiha",           VX_RB_CONST (4, 555, 20), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatfihoa",          VX_RB_CONST (4, 555, 21), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evsplatfida",           VX_RB_CONST (4, 555, 22), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, SIMM}, NULL},
{"evcmpgtdu",             VX_SPE_CRFD (4, 560, 1), VX_SPE_CRFD_MASK, PPCSPE2, PPCNONE, {CRFD, RA, RB}, NULL},
{"evcmpgtds",             VX_SPE_CRFD (4, 561, 1), VX_SPE_CRFD_MASK, PPCSPE2, PPCNONE, {CRFD, RA, RB}, NULL},
{"evcmpltdu",             VX_SPE_CRFD (4, 562, 1), VX_SPE_CRFD_MASK, PPCSPE2, PPCNONE, {CRFD, RA, RB}, NULL},
{"evcmpltds",             VX_SPE_CRFD (4, 563, 1), VX_SPE_CRFD_MASK, PPCSPE2, PPCNONE, {CRFD, RA, RB}, NULL},
{"evcmpeqd",              VX_SPE_CRFD (4, 564, 1), VX_SPE_CRFD_MASK, PPCSPE2, PPCNONE, {CRFD, RA, RB}, NULL},
{"evswapbhilo",           VX (4, 568),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evswapblohi",           VX (4, 569),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evswaphhilo",           VX (4, 570),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evswaphlohi",           VX (4, 571),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evswaphe",              VX (4, 572),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evswaphhi",             VX (4, 573),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evswaphlo",             VX (4, 574),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evswapho",              VX (4, 575),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evinsb",                VX (4, 584), VX_MASK, PPCSPE2, PPCNONE, {RD, RA, DDD, BBB}, NULL},
{"evxtrb",                VX (4, 586), VX_MASK, PPCSPE2, PPCNONE, {RD, RA, DDD, BBB}, NULL},
{"evsplath",              VX_SPE2_HH (4, 588, 0, 0), VX_SPE2_HH_MASK, PPCSPE2, PPCNONE, {RD, RA, HH},   NULL},
{"evsplatb",              VX_SPE2_SPLATB (4, 588, 2), VX_SPE2_SPLATB_MASK, PPCSPE2, PPCNONE, {RD, RA, BBB}, NULL},
{"evinsh",                VX_SPE2_DDHH (4, 589, 0), VX_SPE2_DDHH_MASK, PPCSPE2, PPCNONE, {RD, RA, DD, HH},   NULL},
{"evclrbe",               VX_SPE2_CLR (4, 590, 0), VX_SPE2_CLR_MASK, PPCSPE2, PPCNONE, {RD, RA, MMMM}, NULL},
{"evclrbo",               VX_SPE2_CLR (4, 590, 1), VX_SPE2_CLR_MASK, PPCSPE2, PPCNONE, {RD, RA, MMMM}, NULL},
{"evclrh",                VX_SPE2_CLR (4, 591, 1), VX_SPE2_CLR_MASK, PPCSPE2, PPCNONE, {RD, RA, MMMM}, NULL},
{"evxtrh",                VX_SPE2_DDHH (4, 591, 0), VX_SPE2_DDHH_MASK, PPCSPE2, PPCNONE, {RD, RA, DD, HH},   NULL},
{"evselbitm0",            VX (4, 592),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evselbitm1",            VX (4, 593),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evselbit",              VX (4, 594),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evperm",                VX (4, 596),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evperm2",               VX (4, 597),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evperm3",               VX (4, 598),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evxtrd",                VX (4, 600),   VX_OFF_SPE2_MASK, PPCSPE2, PPCNONE, {RD, RA, RB, VX_OFF_SPE2},    NULL},
{"evsrbu",                VX (4, 608),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsrbs",                VX (4, 609),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsrbiu",               VX (4, 610),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evsrbis",               VX (4, 611),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evslb",                 VX (4, 612),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evrlb",                 VX (4, 613),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evslbi",                VX (4, 614),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evrlbi",                VX (4, 615),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evsrhu",                VX (4, 616),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsrhs",                VX (4, 617),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsrhiu",               VX (4, 618),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evsrhis",               VX (4, 619),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evslh",                 VX (4, 620),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evrlh",                 VX (4, 621),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evslhi",                VX (4, 622),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evrlhi",                VX (4, 623),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evsru",                 VX (4, 624),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsrs",                 VX (4, 625),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsriu",                VX (4, 626),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evsris",                VX (4, 627),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlvsl",                VX (4, 628),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlvsr",                VX (4, 629),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsroiu",               VX_SPE2_OCTET (4, 631, 0), VX_SPE2_OCTET_MASK, PPCSPE2, PPCNONE, {RD, RA, NNN}, NULL},
{"evsrois",               VX_SPE2_OCTET (4, 631, 1), VX_SPE2_OCTET_MASK, PPCSPE2, PPCNONE, {RD, RA, NNN}, NULL},
{"evsloi",                VX_SPE2_OCTET (4, 631, 2), VX_SPE2_OCTET_MASK, PPCSPE2, PPCNONE, {RD, RA, NNN}, NULL},
{"evfssqrt",              VX_RB_CONST(4, 647, 0),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA},       NULL},
{"evfscfh",               VX_RA_CONST(4, 657, 4),  VX_RA_CONST_MASK, PPCSPE2, PPCNONE, {RD, RB},       NULL},
{"evfscth",               VX_RA_CONST(4, 661, 4),  VX_RA_CONST_MASK, PPCSPE2, PPCNONE, {RD, RB},       NULL},
{"evfsmax",               VX (4, 672),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evfsmin",               VX (4, 673),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evfsaddsub",            VX (4, 674),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evfssubadd",            VX (4, 675),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evfssum",               VX (4, 676),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evfsdiff",              VX (4, 677),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evfssumdiff",           VX (4, 678),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evfsdiffsum",           VX (4, 679),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evfsaddx",              VX (4, 680),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evfssubx",              VX (4, 681),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evfsaddsubx",           VX (4, 682),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evfssubaddx",           VX (4, 683),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evfsmulx",              VX (4, 684),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evfsmule",              VX (4, 686),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evfsmulo",              VX (4, 687),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evldbx",                VX (4, 774),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evldb",                 VX (4, 775),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlhhsplathx",          VX (4, 778),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlhhsplath",           VX (4, 779),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlwbsplatwx",          VX (4, 786),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlwbsplatw",           VX (4, 787),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlwhsplatwx",          VX (4, 794),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlwhsplatw",           VX (4, 795),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlbbsplatbx",          VX (4, 798),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlbbsplatb",           VX (4, 799),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evstdbx",               VX (4, 806),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evstdb",                VX (4, 807),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evlwbex",               VX (4, 810),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlwbe",                VX (4, 811),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlwboux",              VX (4, 812),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlwbou",               VX (4, 813),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlwbosx",              VX (4, 814),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlwbos",               VX (4, 815),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evstwbex",              VX (4, 818),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evstwbe",               VX (4, 819),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evstwbox",              VX (4, 822),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evstwbo",               VX (4, 823),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evstwbx",               VX (4, 826),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evstwb",                VX (4, 827),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evsthbx",               VX (4, 830),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evsthb",                VX (4, 831),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evlddmx",               VX (4, 832),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlddu",                VX (4, 833),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evldwmx",               VX (4, 834),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evldwu",                VX (4, 835),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evldhmx",               VX (4, 836),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evldhu",                VX (4, 837),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evldbmx",               VX (4, 838),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evldbu",                VX (4, 839),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlhhesplatmx",         VX (4, 840),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlhhesplatu",          VX (4, 841),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlhhsplathmx",         VX (4, 842),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlhhsplathu",          VX (4, 843),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlhhousplatmx",        VX (4, 844),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlhhousplatu",         VX (4, 845),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlhhossplatmx",        VX (4, 846),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlhhossplatu",         VX (4, 847),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlwhemx",              VX (4, 848),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlwheu",               VX (4, 849),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlwbsplatwmx",         VX (4, 850),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlwbsplatwu",          VX (4, 851),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlwhoumx",             VX (4, 852),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlwhouu",              VX (4, 853),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlwhosmx",             VX (4, 854),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlwhosu",              VX (4, 855),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlwwsplatmx",          VX (4, 856),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlwwsplatu",           VX (4, 857),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlwhsplatwmx",         VX (4, 858),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlwhsplatwu",          VX (4, 859),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlwhsplatmx",          VX (4, 860),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlwhsplatu",           VX (4, 861),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlbbsplatbmx",         VX (4, 862),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlbbsplatbu",          VX (4, 863),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evstddmx",              VX (4, 864),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evstddu",               VX (4, 865),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evstdwmx",              VX (4, 866),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evstdwu",               VX (4, 867),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evstdhmx",              VX (4, 868),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evstdhu",               VX (4, 869),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evstdbmx",              VX (4, 870),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evstdbu",               VX (4, 871),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evlwbemx",              VX (4, 874),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlwbeu",               VX (4, 875),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlwboumx",             VX (4, 876),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlwbouu",              VX (4, 877),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evlwbosmx",             VX (4, 878),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evlwbosu",              VX (4, 879),   VX_MASK, PPCSPE2, PPCNONE, {RD, RA, EVUIMM},   NULL},
{"evstwhemx",             VX (4, 880),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evstwheu",              VX (4, 881),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evstwbemx",             VX (4, 882),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evstwbeu",              VX (4, 883),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evstwhomx",             VX (4, 884),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evstwhou",              VX (4, 885),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evstwbomx",             VX (4, 886),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evstwbou",              VX (4, 887),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evstwwemx",             VX (4, 888),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evstwweu",              VX (4, 889),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evstwbmx",              VX (4, 890),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evstwbu",               VX (4, 891),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evstwwomx",             VX (4, 892),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evstwwou",              VX (4, 893),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evsthbmx",              VX (4, 894),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, RB},       NULL},
{"evsthbu",               VX (4, 895),   VX_MASK, PPCSPE2, PPCNONE, {RS, RA, EVUIMM},   NULL},
{"evmhusi",               VX (4, 1024),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhssi",               VX (4, 1025),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhsusi",              VX (4, 1026),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhssf",               VX (4, 1028),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhumi",               VX (4, 1029),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhssfr",              VX (4, 1030),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhesumi",             VX (4, 1034),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhosumi",             VX (4, 1038),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbeumi",              VX (4, 1048),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbesmi",              VX (4, 1049),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbesumi",             VX (4, 1050),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmboumi",              VX (4, 1052),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbosmi",              VX (4, 1053),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbosumi",             VX (4, 1054),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhesumia",            VX (4, 1066),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhosumia",            VX (4, 1070),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbeumia",             VX (4, 1080),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbesmia",             VX (4, 1081),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbesumia",            VX (4, 1082),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmboumia",             VX (4, 1084),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbosmia",             VX (4, 1085),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbosumia",            VX (4, 1086),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwusiw",              VX (4, 1088),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwssiw",              VX (4, 1089),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwhssfr",             VX (4, 1094),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwehgsmfr",           VX (4, 1110),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwehgsmf",            VX (4, 1111),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwohgsmfr",           VX (4, 1118),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwohgsmf",            VX (4, 1119),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwhssfra",            VX (4, 1126),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwehgsmfra",          VX (4, 1142),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwehgsmfa",           VX (4, 1143),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwohgsmfra",          VX (4, 1150),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwohgsmfa",           VX (4, 1151),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddusiaa",            VX_RB_CONST(4, 1152, 0), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA},   NULL},
{"evaddssiaa",            VX_RB_CONST(4, 1153, 0), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA},   NULL},
{"evsubfusiaa",           VX_RB_CONST(4, 1154, 0), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA},   NULL},
{"evsubfssiaa",           VX_RB_CONST(4, 1155, 0), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA},   NULL},
{"evaddsmiaa",            VX_RB_CONST(4, 1156, 0), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA},   NULL},
{"evsubfsmiaa",           VX_RB_CONST(4, 1158, 0), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA},   NULL},
{"evaddh",                VX (4, 1160),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddhss",              VX (4, 1161),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfh",               VX (4, 1162),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfhss",             VX (4, 1163),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddhx",               VX (4, 1164),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddhxss",             VX (4, 1165),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfhx",              VX (4, 1166),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfhxss",            VX (4, 1167),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddd",                VX (4, 1168),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evadddss",              VX (4, 1169),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfd",               VX (4, 1170),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfdss",             VX (4, 1171),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddb",                VX (4, 1172),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddbss",              VX (4, 1173),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfb",               VX (4, 1174),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfbss",             VX (4, 1175),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddsubfh",            VX (4, 1176),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddsubfhss",          VX (4, 1177),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfaddh",            VX (4, 1178),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfaddhss",          VX (4, 1179),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddsubfhx",           VX (4, 1180),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddsubfhxss",         VX (4, 1181),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfaddhx",           VX (4, 1182),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfaddhxss",         VX (4, 1183),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evadddus",              VX (4, 1184),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddbus",              VX (4, 1185),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfdus",             VX (4, 1186),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfbus",             VX (4, 1187),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddwus",              VX (4, 1188),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddwxus",             VX (4, 1189),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfwus",             VX (4, 1190),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfwxus",            VX (4, 1191),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evadd2subf2h",          VX (4, 1192),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evadd2subf2hss",        VX (4, 1193),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubf2add2h",          VX (4, 1194),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubf2add2hss",        VX (4, 1195),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddhus",              VX (4, 1196),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddhxus",             VX (4, 1197),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfhus",             VX (4, 1198),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfhxus",            VX (4, 1199),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddwss",              VX (4, 1201),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfwss",             VX (4, 1203),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddwx",               VX (4, 1204),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddwxss",             VX (4, 1205),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfwx",              VX (4, 1206),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfwxss",            VX (4, 1207),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddsubfw",            VX (4, 1208),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddsubfwss",          VX (4, 1209),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfaddw",            VX (4, 1210),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfaddwss",          VX (4, 1211),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddsubfwx",           VX (4, 1212),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddsubfwxss",         VX (4, 1213),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfaddwx",           VX (4, 1214),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfaddwxss",         VX (4, 1215),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmar",                 VX_SPE2_EVMAR (4, 1220), VX_SPE2_EVMAR_MASK, PPCSPE2, PPCNONE, {RD},   NULL},
{"evsumwu",               VX_RB_CONST(4, 1221, 0),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsumws",               VX_RB_CONST(4, 1221, 1),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsum4bu",              VX_RB_CONST(4, 1221, 2),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsum4bs",              VX_RB_CONST(4, 1221, 3),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsum2hu",              VX_RB_CONST(4, 1221, 4),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsum2hs",              VX_RB_CONST(4, 1221, 5),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evdiff2his",            VX_RB_CONST(4, 1221, 6),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsum2his",             VX_RB_CONST(4, 1221, 7),  VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsumwua",              VX_RB_CONST(4, 1221, 16), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsumwsa",              VX_RB_CONST(4, 1221, 17), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsum4bua",             VX_RB_CONST(4, 1221, 18), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsum4bsa",             VX_RB_CONST(4, 1221, 19), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsum2hua",             VX_RB_CONST(4, 1221, 20), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsum2hsa",             VX_RB_CONST(4, 1221, 21), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evdiff2hisa",           VX_RB_CONST(4, 1221, 22), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsum2hisa",            VX_RB_CONST(4, 1221, 23), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsumwuaa",             VX_RB_CONST(4, 1221, 24), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsumwsaa",             VX_RB_CONST(4, 1221, 25), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsum4buaaw",           VX_RB_CONST(4, 1221, 26), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsum4bsaaw",           VX_RB_CONST(4, 1221, 27), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsum2huaaw",           VX_RB_CONST(4, 1221, 28), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsum2hsaaw",           VX_RB_CONST(4, 1221, 29), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evdiff2hisaaw",         VX_RB_CONST(4, 1221, 30), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evsum2hisaaw",          VX_RB_CONST(4, 1221, 31), VX_RB_CONST_MASK, PPCSPE2, PPCNONE, {RD, RA}, NULL},
{"evdivwsf",              VX (4, 1228),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdivwuf",              VX (4, 1229),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdivs",                VX (4, 1230),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdivu",                VX (4, 1231),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddwegsi",            VX (4, 1232),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddwegsf",            VX (4, 1233),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfwegsi",           VX (4, 1234),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfwegsf",           VX (4, 1235),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddwogsi",            VX (4, 1236),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddwogsf",            VX (4, 1237),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfwogsi",           VX (4, 1238),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfwogsf",           VX (4, 1239),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddhhiuw",            VX (4, 1240),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddhhisw",            VX (4, 1241),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfhhiuw",           VX (4, 1242),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfhhisw",           VX (4, 1243),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddhlouw",            VX (4, 1244),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evaddhlosw",            VX (4, 1245),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfhlouw",           VX (4, 1246),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsubfhlosw",           VX (4, 1247),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhesusiaaw",          VX (4, 1282),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhosusiaaw",          VX (4, 1286),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhesumiaaw",          VX (4, 1290),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhosumiaaw",          VX (4, 1294),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbeusiaah",           VX (4, 1296),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbessiaah",           VX (4, 1297),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbesusiaah",          VX (4, 1298),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbousiaah",           VX (4, 1300),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbossiaah",           VX (4, 1301),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbosusiaah",          VX (4, 1302),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbeumiaah",           VX (4, 1304),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbesmiaah",           VX (4, 1305),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbesumiaah",          VX (4, 1306),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmboumiaah",           VX (4, 1308),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbosmiaah",           VX (4, 1309),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbosumiaah",          VX (4, 1310),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwlusiaaw3",          VX (4, 1346),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwlssiaaw3",          VX (4, 1347),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwhssfraaw3",         VX (4, 1348),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwhssfaaw3",          VX (4, 1349),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwhssfraaw",          VX (4, 1350),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwhssfaaw",           VX (4, 1351),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwlumiaaw3",          VX (4, 1354),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwlsmiaaw3",          VX (4, 1355),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwusiaa",             VX (4, 1360),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwssiaa",             VX (4, 1361),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwehgsmfraa",         VX (4, 1366),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwehgsmfaa",          VX (4, 1367),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwohgsmfraa",         VX (4, 1374),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwohgsmfaa",          VX (4, 1375),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhesusianw",          VX (4, 1410),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhosusianw",          VX (4, 1414),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhesumianw",          VX (4, 1418),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmhosumianw",          VX (4, 1422),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbeusianh",           VX (4, 1424),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbessianh",           VX (4, 1425),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbesusianh",          VX (4, 1426),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbousianh",           VX (4, 1428),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbossianh",           VX (4, 1429),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbosusianh",          VX (4, 1430),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbeumianh",           VX (4, 1432),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbesmianh",           VX (4, 1433),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbesumianh",          VX (4, 1434),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmboumianh",           VX (4, 1436),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbosmianh",           VX (4, 1437),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmbosumianh",          VX (4, 1438),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwlusianw3",          VX (4, 1474),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwlssianw3",          VX (4, 1475),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwhssfranw3",         VX (4, 1476),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwhssfanw3",          VX (4, 1477),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwhssfranw",          VX (4, 1478),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwhssfanw",           VX (4, 1479),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwlumianw3",          VX (4, 1482),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwlsmianw3",          VX (4, 1483),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwusian",             VX (4, 1488),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwssian",             VX (4, 1489),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwehgsmfran",         VX (4, 1494),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwehgsmfan",          VX (4, 1495),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwohgsmfran",         VX (4, 1502),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmwohgsmfan",          VX (4, 1503),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evseteqb",              VX (4, 1536),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evseteqb.",             VX (4, 1537),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evseteqh",              VX (4, 1538),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evseteqh.",             VX (4, 1539),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evseteqw",              VX (4, 1540),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evseteqw.",             VX (4, 1541),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetgthu",             VX (4, 1544),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetgthu.",            VX (4, 1545),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetgths",             VX (4, 1546),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetgths.",            VX (4, 1547),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetgtwu",             VX (4, 1548),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetgtwu.",            VX (4, 1549),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetgtws",             VX (4, 1550),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetgtws.",            VX (4, 1551),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetgtbu",             VX (4, 1552),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetgtbu.",            VX (4, 1553),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetgtbs",             VX (4, 1554),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetgtbs.",            VX (4, 1555),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetltbu",             VX (4, 1556),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetltbu.",            VX (4, 1557),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetltbs",             VX (4, 1558),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetltbs.",            VX (4, 1559),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetlthu",             VX (4, 1560),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetlthu.",            VX (4, 1561),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetlths",             VX (4, 1562),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetlths.",            VX (4, 1563),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetltwu",             VX (4, 1564),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetltwu.",            VX (4, 1565),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetltws",             VX (4, 1566),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsetltws.",            VX (4, 1567),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsaduw",               VX (4, 1568),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsadsw",               VX (4, 1569),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsad4ub",              VX (4, 1570),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsad4sb",              VX (4, 1571),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsad2uh",              VX (4, 1572),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsad2sh",              VX (4, 1573),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsaduwa",              VX (4, 1576),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsadswa",              VX (4, 1577),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsad4uba",             VX (4, 1578),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsad4sba",             VX (4, 1579),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsad2uha",             VX (4, 1580),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsad2sha",             VX (4, 1581),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evabsdifuw",            VX (4, 1584),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evabsdifsw",            VX (4, 1585),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evabsdifub",            VX (4, 1586),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evabsdifsb",            VX (4, 1587),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evabsdifuh",            VX (4, 1588),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evabsdifsh",            VX (4, 1589),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsaduwaa",             VX (4, 1592),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsadswaa",             VX (4, 1593),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsad4ubaaw",           VX (4, 1594),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsad4sbaaw",           VX (4, 1595),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsad2uhaaw",           VX (4, 1596),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evsad2shaaw",           VX (4, 1597),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evpkshubs",             VX (4, 1600),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evpkshsbs",             VX (4, 1601),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evpkswuhs",             VX (4, 1602),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evpkswshs",             VX (4, 1603),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evpkuhubs",             VX (4, 1604),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evpkuwuhs",             VX (4, 1605),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evpkswshilvs",          VX (4, 1606),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evpkswgshefrs",         VX (4, 1607),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evpkswshfrs",           VX (4, 1608),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evpkswshilvfrs",        VX (4, 1609),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evpksdswfrs",           VX (4, 1610),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evpksdshefrs",          VX (4, 1611),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evpkuduws",             VX (4, 1612),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evpksdsws",             VX (4, 1613),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evpkswgswfrs",          VX (4, 1614),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evilveh",               VX (4, 1616),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evilveoh",              VX (4, 1617),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evilvhih",              VX (4, 1618),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evilvhiloh",            VX (4, 1619),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evilvloh",              VX (4, 1620),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evilvlohih",            VX (4, 1621),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evilvoeh",              VX (4, 1622),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evilvoh",               VX (4, 1623),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdlveb",               VX (4, 1624),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdlveh",               VX (4, 1625),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdlveob",              VX (4, 1626),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdlveoh",              VX (4, 1627),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdlvob",               VX (4, 1628),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdlvoh",               VX (4, 1629),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdlvoeb",              VX (4, 1630),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evdlvoeh",              VX (4, 1631),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmaxbu",               VX (4, 1632),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmaxbs",               VX (4, 1633),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmaxhu",               VX (4, 1634),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmaxhs",               VX (4, 1635),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmaxwu",               VX (4, 1636),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmaxws",               VX (4, 1637),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmaxdu",               VX (4, 1638),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmaxds",               VX (4, 1639),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evminbu",               VX (4, 1640),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evminbs",               VX (4, 1641),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evminhu",               VX (4, 1642),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evminhs",               VX (4, 1643),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evminwu",               VX (4, 1644),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evminws",               VX (4, 1645),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evmindu",               VX (4, 1646),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evminds",               VX (4, 1647),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evavgwu",               VX (4, 1648),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evavgws",               VX (4, 1649),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evavgbu",               VX (4, 1650),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evavgbs",               VX (4, 1651),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evavghu",               VX (4, 1652),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evavghs",               VX (4, 1653),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evavgdu",               VX (4, 1654),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evavgds",               VX (4, 1655),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evavgwur",              VX (4, 1656),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evavgwsr",              VX (4, 1657),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evavgbur",              VX (4, 1658),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evavgbsr",              VX (4, 1659),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evavghur",              VX (4, 1660),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evavghsr",              VX (4, 1661),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evavgdur",              VX (4, 1662),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},
{"evavgdsr",              VX (4, 1663),  VX_MASK, PPCSPE2, PPCNONE, {RD, RA, RB},       NULL},

};

const int spe2_num_opcodes =
  sizeof (spe2_opcodes) / sizeof (spe2_opcodes[0]);
