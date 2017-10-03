/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "lvtlx" 37 } } */

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

vsc  lc1(long a, void *p)           { return __builtin_altivec_lvtlx (a,p); }
vsf  llx01(long a, vsf *p)          { return __builtin_vec_lvtlx (a,p); }
vsf  llx02(long a, sf *p)           { return __builtin_vec_lvtlx (a,p); }
vbi  llx03(long a, vbi *p)          { return __builtin_vec_lvtlx (a,p); }
vsi  llx04(long a, vsi *p)          { return __builtin_vec_lvtlx (a,p); }
vsi  llx05(long a, si *p)           { return __builtin_vec_lvtlx (a,p); }
vui  llx06(long a, vui *p)          { return __builtin_vec_lvtlx (a,p); }
vui  llx07(long a, ui *p)           { return __builtin_vec_lvtlx (a,p); }
vbs  llx08(long a, vbs *p)          { return __builtin_vec_lvtlx (a,p); }
vp   llx09(long a, vp *p)           { return __builtin_vec_lvtlx (a,p); }
vss  llx10(long a, vss *p)          { return __builtin_vec_lvtlx (a,p); }
vss  llx11(long a, ss *p)           { return __builtin_vec_lvtlx (a,p); }
vus  llx12(long a, vus *p)          { return __builtin_vec_lvtlx (a,p); }
vus  llx13(long a, us *p)           { return __builtin_vec_lvtlx (a,p); }
vbc  llx14(long a, vbc *p)          { return __builtin_vec_lvtlx (a,p); }
vsc  llx15(long a, vsc *p)          { return __builtin_vec_lvtlx (a,p); }
vsc  llx16(long a, sc *p)           { return __builtin_vec_lvtlx (a,p); }
vuc  llx17(long a, vuc *p)          { return __builtin_vec_lvtlx (a,p); }
vuc  llx18(long a, uc *p)           { return __builtin_vec_lvtlx (a,p); }
vsf  Dllx01(long a, vsf *p)         { return vec_lvtlx (a,p); }
vsf  Dllx02(long a, sf *p)          { return vec_lvtlx (a,p); }
vbi  Dllx03(long a, vbi *p)         { return vec_lvtlx (a,p); }
vsi  Dllx04(long a, vsi *p)         { return vec_lvtlx (a,p); }
vsi  Dllx05(long a, si *p)          { return vec_lvtlx (a,p); }
vui  Dllx06(long a, vui *p)         { return vec_lvtlx (a,p); }
vui  Dllx07(long a, ui *p)          { return vec_lvtlx (a,p); }
vbs  Dllx08(long a, vbs *p)         { return vec_lvtlx (a,p); }
vp   Dllx09(long a, vp *p)          { return vec_lvtlx (a,p); }
vss  Dllx10(long a, vss *p)         { return vec_lvtlx (a,p); }
vss  Dllx11(long a, ss *p)          { return vec_lvtlx (a,p); }
vus  Dllx12(long a, vus *p)         { return vec_lvtlx (a,p); }
vus  Dllx13(long a, us *p)          { return vec_lvtlx (a,p); }
vbc  Dllx14(long a, vbc *p)         { return vec_lvtlx (a,p); }
vsc  Dllx15(long a, vsc *p)         { return vec_lvtlx (a,p); }
vsc  Dllx16(long a, sc *p)          { return vec_lvtlx (a,p); }
vuc  Dllx17(long a, vuc *p)         { return vec_lvtlx (a,p); }
vuc  Dllx18(long a, uc *p)          { return vec_lvtlx (a,p); }
