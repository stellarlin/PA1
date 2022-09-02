/*
 * character output
 */
#include <stdio.h>
#include <stdlib.h>

int main ( void ) {
  char c =  '@';
  int i =   0x40;
  unsigned  int u = 0xff40;
  
  /* promoted from char to int */
  printf ( "c = %x %d %c\n", c, c, c );
  /* c = 40 64 @ */
  
  /* %c uses only the low 8 bits of the int */
  printf ( "i = %x %d %c\n", i, i, i );
  /* c = 40 64 @ */
  
  /* %c uses only the low 8 bits of the int */
  printf ( "u = %x %d %c\n", u, u, u );
  /* c = ff40 65344 @ */
  
  return EXIT_SUCCESS;
}
