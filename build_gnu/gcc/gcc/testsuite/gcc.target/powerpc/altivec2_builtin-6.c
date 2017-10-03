/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "lvexwx" 11 } } */

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

vsi  le3w(long a, void *p)          { return __builtin_altivec_lvexwx (a,p); }
vsf  lew1(long a, sf *p)            { return __builtin_vec_lvexwx (a,p); }
vsi  lew2(long a, si *p)            { return __builtin_vec_lvexwx (a,p); }
vui  lew3(long a, ui *p)            { return __builtin_vec_lvexwx (a,p); }
vsi  lew4(long a, sl *p)            { return __builtin_vec_lvexwx (a,p); }
vui  lew5(long a, ul *p)            { return __builtin_vec_lvexwx (a,p); }
vsf  Dlew1(long a, sf *p)           { return vec_lvexwx (a,p); }
vsi  Dlew2(long a, si *p)           { return vec_lvexwx (a,p); }
vui  Dlew3(long a, ui *p)           { return vec_lvexwx (a,p); }
vsi  Dlew4(long a, sl *p)           { return vec_lvexwx (a,p); }
vui  Dlew5(long a, ul *p)           { return vec_lvexwx (a,p); }
