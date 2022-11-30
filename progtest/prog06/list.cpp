
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>

struct PRODUCT
{
    int shelf;
    int product_idx;
    int max_name;
    char * name;

};

void free_products(PRODUCT *available, int max) {

    for(int i=0; i<=max; i++)free(available[i].name);
    free(available);
}

bool error (PRODUCT * available, int max){
    free_products(available, max);
    printf("Nespravny vstup.\n");
    return 0;
}

// initialize array of PRODUCTS

void initial_array (PRODUCT ** available, int max_product)
{
    *available = (PRODUCT *)malloc(max_product*sizeof(PRODUCT));
    if(*available==NULL) initial_array(available, max_product);
}

//initialize name of product
void initial_name (char ** name,  int  max )
{
    *name = (char*) malloc(max * sizeof(char));
    if(*name == NULL)initial_name(name, max);

}
//realloc name of product
void realloc_name (char  ** name, int  max)
{
    char * new_name;
    new_name = (char *) realloc(*name, max * sizeof(char));
    if(new_name == NULL)realloc_name(name, max);
    *name = new_name;
}

//realloc array of products
void realloc_product(PRODUCT **available, int *max) {

    PRODUCT * new_available=*available;

    *available = (PRODUCT *)realloc(*available, *max*2*sizeof(PRODUCT));
    if(*available==NULL) realloc_product(&new_available, max);
    *max*=2;
}

//read input line per line, realloc if we don't reach the end of line
int realloc_fgets(PRODUCT ** available, int product_id, int num, bool * empty_line, bool * hash_line, bool list_line)
{

    // output: 1 - success
    //         0 - failure

    //declare tmp name
    char * tmp_name;
    int tmp_max= 100;
    initial_name(&tmp_name, tmp_max);


    //if first character is # then this is # line, we must go out the function
    char c;
    while (isspace(c =getc(stdin)) && c!='\n') {}
    if(c=='#')
    {
          ungetc(c, stdin);
          *hash_line = 1;
          return !list_line;
    }
    //if line is empty, previous product was the last one
    else if(c=='\n')
    {
        *empty_line = 1;
        return 1;
    }
    else ungetc(c,stdin);

    //when we reach EOF, function will return error
    if(fgets(tmp_name, tmp_max, stdin)==NULL)
    {
        free(tmp_name);
        return 0;
    }


    //define how many free space in array we have
    size_t len=strlen(tmp_name);

    while(strchr(tmp_name, '\n') == NULL) {
        tmp_max *= 2;
        realloc_name(&tmp_name, tmp_max);
        if (fgets(tmp_name + len, tmp_max- len, stdin) == NULL)
        {
            free(tmp_name);
            return 0;
        }
        len += strlen(tmp_name + len);
    }

    (*available)[product_id].name=tmp_name;
    (*available)[product_id].name[strlen((*available)[product_id].name)-1] = '\0';
    if(!list_line)(*available)[product_id].shelf=num;
    return 1;
}

//reed lines until hash line or empty line
bool read_line (PRODUCT **available, int * product_id, int num, int * max_product, bool * empty_line, bool * hash_line, bool list_line)
{

    while(1)
    {
     // realloc memory when count of products bigger than max count
      if(*product_id>=*max_product)realloc_product(available, max_product);
     //allocating memory for name of product
        (*available)[*product_id].max_name=100;
      initial_name (&(*available)[*product_id].name, (*available)[*product_id].max_name);

        //read stdin line per line, if line starts with # or is empty, loop will end
       if(realloc_fgets(available, *product_id, num, empty_line, hash_line, list_line)==0
        || *empty_line ==1 || *hash_line==1) break;

       ++*product_id;
    }
    if(feof(stdin) || (*empty_line==0 && *hash_line==0)) return 0;
    return 1;
}

//read number of shelf and control if input conditions met
bool read_shelf_num(int *num) {
    char c;
    int next_num;
    while (isspace(c =getchar()) && c!='\n') {}
    if( c!='#')return 0;
    if (scanf("%d", &next_num)!=1 || next_num != *num+1 ) return 0;
    if(getchar()!='\n')return 0;
    *num = next_num;
    return 1;
}

//read input for available products line per line until empty line
bool read_shelf_content(PRODUCT ** available, int * max_product, int * shelf_num, int *product_id, bool list_line) {

    initial_array(available, *max_product);
    bool empty_line=0, hash_line;
    while(1) {
        hash_line =0;
        if (!read_shelf_num(shelf_num))break;
        if(!read_line(available, product_id, *shelf_num, max_product, &empty_line, &hash_line, list_line))break;
        if (empty_line == 1) break;
    }
    if(feof(stdin) || empty_line!=1) return 0;
    return 1;
}
//read input for  list of products line per line until EOF or another list
bool  read_list_content(PRODUCT ** list, int * max_list, int *list_id, bool list_line) {

    bool empty_line=0, hash_line;
    if( !read_line(list, list_id, 0, max_list, &empty_line, &hash_line, list_line)
         ||   (!feof(stdin)&&!empty_line)  || *list_id ==0 )
    {
        free_products(*list, *max_list);
        return 0;
    }
    return 1;
}

//transform names of two products to lower mode and test if test from first product is in name of second product
// success: return a number of shelfs
// falure: return N_A
int IsSameProduct(char * inList, char * available_pr, int shelf, int N_A)
{
    for(size_t i =0; i<strlen(available_pr); i++)
    {
        if(!isalpha(available_pr[i]) || (islower(available_pr[i]))) continue;
        available_pr[i]= tolower(available_pr[i]);
    }
    for(size_t i =0; i<strlen(inList); i++)
    {
        if(!isalpha(inList[i]) || (islower(inList[i]))) continue;
        inList[i]= tolower(inList[i]);
    }
    if(strstr(inList, available_pr)!=NULL) return shelf;
    return N_A;
}

//dettect if products from list is available or not
void find_among_products(PRODUCT * list, PRODUCT * available, int max_list, int max_product, int max_shelf) {

    char *tmp_name1, *tmp_name2;
    for (int i = 0; i < max_list; i++) {
        initial_name(&tmp_name1, list[i].max_name);
        for (int j = 0; j < max_product; j++) {
            initial_name(&tmp_name2, available[j].max_name);
            list[i].shelf = IsSameProduct(tmp_name1, tmp_name2, available[j].shelf, max_shelf);
            if (list[i].shelf != max_shelf) {
                list[i].product_idx = j;
                free(tmp_name2);
                break;
            }
        }
        free(tmp_name1);
    }
}


int qsort_comparator( const void *first, const  void *second)
{
    const PRODUCT *p1 = (PRODUCT *)first;
    const PRODUCT *p2 = (PRODUCT *)second;
    if (p1->shelf < p2->shelf)
        return -1;
    else if (p1->shelf > p2->shelf)
        return 1;
    else
        return 0;
}

void sort_list(PRODUCT * list, int max_list)
{
qsort(list, max_list, sizeof(PRODUCT), qsort_comparator);
}

void print_list(PRODUCT *list, int max_list, PRODUCT  * available, int max_shelf) {

    printf("Optimalizovany seznam:\n");
    for(int i = 0; i< max_list; i++)
    {
        printf(" %d. %s -> ", i, list[i].name);
       if( list[i]. shelf==max_shelf)printf("N/A\n");
        else printf ("#%d %s\n", list[i].product_idx, available[list[i].product_idx].name);
    }
}

//function to sort, search and organize list
bool list_optimization(PRODUCT * list, PRODUCT * available, int max_shelf, int max_product)
{
    int list_id, max_list = 10;
    while(1)
    {
       list_id = 0;
        initial_array(&list, max_list);
    if(! read_list_content(&list, &max_list, &list_id, 1) || feof(stdin)) break;
    find_among_products (list, available, max_list, max_product, max_shelf);
    sort_list(list, max_list);
    print_list(list, max_list, available, max_shelf);
    free_products(list, list_id);
    }
    if(!feof(stdin))
    {
        free_products(list, list_id);
        return 0;
    }
    return 1;
}



int main (void)
{
    int product_id = 0;
    int max_product = 10, max_shelf=-1;
    PRODUCT * available_products = NULL, *list = NULL;

    if(!read_shelf_content(&available_products, &max_product, &max_shelf, &product_id, 0)) return error(available_products, product_id);
    if(!list_optimization(list, available_products, max_shelf, max_product))return error(available_products, product_id);
    free_products(available_products, product_id);
    return 0;
}
