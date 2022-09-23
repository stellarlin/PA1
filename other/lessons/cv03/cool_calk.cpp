//
// Created by София Прихач on 15.09.2022.
//

#include <cstdio>
#include <cmath>

int error () {
    printf("Nespravny vstup.\n");
    return 0;
}

void sum (double a, double b)
{
    printf(" %f + %f = %f", a,b, a+b);
}
void sub (double a, double b)
{
    printf("%f - %f = %f\n", a, b, a-b);
}

void divis (double a, double b)
{
    printf("%f / %f = %f\n", a, b, a/b);
}

void mod(double a, double b)
{
    double c = fmod(a,b);
    printf("%f %% %f = %f\n", a, b, c);
}

int main()
{
    double a =0, b = 0;
    char c;
    while(!feof(stdin)) {
        printf("Zadejte vyraz:\n");
        if (scanf("%lf %c %lf", &a, &c, &b) != 3
            || (c == '/' && b == 0) || (c == '%' && b == 0))
            return error();

        switch (c) {
            case '+':
                sum(a, b);
                break;
            case '-':
                sub(a, b);
                break;
            case '/':
                divis(a, b);
                break;
            case '%':
                mod(a, b);
                break;
        }
    }
    return 0;
}
