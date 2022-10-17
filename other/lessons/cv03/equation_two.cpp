#include <cstdio>
#include <cmath>
#include <cfloat>

int error () {
    printf("Nespravny vstup.\n");
    return 0;
}
int not_exist() {
    printf("Reseni neexistuje.\n");
    return 0;
}
int infinity() {
    printf("Nekonecne mnoho reseni\n");
    return 0;
}
bool dbl_control (double num1, double num2)
{
    return fabs(num1) <= DBL_EPSILON * (num2);
}

void rovnice ()
int main ()
{
    double a,b,c,d, e, f;
    double x, y;
    printf("Zadejte 2 rovnici ve formatu ax+by=c.\n");
    printf("Prvni rovnice:\n");
    if(scanf(" %lf x + %lf y = %lf", &a,&b,&c)!=3) return error();

    printf("Druha rovnice:\n");
    if(scanf(" %lf x + %lf y = %lf", &d,&e,&f)!=3) return error();


    if((dbl_control(a, fabs(a) ) && dbl_control(b, fabs(b))
    && !dbl_control(c, fabs(c)))
    ||
    (dbl_control(d, fabs(d)) && dbl_control(e, fabs(e)) && !dbl_control(f, fabs(f)))
    ||
    (dbl_control(e*a - d*b,  fabs(e*a) + fabs(d*b)) && !dbl_control(a*f - d*c,  fabs(a*f) + fabs(d*c)))) return not_exist();
    else if (dbl_control (a, fabs(a)) && !dbl_control(a*f*b - c*a*e, fabs(a*f*b)+fabs(c*a*e)))  return not_exist();
    else if(dbl_control(e*a - d*b,  fabs(e*a) + fabs(d*b)) && dbl_control(a*f - d*c,  fabs(a*f) + fabs(d*c))) return infinity();

    if (a ==0 && d !=0) rovnice (d, e, f, a, b, c, &x, &y);
    else if (a!=0 && d==0) rovnice (a, b, c, d, e, f, &x, &y);
    else
    y = a*f - d*c;
    x = e*a - d*b;
    y/= (e*a-b*d);
    x = e*c - f*b;
    x/=(e*a-b*d);
    printf ("x = %.4f, y = %.4f", x,y);
    return 0;
}
