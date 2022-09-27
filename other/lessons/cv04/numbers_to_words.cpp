#include<stdio.h>
int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}

void less_ten (int num)
{
    switch (num)
    {
        case 9: printf("devet");
        break;
        case 8: printf("osm");
            break;
        case 7: printf("sedm");
            break;
        case 6: printf("sest");
            break;
        case 5: printf("pet");
            break;
        case 4: printf("ctyri");
            break;
        case 3: printf("tri");
            break;
        case 2: printf("dva");
            break;
        case 1: printf("jeden");
            break;
        case 0: printf("nula");
            break;
    }
}

void less_twenty( int num)
{
    num = num %10;
    switch (num)
    {
        case 9:
        case 8:
        case 7:
        case 6:
        case 3:
        case 2: less_ten(num); printf("nact");
            break;
        case 5: printf("patnact");
            break;
        case 4: printf("ctrnact");
            break;
        case 1: printf("jedenact");
            break;
        case 0: printf("deset");
            break;
    }
}

void less_hundred(int num)
{
    switch (num) {
        case 9: printf("devadesat");
            break;
        case 6:printf("sedesat");
            break;
        case 5:
            printf("padesat");
            break;

        case 8:
        case 7:
            less_ten(num);
            printf("desat");
            break;

        case 3:
        case 4:
        case 2:
            less_ten(num);
            printf("cet");
            break;
    }

}
int main(void)
{
    int num;
    while(!feof(stdin)) {
        printf("Zadejte cislo od 0 do 9999:\n");
        if (scanf("%d", &num) != 1 || num < 0 || num > 9999 || getchar() != '\n') return error();

        if (num < 10) less_ten(num);
        else if (num < 20 && num >= 10) less_twenty(num);
        else if (num<100 && num >20) less_hundred(num);
        printf("\n\n");
    }
    return 0;
}

