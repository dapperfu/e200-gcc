/* { dg-do compile { target { powerpc*-*-* && lp64 } } } */
/* { dg-options "-O3 -fuse-load-updates" } */

extern void baz(char *s, char *m, char *strend);

void foo(char *s, char *m, char *strend)
{
        while (*s == *m && s < strend) {

		s += 2;
		m -= 2;
	}

	baz(s, 0, strend);
}

/* { dg-final { scan-assembler-times "addi" 1 { target powerpc*-*-* } } } */
/* { dg-final { scan-assembler-times "lbzu" 2 { target powerpc*-*-* } } } */
/* { dg-final { scan-assembler-times "stdu" 1 { target powerpc*-*-* } } } */
