#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
constexpr int MAP_MAX = 200;
#endif /* __PROGTEST__ */

struct Square
{
    Square (int X, int Y) : x(X), y(Y) {}
    int x;
    int y;
};

struct Borders{
explicit Borders(Square castle) : west (castle.x), east (castle.x), north(castle.y), south (castle.y) {}
   int height () const {return  south - north + 1;}
    int width () const { return  east - west + 1;}
int west;
int east;
int north;
int south;
};

struct Stack
{
    int top = -1;
    int capacity;
    int * array;


    bool full () const{return top == capacity - 1;}
    bool empty () const {return top == -1;}

    void push (int item ) {
        if (full()) return;
        array[++top] = item;
    }
    void pop ()
    {
        if (empty()) return;
        top--;
    }

};

Stack* createStack(int capacity)
{
    Stack * stack = (struct Stack *) malloc (sizeof(Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int *) malloc (stack->capacity * sizeof(int));
    return stack;
}

void deleteStack (Stack ** stack)
{
    free ((*stack)->array);
    free (*stack);
}


bool underCastle (Square  square, Square  castle, int altitude[][MAP_MAX])
{
    return (castle.x == square.x && castle.y == square.y) ||
           altitude[castle.y][castle.x] > altitude[square.y][square.x];
}

int max (int a, int b)
{return a >= b ? a : b;}


// Finds the maximum area under
// the histogram represented
// by histogram. See below article for details.

void defineCross (int altitude[][MAP_MAX], Square castle,   Borders * kingdom, int size)
{
    //define North
    for (int y = castle.y - 1; y >= 0; y--)
    {
        if (!underCastle({castle.x, y}, castle, altitude)) break;
        kingdom->north--;
    }
    //define South
    for (int y = castle.y + 1; y <  size; y++)
    {
        if (!underCastle({castle.x, y}, castle, altitude)) break;
        kingdom->south++;
    }
    //define West
    for (int x = castle.x - 1; x >= 0; x--)
    {
        if (!underCastle({x, castle.y}, castle, altitude)) break;
        kingdom->west--;
    }
    //define East
    for (int x = castle.x + 1; x <  size; x++)
    {
        if (!underCastle({x, castle.y}, castle, altitude)) break;
        kingdom->east++;
    }
}



int maxHist(int row[], Square * castle, Borders * Kingdom)
{
    // Create an empty stack.
    Stack * stack = createStack(Kingdom->width());

    //----------Initialization-----------------------
    bool capital_found = false; // true when we detected bar
                                // that consists castle
    int max_area = 0;
    int curr_area;
    int x = 0;
    //----------------------------------------------
    // Run through all bars of given histogram (or row)

    while (x <  Kingdom->width()) {
        // If this bar is higher than the bar on top stack,
        // push it to stack
        if (stack->empty()) stack->push(x++);
        else if (row[stack->top] <= row[x])
        {
            if (row[x] == 0 && capital_found) break;
            if (x == castle->x) capital_found = true;
            stack->push(x++);

        }

        else {
            int & top_val = row[stack->array[stack->top]];
            stack->pop();

            if (row[x] == 0 && capital_found) break;

            curr_area = top_val * x;
            if (!stack->empty()) curr_area = top_val * (x - stack->top - 1);
            max_area = max(curr_area, max_area);
            if (x == castle->x) capital_found = true;
        }
    }

    // Now pop the remaining bars from stack and calculate
    // area with every popped bar as the smallest bar
    while (!stack->empty()) {
        int & top_val = row[stack->array[stack->top]];
        stack->pop();
        curr_area = top_val * x;
        if (!stack->empty())
            curr_area = top_val * (x - stack->top - 1);

        max_area = max(curr_area, max_area);
    }
// free memory
    deleteStack(&stack);
    return max_area;
}


int calculateKingdom (int altitude[][MAP_MAX], Square castle, int size)
{
    if (!altitude[castle.y][castle.x]) return 1;

    //define borders
    Borders Kingdom(castle);
    defineCross(altitude, castle, &Kingdom, size);

    int histograms [MAP_MAX][MAP_MAX];

    //copy first row
    for (int i  = 0; i<= Kingdom.width(); i++)
    {
        histograms[0][i] = underCastle({i + Kingdom.west, Kingdom.north }, castle, altitude);
    }
    //calculate the area of 1 row
    int max_area = maxHist(histograms[0], &castle, &Kingdom);
    //transform rows in as follows, if histograms[i][j]
    // is not zero then histograms[i][j] = histograms[i-1][j] + histograms[i][j].
    for (int y =  1; y < Kingdom.height(); y++) {

        for (int x = 0; x < Kingdom.width(); x++)
        {
            // if A[i][j] is 1 then add A[i -1][j]
            histograms[y][x] =  underCastle({x + Kingdom.west, y + Kingdom.north}, castle, altitude)
                    ? (1 + histograms[y - 1][x]) : 0;
        }

        // Update result  using "Largest Rectangular Area in a Histogram"
        // problem solutionl
        max_area = max(max_area, maxHist(histograms[y], &castle, &Kingdom));

    }
    return max_area;
}

void castleArea ( int altitude[][MAP_MAX], int size, int area[][MAP_MAX] )
{
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x ++)
        {
            area [y][x] = calculateKingdom(altitude, { x, y}, size);
        }
    }
}

void printArea ( int area[][MAP_MAX], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j ++)
        {
            printf ("%d ", area [i][j]);
        }
        printf ("\n");
    }
    printf ("\n");
}


#ifndef __PROGTEST__
bool identicalMap ( const int a[][MAP_MAX], const int b[][MAP_MAX], int n )
{
  for (int i = 0; i < n; i++) {
  for (int j = 0; j < n; j ++) if (a [i][j] != b[i][j]) return false;
  }
      return true;

}
int main ( int argc, char * argv [] )
{
  static int result[MAP_MAX][MAP_MAX];
/*
  static int alt0[MAP_MAX][MAP_MAX] =
  {
    { 1, 2 },
    { 3, 4 }
  };
  static int area0[MAP_MAX][MAP_MAX] =
  {
    { 1, 2 },
    { 2, 4 }
  };
  castleArea ( alt0, 2, result );
  //printArea(result, 2);
  assert ( identicalMap ( result, area0, 2 ) );
*/  static int alt1[MAP_MAX][MAP_MAX] =
  {
    { 2, 7, 1, 9 },
    { 3, 5, 0, 2 },
    { 1, 6, 3, 5 },
    { 1, 2, 2, 8 }
  };
  static int area1[MAP_MAX][MAP_MAX] =
  {
    { 1, 12, 2, 16 },
    { 4, 4, 1, 2 },
    { 1, 9, 4, 4 },
    { 1, 2, 1, 12 }
  };
  castleArea ( alt1, 4, result );
  //printArea(result, 4);
  assert ( identicalMap ( result, area1, 4 ) );
  static int alt2[MAP_MAX][MAP_MAX] =
  {
    { 1, 2, 3, 4 },
    { 2, 3, 4, 5 },
    { 3, 4, 5, 6 },
    { 4, 5, 6, 7 }
  };
  static int area2[MAP_MAX][MAP_MAX] =
  {
    { 1, 2, 3, 4 },
    { 2, 4, 6, 8 },
    { 3, 6, 9, 12 },
    { 4, 8, 12, 16 }
  };
  castleArea ( alt2, 4, result );
    //printArea(result, 4);
  assert ( identicalMap ( result, area2, 4 ) );
  static int alt3[MAP_MAX][MAP_MAX] =
  {
    { 7, 6, 5, 4 },
    { 6, 5, 4, 5 },
    { 5, 4, 5, 6 },
    { 4, 5, 6, 7 }
  };
  static int area3[MAP_MAX][MAP_MAX] =
  {
    { 12, 6, 2, 1 },
    { 6, 2, 1, 2 },
    { 2, 1, 2, 6 },
    { 1, 2, 6, 12 }
  };
  castleArea ( alt3, 4, result );
    //printArea(result, 4);
  assert ( identicalMap ( result, area3, 4 ) );
  static int alt4[MAP_MAX][MAP_MAX] =
  {
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 2, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 }
  };
  static int area4[MAP_MAX][MAP_MAX] =
  {
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 25, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 }
  };
  castleArea ( alt4, 5, result );
    //printArea(result, 5);
  assert ( identicalMap ( result, area4, 5 ) );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
