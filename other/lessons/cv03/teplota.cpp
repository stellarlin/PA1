#include <cstdio>

int error () {
    printf("Nespravny vstup.\n");
    return 0;
}

int main ()
{
    double temp = 0;
    if(scanf("%lf", &temp)!=1) return error();

    return 0;
}
