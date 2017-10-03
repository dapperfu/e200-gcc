/* { dg-do compile { target powerpc*-*-* } } */
/* { dg-options "-O2 -fuse-seq-load-indexes" } */

void
testloadindex (
    short   *Data,     
    short   *AccData,  
    short   DataSize,       
    short   NumberOfLags,   
    short   Scale           
)
{
    int   i;
    int   lag;
    int   LastIndex;
    int   Accumulator;

    for (lag = 0; lag < NumberOfLags; lag++) {
        Accumulator = 0;
        LastIndex = DataSize - lag;
        for (i = 0; i < LastIndex; i++) {
            Accumulator += ((int) Data[i] * (int) Data[i+lag]) >> Scale;
        }
        AccData[lag] = (short) (Accumulator >> 16) ;
    }
}
/* { dg-final { scan-assembler-not "lhau" } }*/
/* { dg-final { scan-assembler-times "lhax" 2 } }*/

