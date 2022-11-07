#ifndef __PROGTEST__
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#endif /* __PROGTEST__ */

#define DAYS 1400

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
    return  (date.d>=1 && date.d<=month_days(date.m, date.y));
}
int check_input (struct DATE date)
{
    return(date.y >=1600 &&
           date.m >0 && date.m <13
           && isValidDay(date)
           && date.h >=0 && date.h<24
           && date.i>=0 && date.i<60);
}

int day_of_week (struct DATE date)
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    date.y -= date.m < 3;
    return (date.y + date.y / 4 - date.y / 100 + date.y / 400  - date.y/4000 + t[date.m - 1] + date.d)% 7;
}
long long int years_in_minute(int year1, int year2)
{
    long long res = 0;
    for(int i=year1; i<=year2; i++) res += DAYS*(365 + isLeap(i));
    return res;
}
long long int month_in_minute(struct DATE date1, struct DATE date2)
{
    long long res = 0;
    for(int i = 1; i<date2.m; i++) res+=DAYS*month_days(i,date2.y);
    for(int i = 1; i<date1.m; i++) res-=DAYS*month_days(i,date1.y);
    return res;
}
long long int time_difference(struct DATE date1, struct DATE date2 )
{
    long long int diff = (date2.i-date1.i) + 60*(date2.h-date1.h) + DAYS *(date2.d-date1.d) + month_in_minute(date1, date2) +  years_in_minute(date1.y, date2.y);

 return (diff <0) ? -1 : diff;
}

void diff_day_convert (long long diff, struct DATE * date1, struct DATE  date2) {

    date1->d=0;
    date1->m = date2.m;
    date1->y = date2.y;
    if (date2.h < (diff % DAYS) / 60) date1->d--;
    if (date1->d + date2.d >= diff / DAYS)   date1->d += date2.d - diff / DAYS;
    else {
        if (date1->m == 1) {
            date1->m = 12;
            date1->y++;
        } else date1->m--;
    }
}

int push_week_day(int * day)
{
    ++(*day);
    *day %=7;
    return *day;
}

void hours_counter (long long int * bell1, long long int * bell2,  long long int diff, int  h, int i )
{
    if (h % 12 == 0) *bell2 += 12;
    else *bell2 += h % 12;
    if (i != diff)  *bell1 += 10;
}
void how_many_days (long long int * bell1, long long int * bell2, long long int diff,  struct DATE * date1, int * week_day)
{
    for (int i =diff/DAYS; i>0;i--)
    {
        if((*week_day+1)%7 ==0) {

            for (int j = date1->h; j < 24; j++)
            {
                if ( j == date1->h && date1->i != 0) j++, *bell1 += 10;
                hours_counter(bell1, bell2, 23, j, j);
            }
        }
        else if(*week_day!=0)
        {
            *bell2+=156;
            *bell1+=240;
        }
        *week_day= push_week_day(week_day);
    }
}
void how_many_hours (long long int * bell1, long long int * bell2, long long int diff,  int * week_day, struct DATE * date1)
{
    diff = diff/60;
    for (int i =0; i<=diff; i++)
    {
        if(date1->h==24)
        {
            if(!*week_day) {
                for (int j = 0; j < date1->i; j += 15) {
                    if (i / 15 == 0) *bell1 += 4;
                    else *bell1 += i / 15;
                }
            }
           date1->h=0;
           push_week_day(week_day);
           if(!*week_day) *bell1-=10;

        }

        if(*week_day!=0) {
            if (i == 0 && date1->i != 0) date1->h++, *bell1 += 10, i++;
            hours_counter(bell1, bell2, diff,  date1->h, i);
            }

        if (i != diff)  date1->h++;
        }
 }

void how_many_minutes (long long int * bell1,  long long int diff,  int * week_day, struct DATE * date1)
{
    if(date1->h==24)
    {
        date1->h=0;
        push_week_day(week_day);
    }
    int i =0;
    if(*week_day==0)
    {
        i=date1->i;
        diff=llabs(diff-60);
    }
    for (; i<=diff;i+=15)
    {
      //  if (date1->i % 15 != 0)i2 += 15;
        if (date1->i/15 == 0) *bell1 += 4;
        else *bell1 += date1->i / 15;

        date1->i+=15;
        if(date1->i>=60) date1->i-=60, date1->h++;
    }

}
void count_bells(long long int * bell1, long long int * bell2, long long int diff,  struct DATE date1, struct DATE date2)
{
    *bell2 =diff/10080 * 1872;
    *bell1 =diff/10080 * ;

    diff = diff % 10080;

    diff_day_convert(diff, &date1, date2);
    int week_day =day_of_week(date1);

    how_many_days(bell1, bell2, diff, &date1, &week_day);

    diff=diff%DAYS;
    how_many_hours(bell1, bell2, diff, &week_day, &date1);

    diff=diff%60;
    how_many_minutes(bell1, diff, &week_day, &date1);
}

int bells ( int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2,
            long long int * b1, long long int * b2 )
{
*b1=4; *b2=12;
    struct DATE date1={y1,m1,d1,h1,i1};
    struct DATE date2={y2,m2,d2,h2,i2};
   if (!check_input(date1) || !check_input(date2)) return 0;
   long long int difference = time_difference(date1, date2);
   if(difference<0) return 0;
   count_bells(b1, b2, difference, date1, date2);
   return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int b1, b2;

/*assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  1, 18, 45, &b1, &b2 ) == 1
           && b1 == 56
           && b2 == 20 );

assert ( bells ( 2022, 10,  3, 13, 15,
                   2022, 10,  4, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
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

 assert ( bells ( 2022, 10,  1, 13, 15,
                      2022, 10,  2, 11, 20, &b1, &b2 ) == 1
              && b1 == 106
              && b2 == 65 );

 assert ( bells ( 2022, 10,  2, 13, 15,
                      2022, 10,  3, 11, 20, &b1, &b2 ) == 1
              && b1 == 115
              && b2 == 78 );
 */
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
