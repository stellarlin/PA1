#include <cstdio>

int error () {
    printf("Nespravny vstup.\n");
    return 0;
}
int main ()
{
    double a,b,c,d, e, f;
    double x, y;
    printf("Zadejte 2 rovnici ve formatu ax+by=c.\n");
    printf("Prvni rovnice:\n");
    if(scanf(" %lfx + %lfy = %lf", &a,&b,&c)!=3) return error();
    printf("Druha rovnice:\n");
    if(scanf(" %lfx + %lfy = %lf", &d,&e,&f)!=3
    || e*a - d*b ==0) return error();

    y = a*f - d*c;
    y/= (e*a-b*d);
    x = e*c - f*b;
    x/=(e*a-b*d);
    printf ("x = %.4f, y = %.4f", x,y);
    return 0;
}
