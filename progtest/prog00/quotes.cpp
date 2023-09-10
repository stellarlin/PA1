#include<cstdio>
#include <cctype>

// Stop the program and show error message
int error (void) {
    printf("luj\n");
    return 0;
}

// show the sentence with number 1-9
bool sentence (const int n)
{
    switch(n)
    {
        case 1: printf("Qapla'\n"
                       "noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n");
            break;
        case 2: printf("Qapla'\nbortaS bIr jablu'DI' reH QaQqu' nay'.\n");
            break;
        case 3: printf("Qapla'\n"
                       "Qu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n");
            break;
        case 4: printf("Qapla'\n"
                       "bISeH'eghlaH'be'chugh latlh Dara'laH'be'.\n");
            break;
        case 5: printf("Qapla'\n"
                       "qaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n");
            break;
        case 6: printf("Qapla'\n"
                       "Suvlu'taHvIS yapbe' HoS neH.\n");
            break;
        case 7: printf("Qapla'\n"
                       "Ha'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n");
            break;

        case 8: printf("Qapla'\n"
                       "Heghlu'meH QaQ jajvam.\n");
            break;

        case 9: printf("Qapla'\n"
                       "leghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n");
        default: return false;
    }
    return true;
}

bool isWhite (void)
{
    char c;
    while ((c = getchar())!=EOF )
    {
        if(!isspace(c)) return false;
    }
    return true;
}

int main(void)
{
    double n;
    // future loop base
    printf("ml' nob:\n");
    if(scanf(" %lf", &n)!=1 // input has less then ome correct integer
       || !isWhite() // after number of sentence there is another text
       || !sentence(n) // number is more then 9 or less then 1
       ) return error();
    return 0;
}


