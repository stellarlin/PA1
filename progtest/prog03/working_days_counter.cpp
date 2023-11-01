#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define starting_year 2000
typedef struct
{
  int m_TotalDays;
  int m_WorkDays;
} TResult;
#endif /* __PROGTEST__ */



struct DATE
{
    DATE (int y, int m, int d) : year(y), month(m), day(d) {}
    int year;
    int month;
    int day;
};

// check if year is leap or not
bool isLeap (int year)
{
    if(year % 4 == 0 && (year % 100 != 0 || (year % 100 == 0 && year % 400 == 0 && year % 4000 !=0))) return true;
    return false;
}

bool isHoliday (DATE * date)
{
    switch (date->month) {

        case 1: return date->day == 1;
        case 5: return date->day == 1 || date->day == 8;
        case 7: return date->day == 5 || date->day == 6;

        case 9:
        case 10: return date->day == 28;

        case 11: return date->day == 17;
        case 12: return date->day > 23 && date->day < 27;
        default: return false;
    }
}

//Zeller's Congruence with extension for new leap year condition (leap year % 4000 != 0)
int dayOfWeek (DATE date)
{
    if (date.month < 3) {
        date.month += 12;
        date.year--;
    }
    //Zeller's Congruence treats January and February as months 13 and 14 of the previous year for the purpose
    // of the formula

    int century = date.year / 100;
    int reminder = date.year % 100;
    return (date.day  + 13 * (date.month  + 1) / 5
    + reminder + reminder / 4 + century / 4 - 2 * century) % 7;

}

//return number of days
int month_days(int m, int y)
{
    switch(m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;

        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return !isLeap(y) ? 28 : 29;
    }
    return 0;
}

long coefficient (DATE * date) {
    int coeff = 0;

    for (int y = 2000; y < date->year; y++) coeff += (isLeap(y) ? 366 : 365);
    for (int m = 1; m < date->month; m++)  coeff += month_days(m, date->year);
    coeff += date->day;

    return coeff;
}

bool isValidInterval (DATE * a, DATE * b) {
    return coefficient(a) <= coefficient(b);
}
//
bool isValidDate (struct DATE * date)
{
    return date->year >= starting_year
    && date->month > 0 && date->month <=12
    && date->day >=1 && date->day <=month_days(date->month, date->year);
}

bool isWorkDay ( int y, int m, int d )
{
    DATE date (y, m, d);
    if (!isValidDate(&date)) return false;

    int day_of_week = dayOfWeek(date);
    return ( day_of_week > 1 && !isHoliday(&date));
}

TResult countDays ( int y1, int m1, int d1,
                    int y2, int m2, int d2 )
{
    TResult result;
    result.m_TotalDays = 0;
    result.m_WorkDays = 0;
    DATE start (y1, m1, d1), end (y2, m2, d2);

    if (!isValidDate(&start) || !isValidDate(&end)
    || ! isValidInterval(&start, &end))
    {
        result.m_TotalDays = -1;
        result.m_WorkDays = -1;
        return result;
    }

  /* todo */
    return result;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  TResult r;

 assert ( isWorkDay ( 2023, 10, 10 ) );

 assert ( ! isWorkDay ( 2023, 11, 11 ) );

 assert ( ! isWorkDay ( 2023, 11, 17 ) );

 assert ( ! isWorkDay ( 2023, 11, 31 ) );

 assert ( ! isWorkDay ( 2023,  2, 29 ) );

 assert ( ! isWorkDay ( 2004,  2, 29 ) );

 assert ( isWorkDay ( 2008,  2, 29 ) );

  assert ( ! isWorkDay ( 2001,  2, 29 ) );

  assert ( ! isWorkDay ( 1996,  1,  2 ) );
/*
  r = countDays ( 2023, 11,  1,
                  2023, 11, 30 );
  assert ( r . m_TotalDays == 30 );
  assert ( r . m_WorkDays == 21 );

  r = countDays ( 2023, 11,  1,
                  2023, 11, 17 );
  assert ( r . m_TotalDays == 17 );
  assert ( r . m_WorkDays == 12 );

  r = countDays ( 2023, 11,  1,
                  2023, 11,  1 );
  assert ( r . m_TotalDays == 1 );
  assert ( r . m_WorkDays == 1 );

  r = countDays ( 2023, 11, 17,
                  2023, 11, 17 );
  assert ( r . m_TotalDays == 1 );
  assert ( r . m_WorkDays == 0 );

  r = countDays ( 2023,  1,  1,
                  2023, 12, 31 );
  assert ( r . m_TotalDays == 365 );
  assert ( r . m_WorkDays == 252 );

  r = countDays ( 2024,  1,  1,
                  2024, 12, 31 );
  assert ( r . m_TotalDays == 366 );
  assert ( r . m_WorkDays == 254 );

  r = countDays ( 2000,  1,  1,
                  2023, 12, 31 );
  assert ( r . m_TotalDays == 8766 );
  assert ( r . m_WorkDays == 6072 );

  r = countDays ( 2001,  2,  3,
                  2023,  7, 18 );
  assert ( r . m_TotalDays == 8201 );
  assert ( r . m_WorkDays == 5682 );

  r = countDays ( 2021,  3, 31,
                  2023, 11, 12 );
  assert ( r . m_TotalDays == 957 );
  assert ( r . m_WorkDays == 666 );
*/

  r = countDays ( 2001,  1,  1,
                  2000,  1,  1 );
  assert ( r . m_TotalDays == -1 );
  assert ( r . m_WorkDays == -1 );

  r = countDays ( 2001,  1,  1,
                  2023,  2, 29 );
  assert ( r . m_TotalDays == -1 );
  assert ( r . m_WorkDays == -1 );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
