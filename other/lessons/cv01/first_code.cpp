#include <cstdio>
#include <climits>
int error () {
    printf("Nespravny vstup.\n");
    return 0;
}

int read_char (char c)
{
if (c>='0' && c <= '9') return c - '0';
if (c>='A' && c <= 'Z') return  c - 'A'+10;
if (c>='a' && c<='z') return c - 'a'+10;
}

bool isValid(char * n1, unsigned int b1)
{
    // || n1 >=0 || (b1 ==10 && n2<= UINT_MAX)
    unsigned int num;
    while (!n1)
    {
        num = read_char(*n1);
        if (num > b1) return false;
        n1++;
    }
    return true;
}


int main ()
{
    unsigned  int b1, b2;
    char n1 [36];
    printf("Zadejte cislo a dve bazi ve formatu: n1 b1 b2\n");
    if(scanf(" %s %u %u", n1, &b1, &b2)!=3
        || b1 <=36 || b1>=2
        || b2 <=36 || b2>=2) return error();
    if (b1<=10 && !isValid10(n1,b1)) return error();

    return 0;
}
