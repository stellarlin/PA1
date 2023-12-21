#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

#define INITIAL_SIZE 10
#define RESULT_SIZE 10
#define ALPHABET_SIZE 10
#define MAX_NUMBER_SIZE 20

//----------------------------------------------------------------------------------------//
// Structures

struct Contact
{
    char * name = NULL;
    char number [MAX_NUMBER_SIZE + 1] = "";
};

struct ContactContainer
{
    Contact * data;
    int count;
    int size;
};

struct trieNode
{
    ContactContainer  ByNumber;
    ContactContainer  ByName;
    trieNode * nextLetter [ALPHABET_SIZE];
};

enum Result {
    ACCEPTED = 0,
    ERROR = 1,
    EXISTS = 2
};
//----------------------------------------------------------------------------------------//
// Container Functions

// Initialize the ContactContainer
// Input: ContactContainer pointer
// Output: true if successful, false otherwise
// Description: Initializes the count, size, and allocates memory for data array.

bool initContacts (ContactContainer * container)
{
    container->count = 0;
    container->size = INITIAL_SIZE;

    container->data = (Contact *)malloc (container->size * sizeof (Contact));
    if (!container->data) return false;

    return true;
}

// Create a new trie node
// Input: None
// Output: Pointer to the newly created trieNode
// Description: Allocates memory for a new trieNode and initializes its members.

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

// Compare two Contact structures for equality
// Input: Two Contact pointers
// Output: true if equal, false otherwise
bool equal(Contact * a, Contact *b) {
    return strcmp(a->name, b->name) == 0 && strcmp(a->number, b->number) ==0;
}

// Allocate memory for a name copy
// Input: New name, size of the name, pointer to store the result
// Output: true if successful, false otherwise
bool addName (char * newName, size_t size,  char ** contactName)
{
    // Allocate exactly the amount of memory needed
    *contactName = (char *)malloc(size + 1 * sizeof(char));
    if (!*contactName ) return false;

    // Copy the content from the buffer to the final line
    strncpy(*contactName , newName, size);
    (*contactName)[size] = '\0';

    return true;
}

// Copy the content of a Contact
// Input: Pointer to the original Contact structure
// Output: Copied Contact structure
// Description: Creates a deep copy of the Contact structure.
Contact copyContact(const Contact *original) {
    Contact copy;

    // Copy the number
    strcpy(copy.number, original->number);
    copy.number[sizeof(copy.number) - 1] = '\0';  // Ensure null termination
    addName(original->name, strlen(original->name), &copy.name);
    return copy;
}

// Reallocate memory for the ContactContainer
// Input: ContactContainer pointer
// Output: Updated ContactContainer pointer after reallocation
// Description: Doubles the size of the data array if it's full.
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

// Insert a contact into the ContactContainer
// Input: ContactContainer pointer, pointer to the contact to be inserted
// Output: true if successful, false otherwise
// Description: Inserts a contact into the ContactContainer, reallocates memory if needed.
bool insertContactContainer (ContactContainer * container, Contact * contact)
{
    container->data[container->count++] = copyContact(contact);
    if (container->size == container->count) {
        if (!reallocContainer(container)) return false;
    }
    return true;
}

// Check if a contact exists in the ContactContainer
// Input: ContactContainer pointer, pointer to the contact to be checked
// Output: true if the contact exists, false otherwise
bool existsInContainer (ContactContainer * container, Contact * contact)
{
    for (int i = 0; i < container->count; i++)
    {
        if (equal(&container->data[i], contact)) return true;
    }
    return false;
}

// Add unique contacts from src to dest
// Input: Source and destination ContactContainers
// Output: true if successful, false otherwise
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

//----------------------------------------------------------------------------------------//
// Free memory functions

// Free Contact
// Input: Pointer to the Contact structure
// Output: None
// Description: Frees the memory occupied by the name field.
void freeContact( Contact *contact) {
    // Check if the name field is not NULL before freeing
    if (contact->name != NULL) {
        free(contact->name);
        contact->name = NULL;  // Set to NULL to avoid double freeing
    }
}


// Free ContactContainer
// Input: Pointer to the ContactContainer to be freed
// Output: None
// Description: Frees the array of contacts and then frees the memory occupied by the name fields of all contacts
//              in the ContactContainer.
void freeContainer(ContactContainer* container) {
    for (int i = 0; i < container->count; i++) {
        freeContact(&container->data[i]); // Free individual contact names
    }
    free(container->data); // Free the contacts array
}

// Free a trieNode and its child nodes
// Input: Pointer to the trieNode pointer
// Output: None
// Description: Recursively frees the trieNode and its child nodes.

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

// Free the entire contact book starting from the root
// Input: Pointer to the trieNode pointer
// Output: None
void freeBook(trieNode ** root ) {
    if (*root == NULL) {
        return;
    }
    // Free the trie nodes starting from the root
    freeTrieNode(root);
    *root = NULL;
}

//----------------------------------------------------------------------------------------//
// Insert Functions

// Read a name from input
// Input: Pointer to store the name
// Output: true if successful, false otherwise
// Description: Reads a name from input and allocates memory for it.
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

// Read a number from input
// Input: Pointer to store the number
// Output: true if successful, false otherwise
bool readNumber (char * number) {
    int index = 0;
    char buffer [MAX_NUMBER_SIZE + 1] = "";

    char c;
    while ((c = getchar()) != ' ' &&  c != '\n' && c != EOF) {
        if (!isdigit(c) || index >= MAX_NUMBER_SIZE) return false;
        buffer[index++] = c;
    }

    if(c == '\n')
    {
        ungetc(c,stdin);
        return false;
    }

     // Copy the content from the buffer to the final line
     strncpy(number, buffer, index + 1);

    number[index] = '\0';

    return strlen(number) > 0;
}

// Insert a contact into the contact book by number
// Input: Pointer to the contact, pointer to the trie root
// Output: Result of the operation
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

// Decode T9 encoding for a letter
// Input: Letter to be decoded
// Output: T9 encoding number
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

// Insert a contact into the contact book by name
// Input: Pointer to the contact, pointer to the trie root
// Output: Result of the operation
// Description: Inserts a contact using the T9 encoded name.
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
            printf("Kontakt jiz existuje.\n");
            break;
        case ERROR:
            freeContact(&contact);
            return false;
    }
    freeContact(&contact);
    return true;
}


//----------------------------------------------------------------------------------------//
// Searching functions


// Store search results
// Input: Pointer to the current trieNode, pointer to the result
// Output: true if successful, false otherwise
// Description: Recursively stores search results in the searchResult container.
bool storeResult (trieNode * current, ContactContainer * searchResult)
{
    if (!current) {
        return true;
    }

    // Recursively free child nodes
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        storeResult(current->nextLetter[i],  searchResult);
    }

    // Store unique contacts from current node in the result
    if(!addUnique(&current->ByNumber, searchResult)) return false;
    if(!addUnique(&current->ByName, searchResult)) return false;

    return true;
}

// Print the search result
// Input: Pointer to the searchResult container
// Output: None
// Description: Prints the search result.
void printResult(ContactContainer * result) {
    if (result->count <= RESULT_SIZE) {
        for (int i = 0; i < result->count; i++) {
            printf("%s %s\n", result->data[i].number, result->data[i].name);
        }
    }

    printf("Celkem: %d\n", result->count);

}

// Search for a contact in the contact book
// Input: Pointer to the trie root
// Output: true if successful, false otherwise
// Description: Searches for a contact in the contact book and prints the result.
bool searchContact(trieNode * root ) {
   ContactContainer searchResult;
   if(!initContacts(&searchResult)) return false;

   char c;
   trieNode * current = root;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (!isdigit(c))
        {
            freeContainer(&searchResult);
            return false;
        }

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
    }
    printResult(&searchResult);
    freeContainer(&searchResult);
    return true;
}


//----------------------------------------------------------------------------------------//
// Main Functions

// Read and process input commands
// Input: Pointer to the trie root
// Output: None
// Description: Reads input commands from standard input and performs the
//              corresponding operations based on the provided commands:
//              '+' is used to insert a new contact (number, name) into the contact book
//              '?' is used to search for contacts based on a given number sequence.
void read_input (trieNode * root )
{
    char c;
   while (true) {
       char sign = getchar();

       if (sign == EOF) break;

       bool error_flag = ((sign != '+' && sign != '?') || (c = getchar()) != ' ');
       if (!error_flag) {
           switch (sign) {
               case '+':
                   error_flag = !insertContact(root);
                   break;
               case '?':
                   error_flag = !searchContact(root);
                   break;
               default:
                   error_flag = true;
           }
       }
       if (error_flag)
       {
           printf("Nespravny vstup.\n");
           if (sign != '+' && sign != '?') c = sign;
           while (c != '\n' && c != EOF) {c = getchar();}
       }
   }
}

int main ()
{
    trieNode * root = createNode();
    read_input(root);
    freeBook(&root);
    return 0;
}
