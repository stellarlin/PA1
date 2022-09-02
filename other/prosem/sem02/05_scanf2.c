/**
 * scanf - read from standard input, validate the input
 */
#include <stdio.h>
#include <stdlib.h>

int main ( void ) {
  int x;
  printf("Enter an integer:\n");
  if ( scanf( "%d", &x ) != 1 ) {
    /* Invalid input - scanf failed the conversion, its return value was not 1 */
    printf("invalid input.\n" );
    return EXIT_FAILURE;
  }
  /* correct input, process the data */
  printf("the integer is %d\n", x );
  return EXIT_SUCCESS;
}
