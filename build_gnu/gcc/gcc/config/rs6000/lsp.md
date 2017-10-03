;; e200 LSP description
;; Copyright (C) 22015 Free Software Foundation, Inc.
;; Contributed by Marcel Achim (rb2501c@freescale.com)

;; This file is part of GCC.

;; GCC is free software; you can redistribute it and/or modify it
;; under the terms of the GNU General Public License as published
;; by the Free Software Foundation; either version 3, or (at your
;; option) any later version.

;; GCC is distributed in the hope that it will be useful, but WITHOUT
;; ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
;; or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
;; License for more details.

;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

;; Modes using a 64-bit register.
(define_mode_iterator LSP64 [V4HI V2SI V1DI])

;; LSP SIMD instructions

(define_insn "lsp_zbrminc"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2200))]
    "TARGET_LSP"
    "zbrminc %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zcircinc"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2201))]
    "TARGET_LSP"
    "zcircinc %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvabsh"
    [(set (match_operand:V2SI 0 "gpc_reg_operand" "=r")
     (unspec:V2SI [(match_operand:V2SI 1 "gpc_reg_operand" "r")] 2202))]
    "TARGET_LSP"
    "zvabsh %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvabshs"
    [(set (match_operand:V2SI 0 "gpc_reg_operand" "=r")
     (unspec:V2SI [(match_operand:V2SI 1 "gpc_reg_operand" "r")] 2203))]
    "TARGET_LSP"
    "zvabshs %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zabsw"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:V2SI 2 "gpc_reg_operand" "r")] 2204))]
    "TARGET_LSP"
    "zabsw %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zabsws"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:V2SI 2 "gpc_reg_operand" "r")] 2205))]
    "TARGET_LSP"
    "zabsws %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zaddd"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (plus:DI (match_operand:DI 1 "gpc_reg_operand" "r")
     	   (match_operand:DI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2206)]
    "TARGET_LSP"
    "zaddd %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zadddss"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (plus:DI (match_operand:DI 1 "gpc_reg_operand" "r")
     	   (match_operand:DI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2207)]
    "TARGET_LSP"
    "zadddss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zadddus"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (plus:DI (match_operand:DI 1 "gpc_reg_operand" "r")
     	   (match_operand:DI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2208)]
    "TARGET_LSP"
    "zadddus %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvaddh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (plus:SI (match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2212)]
    "TARGET_LSP"
    "zvaddh %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvaddhss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (plus:SI (match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2211)]
    "TARGET_LSP"
    "zvaddhss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvaddhus"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (plus:SI (match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2213)]
    "TARGET_LSP"
    "zvaddhus %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvaddhx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (plus:SI (match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2214)]
    "TARGET_LSP"
    "zvaddhx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvaddhxss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (plus:SI (match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2215)]
    "TARGET_LSP"
    "zvaddhxss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvaddih"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (plus:SI (match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2216)]
    "TARGET_LSP"
    "zvaddih %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvaddsubfh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")] 2217))]
    "TARGET_LSP"
    "zvaddsubfh %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvaddsubfhss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")] 2218))]
    "TARGET_LSP"
    "zvaddsubfhss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvaddsubfhx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")] 2219))]
    "TARGET_LSP"
    "zvaddsubfhx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvaddsubfhxss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")] 2220))]
    "TARGET_LSP"
    "zvaddsubfhxss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zaddhesw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (plus:SI (match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2221)]
    "TARGET_LSP"
    "zaddhesw %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zaddheuw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (plus:SI (match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2222)]
    "TARGET_LSP"
    "zaddheuw %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zaddhosw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (plus:SI (match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2223)]
    "TARGET_LSP"
    "zaddhosw %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zaddhouw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (plus:SI (match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2224)]
    "TARGET_LSP"
    "zaddhouw %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvaddw"
    [(set (match_operand:V2SI 0 "gpc_reg_operand" "=r")
     (plus:V2SI (match_operand:V2SI 1 "gpc_reg_operand" "r")
     	   (match_operand:V2SI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2225)]
    "TARGET_LSP"
    "zvaddw %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvaddsubfw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")] 2226))]
    "TARGET_LSP"
    "zvaddsubfw %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvaddsubfwss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")] 2227))]
    "TARGET_LSP"
    "zvaddsubfwss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zaddwgsf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (plus:DI (match_operand:DI 1 "gpc_reg_operand" "r")
     	   (match_operand:DI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2209)]
    "TARGET_LSP"
    "zaddwgsf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zaddwgsi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (plus:DI (match_operand:DI 1 "gpc_reg_operand" "r")
     	   (match_operand:DI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2210)]
    "TARGET_LSP"
    "zaddwgsi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zaddwgui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (plus:DI (match_operand:DI 1 "gpc_reg_operand" "r")
     	   (match_operand:DI 2 "gpc_reg_operand" "r")))
     (unspec [(const_int 0)] 2211)]
    "TARGET_LSP"
    "zaddwgui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zaddwss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")] 2228))]
    "TARGET_LSP"
    "zaddwss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvaddwss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")] 2229))]
    "TARGET_LSP"
    "zvaddwss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zaddwus"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")] 2230))]
    "TARGET_LSP"
    "zaddwus %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvaddwus"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     	   (match_operand:SI 2 "gpc_reg_operand" "r")] 2231))]
    "TARGET_LSP"
    "zvaddwus %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvcmpeqh"
    [(set (match_operand:CC 0 "gpc_reg_operand" "=r")
     (unspec:CC [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:V2SI 2 "gpc_reg_operand" "r")] 2232))]
    "TARGET_LSP"
    "zvcmpeqh %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvcmpgths"
    [(set (match_operand:CC 0 "gpc_reg_operand" "=r")
     (unspec:CC [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:V2SI 2 "gpc_reg_operand" "r")] 2233))]
    "TARGET_LSP"
    "zvcmpgths %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvcmpgthu"
    [(set (match_operand:CC 0 "gpc_reg_operand" "=r")
     (unspec:CC [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:V2SI 2 "gpc_reg_operand" "r")] 2234))]
    "TARGET_LSP"
    "zvcmpgthu %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvcmplths"
    [(set (match_operand:CC 0 "gpc_reg_operand" "=r")
     (unspec:CC [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:V2SI 2 "gpc_reg_operand" "r")] 2235))]
    "TARGET_LSP"
    "zvcmplths %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvcmplthu"
    [(set (match_operand:CC 0 "gpc_reg_operand" "=r")
     (unspec:CC [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:V2SI 2 "gpc_reg_operand" "r")] 2888))]
    "TARGET_LSP"
    "zvcmplthu %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvcntlsh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")] 2236))]
    "TARGET_LSP"
    "zvcntlsh %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zcntlsw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")] 2237))]
    "TARGET_LSP"
    "zcntlsw %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvcntlzh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")] 2238))]
    "TARGET_LSP"
    "zvcntlzh %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zdivwsf"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2239))]
    "TARGET_LSP"
    "zdivwsf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmergehih"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2240))]
    "TARGET_LSP"
    "zvmergehih %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmergehiloh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2241))]
    "TARGET_LSP"
    "zvmergehiloh %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmergeloh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2242))]
    "TARGET_LSP"
    "zvmergeloh %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmergelohih"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2243))]
    "TARGET_LSP"
    "zvmergelohih %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvnegh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2244))]
    "TARGET_LSP"
    "zvnegh %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvnegho"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2245))]
    "TARGET_LSP"
    "zvnegho %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvneghos"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")] 2246))]
    "TARGET_LSP"
    "zvneghos %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvneghs"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")] 2247))]
    "TARGET_LSP"
    "zvneghs %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_znegws"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")] 2248))]
    "TARGET_LSP"
    "znegws %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvpkshgwshfrs"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2249))]
    "TARGET_LSP"
    "zvpkshgwshfrs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zpkswgshfrs"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2250))]
    "TARGET_LSP"
    "zpkswgshfrs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zpkswgswfrs"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2251))]
    "TARGET_LSP"
    "zpkswgswfrs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvpkswshfrs"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2252))]
    "TARGET_LSP"
    "zvpkswshfrs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvpkswshs"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2253))]
    "TARGET_LSP"
    "zvpkswshs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvpkswuhs"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2254))]
    "TARGET_LSP"
    "zvpkswuhs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvpkuwuhs"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2255))]
    "TARGET_LSP"
    "zvpkuwuhs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvrlh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2256))]
    "TARGET_LSP"
    "zvrlh %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvrlhi"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2257))]
    "TARGET_LSP"
    "zvrlhi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zrndwh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")] 2258))]
    "TARGET_LSP"
    "zrndwh %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zrndwhss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")] 2259))]
    "TARGET_LSP"
    "zrndwhss %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsatsdsw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2261))]
    "TARGET_LSP"
    "zsatsdsw %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsatsduw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2262))]
    "TARGET_LSP"
    "zsatsduw %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsatshuh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")] 2263))]
    "TARGET_LSP"
    "zvsatshuh %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsatswsh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")] 2264))]
    "TARGET_LSP"
    "zsatswsh %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsatswuh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")] 2265))]
    "TARGET_LSP"
    "zsatswuh %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsatswuw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")] 2266))]
    "TARGET_LSP"
    "zsatswuw %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsatuduw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2267))]
    "TARGET_LSP"
    "zsatuduw %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsatuhsh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")] 2268))]
    "TARGET_LSP"
    "zvsatuhsh %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsatuwsw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")] 2269))]
    "TARGET_LSP"
    "zsatuwsw %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsatuwsh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")] 2270))]
    "TARGET_LSP"
    "zsatuwsh %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsatuwuh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")] 2271))]
    "TARGET_LSP"
    "zsatuwuh %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvselh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2272))]
    "TARGET_LSP"
    "zvselh %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvslh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2273))]
    "TARGET_LSP"
    "zvslh %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvslhi"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2274))]
    "TARGET_LSP"
    "zvslhi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvslhss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2275))]
    "TARGET_LSP"
    "zvslhss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvslhiss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2276))]
    "TARGET_LSP"
    "zvslhiss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvslhus"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2277))]
    "TARGET_LSP"
    "zvslhus %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvslhius"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2278))]
    "TARGET_LSP"
    "zvslhius %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zslwss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2279))]
    "TARGET_LSP"
    "zslwss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zslwiss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2280))]
    "TARGET_LSP"
    "zslwiss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zslwus"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2281))]
    "TARGET_LSP"
    "zslwus %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zslwius"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2282))]
    "TARGET_LSP"
    "zslwius %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsplatfih"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "immediate_operand" "i")] 2283))]
    "TARGET_LSP"
    "zvsplatfih %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsplatih"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "immediate_operand" "i")] 2284))]
    "TARGET_LSP"
    "zvsplatih %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsrhis"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2285))]
    "TARGET_LSP"
    "zvsrhis %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsrhiu"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2286))]
    "TARGET_LSP"
    "zvsrhiu %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsrhs"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2287))]
    "TARGET_LSP"
    "zvsrhs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsrhu"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2288))]
    "TARGET_LSP"
    "zvsrhu %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsubfaddh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2289))]
    "TARGET_LSP"
    "zvsubfaddh %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsubfaddhss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2290))]
    "TARGET_LSP"
    "zvsubfaddhss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsubfaddhx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2291))]
    "TARGET_LSP"
    "zvsubfaddhx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsubfaddhxss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2292))]
    "TARGET_LSP"
    "zvsubfaddhxss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsubfd"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2293))]
    "TARGET_LSP"
    "zsubfd %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsubfdss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2294))]
    "TARGET_LSP"
    "zsubfdss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsubfdus"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2295))]
    "TARGET_LSP"
    "zsubfdus %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsubfh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2296))]
    "TARGET_LSP"
    "zvsubfh %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsubfhesw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2297))]
    "TARGET_LSP"
    "zsubfhesw %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsubfheuw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2298))]
    "TARGET_LSP"
    "zsubfheuw %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsubfhosw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2299))]
    "TARGET_LSP"
    "zsubfhosw %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsubfhouw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2300))]
    "TARGET_LSP"
    "zsubfhouw %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsubfhss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2301))]
    "TARGET_LSP"
    "zvsubfhss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsubfhus"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2302))]
    "TARGET_LSP"
    "zvsubfhus %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsubfhx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2303))]
    "TARGET_LSP"
    "zvsubfhx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsubfhxss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2304))]
    "TARGET_LSP"
    "zvsubfhxss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsubfw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2305))]
    "TARGET_LSP"
    "zvsubfw %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsubfaddw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2306))]
    "TARGET_LSP"
    "zvsubfaddw %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsubfaddwss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2307))]
    "TARGET_LSP"
    "zvsubfaddwss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsubfwgsf"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2308))]
    "TARGET_LSP"
    "zsubfwgsf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsubfwgsi"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2309))]
    "TARGET_LSP"
    "zsubfwgsi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsubfwgui"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2310))]
    "TARGET_LSP"
    "zsubfwgui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsubfwss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2311))]
    "TARGET_LSP"
    "zsubfwss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsubfwss"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2312))]
    "TARGET_LSP"
    "zvsubfwss %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsubfwus"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2313))]
    "TARGET_LSP"
    "zsubfwus %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsubfwus"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2314))]
    "TARGET_LSP"
    "zvsubfwus %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvsubifh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2315))]
    "TARGET_LSP"
    "zvsubifh %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvunpkhgwsf"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "immediate_operand" "i")] 2316))]
    "TARGET_LSP"
    "zvunpkhgwsf %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvunpkhsf"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "immediate_operand" "i")] 2317))]
    "TARGET_LSP"
    "zvunpkhsf %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvunpkhsi"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "immediate_operand" "i")] 2318))]
    "TARGET_LSP"
    "zvunpkhsi %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvunpkhui"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "immediate_operand" "i")] 2319))]
    "TARGET_LSP"
    "zvunpkhui %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zunpkwgsf"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "immediate_operand" "i")] 2320))]
    "TARGET_LSP"
    "zunpkwgsf %0, %1"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zxtrw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")
     (match_operand:SI 3 "immediate_operand" "i")] 2321))]
    "TARGET_LSP"
    "zxtrw %0, %1, %2, %3"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zldd"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2322))]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zldd %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlddu"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2323))]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlddu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlddx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2324))]
    "TARGET_LSP"
    "zlddx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlddmx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2325))]
    "TARGET_LSP"
    "zlddmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zldh"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2326))]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zldh %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zldhu"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2327))]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zldhu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zldhx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2328))]
    "TARGET_LSP"
    "zldhx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zldhmx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2329))]
    "TARGET_LSP"
    "zldhmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zldw"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2330))]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zldw %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zldwu"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2331))]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zldwu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zldwx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2332))]
    "TARGET_LSP"
    "zldwx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zldwmx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2333))]
    "TARGET_LSP"
    "zldwmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhgwsf"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2334))]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlhgwsf %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhgwsfu"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "immediate_operand" "i")] 2335))]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlhgwsfu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhgwsfx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2336))]
    "TARGET_LSP"
    "zlhgwsfx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhgwsfmx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
     (unspec:SI [(match_operand:SI 1 "gpc_reg_operand" "r")
     (match_operand:SI 2 "gpc_reg_operand" "r")] 2337))]
    "TARGET_LSP"
    "zlhgwsfmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhhe"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2338)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlhhe %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhheu"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2339)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlhheu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhhex"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2392)]
    "TARGET_LSP"
    "zlhhex %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhhemx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2393)]
    "TARGET_LSP"
    "zlhhemx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhhos"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2340)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlhhos %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhhosu"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2341)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlhhosu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhhosx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2342)]
    "TARGET_LSP"
    "zlhhosx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhhosmx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2343)]
    "TARGET_LSP"
    "zlhhosmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhhou"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2344)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlhhou %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhhouu"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2345)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlhhouu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhhoux"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2346)]
    "TARGET_LSP"
    "zlhhoux %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhhoumx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2347)]
    "TARGET_LSP"
    "zlhhoumx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhhsplat"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2348)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlhhsplat %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhhsplatu"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2349)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlhhsplatu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhhsplatx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2350)]
    "TARGET_LSP"
    "zlhhsplatx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlhhsplatmx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2351)]
    "TARGET_LSP"
    "zlhhsplatmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwgsfd"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2352)]
    "TARGET_LSP"
    "zlwgsfd %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwgsfdu"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2353)]
    "TARGET_LSP"
    "zlwgsfdu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwgsfdx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2354)]
    "TARGET_LSP"
    "zlwgsfdx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwgsfdmx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2355)]
    "TARGET_LSP"
    "zlwgsfdmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwh"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2356)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwh %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhu"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2357)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwhu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2358)]
    "TARGET_LSP"
    "zlwhx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhmx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2359)]
    "TARGET_LSP"
    "zlwhmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhed"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2360)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwhed %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhedu"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2361)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwhedu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhedx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2362)]
    "TARGET_LSP"
    "zlwhedx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhedmx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2363)]
    "TARGET_LSP"
    "zlwhedmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhgwsfd"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2364)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwhgwsfd %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhgwsfdu"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2365)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwhgwsfdu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhgwsfdx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2366)]
    "TARGET_LSP"
    "zlwhgwsfdx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhgwsfdmx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2367)]
    "TARGET_LSP"
    "zlwhgwsfdmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhosd"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2368)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwhosd %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhosdu"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2369)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwhosdu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhosdx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2370)]
    "TARGET_LSP"
    "zlwhosdx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhosdmx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2371)]
    "TARGET_LSP"
    "zlwhosdmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhoud"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2372)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwhoud %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhoudu"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2373)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwhoudu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhoudx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2374)]
    "TARGET_LSP"
    "zlwhoudx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhoudmx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2375)]
    "TARGET_LSP"
    "zlwhoudmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhsplatd"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2376)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwhsplatd %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhsplatdu"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2377)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwhsplatdu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhsplatdx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2378)]
    "TARGET_LSP"
    "zlwhsplatdx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhsplatdmx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2379)]
    "TARGET_LSP"
    "zlwhsplatdmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhsplatwd"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2380)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwhsplatwd %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhsplatwdu"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2381)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwhsplatwdu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhsplatwdx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2382)]
    "TARGET_LSP"
    "zlwhsplatwdx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwhsplatwdmx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2383)]
    "TARGET_LSP"
    "zlwhsplatwdmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlww"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2384)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlww %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwwu"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2385)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwwu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwwx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2386)]
    "TARGET_LSP"
    "zlwwx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwwmx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2387)]
    "TARGET_LSP"
    "zlwwmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwwosd"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2388)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwwosd %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwwosdu"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
      (mem:DI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:QI 2 "immediate_operand" "i"))))
      (unspec [(const_int 0)] 2389)]
    "TARGET_LSP && INTVAL (operands[2]) >= 0 && INTVAL (operands[2]) <= 31"
    "zlwwosdu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwwosdx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2390)]
    "TARGET_LSP"
    "zlwwosdx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zlwwosdmx"
    [(set (match_operand:SI 0 "gpc_reg_operand" "=r")
      (mem:SI (plus:SI (match_operand:SI 1 "gpc_reg_operand" "b")
      (match_operand:SI 2 "gpc_reg_operand" "r"))))
      (unspec [(const_int 0)] 2391)]
    "TARGET_LSP"
    "zlwwosdmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstdd"
    [(set (mem:DI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:DI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2394)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zstdd %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstddu"
    [(set (mem:DI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:DI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2395)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zstddu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstddx"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2396)]
    "TARGET_LSP"
    "zstddx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstddmx"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2397)]
    "TARGET_LSP"
    "zstddmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstdh"
    [(set (mem:V4HI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:V4HI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2398)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zstdh %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstdhu"
    [(set (mem:V4HI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:V4HI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2399)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zstdhu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstdhx"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2400)]
    "TARGET_LSP"
    "zstdhx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstdhmx"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2401)]
    "TARGET_LSP"
    "zstdhmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstdw"
    [(set (mem:V2SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:V2SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2402)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zstdw %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstdwu"
    [(set (mem:V2SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:V2SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2403)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zstdwu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstdwx"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2404)]
    "TARGET_LSP"
    "zstdwx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstdwmx"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2405)]
    "TARGET_LSP"
    "zstdwmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsthe"
    [(set (mem:HI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:HI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2406)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zsthe %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstheu"
    [(set (mem:HI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:HI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2407)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zstheu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsthex"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2408)]
    "TARGET_LSP"
    "zsthex %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsthemx"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2409)]
    "TARGET_LSP"
    "zsthemx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstho"
    [(set (mem:HI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:HI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2410)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zstho %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsthou"
    [(set (mem:HI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:HI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2411)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zsthou %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsthox"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2412)]
    "TARGET_LSP"
    "zsthox %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zsthomx"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2413)]
    "TARGET_LSP"
    "zsthomx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstwh"
    [(set (mem:DI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:DI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2414)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zstwh %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstwhu"
    [(set (mem:DI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:DI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2415)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zstwhu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstwhx"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2416)]
    "TARGET_LSP"
    "zstwhx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstwhmx"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2417)]
    "TARGET_LSP"
    "zstwhmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstwhed"
    [(set (mem:DI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:DI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2418)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zstwhed %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstwhedu"
    [(set (mem:DI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:DI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2419)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zstwhedu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstwhedx"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2420)]
    "TARGET_LSP"
    "zstwhedx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstwhedmx"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2421)]
    "TARGET_LSP"
    "zstwhedmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstwhod"
    [(set (mem:DI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:DI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2422)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zstwhod %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstwhodu"
    [(set (mem:DI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:DI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2423)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zstwhodu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstwhodx"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2424)]
    "TARGET_LSP"
    "zstwhodx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstwhodmx"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2425)]
    "TARGET_LSP"
    "zstwhodmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstww"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2426)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zstww %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstwwu"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:QI 1 "immediate_operand" "i")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2427)]
    "TARGET_LSP && INTVAL (operands[1]) >= 0 && INTVAL (operands[1]) <= 31"
    "zstwwu %0, %2(%1)"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstwwx"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2428)]
    "TARGET_LSP"
    "zstwwx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zstwwmx"
    [(set (mem:SI (plus:SI (match_operand:SI 0 "gpc_reg_operand" "b")
      (match_operand:SI 1 "gpc_reg_operand" "r")))
      (match_operand:SI 2 "gpc_reg_operand" "r"))
      (unspec [(const_int 0)] 2429)]
    "TARGET_LSP"
    "zstwwmx %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhegsi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2431))]
    "TARGET_LSP"
    "zmhegsi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhegsmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2432))]
    "TARGET_LSP"
    "zmhegsmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhegsui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2433))]
    "TARGET_LSP"
    "zmhegsui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhegui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2434))]
    "TARGET_LSP"
    "zmhegui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheogsi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2435))]
    "TARGET_LSP"
    "zmheogsi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheogsmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2436))]
    "TARGET_LSP"
    "zmheogsmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheogsui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2437))]
    "TARGET_LSP"
    "zmheogsui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheogui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2438))]
    "TARGET_LSP"
    "zmheogui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhogsi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2439))]
    "TARGET_LSP"
    "zmhogsi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhogsmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2440))]
    "TARGET_LSP"
    "zmhogsmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhogsui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2441))]
    "TARGET_LSP"
    "zmhogsui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhogui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2442))]
    "TARGET_LSP"
    "zmhogui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhegsiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2443))]
    "TARGET_LSP"
    "zmhegsiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhegsmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2444))]
    "TARGET_LSP"
    "zmhegsmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhegsuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2445))]
    "TARGET_LSP"
    "zmhegsuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheguiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2446))]
    "TARGET_LSP"
    "zmheguiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheogsiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2447))]
    "TARGET_LSP"
    "zmheogsiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheogsmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2448))]
    "TARGET_LSP"
    "zmheogsmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheogsuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2449))]
    "TARGET_LSP"
    "zmheogsuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheoguiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2450))]
    "TARGET_LSP"
    "zmheoguiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhogsiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2451))]
    "TARGET_LSP"
    "zmhogsiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhogsmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2452))]
    "TARGET_LSP"
    "zmhogsmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhogsuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2453))]
    "TARGET_LSP"
    "zmhogsuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhoguiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2454))]
    "TARGET_LSP"
    "zmhoguiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhegsian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2455))]
    "TARGET_LSP"
    "zmhegsian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhegsmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2456))]
    "TARGET_LSP"
    "zmhegsmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhegsuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2457))]
    "TARGET_LSP"
    "zmhegsuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheguian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2458))]
    "TARGET_LSP"
    "zmheguian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheogsian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2459))]
    "TARGET_LSP"
    "zmheogsian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheogsmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2460))]
    "TARGET_LSP"
    "zmheogsmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheogsuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2461))]
    "TARGET_LSP"
    "zmheogsuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheoguian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2462))]
    "TARGET_LSP"
    "zmheoguian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhogsian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2463))]
    "TARGET_LSP"
    "zmhogsian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhogsmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2464))]
    "TARGET_LSP"
    "zmhogsmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhogsuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2465))]
    "TARGET_LSP"
    "zmhogsuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhoguian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2466))]
    "TARGET_LSP"
    "zmhoguian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhegwsmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2467))]
    "TARGET_LSP"
    "zmhegwsmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheogwsmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2468))]
    "TARGET_LSP"
    "zmheogwsmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhogwsmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2469))]
    "TARGET_LSP"
    "zmhogwsmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhegwsmfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2470))]
    "TARGET_LSP"
    "zmhegwsmfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheogwsmfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2471))]
    "TARGET_LSP"
    "zmheogwsmfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhogwsmfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2472))]
    "TARGET_LSP"
    "zmhogwsmfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhegwsmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2473))]
    "TARGET_LSP"
    "zmhegwsmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheogwsmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2474))]
    "TARGET_LSP"
    "zmheogwsmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhogwsmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2475))]
    "TARGET_LSP"
    "zmhogwsmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhegwsmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2476))]
    "TARGET_LSP"
    "zmhegwsmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheogwsmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2477))]
    "TARGET_LSP"
    "zmheogwsmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhogwsmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2478))]
    "TARGET_LSP"
    "zmhogwsmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhegwsmfraa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2479))]
    "TARGET_LSP"
    "zmhegwsmfraa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheogwsmfraa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2480))]
    "TARGET_LSP"
    "zmheogwsmfraa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhogwsmfraa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2481))]
    "TARGET_LSP"
    "zmhogwsmfraa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhegwsmfran"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2482))]
    "TARGET_LSP"
    "zmhegwsmfran %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheogwsmfran"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2483))]
    "TARGET_LSP"
    "zmheogwsmfran %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhogwsmfran"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2484))]
    "TARGET_LSP"
    "zmhogwsmfran %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhesf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2485))]
    "TARGET_LSP"
    "zmhesf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheosf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2486))]
    "TARGET_LSP"
    "zmheosf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhosf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2487))]
    "TARGET_LSP"
    "zmhosf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhesfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2488))]
    "TARGET_LSP"
    "zmhesfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheosfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2489))]
    "TARGET_LSP"
    "zmheosfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhosfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2490))]
    "TARGET_LSP"
    "zmhosfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhesfaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2491))]
    "TARGET_LSP"
    "zmhesfaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheosfaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2492))]
    "TARGET_LSP"
    "zmheosfaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhosfaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2493))]
    "TARGET_LSP"
    "zmhosfaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhesfans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2494))]
    "TARGET_LSP"
    "zmhesfans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheosfans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2495))]
    "TARGET_LSP"
    "zmheosfans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhosfans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2496))]
    "TARGET_LSP"
    "zmhosfans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhesfraas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2497))]
    "TARGET_LSP"
    "zmhesfraas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheosfraas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2498))]
    "TARGET_LSP"
    "zmheosfraas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhosfraas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2499))]
    "TARGET_LSP"
    "zmhosfraas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhesfrans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2500))]
    "TARGET_LSP"
    "zmhesfrans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheosfrans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2501))]
    "TARGET_LSP"
    "zmheosfrans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhosfrans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2502))]
    "TARGET_LSP"
    "zmhosfrans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhesi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2503))]
    "TARGET_LSP"
    "zmhesi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheosi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2504))]
    "TARGET_LSP"
    "zmheosi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhosi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2505))]
    "TARGET_LSP"
    "zmhosi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhesui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2506))]
    "TARGET_LSP"
    "zmhesui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheosui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2507))]
    "TARGET_LSP"
    "zmheosui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhosui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2508))]
    "TARGET_LSP"
    "zmhosui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2509))]
    "TARGET_LSP"
    "zmheui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheoui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2510))]
    "TARGET_LSP"
    "zmheoui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhoui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2511))]
    "TARGET_LSP"
    "zmhoui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhesiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2512))]
    "TARGET_LSP"
    "zmhesiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheosiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2513))]
    "TARGET_LSP"
    "zmheosiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhosiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2514))]
    "TARGET_LSP"
    "zmhosiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhesian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2515))]
    "TARGET_LSP"
    "zmhesian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheosian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2516))]
    "TARGET_LSP"
    "zmheosian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhosian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2517))]
    "TARGET_LSP"
    "zmhosian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhesuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2518))]
    "TARGET_LSP"
    "zmhesuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheosuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2519))]
    "TARGET_LSP"
    "zmheosuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhosuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2520))]
    "TARGET_LSP"
    "zmhosuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhesuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2521))]
    "TARGET_LSP"
    "zmhesuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheosuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2522))]
    "TARGET_LSP"
    "zmheosuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhosuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2523))]
    "TARGET_LSP"
    "zmhosuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2524))]
    "TARGET_LSP"
    "zmheuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheouiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2525))]
    "TARGET_LSP"
    "zmheouiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhouiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2526))]
    "TARGET_LSP"
    "zmhouiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2527))]
    "TARGET_LSP"
    "zmheuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheouian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2528))]
    "TARGET_LSP"
    "zmheouian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhouian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2529))]
    "TARGET_LSP"
    "zmhouian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhesiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2530))]
    "TARGET_LSP"
    "zmhesiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheosiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2531))]
    "TARGET_LSP"
    "zmheosiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhosiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2532))]
    "TARGET_LSP"
    "zmhosiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhesians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2533))]
    "TARGET_LSP"
    "zmhesians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheosians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2534))]
    "TARGET_LSP"
    "zmheosians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhosians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2535))]
    "TARGET_LSP"
    "zmhosians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhesuiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2536))]
    "TARGET_LSP"
    "zmhesuiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheosuiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2537))]
    "TARGET_LSP"
    "zmheosuiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhosuiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2538))]
    "TARGET_LSP"
    "zmhosuiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhesuians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2539))]
    "TARGET_LSP"
    "zmhesuians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheosuians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2540))]
    "TARGET_LSP"
    "zmheosuians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhosuians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2541))]
    "TARGET_LSP"
    "zmhosuians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheuiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2542))]
    "TARGET_LSP"
    "zmheuiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheouiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2543))]
    "TARGET_LSP"
    "zmheouiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhouiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2544))]
    "TARGET_LSP"
    "zmhouiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheuians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2545))]
    "TARGET_LSP"
    "zmheuians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmheouians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2546))]
    "TARGET_LSP"
    "zmheouians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmhouians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2547))]
    "TARGET_LSP"
    "zmhouians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsfh"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2548))]
    "TARGET_LSP"
    "zvmhsfh %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsfrh"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2549))]
    "TARGET_LSP"
    "zvmhsfrh %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsfaahs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2550))]
    "TARGET_LSP"
    "zvmhsfaahs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsfanhs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2551))]
    "TARGET_LSP"
    "zvmhsfanhs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsfraahs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2552))]
    "TARGET_LSP"
    "zvmhsfraahs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsfranhs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2553))]
    "TARGET_LSP"
    "zvmhsfranhs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsih"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2554))]
    "TARGET_LSP"
    "zvmhsih %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsuih"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2555))]
    "TARGET_LSP"
    "zvmhsuih %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuih"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2556))]
    "TARGET_LSP"
    "zvmhuih %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsihs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2557))]
    "TARGET_LSP"
    "zvmhsihs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsuihs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2558))]
    "TARGET_LSP"
    "zvmhsuihs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuihs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2559))]
    "TARGET_LSP"
    "zvmhuihs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsiaah"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2560))]
    "TARGET_LSP"
    "zvmhsiaah %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsuiaah"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2561))]
    "TARGET_LSP"
    "zvmhsuiaah %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuiaah"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2562))]
    "TARGET_LSP"
    "zvmhuiaah %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsianh"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2563))]
    "TARGET_LSP"
    "zvmhsianh %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsuianh"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2564))]
    "TARGET_LSP"
    "zvmhsuianh %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuianh"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2565))]
    "TARGET_LSP"
    "zvmhuianh %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsiaahs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2566))]
    "TARGET_LSP"
    "zvmhsiaahs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsuiaahs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2567))]
    "TARGET_LSP"
    "zvmhsuiaahs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuiaahs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2568))]
    "TARGET_LSP"
    "zvmhuiaahs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsianhs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2569))]
    "TARGET_LSP"
    "zvmhsianhs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhsuianhs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2570))]
    "TARGET_LSP"
    "zvmhsuianhs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuianhs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2571))]
    "TARGET_LSP"
    "zvmhuianhs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgsi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2572))]
    "TARGET_LSP"
    "zmwgsi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgsui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2573))]
    "TARGET_LSP"
    "zmwgsui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2574))]
    "TARGET_LSP"
    "zmwgui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgsiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2575))]
    "TARGET_LSP"
    "zmwgsiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgsian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2576))]
    "TARGET_LSP"
    "zmwgsian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgsuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2577))]
    "TARGET_LSP"
    "zmwgsuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgsuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2578))]
    "TARGET_LSP"
    "zmwgsuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwguiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2579))]
    "TARGET_LSP"
    "zmwguiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwguian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2580))]
    "TARGET_LSP"
    "zmwguian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgsiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2581))]
    "TARGET_LSP"
    "zmwgsiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgsians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2582))]
    "TARGET_LSP"
    "zmwgsians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgsuiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2583))]
    "TARGET_LSP"
    "zmwgsuiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgsuians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2584))]
    "TARGET_LSP"
    "zmwgsuians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwguiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2585))]
    "TARGET_LSP"
    "zmwguiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwguians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2586))]
    "TARGET_LSP"
    "zmwguians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgsmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2587))]
    "TARGET_LSP"
    "zmwgsmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgsmfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2588))]
    "TARGET_LSP"
    "zmwgsmfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgsmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2589))]
    "TARGET_LSP"
    "zmwgsmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgsmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2590))]
    "TARGET_LSP"
    "zmwgsmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgsmfraa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2591))]
    "TARGET_LSP"
    "zmwgsmfraa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwgsmfran"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2592))]
    "TARGET_LSP"
    "zmwgsmfran %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwlsis"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2593))]
    "TARGET_LSP"
    "zmwlsis %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwlsuis"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2594))]
    "TARGET_LSP"
    "zmwlsuis %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwluis"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2595))]
    "TARGET_LSP"
    "zmwluis %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwlsiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2596))]
    "TARGET_LSP"
    "zmwlsiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwlsuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2597))]
    "TARGET_LSP"
    "zmwlsuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwluiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2598))]
    "TARGET_LSP"
    "zmwluiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwlsian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2599))]
    "TARGET_LSP"
    "zmwlsian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwlsuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2600))]
    "TARGET_LSP"
    "zmwlsuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwluian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2601))]
    "TARGET_LSP"
    "zmwluian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwlsiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2602))]
    "TARGET_LSP"
    "zmwlsiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwlsians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2603))]
    "TARGET_LSP"
    "zmwlsians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwlsuiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2604))]
    "TARGET_LSP"
    "zmwlsuiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwlsuians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2605))]
    "TARGET_LSP"
    "zmwlsuians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwluiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2606))]
    "TARGET_LSP"
    "zmwluiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwluians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2607))]
    "TARGET_LSP"
    "zmwluians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwsf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2608))]
    "TARGET_LSP"
    "zmwsf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwsfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2609))]
    "TARGET_LSP"
    "zmwsfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwsfaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2610))]
    "TARGET_LSP"
    "zmwsfaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwsfans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2611))]
    "TARGET_LSP"
    "zmwsfans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwsfraas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2612))]
    "TARGET_LSP"
    "zmwsfraas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zmwsfrans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2613))]
    "TARGET_LSP"
    "zmwsfrans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulgwsmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2614))]
    "TARGET_LSP"
    "zvmhulgwsmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllgwsmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2615))]
    "TARGET_LSP"
    "zvmhllgwsmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuugwsmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2616))]
    "TARGET_LSP"
    "zvmhuugwsmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlgwsmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2617))]
    "TARGET_LSP"
    "zvmhxlgwsmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulgwsmfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2618))]
    "TARGET_LSP"
    "zvmhulgwsmfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllgwsmfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2619))]
    "TARGET_LSP"
    "zvmhllgwsmfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuugwsmfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2620))]
    "TARGET_LSP"
    "zvmhuugwsmfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlgwsmfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2621))]
    "TARGET_LSP"
    "zvmhxlgwsmfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulgwsmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2622))]
    "TARGET_LSP"
    "zvmhulgwsmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllgwsmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2623))]
    "TARGET_LSP"
    "zvmhllgwsmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuugwsmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2624))]
    "TARGET_LSP"
    "zvmhuugwsmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlgwsmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2625))]
    "TARGET_LSP"
    "zvmhxlgwsmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulgwsmfraa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2626))]
    "TARGET_LSP"
    "zvmhulgwsmfraa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllgwsmfraa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2627))]
    "TARGET_LSP"
    "zvmhllgwsmfraa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuugwsmfraa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2628))]
    "TARGET_LSP"
    "zvmhuugwsmfraa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlgwsmfraa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2629))]
    "TARGET_LSP"
    "zvmhxlgwsmfraa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulgwsmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2630))]
    "TARGET_LSP"
    "zvmhulgwsmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllgwsmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2631))]
    "TARGET_LSP"
    "zvmhllgwsmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuugwsmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2632))]
    "TARGET_LSP"
    "zvmhuugwsmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlgwsmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2633))]
    "TARGET_LSP"
    "zvmhxlgwsmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulgwsmfran"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2634))]
    "TARGET_LSP"
    "zvmhulgwsmfran %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllgwsmfran"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2635))]
    "TARGET_LSP"
    "zvmhllgwsmfran %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuugwsmfran"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2636))]
    "TARGET_LSP"
    "zvmhuugwsmfran %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlgwsmfran"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2637))]
    "TARGET_LSP"
    "zvmhxlgwsmfran %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulgwsmfanp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2638))]
    "TARGET_LSP"
    "zvmhulgwsmfanp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllgwsmfanp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2639))]
    "TARGET_LSP"
    "zvmhllgwsmfanp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuugwsmfanp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2640))]
    "TARGET_LSP"
    "zvmhuugwsmfanp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlgwsmfanp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2641))]
    "TARGET_LSP"
    "zvmhxlgwsmfanp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulgwsmfranp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2642))]
    "TARGET_LSP"
    "zvmhulgwsmfranp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllgwsmfranp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2643))]
    "TARGET_LSP"
    "zvmhllgwsmfranp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuugwsmfranp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2644))]
    "TARGET_LSP"
    "zvmhuugwsmfranp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlgwsmfranp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2645))]
    "TARGET_LSP"
    "zvmhxlgwsmfranp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2646))]
    "TARGET_LSP"
    "zvmhulsf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2647))]
    "TARGET_LSP"
    "zvmhllsf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2648))]
    "TARGET_LSP"
    "zvmhuusf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2649))]
    "TARGET_LSP"
    "zvmhxlsf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2650))]
    "TARGET_LSP"
    "zvmhulsfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2651))]
    "TARGET_LSP"
    "zvmhllsfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2652))]
    "TARGET_LSP"
    "zvmhuusfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2653))]
    "TARGET_LSP"
    "zvmhxlsfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsfaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2654))]
    "TARGET_LSP"
    "zvmhulsfaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsfaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2655))]
    "TARGET_LSP"
    "zvmhllsfaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusfaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2656))]
    "TARGET_LSP"
    "zvmhuusfaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsfaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2657))]
    "TARGET_LSP"
    "zvmhxlsfaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsfans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2658))]
    "TARGET_LSP"
    "zvmhulsfans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsfans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2659))]
    "TARGET_LSP"
    "zvmhllsfans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusfans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2660))]
    "TARGET_LSP"
    "zvmhuusfans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsfans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2661))]
    "TARGET_LSP"
    "zvmhxlsfans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsfanps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2662))]
    "TARGET_LSP"
    "zvmhulsfanps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsfanps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2663))]
    "TARGET_LSP"
    "zvmhllsfanps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusfanps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2664))]
    "TARGET_LSP"
    "zvmhuusfanps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsfanps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:SI 1 "gpc_reg_operand" "r")
     				(match_operand:SI 2 "gpc_reg_operand" "r")] 2665))]
    "TARGET_LSP"
    "zvmhxlsfanps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsfraas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2666))]
    "TARGET_LSP"
    "zvmhulsfraas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsfraas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2667))]
    "TARGET_LSP"
    "zvmhllsfraas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusfraas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2668))]
    "TARGET_LSP"
    "zvmhuusfraas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsfraas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2669))]
    "TARGET_LSP"
    "zvmhxlsfraas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsfrans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2670))]
    "TARGET_LSP"
    "zvmhulsfrans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsfrans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2671))]
    "TARGET_LSP"
    "zvmhllsfrans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusfrans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2672))]
    "TARGET_LSP"
    "zvmhuusfrans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsfrans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2673))]
    "TARGET_LSP"
    "zvmhxlsfrans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsfranps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2674))]
    "TARGET_LSP"
    "zvmhulsfranps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsfranps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2675))]
    "TARGET_LSP"
    "zvmhllsfranps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusfranps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2676))]
    "TARGET_LSP"
    "zvmhuusfranps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsfranps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2677))]
    "TARGET_LSP"
    "zvmhxlsfranps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2678))]
    "TARGET_LSP"
    "zvmhulsi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2679))]
    "TARGET_LSP"
    "zvmhllsi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2680))]
    "TARGET_LSP"
    "zvmhuusi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2681))]
    "TARGET_LSP"
    "zvmhxlsi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2682))]
    "TARGET_LSP"
    "zvmhulsui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2683))]
    "TARGET_LSP"
    "zvmhllsui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2684))]
    "TARGET_LSP"
    "zvmhuusui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2685))]
    "TARGET_LSP"
    "zvmhxlsui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhului"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2686))]
    "TARGET_LSP"
    "zvmhului %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2687))]
    "TARGET_LSP"
    "zvmhllui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuuui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2688))]
    "TARGET_LSP"
    "zvmhuuui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2689))]
    "TARGET_LSP"
    "zvmhxlui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2690))]
    "TARGET_LSP"
    "zvmhulsiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2691))]
    "TARGET_LSP"
    "zvmhllsiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2692))]
    "TARGET_LSP"
    "zvmhuusiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2693))]
    "TARGET_LSP"
    "zvmhxlsiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2694))]
    "TARGET_LSP"
    "zvmhulsian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2695))]
    "TARGET_LSP"
    "zvmhllsian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2696))]
    "TARGET_LSP"
    "zvmhuusian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2697))]
    "TARGET_LSP"
    "zvmhxlsian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsianp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2698))]
    "TARGET_LSP"
    "zvmhulsianp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsianp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2699))]
    "TARGET_LSP"
    "zvmhllsianp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusianp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2700))]
    "TARGET_LSP"
    "zvmhuusianp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsianp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2701))]
    "TARGET_LSP"
    "zvmhxlsianp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2702))]
    "TARGET_LSP"
    "zvmhulsuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2703))]
    "TARGET_LSP"
    "zvmhllsuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2704))]
    "TARGET_LSP"
    "zvmhuusuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2705))]
    "TARGET_LSP"
    "zvmhxlsuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2706))]
    "TARGET_LSP"
    "zvmhulsuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2707))]
    "TARGET_LSP"
    "zvmhllsuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2708))]
    "TARGET_LSP"
    "zvmhuusuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2709))]
    "TARGET_LSP"
    "zvmhxlsuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsuianp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2710))]
    "TARGET_LSP"
    "zvmhulsuianp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsuianp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2711))]
    "TARGET_LSP"
    "zvmhllsuianp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusuianp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2712))]
    "TARGET_LSP"
    "zvmhuusuianp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsuianp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2713))]
    "TARGET_LSP"
    "zvmhxlsuianp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuluiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2714))]
    "TARGET_LSP"
    "zvmhuluiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhlluiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2715))]
    "TARGET_LSP"
    "zvmhlluiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuuuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2716))]
    "TARGET_LSP"
    "zvmhuuuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxluiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2717))]
    "TARGET_LSP"
    "zvmhxluiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuluian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2718))]
    "TARGET_LSP"
    "zvmhuluian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhlluian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2719))]
    "TARGET_LSP"
    "zvmhlluian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuuuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2720))]
    "TARGET_LSP"
    "zvmhuuuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxluian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2721))]
    "TARGET_LSP"
    "zvmhxluian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuluianp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2722))]
    "TARGET_LSP"
    "zvmhuluianp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhlluianp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2723))]
    "TARGET_LSP"
    "zvmhlluianp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuuuianp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2724))]
    "TARGET_LSP"
    "zvmhuuuianp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxluianp"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2725))]
    "TARGET_LSP"
    "zvmhxluianp %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2726))]
    "TARGET_LSP"
    "zvmhulsiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2727))]
    "TARGET_LSP"
    "zvmhllsiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2728))]
    "TARGET_LSP"
    "zvmhuusiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2729))]
    "TARGET_LSP"
    "zvmhxlsiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2730))]
    "TARGET_LSP"
    "zvmhulsians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2731))]
    "TARGET_LSP"
    "zvmhllsians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2732))]
    "TARGET_LSP"
    "zvmhuusians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2733))]
    "TARGET_LSP"
    "zvmhxlsians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsianps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2734))]
    "TARGET_LSP"
    "zvmhulsianps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsianps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2735))]
    "TARGET_LSP"
    "zvmhllsianps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusianps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2736))]
    "TARGET_LSP"
    "zvmhuusianps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsianps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2737))]
    "TARGET_LSP"
    "zvmhxlsianps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsuiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2738))]
    "TARGET_LSP"
    "zvmhulsuiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsuiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2739))]
    "TARGET_LSP"
    "zvmhllsuiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusuiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2740))]
    "TARGET_LSP"
    "zvmhuusuiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsuiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2741))]
    "TARGET_LSP"
    "zvmhxlsuiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsuians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2742))]
    "TARGET_LSP"
    "zvmhulsuians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsuians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2743))]
    "TARGET_LSP"
    "zvmhllsuians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusuians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2744))]
    "TARGET_LSP"
    "zvmhuusuians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsuians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2745))]
    "TARGET_LSP"
    "zvmhxlsuians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhulsuianps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2746))]
    "TARGET_LSP"
    "zvmhulsuianps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhllsuianps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2747))]
    "TARGET_LSP"
    "zvmhllsuianps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuusuianps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2748))]
    "TARGET_LSP"
    "zvmhuusuianps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxlsuianps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2749))]
    "TARGET_LSP"
    "zvmhxlsuianps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuluiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2750))]
    "TARGET_LSP"
    "zvmhuluiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhlluiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2751))]
    "TARGET_LSP"
    "zvmhlluiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuuuiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2752))]
    "TARGET_LSP"
    "zvmhuuuiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxluiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2753))]
    "TARGET_LSP"
    "zvmhxluiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuluians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2754))]
    "TARGET_LSP"
    "zvmhuluians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhlluians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2755))]
    "TARGET_LSP"
    "zvmhlluians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuuuians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2756))]
    "TARGET_LSP"
    "zvmhuuuians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxluians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2757))]
    "TARGET_LSP"
    "zvmhxluians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuluianps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2758))]
    "TARGET_LSP"
    "zvmhuluianps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhlluianps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2759))]
    "TARGET_LSP"
    "zvmhlluianps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhuuuianps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2760))]
    "TARGET_LSP"
    "zvmhuuuianps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvmhxluianps"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2761))]
    "TARGET_LSP"
    "zvmhxluianps %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgaui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2762))]
    "TARGET_LSP"
    "zvdotphgaui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgaui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2763))]
    "TARGET_LSP"
    "zvdotphxgaui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgasi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2764))]
    "TARGET_LSP"
    "zvdotphgasi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgasi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2765))]
    "TARGET_LSP"
    "zvdotphxgasi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgasui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2766))]
    "TARGET_LSP"
    "zvdotphgasui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgasui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2767))]
    "TARGET_LSP"
    "zvdotphxgasui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgasmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2768))]
    "TARGET_LSP"
    "zvdotphgasmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgasmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2769))]
    "TARGET_LSP"
    "zvdotphxgasmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgauiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2770))]
    "TARGET_LSP"
    "zvdotphgauiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgauiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2771))]
    "TARGET_LSP"
    "zvdotphxgauiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgasiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2772))]
    "TARGET_LSP"
    "zvdotphgasiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgasiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2773))]
    "TARGET_LSP"
    "zvdotphxgasiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgasuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2774))]
    "TARGET_LSP"
    "zvdotphgasuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgasuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2775))]
    "TARGET_LSP"
    "zvdotphxgasuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgasmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2776))]
    "TARGET_LSP"
    "zvdotphgasmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgasmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2777))]
    "TARGET_LSP"
    "zvdotphxgasmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgauian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2778))]
    "TARGET_LSP"
    "zvdotphgauian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgauian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2779))]
    "TARGET_LSP"
    "zvdotphxgauian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgasian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2780))]
    "TARGET_LSP"
    "zvdotphgasian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgasian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2781))]
    "TARGET_LSP"
    "zvdotphxgasian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgasuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2782))]
    "TARGET_LSP"
    "zvdotphgasuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgasuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2783))]
    "TARGET_LSP"
    "zvdotphxgasuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgasmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2784))]
    "TARGET_LSP"
    "zvdotphgasmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgasmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2785))]
    "TARGET_LSP"
    "zvdotphxgasmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgsui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2786))]
    "TARGET_LSP"
    "zvdotphgsui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgssi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2787))]
    "TARGET_LSP"
    "zvdotphgssi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgssui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2788))]
    "TARGET_LSP"
    "zvdotphgssui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgssmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2789))]
    "TARGET_LSP"
    "zvdotphgssmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgsuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2790))]
    "TARGET_LSP"
    "zvdotphgsuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgssiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2791))]
    "TARGET_LSP"
    "zvdotphgssiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgssuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2792))]
    "TARGET_LSP"
    "zvdotphgssuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgssmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2793))]
    "TARGET_LSP"
    "zvdotphgssmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgsuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2794))]
    "TARGET_LSP"
    "zvdotphgsuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgssian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2795))]
    "TARGET_LSP"
    "zvdotphgssian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgssuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2796))]
    "TARGET_LSP"
    "zvdotphgssuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgssmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2797))]
    "TARGET_LSP"
    "zvdotphgssmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasfs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2798))]
    "TARGET_LSP"
    "zvdotphasfs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasfs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2799))]
    "TARGET_LSP"
    "zvdotphxasfs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasfrs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2800))]
    "TARGET_LSP"
    "zvdotphasfrs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasfrs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2801))]
    "TARGET_LSP"
    "zvdotphxasfrs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasfaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2802))]
    "TARGET_LSP"
    "zvdotphasfaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasfaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2803))]
    "TARGET_LSP"
    "zvdotphxasfaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasfans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2804))]
    "TARGET_LSP"
    "zvdotphasfans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasfans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2805))]
    "TARGET_LSP"
    "zvdotphxasfans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasfraas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2806))]
    "TARGET_LSP"
    "zvdotphasfraas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasfraas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2807))]
    "TARGET_LSP"
    "zvdotphxasfraas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasfrans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2808))]
    "TARGET_LSP"
    "zvdotphasfrans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasfrans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2809))]
    "TARGET_LSP"
    "zvdotphxasfrans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphaui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2810))]
    "TARGET_LSP"
    "zvdotphaui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxaui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2811))]
    "TARGET_LSP"
    "zvdotphxaui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2812))]
    "TARGET_LSP"
    "zvdotphasi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2813))]
    "TARGET_LSP"
    "zvdotphxasi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2814))]
    "TARGET_LSP"
    "zvdotphasui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2815))]
    "TARGET_LSP"
    "zvdotphxasui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphauiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2816))]
    "TARGET_LSP"
    "zvdotphauiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxauiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2817))]
    "TARGET_LSP"
    "zvdotphxauiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2818))]
    "TARGET_LSP"
    "zvdotphasiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2819))]
    "TARGET_LSP"
    "zvdotphxasiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2820))]
    "TARGET_LSP"
    "zvdotphasuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2821))]
    "TARGET_LSP"
    "zvdotphxasuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphauian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2822))]
    "TARGET_LSP"
    "zvdotphauian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxauian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2823))]
    "TARGET_LSP"
    "zvdotphxauian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2824))]
    "TARGET_LSP"
    "zvdotphasian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2825))]
    "TARGET_LSP"
    "zvdotphxasian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2826))]
    "TARGET_LSP"
    "zvdotphasuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2827))]
    "TARGET_LSP"
    "zvdotphxasuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphauis"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2828))]
    "TARGET_LSP"
    "zvdotphauis %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxauis"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2829))]
    "TARGET_LSP"
    "zvdotphxauis %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasis"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2830))]
    "TARGET_LSP"
    "zvdotphasis %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasis"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2831))]
    "TARGET_LSP"
    "zvdotphxasis %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasuis"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2832))]
    "TARGET_LSP"
    "zvdotphasuis %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasuis"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2833))]
    "TARGET_LSP"
    "zvdotphxasuis %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphauiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2834))]
    "TARGET_LSP"
    "zvdotphauiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxauiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2835))]
    "TARGET_LSP"
    "zvdotphxauiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2836))]
    "TARGET_LSP"
    "zvdotphasiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2837))]
    "TARGET_LSP"
    "zvdotphxasiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasuiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2838))]
    "TARGET_LSP"
    "zvdotphasuiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasuiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2839))]
    "TARGET_LSP"
    "zvdotphxasuiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphauians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2840))]
    "TARGET_LSP"
    "zvdotphauians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxauians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2841))]
    "TARGET_LSP"
    "zvdotphxauians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2842))]
    "TARGET_LSP"
    "zvdotphasians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2843))]
    "TARGET_LSP"
    "zvdotphxasians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphasuians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2844))]
    "TARGET_LSP"
    "zvdotphasuians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxasuians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2845))]
    "TARGET_LSP"
    "zvdotphxasuians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssfs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2846))]
    "TARGET_LSP"
    "zvdotphssfs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssfrs"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2847))]
    "TARGET_LSP"
    "zvdotphssfrs %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssfaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2848))]
    "TARGET_LSP"
    "zvdotphssfaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssfans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2849))]
    "TARGET_LSP"
    "zvdotphssfans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssfraas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2850))]
    "TARGET_LSP"
    "zvdotphssfraas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssfrans"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2851))]
    "TARGET_LSP"
    "zvdotphssfrans %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphsui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2852))]
    "TARGET_LSP"
    "zvdotphsui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssi"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2853))]
    "TARGET_LSP"
    "zvdotphssi %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssui"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2854))]
    "TARGET_LSP"
    "zvdotphssui %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphsuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2855))]
    "TARGET_LSP"
    "zvdotphsuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2856))]
    "TARGET_LSP"
    "zvdotphssiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssuiaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2857))]
    "TARGET_LSP"
    "zvdotphssuiaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphsuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2858))]
    "TARGET_LSP"
    "zvdotphsuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2859))]
    "TARGET_LSP"
    "zvdotphssian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssuian"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2860))]
    "TARGET_LSP"
    "zvdotphssuian %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphsuis"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2861))]
    "TARGET_LSP"
    "zvdotphsuis %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssis"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2862))]
    "TARGET_LSP"
    "zvdotphssis %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssuis"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2863))]
    "TARGET_LSP"
    "zvdotphssuis %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphsuiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2864))]
    "TARGET_LSP"
    "zvdotphsuiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2865))]
    "TARGET_LSP"
    "zvdotphssiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssuiaas"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2866))]
    "TARGET_LSP"
    "zvdotphssuiaas %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphsuians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2867))]
    "TARGET_LSP"
    "zvdotphsuians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2868))]
    "TARGET_LSP"
    "zvdotphssians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphssuians"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2869))]
    "TARGET_LSP"
    "zvdotphssuians %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgwasmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2870))]
    "TARGET_LSP"
    "zvdotphgwasmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgwasmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2871))]
    "TARGET_LSP"
    "zvdotphxgwasmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgwasmfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2872))]
    "TARGET_LSP"
    "zvdotphgwasmfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgwasmfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2873))]
    "TARGET_LSP"
    "zvdotphxgwasmfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgwasmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2874))]
    "TARGET_LSP"
    "zvdotphgwasmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgwasmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2875))]
    "TARGET_LSP"
    "zvdotphxgwasmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgwasmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2876))]
    "TARGET_LSP"
    "zvdotphgwasmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgwasmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2877))]
    "TARGET_LSP"
    "zvdotphxgwasmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgwasmfraa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2878))]
    "TARGET_LSP"
    "zvdotphgwasmfraa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgwasmfraa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2879))]
    "TARGET_LSP"
    "zvdotphxgwasmfraa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgwasmfran"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2880))]
    "TARGET_LSP"
    "zvdotphgwasmfran %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphxgwasmfran"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2881))]
    "TARGET_LSP"
    "zvdotphxgwasmfran %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgwssmf"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2882))]
    "TARGET_LSP"
    "zvdotphgwssmf %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgwssmfr"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2883))]
    "TARGET_LSP"
    "zvdotphgwssmfr %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgwssmfaa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2884))]
    "TARGET_LSP"
    "zvdotphgwssmfaa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgwssmfan"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2885))]
    "TARGET_LSP"
    "zvdotphgwssmfan %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgwssmfraa"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2886))]
    "TARGET_LSP"
    "zvdotphgwssmfraa %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])

(define_insn "lsp_zvdotphgwssmfran"
    [(set (match_operand:DI 0 "gpc_reg_operand" "=r")
     (unspec:DI [(match_operand:V2SI 1 "gpc_reg_operand" "r")
     (match_operand:DI 2 "gpc_reg_operand" "r")] 2887))]
    "TARGET_LSP"
    "zvdotphgwssmfran %0, %1, %2"
    [(set_attr "type" "vecsimple")
     (set_attr "length" "4")])


