#include<stdio.h>
#include <cmath>
#include <climits>

#define MAX_SUM 1300000

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
int sum_divider(int n)
{
    int sum=1;
    for(int i=1; i<=(int)sqrt(n); i++)
    {
        if(n%i == 0 && i!=1)
        {
            if( i== n/i) sum+=i;
            else sum += i + n/i;
        }
    }
    return sum;
}


void change_set( char * set, int pmax, int ind)
{
    int p = ind;
    set[p] = '0';

    if (p>=INT_MAX/p) return;

    for(int i = p*p; i<pmax; i+=p) set[i] = '0';
}
void prime_sum_interval (int a, int b, char c, char * set)
{
    int count = 0;
    int sum;
    int max=MAX_SUM-1;
    for (int j = b; j < MAX_SUM; j++)
    {
        if(isPrime(sum_divider(j)))
        {
            max = j;
            break;
        }
    }
    for(int i =a; i<=b; i++)
    {
        sum = sum_divider(i);
        if (sum >=MAX_SUM) continue;
        if (set[sum]=='0') continue;
        if(isPrime(sum))
        {
            count++;
            if(c == '?') printf("%d\n", i);
        }
        else change_set(set, max, sum);
    }
    printf("Celkem: %d\n", count);

}

void initial_set (char * set)
{
    for(int i=0; i<MAX_SUM; i++) set[i]='1'; // vsichni soucty muzou byt prvocilem
    set[1] = '0'; //1 neni prvocislo
}

int main(void) {
    int a = 0, b = 0; // hranice intervalu
    char c = 0; // ? nebo #

    char set[MAX_SUM]; // pole 0 a 1 kde 0 = neni prvocislo 1 = prvocislo, index prvku je cislem
    initial_set(set);

    printf("Intervaly:\n");
    while (1) {
        if (scanf(" %c %d %d", &c, &a, &b) != 3
            || b < a || b <= 0 || a <= 0
            || (c != '?' && c != '#'))break;
        prime_sum_interval(a, b, c, set);
    }
    if (!feof(stdin)|| c==0 || a ==0 || b ==0) return error();
    return 0;
}
