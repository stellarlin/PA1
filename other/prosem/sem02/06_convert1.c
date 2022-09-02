/*
 * (silent) output cnversions
 */
#include <stdio.h>
#include <stdlib.h>

int main ( void ) {
  int x = -1;
  printf ( "x = %d  (signed,dec)\n", x );
  /* -1 */
  
  printf ( "x = %i  (signed,dec)\n", x );
  /* -1 */
  
  printf ( "x = %u  (unsigned,dec)\n", x );
  /* 2's complement code of -1 (e.g. 0xffffffff) is 
   * printed out as a decimal unsigned: 4294967295
   */
  
  printf ( "x = %x  (unsigned,hex)\n", x );
  /* 2's complement code of -1 (e.g. 0xffffffff) is 
   * printed out as a hexadecimal: ffffffff 
   */
  
  printf ( "x = %X  (unsigned,HEX)\n", x );
  /* 2's complement code of -1 (e.g. 0xffffffff) is 
   * printed out as an uppercase hexadecimal: FFFFFFFF 
   */
  
  printf ( "x = %o  (unsigned,oct)\n", x );
  /* 2's complement code of -1 (e.g. 0xffffffff) is 
   * printed out as octal number: 37777777777
   */
  return EXIT_SUCCESS;
}
