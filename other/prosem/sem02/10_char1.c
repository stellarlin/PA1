/*
 * character input and output
 */
#include <stdio.h>
#include <stdlib.h>

int main ( void ) {
  char c;
  printf ( "Enter a character:\n" );
  if ( scanf ( "%c", &c ) == 1 )
    printf ( "input character: %c, code %d\n", c, (unsigned char)c );
  else
    printf ( "no input data.\n" );
  return EXIT_SUCCESS;
}
