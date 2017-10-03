/* { dg-do compile { target { powerpc*-*-* && lp64 } } } */
/* { dg-options "-O3 -fuse-load-updates" } */

extern void baz(char *p, char *s);

void foo(char *p, char *q, char *r, char *s)
{
        while (*p && *q && *r && *s &&
               *p == *q && *p == *r && *p == *s &&
               *q == *r && *q == *s &&
               *r == *s) {

		p += 1;
		q += 1;
		r += 1;
		s += 1;
	}
}

/* { dg-final { scan-assembler-times "addi" 0 { target powerpc*-*-* } } } */
/* { dg-final { scan-assembler-times "lbzu" 4 { target powerpc*-*-* } } } */
