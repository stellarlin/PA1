#include<stdio.h>
int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}
int main(void) {
    char h1, h2;
    while (!feof(stdin)) {
        printf("Zadejte vyber  dvou hracu:\n");
        if (scanf(" %c %c", &h1, &h2) != 2 || (h1 != 'K' && h1 != 'N' && h1 != 'P') ||
            (h2 != 'K' && h2 != 'N' && h2 != 'P') || getchar() != '\n')
            return error();
        if((h1=='K'&& h2=='N') || (h1=='N' && h2=='P')|| (h1=='P' && h2=='K'))printf ("Hrac 1 vyhral\n");
        else if((h1=='K'&& h2=='K') || (h1=='N' && h2=='N')|| (h1=='P' && h2=='P')) printf ("Nikdo nevyhral\n");
        else printf ("Hrac 2 vyhral\n");
    }
    return 0;
}
