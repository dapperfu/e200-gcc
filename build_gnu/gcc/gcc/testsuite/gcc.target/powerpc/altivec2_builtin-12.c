/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "lvtrx" 37 } } */

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

vsc  lc3(long a, void *p)           { return __builtin_altivec_lvtrx (a,p); }
vsf  lrx01(long a, vsf *p)          { return __builtin_vec_lvtrx (a,p); }
vsf  lrx02(long a, sf *p)           { return __builtin_vec_lvtrx (a,p); }
vbi  lrx03(long a, vbi *p)          { return __builtin_vec_lvtrx (a,p); }
vsi  lrx04(long a, vsi *p)          { return __builtin_vec_lvtrx (a,p); }
vsi  lrx05(long a, si *p)           { return __builtin_vec_lvtrx (a,p); }
vui  lrx06(long a, vui *p)          { return __builtin_vec_lvtrx (a,p); }
vui  lrx07(long a, ui *p)           { return __builtin_vec_lvtrx (a,p); }
vbs  lrx08(long a, vbs *p)          { return __builtin_vec_lvtrx (a,p); }
vp   lrx09(long a, vp *p)           { return __builtin_vec_lvtrx (a,p); }
vss  lrx10(long a, vss *p)          { return __builtin_vec_lvtrx (a,p); }
vss  lrx11(long a, ss *p)           { return __builtin_vec_lvtrx (a,p); }
vus  lrx12(long a, vus *p)          { return __builtin_vec_lvtrx (a,p); }
vus  lrx13(long a, us *p)           { return __builtin_vec_lvtrx (a,p); }
vbc  lrx14(long a, vbc *p)          { return __builtin_vec_lvtrx (a,p); }
vsc  lrx15(long a, vsc *p)          { return __builtin_vec_lvtrx (a,p); }
vsc  lrx16(long a, sc *p)           { return __builtin_vec_lvtrx (a,p); }
vuc  lrx17(long a, vuc *p)          { return __builtin_vec_lvtrx (a,p); }
vuc  lrx18(long a, uc *p)           { return __builtin_vec_lvtrx (a,p); }
vsf  Dlrx01(long a, vsf *p)         { return vec_lvtrx (a,p); }
vsf  Dlrx02(long a, sf *p)          { return vec_lvtrx (a,p); }
vbi  Dlrx03(long a, vbi *p)         { return vec_lvtrx (a,p); }
vsi  Dlrx04(long a, vsi *p)         { return vec_lvtrx (a,p); }
vsi  Dlrx05(long a, si *p)          { return vec_lvtrx (a,p); }
vui  Dlrx06(long a, vui *p)         { return vec_lvtrx (a,p); }
vui  Dlrx07(long a, ui *p)          { return vec_lvtrx (a,p); }
vbs  Dlrx08(long a, vbs *p)         { return vec_lvtrx (a,p); }
vp   Dlrx09(long a, vp *p)          { return vec_lvtrx (a,p); }
vss  Dlrx10(long a, vss *p)         { return vec_lvtrx (a,p); }
vss  Dlrx11(long a, ss *p)          { return vec_lvtrx (a,p); }
vus  Dlrx12(long a, vus *p)         { return vec_lvtrx (a,p); }
vus  Dlrx13(long a, us *p)          { return vec_lvtrx (a,p); }
vbc  Dlrx14(long a, vbc *p)         { return vec_lvtrx (a,p); }
vsc  Dlrx15(long a, vsc *p)         { return vec_lvtrx (a,p); }
vsc  Dlrx16(long a, sc *p)          { return vec_lvtrx (a,p); }
vuc  Dlrx17(long a, vuc *p)         { return vec_lvtrx (a,p); }
vuc  Dlrx18(long a, uc *p)          { return vec_lvtrx (a,p); }
