/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "lvtlxl" 37 } } */

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

vsc  lc2(long a, void *p)           { return __builtin_altivec_lvtlxl (a,p); }
vsf  llxl01(long a, vsf *p)         { return __builtin_vec_lvtlxl (a,p); }
vsf  llxl02(long a, sf *p)          { return __builtin_vec_lvtlxl (a,p); }
vbi  llxl03(long a, vbi *p)         { return __builtin_vec_lvtlxl (a,p); }
vsi  llxl04(long a, vsi *p)         { return __builtin_vec_lvtlxl (a,p); }
vsi  llxl05(long a, si *p)          { return __builtin_vec_lvtlxl (a,p); }
vui  llxl06(long a, vui *p)         { return __builtin_vec_lvtlxl (a,p); }
vui  llxl07(long a, ui *p)          { return __builtin_vec_lvtlxl (a,p); }
vbs  llxl08(long a, vbs *p)         { return __builtin_vec_lvtlxl (a,p); }
vp   llxl09(long a, vp *p)          { return __builtin_vec_lvtlxl (a,p); }
vss  llxl10(long a, vss *p)         { return __builtin_vec_lvtlxl (a,p); }
vss  llxl11(long a, ss *p)          { return __builtin_vec_lvtlxl (a,p); }
vus  llxl12(long a, vus *p)         { return __builtin_vec_lvtlxl (a,p); }
vus  llxl13(long a, us *p)          { return __builtin_vec_lvtlxl (a,p); }
vbc  llxl14(long a, vbc *p)         { return __builtin_vec_lvtlxl (a,p); }
vsc  llxl15(long a, vsc *p)         { return __builtin_vec_lvtlxl (a,p); }
vsc  llxl16(long a, sc *p)          { return __builtin_vec_lvtlxl (a,p); }
vuc  llxl17(long a, vuc *p)         { return __builtin_vec_lvtlxl (a,p); }
vuc  llxl18(long a, uc *p)          { return __builtin_vec_lvtlxl (a,p); }
vsf  Dllxl01(long a, vsf *p)        { return vec_lvtlxl (a,p); }
vsf  Dllxl02(long a, sf *p)         { return vec_lvtlxl (a,p); }
vbi  Dllxl03(long a, vbi *p)        { return vec_lvtlxl (a,p); }
vsi  Dllxl04(long a, vsi *p)        { return vec_lvtlxl (a,p); }
vsi  Dllxl05(long a, si *p)         { return vec_lvtlxl (a,p); }
vui  Dllxl06(long a, vui *p)        { return vec_lvtlxl (a,p); }
vui  Dllxl07(long a, ui *p)         { return vec_lvtlxl (a,p); }
vbs  Dllxl08(long a, vbs *p)        { return vec_lvtlxl (a,p); }
vp   Dllxl09(long a, vp *p)         { return vec_lvtlxl (a,p); }
vss  Dllxl10(long a, vss *p)        { return vec_lvtlxl (a,p); }
vss  Dllxl11(long a, ss *p)         { return vec_lvtlxl (a,p); }
vus  Dllxl12(long a, vus *p)        { return vec_lvtlxl (a,p); }
vus  Dllxl13(long a, us *p)         { return vec_lvtlxl (a,p); }
vbc  Dllxl14(long a, vbc *p)        { return vec_lvtlxl (a,p); }
vsc  Dllxl15(long a, vsc *p)        { return vec_lvtlxl (a,p); }
vsc  Dllxl16(long a, sc *p)         { return vec_lvtlxl (a,p); }
vuc  Dllxl17(long a, vuc *p)        { return vec_lvtlxl (a,p); }
vuc  Dllxl18(long a, uc *p)         { return vec_lvtlxl (a,p); }
