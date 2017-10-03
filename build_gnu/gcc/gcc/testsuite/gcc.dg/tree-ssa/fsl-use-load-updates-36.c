/* { dg-do compile { target { powerpc*-*-* && lp64 } } } */
/* { dg-options "-O3 -fuse-load-updates" } */

extern void foo (char *p, char *q, const char *bound);

void incrBytes(char *p, char *q, const char *bound)
{
	while (*p == *q && p < bound) {

		p += 1;
		*p = *p + 1;

		q += 1;
		*q = *q+ 1;

	}

	foo (p, 0, bound);
}

/* { dg-final { scan-assembler-times "addi" 3 { target powerpc*-*-* } } } */
/* { dg-final { scan-assembler-times "lbzu" 2 { target powerpc*-*-* } } } */
/* { dg-final { scan-assembler-times "stdu" 1 { target powerpc*-*-* } } } */
