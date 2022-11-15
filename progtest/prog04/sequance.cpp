
#include<cstdio>
#include <ctype.h>
#define MAX_SIZE 2000
#define SET_SIZE 1000000

int count_sum_interval(char * major, char * minor, int count)
{
    int res = 0;
    return res;
}
bool error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}

int read_seq (int * array, int * count)
{
    char c;
    int   sign;
    bool flag = true;
    while(1) {
        if((c=getchar())==EOF || *count>2000)break;
            sign =1;
            while (isspace(c))  c = getchar();
            while (!isspace(c) && c!=EOF) {
                if (c == '-' && array[*count] == 0) sign = -1;
                else if ((c < '0' || c > '9')) break;
                else array[*count] = array[*count] * 10 + c - '0';
                c = getchar();
            }
            if(!isspace(c) && c!=EOF)
            {
                flag=false;
                break;
            }
            array[*count] *= sign;
            ++*count;
        }
    if(!feof(stdin) || !flag || *count == 0|| *count>2000 ) return 0;
    return 1;
}

int main (void)
{
    int count=0;
    int array[MAX_SIZE];
    char set_major[SET_SIZE], set_minor[SET_SIZE];
    printf ("Posloupnost:\n");
    if (!read_seq(array, &count)) return error();
    printf("%d\n", count_sum_interval(set_major, set_minor, count));
    return 0;
}

