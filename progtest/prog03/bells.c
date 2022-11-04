#ifndef __PROGTEST__
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#endif /* __PROGTEST__ */

struct DATE
{
    int y;
    int m;
    int d;
    int h;
    int i;
};

bool isLeap (int year)
{
    if((year % 4 == 0 && year % 100 != 0 && year % 4000!=0) || (year % 4 == 0 && year % 400 == 0 && year % 4000 !=0)) return true;
    return false;
}
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
            if (!isLeap(y))return 28;
            else return 29;
    }
    return 0;
}
bool isValidDay(struct DATE date)
{
    return  (date.d>=1 && date.d< month_days(date.m, date.y));
}
int check_input (struct DATE date)
{
    return(date.y >=1600 &&
           date.m >0 && date.m <13
           && isValidDay(date)
           && date.h >=0 && date.h<24
           && date.i>=0 && date.i<60);
}

int offset (int y, int m)
{
    if(!isLeap(y))
    {
        switch (m)
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
        switch (m)
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
int day_of_week (struct DATE date)
{

    int num = (5*((date.y -1)%4) + 4*((date.y-1)%100) + 6*((date.y-1) %400))%7;
    return  (num+offset(date.y, date.m) + date.d)%7;
}

long long int time_difference(long long int date1, long long int date2 )
{
 return (date2-date1 <0) ? -1 : date2-date1;
}
long long int date_to_minute(struct DATE date)
{
    return date.i + 60*date.h + 1440*date.d + 43800*date.m + 525960*date.y;
}
void diff_day_convert (long long diff, struct DATE * date1, struct DATE  date2) {

    date1->d=date1->h=0;
    date1->m = date2.m;
    date1->y = date2.y;
    if (date2.i >= (diff % 1440) % 60) date1->i = date2.i - (diff % 1440) % 60;
    else {
        date1->i = date2.i - diff % 1440 % 60 + 60;
        date1->h--;
    }
    if (date1->h + date2.h >= (diff % 1440) / 60) date1->h += date2.h - (diff % 1440) / 60;
    else {
        date1->h += date2.h - diff % 1440 / 60 + 24;
        date1->d--;
    }
    if (date1->d + date2.d >= diff / 1440)   date1->d += date2.d - diff / 1440;
    else {
        if (date1->m == 1) {
            date1->m = 12;
            date1->y++;
        } else date1->m--;
    }
}

int push_week_day(int * day)
{
    ++*day;
    *day %=7;
    return *day;
}

void how_many_days (long long int * bell1, long long int * bell2, long long int diff,  int * week_day)
{
    for (int i =diff/1440; i>0;i--)
    {
        if(*week_day!=0)
        {
            *bell2+=312;
            *bell1+=1440;
        }
        *week_day= push_week_day(week_day);
    }
}
void how_many_hours (long long int * bell1, long long int * bell2, long long int diff,  int * week_day, struct DATE * date1,struct DATE date2 )
{
    diff = diff/60;
    for (int i =0; i<=diff; i++)
    {
        if(date1->h==24)
        {
            date1->h=1;
            *bell2 +=12;
           push_week_day(week_day);
        }
        if(*week_day!=0) {
            if (i == 0 && date1->i != 0) {}
            else if (date1->h % 12 != 0) *bell2 += 12;
            else *bell2 += date1->h % 12;
            if (i != diff) *bell1 += 10;
            }
        date1->h++;
        }
 }

void how_many_minutes (long long int * bell1,  long long int diff,  int * week_day, struct DATE * date1)
{
    if(week_day==0) diff=llabs(diff-60);
    for (int i =0; i<=diff;i+=15)
    {
        if(week_day==0)
        {
            i=date1->i;
            diff=llabs(diff-60);
        }

      //  if (date1->i % 15 != 0)i2 += 15;
        if (date1->i/ 15 == 0) *bell1 += 4;
        else *bell1 += date1->i / 15;

        date1->i+=15;
        if(date1->i>=60) date1->i-=60;
    }

}
void count_bells(long long int * bell1, long long int * bell2, long long int diff,  struct DATE date1, struct DATE date2)
{
    *bell2 =diff/10080 * 1872;
    *bell1 =diff/10080 * 1440;

    diff = diff % 10080;

    diff_day_convert(diff, &date1, date2);
    int week_day =day_of_week(date1)%7;

    how_many_days(bell1, bell2, diff, &week_day);

    diff=diff%1440;
    how_many_hours(bell1, bell2, diff, &week_day, &date1, date2);

    diff=diff%60;
    how_many_minutes(bell1, diff, &week_day, &date1);
}

int bells ( int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2,
            long long int * b1, long long int * b2 )
{

    struct DATE date1={y1,m1,d1,h1,i1};
    struct DATE date2={y2,m2,d2,h2,i2};
   if (!check_input(date1) || !check_input(date2)) return 0;
   long long int difference = time_difference(date_to_minute(date1), date_to_minute(date2));
   if(difference<0) return 0;
   count_bells(b1, b2, difference, date1, date2);
   return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int b1, b2;
/*
assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  1, 18, 45, &b1, &b2 ) == 1
           && b1 == 56
           && b2 == 20 );

assert ( bells ( 2022, 10,  3, 13, 15,
                   2022, 10,  4, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
*/  assert ( bells ( 2022, 10,  1, 13, 15,
                      2022, 10,  2, 11, 20, &b1, &b2 ) == 1
              && b1 == 106
              && b2 == 65 );
 assert ( bells ( 2022, 10,  2, 13, 15,
                      2022, 10,  3, 11, 20, &b1, &b2 ) == 1
              && b1 == 115
              && b2 == 78 );
     assert ( bells ( 2022, 10,  1, 13, 15,
                      2022, 10,  3, 11, 20, &b1, &b2 ) == 1
              && b1 == 221
              && b2 == 143 );
  /*   assert ( bells ( 2022,  1,  1, 13, 15,
                      2022, 10,  5, 11, 20, &b1, &b2 ) == 1
              && b1 == 56861
              && b2 == 36959 );
     assert ( bells ( 2019,  1,  1, 13, 15,
                      2019, 10,  5, 11, 20, &b1, &b2 ) == 1
              && b1 == 57101
              && b2 == 37115 );
     assert ( bells ( 2024,  1,  1, 13, 15,
                      2024, 10,  5, 11, 20, &b1, &b2 ) == 1
              && b1 == 57341
              && b2 == 37271 );
     assert ( bells ( 1900,  1,  1, 13, 15,
                      1900, 10,  5, 11, 20, &b1, &b2 ) == 1
              && b1 == 57101
              && b2 == 37115 );
     assert ( bells ( 2022, 10,  1,  0,  0,
                      2022, 10,  1, 12,  0, &b1, &b2 ) == 1
              && b1 == 124
              && b2 == 90 );
     assert ( bells ( 2022, 10,  1,  0, 15,
                      2022, 10,  1,  0, 25, &b1, &b2 ) == 1
              && b1 == 1
              && b2 == 0 );
     assert ( bells ( 2022, 10,  1, 12,  0,
                      2022, 10,  1, 12,  0, &b1, &b2 ) == 1
              && b1 == 4
              && b2 == 12 );
     assert ( bells ( 2022, 11,  1, 12,  0,
                      2022, 10,  1, 12,  0, &b1, &b2 ) == 0
              && b1 == 4
              && b2 == 12 );
     assert ( bells ( 2022, 10, 32, 12,  0,
                      2022, 11, 10, 12,  0, &b1, &b2 ) == 0
              && b1 == 4
              && b2 == 12 );
     assert ( bells ( 2100,  2, 29, 12,  0,
                      2100,  2, 29, 12,  0, &b1, &b2 ) == 0
              && b1 == 4
              && b2 == 12 );
     assert ( bells ( 2000,  2, 29, 12,  0,
                      2000,  2, 29, 12,  0, &b1, &b2 ) == 1
              && b1 == 4
              && b2 == 12 );
     assert ( bells ( 2004,  2, 29, 12,  0,
                      2004,  2, 29, 12,  0, &b1, &b2 ) == 1
              && b1 == 0
              && b2 == 0 );
*/
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
