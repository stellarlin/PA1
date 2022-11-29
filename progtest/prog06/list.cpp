
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>

struct PRODUCT
{
    int shelf;
    int max_name;
    char * name;

};

void free_products(PRODUCT *available, int max) {

    int count = 0;
    for(int i=0; i<=max; i++)
    {
        printf("%d\n",count);
        free(available[i].name);
        count++;

    }
free(available);
}

bool error (PRODUCT * available, int max){
    free_products(available, max);
    printf("Nespravny vstup.\n");
    return 0;
}



void initial_array (PRODUCT ** available, int max_product)
{
    *available = (PRODUCT *)malloc(max_product*sizeof(PRODUCT));
    if(*available==NULL) initial_array(available, max_product);
}

void initial_name (char ** name,  int  max )
{
    *name = (char*) malloc(max * sizeof(char));
    if(*name == NULL)initial_name(name, max);

}
void realloc_name (char  ** name, int  max)
{
    char * new_name;
    new_name = (char *) realloc(*name, max * sizeof(char));
    if(new_name == NULL)realloc_name(name, max);
    *name = new_name;
}


void realloc_product(PRODUCT **available, int *max) {

    PRODUCT * new_available=*available;

    *available = (PRODUCT *)realloc(*available, *max*2*sizeof(PRODUCT));
    if(*available==NULL) realloc_product(&new_available, max);

    //*available=new_available;

    *max*=2;
}


int realloc_fgets(PRODUCT * available, int product_id, int num, bool * empty_line, bool * hash_line)
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
          return 1;
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

    available[product_id].name=tmp_name;
    available[product_id].name[strlen(available[product_id].name)-1] = '\0';
    available[product_id].shelf=num;
    return 1;
}
bool read_line(PRODUCT *available, int * product_id, int num, int * max_product, bool * empty_line, bool * hash_line) {

    while(1)
    {
     // realloc memory when count of products bigger than max count
      if(*product_id>=*max_product)realloc_product(&available, max_product);
     //allocating memory for name of product
      available[*product_id].max_name=100;
      initial_name (&available[*product_id].name, available[*product_id].max_name);

        //read stdin line per line, if line starts with # or is empty, loop will end
       if(realloc_fgets(available, *product_id, num, empty_line, hash_line)==0
        || *empty_line ==1 || *hash_line==1) break;

       ++*product_id;
    }
    if(feof(stdin) || (*empty_line==0 && *hash_line==0)) return 0;
    return 1;
}

bool read_shelf_num(int *num) {
    char c;
    int next_num;
    while (isspace(c =getchar()) && c!='\n') {}
    if( c!='#')return 0;
    if (scanf("%d", &next_num)!=1 || next_num != *num+1 || getchar()!='\n') return 0;
    *num = next_num;
    return 1;
}

bool read_shelf_content(PRODUCT ** available, int * max_product,int *product_id) {

    bool empty_line=0, hash_line;
    int shelf_num = -1;
    while(1) {
        hash_line =0;
        if (!read_shelf_num(&shelf_num))break;
        if(!read_line(*available, product_id, shelf_num, max_product, &empty_line, &hash_line))break;
        if (empty_line == 1) break;
    }
    if(feof(stdin) || empty_line!=1) return 0;
        return 1;
}

int main (void)
{
    int product_id = 0;
    int max_product = 10;
    PRODUCT * available_products;
    initial_array(&available_products, max_product);
    for(int i =0; i<max_product; i++) available_products[i].max_name=100;
    if(!read_shelf_content(&available_products, &max_product, &product_id)) return error(available_products, product_id);
    free_products(available_products, product_id);
    return 0;
}
