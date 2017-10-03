/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "stvexwx" 17 } } */

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

void se3w(vsi v, long a, vsi *p)    { __builtin_altivec_stvexwx (v,a,p); }
void sew1(vsf v, long a, sf *p)     { __builtin_vec_stvexwx (v,a,p); }
void sew2(vsi v, long a, si *p)     { __builtin_vec_stvexwx (v,a,p); }
void sew3(vui v, long a, ui *p)     { __builtin_vec_stvexwx (v,a,p); }
void sew4(vbi v, long a, si *p)     { __builtin_vec_stvexwx (v,a,p); }
void sew5(vbi v, long a, ui *p)     { __builtin_vec_stvexwx (v,a,p); }
void sew6(vsf v, long a, void *p)   { __builtin_vec_stvexwx (v,a,p); }
void sew7(vsi v, long a, void *p)   { __builtin_vec_stvexwx (v,a,p); }
void sew8(vui v, long a, void *p)   { __builtin_vec_stvexwx (v,a,p); }
void Dsew1(vsf v, long a, sf *p)    { vec_stvexwx (v,a,p); }
void Dsew2(vsi v, long a, si *p)    { vec_stvexwx (v,a,p); }
void Dsew3(vui v, long a, ui *p)    { vec_stvexwx (v,a,p); }
void Dsew4(vbi v, long a, si *p)    { vec_stvexwx (v,a,p); }
void Dsew5(vbi v, long a, ui *p)    { vec_stvexwx (v,a,p); }
void Dsew6(vsf v, long a, void *p)  { vec_stvexwx (v,a,p); }
void Dsew7(vsi v, long a, void *p)  { vec_stvexwx (v,a,p); }
void Dsew8(vui v, long a, void *p)  { vec_stvexwx (v,a,p); }
