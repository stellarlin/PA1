#include <cstdio>
using namespace std;

int main ( int argc, char * argv [] )
{
  int          a = 10;
  double       b = 20;
  const char * c = "test";

  // C-like formatted output, by the book

  printf ( "a = %d\n", a );
  printf ( "b = %f\n", b );
  printf ( "c = %s\n", c );

  // Oops, format string does not match the actual variable types.

  printf ( "a = %f\n", a );
  printf ( "b = %d\n", b );
  printf ( "c = %d\n", c );
  printf ( "c = %s\n", a );

  return 0;
}
