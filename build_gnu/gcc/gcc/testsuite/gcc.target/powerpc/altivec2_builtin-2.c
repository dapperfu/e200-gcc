/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "vabsduh" 7 } } */

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

vus  fa2h(vus a, vus b)             { return __builtin_altivec_vabsduh (a,b); }
vus  ad4(vus a, vus b)              { return __builtin_vec_absd (a,b); }
vus  ad5(vbs a, vus b)              { return __builtin_vec_absd (a,b); }
vus  ad6(vus a, vbs b)              { return __builtin_vec_absd (a,b); }
vus  Dad4(vus a, vus b)             { return vec_absd (a,b); }
vus  Dad5(vbs a, vus b)             { return vec_absd (a,b); }
vus  Dad6(vus a, vbs b)             { return vec_absd (a,b); }
