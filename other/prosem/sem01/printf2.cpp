/* gcc provides somewhat more detailed analysis of the format string.
 * It knows the printf function and it knows the structure of the format string.
 * Therefore, it can report mismatches. On the other hand, the analysis is
 * ad-hoc. If we reimplement printf function (here myprintf), the problem with
 * the format string persist: the compiler is unable to analyse the mismatches
 * because it does not know anything about myprintf.
 */

#include <cstdarg>
#include <cstdio>
using namespace std;

// simple int to string conversion function
static void  printInt ( int x )
{
  if ( x <= 9 )
    putc ( x + '0', stdout );
  else
  {
    printInt ( x / 10 );
    putc ( x % 10 + '0', stdout );
  }
}
// our myprintf implementation
void myprintf ( const char * fmt, ... )
{
  va_list va;
  bool    conv = false;
  int     i;
  const char * str;

  // va_arg and the related macros are used to access the variadic parameters.
  // see stdarg header file
  va_start ( va, fmt );

  while ( *fmt )
  {
    // iterate through the format string
    if ( conv )
    {
      switch ( *fmt )
      {
        case 'd': // decimal conversion
          i = va_arg ( va, int );
          if ( i < 0 )
          {
            putc ( '-', stdout );
            i = -i;
          }
          printInt ( i );
          break;

        case 's': // string conversion
          str = va_arg ( va, const char *);
          while ( *str )
          {
            putc ( *str, stdout );
            str ++;
          }
          break;

        case '%': // percent - the escape sequence
          putc ( '%', stdout );
          break;
        default: // unknown conversion - skip
          break;
      }
      conv = false;
    }
    else
    {
      if ( *fmt == '%' )  // we have percent char -> the next character is a conversion.
        conv = true;
      else
        putc ( *fmt, stdout );
    }
    fmt ++;
  }
  va_end ( va );
}

int main ( int argc, char * argv [] )
{
  int          a = 123;
  const char * c = "test";

  // legal use
  myprintf ( "a = %d\n", a );
  myprintf ( "c = %s\n", c );

  // invalid use. The compiler, however, does not warn here.
  // Even gcc with -Wall -pedantic does not.
  myprintf ( "c = %d\n", c );
  myprintf ( "a = %s\n", a );

  return 0;
}

