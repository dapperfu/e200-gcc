/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "stvfrxl" 37 } } */

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

void sc4(vsc v, long a, void *p)    { __builtin_altivec_stvfrxl (v,a,p); }
void srxl01(vsf v, long a, vsf *p)  { __builtin_vec_stvfrxl (v,a,p); }
void srxl02(vsf v, long a, sf *p)   { __builtin_vec_stvfrxl (v,a,p); }
void srxl03(vbi v, long a, vbi *p)  { __builtin_vec_stvfrxl (v,a,p); }
void srxl04(vsi v, long a, vsi *p)  { __builtin_vec_stvfrxl (v,a,p); }
void srxl05(vsi v, long a, si *p)   { __builtin_vec_stvfrxl (v,a,p); }
void srxl06(vui v, long a, vui *p)  { __builtin_vec_stvfrxl (v,a,p); }
void srxl07(vui v, long a, ui *p)   { __builtin_vec_stvfrxl (v,a,p); }
void srxl08(vbs v, long a, vbs *p)  { __builtin_vec_stvfrxl (v,a,p); }
void srxl09(vp v, long a, vp *p)    { __builtin_vec_stvfrxl (v,a,p); }
void srxl10(vss v, long a, vss *p)  { __builtin_vec_stvfrxl (v,a,p); }
void srxl11(vss v, long a, ss *p)   { __builtin_vec_stvfrxl (v,a,p); }
void srxl12(vus v, long a, vus *p)  { __builtin_vec_stvfrxl (v,a,p); }
void srxl13(vus v, long a, us *p)   { __builtin_vec_stvfrxl (v,a,p); }
void srxl14(vbc v, long a, vbc *p)  { __builtin_vec_stvfrxl (v,a,p); }
void srxl15(vsc v, long a, vsc *p)  { __builtin_vec_stvfrxl (v,a,p); }
void srxl16(vsc v, long a, sc *p)   { __builtin_vec_stvfrxl (v,a,p); }
void srxl17(vuc v, long a, vuc *p)  { __builtin_vec_stvfrxl (v,a,p); }
void srxl18(vuc v, long a, uc *p)   { __builtin_vec_stvfrxl (v,a,p); }
void Dsrxl01(vsf v, long a, vsf *p) { vec_stvfrxl (v,a,p); }
void Dsrxl02(vsf v, long a, sf *p)  { vec_stvfrxl (v,a,p); }
void Dsrxl03(vbi v, long a, vbi *p) { vec_stvfrxl (v,a,p); }
void Dsrxl04(vsi v, long a, vsi *p) { vec_stvfrxl (v,a,p); }
void Dsrxl05(vsi v, long a, si *p)  { vec_stvfrxl (v,a,p); }
void Dsrxl06(vui v, long a, vui *p) { vec_stvfrxl (v,a,p); }
void Dsrxl07(vui v, long a, ui *p)  { vec_stvfrxl (v,a,p); }
void Dsrxl08(vbs v, long a, vbs *p) { vec_stvfrxl (v,a,p); }
void Dsrxl09(vp v, long a, vp *p)   { vec_stvfrxl (v,a,p); }
void Dsrxl10(vss v, long a, vss *p) { vec_stvfrxl (v,a,p); }
void Dsrxl11(vss v, long a, ss *p)  { vec_stvfrxl (v,a,p); }
void Dsrxl12(vus v, long a, vus *p) { vec_stvfrxl (v,a,p); }
void Dsrxl13(vus v, long a, us *p)  { vec_stvfrxl (v,a,p); }
void Dsrxl14(vbc v, long a, vbc *p) { vec_stvfrxl (v,a,p); }
void Dsrxl15(vsc v, long a, vsc *p) { vec_stvfrxl (v,a,p); }
void Dsrxl16(vsc v, long a, sc *p)  { vec_stvfrxl (v,a,p); }
void Dsrxl17(vuc v, long a, vuc *p) { vec_stvfrxl (v,a,p); }
void Dsrxl18(vuc v, long a, uc *p)  { vec_stvfrxl (v,a,p); }
