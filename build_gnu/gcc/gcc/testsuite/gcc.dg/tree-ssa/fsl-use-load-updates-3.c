/* { dg-do compile { target { powerpc*-*-* && ilp32 } } } */
/* { dg-options "-O3 -fuse-load-updates" } */

extern void baz(char *s, char *m, char *end);

void foo(char *s, char *m, char *end)
{
        while (*s == *m && s < end) {

		s += 1;
		m += 1;
	}

	baz(s, 0, end);
}

/* { dg-final { scan-assembler-times "lbzu" 2 { target powerpc*-*-* } } } */
