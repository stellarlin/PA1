#include<cstdio>
#include <cctype>

enum modes {RANGE, NAN, SYNTAX};

// Stop the program and show error message
int error (const modes mode, const int number = 0) {
   switch(mode) {
       case NAN:
           printf("Neh mi'\n");
           break;
       case RANGE:
           printf("Qih mi' %d\n", number);
           break;
       case SYNTAX:
           printf("bIjatlh 'e' yImev\n");
   }
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
    int n = -1;
    printf("ml' nob:\n");

    if(scanf(" %d", &n)!=1) return error(NAN);

    if(!isValid(n) ) return error(RANGE, n); //if  number is more than 9 or less than 1, stop the program
    // with range error message
    if(!isLineEnding()) return error (SYNTAX); // if after number of sentence there is another text, stop the program
    // with  syntax error message

    displaySentence(n);

    return 0;
}
