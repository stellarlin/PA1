//
// Created by София Прихач on 15.09.2022.
//
#include <cstdio>

int error () {
    printf("Nespravny vstup.\n");
    return 0;
}

int main ()
{
    int a, b , c, max, min, mid;
//<Условие> ? <если выполнено> : <если нет>
    if (scanf("%d %d %d", &a, &b, &c)!=3) return error();
    max = min = a;
    b>max ? max = b : max;
    c>max ? max = c : max;
    b<min ? min = b : min;
    c<min ? min = c : min;
    mid = a + b + c - max - min;
    printf("max = %d, mid = %d, min = %d\n", max, mid, min);

    return 0;
}
