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
    bool equal (Square  other) { return x == other.x && y == other.y;}
    bool under (Square other) { return y > other.y;}
    bool above (Square other) { return !under(other);}
    bool right (Square other) {return x < other.x;}
    bool left (Square other) { return !right(other);}

    int x;
    int y;
};

struct Borders
{
    Borders(Square castle) : west (castle.x), east (castle.x), north(castle.y), south (castle.y) {}
    int area () const { return (east - west + 1) * (south - north + 1);}
    int west;
    int east;
    int north;
    int south;

};



bool underCastle (Square  square, Square  castle, int altitude[][MAP_MAX])
{
    return altitude[castle.y][castle.x] > altitude [square.y][square.x];
}

bool insideKingdom (Borders * kingdom, Square  square)
{
    return square.x >= kingdom->north && square.x <= kingdom->south
           && square.y >= kingdom->west && square.y <= kingdom->east;
}

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

bool isCross (Square castle, Square square)
{
    return castle.x == square.x || castle.y == square.y;
}


void changeBorder ( Square castle, Square wrongSquare, Borders * kingdom)
{
    if (wrongSquare.under(castle) && wrongSquare.right(castle))
    {
        kingdom->east -= kingdom->east > wrongSquare.x ? 1 : 0;
        kingdom->south -= kingdom->south > wrongSquare.y ? 1: 0;
    }
    else if (wrongSquare.under(castle) && wrongSquare.left(castle))
    {
        kingdom->west += kingdom->west > wrongSquare.x ? 1 : 0;
        kingdom->south -= kingdom->south > wrongSquare.y ? 1: 0;
    }
    else if (wrongSquare.above(castle) && wrongSquare.right(castle))
    {
        kingdom->east -= kingdom->east > wrongSquare.x ? 1 : 0;
        kingdom->north += kingdom->north > wrongSquare.y ? 1: 0;
    }
    else
    {
        kingdom->west += kingdom->west > wrongSquare.x ? 1 : 0;
        kingdom->north += kingdom->north > wrongSquare.y ? 1: 0;
    }
}

void checkArea (int altitude[][MAP_MAX], Square castle,   Borders * kingdom, int size)

{
    for (int y = kingdom->north; y <= kingdom->south; y++)
    {
        for (int x = kingdom->west; x <= kingdom->east; x++)
        {
            if (insideKingdom(kingdom, {x,y}) || isCross (castle, {x,y}) ) continue;
            if (!underCastle( {x,y}, castle, altitude))
                changeBorder(castle, {x,y}, kingdom);
        }
    }

}


int calculateKingdom (int altitude[][MAP_MAX], Square castle, int size)
{

    //define borders
    Borders Kingdom(castle);
    defineCross(altitude, castle, &Kingdom, size);
    checkArea(altitude, castle, &Kingdom, size);

    return Kingdom.area();
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
}


#ifndef __PROGTEST__
bool identicalMap ( const int a[][MAP_MAX], const int b[][MAP_MAX], int n )
{

    return true;
  for (int i = 0; i < n; i++) {
  for (int j = 0; j < n; j ++) if (a [i][j] != b[i][j]) return false;
  }
      return true;

}
int main ( int argc, char * argv [] )
{
  static int result[MAP_MAX][MAP_MAX];

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
  printArea(result, 2);
  assert ( identicalMap ( result, area0, 2 ) );
  static int alt1[MAP_MAX][MAP_MAX] =
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
  printArea(result, 4);
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
  assert ( identicalMap ( result, area4, 5 ) );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
