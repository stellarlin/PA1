#include<stdio.h>
#include <cmath>
int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}
bool isPrime(int n)
{
    if (n==1) return false;
    for(int i=1; i<=(int)sqrt(n); i++)
    {
        if(n%i == 0 && i!=1 ) return false;
    }
    return true;
}
int sum(int n)
{
    int sum=1;
    for(int i=1; i<=n/2; i++)
    {
        if(n%i == 0 && i!=1) sum+=i;
    }
    return sum;
}


void prime_sum_description (int a, int b)
{
    int count = 0;
    for(int i =a; i<=b; i++)
    {
        if(isPrime(sum(i)))
        {
            printf("%d\n", i);
            count ++;
        }
    }
    printf("Celkem: %d\n", count);
}
void prime_sum_count (int a, int b)
{
    int count = 0;
    for(int i =a; i<=b; i++)
    {
        if(isPrime(sum(i))) count++;
    }
    printf("Celkem: %d\n", count);
}

int main(void)
{
    int a, b;
    char c;
    printf("Intervaly:\n");
    while (!feof(stdin)) {
        if (scanf(" %c %d %d", &c, &a, &b) != 3
            || b < a || b <= 0 || a <= 0
            || (c != '?' && c != '#')
            || getchar() != '\n')
            return error();
       switch (c)
       {
           case '?': prime_sum_description(a, b);
           break;
           case '#': prime_sum_count(a, b);
       }
    }
    return 0;
}