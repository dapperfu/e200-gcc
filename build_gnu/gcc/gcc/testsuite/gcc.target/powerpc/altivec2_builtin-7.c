/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "stvexbx" 13 } } */

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

void se1b(vsc v, long a, vsc *p)    { __builtin_altivec_stvexbx (v,a,p); }
void seb1(vsc v, long a, sc *p)     { __builtin_vec_stvexbx (v,a,p); }
void seb2(vuc v, long a, uc *p)     { __builtin_vec_stvexbx (v,a,p); }
void seb3(vbc v, long a, sc *p)     { __builtin_vec_stvexbx (v,a,p); }
void seb4(vbc v, long a, uc *p)     { __builtin_vec_stvexbx (v,a,p); }
void seb5(vsc v, long a, void *p)   { __builtin_vec_stvexbx (v,a,p); }
void seb6(vuc v, long a, void *p)   { __builtin_vec_stvexbx (v,a,p); }
void Dseb1(vsc v, long a, sc *p)    { vec_stvexbx (v,a,p); }
void Dseb2(vuc v, long a, uc *p)    { vec_stvexbx (v,a,p); }
void Dseb3(vbc v, long a, sc *p)    { vec_stvexbx (v,a,p); }
void Dseb4(vbc v, long a, uc *p)    { vec_stvexbx (v,a,p); }
void Dseb5(vsc v, long a, void *p)  { vec_stvexbx (v,a,p); }
void Dseb6(vuc v, long a, void *p)  { vec_stvexbx (v,a,p); }
