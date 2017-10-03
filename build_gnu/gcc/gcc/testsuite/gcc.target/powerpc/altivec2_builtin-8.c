/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "stvexhx" 13 } } */

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

void se2h(vss v, long a, vss *p)    { __builtin_altivec_stvexhx (v,a,p); }
void seh1(vss v, long a, ss *p)     { __builtin_vec_stvexhx (v,a,p); }
void seh2(vus v, long a, us *p)     { __builtin_vec_stvexhx (v,a,p); }
void seh3(vbs v, long a, ss *p)     { __builtin_vec_stvexhx (v,a,p); }
void seh4(vbs v, long a, us *p)     { __builtin_vec_stvexhx (v,a,p); }
void seh5(vss v, long a, void *p)   { __builtin_vec_stvexhx (v,a,p); }
void seh6(vus v, long a, void *p)   { __builtin_vec_stvexhx (v,a,p); }
void Dseh1(vss v, long a, ss *p)    { vec_stvexhx (v,a,p); }
void Dseh2(vus v, long a, us *p)    { vec_stvexhx (v,a,p); }
void Dseh3(vbs v, long a, ss *p)    { vec_stvexhx (v,a,p); }
void Dseh4(vbs v, long a, us *p)    { vec_stvexhx (v,a,p); }
void Dseh5(vss v, long a, void *p)  { vec_stvexhx (v,a,p); }
void Dseh6(vus v, long a, void *p)  { vec_stvexhx (v,a,p); }
