#include <cstdio>
#include <cstdlib>

struct MOVE_NOTATION
{
    int match_idx;
    char direction;
};


int error (void)
{
    printf ("Nespravny vstup.\n");
    return 0;
}

void print_match_count (MOVE_NOTATION *  game_progress, const int count)
{
for(int i =0; i<count-1;i++)
{
    if(game_progress[i].direction!=0 && game_progress[i+1].direction!=0)
    {
        printf("%d%c,",game_progress[i].match_idx, game_progress[i].direction);
    }
    else if(game_progress[i].direction!=0 && game_progress[i+1].direction!=0)
    {
        printf("%d%c\n",game_progress[i].match_idx, game_progress[i].direction);
    }
    else return;
}
}

int new_current(char * matches,  const int count, int current ) {

    int new_current=current;
    while (matches[new_current]!='1' &&  new_current<count) new_current++;

    if(new_current==current)
    {
        while (matches[new_current]!='1' &&  new_current<count) new_current--;
    }
    return new_current==current ? current : new_current;
}

int step_destination(int current, char * matches, const int step, const int count, bool direction) {

    int sum =0;
    int idx = current;
    if(direction == 0) {
        while (sum != step + 1 && idx < count - 1) {
            if (matches[idx] == '1')sum++;
            else if (matches[idx] == 'X')sum += 2;
            idx++;
        }
    }
    else
    {
          while (sum != step - 1 && idx > 0) {
            if (matches[idx] == '1')sum++;
            else if (matches[idx] == 'X')sum += 2;
            idx++;
        }
    }
    return idx == current ? current : idx;
}

void game_iteration (MOVE_NOTATION *game_progress, int * solutions_counter, int * game_idx, char * matches, const int count, const int step, int * current, int * one_match)
{
    //return condition
    if(*one_match==0)
    {
        print_match_count(game_progress, count);
        (*solutions_counter)++;
        *one_match=count;
        *game_idx=0;
        for(int i=0; i<count;i++) game_progress[i]={0, 0};
    }
    // step to right
    bool toRight =0, toLeft=0;
    int destination_idx = step_destination(*current, matches, step, count, 0);
    if(destination_idx!=*current && matches[destination_idx] !='X' && matches[destination_idx] !='0')
    {
        toRight=1;
        matches[*current]='0';
        matches[*current+step+1]='X';
        (*one_match)-=2;

        game_progress[*game_idx]={*current, 'R'};
        (*game_idx)++;
        if(*current!=new_current(matches, count, *current)) {
            *current=new_current(matches, count, *current);
            game_iteration(game_progress, solutions_counter, game_idx, matches, count, step, current, one_match);
        }
    }

    //step to left
    step_destination(*current, matches, step, count, 1);
     if(destination_idx!=*current && matches[destination_idx] !='X' && matches[destination_idx] !='0')
    {
         toLeft=1;
        matches[*current]='0';
        matches[*current-step-1]='X';
        (*one_match)-=2;

        game_progress[*game_idx]={*current, 'L'};
        (*game_idx)++;
        if(*current!=new_current(matches, count, *current)) {
            *current=new_current(matches, count, *current);
            game_iteration(game_progress, solutions_counter,game_idx, matches, count, step, current, one_match);
        }
    }

     if(!toLeft && !toRight)
     {

     }

}


void move_match(char * matches, int count, int step) {

    MOVE_NOTATION *game_progress;
    game_progress=(MOVE_NOTATION *) malloc(count *sizeof(MOVE_NOTATION));
    for(int i=0; i<count;i++) game_progress[i]={0, 0};
    int solutions_counter=0, one_match=count, game_idx=0, current =0;
   /*( if(count % step !=0 || step==1)
    {
    printf("Celkem reseni: %d\n", count_solutions);
    return;
    }

    */

    game_iteration (game_progress, &solutions_counter, &game_idx, matches, count,  step, &current, &one_match);
    printf("Celkem reseni: %d\n", solutions_counter);
    free(game_progress);
}

int main (void)

{
    int count_match =-1, step =-1;
    char * matches;
    printf ("Pocet sirek:\n");
    if(scanf(" %d", &count_match)!=1 || count_match<2 || getchar()!='\n') return error();
    printf ("Velikost skoku:\n");
    if(scanf(" %d", &step)!=1 || step <0 || getchar()!='\n') return error();

    matches = (char*) malloc ( count_match *sizeof(char));
    for(int i =0; i<count_match; i++) matches[i]='1';

    move_match(matches, count_match, step);
    free(matches);
    return 0;

}