#include <cstdio>
#include <climits>
#include <cstring>

int error () {
    printf("Nespravny vstup.\n");
    return 0;
}

int read_char (char c)
{
if (c>='0' && c <= '9') return c - '0';
if (c>='A' && c <= 'Z') return  c - 'A'+10;
if (c>='a' && c<='z') return c - 'a'+10;
return 0;
}

bool isValid(char * n1, unsigned int b1)
{
    // || n1 >=0 || (b1 ==10 && n2<= UINT_MAX)
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


unsigned int convert_decimal (char * n1, unsigned int b1)
{
    unsigned int num=0, size = strlen(n1), z =1;
    for (int i =  size-1; i>=0; --i)
    {
        z=1;
        int j = i;
        while (j>=0)
        {
            if(j==0) break;
            z*=b1;
            j--;
        }
        num+=read_char(n1[i])*z;
    }
return num;
}

int main ()
{
    unsigned  int b1, b2;
    char n1 [32];
    printf("Zadejte cislo a dve bazi ve formatu: n1 b1 b2\n");
    if(scanf(" %s %u %u", n1, &b1, &b2)!=3
        || b1 >36 || b1<2
        || b2 >36 || b2<2
        || !isValid(n1,b1)) return error();
    printf("%d\n", convert_decimal(n1, b1));

    return 0;
}

