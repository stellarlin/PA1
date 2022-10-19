
#include <cstdio>
#include <cmath>
#include <cfloat>

bool isDec (double n)
{
 return fabs(n- (int)n) <= DBL_EPSILON*abs(int(n));
}

int error () {
    printf("Nespravny vstup.\n");
    return 0;
}

void print_res (double c)
{
    if (!isDec(c)) printf("%.1f\n", c);
    else printf("%d\n", int(c));
}


int main()
{
    double a =0, b = 0;
    char c;
    printf("Zadejte vzorec:\n");
    if (scanf(" %lf %c %lf =", &a, &c, &b) != 3
        || (c == '/' && b == 0) || (c == '%' && b == 0)|| getchar()!='\n')
        return error();

    switch (c) {
        case '+':
            print_res(a+b);
            break;
        case '-':
            print_res(a-b);
            break;
        case '*':
            print_res(a*b);
            break;
        case '/':
            print_res(floor(a/b));
            break;
        case '%':
            print_res(fmod(a,b));
            break;
        default: return error();
    }
    return 0;
}
