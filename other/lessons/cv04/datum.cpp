#include <cstdio>

int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}

struct date
{
    int day;
    int month;
    int year;
};

bool isLeap (int year)
{
    if((year % 4 == 0 && year % 100 != 0) || (year % 4 == 0 && year % 400 == 0)) return true;
    return false;
}

bool isValidDay(date user)
{
    switch(user.month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12: if (user.day<1 || user.day>31) return false;
                 break;
        case 4:
        case 6:
        case 9:
        case 11: if (user.day<1 || user.day>30) return false;
                 break;
        case 2: if (user.day<1 || (!isLeap(user.year) && user.day>28)
                || (isLeap(user.year) && user.day>29) ) return false;
                break;
    }
    return true;
}

int offset (date user)
{
    if(!isLeap(user.year))
    {
        switch (user.month)
        {
            case 1:
            case 10: return 0;
            case 2:
            case 3:
            case 11: return 3;
            case 4:
            case 7:  return 6;
            case 5:  return 1;
            case 6:  return 4;
            case 8:  return 2;
            case 9:
            case 12: return 5;
        }
    }
    else
    {
        switch (user.month)
        {
            case 1:
            case 4:
            case 7: return 0;
            case 2:
            case 8: return 3;
            case 3:
            case 11: return 4;
            case 5: return 2;
            case 6: return 5;
            case 9:
            case 12: return 6;
            case 10: return 1;
        }
    }
    return 0;
}

int determination (date user)
{

    int num = (5*((user.year -1)%4) + 4*((user.year-1)%100) + 6*((user.year -1) %400))%7;
    return  (num+offset(user)+user.day)%7;
}

int main(void)
{
    date user_date;
    while(!feof(stdin)) {
        printf("Zadejte datum ve formatu dd.mm.yyyy:\n");
        if (scanf(" %d . %d . %d", &user_date.day, &user_date.month, &user_date.year) != 3
            || user_date.month < 1 || user_date.month > 12
            || !isValidDay(user_date)
            || getchar() != '\n')
            return error();

        switch (determination(user_date)) {
            case 0:
                printf("Nedele. \n");
                break;
            case 1:
                printf("Pondeli. \n");
                break;
            case 2:
                printf("Utery. \n");
                break;
            case 3:
                printf("Streda. \n");
                break;
            case 4:
                printf("Ctvrtek. \n");
                break;
            case 5:
                printf("Patek. \n");
                break;
            case 6:
                printf("Sobota. \n");
                break;
        }
        printf("Budeme pokracovat? A/N. \n");
        char c;
        bool flag = false;
        while (!flag) {
            if (scanf(" %c", &c) != 1 || getchar() != '\n' ||
                (c != 'A' && c != 'a' && c != 'n' && c != 'N'))
            {
                printf("Zkus znovu. A/N?\n");
                while ((c=getchar())!='\n'){ }
            }
            else if (c == 'N' || c == 'n') {
                printf("Ok. Bye\n");
                return 0;
            } else {
                printf("\n");
                flag = true;
            }
        }
    }
    return 0;
}

