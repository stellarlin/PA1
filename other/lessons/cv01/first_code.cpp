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
else return c - 'a'+10;
}

char write_char(unsigned int n)
{
    if (n >=0 && n<=9) return (char)(n + '0');
    else return (char) (n +'A' -10);
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


unsigned int convert_decimal (char * n1, unsigned int b1, int * exit)
{
    unsigned int num=0, size = strlen(n1),z;
    for (unsigned int i = size; i>0; --i)
    {
        z=1;  long long tmp;
        unsigned int j = i-1;
        while (j>0)
        {
            z*=b1;
            j--;
        }
        tmp = (num+read_char(n1[i])*z);
        if( tmp >UINT_MAX || tmp <0)
        {*exit =1; return 0;}

        num+=read_char(n1[size-i])*z;
    }
return num;
}

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

char * convert_base (char * n2, unsigned int n1, unsigned int b2)
{
    int i = 0;
    while (n1 > 0) {
        n2[i] = write_char(n1 % b2);
        n1 /= b2;
        i++;
    }
    n2[i] = '\0';
    reverse(n2);
    return n2;
}
int main ()
{
    int exit = 0;
    unsigned  int b1, b2, num;
    char n1 [32], n2[32];
    printf("Zadejte cislo a dve bazi ve formatu: n1 b1 b2\n");
    if(scanf(" %s %u %u", n1, &b1, &b2)!=3
        || b1 >36 || b1<2
        || b2 >36 || b2<2
        || !isValid(n1,b1)) return error();
    num = convert_decimal(n1, b1, &exit);
    if(exit==1)return error();
    printf ("%s\n", convert_base(n2,num,b2));
    return 0;
}

