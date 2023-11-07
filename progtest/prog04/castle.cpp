#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
constexpr int MAP_MAX = 200;
#endif /* __PROGTEST__ */

struct Area
{
    Area (int X, int Y) : x(X), y(Y) {}
    bool equal (Area * other) { return x == other->x && y == other->y;}
    int x;
    int y;
};

struct Borders
{
    Borders(Area * area, int size) : west (area->x >= 1 ? area->x - 1 : area->x ),
                                     east (area->x < size - 1 ? area->x + 1 : area->x),
                                     north(area->y >= 1 ? area->y - 1 : area->y),
                                     south (area->y < size - 1 ? area->y + 1 : area->y) {}
    int area () const { return (east - west + 1) * (south - north + 1);}
    int west;
    int east;
    int north;
    int south;
};

struct Node
{
    Area square;
    Node * next;
};

struct Queue
{
    explicit Queue (Borders borders) :  head (NULL), tail(NULL) {
        for (int i = borders.north; i <= borders.south; i ++)
        {
            for (int j = borders.west; j <= borders.east; j++)
            {
                push ({i,j});
            }
        }
        current = head;
    }
    void push (Area a);
    void pop (Node * node);
    Node * head, * tail, * current;

    ~Queue();


};

void Queue::push(Area a) {

    Node *tmp = (Node *) malloc(sizeof(Node));
    tmp->square = a;
    tmp->next = NULL;

    if(head == NULL) head = tmp, tail = tmp;
    else
    {
        tail->next = tmp;
        tail = tail->next;
    }
}

Queue::~Queue() {
    pop(head);
}

void Queue::pop(Node *node) {
    if (head == NULL) return;

    current = head;
    head = head->next;
    free (current);
    pop (head);
}


bool insideKingdom (Borders * kingdom, Area * square)
{
    return square->x >= kingdom->north && square->x <= kingdom->south
    && square->y >= kingdom->west && square->y <= kingdom->east;
}

bool underCastle (Area * square, Area * castle, int altitude[][MAP_MAX])
{
    return altitude[castle->x][castle->y] >= altitude [square->x][square->y];
}





int calculateKingdom (int altitude[][MAP_MAX], Area castle, int size)
{
    bool explored [MAP_MAX][MAP_MAX];

    //define borders
    Borders Kingdom (&castle, size);

    // define explored area
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) explored [i][j] = false;
    }
    explored [castle.x] [castle.y] = true;

    //define queue
    Queue queue (Kingdom);

    while (queue.current == NULL)
    {
        auto & square = queue.current->square;
        if (square.equal(&castle)) queue.current = queue.current->next;

        if (insideKingdom(&Kingdom, &square))
        {
            if (!underCastle(&square, &castle, altitude))
            {
                changeBorders(Kingdom, &castle);
            }

        }
        explored[square.x][square.y] = true;
        queue.current = queue.current->next;
    }
    return Kingdom.area();
}

void castleArea ( int altitude[][MAP_MAX], int size, int area[][MAP_MAX] )
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j ++)
        {
            area [i][j] = calculateKingdom(altitude, Area(i, j), size);
        }
    }
}

#ifndef __PROGTEST__
bool identicalMap ( const int a[][MAP_MAX], const int b[][MAP_MAX], int n )
{
  /* todo */
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
