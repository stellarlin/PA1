#include<stdio.h>
int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}
void less_ten (int num);
void less_twenty( int num);
void less_hundred(int num);
void less_thousand(int num);
void less_10thousand (int num);

void itinerary(int num)
{
    if (num < 10) less_ten(num);
    else if (num < 20) less_twenty(num);
    else if (num< 100) less_hundred(num);
   else if (num< 1000) less_thousand(num);
   else less_10thousand(num);
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
    switch (num%10)
    {
        case 9:
        case 8:
        case 7:
        case 6:
        case 3:
        case 2: itinerary(num%10); printf("nact");
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
    switch (num/10) {
        case 9: printf("devadesat ");
            break;
        case 6:printf("sedesat ");
            break;
        case 5:
            printf("padesat ");
            break;

        case 8:
        case 7:
            itinerary(num/10);
            printf("desat ");
            break;

        case 3:
        case 4:
        case 2:
            itinerary(num/10);
            printf("cet ");
            break;
    }
    if(num%10 !=0) itinerary(num%10);
}

void less_thousand(int num)
{
    switch (num/100) {
        case 9:
        case 8:
        case 7:
        case 6:
        case 5:
            itinerary(num/100);
            printf(" set ");
            break;

        case 3:
        case 4:
            itinerary(num/100);
            printf(" sta ");
            break;

        case 2:
            printf("dve ste ");
            break;
        case 1:  printf("sto ");
            break;

    }
    if(num%10 !=0) itinerary(num%100);
}

void less_10thousand (int num)
{
    itinerary(num/1000);
    printf(" tisic ");
    itinerary(num%1000);

}
int main(void)
{
    int num;
    while(!feof(stdin)) {
        printf("Zadejte cislo od 0 do 9999:\n");
        if (scanf("%d", &num) != 1 || num < 0 || num > 9999 || getchar() != '\n') return error();

        itinerary(num);
        printf("\n\n");
    }
    return 0;
}

