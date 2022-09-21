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

void temp_value (int first_letter, int second_letter, double temp) {
    if (second_letter == first_letter) print_temp(temp);//
    else if (second_letter == 1 && first_letter == 0)print_temp(temp + 273.15);//
    else if (second_letter == 2 && first_letter == 0)print_temp(1.8 * temp + 32);//
    else if (second_letter == 0 && first_letter == 1) print_temp(temp - 273.15);//
    else if (second_letter == 2 && first_letter == 1)print_temp(1.8 * temp - 459.67);//
    else if (second_letter == 0 && first_letter == 2) print_temp(((temp - 32) / 1.8));//
    else print_temp((temp + 459.67) / 1.8);//
}

void row (int first_letter, int second_letter, double temp)
{
    print_name(first_letter);
    for(;second_letter<3; ++second_letter)
    {
        temp_value(first_letter,second_letter,temp);
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

int char_to_int(char c)
{
    if(c=='C') return 0;
    if(c=='K') return 1;
    else return 2;
}

void convert (double temp, char from, char to)
{
    // C=0, K = 1, F = 2//
    temp_value(char_to_int(from),+char_to_int(to),temp);

}

int main ()
{
    double temp = 0;
    char iter, from, to;
    while(!feof(stdin)) {
        printf("Teplota:\n");
        if (scanf(" %c", &iter) != 1
            || (iter != 'C' && iter != 'T'))
            return error();
        switch (iter) {
            case 'T':
                if (scanf(" %lf", &temp) != 1) return error();
                if (getchar() != '\n') return error();
                temp_table(temp);
                break;

            case 'C':
                if (scanf(" %lf %c %c", &temp, &from, &to) != 3 ||
                    (from != 'C' && from != 'K' && from != 'F') ||
                    (to != 'C' && to != 'K' && to != 'F'))
                    return error();
                if (getchar() != '\n') return error();
                convert(temp, from, to);
                break;
        }
        printf("\n");

    }
    return 0;
}
