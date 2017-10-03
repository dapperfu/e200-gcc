/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "lvswx" 37 } } */

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

vsc  ls1(long a, void *p)           { return __builtin_altivec_lvswx (a,p); }
vsf  ls01(long a, vsf *p)           { return __builtin_vec_lvswx (a,p); }
vsf  ls02(long a, sf *p)            { return __builtin_vec_lvswx (a,p); }
vbi  ls03(long a, vbi *p)           { return __builtin_vec_lvswx (a,p); }
vsi  ls04(long a, vsi *p)           { return __builtin_vec_lvswx (a,p); }
vsi  ls05(long a, si *p)            { return __builtin_vec_lvswx (a,p); }
vui  ls06(long a, vui *p)           { return __builtin_vec_lvswx (a,p); }
vui  ls07(long a, ui *p)            { return __builtin_vec_lvswx (a,p); }
vbs  ls08(long a, vbs *p)           { return __builtin_vec_lvswx (a,p); }
vp   ls09(long a, vp *p)            { return __builtin_vec_lvswx (a,p); }
vss  ls10(long a, vss *p)           { return __builtin_vec_lvswx (a,p); }
vss  ls11(long a, ss *p)            { return __builtin_vec_lvswx (a,p); }
vus  ls12(long a, vus *p)           { return __builtin_vec_lvswx (a,p); }
vus  ls13(long a, us *p)            { return __builtin_vec_lvswx (a,p); }
vbc  ls14(long a, vbc *p)           { return __builtin_vec_lvswx (a,p); }
vsc  ls15(long a, vsc *p)           { return __builtin_vec_lvswx (a,p); }
vsc  ls16(long a, sc *p)            { return __builtin_vec_lvswx (a,p); }
vuc  ls17(long a, vuc *p)           { return __builtin_vec_lvswx (a,p); }
vuc  ls18(long a, uc *p)            { return __builtin_vec_lvswx (a,p); }
vsf  Dls01(long a, vsf *p)          { return vec_lvswx (a,p); }
vsf  Dls02(long a, sf *p)           { return vec_lvswx (a,p); }
vbi  Dls03(long a, vbi *p)          { return vec_lvswx (a,p); }
vsi  Dls04(long a, vsi *p)          { return vec_lvswx (a,p); }
vsi  Dls05(long a, si *p)           { return vec_lvswx (a,p); }
vui  Dls06(long a, vui *p)          { return vec_lvswx (a,p); }
vui  Dls07(long a, ui *p)           { return vec_lvswx (a,p); }
vbs  Dls08(long a, vbs *p)          { return vec_lvswx (a,p); }
vp   Dls09(long a, vp *p)           { return vec_lvswx (a,p); }
vss  Dls10(long a, vss *p)          { return vec_lvswx (a,p); }
vss  Dls11(long a, ss *p)           { return vec_lvswx (a,p); }
vus  Dls12(long a, vus *p)          { return vec_lvswx (a,p); }
vus  Dls13(long a, us *p)           { return vec_lvswx (a,p); }
vbc  Dls14(long a, vbc *p)          { return vec_lvswx (a,p); }
vsc  Dls15(long a, vsc *p)          { return vec_lvswx (a,p); }
vsc  Dls16(long a, sc *p)           { return vec_lvswx (a,p); }
vuc  Dls17(long a, vuc *p)          { return vec_lvswx (a,p); }
vuc  Dls18(long a, uc *p)           { return vec_lvswx (a,p); }
