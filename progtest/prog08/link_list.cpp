#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TItem
{
    struct TItem * m_Next;
    char * m_Name;
    char m_Secret[24];
} TITEM;

#endif /* __PROGTEST__ */

#define ASC 1
#define DESC 0
TITEM * allocation_item (void)
{
    TITEM * item;
    item=(TITEM *) malloc (sizeof (TITEM));
    if (item == NULL)  item = allocation_item();
    return item;
}

char * allocation_name ( size_t size)
{
    char * name;
    name = (char *) malloc (size* sizeof (char));
    if(name ==NULL) name = allocation_name(size);
    return name;
}
TITEM * newItem ( const char * name, TITEM * next )
{
   TITEM * newTI;
   newTI=allocation_item();
   size_t name_size= strlen(name)+1;
   newTI->m_Name= allocation_name(name_size);
   strcpy(newTI->m_Name, name);
   newTI->m_Next=next;
   for(size_t i=0; i<name_size;i++) newTI->m_Secret[i]='\0';
   return newTI;
}


bool name_compare(const char *name1, const char *name2, bool type) {
    return type == ASC ?  strcmp(name1, name2)>0 : strcmp(name1, name2)<0;
}

void swap_item(TITEM *firstIT, TItem *secondIT) {
    char *tmp = firstIT->m_Name;
    firstIT->m_Name=secondIT->m_Name;
    secondIT->m_Name=tmp;
}


TITEM * sortList ( TITEM * l,  int ascending )
{
    bool type;
    if (ascending==0) type = DESC;
    else type = ASC;

    TITEM * start = NULL;
    TITEM * end = NULL;
    bool swapped = true;

    if (l == NULL || l->m_Next ==NULL) return l;

    while (swapped)
    {
        swapped = 0;
        start = l;

        while (start->m_Next!=end)
        {

            if( name_compare(start->m_Name, start->m_Next->m_Name, type)) {
                swap_item(start, start->m_Next);
                swapped = 1;
            }
            start = start->m_Next;
        }
        end = start;
    }
    return l;
}

void freeList     ( TITEM * src )
{
  TITEM * tmp;
  while ( src != NULL)
  {
      tmp = src;
      src = src ->m_Next;
      free(tmp->m_Name);
      free (tmp);
  }
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    TITEM * l;
    char tmp[50];

    assert ( sizeof ( TITEM ) == sizeof ( TITEM * ) + sizeof ( char * ) + 24 * sizeof ( char ) );
    l = NULL;
    l = newItem ( "PA1", l );
    l = newItem ( "PA2", l );
    l = newItem ( "UOS", l );
    l = newItem ( "LIN", l );
    l = newItem ( "AG1", l );
    assert ( l
             && ! strcmp ( l -> m_Name, "AG1" ) );
    assert ( l -> m_Next
             && ! strcmp ( l -> m_Next -> m_Name, "LIN" ) );
    assert ( l -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "UOS" ) );
    assert ( l -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );

       l = sortList ( l, 1 );
    assert ( l
                && ! strcmp ( l -> m_Name, "AG1" ) );
       assert ( l -> m_Next
                && ! strcmp ( l -> m_Next -> m_Name, "LIN" ) );
       assert ( l -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "PA1" ) );
       assert ( l -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "UOS" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
       l = newItem ( "programming and algorithmic I", l );
       l = newItem ( "AAG", l );
       assert ( l
                && ! strcmp ( l -> m_Name, "AAG" ) );
       assert ( l -> m_Next
                && ! strcmp ( l -> m_Next -> m_Name, "programming and algorithmic I" ) );
       assert ( l -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "AG1" ) );
       assert ( l -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "LIN" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "UOS" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
       l = sortList ( l, 0 );
       assert ( l
                && ! strcmp ( l -> m_Name, "programming and algorithmic I" ) );
       assert ( l -> m_Next
                && ! strcmp ( l -> m_Next -> m_Name, "UOS" ) );
       assert ( l -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "PA2" ) );
       assert ( l -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "LIN" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AG1" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AAG" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
       freeList ( l );
       l = NULL;
       strncpy ( tmp, "PA1", sizeof ( tmp ) - 1 );
       tmp[sizeof ( tmp ) - 1 ] = '\0';
       l = newItem ( tmp, l );
       strncpy ( tmp, "PA2", sizeof ( tmp ) - 1 );
       tmp[sizeof ( tmp ) - 1 ] = '\0';
       l = newItem ( tmp, l );
       strncpy ( tmp, "UOS", sizeof ( tmp ) - 1 );
       tmp[sizeof ( tmp ) - 1 ] = '\0';
       l = newItem ( tmp, l );
       strncpy ( tmp, "LIN", sizeof ( tmp ) - 1 );
       tmp[sizeof ( tmp ) - 1 ] = '\0';
       l = newItem ( tmp, l );
       strncpy ( tmp, "AG1", sizeof ( tmp ) - 1 );
       tmp[sizeof ( tmp ) - 1 ] = '\0';
       l = newItem ( tmp, l );
       assert ( l
                && ! strcmp ( l -> m_Name, "AG1" ) );
       assert ( l -> m_Next
                && ! strcmp ( l -> m_Next -> m_Name, "LIN" ) );
       assert ( l -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "UOS" ) );
       assert ( l -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
       l = sortList ( l, 1 );
       assert ( l
                && ! strcmp ( l -> m_Name, "AG1" ) );
       assert ( l -> m_Next
                && ! strcmp ( l -> m_Next -> m_Name, "LIN" ) );
       assert ( l -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "PA1" ) );
       assert ( l -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "UOS" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
       strncpy ( tmp, "programming and algorithmic I", sizeof ( tmp ) - 1 );
       tmp[sizeof ( tmp ) - 1 ] = '\0';
       l = newItem ( tmp, l );
       strncpy ( tmp, "AAG", sizeof ( tmp ) - 1 );
       tmp[sizeof ( tmp ) - 1 ] = '\0';
       l = newItem ( tmp, l );
       assert ( l
                && ! strcmp ( l -> m_Name, "AAG" ) );
       assert ( l -> m_Next
                && ! strcmp ( l -> m_Next -> m_Name, "programming and algorithmic I" ) );
       assert ( l -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "AG1" ) );
       assert ( l -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "LIN" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "PA2" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "UOS" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
       l = sortList ( l, 0 );
       assert ( l
                && ! strcmp ( l -> m_Name, "programming and algorithmic I" ) );
       assert ( l -> m_Next
                && ! strcmp ( l -> m_Next -> m_Name, "UOS" ) );
       assert ( l -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "PA2" ) );
       assert ( l -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "PA1" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "LIN" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AG1" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
                && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AAG" ) );
       assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );

    freeList ( l );
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
