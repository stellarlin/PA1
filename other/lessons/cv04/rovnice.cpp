#include<stdio.h>
#include <cfloat>
#include <cmath>

int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}

void rovnice (double top, double bottom, double D)
{
    double res1, res2;
    res1=(top+sqrt(D))/bottom;
    res2=(top-sqrt(D))/bottom;
    printf("x1 = %.2f, x2 = %.2f", res1,res2);
}

int main(void)
{
    double a,b,c,d,e,f;
    while(!feof(stdin)) {
        printf("Zadejte kvadratickou rovnici ve tvaru a x^2 + b x + c = d x^2 + e x + f:\n");
        if (scanf(" %lf x^2 + %lf x + %lf = %lf x^2 + %lf x + %lf", &a, &b, &c, &d, &e, &f) != 6) return error();
        if (fabs(b * b - 2 * b * e + e * e - 4 * (a - d) * (c - f)) <= 100 * 4 * (a - d) * (c - f) * DBL_EPSILON)
            printf("x=%.f.\n", (e - b) / 2 * (a - d));
        else if (b * b - 2 * b * e + e * e - 4 * (a - d) * (c - f) > 100 * 4 * (a - d) * (c - f) * DBL_EPSILON)
            rovnice(e - b, 2 * (a - d), b * b - 2 * b * e + e * e - 4 * (a - d) * (c - f));
        else printf("Neexistuje reseni v R. Zadejte jinou hodnotu\n");
    }
    return 0;
}

