#include<stdio.h>
#include <cmath>

int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}

void print_num(int num, char c)
{
    while (num)
    {
        printf("%c", c);
        num--;
    }
}

void less_ten (int num)
{

int carry;
    switch (num)
    {
        case 10:
        case 9: carry=num-10;
                print_num(abs(carry), 'I');
                print_num(1, 'X');
            break;
        case 8:
        case 7:
        case 6:
        case 5:
        case 4:
            if ((carry=num-5)<=0)
            {
                print_num(abs(carry), 'I');
                print_num(1, 'V');
            }
            else
            {
                print_num(1, 'V');
                print_num(abs(carry), 'I');
            }
            break;
        case 3:
        case 2:
        case 1:
            print_num(num,'I');
            break;
        case 0: break;
    }
}

void less_fifty( int num)
{
    if(num==0)return;
    int carry;
    if ((carry=num-50)<=0 && carry >= -10) {
        less_ten(abs(carry));
        print_num(1, 'L');
    }
    else
    {
        print_num(num/10, 'X');
        less_ten(num%10);
    }
}

void less_hundred(int num)
{
    if(num==0)return;
    int carry;
    if ((carry=num-100)<=0 && carry >= -10) {
        less_ten(abs(carry));
        print_num(1, 'C');
    }
    else
    {
        print_num(1, 'L');
        print_num(abs(num-50)/10, 'X');
        less_ten(abs(num-50)%10);
    }
    }

    void less_5hundred(int num)
    {
    if(num==0) return;
    int carry;
        if ((carry=num-500)<=0 && carry >= -100) {
            less_hundred(abs(carry));
            print_num(1, 'D');
        }
        else
        {
            print_num(num/100, 'C');
            less_hundred(num%100);
        }
    }

    void less_thousand(int num)
    {
        if(num==0) return;
        int carry;
        if ((carry=num-1000)<=0 && carry >= -100) {
            less_5hundred(abs(carry));
            print_num(1, 'M');
        }
        else
        {
            print_num(num/500, 'D');
            less_5hundred(num%500);
        }
    }
void less_4thousand(int num)
{
    print_num(num/1000, 'M');
    less_thousand(num%1000);
}
int main(void)
{
    int num;
    while(!feof(stdin)) {
        printf("Zadejte cislo od 0 do 3999:\n");
        if (scanf("%d", &num) != 1 || num < 0 || num > 3999 || getchar() != '\n') return error();
        if (num <= 10) less_ten(num);
        else if (num <= 50 && num > 10) less_fifty(num);
        else if (num<=100 && num >50) less_hundred(num);
        else if (num<=500 && num >100)less_5hundred(num);
        else if (num<=1000 && num >500) less_thousand(num);
        else if (num<4000 && num >1000) less_4thousand(num);
        printf("\n\n");
    }
    return 0;
}

