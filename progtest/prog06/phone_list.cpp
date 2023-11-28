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

struct ContactContainer
{
    Contact * data;
    int count;
    int size;
};

bool initContacts (ContactContainer * container)
{
    container->count = 0;
    container->size = INITIAL_SIZE;

    container->data = (Contact *)malloc (container->size * sizeof (Contact));
    if (!container->data) return false;

    return true;
}

struct trieNode
{
    ContactContainer  ByNumber;
    ContactContainer  ByName;
    trieNode * nextLetter [ALPHABET_SIZE];
};


// Function to create a new trie node
trieNode * createNode() {
    auto * newNode = (trieNode *)malloc(sizeof(trieNode));
    if (!newNode) return NULL;

    if (!initContacts(&newNode->ByName) || !initContacts(&newNode->ByNumber))
    {
        free (newNode);
        return NULL;
    }

    for (int i = 0; i < 10; ++i) {
        newNode->nextLetter[i] = NULL;
    }
    return newNode;
}

bool equal(Contact * a, Contact *b) {
    return strcmp(a->name, b->name) == 0 && strcmp(a->number, b->number) ==0;
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


ContactContainer * reallocContainer  (ContactContainer * container)
{
    container->size *= 2;
    auto * newContracts = (Contact *)realloc(container->data, container->size * sizeof(Contact));

    if (!newContracts) {
        return NULL;
    }
    container->data = newContracts;
    return container;
}

bool insertContactContainer (ContactContainer * container, Contact * contact)
{
    container->data[container->count++] = copyContact(contact);
    if (container->size == container->count) {
        if (!reallocContainer(container)) return false;
    }
    return true;
}
bool addContainer (ContactContainer * src, ContactContainer * dest)
{
    for (int i = 0; i < src->count; i++)
    {
        if (!insertContactContainer(dest, &src->data[i])) return false;
    }
    return true;
}



bool existsInContainer (ContactContainer * container, Contact * contact)
{
    for (int i = 0; i < container->count; i++)
    {
        if (equal(&container->data[i], contact)) return true;
    }
    return false;
}

bool addUnique (ContactContainer * src, ContactContainer * dest)
{
    for (int i = 0; i < src->count; i++)
    {
        if (!existsInContainer(dest, &src->data[i])) {
            if (!insertContactContainer(dest, &src->data[i])) return false;
        }
    }
    return true;
}


// Function to free the dynamically allocated memory inside a Contact structure
void freeContact( Contact *contact) {
    // Check if the name field is not NULL before freeing
    if (contact->name != NULL) {
        free(contact->name);
        contact->name = NULL;  // Set to NULL to avoid double freeing
    }
}


void freeContainer (ContactContainer * container)
{
    for (int i = 0; i < container->count; i++) freeContact(&container->data[i]);
    // Free the contacts array
    free(container->data);
}

void freeTrieNode(trieNode ** node) {
    if (*node == NULL) {
        return;
    }

    // Recursively free child nodes
    for (int i = 0; i < 10; ++i) {
        freeTrieNode(&(*node)->nextLetter[i]);
    }

    freeContainer(&(*node)->ByName);
    freeContainer(&(*node)->ByNumber);

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


Result insertNumber(Contact * contact, trieNode * root ) {
    trieNode * current = root;
    for (size_t i = 0; i < strlen(contact->number); ++i) {
        int index = contact->number[i] - '0';  // Assuming only lowercase letters; adjust as needed

        if (!current->nextLetter[index]) {
            current->nextLetter[index] = createNode();
            if (!current->nextLetter[index]) return ERROR;
        }
        current = current->nextLetter[index];
    }

    if (existsInContainer(&current->ByNumber, contact)) return EXISTS;

    return insertContactContainer(&current->ByNumber, contact) ? ACCEPTED : ERROR;
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

Result insertName(Contact * contact, trieNode * root ) {
    trieNode * current = root;
    for (size_t i = 0; i < strlen(contact->name); ++i) {
        int index = decodeT9(contact->name[i]);  // Assuming only lowercase letters; adjust as needed

        if (current->nextLetter[index] == NULL) {
            current->nextLetter[index] = createNode();
        }
        current = current->nextLetter[index];
    }
    if (existsInContainer(&current->ByName, contact)) return EXISTS;

    return insertContactContainer(&current->ByName, contact) ? ACCEPTED : ERROR;
}

bool insertContact(trieNode * root ) {
    Contact contact;

    if(!readNumber(contact.number)) return false;
    if(!readName(&contact.name))
    {
        freeContact(&contact);
        return false;
    }

    switch (insertNumber(&contact , root))
    {
        case ACCEPTED:
            printf("OK\n");
            insertName (&contact , root);
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

bool storeResult (trieNode * current, ContactContainer * searchResult)
{
    if (!current) {
        return true;
    }

    // Recursively free child nodes
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        storeResult(current->nextLetter[i],  searchResult);
    }

    if(!addContainer (&current->ByNumber, searchResult)) return false;
    if(!addUnique(&current->ByName, searchResult)) return false;

    return true;
}


void printResult(ContactContainer * result) {
    if (result->count <= RESULT_SIZE) {
        for (int i = 0; i < result->count; i++) {
            printf("%s %s\n", result->data[i].number, result->data[i].name);
        }
    }

    printf("Celkem: %d\n", result->count);

}

bool searchContact(trieNode * root ) {
   ContactContainer searchResult;
   if(!initContacts(&searchResult)) return false;

   char c;
   trieNode * current = root;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (!isdigit(c)) return false;

        int index = c - '0';
        if (current) current = current->nextLetter[index];
    }
    if (current)
    {
        if(!storeResult(current, &searchResult))
        {
            freeContainer(&searchResult);
            return false;
        }
        printResult(&searchResult);
        freeContainer(&searchResult);
    }
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
