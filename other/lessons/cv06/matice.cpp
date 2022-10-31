
#include<cstdio>
#include <cmath>
#define MAX_SIZE 50
#define MAX_CHAR 2500
int error (void) {
    printf("Error.\n");
    return 0;
}


int matrix_declaration (int array[][MAX_SIZE], int size)
{
    for(int i = 0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            if(scanf(" %d", &array[j][i])!=1) return 0;
        }
        if(getchar()!='\n') return 0;
    }
    return 1;
}

void int_to_char(int num,char * s, int * i )
{
    if(num<10)
    {
        s[*i]=num+'0';
        return;
    }
    while (num!=0)
    {
        int j=10;
        while(j>=10)
        {
            j = num/10;
        }
        s[*i]='0'+j;
        num=num/10;
        ++*i;
    }
}
void read_matrix (int array[][MAX_SIZE], int size, char * s)
{
    int index = 0;
    int i, j;
    for ( i =0; i<size; i++)
    {
        for (j = 0; j <size-i; j++)
        {
            int_to_char(array[j][i], s, &index);
        }
        for(j=i+1; j<size-i; j++)
        {
            int_to_char(array[j][size-i], s, &index);
            s[index]=;
            index++;
        }
        for (j=size-i; j>i; j--)
        {
            s[index]=array[size-i][j];
            index++;
        }
        for (j=size-i; j>i; j--)
        {
            s[index]=array[j][i];
            index++;
        }
    }
}

int main (void)
{
    int size = 0;
    char s [MAX_CHAR];
    int array[MAX_SIZE][MAX_SIZE];
    printf ("Zadejte velikost matici:\n");
    if(scanf(" %d", &size)!=1
    || size <1 || size > MAX_SIZE
    || getchar()!='\n') return error();
    printf ("Zadejte matici:\n");
    if (!matrix_declaration(array, size)) return error();
    read_matrix(array, size, s);

    return 0;
}