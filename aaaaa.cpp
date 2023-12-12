
#include <stdio.h>

int rec ( int x )
{
    if ( x == 0 ) return 0;
    return rec ( x < 0 ? x + 1 : x - 1 ) - 1;
}

int main ()
{
    int r = 0;
    int N = 100;
    for ( int i = N; i > 0; i /= 5 )
        r++;
    printf ("%d\n", r);
}