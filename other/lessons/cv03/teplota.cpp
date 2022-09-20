#include <cstdio>

int error () {
    printf("Nespravny vstup.\n");
    return 0;
}

void print_temp(double temp)
{
    printf("%.2lf\t", temp);
}

void print_name (int first_letter)
{
    if(first_letter==0)printf("°C\t\t");
    else if (first_letter==1)printf(" K\t\t");
    else if (first_letter==2)printf("°F\t\t");
}

void row (int first_letter, int second_letter, double temp)
{
    print_name(first_letter);
    for(;second_letter<3; ++second_letter)
    {

        if(second_letter==first_letter) print_temp(temp);//
        else if (second_letter==1 && first_letter==0)print_temp(temp+273.15);//
        else if (second_letter==2 && first_letter==0)print_temp(1.8*temp +32);//
        else if (second_letter ==0 && first_letter==1) print_temp(temp-273.15);//
        else if (second_letter==2 && first_letter==1)print_temp(1.8*temp- 459.67);//
        else if (second_letter==0 && first_letter==2) print_temp(((temp-32)/1.8));//
        else print_temp((temp+459.67)/1.8);//
    }
    printf("\n");
}

void temp_table (double temp)
{
 // C=0, K = 1, F = 2//
 int first_letter = 0, second_letter = 0;
 printf("\\/\\/\\/\\\t °C\t\t K\t\t °F\n");
 for (;first_letter<3; ++first_letter)
 {
     row (first_letter, second_letter, temp);
 }
}
int main ()
{
    double temp = 0;
    printf("Teplota:\n");
    if(scanf("%lf", &temp)!=1) return error();
    if (getchar()!='\n') return error();
    temp_table(temp);

    return 0;
}
