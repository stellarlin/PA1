#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#endif /* __PROGTEST__ */

int error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}

struct Date
{   int y;
    int m;
    int d;
    int h;
    int mi;
};

bool isLeap (int year)
{
    if((year % 4 == 0 && year % 100 != 0) || (year % 4 == 0 && year % 400 == 0)) return true;
    return false;
}

bool isValidDay(struct Date user)
{
    switch(user.m)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12: if (user.d<1 || user.d>31) return false;
            break;
        case 4:
        case 6:
        case 9:
        case 11: if (user.d<1 || user.d>30) return false;
            break;
        case 2: if (user.d<1 || (!isLeap(user.y) && user.d>28)
                    || (isLeap(user.y) && user.d>29) ) return false;
            break;
    }
    return true;
}

int offset (struct Date user)
{
    if(!isLeap(user.y))
    {
        switch (user.m)
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
        switch (user.m)
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

int determination (struct Date user)
{

    int num = (5*((user.year -1)%4) + 4*((user.year-1)%100) + 6*((user.year -1) %400))%7;
    return  (num+offset(user)+user.day)%7;
}

int check_input (struct Date date)
{
    return(date.y >=1600
           && date.m >0 && date.m <13
           && isValidDay(date)
           && date.h >=0 && date.h<24
           && date.mi>=0 && date.mi<60);
}

void time_declaration (int y, int m, int d, int h, int i, struct Date * date)
{
    date->y=y;
    date->m=m;
    date->d=d;
    date->h=h;
    date->mi=i;
}


int bells ( int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2,
            long long int * b1, long long int * b2 )
{
    struct Date t1; struct Date t2; struct Date diff;
    time_declaration(y1,m1,d1,h1,i1, &t1);
    time_declaration(y2,m2,d2,h2,i2, &t2);
   if (!check_input(t1) || !check_input(t2) ) return error();
  /* todo */
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int b1, b2;

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
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
