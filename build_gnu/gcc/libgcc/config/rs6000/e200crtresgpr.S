/*
 * Special support for eabi and SVR4
 *
 *   Copyright (C) 1995-2014 Free Software Foundation, Inc.
 *   Written By Michael Meissner
 *   64-bit support written by David Edelsohn
 * 
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3, or (at your option) any
 * later version.
 * 
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * Under Section 7 of GPL version 3, you are granted additional
 * permissions described in the GCC Runtime Library Exception, version
 * 3.1, as published by the Free Software Foundation.
 *
 * You should have received a copy of the GNU General Public License and
 * a copy of the GCC Runtime Library Exception along with this program;
 * see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
 * <http://www.gnu.org/licenses/>.
 */ 

/* Do any initializations needed for the eabi environment */

	.section ".text"
	#include "ppc-asm.h"


/* Routines for restoring integer registers, called by the compiler.  */
/* Called with r11 pointing to the stack header word of the caller of the */
/* function, just beyond the end of the integer restore area.  */

CFI_STARTPROC
HIDDEN_FUNC(_restgpr_14)	e_lwz	14,-72(11)	/* restore gp registers */
HIDDEN_FUNC(_restgpr_15)	e_lwz	15,-68(11)
HIDDEN_FUNC(_restgpr_16)	e_lwz	16,-64(11)
HIDDEN_FUNC(_restgpr_17)	e_lwz	17,-60(11)
HIDDEN_FUNC(_restgpr_18)	e_lwz	18,-56(11)
HIDDEN_FUNC(_restgpr_19)	e_lwz	19,-52(11)
HIDDEN_FUNC(_restgpr_20)	e_lwz	20,-48(11)
HIDDEN_FUNC(_restgpr_21)	e_lwz	21,-44(11)
HIDDEN_FUNC(_restgpr_22)	e_lwz	22,-40(11)
HIDDEN_FUNC(_restgpr_23)	e_lwz	23,-36(11)
HIDDEN_FUNC(_restgpr_24)	e_lwz	24,-32(11)
HIDDEN_FUNC(_restgpr_25)	e_lwz	25,-28(11)
HIDDEN_FUNC(_restgpr_26)	e_lwz	26,-24(11)
HIDDEN_FUNC(_restgpr_27)	e_lwz	27,-20(11)
HIDDEN_FUNC(_restgpr_28)	e_lwz	28,-16(11)
HIDDEN_FUNC(_restgpr_29)	e_lwz	29,-12(11)
HIDDEN_FUNC(_restgpr_30)	e_lwz	30,-8(11)
HIDDEN_FUNC(_restgpr_31)	e_lwz	31,-4(11)
			se_blr
FUNC_END(_restgpr_31)
FUNC_END(_restgpr_30)
FUNC_END(_restgpr_29)
FUNC_END(_restgpr_28)
FUNC_END(_restgpr_27)
FUNC_END(_restgpr_26)
FUNC_END(_restgpr_25)
FUNC_END(_restgpr_24)
FUNC_END(_restgpr_23)
FUNC_END(_restgpr_22)
FUNC_END(_restgpr_21)
FUNC_END(_restgpr_20)
FUNC_END(_restgpr_19)
FUNC_END(_restgpr_18)
FUNC_END(_restgpr_17)
FUNC_END(_restgpr_16)
FUNC_END(_restgpr_15)
FUNC_END(_restgpr_14)
CFI_ENDPROC

