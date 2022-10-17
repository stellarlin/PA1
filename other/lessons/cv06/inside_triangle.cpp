#include<cstdio>
#include <valarray>
#include <cfloat>

int error (void) {
    printf("Error.\n");
    return 0;
}

struct point
{
    double x;
    double y;
};

double area ( point a, point b, point c)
{

}
int main (void)
{
    point a, b, c;
    double side_a, side_b, side_c;
    printf("Zadejte vrcholy a, b, c: "
           "\"(aX, aY), (bX, bY), (cX, cY)\"\n");
    if (scanf(" ( %lf , %lf ) ,  ( %lf , %lf ) ,  ( %lf , %lf ", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y) != 6
        //a > b + c || b > a + c || c > a + b
        || getchar() != ')')
        return error();
    side_a =  sqrt(pow((a.x*a.x -b.x*b.x),2) + pow((a.y*a.y -b.y*b.y),2));
    side_b =  sqrt(pow((b.x*b.x -c.x*c.x),2) + pow((b.y*b.y -c.y*c.y),2));
    side_c =  sqrt(pow((c.x*c.x -a.x*a.x),2) + pow((c.y*c.y -a.y*a.y),2));
    if (side_a <=0 || side_b <=0|| side_c <=0
    || side_a - side_b - side_c > DBL_EPSILON*100*side_b*side_c
    || side_b - side_a - side_c > DBL_EPSILON*100*side_a*side_c
    || side_c - side_a - side_b > DBL_EPSILON*100*side_a*side_b) return error();


}