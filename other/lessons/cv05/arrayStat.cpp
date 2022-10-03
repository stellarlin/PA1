#include<stdio.h>

int error (void) {
    printf("Error.\n");
    return 0;
}

bool method_parameter (int method, int k, int num)
{
    switch (method)
    {
        case 1: return true;
        case 2: if(num>k) return true;
            break;
        case 3: if(num%k==0) return true;
            break;
        case 4: if(num>k && num%k==0) return true;
            break;
        case 5: if(num>k || num%k==0) return true;
    }
    return false;
}

void stats (int count, int sum, int min, int max, int sec_max, double expected, int type, int arge_type)
{
    printf("Count of numbers: %d\n"
           "Sum of numbers: %d\n"
           "Minimum: %d\n"
           "Maximum: %d\n"
           "Second maximum: %d\n"
           "Expected value: %f\n", count, sum, min, max, sec_max, expected);
    printf ("Type of monotony: ");
    switch (type)
    {
        case 0: printf ("not constant, not declining, not growing sequence.\n ");
                break;
        case 1: printf ("constant sequence.\n");
                break;
        case 2: printf ("growing sequence.\n");
                break;
        case 3: printf ("declining sequence.\n");
        printf("\n");
    }
    printf ("Function is ");
    switch (arge_type)
    {
        case 3: printf("not arithmetic and not geometric.\n");
                break;
        case 2: printf("geometric sequence.\n");
                break;
        case 1: printf("arithmetic sequence.\n");
            break;
    }
}

int type_progression(int first, int last, int i, int type) {
    if (i == 0) return 1;
    if (last == first && type == 1) return 1;
    if (last < first && (i == 1 || type ==1 || type == 2)) return 2;
    if (last > first && (i == 1 || type ==1 || type == 3)) return 3;
    return 0;
}
int ar_ge_progression(int first, int last, int * ar_diff, int *ge_diff, int i, int  arge_type)
{
    if (i==0) return 0;
    if (i == 1) {
        *ar_diff = first - last;
        *ge_diff = first / last;
        return 0;
    }
    else if((first-last)==*ar_diff && ( arge_type == 0 || arge_type ==1)) return 1;
    else if((first/last)==*ge_diff && (arge_type == 0 || arge_type ==2)) return 2;
    return 3;

}

void required_num (int method, int k, int *num, int * last,
                   int *n, int *min, int *max, int *sec_max, int *sum, int * type,
                   int * ar_diff, int * ge_diff, int * arge_tipe)
{
    if (!method_parameter(method, k, *num))return;
    *type = type_progression(*num, *last, *n, *type);
    *arge_tipe= ar_ge_progression(*num, *last, &*ar_diff, &* ge_diff, *n, *arge_tipe);
    *sum += *num;
    if (*n == 0 || *num > *max ) {
        *sec_max=*max;
        *max = *num;
    }
    if (*n == 0 || *num < *min) *min = *num;
    ++*n;
    *last = *num;
}

int N_numbers( int k, int method)
{
    int n, i=0, num, type=0, last=0, sum=0, min, max, sec_max, ar_diff, ge_diff, arge_type = 0;
    printf ("Choose your n:\n");
    if(scanf(" %d", &n)!=1 || n < 1 || getchar()!='\n') return 0;
    printf("Start to print your numbers:\n");
    while( i < n)
    {
        if(scanf(" %d", &num)!=1) return 0;
        required_num(method,k, &num, &last, &i, &min, &max,&sec_max, &sum, &type, &ar_diff, &ge_diff,
                     &arge_type);

    }
    stats(n, sum, min, max, sec_max, sum*1.0/n, type, arge_type);
    return 1;
}
int until_zero(int k, int method)
{
    int n=0, num, sum=0, last = 0, min, max, sec_max, err, type=0, arge_type = 0, ar_diff=0, ge_diff=0;
    printf("Start to print your numbers:\n");
    while((err=scanf(" %d", &num)) == 1 && num !=0) {
        required_num(method,k,&num, &last, &n, &min, &max,&sec_max, &sum, &type, &ar_diff, &ge_diff, &arge_type);
    }
    if(num=='0'|| err!=1) return 0;
    stats(n, sum, min, max, sec_max, sum*1.0/n, type, arge_type);
    return 1;
}
int until_EOF(int k, int method) {
    int n = 0, num, last=0, sum = 0, min=0, max=0, sec_max=0, type=0, ar_diff=0, ge_diff=0, arge_type=0, err;
    printf("Start to print your numbers:\n");
    while ((err = scanf(" %d", &num)) == 1) {
        required_num(method,k,&num, &last, &n, &min, &max,&sec_max, &sum, &type, &ar_diff, &ge_diff, &arge_type);

    }
        if (err!= EOF) return 0;
        stats(n, sum, min, max, sec_max, sum * 1.0 / n, type, arge_type);
        return 1;
}

int stat_menu (void)
{
    char c;
    bool flag=false;
    int k, k_method;
    while (!flag) {
        printf("Choose your input method, coefficient and use: \"c, k, n\"\n"
               "N - read n decimal numbers\n"
               "Z - read decimal numbers until 0\n"
               "E - read decimal numbers until EOF\n"
               "\n1) all\n"
               "2) all bigger than k\n"
               "3) all divisible by k\n"
               "4) all bigger than k and divisible by k\n"
               "5) all bigger than k or divisible by k\n");

        if (scanf(" %c, %d, %d", &c, &k, &k_method) == 3
            && (c == 'N' || c == 'Z' || c == 'E')
            && (k_method > 0 && k_method < 6)
            && getchar() == '\n')
            flag = true;
        if (!flag) {
            printf("Incorrect. Try again.\n\n");
            while ((c = getchar()) != '\n') {}
        }
    }

    switch (c) {
        case 'N':
            if (!N_numbers(k, k_method)) return error();
            break;
        case 'Z':
            if (!until_zero(k, k_method)) return error();
            break;
        case 'E':
            if (!until_EOF(k, k_method)) return error();

    }
return 1;
}

int main(void)
{
    char c;
    bool flag;
    while (!feof(stdin)) {
        stat_menu();
        printf("Want to continue? Y/N. \n");
        while ((c=getchar())!='\n'){ }
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

