/* { dg-do compile { target { powerpc*-*-* && lp64 } } } */
/* { dg-options "-O3 -fuse-load-updates" } */

extern void baz(int *s, int *m, int *end);

void foo(int *s, int *m, int *end)
{
        while (*s == *m && s < end) {

		s += 3;
		m += 3;
	}

	baz(s, 0, end);
}

/* { dg-final { scan-assembler-times "addi" 1 { target powerpc*-*-* } } } */
/* { dg-final { scan-assembler-times "lwzu" 2 { target powerpc*-*-* } } } */
/* { dg-final { scan-assembler-times "stdu" 1 { target powerpc*-*-* } } } */
