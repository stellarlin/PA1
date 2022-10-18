#include <cstdio>
#include <cmath>
#include <cfloat>

int error (void)
{
    printf ("Nespravny vstup.\n");
    return 0;
}
bool read_procent(double * proc)
{
    return (scanf(" %lf", &*proc)==1
    && getchar()=='\n'
    && *proc > 0);
}

void count_procent (double * account, double procent,  int day, int prev)
{
    if (prev==day || day ==0)return;
    if (prev == -1) prev = 0;
    if(*account >=0) *account +=  floor(*account*procent)/100;
    else  *account +=  ceil(*account*procent)/100;
   count_procent(&*account,  procent, --day,  prev);
}
int main (void)
{
    double kredit, debit, account=0, amount = 1;
    int  day, previous_day =-1;
    printf("Zadejte kreditni urok [%%]:\n");
    if (!read_procent (&kredit)) return error();
    printf("Zadejte debetni urok [%%]:\n");
    if (!read_procent (&debit)) return error();

    printf ("Zadejte transakce:\n");
    while (amount!=0) {
        if (scanf(" %d , %lf", &day, &amount) != 2 || getchar() != '\n' || day < 0
        || day <=previous_day) return error();

        if (account >= 0) count_procent(&account, kredit, day, previous_day);
        else count_procent(&account, debit, day, previous_day);
        previous_day=day;
        account = account + amount;
    }
    printf ("Zustatek: %.2f\n", account);
    return 0;
}