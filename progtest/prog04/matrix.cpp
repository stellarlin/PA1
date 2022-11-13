
#include<cstdio>

#define MAX_SIZE 100
bool error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}


int matrix_declaration (int array[][MAX_SIZE], int * column, int * row)
{
    char c = getchar();
    int i, j = 0, sign;
    bool flag = 1;
    while(1) {
        i = 0;
        while (1) {
            sign =1;
            while (c == ' ' || c == '\t')  c = getchar();
            while (c != ' ' && c != '\t') {
                if (c == '-' && array[j][i] == 0) sign = -1;
                else if (c=='\n') break;
                else if ((c < '0' || c > '9')) break;
                else array[j][i] = array[j][i] * 10 + c - '0';
                c = getchar();
            }
            if(c!=' ' && c!= '\t' && c!='\n')break;
            array[j][i] *= sign;
            i++;
            if (j == 0) ++*column;
            if(c == '\n' || (j!=0 && i>*column)) break;
            c = getchar();
        }
        if(c==EOF) break;
        if((c!='\n' )|| i!=*column)
        {
            flag=0;
            break;
        }
        ++j;
        ++*row;
        c = getchar();
    }
    if(!feof(stdin) ||  flag != 1 || *column ==0 || *row ==0 || *column >100 || *row >100) return 0;
    return 1;
}

/*
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
*/
int main (void)
{
    int column_size, row_size;
    int array[MAX_SIZE][MAX_SIZE];
    printf ("Matice:\n");
    if (!matrix_declaration(array, &column_size, &row_size)) return error();
    return 0;
}
