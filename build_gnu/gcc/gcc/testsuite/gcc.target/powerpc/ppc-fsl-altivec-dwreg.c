/* { dg-do compile { target { powerpc*-*-* } } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-O0 -g -mmap_dwarf_vecreg" } */
/* { dg-final { scan-assembler-times ".uleb128 0x481" 1 } } */
/* { dg-final { scan-assembler-times ".uleb128 0x482" 1 } } */
/* { dg-final { scan-assembler-times ".uleb128 0x483" 1 } } */

#include <altivec.h>

vector unsigned int fun()
{
  register vector unsigned int vi1 = {0,1,2,3}; 
  register vector unsigned int vi2 = {1,2,3,4};
  register vector unsigned int ri = {0,0,0,0};
  ri = vec_add(vi1, vi2); /* ri = vi1 + vi2 */

  return ri;
}
