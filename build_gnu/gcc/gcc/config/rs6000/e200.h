/* Enable E200 support.
   Copyright (C) 2003-2014 Free Software Foundation, Inc.
   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3, or (at your
   option) any later version.

   GCC is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING3.  If not see
   <http://www.gnu.org/licenses/>.  */

#undef TARGET_SPE_ABI
#undef TARGET_SPE
#undef TARGET_FPRS
#undef TARGET_E500_SINGLE
#undef TARGET_E500_DOUBLE
#undef CHECK_E500_OPTIONS

#define TARGET_SPE_ABI rs6000_spe_abi
#define TARGET_SPE rs6000_spe
#define TARGET_FPRS (rs6000_float_gprs == 0)
#define TARGET_E500_SINGLE (TARGET_HARD_FLOAT)
#define TARGET_E500_DOUBLE 0

#undef TARGET_ASM_NAMED_SECTION
#define TARGET_ASM_NAMED_SECTION  rs6000_elf_asm_named_section

#undef	TEXT_SECTION_ASM_OP
#define	TEXT_SECTION_ASM_OP	"\t.section\t\".text\",\"axv\""
#define	TEXT_SECTION_ASM_OP_BOOKE	"\t.section\t\".text\",\"ax\""

#define CHECK_E500_OPTIONS									\
  do {														\
    if (TARGET_SPE || TARGET_SPE_ABI || TARGET_E500_SINGLE)	\
      {														\
	if (TARGET_ALTIVEC)										\
	  error ("AltiVec instructions cannot coexist");		\
	if (TARGET_VSX)											\
	  error ("VSX instructions cannot coexist");			\
	if (TARGET_64BIT)										\
	  error ("64-bit SPE not supported");					\
	if (TARGET_HARD_FLOAT && TARGET_FPRS)					\
	  error ("E200 and FPRs not supported");				\
	if (TARGET_E500_DOUBLE)									\
	  error ("E200 and double FPRs not supported");			\
      }														\
  } while (0)

/* Override rs6000.h definition.  */
#undef HARD_REGNO_CALLER_SAVE_MODE

/* When setting up caller-save slots (MODE == VOIDmode) ensure we
   allocate space for DFmode.  Save gprs in the correct mode too.  */
#define HARD_REGNO_CALLER_SAVE_MODE(REGNO, NREGS, MODE) \
  (choose_hard_reg_mode ((REGNO), (NREGS), false))

/* Add -meabi to target flags.  */
#undef TARGET_DEFAULT
#define TARGET_DEFAULT MASK_EABI

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()          \
  do                                      \
    {                                     \
      builtin_define_std ("PPC");         \
      builtin_define ("__embedded__");    \
      builtin_define ("__PPC_EABI__");    \
      builtin_assert ("system=embedded"); \
      builtin_assert ("cpu=powerpc");     \
      builtin_assert ("machine=powerpc"); \
      TARGET_OS_SYSV_CPP_BUILTINS ();     \
    }                                     \
  while (0)

#undef SUBSUBTARGET_OVERRIDE_OPTIONS
#define SUBSUBTARGET_OVERRIDE_OPTIONS		\
  do						\
    {						\
      if (!global_options_set.x_rs6000_alignment_flags)	\
	rs6000_alignment_flags = MASK_ALIGN_NATURAL;		\
    target_flags &= ~(MASK_PPC_GPOPT);					\
	if (TARGET_HARD_FLOAT)								\
		rs6000_float_gprs=1;							\
    }						\
  while (0)
