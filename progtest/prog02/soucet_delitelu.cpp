#include<stdio.h>
#include <cmath>

#define MAX_NUM 2000000
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
void prime_sum_count (  int a,  int b, int * array)
{
    int count = 0;
    for( int i =a; i<=b; i++)
    {
        if(array[i] == 1) count ++;
    }
    printf("Celkem: %d\n", count);
}


void prime_sum_description (int a, int b, char c,  int * array)
{
    for(int i =a; i<=b; i++)
    {
      if (array[i]==1) continue;
      if(isPrime(sum(i)))
      {
        array[i] = 1;
        if ( c == '?') printf("%d\n", i);
    }
    }
    prime_sum_count(a, b, array);
}

int main(void) {
     int a = 0, b = 0;
    char c = 0;
   int array_prime[MAX_NUM + 1] ;

    //   for(int i=0; i<=MAX_NUM; i++) array_prime[i]=0;

    printf("Intervaly:\n");
    while (1) {
        if (scanf(" %c %d %d", &c, &a, &b) != 3
            || b < a || b <= 0 || a <= 0
            || (c != '?' && c != '#'))break;
        prime_sum_description(a, b, c, array_prime);
    }
    if (!feof(stdin)|| c==0 || a ==0 || b ==0) return error();
        return 0;
}