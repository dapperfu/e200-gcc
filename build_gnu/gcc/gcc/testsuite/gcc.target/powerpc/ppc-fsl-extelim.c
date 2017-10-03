/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-options "-O2 -std=c99" } */
/* { dg-final { scan-assembler-times "rlwinm" 2 { target { ilp32 } } } } */
/* { dg-final { scan-assembler-times "rldicl" 2 { target { lp64 } } } } */

int hipBugTest_c1 ();

int hipBugTest_c1 ()
{
  const int iN = 16;

  signed char pcIn[iN];
  unsigned char pucOut[iN];

  for (int i = 0; i < iN; i++)
  {
    pcIn[i] = (signed char) (i - 11);
    pucOut[i] = 0;
  }

  for (int i = 0; i < iN; i++)
  {
    const unsigned char ucGain = 3;
    const unsigned char ucLimit = 100;

    unsigned char ucIn;
    unsigned char ucErr;
    unsigned int uiVal;

    if (pcIn[i] < 0)
      ucIn = (unsigned char) ( pcIn[i] * -1);
    else
      ucIn = (unsigned char) pcIn[i];

    uiVal = ucIn - 3;
    uiVal = uiVal * (unsigned int) ucGain;

    if (uiVal > ucLimit)
      ucErr = ucLimit;
    else
      ucErr = (unsigned char)uiVal;

    pucOut[i] = ucErr;
  }
  return pucOut[0];
}
