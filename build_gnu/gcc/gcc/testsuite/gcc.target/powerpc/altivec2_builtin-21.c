/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-skip-if "" { powerpc*-*-darwin* } { "*" } { "" } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O2 -maltivec -maltivec2" } */
/* { dg-final { scan-assembler-times "stvswxl" 37 } } */

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

void ss2l(vsc v, long a, vsc *p)    { __builtin_altivec_stvswxl (v,a,p); }
void ssxl01(vsf v, long a, vsf *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl02(vsf v, long a, sf  *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl03(vbi v, long a, vbi *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl04(vsi v, long a, vsi *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl05(vsi v, long a, si  *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl06(vui v, long a, vui *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl07(vui v, long a, ui  *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl08(vbs v, long a, vbs *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl09(vp  v, long a, vp  *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl10(vss v, long a, vss *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl11(vss v, long a, ss  *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl12(vus v, long a, vus *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl13(vus v, long a, us  *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl14(vbc v, long a, vbc *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl15(vsc v, long a, vsc *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl16(vsc v, long a, sc  *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl17(vuc v, long a, vuc *p)  { __builtin_vec_stvswxl (v,a,p); }
void ssxl18(vuc v, long a, uc  *p)  { __builtin_vec_stvswxl (v,a,p); }
void Dssxl01(vsf v, long a, vsf *p) { vec_stvswxl (v,a,p); }
void Dssxl02(vsf v, long a, sf  *p) { vec_stvswxl (v,a,p); }
void Dssxl03(vbi v, long a, vbi *p) { vec_stvswxl (v,a,p); }
void Dssxl04(vsi v, long a, vsi *p) { vec_stvswxl (v,a,p); }
void Dssxl05(vsi v, long a, si  *p) { vec_stvswxl (v,a,p); }
void Dssxl06(vui v, long a, vui *p) { vec_stvswxl (v,a,p); }
void Dssxl07(vui v, long a, ui  *p) { vec_stvswxl (v,a,p); }
void Dssxl08(vbs v, long a, vbs *p) { vec_stvswxl (v,a,p); }
void Dssxl09(vp  v, long a, vp  *p) { vec_stvswxl (v,a,p); }
void Dssxl10(vss v, long a, vss *p) { vec_stvswxl (v,a,p); }
void Dssxl11(vss v, long a, ss  *p) { vec_stvswxl (v,a,p); }
void Dssxl12(vus v, long a, vus *p) { vec_stvswxl (v,a,p); }
void Dssxl13(vus v, long a, us  *p) { vec_stvswxl (v,a,p); }
void Dssxl14(vbc v, long a, vbc *p) { vec_stvswxl (v,a,p); }
void Dssxl15(vsc v, long a, vsc *p) { vec_stvswxl (v,a,p); }
void Dssxl16(vsc v, long a, sc  *p) { vec_stvswxl (v,a,p); }
void Dssxl17(vuc v, long a, vuc *p) { vec_stvswxl (v,a,p); }
void Dssxl18(vuc v, long a, uc  *p) { vec_stvswxl (v,a,p); }
