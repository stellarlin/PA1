#include<stdio.h>
#include <cmath>
int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}

int main(void)
{
    int n;
    while(!feof(stdin)) {
        printf("Zadejte cislo:\n");
        if (scanf(" %d", &n) != 1)return error();
        if (n % 2 == 0) printf("Cislo je sude");
        else printf("Cislo je liche");

        if (n > 0) printf(",kladne.\n");
        else if (n == 0) printf(",je 0.\n");
        else printf(",zaporne.\n");
        return 0;
    }
}

