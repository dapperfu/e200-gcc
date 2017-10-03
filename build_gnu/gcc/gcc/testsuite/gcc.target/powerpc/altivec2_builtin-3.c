/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "vabsduw" 7 } } */

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

vui  fa3w(vui a, vui b)             { return __builtin_altivec_vabsduw (a,b); }
vui  ad7(vui a, vui b)              { return __builtin_vec_absd (a,b); }
vui  ad8(vbi a, vui b)              { return __builtin_vec_absd (a,b); }
vui  ad9(vui a, vbi b)              { return __builtin_vec_absd (a,b); }
vui  Dad7(vui a, vui b)             { return vec_absd (a,b); }
vui  Dad8(vbi a, vui b)             { return vec_absd (a,b); }
vui  Dad9(vui a, vbi b)             { return vec_absd (a,b); }
