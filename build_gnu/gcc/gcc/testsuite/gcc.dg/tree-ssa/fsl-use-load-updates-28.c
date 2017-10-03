/* { dg-do compile { target { powerpc*-*-* && lp64 } } } */
/* { dg-options "-O3 -fuse-load-updates" } */

extern void baz(char *scan, char *match, char *strend);

void foo(char *scan, char *match, char *strend)
{
        while (*scan == *match && scan > strend) {

		scan  += -2;
		match += -2;

		*scan = 0;
		*match = 0;
	}

	baz(scan, 0, strend);
}

/* { dg-final { scan-assembler-times "addi" 1 { target powerpc*-*-* } } } */
/* { dg-final { scan-assembler-times "stbu" 2 { target powerpc*-*-* } } } */
/* { dg-final { scan-assembler-times "stdu" 1 { target powerpc*-*-* } } } */
