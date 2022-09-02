/* compile: gcc -Wall -pedantic -lm 04_sincos.c */
#include <stdio.h>
#include <math.h>


int main ( void )
{
  for ( int i = 0; i < 628; i ++ )
  {
    double x = i / 100.0;
    /* the equality is not matched for some values of x (rounding errors) */
    if ( sin (x) * sin (x) + cos(x) * cos(x) == 1 )
      printf ( "%f: ok\n", x );
    else
      printf ( "%f: mismatch\n", x );
  }
  return 0;
}
