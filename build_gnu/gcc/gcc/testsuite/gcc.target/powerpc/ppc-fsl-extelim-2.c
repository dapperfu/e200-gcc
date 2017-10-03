/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-options "-O2 -std=c99" } */
/* { dg-final { scan-assembler "rlwinm \[0-9\]+,\[0-9\]+,\[0-9\]+,0xff"  { target { ilp32 } } } } */

#define GET_MODULE(_id)         ((_id & 0x00003F00) >> 8)
#define GET_IF(_id)             ((_id & 0x000000FF))
#define GET_IF_ID(_module, _if) (((_module) << 8) | (_if))

unsigned int dev;

void testthebug(unsigned short i);

void testbug(void)
{
  unsigned char  module;
  unsigned char  interface;
  unsigned short ifid;

  module = GET_MODULE(dev);
  interface = GET_IF(dev);
  ifid = GET_IF_ID(module + 1, interface + 1);

  testthebug(ifid);
}
