#include <stdio.h>

int main ( void )
{
  double x = 0, y = 0.1;
  
  for ( int i = 0; i < 10; i ++ )
    x += y;
    
  /* 10 * 0.1 != 1 */  
  if ( x == 1 )
    printf ( "%f = 1\n", x );
  else
    printf ( "%.20f <> 1\n", x ); /* try with format %.20f */
  
  return 0;
}
