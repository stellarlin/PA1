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
    bool equal (Area  other) { return x == other.x && y == other.y;}
    int x;
    int y;
};

struct Borders
{
    Borders(int size) : west (0),
                                     east (size),
                                     north(0),
                                     south (size) {}
    int area () const { return (east - west) * (south - north);}
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
    explicit Queue (Area * castle, int size, bool explored [][MAP_MAX]) :  head (NULL), tail(NULL) {
        addSquares(*castle, size, explored);
        current = head;
    }

    Queue(Queue & other) :  head (NULL), tail(NULL), current(NULL){
        clone (other.head, other.current);
    }

    void clone(Node * node, Node * other_current) {
        if (node == NULL) return;

        push(node->square);
        if (node == other_current) current = tail;
        clone(node->next, other_current);
    }
    void addSquares (Area a, int size, bool explored [][MAP_MAX]);
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

void Queue::addSquares(Area a, int size, bool explored[][200]) {
    for (int i = a.x - (a.x == 0 ? 0 : 1);
         i <= a.x + (a.x == size - 1 ? 0 : 1)  ; i++)
    {
        for(int j = a.y - (a.y == 0 ? 0 : 1);
            j <= a.y + (a.y == size - 1 ? 0 : 1)  ; j++)
        {
            if (!explored[i][j]) push ({i,j}), explored[i][j] = true;
        }
    }
}


bool insideKingdom (Borders * kingdom, Area * square)
{
    return square->x >= kingdom->north && square->x < kingdom->south
    && square->y >= kingdom->west && square->y < kingdom->east;
}

bool underCastle (Area * square, Area * castle, int altitude[][MAP_MAX])
{
    return altitude[castle->x][castle->y] > altitude [square->x][square->y];
}

Borders  changeBorder_y(Borders *kingdom, Area castle, Area wrongSquare) {
    Borders new_kingdom  = * kingdom;
    if (wrongSquare.y < castle.y) new_kingdom.west = wrongSquare.y + 1;
    else new_kingdom.east = wrongSquare.y;
    return new_kingdom;
}
Borders  changeBorder_x(Borders *kingdom, Area castle, Area wrongSquare) {
    Borders new_kingdom  = *kingdom;
    if (wrongSquare.x < castle.x) new_kingdom.north = wrongSquare.x + 1;
    else  new_kingdom.south = wrongSquare.x;
    return new_kingdom;
}
Borders  changeBorders (Borders *kindom, Area castle, Area wrongSquare) {
    if (wrongSquare.y == castle.y) return changeBorder_x(kindom, castle, wrongSquare);
    else if (wrongSquare.x == castle.x)  return changeBorder_y(kindom, castle, wrongSquare);
}

int calculateKingdom_recursion (int altitude[][MAP_MAX], int size, Area castle,
                                bool explored [][MAP_MAX], Borders Kingdom, Queue * queue)
{
    if(queue->current == NULL) return Kingdom.area();

        auto & square = queue->current->square;
        explored[square.x][square.y] = true;

        if (insideKingdom(&Kingdom, &square))
        {
            queue->addSquares(square, size, explored);
            if (!underCastle(&square, &castle, altitude))
            {
               if (square.x != castle.x && square.y != castle.y)
               {
                   queue->current = queue->current->next;
                   Queue queue2 = *queue;
                   int result1 = calculateKingdom_recursion(altitude, size,castle, explored,
                                                            changeBorder_x(&Kingdom, castle,
                                                                           square), queue);

                   int result2 = calculateKingdom_recursion(altitude, size,castle, explored,
                                                            changeBorder_y(&Kingdom, castle,
                                                                           square), &queue2);
                   return result1 >= result2 ? result1 : result2;
               }
               else Kingdom = changeBorders (&Kingdom, castle, square);
            }
        }
    queue->current = queue->current->next;
    return calculateKingdom_recursion(altitude, size,castle, explored, Kingdom, queue);
}
int calculateKingdom_definition (int altitude[][MAP_MAX], Area castle, int size)
{
    bool explored [MAP_MAX][MAP_MAX];

    //define borders
    Borders Kingdom (size);

    // define explored area
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++) explored [i][j] = false;
    }
    explored [castle.x] [castle.y] = true;

    //define queue
    Queue queue (&castle, size, explored);
    return calculateKingdom_recursion(altitude, size,castle, explored, Kingdom, &queue);

}

void castleArea ( int altitude[][MAP_MAX], int size, int area[][MAP_MAX] )
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j ++)
        {
            area [i][j] = calculateKingdom_definition(altitude, Area(i, j), size);
        }
    }
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
