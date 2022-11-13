
#include<cstdio>

#define MAX_SIZE 100
bool error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}

void yes_or_not (bool result)
{
   result == 1  ? printf ("ano\n") : printf("ne\n");
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

bool horizontal_symmetry(int array[][MAX_SIZE], int * column, int * row) {

return 1;
}

bool vertical_symmetry(int array[][MAX_SIZE], int * column, int * row) {
    return 1;
}

bool center_symmetry(int array[][MAX_SIZE], int * column, int * row) {
    return 1;
}

int main (void)
{
    int column_size, row_size;
    int array[MAX_SIZE][MAX_SIZE];
    printf ("Matice:\n");
    if (!matrix_declaration(array, &column_size, &row_size)) return error();

    printf ("Symetrie podle horizontalni osy: ");
    yes_or_not(horizontal_symmetry(array, &column_size, &row_size));

    printf ("Symetrie podle vertikalni osy: ");
    yes_or_not(  vertical_symmetry(array, &column_size, &row_size));

    printf ("Symetrie podle stredu: ");
    yes_or_not( center_symmetry(array, &column_size, &row_size));
    return 0;
}
