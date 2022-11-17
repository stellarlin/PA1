
#include<cstdio>
#include <ctype.h>
#include <cmath>
#include <climits>

#define MAX_SIZE 2000
#define SET_SIZE 100000000
char set_major[SET_SIZE], set_minor[SET_SIZE];

bool error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}
bool carry_int(int num, char c)
{
    return 10*num - INT_MAX +c -'0' <=0;
}
int read_seq (int * array, int * count)
{
    char c;
    int   sign;
    bool flag = true;
    while(1) {
        if((c=getchar())==EOF ||  *count>2000)break;
        sign =1;
        while (isspace(c))  c = getchar();
        if(c==EOF) break;
        while (!isspace(c) && c!=EOF) {
            if (c == '-' && array[*count] == 0) sign = -1;
            else if ((c < '0' || c > '9') || !carry_int(array[*count], c)) break;
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
void sum_seq(int * array, int from, int to, int *sum)
{
    *sum=0;
    for(int i=from; i<=to; i++)*sum+=array[i];
}
void find_set(int sum, char * set, int *res)
{
    if(sum >= SET_SIZE) return;
    if(set[sum]!=0)*res+=set[sum];
    set[sum]++;
}

int count_sum_interval(int * array, const int count, char * major, char * minor )
{
    int res = 0, sum = 0;
    for(int i=0; i<count-1; ++i)
    {
        for(int j = i+1; j<count; j++)
        {
            sum_seq(array, i, j, &sum);
            if(sum<0) find_set(abs(sum), minor, &res);
            else find_set(sum, major, &res);
        }
    }

    return res;
}


int main (void)
{
    int count=0;
    int array[MAX_SIZE];
    for (int i=0; i<SET_SIZE; i++) set_major[i]=0;
    for (int i=0; i<SET_SIZE; i++) set_minor[i]=0;
    printf ("Posloupnost:\n");
    if (!read_seq(array, &count)) return error();
    printf("Pocet dvojic: %d\n", count_sum_interval(array, count, set_major, set_minor));
    return 0;
}

