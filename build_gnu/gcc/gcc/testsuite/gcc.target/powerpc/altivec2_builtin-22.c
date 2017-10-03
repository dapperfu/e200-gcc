/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "lvsm" 37 } } */

#include <altivec.h>

typedef __vector signed char vsc;
typedef __vector signed short vss;
typedef __vector signed int vsi;
typedef __vector unsigned char vuc;
typedef __vector unsigned short vus;
typedef __vector unsigned int vui;
typedef __vector bool char vbc;
typedef __vector bool short vbs;
typedef __vector bool int vbi;
typedef __vector float vsf;
typedef __vector pixel vp;
typedef signed char sc;
typedef signed short ss;
typedef signed int si;
typedef signed long sl;
typedef unsigned char uc;
typedef unsigned short us;
typedef unsigned int ui;
typedef unsigned long ul;
typedef float sf;

vsc  lsm(long a, void *p)           { return __builtin_altivec_lvsm (a,p); }
vsf  lm01(long a, vsf *p)           { return __builtin_vec_lvsm (a,p); }
vsf  lm02(long a, sf *p)            { return __builtin_vec_lvsm (a,p); }
vbi  lm03(long a, vbi *p)           { return __builtin_vec_lvsm (a,p); }
vsi  lm04(long a, vsi *p)           { return __builtin_vec_lvsm (a,p); }
vsi  lm05(long a, si *p)            { return __builtin_vec_lvsm (a,p); }
vui  lm06(long a, vui *p)           { return __builtin_vec_lvsm (a,p); }
vui  lm07(long a, ui *p)            { return __builtin_vec_lvsm (a,p); }
vbs  lm08(long a, vbs *p)           { return __builtin_vec_lvsm (a,p); }
vp   lm09(long a, vp *p)            { return __builtin_vec_lvsm (a,p); }
vss  lm10(long a, vss *p)           { return __builtin_vec_lvsm (a,p); }
vss  lm11(long a, ss *p)            { return __builtin_vec_lvsm (a,p); }
vus  lm12(long a, vus *p)           { return __builtin_vec_lvsm (a,p); }
vus  lm13(long a, us *p)            { return __builtin_vec_lvsm (a,p); }
vbc  lm14(long a, vbc *p)           { return __builtin_vec_lvsm (a,p); }
vsc  lm15(long a, vsc *p)           { return __builtin_vec_lvsm (a,p); }
vsc  lm16(long a, sc *p)            { return __builtin_vec_lvsm (a,p); }
vuc  lm17(long a, vuc *p)           { return __builtin_vec_lvsm (a,p); }
vuc  lm18(long a, uc *p)            { return __builtin_vec_lvsm (a,p); }
vsf  Dlm01(long a, vsf *p)          { return vec_lvsm (a,p); }
vsf  Dlm02(long a, sf *p)           { return vec_lvsm (a,p); }
vbi  Dlm03(long a, vbi *p)          { return vec_lvsm (a,p); }
vsi  Dlm04(long a, vsi *p)          { return vec_lvsm (a,p); }
vsi  Dlm05(long a, si *p)           { return vec_lvsm (a,p); }
vui  Dlm06(long a, vui *p)          { return vec_lvsm (a,p); }
vui  Dlm07(long a, ui *p)           { return vec_lvsm (a,p); }
vbs  Dlm08(long a, vbs *p)          { return vec_lvsm (a,p); }
vp   Dlm09(long a, vp *p)           { return vec_lvsm (a,p); }
vss  Dlm10(long a, vss *p)          { return vec_lvsm (a,p); }
vss  Dlm11(long a, ss *p)           { return vec_lvsm (a,p); }
vus  Dlm12(long a, vus *p)          { return vec_lvsm (a,p); }
vus  Dlm13(long a, us *p)           { return vec_lvsm (a,p); }
vbc  Dlm14(long a, vbc *p)          { return vec_lvsm (a,p); }
vsc  Dlm15(long a, vsc *p)          { return vec_lvsm (a,p); }
vsc  Dlm16(long a, sc *p)           { return vec_lvsm (a,p); }
vuc  Dlm17(long a, vuc *p)          { return vec_lvsm (a,p); }
vuc  Dlm18(long a, uc *p)           { return vec_lvsm (a,p); }
