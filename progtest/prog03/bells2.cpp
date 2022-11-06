#ifndef __PROGTEST__
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#endif /* __PROGTEST__ */

#ifndef __PROGTEST__
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
bool isValidDay(int y, int m, int d)
{
    return  (d>=1 && d< month_days(m,y));
}
int check_input (int y, int m, int d, int h, int i)
{
    return(y >=1600 &&
           m >0 && m <13
           && isValidDay(y,m,d)
           && h >=0 && h<24
           && i>=0 && i<60);
}

int bells ( int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2,
            long long int * b1, long long int * b2 )
{

    if (!check_input(y1,m1,d1,h1,i1) || !check_input(y2,m2,d2,h2,i2)) return 0;
    long long int difference = time_difference(date_to_minute(y1,m1,d1,h1,i1), date_to_minute(y2,m2,d2,h2,i2));
    if(difference<0) return 0;
    count_bells(b1, b2, difference, y2,m2,d2,h2,i2);
    return 1;
}

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
    assert ( bells ( 2022, 10,  1, 13, 15,
                      2022, 10,  2, 11, 20, &b1, &b2 ) == 1
              && b1 == 106
              && b2 == 65 );
 */ assert ( bells ( 2022, 10,  2, 13, 15,
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
