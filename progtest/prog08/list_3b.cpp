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
    if(size==1) return nullptr;
    char * name;
    name = (char *) malloc (size* sizeof (char));
    if(name ==nullptr) name = allocation_name(size);
    return name;
}
TITEM * newItem ( const char * name, TITEM * next )
{
    TITEM * newTI;
    newTI=allocation_item();
    size_t name_size= strlen(name)+1;
    newTI->m_Name= allocation_name(name_size);
    if (name_size!=1) strcpy(newTI->m_Name, name);
    newTI->m_Next=next;
    for(char & i : newTI->m_Secret) i='\0';
    return newTI;
}



bool name_compare(const char *name1, const char *name2, bool type) {
    return type == ASC ?  strcmp(name1, name2)>0 : strcmp(name1, name2)<0;
}

void swap_item(TITEM **firstIT, TItem **secondIT) {
    TItem ** tmp = firstIT;
    firstIT=secondIT;
    secondIT=tmp;
}


TITEM * sortList ( TITEM * l,  int ascending )
{
    bool type;
    if (ascending==0) type = DESC;
    else type = ASC;

    TITEM * done;
    TITEM * start = nullptr;
    TITEM * prev;
    TITEM * current = nullptr;

    bool isHEAD = false, isSEQ=false;

    if (l == nullptr ) return l;

    done=start=l;
    while(start->m_Next)
    {
        prev=current=start->m_Next;
        while(current) {
            if (name_compare(start->m_Name, current->m_Name, type)) {

                // If end and current have some non-zero
                // number of nodes in between them
                if (current != start->m_Next) isSEQ=true;
                    //case 1: start is head
                if (start == l) isHEAD=true;
                if(isSEQ) {
                    swap_item(&start->m_Next, &current->m_Next);
                    prev->m_Next = start;
                }
                else {
                    start->m_Next = current->m_Next;
                    current->m_Next = start;
                }
                    if(!isHEAD) done->m_Next= current;
                    swap_item(&start, &current);

                     prev=current;
                     if(isHEAD) l = start;

                     current=current->m_Next;
                     isHEAD=false;
                     isSEQ=false;
            }
            else
            {
                prev=current;
                current=current->m_Next;
            }
        }
        done=start;
        start=start->m_Next;
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
