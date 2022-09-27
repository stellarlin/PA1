#include<stdio.h>
int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}
int main(void) {
    unsigned int n;
    while (!feof(stdin)) {
        printf("Zadejte cidlo roku:\n");
        if (scanf(" %u", &n) != 1 || n < 1584 || getchar() != '\n') return error();

        if ((n % 4 == 0 && n % 100 != 0) || (n % 4 == 0 && n % 400 == 0)) printf("Rok je prestupny.\n");
        else printf("Rok neni prestupny.\n\n");

    }
    return 0;
}
