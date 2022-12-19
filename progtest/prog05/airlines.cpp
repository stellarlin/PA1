
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

struct MIN_DISTANCE
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

void initial_min_array(MIN_DISTANCE ** min_arr, int count)
{
    *min_arr= (MIN_DISTANCE *)malloc(count*sizeof(MIN_DISTANCE));
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

//return true if they are not equal
//using approximation error
bool dbl_eps_check( double a, double b)
{
    return fabs(a-b)>DBL_EPSILON*fabs(a+b)*30;
}

// return distance between two coordinate using the distance formula (distance=√(x2−x1)^2+(y2−y1)^2)
double distance (AIRPLANE_COORDINATE first, AIRPLANE_COORDINATE next)
{
   return  sqrt(pow(first.x-next.x, 2) + pow(first.y-next.y, 2));
}


//function to find all minimal distance for each airplane and find global minimal distance
//______________________________________________________________
//for each pair of airplanes
//1) find distance between airplane i and airplane j
//2) if global  minimum has not been defined or distance is less than global minimal distance, change  the global minimum to the current distance
//3) if minimum for this airplane has not been defined or distance is less than minimal distance, set minimum for this airplane and set count of pair to 0
//    else if distance is the same as minimal, add 1 to count
//______________________________________________________________

void find_global_min(AIRPLANE_COORDINATE * airpl_data, int count, double * global_min, MIN_DISTANCE * min_arr) {

    double diff;

    for (int i = 0; i < count - 1; i++) {
        for (int j = i+1; j < count; j++) {

            //1) find distance between airplane i and airplane j
            diff = distance(airpl_data[i], airpl_data[j]);
            //2) if global  minimum has not been defined or distance is less than global minimal distance, change  the global minimum to the current distance
            if(j==1 || (dbl_eps_check(*global_min, diff) && diff<*global_min)) *global_min=diff;

            // 3) if minimum for this airplane has not been defined or distance is less than minimal distance, set minimum for this airplane and set count of pair to 0
            //    else if distance is the same as minimal, add 1 to count
            if (j == i+1 || (dbl_eps_check(diff, min_arr[i].min) && diff < min_arr[i].min)) {
                min_arr[i].min = diff;
                min_arr[i].count = 1;
            }
            else if (!dbl_eps_check(diff, min_arr[i].min)) min_arr[i].count++;
        }
    }
}

//function to count all pairs with minimal distance

void find_global_count (MIN_DISTANCE * min_arr,  double * global_min, int * global_count, int count )
{
    for(int i = 0; i<count; i++)
    {
        if(!dbl_eps_check(min_arr[i].min,*global_min)) *global_count+=min_arr[i].count;
    }
}

//function to print global min
void print_global_min(double min) {
    printf("Vzdalenost nejblizsich letadel: %f\n", min);
}
//function to print count of pair with minimal distance
void print_global_count(int count) {
    printf("Nalezenych dvojic: %d\n", count);
}
//function to print one pair of airplanes
void print_pair(AIRPLANE_COORDINATE first, AIRPLANE_COORDINATE second) {
    printf("%s - %s\n", first.name, second.name);
}


//function to print all pairs with the closest distance between two airplanes
//______________________________________________________________
//for each  airplane, which minimal distance  is equal to global minimal distance
//for all pairs with this airplane
//1) search pair with global distance
//2) print this pair
//______________________________________________________________

void print_global_pair(AIRPLANE_COORDINATE *airpl_data, int count, double global_min, MIN_DISTANCE *min_arr) {

    double diff;

    for (int i = 0; i < count - 1; i++) {
        if (dbl_eps_check(min_arr[i].min, global_min)) continue;
        for (int j = i+1; j < count; j++) {
            //1) search pair with global distance
            diff = distance(airpl_data[i], airpl_data[j]);
            if(dbl_eps_check(diff,global_min))continue;
            //2) print this pair
            print_pair(airpl_data[i], airpl_data[j]);
        }
    }

}

int main (void)
{
    int count = 0, max=2;
    double global_min=0;
    int global_count = 0;

    MIN_DISTANCE *min_array; // consists minimal distance and count of pair  for each airplane
    AIRPLANE_COORDINATE * airpl_data, * airpl_realloc;
    initial_data(&airpl_data, max); //allocate memoru for airplane's coordinate data
    printf("Pozice letadel:\n");
    while(1)
    {
        //read airplane's positions
        if(!read_coordinate(airpl_data, &count) || getchar()==EOF) break;
        //increase array capacity if the last element of array was stored
        if(count+1>=max) realloc_data(&airpl_data, &airpl_realloc, &max);
    }
    if(!feof(stdin) || count<2) return error(&airpl_data); //if there is no pair or read conditions were not met, return error statement

    initial_min_array(&min_array, count); //allocate memory for array of minimal distance
    //set all elements to zero
    for(int i = 0; i<count; i++)
    {
        min_array[i].min=0;
        min_array[i].count=0;
    }

    //function to find the closest distance between all airplane and print it
    find_global_min(airpl_data, count, &global_min, min_array);
    print_global_min (global_min);
    //function to count pairs with the closest distance between two airplanes and print it
    find_global_count(min_array, &global_min, &global_count, count);
    print_global_count (global_count);
    //function to print all pairs with the closest distance between two airplanes
    print_global_pair(airpl_data, count, global_min, min_array);

    free(airpl_data);
    free(min_array);
    return 0;
}

