
#include <cstdio>

int error () {
    printf("Nespravny vstup.\n");
    return 0;
}

struct time
{
    int hour;
    int minute;
};

int main ()
{
    time first, second, res;
    int carry = 0;
    if (scanf("%d:%d %d:%d", &first.hour, &first.minute, &second.hour, &second.minute)!=4 ||
            first.hour <0 || first.hour>23 ||second.hour <0 || second.hour>23||
            first.minute<0 || first.minute>59 || second.minute<0 || second.minute>59||
            second.hour<first.hour || (second.hour==first.hour && second.minute < first.minute)) return error();
    second.minute<first.minute
    ? res.minute = second.minute - first.minute +60, carry=1
    : res.minute = second.minute-first.minute;

    res.hour = second.hour-first.hour-carry;

    printf("Time difference is %d:%d\n", res.hour, res.minute);
    return 0;
}
