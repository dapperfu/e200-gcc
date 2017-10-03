/* { dg-do compile { target { powerpc*-*-* && lp64 } } } */
/* { dg-options "-O3 -fuse-load-updates -fno-builtin -fno-tree-loop-optimize" } */

void *memset(void *b, int c, unsigned long len)
{
        unsigned long i;

        for (i = 0; i < len; i++)
                ((unsigned char *)b)[i] = c;

        return b;
}

/* NOTE: We ought to get at-least one stwu - there is some vector related stuff that
 *       we need to take into consideration under -fuse-load-updates. With plain
 *       vanilla GCC, we do get one stwu, so we are actually degrading performance
 *       by not taking the "vector stuff" into account. */

/* { dg-final { scan-assembler-times "addi" 1 { target powerpc*-*-* } } } */
