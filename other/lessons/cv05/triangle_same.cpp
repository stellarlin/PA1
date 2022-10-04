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
void print_space (int l)
{
    while (l > 0) {
        printf(" ");
        --l;
    }
}
void print_triang (int h)
{
    for (int i=0; i<h; ++i)
    {
        print_space(h-1-i);
        print_row(2*i+1);
        print_space(h-1-i);
        printf("\n");
    }
}
int main(void)
{
    int  high;
    printf("What is the high of the triangle you need?\n");
    if(scanf(" %d", &high)!=1 || high <2||getchar()!='\n') return error();
    print_triang(high);
    return 0;
}