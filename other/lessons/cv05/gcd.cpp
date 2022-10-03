#include<stdio.h>

int error (void) {
    printf("Error.\n");
    return 0;
}
void reverse ( int * m, int * n)
{
    int tmp;
    tmp = *m;
    *m=*n;
    *n=tmp;
}
int naive_gcd(int n, int m)
{
if (n<m) reverse(&n,&m);
for(int i = m; i>0; i--)
{
    if ( n%i == 0 && m%i ==0) return i;
}
    return 1;

}
int gcd (int *n, int * m)
{
    if (*n<*m) reverse(&*n,&*m);
    if (*m == 0)
        return *n;
    int tmp =*n - *m;
    return gcd(&tmp, &*m);
}
int sub_gcd(int n, int  m) {
    return gcd ( &n, &m);
}
int mod_gcd(int n, int m) {

    if (n == 0)
        return m;
    return mod_gcd(n % m, n);
}


int main (void)
{
        char c;
        int n1, n2, gcd;
        bool flag=false;
        while (!flag) {
            printf("Choose your input method, and two numbers: \"c n1 n2\"\n"
                   "N - naive\n"
                   "E - euclid algorithm using sub \n"
                   "M - uclid algorithm using mod \n");

            if (scanf(" %c %d %d", &c, &n1, &n2) == 3
                && (c == 'N' || c == 'M' || c == 'E')
                && n1>0 && n2>0
                && getchar() == '\n')
                flag = true;
            if (!flag) {
                printf("Incorrect. Try again.\n\n");
                while ((c = getchar()) != '\n') {}
            }
        }

        switch (c) {
            case 'N':
                gcd = naive_gcd(n1,n2);
                break;
            case 'E':
                gcd = sub_gcd(n1, n2);
                break;
            case 'M':
                gcd = mod_gcd(n1,n2);

        }
        printf ("GCD of %d and %d is %d.\n", n1,n2, gcd);
    return 0;
}

