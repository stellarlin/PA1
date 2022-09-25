#include<stdio.h>
#include <cmath>
int error () {
    printf("Nespravny vstup.\n");
    return 0;
}

void trian(bool * flag )
{
    double a,b,c, per, half_per;
    printf("Vypocitani obsahu a obvodu trouhelniku zadaného délkou stran a, b, c:\n");
    if(scanf(" %lf %lf %lf", &a, &b, &c)!=3
       || a <=0 || b<=0 || c <= 0
       || a > b +c || b > a +c || c > a+b
       || getchar()!='\n')
    {
        error();
        *flag = false;
        return;
    }
    per=(a+b+c);
    half_per=(double)per/2;
    printf("obvod trouhelniku = %.3lf\n", per);
    printf("obsah trouhelniku = %.5lf\n", sqrt(half_per*(half_per -a)*(half_per-b)*(half_per-c)));

}

void rectang (bool *flag)
{
    double a,b;
    printf("Vypocitani obsahu a obvodu obdélníku zadaného délkou stran a, b:\n");
    if(scanf(" %lf %lf", &a, &b)!=2
       || a <=0 || b<=0|| getchar()!='\n')
    {
        error();
        *flag = false;
        return;
    }
    printf("obvod obdelniku = %.3lf\n", 2*a+2*b);
    printf("obsah obdelniku = %.3lf\n", a*b);
}

void parallel(bool * flag)
{
    double a,b, alpha;
    printf("Vypocitani obsahu a obvodu rovnoběžníku zadaného délkou stran a, b a jejich úhlem alpha:\n");
    if(scanf("%lf %lf %lf", &a, &b, &alpha)!=3 || a <=0 || b<=0
       || alpha < 0 || alpha >=180 || getchar()!='\n')
    {
        error();
        *flag = false;
        return;
    }
    printf("obvod obdelniku = %.3lf\n", 2*a+2*b);
    double tmp=a, h;
    a < b ?  a = b, b = tmp : a;
    h = b*sin(alpha* ( M_PI / 180.0 ));
    printf("obsah = %.3lf\n", a*h);

}

void circle(bool * flag)
{
    double d;
    printf("Vypocitani obsahu a obvodu kruhu zadaného průměrem d:\n");
    if(scanf("%lf", &d)!=1 || d <=0  || getchar()!='\n')
    {
        error();
        *flag = false;
        return;
    }
    printf("obvod kruhu = %.3lf\n", M_PI*d);
    printf("obsah = %.3lf\n", (double)M_PI*d*d/4);


}

int main(void)
{

    bool flag = true;
    char it;

    while(!feof(stdin)) {
        printf("Vyberte figuru pro vypocet:\n 'o' -> obdelnik \n 't' -> trouhelnik \n 'r' -> rovnobeznik \n 'k' -> kruh \n");
        if (scanf(" %c", &it) != 1 || (it != 'o' && it != 't' && it != 'r' && it != 'k')) return error();

        switch (it) {
            case 't':
                trian(&flag);
                break;
            case 'o':
                rectang(&flag);
                break;
            case 'r': parallel(&flag);
                break;
            case 'k': circle(&flag);
                break;

        }
        if (!flag) return error();
        flag = true;
        printf("\n");
    }

}
