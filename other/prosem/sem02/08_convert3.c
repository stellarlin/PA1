/*
 * (silent) output cnversions
 */
#include <stdio.h>
#include <stdlib.h>

int main ( void ) {
  int x = 1000, y = 767;
  signed char cx, cy;
  
  /* char is smaller than int -> strip high order bits */
  cx = x; /* 0...011 1110 1000 -> 1110 1000 */
  printf ( "x = %d, cx = %d\n", x, cx );
  /* x = 1000, cx = -24 */
  
  cy = y; /* 0...010 1111 1111 -> 1111 1111 */
  printf ( "y = %d, cy = %d\n", y, cy );
  /* y = 767, cy = -1 */
  return EXIT_SUCCESS;
}
