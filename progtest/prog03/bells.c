#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#endif /* __PROGTEST__ */

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
int determination (int y, int m, int d)
{

    int num = (5*((y -1)%4) + 4*((y-1)%100) + 6*((y-1) %400))%7;
    return  (num+offset(y,m)+d)%7;
}
int check_input (int y, int m, int d, int h, int i)
{
    return(y >=1600 &&
           m >0 && m <13
           && isValidDay(y,m,d)
           && h >=0 && h<24
           && i>=0 && i<60);
}
long long int time_difference(long long int date1, long long int date2 )
{
 return (date2-date1 <0) ? -1 : date2-date1;
}
long long int date_to_secund(int y, int m, int d, int h, int i)
{
    return i + 60*h + 1440*d + 43800*m+525960*y;
}
void hour_min_clock_counter (long long int * bell1, long long int * bell2, int h, int i, int h_limit, int i_limit)
{
    if(i%15!=0)i+=15;
    while(i<i_limit)
    {
        if(i/15==0) *bell1 +=4;
        else *bell1 += i/15;
        i+=15;
    }
    h++;

    while (h<h_limit)
    {
        if(h!=h_limit-1)*bell1+=10;
        if(h==0) *bell2 +=12;
        else if(h<=12)  *bell2 +=  h;
        else *bell2 += (h-12);
        h++;
    }
}
void count_bells(long long int * bell1, long long int * bell2, long long int diff, int y1, int m1, int d1, int h1, int i1)
{
    *bell2 =diff/10080 * 1872;
    *bell1 =diff/10080 * 1440;

    diff = diff % 10080;

    int y2,m2=0,d2=0,h2=0,i2;
    if(i1>=(diff%1440)%60) i2 = i1-(diff%1440)%60;
    else
    {
        i2 = i1 - diff%1440%60 + 60;
        h2--;
    }
    if(h1+h2 >=(diff%1440)/60) h2 += h1 - (diff%1440)/60;
    else
    {
        h2+=h1-diff%1440/60 + 24;
        d2--;
    }
    if(d1+d2>=diff/1440)
    {
        d2 += d1-diff/1440;
        m2=m1;
        y2=y1;
    }
    else {
        if (m1 == 1) {
            m2 = 12;
            y2=y1-1;
        } else m2 = m1 - 1;

        d2 += d1 - diff / 1440 + month_days(m2, y2);
    }


    int det =determination(y2,m2,d2)%7;
    for (int i =diff/1440; i>0;i--)
    {
        if(det!=0)
        {
            *bell2+=312;
            *bell1+=1440;
        }
        det++;
        det=det%7;
    }
    if(!det) hour_min_clock_counter(bell1, bell2, h2, i2, 24,60 );
    else if(d1==d2) {
         hour_min_clock_counter(bell1, bell2, 0, i2, 0, 60);
         hour_min_clock_counter(bell1, bell2, h2, 0, h1+1, i1+1);
    }
    else
        {
        hour_min_clock_counter(bell1, bell2, h2, 0, 24, i1+1);
        hour_min_clock_counter(bell1, bell2, 0, i2, h1+1, 60);

        }

}

int bells ( int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2,
            long long int * b1, long long int * b2 )
{

   if (!check_input(y1,m1,d1,h1,i1) || !check_input(y2,m2,d2,h2,i2)) return 0;
   long long int difference = time_difference(date_to_secund(y1,m1,d1,h1,i1), date_to_secund(y2,m2,d2,h2,i2));
   if(difference==-1) return 0;
    count_bells(b1, b2, difference, y2,m2,d2,h2,i2);

   return 1;
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
    /*  assert ( bells ( 2022, 10,  1, 13, 15,
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
