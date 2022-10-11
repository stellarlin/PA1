#include <cstdio>

int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}
void print_sign(int l, char c) {
    while (l > 0) {
        printf("%c", c);
        --l;
    }
}

int  count_dig(int n,  int count)
{
    if(!n) return count;
    count++;
    count = count_dig(n/10, count);
    return count;
}

void draw_head(int n)
{
    int count = 0, count_n = n*n;
    count = count_dig(count_n, count) +1;
    print_sign(count-1, ' ');
    printf("|");

    int i =n;

    while (i)
    {
        count_n=0;
        count_n=count - count_dig(i, count_n);
        print_sign(count_n, ' ');
        printf("%d", i);
        i--;
    }
    printf("\n");

    print_sign(count-1,'-');
    printf("+");
    print_sign(count*n,'-');
    printf("\n");
}
void tab (int n)
{
    int count = 0, count_n = n*n, num = 0;
    count = count_dig(count_n, count);
 for (int i = 1; i<=n; i++)
 {
     count_n = 0;
     count_n = count - count_dig(i, count_n);
     print_sign(count_n, ' ');
     printf("%d", i);
     printf("|");
     for(int j = n-i+1; j>0; j--)
     {
         num = i*(j+i-1);
         count_n = 0;
         count_n = count +1 - count_dig(num, count_n);
         print_sign(count_n, ' ');
         printf("%d", num);
     }
     printf("\n");
 }
}

int main (void)
{
    int n;
    printf("Rozsah:\n");
    if(scanf(" %d", &n)!=1 || n<1) return error();

    draw_head(n);
    tab (n);
    return 0;
}
