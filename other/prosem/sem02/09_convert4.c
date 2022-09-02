/*
 * (silent) output cnversions
 */
#include <stdio.h>
#include <stdlib.h>

int main ( void ) {
  int x, y, z = 128;
  unsigned char cx = 128;
  signed char   cy = -10, cz;
  
  /* promotion from unsigned -> zero pad high order bits */
  x = cx; /* 1000 0000 -> 0...00 1000 0000 */
  printf ( "x = %d\n", x); 
  /* x = 128 */
  
  /* promotion from signed -> pad high order bits with sign bit */
  y = cy; /* 1111 0110 -> 1...11 1111 0110 */
  printf ( "y = %d\n", y); 
  /* y = -10 */
  
  /* to smaller data type -> strip high order bits */
  cz = z; /* 0...00 1000 0000 -> 1000 0000 */
  /* from unsigned -> pad high order bits with sign bit */
  z = cz; /* 1000 0000 -> 1...11 1000 0000 */
  printf ( "z = %d\n", z); 
  /* z = -128 */
  return EXIT_SUCCESS;
}
