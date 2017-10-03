/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "stvswx" 37 } } */

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

void ss1(vsc v, long a, vsc *p)     { __builtin_altivec_stvswx (v,a,p); }
void ssx01(vsf v, long a, vsf *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx02(vsf v, long a, sf  *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx03(vbi v, long a, vbi *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx04(vsi v, long a, vsi *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx05(vsi v, long a, si  *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx06(vui v, long a, vui *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx07(vui v, long a, ui  *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx08(vbs v, long a, vbs *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx09(vp  v, long a, vp  *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx10(vss v, long a, vss *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx11(vss v, long a, ss  *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx12(vus v, long a, vus *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx13(vus v, long a, us  *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx14(vbc v, long a, vbc *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx15(vsc v, long a, vsc *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx16(vsc v, long a, sc  *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx17(vuc v, long a, vuc *p)   { __builtin_vec_stvswx (v,a,p); }
void ssx18(vuc v, long a, uc  *p)   { __builtin_vec_stvswx (v,a,p); }
void Dssx01(vsf v, long a, vsf *p)  { vec_stvswx (v,a,p); }
void Dssx02(vsf v, long a, sf  *p)  { vec_stvswx (v,a,p); }
void Dssx03(vbi v, long a, vbi *p)  { vec_stvswx (v,a,p); }
void Dssx04(vsi v, long a, vsi *p)  { vec_stvswx (v,a,p); }
void Dssx05(vsi v, long a, si  *p)  { vec_stvswx (v,a,p); }
void Dssx06(vui v, long a, vui *p)  { vec_stvswx (v,a,p); }
void Dssx07(vui v, long a, ui  *p)  { vec_stvswx (v,a,p); }
void Dssx08(vbs v, long a, vbs *p)  { vec_stvswx (v,a,p); }
void Dssx09(vp  v, long a, vp  *p)  { vec_stvswx (v,a,p); }
void Dssx10(vss v, long a, vss *p)  { vec_stvswx (v,a,p); }
void Dssx11(vss v, long a, ss  *p)  { vec_stvswx (v,a,p); }
void Dssx12(vus v, long a, vus *p)  { vec_stvswx (v,a,p); }
void Dssx13(vus v, long a, us  *p)  { vec_stvswx (v,a,p); }
void Dssx14(vbc v, long a, vbc *p)  { vec_stvswx (v,a,p); }
void Dssx15(vsc v, long a, vsc *p)  { vec_stvswx (v,a,p); }
void Dssx16(vsc v, long a, sc  *p)  { vec_stvswx (v,a,p); }
void Dssx17(vuc v, long a, vuc *p)  { vec_stvswx (v,a,p); }
void Dssx18(vuc v, long a, uc  *p)  { vec_stvswx (v,a,p); }
