#include<stdio.h>
#include <cfloat>
#include <cmath>

int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}

void rovnice (double top, double bottom, double D, char z)
{
    double res1, res2;
    res1=(top+sqrt(D))/bottom;
    res2=(top-sqrt(D))/bottom;
    printf("%c1 = %.2f, %c2 = %.2f\n", z, res1, z, res2);
}

int main(void)
{
    double a,b,c,d,e,f;
    char z1, z2, z3, z4;
    while(!feof(stdin)) {
        printf("Zadejte kvadratickou rovnici ve tvaru a x^2 + b x + c = d x^2 + e x + f:\n");
        if (scanf(" %lf %c^2 + %lf %c + %lf = %lf %c^2 + %lf %c + %lf", &a, &z1, &b, &z2, &c, &d, &z3, &e, &z4, &f) != 10
            || z1!=z2 || z1!=z3 || z1!=z4 || z2!=z3 || z2!=z4 || z3!=z4 ||getchar()!='\n') return error();
        if(z1<'A' || (z1>'Z' && z1<'a') || z1>'z') return error();

        if (fabs(b * b - 2 * b * e + e * e - 4 * (a - d) * (c - f)) <= 100 *  2 * b * e*4 * (a - d) * (c - f) * DBL_EPSILON)
            printf("%c=%.f.\n", z1, (e - b) / 2 * (a - d));
        else if (b * b - 2 * b * e + e * e - 4 * (a - d) * (c - f) > 100 *  2 * b * e * 4 * (a - d) * (c - f) * DBL_EPSILON)
            rovnice(e - b, 2 * (a - d), b * b - 2 * b * e + e * e - 4 * (a - d) * (c - f),z1);
        else printf("Neexistuje reseni v R. Zadejte jinou hodnotu\n");
        printf("\n");
    }
    return 0;
}

