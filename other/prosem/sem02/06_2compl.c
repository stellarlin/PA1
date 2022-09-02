#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int main ( void )
{
  int zero = 0;
  
  /* try all integers (except INT_MAX), takes a while */
  for ( int i = INT_MIN; i != INT_MAX; i ++ )
  {
    /* integers: x = -x only iff x = 0 */
    /* 2's complement code: x = -x  when x = 0 or x = INT_MIN */
    if ( i == -i )
      zero ++;
  }
  printf ( "%d\n", zero ); /* expected value: 1, result: 2 */
  return 0;
}
