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

void print_bal (int h)
{

    int full_h = h*3;
    if(h%2==0)full_h++;

    print_sign((full_h-5)/2 +1, ' ');
    printf("0%%0");
    printf("\n");

    print_sign((full_h-5)/2, '*');
    printf("/");
    print_sign(3, '*');
    printf("\\");
    print_sign((full_h-5)/2, '*');
    printf("\n");

    for (int i=0; i<full_h; ++i) {
        if (h%2==0 &&  (i==full_h/2 || i==(full_h/2)+2)) printf("|");
        else if (h%2!=0 && i==full_h/2 ) printf("|");
        else if (h%2!=0 &&  i==full_h/2 +3 ) printf("\\");
        else if (i==(full_h-5)/2-1) printf("/");
        else if (i ==0 || i==full_h-1) print_sign(1, '*');
        else print_sign(1, ' ');
    }
    printf("\n");
    for (int i=0; i<full_h; ++i) {
        if (h%2==0 &&  (i==(full_h-5)/2-1|| i==full_h/2)) printf("|");
        else if(h%2!=0 &&  (i==full_h/2 + 3 || i==full_h/2))  printf("|");
        else if (h%2!=0 &&  i==(full_h-5)/2 -2) printf("/");
        else if (i ==0 || i==full_h-1) print_sign(1, '*');
        else print_sign(1, ' ');
    }
    printf("\n");
    for (int i=0; i<h-2; ++i) {
        for (int j=0; j<full_h; ++j) {
            if(j==0 || j == full_h-1) print_sign(1,'*');
            else if(h%2!=0 &&  i==0 && j==(full_h-5)/2-2)  printf("|");
            else if(j==full_h/2) printf("|");
            else print_sign(1, ' ');
        }
        printf("\n");
        }

    for (int i=0; i<full_h; ++i) {
        if (i==full_h/2) printf("+");
        else if (i ==0 || i==full_h-1) print_sign(1, '*');
        else print_sign(1, '-');
    }
    printf("\n");

    for (int i=0; i<h+1; ++i) {
        for (int j=0; j<full_h; ++j) {
            if(j==0 || j == full_h-1) print_sign(1,'*');
            else if(j==full_h/2) printf("|");
            else print_sign(1, ' ');
        }
        printf("\n");
    }
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