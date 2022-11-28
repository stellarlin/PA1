
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

struct MIN_ARRAY
{
    double min;
    int count;
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

void initial_min_array(MIN_ARRAY ** min_arr, int count)
{
    *min_arr= (MIN_ARRAY *)malloc(count*sizeof(MIN_ARRAY));
    if(*min_arr==NULL) initial_min_array(min_arr, count);

}

void realloc_data(AIRPLANE_COORDINATE **data, AIRPLANE_COORDINATE **data_realloc,  int * max) {
    *data_realloc= (AIRPLANE_COORDINATE*)realloc(*data, (*max) * 2 * sizeof(AIRPLANE_COORDINATE));
    if(*data_realloc==NULL)realloc_data(data, data_realloc,  max);
    *max*=2;
    *data=*data_realloc;
}

bool read_coordinate(AIRPLANE_COORDINATE * airpl_data, int * count) {


    if(scanf(" %lf , %lf :  %199s", &airpl_data[*count].x, &airpl_data[*count].y, airpl_data[*count].name)!=3) return false;
    ++*count;
    return true;
}
bool dbl_eps_check( double a, double b)
{
    return fabs(a-b)>DBL_EPSILON*fabs(a+b)*30;
}


double distance (AIRPLANE_COORDINATE first, AIRPLANE_COORDINATE next)
{
    return  sqrt(pow(first.x-next.x, 2) + pow(first.y-next.y, 2));

}

void min_dist_count(AIRPLANE_COORDINATE * airpl_data, int count, double * global_min, MIN_ARRAY * min_arr) {
    double diff;

    for (int i = 0; i < count - 1; i++) {
        for (int j = i+1; j < count; j++) {
            diff = distance(airpl_data[i], airpl_data[j]);
            if(j==1 || (dbl_eps_check(*global_min, diff) && diff<*global_min)) *global_min=diff;
            if (j == i+1 || (dbl_eps_check(diff, min_arr[i].min) && diff < min_arr[i].min)) {
                min_arr[i].min = diff;
                min_arr[i].count = 0;
            }

            if (!dbl_eps_check(diff, min_arr[i].min)) min_arr[i].count++;
        }
    }
}


void global_count_sum (MIN_ARRAY * min_arr,  double * global_min, int * global_count, int count )
{
    for(int i = 0; i<count; i++)
    {
        if(!dbl_eps_check(min_arr[i].min,*global_min)) *global_count+=min_arr[i].count;
    }
}

void print_global_min(double min) {
    printf("Vzdalenost nejblizsich letadel: %f\n", min);
}
void print_global_count(int count) {
    printf("Nalezenych dvojic: %d\n", count);
}

void print_pair(AIRPLANE_COORDINATE first, AIRPLANE_COORDINATE second) {
    printf("%s - %s\n", first.name, second.name);
}

void min_pair_print(AIRPLANE_COORDINATE *airpl_data, int count, double global_min, MIN_ARRAY *min_arr) {

    double diff;

    for (int i = 0; i < count - 1; i++) {
        if (dbl_eps_check(min_arr[i].min, global_min)) continue;
        for (int j = i+1; j < count; j++) {
            diff = distance(airpl_data[i], airpl_data[j]);
            if(dbl_eps_check(diff,global_min))continue;
            print_pair(airpl_data[i], airpl_data[j]);
        }
    }

}

int main (void)
{
    int count = 0, max=2;
    double global_min=0;
    int global_count = 0;

    MIN_ARRAY *min_array;
    AIRPLANE_COORDINATE * airpl_data, * airpl_realloc;
    initial_data(&airpl_data, max);
    printf("Pozice letadel:\n");
    while(1)
    {
        if(!read_coordinate(airpl_data, &count) || getchar()==EOF) break;
        if(count+1>=max) realloc_data(&airpl_data, &airpl_realloc, &max);
    }
    if(!feof(stdin) || count<2) return error(&airpl_data);

    initial_min_array(&min_array, count);
    for(int i = 0; i<count; i++)
    {
        min_array[i].min=0;
        min_array[i].count=0;
    }

    min_dist_count(airpl_data, count, &global_min, min_array);
    print_global_min (global_min);
    global_count_sum(min_array, &global_min, &global_count, count);
    print_global_count (global_count);
    min_pair_print(airpl_data, count, global_min, min_array);
    free(airpl_data);
    free(min_array);
    return 0;
}
