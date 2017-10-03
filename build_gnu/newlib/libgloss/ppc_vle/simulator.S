/*
 * simulator.S -- PowerPC simulator system calls.
 *
 * Copyright (c) 1995, 2000, 2001 Cygnus Support
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose, provided
 * that existing copyright notices are retained in all copies and that this
 * notice is included verbatim in any distributions. No written agreement,
 * license, or royalty fee is required for any of the authorized uses.
 * Modifications to this software may be copyrighted by their authors
 * and need not follow the licensing terms described here, provided that
 * the new terms are clearly indicated on the first page of each file where
 * they apply.
 */

#include "ppc-asm.h"

FUNC_START(_exit)
	se_li	r0, 1
	se_sc

/*
 * Insure that the debugger tells the client that the PC is in _exit,
 * not whatever function happens to follow this function.
 */

0:	trap
	se_b	0b			/* we never should return, but... */

FUNC_END(_exit)

FUNC_START(read)
	se_li	r0,3
	se_sc
	se_bso	err
	se_blr
FUNC_END(read)

FUNC_START(write)
	se_li	r0,4
	se_sc
	se_bso	err
	se_blr
FUNC_END(write)

FUNC_START(open)
	se_li	r0,5
	se_sc
	se_bso	err
	se_blr
FUNC_END(open)

FUNC_START(close)
	se_li	r0,6
	se_sc
	se_bso	err
	se_blr
FUNC_END(close)

FUNC_START(brk)
	se_li	r0,17
	se_sc
	se_bso	err
	se_blr
FUNC_END(brk)

FUNC_START(access)
	se_li	r0,33
	se_sc
	se_bso	err
	se_blr
FUNC_END(access)

FUNC_START(dup)
	se_li	r0,41
	se_sc
	se_bso	err
	se_blr
FUNC_END(dup)

FUNC_START(gettimeofday)
	e_li	r0,116
	se_sc
	se_bso	err
	se_blr
FUNC_END(gettimeofday)

FUNC_START(lseek)
	e_li	r0,199
	se_sc
	se_bso	err
	se_blr
FUNC_END(lseek)
err:
	e_b	FUNC_NAME(_cerror)

