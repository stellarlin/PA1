#include <stdio.h>
#include <float.h>


int main ( void )
{
  double a, b, c;
  
  if ( scanf ( "%lf %lf %lf", &a, &b, &c ) != 3 )
    return 1;
    
  /* input 1 2 3         -> works as expected */
  /* input 1e30 -1e30 1  -> oops */
   
  printf ("(%e + %e) + %e = %e\n", a, b, c, ( a + b ) + c );
  printf ( "%e + (%e + %e) = %e\n", a, b, c, a + ( b + c ) );
  return 0;
}
