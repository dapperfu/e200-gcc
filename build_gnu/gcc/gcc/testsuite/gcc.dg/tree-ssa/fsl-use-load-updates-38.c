/* { dg-do compile { target { powerpc*-*-* && lp64 } } } */
/* { dg-options "-O3 -fuse-load-updates" } */

struct rx {
 char **startp;
};

extern int *foo();

int **bar(void)
{
 int **sp;
 int iterations, i;
 struct rx *rx;

 for (i = i; i <= iterations; i++) {

   ++sp;
   *sp = foo();

   if (rx->startp[i])
     gorp();
 }

 return sp;
}

/* { dg-final { scan-assembler-times "addi" 3 { target powerpc*-*-* } } } */
/* { dg-final { scan-assembler-times "stdu" 2 { target powerpc*-*-* } } } */
