#include<stdio.h>

int error (void) {
    printf("Error.\n");
    return 0;
}

void print_sign(int l, char c) {
    while (l > 0) {
        printf("%c", c);
        --l;
    }
}
void print_head(int full_h )
{
    print_sign((full_h-5)/2 +1, ' ');
    printf("0%%0");
    printf("\n");

    print_sign((full_h-5)/2, '*');
    printf("/");
    print_sign(3, '*');
    printf("\\");
    print_sign((full_h-5)/2, '*');
    printf("\n");
}
void print_free_line ( int count, int full_h)
{
    for (int  i=0; i<count; ++i) {
        for (int j=0; j<full_h; ++j) {
            if(j==0 || j == full_h - 1) print_sign(1,'*');
            else if(j==full_h/2) printf("|");
            else print_sign(1, ' ');
        }
        printf("\n");
    }
}
void print_arrow(int space) {

    int j = 0;

    while (space > 0) {
        print_sign(1, '*');
        print_sign(space, ' ');
        if (space == 1)printf("|");
        else printf("/");
        print_sign(2 + j, ' ');
        printf("|");
        print_sign(1 + j, ' ');
        if (space == 2)printf(" |");
        else if (space == 1) print_sign(2, ' ');
        else printf(" \\");
        print_sign(space, ' ');
        print_sign(1, '*');
        printf("\n");
        space--;
        j++;

    }
}

void print_bal (int h)
{

    int full_h = h*3;
    if(h%2==0)full_h++;
    print_head(full_h);
    print_arrow((full_h-5)/2 -2);
    print_free_line(h-2, full_h);

    for (int i=0; i<full_h; ++i) {
        if (i==full_h/2) printf("+");
        else if (i ==0 || i==full_h-1) print_sign(1, '*');
        else print_sign(1, '-');
    }
    printf("\n");

    print_free_line(h+1, full_h);
    print_sign(full_h, '*');
    printf("\n");
}
int main(void)
{
    int  high;
    printf("What is the high of the balik  you need?\n");
    if(scanf(" %d", &high)!=1 || high <4||getchar()!='\n') return error();
    print_bal(high);
    return 0;
}