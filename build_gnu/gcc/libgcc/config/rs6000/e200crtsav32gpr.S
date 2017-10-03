/*
 * Special support for e500 eabi and SVR4
 *
 *   Copyright (C) 2008-2014 Free Software Foundation, Inc.
 *   Written by Nathan Froyd
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

	.section ".text"
	#include "ppc-asm.h"

#ifdef __SPE__

/* Routines for saving 32-bit integer registers, called by the compiler.  */
/* "Bare" versions that simply return to their caller.  */

HIDDEN_FUNC(_save32gpr_14)	e_stw 14,-72(11)
HIDDEN_FUNC(_save32gpr_15)	e_stw 15,-68(11)
HIDDEN_FUNC(_save32gpr_16)	e_stw 16,-64(11)
HIDDEN_FUNC(_save32gpr_17)	e_stw 17,-60(11)
HIDDEN_FUNC(_save32gpr_18)	e_stw 18,-56(11)
HIDDEN_FUNC(_save32gpr_19)	e_stw 19,-52(11)
HIDDEN_FUNC(_save32gpr_20)	e_stw 20,-48(11)
HIDDEN_FUNC(_save32gpr_21)	e_stw 21,-44(11)
HIDDEN_FUNC(_save32gpr_22)	e_stw 22,-40(11)
HIDDEN_FUNC(_save32gpr_23)	e_stw 23,-36(11)
HIDDEN_FUNC(_save32gpr_24)	e_stw 24,-32(11)
HIDDEN_FUNC(_save32gpr_25)	e_stw 25,-28(11)
HIDDEN_FUNC(_save32gpr_26)	e_stw 26,-24(11)
HIDDEN_FUNC(_save32gpr_27)	e_stw 27,-20(11)
HIDDEN_FUNC(_save32gpr_28)	e_stw 28,-16(11)
HIDDEN_FUNC(_save32gpr_29)	e_stw 29,-12(11)
HIDDEN_FUNC(_save32gpr_30)	e_stw 30,-8(11)
HIDDEN_FUNC(_save32gpr_31)	e_stw 31,-4(11)
				se_blr
FUNC_END(_save32gpr_31)
FUNC_END(_save32gpr_30)
FUNC_END(_save32gpr_29)
FUNC_END(_save32gpr_28)
FUNC_END(_save32gpr_27)
FUNC_END(_save32gpr_26)
FUNC_END(_save32gpr_25)
FUNC_END(_save32gpr_24)
FUNC_END(_save32gpr_23)
FUNC_END(_save32gpr_22)
FUNC_END(_save32gpr_21)
FUNC_END(_save32gpr_20)
FUNC_END(_save32gpr_19)
FUNC_END(_save32gpr_18)
FUNC_END(_save32gpr_17)
FUNC_END(_save32gpr_16)
FUNC_END(_save32gpr_15)
FUNC_END(_save32gpr_14)

#endif
