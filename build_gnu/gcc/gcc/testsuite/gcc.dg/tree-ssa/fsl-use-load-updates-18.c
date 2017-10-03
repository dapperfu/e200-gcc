/* { dg-do compile { target { powerpc*-*-* && lp64 } } } */
/* { dg-options "-O3 -fuse-load-updates" } */

extern void baz(char *p, char *s);

void foo(char *p, char *q, char *r, char *s)
{
        while (*p == *q && *p == *r && p < s) {

		p += 2;
		q += 3;
		r += 7;
	}

	baz(p, s);
}

/* { dg-final { scan-assembler-times "addi" 1 { target powerpc*-*-* } } } */
/* { dg-final { scan-assembler-times "lbzu" 3 { target powerpc*-*-* } } } */
/* { dg-final { scan-assembler-times "stdu" 1 { target powerpc*-*-* } } } */
