/* { dg-do compile { target { powerpc*-*-* && ilp32 } } } */
/* { dg-options "-O3 -fdump-rtl-loop2_invariant" } */
/* { dg-final { scan-rtl-dump-times "Decided to move" 10 "loop2_invariant"} } */
/* { dg-final { cleanup-rtl-dump "loop2_invariant" } } */

#include <string.h>
unsigned char setmask[] =
{
    0x01, 0x02, 0x04, 0x08,
    0x10, 0x20, 0x40, 0x80,
};


int threashold[] = { 139,138,122,120,131,135,109,130 };
void ditherImage (unsigned char *input_buffer, int input_height,
                         int input_width, unsigned char *output_buffer)
{
  int * c0;
  int * c1;
  int column;
  int pixel;
  unsigned char byte = 0;
  int error;
  int row;
  int bit = 0;
  int * temp;
  int * err0;
  int storage_err0[(2) * (256 +2*(1))];

  memset((void*)output_buffer, 0,
              (input_height * ((input_width-1)/(8)+1)));

  err0 = storage_err0;
  memset((void*)err0, 0,
              (2) * (input_width+2*(1)) * sizeof(int));

  c0 = err0 + (1);
  c1 = c0 + input_width + 2*(1);

  for (row = 0; row < input_height; ++row)
  {
    error = 0;
    for (column = 0; column < input_width; ++column)
    {
      if ((pixel = *(input_buffer++)) == (255))
        c0[column] = error = 0;
      else
      {
        pixel += ((error * 8 + c1[column+1] * 3 + c1[column] * 5
                  + c1[column-1] * 1)/16);
        if (pixel < threashold[bit])
        {
          byte |= setmask[bit];
          c0[column] = error = pixel;
        }
        else
        {
          c0[column] = error = pixel - (255);
        }
      }

      if (++bit >= (8))
      {
        *(output_buffer++) = byte;
        byte = bit = 0;
      }
    }

    if (bit != 0)
    {
      *(output_buffer++) = byte;
      byte = bit = 0;
    }

    temp = c0;
    c0 = c1;
    c1 = temp;
  }
  return;
}
