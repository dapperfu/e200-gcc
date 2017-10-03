/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "vabsdub" 7 } } */

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

vuc  fa1b(vuc a, vuc b)             { return __builtin_altivec_vabsdub (a,b); }
vuc  ad1(vuc a, vuc b)              { return __builtin_vec_absd (a,b); }
vuc  ad2(vbc a, vuc b)              { return __builtin_vec_absd (a,b); }
vuc  ad3(vuc a, vbc b)              { return __builtin_vec_absd (a,b); }
vuc  Dad1(vuc a, vuc b)             { return vec_absd (a,b); }
vuc  Dad2(vbc a, vuc b)             { return vec_absd (a,b); }
vuc  Dad3(vuc a, vbc b)             { return vec_absd (a,b); }
