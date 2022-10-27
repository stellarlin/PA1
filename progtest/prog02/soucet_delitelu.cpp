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


void prime_sum_description (int a, int b, char c)
{
    int count= 0;
    for(int i =a; i<=b; i++)
    {
      if(isPrime(sum(i)))
      {
        count++;
        if ( c == '?') printf("%d\n", i);
    }
    }
    printf("Celkem: %d\n", count);
}

int main(void) {
     int a = 0, b = 0;
    char c = 0;

    //   for(int i=0; i<=MAX_NUM; i++) array_prime[i]=0;

    printf("Intervaly:\n");
    while (1) {
        if (scanf(" %c %d %d", &c, &a, &b) != 3
            || b < a || b <= 0 || a <= 0
            || (c != '?' && c != '#'))break;
        prime_sum_description(a, b, c);
    }
    if (!feof(stdin)|| c==0 || a ==0 || b ==0) return error();
        return 0;
}