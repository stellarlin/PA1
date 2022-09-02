/*
 * (silent) output cnversions
 */
#include <stdio.h>
#include <stdlib.h>

int main ( void ) {
  int x, y;
  unsigned int ux = 1000, uy = 0xffffffff;
  
  /* operands of the same size -> binary representation is copied without 
   * any modifications
   */
  x = ux; /* 00...001111101000 */
  printf ( "ux = %u, x = %d\n", ux, x ); 
  /* ux = 1000, x = 1000 */
  
  /* operands of the same size -> binary representation is copied without 
   * any modifications
   */
  y = uy; /* 11...111111111111 */
  printf ( "uy = %u, y = %d\n", uy, y );
  /* uy = 4294967295, y = -1 */
  
  /* operands of the same size -> binary representation is copied without 
   * any modifications (2's complement of -100)
   */
  ux = -100; /* 11...111110011100 */
  printf ( "ux = %u\n", ux ); 
  /* ux = 4294967196 */
  return EXIT_SUCCESS;
}
