#include <stdio.h>


int main ( void )
{
  double a = 1.0 / 0.0; /* prepare inf value */
  double b = 0 * a;     /* prepare nan value */
  
  printf ( "a = %f, b = %f\n", a, b );
  
  printf ( "a == a -> %d\n", a == a );
  
  /* nan behavior in comparisons */
  printf ( "b > 0 -> %d\n", b > 0 );
  printf ( "b == 0 -> %d\n", b == 0 );
  printf ( "b < 0 -> %d\n", b < 0 );
  printf ( "b == b -> %d\n", b == b );
  
  /* expressions with a nan value */
  printf ( "b * 0 -> %f\n", b * 0 );
  printf ( "b - b -> %f\n", b - b );
  printf ( "b * inf -> %f\n", b * a );
  
  return 0;
}
