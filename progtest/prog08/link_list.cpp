#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

typedef struct TItem
{
    struct TItem * m_Next;
    char * m_Name;
    char m_Secret[24];
} TITEM;

int cmpName ( const TITEM * a,
              const TITEM * b )
{
    return strcmp ( a -> m_Name, b -> m_Name );
}

int cmpNameInsensitive ( const TITEM * a,
                         const TITEM * b )
{
    return strcasecmp ( a -> m_Name, b -> m_Name );
}

int cmpNameLen ( const TITEM * a,
                 const TITEM * b )
{
    size_t la = strlen ( a -> m_Name ), lb = strlen ( b -> m_Name );
    return ( lb < la ) - ( la < lb );
}

#endif /* __PROGTEST__ */

#define ASC 1
#define DESC 0
TITEM * allocation_item (void)
{
    TITEM * item;
    item=(TITEM *) malloc (sizeof (TITEM));
    if (item == nullptr)  item = allocation_item();
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


bool name_compare(TITEM * firstIT, TITEM * secondIT,  bool type, int (* cmpFn) ( const TITEM *, const TITEM *)) {
    return type == ASC ?  cmpFn(firstIT, secondIT) > 0 : cmpFn(firstIT, secondIT) < 0;
}




TITEM * sorting_condition_combine(TITEM *first, TITEM *second, const bool type, int (* cmpFn) ( const TITEM *, const TITEM *)) {
    TITEM * res;
    if ( !first) return second;
    else if (!second) return first;
    if (name_compare(first, second, type, cmpFn))
    {
        res = second;
        res->m_Next= sorting_condition_combine(first, second->m_Next, type, cmpFn);
    }
    else

    {
        res = first;
        res->m_Next= sorting_condition_combine(first->m_Next, second, type, cmpFn);
    }
        return res;
}


void split_list(TITEM *src, TITEM **first, TITEM **second) {

    TITEM * slow = src;
    TITEM * fast = src ->m_Next;

    while (fast)
    {
        fast = fast->m_Next;
        if (fast)
        {
            slow=slow->m_Next;
            fast = fast->m_Next;
        }
    }
    *first = src;
    *second=slow->m_Next;
    slow->m_Next = NULL;
}


TITEM * sortListCmp  ( TITEM* l, int ascending, int (* cmpFn) ( const TITEM *, const TITEM *) )
{

    int type;
    if (ascending==0) type = DESC;
    else type = ASC;

    TITEM * head = l;
    TITEM * first;
    TITEM * second;

    if (head == nullptr || head->m_Next == nullptr) return l;
    split_list(head, &first, &second);
    first = sortListCmp(first, type, cmpFn);
    second = sortListCmp(second, type, cmpFn);

    l = sorting_condition_combine (first, second, type, cmpFn);
    return l;
}

void freeList     ( TITEM * src )
{
  TITEM * tmp = src;
  while ( src)
  {
      src = src ->m_Next;
      free(tmp->m_Name);
      free (tmp);
      tmp = src;
  }
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{

    TITEM * l;
    char tmp[50];

    assert ( sizeof ( TITEM ) == sizeof ( TITEM * ) + sizeof ( char * ) + 24 * sizeof ( char ) );
    l = NULL;
    //l = newItem ( "", l );
    l = newItem ( "BI-PA1", l );
    l = newItem ( "BIE-PA2", l );
    l = newItem ( "NI-PAR", l );
    l = newItem ( "lin", l );
    l = newItem ( "AG1", l );
    assert ( l
             && ! strcmp ( l -> m_Name, "AG1" ) );
    assert ( l -> m_Next
             && ! strcmp ( l -> m_Next -> m_Name, "lin" ) );
    assert ( l -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
    assert ( l -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    l = sortListCmp ( l, 1, cmpName );
    assert ( l
             && ! strcmp ( l -> m_Name, "AG1" ) );
    assert ( l -> m_Next
             && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
    assert ( l -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
    assert ( l -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    l = sortListCmp ( l, 1, cmpNameInsensitive );
    assert ( l
             && ! strcmp ( l -> m_Name, "AG1" ) );
    assert ( l -> m_Next
             && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
    assert ( l -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
    assert ( l -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    l = sortListCmp ( l, 1, cmpNameLen );
    assert ( l
             && ! strcmp ( l -> m_Name, "AG1" ) );
    assert ( l -> m_Next
             && ! strcmp ( l -> m_Next -> m_Name, "lin" ) );
    assert ( l -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
    assert ( l -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    l = newItem ( "AAG.3", l );
    assert ( l
             && ! strcmp ( l -> m_Name, "AAG.3" ) );
    assert ( l -> m_Next
             && ! strcmp ( l -> m_Next -> m_Name, "AG1" ) );
    assert ( l -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "lin" ) );
    assert ( l -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    l = sortListCmp ( l, 0, cmpNameLen );
    assert ( l
             && ! strcmp ( l -> m_Name, "BIE-PA2" ) );
    assert ( l -> m_Next
             && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
    assert ( l -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
    assert ( l -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "AAG.3" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AG1" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    freeList ( l );
    l = NULL;
    strncpy ( tmp, "BI-PA1", sizeof ( tmp ) - 1 );
    tmp[sizeof ( tmp ) - 1 ] = '\0';
    l = newItem ( tmp, l );
    strncpy ( tmp, "BIE-PA2", sizeof ( tmp ) - 1 );
    tmp[sizeof ( tmp ) - 1 ] = '\0';
    l = newItem ( tmp, l );
    strncpy ( tmp, "NI-PAR", sizeof ( tmp ) - 1 );
    tmp[sizeof ( tmp ) - 1 ] = '\0';
    l = newItem ( tmp, l );
    strncpy ( tmp, "lin", sizeof ( tmp ) - 1 );
    tmp[sizeof ( tmp ) - 1 ] = '\0';
    l = newItem ( tmp, l );
    strncpy ( tmp, "AG1", sizeof ( tmp ) - 1 );
    tmp[sizeof ( tmp ) - 1 ] = '\0';
    l = newItem ( tmp, l );
    assert ( l
             && ! strcmp ( l -> m_Name, "AG1" ) );
    assert ( l -> m_Next
             && ! strcmp ( l -> m_Next -> m_Name, "lin" ) );
    assert ( l -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
    assert ( l -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    l = sortListCmp ( l, 1, cmpName );
    assert ( l
             && ! strcmp ( l -> m_Name, "AG1" ) );
    assert ( l -> m_Next
             && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
    assert ( l -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
    assert ( l -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    l = sortListCmp ( l, 1, cmpNameInsensitive );
    assert ( l
             && ! strcmp ( l -> m_Name, "AG1" ) );
    assert ( l -> m_Next
             && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
    assert ( l -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
    assert ( l -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    l = sortListCmp ( l, 1, cmpNameLen );
    assert ( l
             && ! strcmp ( l -> m_Name, "AG1" ) );
    assert ( l -> m_Next
             && ! strcmp ( l -> m_Next -> m_Name, "lin" ) );
    assert ( l -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
    assert ( l -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    strncpy ( tmp, "AAG.3", sizeof ( tmp ) - 1 );
    tmp[sizeof ( tmp ) - 1 ] = '\0';
    l = newItem ( tmp, l );
    assert ( l
             && ! strcmp ( l -> m_Name, "AAG.3" ) );
    assert ( l -> m_Next
             && ! strcmp ( l -> m_Next -> m_Name, "AG1" ) );
    assert ( l -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "lin" ) );
    assert ( l -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "BI-PA1" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "BIE-PA2" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    l = sortListCmp ( l, 0, cmpNameLen );
    assert ( l
             && ! strcmp ( l -> m_Name, "BIE-PA2" ) );
    assert ( l -> m_Next
             && ! strcmp ( l -> m_Next -> m_Name, "BI-PA1" ) );
    assert ( l -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Name, "NI-PAR" ) );
    assert ( l -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Name, "AAG.3" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "AG1" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
             && ! strcmp ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "lin" ) );
    assert ( l -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    freeList ( l );
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
