#include<stdio.h>
#include <cmath>
int error () {
    printf("Nespravny vstup.\n");
    return 0;
}

void cube(bool * flag)
{
    double a,b,c;
    printf("Vypocitani povrchu a objemu kvadru zadaného délkou hran a, b, c:\n");
    if(scanf(" %lf %lf %lf", &a, &b, &c)!=3
       || a <=0 || b<=0 || c <= 0
       || getchar()!='\n')
    {
        error();
        *flag = false;
        return;
    }
    printf("povrh kvadru = %.3lf\n", 2*(a*b+b*c+a*c));
    printf("objem kvadru = %.3lf\n", a*b*c);
}

void prism (bool * flag)
{
    double a,b,c, v, ob;
    printf("Vypocitani povrchu a objemu tribokeho hranolu zadaneho trojuhelníkem a výškou v:\n");
    if(scanf(" %lf %lf %lf %lf", &a, &b, &c, &v)!=4
       || a <=0 || b<=0 || c <= 0 || v<=0
       || a > b +c || b > a +c || c > a+b
       || getchar()!='\n')
    {
        error();
        *flag = false;
        return;
    }
    ob = 0.25*v*sqrt(2*(a*a*b*b)+2*(a*a*c*c)+2*(b*b*c*c)-a*a*a*a-b*b*b*b-c*c*c*c);
    printf("povrh tribokeho hranolu = %.3lf\n", v * (2*a + b + c));
    printf("objem tribokeho hranolu = %.5lf\n", ob);
}

void cole(bool * flag)
{
    double d, v;
    printf("Vypocitani povrchu a objemu kuzelu zadaneho prumerem d a vyskou v:\n");
    if(scanf(" %lf %lf", &d, &v)!=2
       || d<=0 || v<=0
       || getchar()!='\n')
    {
        error();
        *flag = false;
        return;
    }

    printf("povrh kuzelu = %.3lf\n", sqrt(d*d/4 + v*v));
    printf("objem kuzelu = %.5lf\n", M_PI*d*d*v/12);

}

void ball(bool * flag)
{
    double d;
    printf("Vypocitani povrchu a objemu koule o prumeru d:\n");
    if(scanf(" %lf", &d)!=1
       || d<=0
       || getchar()!='\n')
    {
        error();
        *flag = false;
        return;
    }
    printf("povrh koule = %.3lf\n", M_PI*d*d);
    printf("objem koule = %.5lf\n", M_PI*d*d*d/6);
}
int main(void)
{

    bool flag = true;
    char  it;

    while(!feof(stdin)) {
        printf("Vyberte figuru pro vypocet:\n 'k' -> kvadr \n 't' -> triboky hranol \n 'u' -> kuzel \n 'o' -> koule \n");
        if (scanf(" %c", &it) != 1 || (it != 'k' && it != 't' && it != 'u' && it != 'o')) return error();


        switch (it) {
            case 'k':
                cube(&flag);
                break;
            case 't':
                prism(&flag);
                break;
            case 'u': cole(&flag);
                break;
            case 'o': ball(&flag);
                break;

        }
        if (!flag) return error();
        flag = true;
        printf("\n");
    }

}
