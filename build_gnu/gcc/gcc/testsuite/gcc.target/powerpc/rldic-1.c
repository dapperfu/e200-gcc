/* { dg-do run { target { powerpc*-*-* } } } */
/* skip test unless -m64 is present */
/* { dg-skip-if "" { powerpc*-*-* } { "*" } { "-m64" } } */
/* { dg-options "-O3 -save-temps" } */

int sum;

void sum1 ( unsigned  int N, short *C) __attribute__((__noinline__)); 
void sum1 ( unsigned  int N, short *C) 
{
        unsigned int i;

        for (i=0; i<N; i++)
        {
                sum += C[i*N];
        }
} __attribute__((__noinline__))
int main()
{
        short C [5*5] = { 1 , 0, 0, 0, 0, 
        2 , 0, 0, 0, 0, 
        3 , 0, 0, 0, 0, 
        4 , 0, 0, 0, 0, 
        5 , 0, 0, 0, 0,         
        };
        sum1 (5, C);
        return (sum==15 ? 0 : 1);
}



/* { dg-final { scan-assembler-times "rldic " 1  { target powerpc*-*-*  } } } */
/* { dg-final { cleanup-saved-temps } } */
