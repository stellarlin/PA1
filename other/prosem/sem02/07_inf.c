#include <stdio.h>
#include <float.h>


int main ( void )
{
  double a = DBL_MAX;
  double b = 1.0 / 0.0;

  printf ( "a = %e, b = %e\n", a, b );  
  /* inf > DBL_MAX */
  printf ( "b > a -> %d\n", b > a  ); 
  /* 1.0000000000000001 is represented as 1, inf > DBL_MAX */
  printf ( "b > 1.0000000000000001 a -> %d\n", b > 1.0000000000000001 * a );
  /* 1.0000000000000002 is greater than 1,  1.0000000000000002 * DBL_MAX = inf */
  printf ( "b > 1.0000000000000002 a -> %d\n", b > 1.0000000000000002 * a );
  return 0;
}
