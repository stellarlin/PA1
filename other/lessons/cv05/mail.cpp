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

        print_row(h);
        printf("\n");
        print_row(2);
        print_space(h-4);
        print_row(2);
        printf("\n");
         for (int i=0; i<h; ++i) {
             if (h%2==0 &&  i>=h/2)
             {
                 if (i % 2 == 0) print_space(1);
                 else print_row(1);

             }
             else if (i % 2 == 0) print_row(1);
             else print_space(1);
         }
        printf("\n");
    for (int i=0; i<h; ++i) {
        if (h%2==0 && i==h/2-1) print_row(1);
        else if (i == 0 || i==h-1 || i==h/2) print_row(1);
        else print_space(1);
    }
        printf("\n");
         for (int i=0; i<h-5; ++i) {
            print_row(1);
            print_space(h - 2);
            print_row(1);
            printf("\n");
        }
    print_row(h);

    printf("\n");
}
int main(void)
{
    int  high;
    printf("What is the high of the triangle you need?\n");
    if(scanf(" %d", &high)!=1 || high <5||getchar()!='\n') return error();
    print_triang(high);
    return 0;
}