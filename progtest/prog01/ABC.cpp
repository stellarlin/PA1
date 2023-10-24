
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define DAY 1440
#define MIN_WAITING 5
#define MAX_WAITING 180

// Stop the program and show error message
int error () {
    printf("Nespravny vstup.\n");
    return 0;
}

struct CTrain
{
    CTrain(char letter) : name (letter){}
    char name;
    int arrival;
    int department;
};

int readTime ()
{
    int h, m;
    if(scanf(" %d : %d", &h, &m) !=2
       || h < 0 || h > 23
       || m < 0 || m > 59) return -1;
    return h*60 + m;
}
bool readTrain (CTrain * train)
{

    printf("Cas prijezdu vlaku %c:\n", train->name);
    if((train->arrival = readTime()) == -1) return false;
    printf("Cas odjezdu vlaku %c:\n", train->name);
    if((train->department = readTime()) == -1) return false;

    return true;
}


bool checkTransfer (const CTrain * train_a, const CTrain *  train_b)
{
    int  transfer_time = (train_b->department  < train_a->arrival) * DAY + train_b->department  - train_a->arrival;
    int arrival_difference = transfer_time - (train_b->arrival >= train_a->arrival)
            * ((train_b->department  < train_b->arrival) * DAY + train_b->department - train_b->arrival);

    return transfer_time >= MIN_WAITING && arrival_difference <= MAX_WAITING;
}


void calculateTransfer (CTrain * current, const CTrain * option1, const CTrain * option2 )
{
    char transfers [3] = "";
    int counter = 0;
    printf("Z vlaku %c ", current->name);

    if (checkTransfer(current, option1)) transfers[counter++] = option1->name;
    if (checkTransfer(current, option2)) transfers[counter++] = option2->name;

    if(counter== 0) printf("nelze prestupovat.\n");
    else
    {
        printf("lze prestoupit na vlak");
        counter == 1 ?  printf(" %c.\n", transfers[0])
        : printf("y %c a %c.\n", transfers[0], transfers[1]);
    }


}

int main (void)
{
    CTrain A('A'), B('B'), C ('C');
    if(!readTrain(&A)) return error();
    if(!readTrain(&B)) return error();
    if(!readTrain(&C)) return error();
    calculateTransfer(&A, &B, &C);
    calculateTransfer(&B, &A, &C);
    calculateTransfer(&C, &A, &B);
    return 0;
}

