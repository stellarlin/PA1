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

double count_procent (double  account, double procent, int day, int prev)
{
    if (prev==day)return account;
    if (prev == -1) prev = 0;
    account = account*procent + account;
    if (day ==0) return account;
    account = count_procent (account, procent, --day, prev);
    return account;
}
int main (void)
{
    double kredit, debit, account=0, amount = 1;
    int day, previous_day =-1;
    printf("Zadejte kreditni urok [%%]:\n");
    if (!read_procent (&kredit)) return error();
    printf("Zadejte debetni urok [%%]:\n");
    if (!read_procent (&debit)) return error();

    printf ("Zadejte transakce:\n");
    while (amount!=0) {
        if (scanf(" %d , %lf", &day, &amount) != 2 || getchar() != '\n' || day < 0
        ||( day <=previous_day && previous_day!=-1)) return error();
        account = account + amount;
        if (account > 0) account = count_procent(account,  kredit, day, previous_day);
        else if (account < 0) account = count_procent(account,  (-1)*debit, day, previous_day);
        previous_day=day;
    }
    return 0;
}