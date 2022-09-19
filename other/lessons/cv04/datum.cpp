#include<stdio.h>
#include <cmath>
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

int main(void)
{
    date user_date;
    if(scanf(" %d . %d . %d", &user_date.day, &user_date.month, &user_date.year)!=3
    || user_date.year <1990  )

    return 0;
}

