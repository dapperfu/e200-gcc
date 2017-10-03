;; Constraint definitions for RS6000
;; Copyright (C) 2006-2014 Free Software Foundation, Inc.
;;
;; This file is part of GCC.
;;
;; GCC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.
;;
;; GCC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

;; Available constraint letters: "e", "k", "q", "u", "A", "B", "C", "D"

;; Register constraints

(define_register_constraint "f" "rs6000_constraints[RS6000_CONSTRAINT_f]"
  "@internal")

(define_register_constraint "d" "rs6000_constraints[RS6000_CONSTRAINT_d]"
  "@internal")

(define_register_constraint "b" "BASE_REGS"
  "@internal")

(define_register_constraint "h" "SPECIAL_REGS"
  "@internal")

(define_register_constraint "c" "CTR_REGS"
  "@internal")

(define_register_constraint "l" "LINK_REGS"
  "@internal")

(define_register_constraint "v" "ALTIVEC_REGS"
  "@internal")

(define_register_constraint "x" "CR0_REGS"
  "@internal")

(define_register_constraint "y" "CR_REGS"
  "@internal")

(define_register_constraint "z" "CA_REGS"
  "@internal")

;; Use w as a prefix to add VSX modes
;; any VSX register
(define_register_constraint "wa" "rs6000_constraints[RS6000_CONSTRAINT_wa]"
  "Any VSX register if the -mvsx option was used or NO_REGS.")

;; NOTE: For compatibility, "wc" is reserved to represent individual CR bits.
;; It is currently used for that purpose in LLVM.

(define_register_constraint "wd" "rs6000_constraints[RS6000_CONSTRAINT_wd]"
  "VSX vector register to hold vector double data or NO_REGS.")

(define_register_constraint "wf" "rs6000_constraints[RS6000_CONSTRAINT_wf]"
  "VSX vector register to hold vector float data or NO_REGS.")

(define_register_constraint "wg" "rs6000_constraints[RS6000_CONSTRAINT_wg]"
  "If -mmfpgpr was used, a floating point register or NO_REGS.")

(define_register_constraint "wh" "rs6000_constraints[RS6000_CONSTRAINT_wh]"
  "Floating point register if direct moves are available, or NO_REGS.")

;; At present, DImode is not allowed in the Altivec registers.  If in the
;; future it is allowed, wi/wj can be set to VSX_REGS instead of FLOAT_REGS.
(define_register_constraint "wi" "rs6000_constraints[RS6000_CONSTRAINT_wi]"
  "FP or VSX register to hold 64-bit integers for VSX insns or NO_REGS.")

(define_register_constraint "wj" "rs6000_constraints[RS6000_CONSTRAINT_wj]"
  "FP or VSX register to hold 64-bit integers for direct moves or NO_REGS.")

(define_register_constraint "wk" "rs6000_constraints[RS6000_CONSTRAINT_wk]"
  "FP or VSX register to hold 64-bit doubles for direct moves or NO_REGS.")

(define_register_constraint "wl" "rs6000_constraints[RS6000_CONSTRAINT_wl]"
  "Floating point register if the LFIWAX instruction is enabled or NO_REGS.")

(define_register_constraint "wm" "rs6000_constraints[RS6000_CONSTRAINT_wm]"
  "VSX register if direct move instructions are enabled, or NO_REGS.")

;; NO_REGs register constraint, used to merge mov{sd,sf}, since movsd can use
;; direct move directly, and movsf can't to move between the register sets.
;; There is a mode_attr that resolves to wm for SDmode and wn for SFmode
(define_register_constraint "wn" "NO_REGS" "No register (NO_REGS).")

(define_register_constraint "wr" "rs6000_constraints[RS6000_CONSTRAINT_wr]"
  "General purpose register if 64-bit instructions are enabled or NO_REGS.")

(define_register_constraint "ws" "rs6000_constraints[RS6000_CONSTRAINT_ws]"
  "VSX vector register to hold scalar double values or NO_REGS.")

(define_register_constraint "wt" "rs6000_constraints[RS6000_CONSTRAINT_wt]"
  "VSX vector register to hold 128 bit integer or NO_REGS.")

(define_register_constraint "wu" "rs6000_constraints[RS6000_CONSTRAINT_wu]"
  "Altivec register to use for float/32-bit int loads/stores  or NO_REGS.")

(define_register_constraint "wv" "rs6000_constraints[RS6000_CONSTRAINT_wv]"
  "Altivec register to use for double loads/stores  or NO_REGS.")

(define_register_constraint "ww" "rs6000_constraints[RS6000_CONSTRAINT_ww]"
  "FP or VSX register to perform float operations under -mvsx or NO_REGS.")

(define_register_constraint "wx" "rs6000_constraints[RS6000_CONSTRAINT_wx]"
  "Floating point register if the STFIWX instruction is enabled or NO_REGS.")

(define_register_constraint "wy" "rs6000_constraints[RS6000_CONSTRAINT_wy]"
  "FP or VSX register to perform ISA 2.07 float ops or NO_REGS.")

(define_register_constraint "wz" "rs6000_constraints[RS6000_CONSTRAINT_wz]"
  "Floating point register if the LFIWZX instruction is enabled or NO_REGS.")

(define_constraint "wD"
  "Int constant that is the element number of the 64-bit scalar in a vector."
  (and (match_code "const_int")
       (match_test "TARGET_VSX && (ival == VECTOR_ELEMENT_SCALAR_64BIT)")))

;; Lq/stq validates the address for load/store quad
(define_memory_constraint "wQ"
  "Memory operand suitable for the load/store quad instructions"
  (match_operand 0 "quad_memory_operand"))

;; Altivec style load/store that ignores the bottom bits of the address
(define_memory_constraint "wZ"
  "Indexed or indirect memory operand, ignoring the bottom 4 bits"
  (match_operand 0 "altivec_indexed_or_indirect_operand"))

;; Integer constraints

(define_constraint "I"
  "A signed 16-bit constant"
  (and (match_code "const_int")
       (match_test "(unsigned HOST_WIDE_INT) (ival + 0x8000) < 0x10000")))

(define_constraint "J"
  "high-order 16 bits nonzero"
  (and (match_code "const_int")
       (match_test "(ival & (~ (unsigned HOST_WIDE_INT) 0xffff0000)) == 0")))

(define_constraint "K"
  "low-order 16 bits nonzero"
  (and (match_code "const_int")
       (match_test "(ival & (~ (HOST_WIDE_INT) 0xffff)) == 0")))

(define_constraint "L"
  "signed 16-bit constant shifted left 16 bits"
  (and (match_code "const_int")
       (match_test "((ival & 0xffff) == 0
		      && (ival >> 31 == -1 || ival >> 31 == 0))")))

(define_constraint "M"
  "constant greater than 31"
  (and (match_code "const_int")
       (match_test "ival > 31")))

(define_constraint "N"
  "positive constant that is an exact power of two"
  (and (match_code "const_int")
       (match_test "ival > 0 && exact_log2 (ival) >= 0")))

(define_constraint "O"
  "constant zero"
  (and (match_code "const_int")
       (match_test "ival == 0")))

(define_constraint "P"
  "constant whose negation is signed 16-bit constant"
  (and (match_code "const_int")
       (match_test "(unsigned HOST_WIDE_INT) ((- ival) + 0x8000) < 0x10000")))

;; VLE constraints

(define_register_constraint "kareg" "VLE_ALT_REGS"
  "Alternate General Purpose Register in the range r8-r23 to be used in VLE")

(define_register_constraint "kcreg" "VLE_CR_REGS"
  "CR fields from Field 0 to Field 3 to be used in VLE")

(define_register_constraint "kcrxx"
  "rs6000_constraints[RS6000_CONSTRAINT_kcrxx]"
  "@internal")

(define_constraint "kli20"
  "A signed 20-bit immediate"
  (and (match_code "const_int")
       (match_test "ival >= -524288 && ival <= 524287")))

(define_constraint "kmsd4"
  "An SD4(Rx) form memory operand"
  (match_operand 0 "vle_sd4_operand"))

(define_constraint "kmmd8"
  "An 8-bit signed immediate"
  (and (match_code "const_int")
       (match_test " ival >= -128 && ival < 128")))

(define_constraint "koim5"
  "A constant in the range 1-32"
  (and (match_code "const_int")
       (match_test "ival >= 1 && ival <= 32")))

(define_constraint "kone1"
  "The constant 1"
  (match_test "op == const1_rtx || op == CONST1_RTX (GET_MODE (op))"))

(define_register_constraint "kregs" "VLE_REGS"
  "General Purpose Register in the ranges r0-r7 or r24-r31 to be used in VLE")

(define_constraint "ksci8"
  "An eight bit immediate constant shifted left by 0, 1, 2 or 3 bytes"
  (and (match_code "const_int")
       (match_test "valid_sci8_immediate (ival)")))

(define_constraint "kscp8"
  "A constant whose negation is an eight bit immediate shifted left by 0, 1, 2 or 3 bytes"
  (and (match_code "const_int")
       (match_test "valid_sci8_immediate (-ival)")))

(define_constraint "kscI8"
  "An immediate constant that matches the ksci8 or I constraint if making VLE or non-VLE code respectively"
  (and (match_code "const_int")
       (if_then_else (match_test "TARGET_VLE")
		     (match_test "satisfies_constraint_ksci8 (op)")
		     (match_test "satisfies_constraint_I (op)"))))

(define_constraint "kscP8"
  "An immediate constant that matches the kscp8 or P constraint if making VLE or non-VLE code respectively"
  (and (match_code "const_int")
       (if_then_else (match_test "TARGET_VLE")
		     (match_test "satisfies_constraint_kscp8 (op)")
		     (match_test "satisfies_constraint_P (op)"))))

(define_constraint "kuim5"
  "A constant in the range 0-31"
  (and (match_code "const_int")
       (match_test "ival >= 0 && ival <= 31")))

(define_constraint "kbit5"
  "A 32-bit constant that has exactly one bit set"
  (and (match_code "const_int")
       (ior (match_test "ival != 0 && (ival & -ival & 0xffffffff) == ival")
	    (match_test "TARGET_32BIT && ival + 0x80000000 == 0"))))

(define_constraint "kbic5"
  "A 32-bit constant that has exactly one bit clear"
  (and (match_code "const_int")
       (ior (match_test "(~ival & -~ival & 0xffffffff) == ~ival")
	    (match_test "TARGET_32BIT && ival == 0x7fffffff"))))

(define_constraint "kmsk5"
  "A 32-bit constant that is a contiguous mask of 1-32 low-order bits set"
  (and (match_code "const_int")
       (ior (and (match_test "((ival | 0xffffffff) ^ 0xffffffff) == 0")
		 (match_test "((ival + 1) & -(ival + 1)) == ival + 1"))
	    (match_test "TARGET_32BIT && ival + 1 == 0"))))

(define_constraint "kuim7"
  "A constant in the range 0-127"
  (and (match_code "const_int")
       (match_test "ival >= 0 && ival <= 127")))

(define_constraint "kui16"
  "An unsigned 16-bit constant."
  (and (match_code "const_int")
       (match_test "ival >= 0 && ival <= 65535")))


;; Floating-point constraints

(define_constraint "G"
  "Constant that can be copied into GPR with two insns for DF/DI
   and one for SF."
  (and (match_code "const_double")
       (match_test "num_insns_constant (op, mode)
		    == (mode == SFmode ? 1 : 2)")))

(define_constraint "H"
  "DF/DI constant that takes three insns."
  (and (match_code "const_double")
       (match_test "num_insns_constant (op, mode) == 3")))

;; Memory constraints

(define_memory_constraint "es"
  "A ``stable'' memory operand; that is, one which does not include any
automodification of the base register.  Unlike @samp{m}, this constraint
can be used in @code{asm} statements that might access the operand
several times, or that might not access it at all."
  (and (match_code "mem")
       (match_test "GET_RTX_CLASS (GET_CODE (XEXP (op, 0))) != RTX_AUTOINC")))

(define_memory_constraint "Q"
  "Memory operand that is an offset from a register (it is usually better
to use @samp{m} or @samp{es} in @code{asm} statements)"
  (and (match_code "mem")
       (match_test "GET_CODE (XEXP (op, 0)) == REG")))

(define_memory_constraint "Y"
  "memory operand for 8 byte and 16 byte gpr load/store"
  (and (match_code "mem")
       (match_operand 0 "mem_operand_gpr")))

(define_memory_constraint "Z"
  "Memory operand that is an indexed or indirect from a register (it is
usually better to use @samp{m} or @samp{es} in @code{asm} statements)"
  (match_operand 0 "indexed_or_indirect_operand"))

;; Address constraints

(define_address_constraint "a"
  "Indexed or indirect address operand"
  (match_operand 0 "indexed_or_indirect_address"))

(define_constraint "R"
  "AIX TOC entry"
  (match_test "legitimate_constant_pool_address_p (op, QImode, false)"))

;; General constraints

(define_constraint "S"
  "Constant that can be placed into a 64-bit mask operand"
  (match_operand 0 "mask64_operand"))

(define_constraint "T"
  "Constant that can be placed into a 32-bit mask operand"
  (match_operand 0 "mask_operand"))

(define_constraint "U"
  "V.4 small data reference"
  (and (match_test "DEFAULT_ABI == ABI_V4")
       (match_operand 0 "small_data_operand")))

(define_constraint "t"
  "AND masks that can be performed by two rldic{l,r} insns
   (but excluding those that could match other constraints of anddi3)"
  (and (and (and (match_operand 0 "mask64_2_operand")
		 (match_test "(fixed_regs[CR0_REGNO]
			      || !logical_operand (op, DImode))"))
	    (not (match_operand 0 "mask_operand")))
       (not (match_operand 0 "mask64_operand"))))

(define_constraint "W"
  "vector constant that does not require memory"
  (match_operand 0 "easy_vector_constant"))

(define_constraint "j"
  "Zero vector constant"
  (match_test "op == const0_rtx || op == CONST0_RTX (GET_MODE (op))"))
