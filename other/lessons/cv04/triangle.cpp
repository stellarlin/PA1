#include<stdio.h>
#include <cfloat>
#include <cmath>

int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}

int main (void) {
    double a, b, c;
    while(!feof(stdin)){
    printf("Zadejte délku stran a, b, c:\n");
    if (scanf(" %lf %lf %lf", &a, &b, &c) != 3
        || a <= 0 || b <= 0 || c <= 0
        || a > b + c || b > a + c || c > a + b
        || getchar() != '\n')
        return error();

    if (fabs(a - b) <= 100 * b * DBL_EPSILON && fabs(b - c) <= 100 * c * DBL_EPSILON &&
        fabs(a - c) <= 100 * c * DBL_EPSILON)
        printf("Trojúhelník je rovnostranný");
    else printf("Trojúhelník neni rovnostranný");

    if (fabs(a - b) <= 100 * b * DBL_EPSILON || fabs(b - c) <= 100 * c * DBL_EPSILON ||
        fabs(a - c) <= 100 * c * DBL_EPSILON)
        printf(",je rovnoramenný");
    else printf(",neni rovnoramenný");

    if (fabs(a * a + b * b - c * c) <= 100 * c * c * DBL_EPSILON) printf(",je pravoúhlý.\n");
    else printf(",neni pravoúhlý.\n");
    printf("\n");
}
   return 0;
}