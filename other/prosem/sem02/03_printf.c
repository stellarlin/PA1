/**
 * printf - print variables, formatting
 */
#include <stdio.h>
#include <stdlib.h>

int main ( void ) {
  int a, b;
  a = 123;
  b = 1;
  printf("a = %d\n", a);
  /* a = 10 */
  printf("%d + %d = %d\n", a, b, a + b);
  /* 10 + 20 = 30 */
  printf("%2d + %2d = %05d\n", a, b, a + b);
  /* 10 + 20 = 00030 */
  return EXIT_SUCCESS;
}
