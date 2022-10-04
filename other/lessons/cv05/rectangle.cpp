#include<stdio.h>

int error (void) {
    printf("Error.\n");
    return 0;
}

void print_row(int l) {
    while (l > 0) {
        printf("*");
        --l;
    }
}
void print_rectang (int h, int l)
{
    for (int i=0; i<h; ++i)
    {
        print_row(l);
        printf("\n");
    }
}
int main(void)
{
    int len, high;
    printf("What is the length and width of the rectangle you need?\n");
    if(scanf(" %d %d", &len, &high)!=2 || len <1 || high <1||getchar()!='\n') return error();
    print_rectang(high, len);
    return 0;
}