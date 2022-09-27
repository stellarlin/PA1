
#include<stdio.h>
int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}
int main(void)
{
    int n;
    while(!feof(stdin)) {
        printf("Zadejte cidlo dnu:\n");
        if (scanf(" %d", &n) != 1 || n >7 || n<1 || getchar()!='\n')return error();
        printf ("Dnes je ");
        switch(n) {
            case 1:
                printf("Pondeli.\n");
                break;
            case 2:
                printf("Utery.\n");
                break;
            case 3:
                printf("Streda.\n");
                break;
            case 4:
                printf("Ctvrtek.\n");
                break;
            case 5:
                printf("Patek.\n");
                break;
            case 6:
                printf("Sobota.\n");
                break;
            case 7:
                printf("Nedele.\n");
                break;
        }
    }
    return 0;
}