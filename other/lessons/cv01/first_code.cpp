#include <cstdio>
#include <cstring>

int error () {
    printf("Nespravny vstup.\n");
    return 0;
}

//precte char, vrati ho jako decimalne cislo
unsigned int read_char (char c)
{
if (c>='0' && c <= '9') return c - '0';
if (c>='A' && c <= 'Z') return  c - 'A'+10;
else return c - 'a'+10;
}

//precte decimalne cislo a vrati cislice jako znak
char write_char(unsigned int n)
{
    if (n >=0 && n<=9) return (char)(n + '0');
    else return (char) (n +'A' -10);
}

//overeni jestli vsechny znaky jsou vhodne pro zvolenou bazi
//(jestli jsou v mod b1 nebo jestli jsou mezi a-b, A-B nebo 0-9)

bool isValid(char * n1, unsigned int b1)
{
    unsigned int num;
    while (*n1!='\0')
    {
        if (*n1<'0' || (*n1 >'9' && *n1<'A') || (*n1>'Z' && *n1<'a') || *n1 >'z') return false;
        num = read_char(*n1);
        if (num > b1) return false;
        n1++;
    }
    return true;
}

//prevede retez na decimalni hodnotu, kontrola preteceni UINT_MAX

unsigned int convert_decimal (char * n1, unsigned int b1, int * exit)
{
    unsigned int num=0, size = strlen(n1), poverOf,tmp;
    for (unsigned int i = size; i>0; --i)
    {
        poverOf=1;
        unsigned int j = i-1;
        while (j>0)
        {
            tmp = poverOf*b1;
            if (!tmp)
            {
                *exit =1;
                return 0;
            }
            poverOf*=b1;
            j--;
        }
        tmp = num + read_char(n1[size-i])*poverOf;
        if (!tmp)
        {
            *exit =1;
            return 0;
        }
        num+=read_char(n1[size-i])*poverOf;
    }
return num;
}

// prohodime prvky vysledku, aby dostat spravne poradi cislic
void reverse ( char * n2)
{
    unsigned int len= strlen(n2);
    unsigned int i;
    for (i = 0; i < len/2; i++)
    {
        char temp = n2[i];
        n2[i] = n2[len-i-1];
        n2[len-i-1] = temp;
    }
}

//prevedeme decimalne cislo na cislo v bazi b2, ulozim ho do retezu n2 a prohodim prvky

void convert_base (char * n2, unsigned int n1, unsigned int b2)
{
    int i = 0;
    if(n1==0)
    {
        n2[i]='0'; i++;
    }
    while (n1 > 0) {
        n2[i] = write_char(n1 % b2);
        n1 /= b2;
        i++;
    }
    n2[i] = '\0';
    reverse(n2);
}
int main ()
{
    int exit = 0; //flag chyby behem converze do decimalnich cisel
    unsigned  int b1, b2, num;
    char n1 [32], n2[32];

    printf("Zadejte cislo a dve bazi ve formatu: n1 b1 b2\n");
    if(scanf(" %s %u %u", n1, &b1, &b2)!=3
        || b1 >36 || b1<2
        || b2 >36 || b2<2
        || !isValid(n1,b1)) return error();
    num = convert_decimal(n1, b1, &exit);
    if(exit==1)return error();
    convert_base(n2,num,b2);
    printf ("%s\n", n2);
    return 0;
}

