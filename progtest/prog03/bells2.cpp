#ifndef __PROGTEST__
#include <cstdlib>
#include <cassert>

#endif /* __PROGTEST__ */

#define minute_one_week 10080
#define minute_one_day 1440
#define minute_one_hour 60

#define hour_bells_week 936 // week without sunday
#define minute_bells_week 1440 // week without sunday
#define minute_bells_day 240
#define hour_bells_day 156
#define minute_bells_hour 10

struct DATE
{
    int y;
    int m;
    int d;
    int h;
    int i;
};

// check if year is leap or not
bool isLeap (int year)
{
    if((year % 4 == 0 && year % 100 != 0 && year % 4000!=0) || (year % 4 == 0 && year % 400 == 0 && year % 4000 !=0)) return true;
    return false;
}
//return number of da
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
//check input functions
bool isValidDay(struct DATE date)
{
    return  (date.d>=1 && date.d<=month_days(date.m, date.y));
}
bool check_input (struct DATE date)
{
    return(date.y >=1600 &&
           date.m >0 && date.m <13
           && isValidDay(date)
           && date.h >=0 && date.h<24
           && date.i>=0 && date.i<60);
}

long long int year_in_minute(int year)
{
    long long res = 0;
    for(int i=1600; i<year; i++) res += minute_one_day*(365 + isLeap(i));
    return res;
}
long long int month_in_minute(struct DATE date)
{
    long long res = 0;
    for(int i=1; i<date.m; i++) res += minute_one_day* month_days(i, date.y);
    return res;
}
long long int date_to_minute(struct DATE date)
{
    return date.i + minute_one_hour*date.h + minute_one_day*date.d + month_in_minute(date) + year_in_minute(date.y);
}

//return  difference of two dates in minutes
long long int time_difference(long long int date1, long long int  date2 )
{
    return date2-date1;
}

void diff_day_convert (long long diff, struct DATE * date1, struct DATE  date2) {

    date1->d=0;
    date1->m = date2.m;
    date1->y = date2.y;
    if (date2.h < (diff % minute_one_day) / minute_one_hour) date1->d--;
    if (date1->d + date2.d >= diff /minute_one_day )   date1->d += date2.d - diff / minute_one_day;
    else {
        if (date1->m == 1) {
            date1->m = 12;
            date1->y++;
        } else date1->m--;
    }
}
int day_of_week (struct DATE date)
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    date.y -= date.m < 3;
    return (date.y + date.y / 4 - date.y / 100 + date.y / 400  - date.y/4000 + t[date.m - 1] + date.d)% 7;
}


int hours_counter (  int  h)
{
    return (h % 12 == 0) ? 12 :  h % 12;

}
int minute_counter ( int  i)
{
    return (i / 15 == 0) ?  4 :  i / 15;
}

int push_week_day(int * day)
{
    ++(*day);
    *day %=7;
    return *day;
}

void how_many_days (long long int * bell1, long long int * bell2,  struct DATE  * date1, struct DATE   date2, int * week_day, bool * first_hour_flag) {

    if (date1->d == date2.d)return;
    if (*week_day != 0) {

        if (date1->i != 0 && !*first_hour_flag) {
            if (date1->i % 15 != 0) date1->i += 15;
            *first_hour_flag = 1;
            date1->h++;
            *bell1 += minute_bells_hour;
        }

        while (date1->i < 60) {
            *bell1 += minute_counter(date1->i);
            date1->i += 15;
        }

        while (date1->h < 24) {
            *bell2 += hours_counter(date1->h);
            if (date1->h < 23) *bell1 += minute_bells_hour;
            date1->h++;
        }
    }
    date1->h = date1->i = 0;
    date1->d++;
    *week_day = push_week_day(week_day);

    while (date1->d != date2.d) {
        if (*week_day != 0) {
            //count bells per one full day
            *bell2 += hour_bells_day;
            *bell1 += minute_bells_day;
        }
        date1->d++;
        *week_day = push_week_day(week_day);
    }
}

void how_many_hours (long long int * bell1, long long int * bell2, struct DATE * date1,  struct DATE  date2, int * week_day, bool * first_hour_flag)
{
  if((date1->h == date2.h && date1->i!=0) || !*week_day) return;

  if(date1->h == date2.h && date1->i==0)
  {
     *bell2 += hours_counter(date1->h);
      return;
  }

  if( date1->i != 0 ) {
      if (!*first_hour_flag && date1->i % 15 != 0) date1->i += 15;
      if (*first_hour_flag) hours_counter(date1->h);
      while(date1->i< 60)
      {
          *bell1 += minute_counter(date1->i);
          date1->i+=15;
      }
      date1->i=0;
      date1->h++;
  }
  else *first_hour_flag = 1;
    while (date1->h<=date2.h) {
        *bell2 += hours_counter(date1->h);
        if(date1->h!=date2.h)*bell1 += minute_bells_hour;
        date1->h++;
    }
    }

void how_many_minutes (long long int * bell1, int * week_day, struct DATE * date1,  struct DATE  date2,  bool * first_hour_flag)
{
    if(!*week_day ) return;
    while (date1->i < date2.i+15) {
        if (!*first_hour_flag && date1->i % 15 != 0) *first_hour_flag=1,  date1->i+=15;
        if(date1->i>=date2.i)
        {
            if(date2.i%15 == 0) *bell1 += minute_counter(date1->i);
            return;
        }
        *bell1 += minute_counter(date1->i);
        date1->i+=15;
    }
   // if(date1->i >= date2.i && date2.i%15==0)  *bell1 += minute_counter(date2.i);


}

void count_bells(long long int * bell1, long long int * bell2, long long int diff,  struct DATE date1, struct DATE date2)
{
    bool first_hour_flag=0;
    *bell2 =diff/minute_one_week * hour_bells_week ;
    *bell1 =diff/minute_one_week * minute_bells_week;

    diff = diff % minute_one_week;

    diff_day_convert(diff, &date1, date2);
    int week_day =day_of_week(date1);

    how_many_days(bell1, bell2,  &date1, date2,  &week_day, &first_hour_flag);
    how_many_hours(bell1, bell2,&date1, date2, &week_day, &first_hour_flag);
    how_many_minutes(bell1, &week_day, &date1, date2, &first_hour_flag);
}


int  bells ( int y1, int m1, int d1, int h1, int i1,
           int y2, int m2, int d2, int h2, int i2,
           long long int * b1, long long int * b2 )
{
    struct DATE date1={y1,m1,d1,h1,i1};
    struct DATE date2={y2,m2,d2,h2,i2};
    if (!check_input(date1) || !check_input(date2)) return 0;
    long long int difference = time_difference(date_to_minute(date1), date_to_minute(date2) );
    if(difference<0) return 0;
    count_bells(b1, b2, difference, date1, date2);
    return 1;
}






#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    long long int b1, b2;
    b1=2; b2=0;

    assert ( bells ( 2022, 11,  1, 12,  0,
                     2022, 10,  1, 12,  0, &b1, &b2 ) == 0
             && b1 == 2
             && b2 == 0 );
    assert ( bells ( 2022, 10, 32, 12,  0,
                     2022, 11, 10, 12,  0, &b1, &b2 ) == 0
             && b1 == 2
             && b2 == 0 );
    assert ( bells ( 2100,  2, 29, 12,  0,
                     2100,  2, 29, 12,  0, &b1, &b2 ) == 0
             && b1 == 2
             && b2 == 0 );

    assert(bells(1666,3,10,8,50,  1666,3,10,26,59,  &b1, &b2) == 0 && b1 == 2 && b2 == 0);
    assert(bells(1666,8,15,12,1,  1666,8,15,25,43,  &b1, &b2) == 0 && b1 == 2 && b2 == 0);
    assert(bells(1666,6,25,16,32,  1666,6,25,33,39,  &b1, &b2) == 0 && b1 == 2 && b2 == 0);
    assert(bells(1666,2,6,19,6,  1666,2,6,27,40,  &b1, &b2) == 0 && b1 == 2 && b2 == 0);
    assert(bells(1666,5,1,8,43,  1666,5,1,27,81,  &b1, &b2) == 0 && b1 == 2 && b2 == 0);
    assert(bells(1666,10,4,6,52,  1666,10,4,9,95,  &b1, &b2) == 0 && b1 == 2 && b2 == 0);
    assert(bells(1666,1,17,14,10,  1666,1,17,32,46,  &b1, &b2) == 0 && b1 == 2 && b2 == 0);
    assert(bells(1666,4,7,13,44,  1666,4,7,30,48,  &b1, &b2) == 0 && b1 == 2 && b2 == 0);
    assert(bells(1666,2,26,6,57,  1666,2,26,10,73,  &b1, &b2) == 0 && b1 == 2 && b2 == 0);
    assert(bells(1666,8,2,17,59,  1666,8,2,19,65,  &b1, &b2) == 0 && b1 == 2 && b2 == 0);
    assert(bells(1666,3,1,9,43,  1666,3,1,17,68,  &b1, &b2) == 0 && b1 == 2 && b2 == 0);
    assert(bells(1666,12,20,9,30,  1666,12,20,17,73,  &b1, &b2) == 0 && b1 == 2 && b2 == 0);


assert ( bells ( 2022, 10,  1, 13, 15,
                  2022, 10,  1, 18, 45, &b1, &b2 ) == 1
          && b1 == 56
           && b2 == 20 );
 assert ( bells ( 2022, 10,  3, 13, 15,
                   2022, 10,  4, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                      2022, 10,  2, 11, 20, &b1, &b2 ) == 1
              && b1 == 106
              && b2 == 65 );

   assert ( bells ( 2022, 10,  1, 11, 16,
                    2022, 10,  1, 11, 20, &b1, &b2 ) == 1
            && b1 == 0
            && b2 == 0 );
    assert ( bells ( 2022, 10,  1, 11, 01,
                     2022, 10,  1, 11, 30, &b1, &b2 ) == 1
             && b1 == 3
             && b2 == 0 );
   assert ( bells ( 2022, 10,  1, 11, 16,
                    2022, 10,  1, 12, 20, &b1, &b2 ) == 1
            && b1 == 10
            && b2 == 12 );
   assert ( bells ( 2022, 10,  1, 13, 16,
                     2022, 10,  3, 11, 20, &b1, &b2 ) == 1
             && b1 == 220
             && b2 == 143 );

 assert ( bells ( 2022, 10,  2, 13, 15,
                     2022, 10,  3, 11, 20, &b1, &b2 ) == 1
             && b1 == 115
             && b2 == 78 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                     2022, 10,  3, 11, 20, &b1, &b2 ) == 1
             && b1 == 221
             && b2 == 143 );
      assert ( bells ( 2022,  1,  1, 13, 15,
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

    assert ( bells ( 2000,  2, 29, 12,  0,
                     2000,  2, 29, 12,  0, &b1, &b2 ) == 1
             && b1 == 4
             && b2 == 12 );
    assert ( bells ( 2004,  2, 29, 12,  0,
                     2004,  2, 29, 12,  0, &b1, &b2 ) == 1
             && b1 == 0
             && b2 == 0 );


assert ( bells ( 2022, 10,  1,  23, 46,
                     2022, 10,  2,  0, 00, &b1, &b2 ) == 1
             && b1 == 0
             && b2 == 0 );
           assert ( bells ( 2022, 10,  1, 12,  0,
                        2022, 10,  1, 12,  0, &b1, &b2 ) == 1
                && b1 == 4
                && b2 == 12 );



  assert(bells(1666,12,28,3,43,  1666,12,28,16,47,  &b1, &b2) == 1 && b1 == 133 && b2 == 82);
     assert(bells(1666,6,2,6,29,  1666,6,2,6,36,  &b1, &b2) == 1 && b1 == 2 && b2 == 0);
    assert(bells(1666,4,14,1,5,  1666,4,14,7,27,  &b1, &b2) == 1 && b1 == 61 && b2 == 27);
    assert(( bells ( 1700, 9, 9, 0, 0, 1700, 9, 9, 22, 0, &b1, &b2 ) == 1 && b1 == 224 && b2 == 145));

    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
