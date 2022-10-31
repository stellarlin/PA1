
#include<cstdio>
#include <cmath>
#include <cstring>

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
      if(getchar()!='\n')return 0;

    }
    return 1;
}

/*void print_matrix  (int array[][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf(" %d", array[j][i]);
        }
        printf ("\n");
    }
}
 */

void int_to_char(int num,char * s, int * i )
{
    if(num<10)
    {
        s[*i]=num+'0';
        ++*i;
        return;
    }
    while (num!=0)
    {
        int j=num;
        while(j>=10)
        {
            j = j/10;
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
    if(size==1)
    {
        int_to_char(array[0][0], s, &index);
        s[index]='\0';
        return;
    }
    for ( i =0; i<size-1; i++)
    {
        for (j = 0; j <size-i; j++) int_to_char(array[j][i], s, &index);
        for(j=i+1; j<size-i; j++) int_to_char(array[size-i-1][j], s, &index);
        for (j=size-i-2; j>i; j--)  int_to_char(array[j][size-i-1], s, &index);
        for (j=size-i-1; j>i+1; j--)  int_to_char(array[i][j], s, &index);
    }
    s[index]='\0';
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
  //  print_matrix(array, size);
    printf(" %s ", s);
    printf("\n");
    return 0;
}