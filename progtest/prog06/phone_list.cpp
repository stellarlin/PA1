#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

#define INITIAL_SIZE 10
#define RESULT_SIZE 10
#define ALPHABET_SIZE 10
#define MAX_NUMBER_SIZE 20

// Function to stop the program and show an error message
int error() {
    printf("Nespravny vstup.\n");
    return 0;
}

struct Contact
{
    char * name = NULL;
    char number [21] = "";
};

struct trieNode
{
    Contact * contacts;
    int count;
    int size;
    trieNode * nextLetter [ALPHABET_SIZE];
};


// Function to create a new trie node
trieNode * createNode() {
    auto * newNode = (trieNode *)malloc(sizeof(trieNode));
    if (!newNode) return NULL;

    newNode->count = 0;
    newNode->size = INITIAL_SIZE;

    newNode->contacts = (Contact *)malloc (newNode->size * sizeof (Contact));
    if (!newNode->contacts) return NULL;



    for (int i = 0; i < 10; ++i) {
        newNode->nextLetter[i] = NULL;
    }
    return newNode;
}


bool addName (char * newName, int size,  char ** contactName)
{
    // Allocate exactly the amount of memory needed
    *contactName = (char *)malloc(size + 1 * sizeof(char));
    if (!*contactName ) return false;

    // Copy the content from the buffer to the final line
    strncpy(*contactName , newName, size);
    (*contactName)[size] = '\0';

    return true;
}

Contact copyContact(const Contact *original) {
    Contact copy;

    // Copy the number
    strcpy(copy.number, original->number);
    addName(original->name, strlen(original->name), &copy.name);
    return copy;
}


trieNode * reallocContacts (trieNode * node)
{
    node->size *= 2;
    auto * newContracts = (Contact *)realloc(node->contacts, node->size * sizeof(Contact));

    if (!newContracts) {
        return NULL;
    }
    node->contacts = newContracts;
    return node;
}


// Function to free the dynamically allocated memory inside a Contact structure
void freeContact( Contact *contact) {
    // Check if the name field is not NULL before freeing
    if (contact->name != NULL) {
        free(contact->name);
        contact->name = NULL;  // Set to NULL to avoid double freeing
    }
}
void freeTrieNode(trieNode** node) {
    if (*node == NULL) {
        return;
    }

    // Recursively free child nodes
    for (int i = 0; i < 10; ++i) {
        freeTrieNode(&(*node)->nextLetter[i]);
    }

    for (int i = 0; i < (*node)->count; i++) freeContact(&(*node)->contacts[i]);
    // Free the contacts array
    free((*node)->contacts);

    // Free the node itself
    free(*node);
    *node = NULL;
}

void freeBook(trieNode ** root ) {
    if (*root == NULL) {
        return;
    }
    // Free the trie nodes starting from the root
    freeTrieNode(root);
    *root = NULL;
}

enum Result {
    ACCEPTED = 0,
    ERROR = 1,
    EXISTS = 2
};

bool readName (char ** name ) {
    int size = INITIAL_SIZE;
    int index = 0;
    char *buffer = (char *)malloc(size * sizeof(char));

    if (!buffer) return false;

    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c == ' ') {
            if (index == 0 || buffer[index - 1] == ' ' )
            {
                free(buffer);
                return false;
            }
        }
        if (!isalpha(c) && !isspace(c))
        {
            free(buffer);
            return false;
        }

        // Reallocate memory if needed
        if (index == size - 1) {
            size *= 2;
            char *newBuffer = (char *)realloc(buffer, size * sizeof(char));

            if (!newBuffer) {
                free(buffer);
                return false;
            }
            buffer = newBuffer;
        }

        buffer[index++] = c;
    }

    if (! addName(buffer, index, name) || buffer[index - 1] == ' ') {
        free(buffer);
        return false;
    }

    free(buffer);
    return strlen(*name) > 0;
}

bool readNumber (char * number) {
    int index = 0;
    char buffer [MAX_NUMBER_SIZE + 1];

    char c;
    while ((c = getchar()) != ' ' && c != EOF) {
        if (!isdigit(c) || index >= MAX_NUMBER_SIZE) return false;
        buffer[index++] = c;
    }

    // Copy the content from the buffer to the final line
    strncpy(number, buffer, index);
    number[index] = '\0';

    return strlen(number) > 0;
}

bool equal(Contact * a, Contact *b) {
    return strcmp(a->name, b->name) == 0 && strcmp(a->number, b->number) ==0;
}



Result insertNumber(Contact contact, trieNode * root ) {
    trieNode * current = root;
    for (size_t i = 0; i < strlen(contact.number); ++i) {
        int index = contact.number[i] - '0';  // Assuming only lowercase letters; adjust as needed

        if (!current->nextLetter[index]) {
            current->nextLetter[index] = createNode();
            if (!current->nextLetter[index]) return ERROR;
        }
        current = current->nextLetter[index];
    }
    for (int i = 0; i < current->count; i++)
    {
        if (equal(&current->contacts[i], &contact)) return EXISTS;
    }

    current->contacts[current->count++] = contact;
    if (current->size == current->count) {
        if (!reallocContacts(current)) return ERROR;
    }

    return ACCEPTED;
}

int decodeT9(char letter) {
    if (letter == ' ') return 1;
    // T9 encoding mapping

    // Check if the letter is a valid alphabet character
    if (isalpha(letter)) {
        // Convert the letter to uppercase for simplicity
        letter = toupper(letter);

        switch (letter) {
            case 'A':
            case 'B':
            case 'C':
                return 2;
            case 'D':
            case 'E':
            case 'F':
                return 3;
            case 'G':
            case 'H':
            case 'I':
                return 4;
            case 'J':
            case 'K':
            case 'L':
                return 5;
            case 'M':
            case 'N':
            case 'O':
                return 6;
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
                return 7;
            case 'T':
            case 'U':
            case 'V':
                return 8;
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
                return 9;
            default:
                return 0;
        }
    }
return 0;
}

Result insertName(Contact contact, trieNode * root ) {
    trieNode * current = root;
    for (size_t i = 0; i < strlen(contact.name); ++i) {
        int index = decodeT9(contact.name[i]);  // Assuming only lowercase letters; adjust as needed

        if (current->nextLetter[index] == NULL) {
            current->nextLetter[index] = createNode();
        }
        current = current->nextLetter[index];
    }
    for (int i = 0; i < current->count; i++)
    {
        if (equal(&current->contacts[i], &contact)) return EXISTS;
    }

    current->contacts[current->count++] = contact;
    if (current->size == current->count)
    {
        if(!reallocContacts(current)) return ERROR;
    }
    return ACCEPTED;

}

bool insertContact(trieNode * root ) {
    Contact contact;

    if(!readNumber(contact.number)) return false;
    if(!readName(&contact.name))
    {
        freeContact(&contact);
        return false;
    }

    switch (insertNumber(contact , root))
    {
        case ACCEPTED:
            printf("OK\n");
            insertName (copyContact(&contact) , root);
            break;
        case EXISTS:
            freeContact(&contact);
            printf("Kontakt jiz existuje.\n");
            break;
        case ERROR:
            freeContact(&contact);
            return false;
    }
    return true;
}

void storeResult (trieNode * current, int * count, Contact * searchResult)
{
    if (!current) {
        return;
    }

    // Recursively free child nodes
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        storeResult(current->nextLetter[i], count, searchResult);
    }

        for (int i =0; i < current->count; i++)
        {
            bool unique = true;
            for (int j = 0; j < (*count >= RESULT_SIZE ? RESULT_SIZE : *count); j++)
            {
                unique = !equal(&searchResult[j], &current->contacts[i]);
                if (!unique) break;
            }
            if (unique) {
                if (*count < RESULT_SIZE)  searchResult[*count] = copyContact(&current->contacts[i]);
                ++*count;
            }
        }
    }


void printResult(Contact * result, int count) {
    for (int i = 0; i < count; i++)
    {
        printf ("%s %s\n", result[i].number, result[i].name);
    }
}

bool searchContact(trieNode * root ) {
   int count = 0;
   char c;
   trieNode * current = root;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (!isdigit(c)) return false;

        int index = c - '0';
        if (current) current = current->nextLetter[index];
    }
    if (current)
    {
        Contact searchResult [RESULT_SIZE];
        storeResult(current, &count, searchResult);
        if (count <= RESULT_SIZE) printResult(searchResult, count);
        for (auto & i : searchResult)freeContact(&i);
    }
    printf("Celkem: %d\n", count);
    return true;
}

bool read_input (trieNode * root )
{
    bool error_flag = false;
   while (true)
   {
       char sign;
       if (scanf(" %c", &sign) != 1  || (sign != '+'  && sign != '?') || getchar() != ' ')break;

       switch (sign){
           case '+': error_flag = !insertContact (root);
                        break;
           case '?': error_flag = !searchContact (root);
                    break;
           default: error_flag = true;
       }
       if(error_flag) break;
}
   return  feof(stdin)  && !error_flag;
}



int main ()
{
    trieNode * root = createNode();
    if (!read_input(root)) error();
    freeBook(&root);
    return 0;
}
