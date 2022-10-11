
#include<cstdio>
#include <valarray>

int error (void) {
    printf("Error.\n");
    return 0;
}

int  count_dig(int n, int base, int count)
{
    if(n<2) return count;
    if(n%base==0) count++;
    count = count_dig(n/base, base, count);
    return count;
}

void print_num(int amount, int n, int method) {
    switch (method)
    {
        case 1:
                while (amount > 0) {
                printf("%d", n);
                if (amount!=1) printf (" * ");
                --amount;
                } break;
        case 2: printf ("%d^%d", n, amount);
                break;
        case 3: if (amount!=1) printf ("%d^%d", n, amount);
                else  printf ("%d", n);
            break;
    }

}

bool isPrime(int n)
{
    for(int i=1; i<=(int)sqrt(n); i++)
    {
        if(n%i == 0 && i!=1 ) return false;
    }
    return true;
}

void representation (int num, int method)
{
    int amount, tracker = 1;
    printf ("%d = ", num);
     for( int i = 2; i<=num; i++)
     {

         amount=0;
         if(isPrime(i) && num%i==0)
         {
             if(!tracker)
             {
                 printf (" * ");
             }
            amount = count_dig(num, i, amount);
             print_num(amount, i, method);
             tracker = 0;
         }
     }
    printf("\n");
}

int stat_menu (void)
{
    char c;
    bool flag=false;
    int num, met;
    while (!flag) {
        printf("Choose your method and number: \"met, num\"\n"
               "1 - easy\n"
               "2 - with power\n"
               "3 - with power unless without 1\n");

        if (scanf(" %d, %d", &met, &num) == 2
            && (met >0 && met<4)
            && (num >0)
            && getchar() == '\n')
            flag = true;
        if (!flag) {
            printf("Incorrect. Try again.\n\n");
            while ((c = getchar()) != '\n') {}
        }
    }
    representation (num, met);

    return 1;
}

int main(void)
{
    char c;
    bool flag;
    while (!feof(stdin)) {
        stat_menu();
        printf("Want to continue? Y/N. \n");
        flag = false;
        while (!flag) {
            if (scanf(" %c", &c) != 1 || getchar() != '\n' ||
                (c != 'Y' && c != 'y' && c != 'n' && c != 'N'))
            {
                printf("Try again. Y/N?\n");
                while ((c=getchar())!='\n'){ }
            }
            else if (c == 'N' || c == 'n') {
                printf("Ok. Bye!\n");
                return 0;
            } else {
                printf("\n");
                flag = true;
            }
        }
    }
    return 0;
}

