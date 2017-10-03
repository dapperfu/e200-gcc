/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "lvexhx" 5 } } */

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

vss  le2h(long a, void *p)          { return __builtin_altivec_lvexhx (a,p); }
vss  leh1(long a, ss *p)            { return __builtin_vec_lvexhx (a,p); }
vus  leh2(long a, us *p)            { return __builtin_vec_lvexhx (a,p); }
vss  Dleh1(long a, ss *p)           { return vec_lvexhx (a,p); }
vus  Dleh2(long a, us *p)           { return vec_lvexhx (a,p); }
