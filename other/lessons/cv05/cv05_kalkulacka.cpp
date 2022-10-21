
#include <cstdio>
#include <cmath>
#include <cfloat>
#include <ctype.h>


bool isDec (double n)
{
  return  fabs(n- floor(n)) <= DBL_EPSILON*100*fabs(floor(n));
}

bool isWhite (void)
{
    char c;
    while ((c = getchar())!='\n')
    {
        if(!isspace(c)) return false;
    }
    return true;
}

int error () {
    printf("Nespravny vstup.\n");
    return 0;
}

void print_res (double a , double b,  double c)
{
    if (a > 1000000 || b > 1000000)printf("%.3g\n", c);
    else if (isDec(c))printf("%.f\n", c);
    else  printf("%.1f\n", c);
}


int main()
{
    double a =0, b = 0;
    char c;
    printf("Zadejte vzorec:\n");
    if (scanf(" %lf %c %lf =", &a, &c, &b) != 3
        || (c == '/' && b == 0) || (c == '%' && b == 0)|| !isWhite())
        return error();

    switch (c) {
        case '+':
            print_res(a, b, a+b);
            break;
        case '-':
            print_res(a, b, a-b);
            break;
        case '*':
            print_res(a, b, a*b);
            break;
        case '/':
            print_res(a,b, trunc(a/b));;
            break;
        case '%':
            print_res(a, b, fmod(a,b));
            break;
        default: return error();
    }
    return 0;
}
