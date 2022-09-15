//
// Created by София Прихач on 15.09.2022.
//

#include <cstdio>
#include <climits>
#include <cmath>

int error () {
    printf("Nespravny vstup.\n");
    return 0;
}

int main()
{
    int a =0, b = 0;
    unsigned int s;
    if(scanf("%d %d", &a, &b)!=2) return error();

    //--------------------------------------------//
    //sum//
    if ((a > 0 && b >0) )
    {
        s =abs(a)+abs(b);
        if ( s>INT_MAX) return error();
    }
    if ((a < 0 && b <0) )
    {
        s =abs(a)+abs(b);
        if ( s>abs(INT_MIN)) return error();
    }

    printf("%d + %d = %d\n", a, b, a+b);

    //--------------------------------------------//
    if ((a > 0 && b <0) )
    {
        s =abs(a)+abs(b);
        if ( s>INT_MAX) return error();
    }
    if ((a < 0 && b >0) )
    {
        s =abs(a)+abs(b);
        if ( s>abs(INT_MIN)) return error();
    }
    printf("%d - %d = %d\n", a, b, a-b);
    //--------------------------------------------//
    if (b==0)return error();
    printf("%d / %d = %d\n", a, b, a/b);
    int c = a % b;
    printf("%d %% %d = %d\n", a, b, c);
    return 0;
}
