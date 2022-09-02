#include <stdio.h>


int main ( void )
{
  int a, b, c;
  int min, med, max;
  
  if ( scanf ( "%d %d %d", &a, &b, &c ) != 3 )
    return 1;
    
  min = a;
  if ( b < min )
    min = b;
  if ( c < min )
    min = c;
      
  max = a;
  if ( b > max )
    max = b;
  if ( c > max )
    max = c;

  med = a + b + c - min - max;
  
  /* works fine for integers, even when there is an overflow, e.g.: */
  /* 2000000000 1200000000 1500000000 */
  printf ( "min = %d, med = %d, max = %d\n", min, med, max );
  
  /* may fail when modified for floating point numbers, e.g.: */
  /* 1e30 -1e30 1 */
  return 0;
}
