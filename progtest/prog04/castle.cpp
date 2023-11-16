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

struct Kingdom{
explicit Kingdom(Square Castle) : castle(Castle), west (castle.x), east (castle.x), north(castle.y), south (castle.y) {}
  // int height () const {return  south - north + 1;}
    int width () const { return  east - west + 1;}

    Square castle;
    int west;
    int east;
    int north;
    int south;


};

struct Stack
{
    int current = -1;
    int capacity;
    int array[200];


    int & top (){return array[current];}
    bool full () const{return current == capacity - 1;}
    bool empty () const {return current == -1;}

    void push (int item ) {
        if (full()) return;
        array[++current] = item;
    }
    void pop ()
    {
        if (empty()) return;
        current--;
    }

};

Stack* createStack( Stack * stack, int capacity)
{
    stack->current = -1;
    stack->capacity = capacity;
    return stack;
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

void defineCross (int altitude[][MAP_MAX],  Kingdom * kingdom, int size)
{
    //define North
    for (int y = kingdom->castle.y - 1; y >= 0; y--)
    {
        if (!underCastle({kingdom->castle.x, y}, kingdom->castle, altitude)) break;
        kingdom->north--;
    }
    //define South
    for (int y = kingdom->castle.y + 1; y <  size; y++)
    {
        if (!underCastle({kingdom->castle.x, y}, kingdom->castle, altitude)) break;
        kingdom->south++;
    }
    //define West
    for (int x = kingdom->castle.x - 1; x >= 0; x--)
    {
        if (!underCastle({x, kingdom->castle.y}, kingdom->castle, altitude)) break;
        kingdom->west--;
    }
    //define East
    for (int x = kingdom->castle.x + 1; x <  size; x++)
    {
        if (!underCastle({x, kingdom->castle.y}, kingdom->castle, altitude)) break;
        kingdom->east++;
    }
}

void defineHistogramLine (int histograms[][MAP_MAX], int altitude[][MAP_MAX],
                          int line,  Kingdom * kingdom)
{
    bool castle_found = false, zeroed = false;
    // if A[i][j] is 1 then add A[i -1][j]
    for (int x = kingdom->west; x <= kingdom->east; x++)
    {
        histograms[line][x] =  !zeroed && underCastle({x, line}, kingdom->castle, altitude);
        if (histograms[line][x])
        {
            if(line != kingdom->north) histograms[line][x]  += histograms[line - 1][x];
        }
        else if (!zeroed && castle_found) zeroed = true;

        castle_found = x >= kingdom->castle.x;
    }
}


int maxHist(int row[],  Kingdom * kingdom, bool lower_half)
{
    // Create an empty stack.
    Stack stack;
    createStack(&stack, kingdom->width());

    //----------Initialization-----------------------
    int max_area = 0;
    int curr_area;
    int x = kingdom->west;
    //----------------------------------------------
    // Run through all bars of given histogram (or row)



    while (x <=  kingdom->east) {
        // If this bar is higher than the bar on top stack,
        // push it to stack

        if (row[x] == 0)
        {
           if (x>=kingdom->castle.x)
           {
               if(lower_half) kingdom->east = x - 1;
               break;
           }

           max_area = 0;
           stack.current = -1;
            if(lower_half) kingdom->west = ++x;
        }

        if (stack.empty() || row[stack.top()] <= row[x]) stack.push(x++);
        else {
            int & top_val = row[stack.top()];
            stack.pop();

            if (x>=kingdom->castle.x) {
                curr_area = (!stack.empty()) ? top_val * (x - stack.top() - 1)
                                             : top_val * (x - kingdom->west);
                max_area = max(curr_area, max_area);
            }
        }


    }

    // Now pop the remaining bars from stack and calculate
    // area with every popped bar as the smallest bar
    while (!stack.empty()) {

        int & top_val = row[stack.top()];
        stack.pop();


        curr_area = (!stack.empty()) ? top_val * (x - stack.top() - 1)
                                     : top_val * (x - kingdom->west);
        max_area = max(curr_area, max_area);
    }
    return max_area;
}



int calculateKingdom (int altitude[][MAP_MAX], Square castle, int size)
{
    if (!altitude[castle.y][castle.x]) return 1;

    //define Kingdom
    Kingdom kingdom(castle);
    defineCross(altitude,  &kingdom, size);
    bool lower_half = false;

    int histograms [MAP_MAX][MAP_MAX];

    //calculate first row

    //calculate the area of 1 row
    int max_area = 0;

    //transform rows in as follows, if histograms[i][j]
    // is not zero then histograms[i][j] = histograms[i-1][j] + histograms[i][j].
    for (int y =  kingdom.north; y <= kingdom.south; y++) {


        defineHistogramLine(histograms, altitude, y, &kingdom);
        //check if we are allowed to change Kingdom
        if (!lower_half && y > castle.y) lower_half = true;
        // Update result  using "Largest Rectangular Area in a Histogram"
        // problem solutionl
        if (y >= castle.y) max_area = max(max_area, maxHist(histograms[y], &kingdom, lower_half));
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
        printf("{");
        for (int j = 0; j < size; j ++)
        {
            printf (" %d%c", area [i][j], j == size -1 ? '}' : ',');
        }
        printf ("%c\n", i == size -1 ? '}' : ',');
    }
    printf ("};\n");
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
    static int alt0[MAP_MAX][MAP_MAX] = {
            {864, 127, 191, 680, 522, 25,  318, 392, 717, 53,  419, 419, 6,   145, 503, 347, 38,  275, 67,  455, 675, 976, 596, 655, 686},
            {246, 649, 860, 119, 999, 824, 335, 126, 367, 367, 0,   392, 686, 393, 461, 739, 164, 881, 97,  309, 736, 796, 700, 12,  863},
            {155, 39,  191, 751, 46,  877, 349, 47,  89,  468, 46,  913, 156, 524, 633, 523, 524, 25,  561, 269, 487, 653, 433, 720, 102},
            {95,  456, 899, 795, 820, 114, 302, 211, 306, 405, 257, 183, 754, 304, 625, 575, 350, 890, 731, 874, 523, 254, 751, 549, 168},
            {20,  388, 821, 454, 108, 923, 549, 916, 822, 696, 89,  937, 998, 300, 595, 403, 558, 130, 157, 214, 755, 84,  565, 998, 815},
            {791, 521, 422, 542, 422, 942, 915, 810, 763, 369, 270, 686, 270, 187, 861, 318, 628, 150, 316, 928, 745, 719, 838, 875, 228},
            {53,  983, 665, 970, 981, 480, 761, 854, 254, 656, 277, 196, 923, 439, 311, 292, 62,  350, 914, 601, 211, 232, 229, 361, 900},
            {157, 458, 971, 348, 685, 199, 401, 668, 864, 371, 1,   697, 484, 856, 303, 492, 485, 852, 415, 924, 163, 59,  338, 865, 973},
            {939, 76,  557, 168, 789, 457, 678, 599, 428, 26,  285, 980, 427, 305, 196, 150, 659, 245, 986, 515, 549, 479, 0,   753, 246},
            {276, 268, 306, 615, 134, 631, 906, 562, 189, 75,  704, 998, 753, 303, 427, 131, 940, 759, 910, 246, 955, 60,  905, 201, 46},
            {772, 102, 877, 124, 855, 124, 752, 475, 430, 719, 609, 61,  626, 524, 602, 53,  228, 601, 158, 531, 380, 289, 824, 139, 199},
            {70,  446, 611, 327, 647, 657, 451, 101, 535, 927, 308, 659, 679, 784, 441, 399, 745, 502, 377, 269, 457, 430, 497, 58,  588},
            {381, 790, 229, 205, 929, 428, 627, 727, 391, 306, 375, 48,  757, 828, 935, 684, 137, 594, 715, 921, 35,  466, 666, 890, 843},
            {288, 347, 625, 785, 757, 565, 518, 547, 794, 723, 828, 574, 702, 555, 965, 8,   282, 366, 117, 463, 301, 801, 600, 248, 517},
            {521, 635, 983, 539, 525, 179, 827, 224, 804, 965, 333, 370, 483, 880, 164, 559, 60,  91,  261, 968, 56,  270, 602, 422, 387},
            {65,  724, 541, 665, 324, 410, 538, 959, 745, 430, 837, 924, 609, 61,  81,  574, 395, 451, 58,  627, 967, 617, 40,  410, 230},
            {8,   467, 852, 962, 241, 592, 28,  317, 133, 45,  641, 895, 936, 601, 640, 366, 438, 917, 975, 851, 998, 902, 246, 801, 960},
            {226, 768, 929, 266, 179, 511, 626, 998, 364, 588, 239, 308, 968, 909, 441, 14,  550, 688, 302, 503, 328, 20,  941, 597, 347},
            {793, 595, 249, 391, 396, 561, 969, 517, 842, 235, 696, 354, 861, 46,  70,  802, 637, 378, 770, 546, 171, 136, 97,  859, 790},
            {600, 539, 810, 894, 137, 158, 39,  732, 407, 430, 481, 969, 400, 998, 811, 987, 46,  517, 201, 444, 587, 3,   81,  965, 125},
            {628, 136, 614, 725, 347, 404, 677, 887, 215, 571, 24,  725, 610, 108, 132, 393, 941, 453, 145, 939, 617, 484, 337, 486, 685},
            {781, 74,  40,  863, 391, 518, 843, 528, 132, 568, 875, 888, 597, 114, 103, 521, 490, 828, 131, 599, 313, 876, 892, 118, 373},
            {832, 87,  858, 521, 574, 895, 303, 0,   288, 518, 391, 806, 361, 271, 290, 281, 499, 178, 230, 613, 634, 751, 104, 814, 235},
            {55,  479, 111, 947, 598, 837, 131, 37,  695, 653, 963, 942, 308, 963, 230, 178, 355, 36,  539, 978, 678, 172, 477, 857, 402},
            {91,  843, 154, 547, 657, 741, 602, 137, 852, 901, 87,  41,  385, 124, 736, 390, 88,  31,  698, 403, 261, 228, 758, 650, 119}
    };
    static int area0 [MAP_MAX][MAP_MAX] = {
            { 21, 1, 2, 7, 4, 1, 2, 8, 20, 1, 9, 3, 1, 2, 11, 4, 1, 3, 1, 5, 12, 80, 1, 2, 3 },
            { 4, 8, 9, 1, 625, 24, 2, 2, 9, 2, 1, 6, 12, 2, 2, 22, 2, 32, 2, 2, 9, 16, 4, 1, 15 },
            { 3, 1, 3, 5, 1, 24, 6, 1, 2, 15, 2, 64, 1, 7, 12, 1, 4, 1, 6, 1, 2, 11, 1, 13, 1 },
            { 2, 6, 25, 6, 14, 1, 3, 3, 4, 7, 4, 1, 20, 3, 8, 10, 1, 45, 6, 21, 2, 2, 10, 2, 2 },
            { 1, 2, 10, 2, 1, 33, 5, 55, 21, 18, 1, 48, 176, 2, 7, 3, 5, 1, 2, 3, 14, 1, 2, 192, 4 },
            { 10, 4, 1, 4, 2, 84, 30, 7, 8, 2, 5, 6, 2, 1, 36, 2, 12, 2, 4, 70, 8, 11, 24, 16, 1 },
            { 1, 132, 2, 25, 120, 3, 6, 10, 1, 8, 7, 1, 39, 5, 3, 2, 1, 4, 48, 5, 2, 4, 1, 4, 10 },
            { 2, 5, 77, 2, 5, 1, 2, 5, 33, 4, 1, 9, 2, 20, 2, 8, 2, 15, 1, 38, 2, 1, 6, 12, 80 },
            { 66, 1, 4, 1, 10, 2, 6, 8, 4, 1, 8, 63, 4, 3, 2, 3, 14, 1, 160, 2, 9, 7, 1, 8, 3 },
            { 2, 3, 3, 6, 1, 6, 36, 6, 2, 2, 20, 275, 12, 1, 6, 2, 65, 8, 14, 1, 52, 1, 36, 4, 1 },
            { 9, 1, 25, 1, 22, 1, 17, 2, 3, 22, 3, 1, 12, 3, 12, 1, 2, 10, 1, 8, 2, 2, 30, 2, 2 },
            { 1, 4, 4, 3, 5, 16, 2, 1, 5, 70, 1, 6, 6, 24, 2, 4, 24, 7, 2, 1, 5, 3, 6, 1, 8 },
            { 3, 18, 2, 1, 60, 1, 4, 10, 4, 1, 3, 1, 10, 12, 75, 16, 1, 8, 16, 40, 1, 6, 6, 25, 8 },
            { 1, 2, 3, 9, 18, 4, 1, 2, 16, 2, 16, 3, 4, 1, 100, 1, 3, 6, 1, 6, 3, 15, 3, 1, 6 },
            { 7, 4, 150, 3, 8, 1, 20, 1, 14, 102, 1, 2, 3, 20, 2, 8, 1, 2, 3, 132, 1, 2, 9, 4, 2 },
            { 2, 8, 1, 6, 3, 2, 3, 68, 6, 2, 21, 24, 7, 1, 2, 12, 4, 9, 1, 8, 45, 8, 1, 3, 1 },
            { 1, 2, 6, 60, 2, 16, 1, 4, 2, 1, 7, 12, 28, 2, 12, 2, 5, 27, 119, 5, 225, 24, 2, 8, 44 },
            { 3, 11, 36, 2, 1, 3, 9, 253, 2, 8, 1, 2, 90, 20, 2, 1, 6, 8, 1, 4, 4, 1, 48, 2, 1 },
            { 26, 6, 1, 2, 7, 10, 77, 1, 18, 1, 10, 2, 18, 1, 2, 19, 8, 1, 18, 6, 3, 4, 2, 12, 8 },
            { 2, 5, 12, 33, 1, 3, 1, 7, 4, 2, 3, 78, 1, 180, 11, 150, 1, 4, 3, 2, 9, 1, 2, 68, 1 },
            { 4, 3, 4, 7, 2, 4, 6, 22, 2, 8, 1, 8, 12, 1, 4, 3, 75, 2, 2, 30, 9, 6, 3, 3, 6 },
            { 6, 2, 1, 15, 3, 6, 12, 4, 1, 6, 24, 32, 10, 2, 1, 9, 1, 20, 1, 3, 1, 20, 38, 1, 2 },
            { 30, 2, 21, 1, 9, 50, 4, 1, 3, 5, 1, 17, 4, 3, 6, 2, 9, 3, 4, 8, 9, 11, 1, 19, 1 },
            { 1, 4, 1, 60, 10, 8, 2, 2, 10, 9, 66, 10, 1, 40, 2, 1, 4, 2, 10, 125, 8, 1, 2, 15, 4 },
            { 2, 32, 2, 2, 11, 6, 6, 3, 17, 36, 2, 1, 4, 1, 15, 6, 2, 1, 12, 3, 2, 2, 15, 2, 1 }
    };

    Square castle(2,3);
//    printf ("Area of (%d, %d) is %d.\n", castle.x, castle.y, calculateKingdom(alt0, castle, 25));
    castleArea ( alt0, 25, result );
    //printArea(result, 25);
       assert ( identicalMap ( result, area0, 25 ) );
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
 // printArea(result, 4);
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
