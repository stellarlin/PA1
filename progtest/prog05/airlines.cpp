
#include<cstdio>
#include <cstdlib>
#include <cmath>
#include <cfloat>

#define MAX_PLANE_NAME 200

struct AIRPLANE_COORDINATE
{
    char name [MAX_PLANE_NAME];
    double x;
    double y;
};
bool error ( AIRPLANE_COORDINATE ** a) {
    free(*a);
    printf("Nespravny vstup.\n");
    return 0;
}


void initial_data (AIRPLANE_COORDINATE ** airpl_data, int max)
{
    *airpl_data = (AIRPLANE_COORDINATE *)malloc(max*sizeof(AIRPLANE_COORDINATE));
    if(*airpl_data==NULL) initial_data(airpl_data, max);
}

void realloc_data(AIRPLANE_COORDINATE **data, AIRPLANE_COORDINATE **data_realloc,  int * max) {
    *data_realloc= (AIRPLANE_COORDINATE*)realloc(*data, (*max) * 2 * sizeof(AIRPLANE_COORDINATE));
    if(*data_realloc==NULL)realloc_data(data, data_realloc,  max);
    *max*=2;
    *data=*data_realloc;
}

bool read_coordinate(AIRPLANE_COORDINATE * airpl_data, int * count) {


    if(scanf(" %lf, %lf :  %199s", &airpl_data[*count].x, &airpl_data[*count].y, airpl_data[*count].name)!=3) return false;
        ++*count;
    return true;
}
bool dbl_eps_check( double a, double b)
{
    return fabs(a-b)>=DBL_EPSILON*100*(fabs(b) + fabs(a));
}


double distance (AIRPLANE_COORDINATE first, AIRPLANE_COORDINATE next, double * min)
{
    double dis = sqrt(pow(first.x-next.x, 2) + pow(first.y-next.y, 2));
    if(dbl_eps_check(*min, dis) && dis<*min) *min=dis;
    return dis;
}
void swap (AIRPLANE_COORDINATE * x, AIRPLANE_COORDINATE * y, AIRPLANE_COORDINATE * z)
{
    AIRPLANE_COORDINATE  tmp;
    tmp = *x;
    *x = *y;
    *y=*z;
    *z=tmp;
}

void sort_data(AIRPLANE_COORDINATE * airpl_data, int count, double * min_distance)
{
    bool swapped = true;
    double diff_1, diff_2;
    int start = 0;
    int end = count - 2;
    *min_distance =distance(airpl_data[0], airpl_data[1], min_distance);
    while(swapped)
    {
        swapped = false;
        for (int i = start; i < end; ++i) {
            diff_1=distance(airpl_data[i], airpl_data[i + 1], min_distance);
            diff_2= distance(airpl_data[i+1], airpl_data[i + 2], min_distance);
            if (dbl_eps_check(diff_2,
                             diff_1) && diff_2<diff_1) {
                swap(&airpl_data[i], &airpl_data[i + 1], &airpl_data[i + 2]);
                swapped = true;
            }
        }
            //if nothing moved, then array is sorted.
            if (!swapped)
                break;

            swapped = false;
            --end;

            // from right to left, doing the
            // same comparison as in the previous stage
        for (int i = end; i >= start; --i) {
            diff_1=distance(airpl_data[i], airpl_data[i + 1], min_distance);
            diff_2= distance(airpl_data[i+1], airpl_data[i + 2], min_distance);

            if (dbl_eps_check(diff_2,
                              diff_1) || diff_2 < diff_1)
            {
                swap(&airpl_data[i], &airpl_data[i + 1], &airpl_data[i + 2]);
                swapped = true;
           }
            }
        }
    }

int main (void)
{
    int count = 0, max=2;
    char c;
    double min_distance=0;
    AIRPLANE_COORDINATE * airpl_data, * airpl_realloc;
    initial_data(&airpl_data, max);
    printf("Pozice letadel:\n");
    while(1)
    {
        if(!read_coordinate(airpl_data, &count) || (c=getchar())==EOF || c=='/') break;
        if(count+1>=max) realloc_data(&airpl_data, &airpl_realloc, &max);
    }
    if((!feof(stdin) && c!='\n') || count<2) return error(&airpl_data);
    sort_data(airpl_data, count, &min_distance);
    free(airpl_data);
    return 0;
}
