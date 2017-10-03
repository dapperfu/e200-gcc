/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "lvswxl" 37 } } */

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

vsc  ls2l(long a, void *p)          { return __builtin_altivec_lvswxl (a,p); }
vsf  lsl01(long a, vsf *p)          { return __builtin_vec_lvswxl (a,p); }
vsf  lsl02(long a, sf *p)           { return __builtin_vec_lvswxl (a,p); }
vbi  lsl03(long a, vbi *p)          { return __builtin_vec_lvswxl (a,p); }
vsi  lsl04(long a, vsi *p)          { return __builtin_vec_lvswxl (a,p); }
vsi  lsl05(long a, si *p)           { return __builtin_vec_lvswxl (a,p); }
vui  lsl06(long a, vui *p)          { return __builtin_vec_lvswxl (a,p); }
vui  lsl07(long a, ui *p)           { return __builtin_vec_lvswxl (a,p); }
vbs  lsl08(long a, vbs *p)          { return __builtin_vec_lvswxl (a,p); }
vp   lsl09(long a, vp *p)           { return __builtin_vec_lvswxl (a,p); }
vss  lsl10(long a, vss *p)          { return __builtin_vec_lvswxl (a,p); }
vss  lsl11(long a, ss *p)           { return __builtin_vec_lvswxl (a,p); }
vus  lsl12(long a, vus *p)          { return __builtin_vec_lvswxl (a,p); }
vus  lsl13(long a, us *p)           { return __builtin_vec_lvswxl (a,p); }
vbc  lsl14(long a, vbc *p)          { return __builtin_vec_lvswxl (a,p); }
vsc  lsl15(long a, vsc *p)          { return __builtin_vec_lvswxl (a,p); }
vsc  lsl16(long a, sc *p)           { return __builtin_vec_lvswxl (a,p); }
vuc  lsl17(long a, vuc *p)          { return __builtin_vec_lvswxl (a,p); }
vuc  lsl18(long a, uc *p)           { return __builtin_vec_lvswxl (a,p); }
vsf  Dlsl01(long a, vsf *p)         { return vec_lvswxl (a,p); }
vsf  Dlsl02(long a, sf *p)          { return vec_lvswxl (a,p); }
vbi  Dlsl03(long a, vbi *p)         { return vec_lvswxl (a,p); }
vsi  Dlsl04(long a, vsi *p)         { return vec_lvswxl (a,p); }
vsi  Dlsl05(long a, si *p)          { return vec_lvswxl (a,p); }
vui  Dlsl06(long a, vui *p)         { return vec_lvswxl (a,p); }
vui  Dlsl07(long a, ui *p)          { return vec_lvswxl (a,p); }
vbs  Dlsl08(long a, vbs *p)         { return vec_lvswxl (a,p); }
vp   Dlsl09(long a, vp *p)          { return vec_lvswxl (a,p); }
vss  Dlsl10(long a, vss *p)         { return vec_lvswxl (a,p); }
vss  Dlsl11(long a, ss *p)          { return vec_lvswxl (a,p); }
vus  Dlsl12(long a, vus *p)         { return vec_lvswxl (a,p); }
vus  Dlsl13(long a, us *p)          { return vec_lvswxl (a,p); }
vbc  Dlsl14(long a, vbc *p)         { return vec_lvswxl (a,p); }
vsc  Dlsl15(long a, vsc *p)         { return vec_lvswxl (a,p); }
vsc  Dlsl16(long a, sc *p)          { return vec_lvswxl (a,p); }
vuc  Dlsl17(long a, vuc *p)         { return vec_lvswxl (a,p); }
vuc  Dlsl18(long a, uc *p)          { return vec_lvswxl (a,p); }
