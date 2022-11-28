
#include <cstdio>
#include <cstdlib>
#include <cctype>
struct PRODUCT
{
    char * name;
    int max_name;
    int shelf;

};

void free_products(PRODUCT **available, int max) {
for(int i =0; i<max; i++) free(available[i]->name);
free(*available);
}

bool error (PRODUCT ** available, int max) {
    free_products(available, max);
    printf("Nespravny vstup.\n");
    return 0;
}

void initial_name (char ** name,  int * max , int new_max)
{
    if(*max<new_max) *max=new_max;
    *name = (char*) malloc(*max * sizeof(char*));
    if(*name == NULL)initial_name(name, max, new_max);

}

void initial_array (PRODUCT ** available, int max_product)
{
    *available = (PRODUCT *)malloc(max_product*sizeof(PRODUCT));
    if(*available==NULL) initial_array(available, max_product);


}

void realloc_name (char  ** name, int * max_name, int new_max)
{
    char * new_name;
    new_name = (char *) realloc(*name, new_max * sizeof(char));
    if(new_name == NULL)realloc_name(name, max_name, new_max);
    *max_name=new_max;
    *name = new_name;
}


void realloc_product(PRODUCT **available, int *max) {

    PRODUCT * new_available;
    new_available = (PRODUCT *)realloc(*available, *max*2*sizeof(PRODUCT));
    if(new_available==NULL) realloc_product(available, max);

    *available=new_available;
    for(int i = 0; i<*max*2; i++)
    {
        realloc_name(&available[i]->name, &available[i]->max_name, 100);
    }

    for(int i =*max; i<*max*2; i++)
    {
        available[i]->shelf=0;
        available[i]->max_name=100;
    }
    *max*=2;
}

bool read_line(PRODUCT *available, int num, int * max_product) {
    int idx = 0;
    int new_max;
    char c;
    while(1)
    {
        new_max=0;
        if(idx>=*max_product)realloc_product(&available, max_product);
        while((c= getchar())!='\n' && c!=EOF && c!='\\') new_max++;
        initial_name (&available[idx].name, &available[idx].max_name, new_max);
        if(fgets(available[idx].name, available[idx].max_name, stdin)==NULL )break;
        available[idx].shelf=num;
        idx++;
    }
    if(!feof(stdin)) return 0;
    return 1;
}

bool read_shelf_num(int *num) {
    char c;
    int next_num;
    while (isspace(c =getchar()) && c!='\n') {}
    if( c!='#')return 0;
    if (scanf(" %d", &next_num)!=1 || next_num <= *num || (next_num!=0 && *num ==-1)) return 0;
    *num = next_num;
    return 1;
}

bool read_shelf_content(PRODUCT * available, int * max_product) {


    int shelf_num = -1;
        if(!read_shelf_num(&shelf_num)) return 0;
         while((c= getchar())!='\n') new_max++;
        read_line(available, shelf_num, max_product);

    return 1;
}

int main (void)
{

    int max_product = 10;
    PRODUCT * available_products;
    initial_array(&available_products, max_product);
    for(int i =0; i<max_product; i++)
    {
        available_products[i].shelf=0;
        available_products[i].max_name=100;
    }
    if(!read_shelf_content(available_products, &max_product)) return error(&available_products, max_product);
    free_products(&available_products, max_product);
    return 0;
}
