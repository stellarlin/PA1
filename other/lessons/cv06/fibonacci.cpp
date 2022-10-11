#include<cstdio>

int error (void) {
    printf("Error.\n");
    return 0;
}

void move_value (int * n, int * m)
{
    int tmp = *n + *m;
    *m = *n;
    *n = tmp;
}
int fibonacci(int n)
{
int val1 = 1, val2 = 1;
if (n==1 || n==2) return 1;
    for (int i=3; i<=n; i++)
    {
        move_value (&val1, &val2);
    }
    return val1;
}
int main (void)
{
    int n;
    printf("Fibonacci. Choose your n:\n");
    if (scanf(" %d", &n)!=1 || n <1 || getchar()!='\n')return error();
    printf("#%d member of fibonacci sequence is %d.\n", n, fibonacci(n));
    return 0;
}

