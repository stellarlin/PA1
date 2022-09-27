#include<stdio.h>
int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}

int main(void)
{
    int n, m;
    while(!feof(stdin)) {
        printf("Zadejte cisla:\n");
        if (scanf(" %d %d", &n, &m) != 2 || getchar()!='\n')return error();
        printf ("n = %d, m = %d\n", n, m);
       if(n>=m) printf ("Sorted: %d, %d\n",n, m);
       else printf (" Sorted: %d, %d\n", m, n);
        printf ("Prumer: %f\n",1.0*(n+m)/2);
        int tmp = n;
        n=m;
        m=tmp;
        printf ("n = %d, m = %d\n", n, m);
    }
    return 0;
}

