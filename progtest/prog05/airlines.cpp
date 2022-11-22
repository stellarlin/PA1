
#include<cstdio>
#include <cstdlib>

#define MAX_PLANE_NAME 200

struct AIRPLANE_COORDINATE
{
    char name [MAX_PLANE_NAME];
    double x;
    double y;
};
bool error (void) {
    printf("Nespravny vstup.\n");
    return 0;
}


void initial_data (AIRPLANE_COORDINATE ** airpl_data)
{
    *airpl_data = (AIRPLANE_COORDINATE *)malloc(2*sizeof(AIRPLANE_COORDINATE));
    if(*airpl_data==NULL) initial_data(airpl_data);
}
bool read_coordinate(AIRPLANE_COORDINATE * airpl_data, int * count) {
    if(scanf(" %lf , %lf : %199s", airpl_data[*count]->x, &airpl_data[*count].y, airpl_data[*count].name)!=3
        || getchar()!='\n' ) return false;
        ++*count;
    return true;
}

int main (void)
{
    int count = 0;
    AIRPLANE_COORDINATE * airpl_data;
    initial_data(&airpl_data);
    printf("Pozice letadel:\n");
    while(1)
    {
        if(getchar()==EOF || !read_coordinate(airpl_data, &count)) break;

    }
    if(!feof(stdin) || count==0) return error();
    return 0;
}
