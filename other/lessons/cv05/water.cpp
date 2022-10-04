#include<stdio.h>
#include <cstdlib>
#include <ctime>

#define MINS -10000
#define MAXS 10000


int error (void) {
    printf("Error.\n");
    return 0;
}

int move_pos(void) {return ((rand()%(MAXS-MINS+1))+MINS);}

int main (void)
{
    int position, last_pos = 0;
    int goal, D;
    int count_step, record=0;
    bool flag;
    char c;


    while(!feof(stdin)) {
        srand(time(0));
        D = 50;
        flag = false;
        count_step = 0;
        goal = move_pos();
        while (!flag) {
            position = move_pos();
            if (count_step%100==0) D--;
            if (abs(goal - position) < D) {
                printf("Hori!\n");
                printf("Pocet tipu je %d\n", count_step);
                if (record==0 || count_step < record) {
                    printf("Novy rekord!\n");
                    record = count_step;
                }
               else  printf("Neni rekord... Rekord is %d\n", record);
                flag = true;
            } else if (abs(goal - position) < abs(goal - last_pos)) printf("Prihoriva\n");
            else printf("Sama voda\n");
            last_pos = position;
            count_step++;
        }
        printf("Want to continue? Y/N. \n");
        flag = false;
        while (!flag) {
            if (scanf(" %c", &c) != 1 || getchar() != '\n' ||
                (c != 'Y' && c != 'y' && c != 'n' && c != 'N'))
            {
                printf("Try again. Y/N?\n");
                while ((c=getchar())!='\n'){ }
            }
            else if (c == 'N' || c == 'n') {
                printf("Ok. Bye!\n");
                return 0;
            } else {
                printf("\n");
                flag = true;
            }
        }

        printf("\n\n");
    }


    return 0;
}



