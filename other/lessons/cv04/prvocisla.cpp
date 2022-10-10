#include<stdio.h>
#include <cmath>
int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}

bool isPrime(int n)
{
    for(int i=1; i<=(int)sqrt(n); i++)
    {
        if(n%i == 0 && i!=1 ) return false;
    }
    return true;
}

int sum_of (int a, int b)
{
    int sum = 0;
    if(a==b && isPrime(a)) return a;
    for(int i =a; i<=b; i++)
    {

        if(isPrime(i)) sum+=i;
    }
    return sum;
}
int main(void)
{
    int a, b;
    printf("Zadejte dva cisla:\n");
    if (scanf(" %d %d", &a, &b) != 2 || b < a || b<=0 || a<=0 || getchar() != '\n') return error();
    printf("Soucet prvocisel v intervalu [%d, %d] is %d", a, b, sum_of(a,b));
    return 0;
}