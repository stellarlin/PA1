#include<cstdio>

int error (void) {
    printf("Error.\n");
    return 0;
}

void move_value (int * v1, int * v2, int * v3)
{
    int tmp = *v1 + *v2 + *v3;
    *v1 = *v2;
    *v2 = *v3;
    *v3 = tmp;
}
int tribonacci(int n)
{
    int val1 = 1, val2 = 1, val3 = 2;
    if (n==1 || n==2) return 1;
    else if (n==3) return 2;
    for (int i=4; i<=n; i++)
    {
        move_value (&val1, &val2, &val3);
    }
    return val3;
}
int main (void)
{
    int n;
    printf("Tribonacci. Choose your n:\n");
    if (scanf(" %d", &n)!=1 || n <1 || getchar()!='\n')return error();
    printf("#%d member of tribonacci sequence is %d.\n", n, tribonacci(n));
    return 0;
}

