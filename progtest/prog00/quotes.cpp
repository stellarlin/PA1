#include<cstdio>
#include <cctype>

#define RANGE true
#define SYNTAX false

// Stop the program and show error message
int error (bool mode, const int number = 0) {
   mode ? printf("Neh mi'\n")
        : printf("Qih mi' %d\n", number);
    return 0;
}

void displaySentence (const int n)
{
    switch(n)
    {
        case 0: printf("Qapla'\n"
                       "noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n");
            break;
        case 1: printf("Qapla'\nbortaS bIr jablu'DI' reH QaQqu' nay'.\n");
            break;
        case 2: printf("Qapla'\n"
                       "Qu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n");
            break;
        case 3: printf("Qapla'\n"
                       "bISeH'eghlaH'be'chugh latlh Dara'laH'be'.\n");
            break;
        case 4: printf("Qapla'\n"
                       "qaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n");
            break;
        case 5: printf("Qapla'\n"
                       "Suvlu'taHvIS yapbe' HoS neH.\n");
            break;
        case 6: printf("Qapla'\n"
                       "Ha'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n");
            break;

        case 7: printf("Qapla'\n"
                       "Heghlu'meH QaQ jajvam.\n");
            break;

        case 8: printf("Qapla'\n"
                       "leghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n");
        default: break;
    }
}

bool isValid (const int n)
{
    return (n>=0 && n<9 );
}

bool isLineEnding (void)
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
    int n;
    printf("ml' nob:\n");
    //skipping leading zeroes. example: 00007 = 7
    do{
        if(scanf(" %1d", &n)!=1) return error(SYNTAX);
    } while(n == 0);

    if(!isValid(n) ) return error(RANGE, n); //if  number is more then 9 or less then 1, stop the program
                                                          // with range error message
    if(!isLineEnding()) return error (SYNTAX); // if after number of sentence there is another text, stop the program
                                                  // with  syntax error message

    displaySentence(n);
    return 0;
}