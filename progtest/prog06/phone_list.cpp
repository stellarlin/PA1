#include <cstdio>
#include <cstdlib>
#include <cstring>

#define INITIAL_SIZE 10
#define BUFFER_SIZE 256

// Function to stop the program and show an error message
int error() {
    printf("Nespravny vstup.\n");
    return 0;
}

struct phoneNode
{
    char * name;
    phoneNode * next [10];
};

struct nameNode
{
    nameNode (int num = -1) : number (num) {
        for (int i = 0; i < 52; i++) nextLetter[i] = NULL;
    }
    int number;
    nameNode * nextLetter [52]{};
};

struct phoneBook
{
    phoneBook () : phones_root(NULL), names_root(NULL){}

    phoneNode * phones_root;
    nameNode * names_root;
};


bool readName (char ** name) {
    int size = INITIAL_SIZE;
    int index = 0;
    char *buffer = (char *)malloc(size * sizeof(char));

    if (!buffer) return false;

    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c == ' ') {
            char tmp = c;
            if (index == 0 || buffer[index - 1] == ' ' || (c = getchar()) == EOF) return false;
            c = tmp;
        }
        // Reallocate memory if needed
        if (index == size - 1) {
            size *= 2;
            buffer = (char *) realloc(buffer, size * sizeof(char));

            if (!buffer) {
                free(*name);
                return false;
            }
        }
        buffer[index++] = c;
    }

    // Allocate exactly the amount of memory needed
    *name = (char *)malloc((index + 1) * sizeof(char));

    if (!*name) {
        fprintf(stderr, "Memory allocation error\n");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    // Copy the content from the buffer to the final line
    strncpy(*name, buffer, index);
    (*name)[index] = '\0';

    free(buffer);
    return true;
}

bool insertContact(phoneBook *book) {

    return true;
}

bool searchContact(phoneBook *book) {
    return false;
}



bool read_input (phoneBook * phone_book)
{
    bool error_flag = false;
   while (true)
   {
       char sign;
       if (scanf(" %c", &sign) != 1  || (sign != '+'  && sign != '?') || getchar() != ' ')break;
       printf ("%c\n", sign);
       switch (sign){
           case '+': error_flag = !insertContact (phone_book);
                        break;
           case '?': error_flag = !searchContact (phone_book);
       }
       if(error_flag) break;
}
   return  feof(stdin) && !error_flag;
}
int main (void)
{
    phoneBook phone_book;
    if (!read_input(&phone_book)) return error();
    return 0;
}
