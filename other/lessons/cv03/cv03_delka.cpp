
#include <cstdio>
#include <cstring>
#include <cmath>

int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}

struct TIME
{
    int h;
    int m;
    int s;
    int ms;
    char  ms_c [3] = { };
};

void different( TIME a, TIME b, TIME *c)
{
    TIME carry = {0,0,0,0};
    if(a.ms > b.ms)
    {
        carry.ms=1;
        b.ms +=1000;
    }
    if(a.s > b.s)
    {
        carry.s=1;
        b.s+=60;
    }
    if(a.m > b.m)
    {
        carry.m=1;
        b.m+=60;
    }

    c->ms = b.ms - a.ms;
    c->s = b.s  - carry.ms - a.s;
    if(c->s <0)
    {
        carry.s+=1;
        c->s+=60;
    }
    c->m = b.m  - carry.s - a.m;
    if(c->m <0)
    {
        carry.m+=1;
        c->m+=60;
    }
    c -> h = b.h - a.h - carry.m;

}

int char_to_ms (char * ms_c)
{
    int ms=0;
    int len = strlen(ms_c);

    for (int i=0; i<len; i++)
    {
        if(ms_c[i]>'9' || ms_c[i]<'0') return -1;
        ms +=(ms_c[i]-'0')*pow(10, len-1-i);
    }
    switch (len)
    {
        case 1: ms *=100;
            break;
        case 2: ms *=10;
            break;
        case 3: break;
    }
    return ms;
}

int main(void)
{
    TIME t1; TIME t2; TIME diff;
    printf("Zadejte cas t1:\n");
    if ( scanf(" %d : %d : %d , %3s", &t1.h, &t1.m, &t1.s, t1.ms_c)!= 4
         || t1.h > 23 || t1.m > 59 || t1.s > 59 || (t1.ms = char_to_ms(t1.ms_c)) > 999
         || t1.h < 0 || t1.m < 0 || t1.s < 0 || t1.ms < 0
         || getchar()!='\n') return error();
    printf("Zadejte cas t2:\n");
    if ( scanf(" %d : %d : %d , %3s", &t2.h, &t2.m, &t2.s, t2.ms_c)!= 4
         || t2.h > 23 || t2.m > 59 || t2.s > 59 || (t2.ms = char_to_ms(t2.ms_c))>999
         || t2.h < 0 || t2.m < 0 || t2.s < 0 || t2.ms < 0
         || getchar()!='\n') return error();

    different(t1, t2, &diff);
    if(diff.h < 0|| diff.m <0 ||diff.s < 0 ||diff.ms <0) return error();
    else
    {
        printf("Doba: %2d:%.2d:%.2d,%.3d\n", diff.h, diff.m, diff.s, diff.ms);
    }

}
