
#include<cstdio>
#include <ctype.h>
#define MAX_SIZE 2000
bool error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}

void yes_or_not (bool result)
{
    result == 1  ? printf ("ano\n") : printf("ne\n");
}

int array_declaration (int * array, int * count)
{
    char c = getchar();
    int i, j = 0, sign;
    bool flag = 1;
    while(1) {
        i = 0;
        while (1) {
            sign =1;
            while (isspace(c))  c = getchar();
            while (!isspace(c)) {
                if (c == '-' && array[i] == 0) sign = -1;
                else if ((c < '0' || c > '9')) break;
                else array[i] = array[i] * 10 + c - '0';
                c = getchar();
            }
            if(!isspace(c))break;
            array[i] *= sign;
            i++;
            ++*count;
            c = getchar();
        }
        if(c==EOF) break;
        if( )
        c = getchar();
    }
    if(!feof(stdin) ||  flag != 1 || *count == 0 ) return 0;
    return 1;
}

int main (void)
{
    int count=0;
    int array[MAX_SIZE];
    printf ("Matice:\n");
    if (!array_declaration(array, &count)) return error();

    return 0;
}
