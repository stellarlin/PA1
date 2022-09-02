#include <stdio.h>
#include <float.h>


int main ( void )
{
  for ( int i = 0; i < 100000000; i ++ )
  {
  } 
  /* completes */
  printf ( "int done\n" ); 

  for ( double i = 0; i < 1e8; i ++ )
  {
  } 
  /* completes */
  printf ( "double done\n" );  
  
  for ( float i = 0; i < 1e8; i ++ )
  {
  }
  /* an infinite loop, 1 + 2^24 = 2^24 in IEEE 754 32-bit type */
  printf ( "float done\n" ); 
  
  return 0;
}
