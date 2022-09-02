/**
 * scanf - read from standard input, invalid input is not tested
 */
#include <stdio.h>
#include <stdlib.h>

int main ( void ) {
  int x;
  printf("Enter an integer:\n");
  scanf( "%d", &x );   /* note the &  */
  /* If the input is invalid, scanf returns and variable x is not initialized */
  printf("the integer is %d\n", x );
  return EXIT_SUCCESS;
}
