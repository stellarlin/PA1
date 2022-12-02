
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
int realloc_fgets(PRODUCT ** available, int product_id, int num, bool * empty_line, bool * hash_line, bool * EOF_line, bool list_line)
{

    // output: 1 - success
    //         0 - failure

    //declare tmp name
    char * tmp_name;
    int tmp_max= 100;
    initial_name(&tmp_name, tmp_max);


    //if first character is # then this is # line, we must go out the function
    char c=getchar();
   // while (isspace(c =getc(stdin)) && c!='\n' && c!=EOF) {}
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
    else if(c==EOF)
    {
        *EOF_line = 1;
        return 1;
    }
    else ungetc(c,stdin);

    //when we reach EOF, function will return error
    if(fgets(tmp_name, tmp_max, stdin)==NULL &&  (!list_line || !feof(stdin)))
    {
        free(tmp_name);
        return 0;
    }

    //define how many free space in array we have
    size_t len=strlen(tmp_name);

    while(strchr(tmp_name, '\n') == NULL && !feof(stdin)) {
        tmp_max *= 2;
        realloc_name(&tmp_name, tmp_max);
        if (fgets(tmp_name + len, tmp_max- len, stdin) == NULL &&  (!list_line || !feof(stdin)))
        {
            free(tmp_name);
            return 0;
        }
        len += strlen(tmp_name + len);
    }

    (*available)[product_id].name=tmp_name;
    if((*available)[product_id].name[strlen((*available)[product_id].name)-1] =='\n') (*available)[product_id].name[strlen((*available)[product_id].name)-1] = '\0';
    if(!list_line)(*available)[product_id].shelf=num;
    return 1;
}

//reed lines until hash line or empty line
bool read_line (PRODUCT **products, int * product_id, int num, int * max_product, bool * empty_line, bool * hash_line, bool * EOF_line, bool list_line)
{
    while(1)
    {
     // realloc memory when count of products bigger than max count
      if(*product_id>=*max_product)realloc_product(products, max_product);
     //allocating memory for name of product
        (*products)[*product_id].max_name=100;
      initial_name (&(*products)[*product_id].name, (*products)[*product_id].max_name);

        //read stdin line per line, if line starts with # or is empty, loop will end
       if(realloc_fgets(products, *product_id, num, empty_line, hash_line, EOF_line, list_line)==0
        || *EOF_line == 1 || *empty_line ==1 || *hash_line==1) break;
        (*product_id)++;
    }
    if((list_line && *EOF_line ==0 && *empty_line==0 && *hash_line==0) || (!list_line && *EOF_line==1 )) return 0;
    return 1;
}

//read number of shelf and control if input conditions met
bool read_shelf_num(int *num) {
    char c;
    int next_num;
    while (isspace(c =getchar()) && c!='\n' && EOF) {}
    if( c!='#')return 0;
    if (scanf("%d", &next_num)!=1 || next_num != *num+1 ) return 0;
    if(getchar()!='\n')return 0;
    *num = next_num;
    return 1;
}

//read input for available products line per line until empty line
bool read_shelf_content(PRODUCT ** available, int * max_product, int * shelf_num, int *product_id) {

    initial_array(available, *max_product);
    bool empty_line=0, hash_line=0, EOF_line =0;
    while(1) {
        hash_line =0;
        if (!read_shelf_num(shelf_num))break;
        if(!read_line(available, product_id, *shelf_num, max_product, &empty_line, &hash_line,&EOF_line, 0)
        || EOF_line ==1 || empty_line == 1) break;
    }
    if(empty_line!=1 && EOF_line!=0) return 0;
    return 1;
}
//read input for  list of products line per line until EOF or another list
bool  read_list_content(PRODUCT ** list, int * max_list, int *list_id, bool * EOF_line) {

    bool empty_line=0, hash_line=0;
    if( !read_line(list, list_id, 0, max_list, &empty_line, &hash_line, EOF_line, 1)
         || (empty_line!=1 && *EOF_line!=1) || *list_id ==0 ) return 0;
    return 1;
}

void transform_to_lower (char * name)
{
    for(size_t i =0; i<strlen(name); i++)
    {
        if(!isalpha(name[i]) || (islower(name[i]))) continue;
        name[i]= tolower(name[i]);
    }
}
//transform names of two products to lower mode and test if test from first product is in name of second product
// success: return a number of shelfs
// falure: return N_A
int IsSimilarProductName(char * list_pr, char * available_pr, int shelf, int N_A)
{
    transform_to_lower(available_pr);
    transform_to_lower(list_pr);
    return strstr(available_pr, list_pr)!=NULL ? shelf : N_A;
}

int IsEqualProductName(char * list_pr, char * available_pr, int shelf, int N_A)
{
    transform_to_lower(available_pr);
    transform_to_lower(list_pr);
    return !strcmp (list_pr, available_pr) ? shelf :  N_A;
}

void copy_tmp_name (char ** des, char *  src, int max_char)
{
    initial_name(des, max_char);
    strncpy(*des, src, max_char);
}
//dettect if products from list is available or not
void find_among_products(PRODUCT * list, PRODUCT * available, int list_max_id, int product_max_id, int max_shelf) {

    char *tmp_name1, *tmp_name2;
    int N_A=max_shelf+1;
    int shelf_storage, idx_storage=0;
    for (int i = 0; i < list_max_id; i++) {

        list[i].shelf = N_A;
        shelf_storage = N_A;
        copy_tmp_name(&tmp_name1,list[i].name, list[i].max_name);

        for (int j = 0; j < product_max_id; j++) {

            copy_tmp_name(&tmp_name2, available[j].name, available[j].max_name);
            list[i].shelf = IsEqualProductName(tmp_name1, tmp_name2, available[j].shelf, N_A);
            if (list[i].shelf == N_A) {
                list[i].shelf = IsSimilarProductName(tmp_name1, tmp_name2, available[j].shelf, N_A);
                if (list[i].shelf != N_A && shelf_storage ==N_A)  shelf_storage = list[i].shelf, idx_storage = j;
            }
            else{
                list[i].product_idx = j;
                free(tmp_name2);
                break;
            }
            free(tmp_name2);
        }
        if (list[i].shelf==N_A &&  shelf_storage!=N_A) list[i].shelf=shelf_storage, list[i].product_idx=idx_storage;
        free(tmp_name1);
    }
}


void swap_product (PRODUCT * first, PRODUCT *  second)
{
    PRODUCT tmp;
    tmp = *first;
    *first = *second;
    *second = tmp;
}
void sort_list(PRODUCT * list, int max_list_id)
{
    bool swapped = 1;
    int start = 0;
    int end = max_list_id-1;
    while(swapped)
    {
        swapped=0;
        for (int i = start; i < end; ++i) {
            if (list[i].shelf > list[i + 1].shelf) {
                swap_product(&list[i], &list[i + 1]);
                swapped = 1;
            }
        }
            if(!swapped) break;
            swapped = 0;
            --end;
            for (int i = end - 1; i >= start; --i) {
                if (list[i].shelf > list[i + 1].shelf) {
                    swap_product(&list[i], &list[i + 1]);
                    swapped = 1;

                }
            }
            start++;
        }

    }

void print_list(PRODUCT *list, int list_max_id, PRODUCT  * available, int max_shelf) {

    printf("Optimalizovany seznam:\n");
    for(int i = 0; i< list_max_id; i++)
    {
        printf(" %d. %s -> ", i, list[i].name);
       if( list[i]. shelf==max_shelf+1)printf("N/A\n");
        else printf ("#%d %s\n", list[i].shelf, available[list[i].product_idx].name);
    }
}

//function to sort, search and organize list
bool list_optimization(PRODUCT * list, PRODUCT * available, int max_shelf, int product_max_id)
{
    int list_id, max_list = 10;
    bool broken = 0;
    bool EOF_line =0;
    while(1)
    {
       list_id = 0;
        initial_array(&list, max_list);
        if( ! read_list_content(&list, &max_list, &list_id, &EOF_line)) { broken =1; break;}
        find_among_products (list, available, list_id, product_max_id, max_shelf);
        sort_list(list, list_id);
        print_list(list, list_id, available, max_shelf);
        free_products(list, list_id);
        if(EOF_line==1) break;

    }

    if(EOF_line!=1 || broken)
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

    if(!read_shelf_content(&available_products, &max_product, &max_shelf, &product_id)) return error(available_products, product_id);
    if(!list_optimization(list, available_products, max_shelf, product_id))return error(available_products, product_id);
    free_products(available_products, product_id);
    return 0;
}
