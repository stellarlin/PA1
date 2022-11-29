
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>

struct PRODUCT
{
    char * name;
    int max_name;
    int shelf;

};

void free_products(PRODUCT *available) {
free(available->name);
free(available);
}

bool error (PRODUCT * available ){
    free_products(available);
    printf("Nespravny vstup.\n");
    return 0;
}

void initial_name (char ** name,  int  max )
{
    *name = (char*) malloc(max * sizeof(char*));
    if(*name == NULL)initial_name(name, max);

}

void initial_array (PRODUCT ** available, int max_product)
{
    *available = (PRODUCT *)malloc(max_product*sizeof(PRODUCT));
    if(*available==NULL) initial_array(available, max_product);


}

void realloc_name (char  ** name, int  max)
{
    char * new_name;
    new_name = (char *) realloc(*name, max * sizeof(char));
    if(new_name == NULL)realloc_name(name, max);
    *name = new_name;
}


void realloc_product(PRODUCT **available, int *max) {

    PRODUCT * new_available;
    new_available = (PRODUCT *)realloc(*available, *max*2*sizeof(PRODUCT));
    if(new_available==NULL) realloc_product(available, max);

    *available=new_available;
    for(int i = 0; i<*max*2; i++)
    {
        realloc_name(&available[i]->name, available[i]->max_name);
    }

    for(int i =*max; i<*max*2; i++)
    {
        available[i]->shelf=0;
        available[i]->max_name=100;
    }
    *max*=2;
}


int realloc_fgetc(PRODUCT * available, int idx, int num)
{
    char * tmp_name;
    char c;
    int tmp_max= 100;
    initial_name(&tmp_name, tmp_max);
    if((c=getc(stdin))=='#')
    {
          ungetc('#', stdin);
          return 2;
    }
    ungetc(c,stdin);
    if(fgets(tmp_name, tmp_max, stdin)==NULL)
    {
        free(tmp_name);
        return 0;
    }


    size_t len=strlen(tmp_name);

    while(strchr(tmp_name, '\n') == NULL) {
        tmp_max += 100;
        realloc_name(&tmp_name, tmp_max);
        if (fgets(tmp_name + len, tmp_max- len, stdin) == NULL)
        {
            free(tmp_name);
            return 0;
        }
        len += strlen(tmp_name + len);
    }
    available[idx].name=tmp_name;
    available[idx].name[strlen(available[idx].name)-1] = '\0';
    available[idx].shelf=num;
    return 1;
}
bool read_line(PRODUCT *available, int num, int * max_product) {
    int idx = 0;
    int res = 1;
    bool flag=1;
    while(1)
    {
      if(idx>=*max_product)realloc_product(&available, max_product);
      initial_name (&available[idx].name, available[idx].max_name);
       if((res =realloc_fgetc(available, idx, num))==0 )
       {
           flag = 0;
           break;
       }
       if(res==2 )break;
       idx++;
    }
    if(feof(stdin) || flag==0) return 0;
    return 1;
}

bool read_shelf_num(int *num) {
    char c;
    int next_num;
    while (isspace(c =getchar()) && c!='\n') {}
    if( c!='#')return 0;
    if (scanf("%d", &next_num)!=1 || next_num <= *num || (next_num!=0 && *num ==-1)|| getchar()!='\n') return 0;
    *num = next_num;
    return 1;
}

bool read_shelf_content(PRODUCT * available, int * max_product) {

    int shelf_num = -1;
        if(!read_shelf_num(&shelf_num)) return 0;
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
    if(!read_shelf_content(available_products, &max_product)) return error(available_products);
    free_products(available_products);
    return 0;
}
