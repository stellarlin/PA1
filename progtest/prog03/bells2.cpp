#ifndef __PROGTEST__
#include <cstdlib>
#include <cassert>
#include <cstdio>

#endif /* __PROGTEST__ */

#define minute_one_day 1440
#define minute_one_hour 60

#define hour_bells_week 1092
#define minute_bells_week 1680
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





int  bells ( int y1, int m1, int d1, int h1, int i1,
           int y2, int m2, int d2, int h2, int i2,
           long long int * b1, long long int * b2 )
{
    struct DATE date1={y1,m1,d1,h1,i1};
    struct DATE date2={y2,m2,d2,h2,i2};
    if (!check_input(date1) || !check_input(date2)) return 0;
    long long int difference = time_difference(date_to_minute(date1), date_to_minute(date2) );
    if(difference<0) return 0;
printf("diff: %lld\n",difference);

return 1;
}






#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    long long int b1, b2;
    b1=4; b2=12;

    bells ( 2023, 10,  1, 13, 15,
            2024, 10,  1, 13, 15, &b1, &b2 );



/*assert ( bells ( 2022, 10,  1, 13, 15,
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
