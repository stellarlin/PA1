#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

#define INITIAL_SIZE 10


// Function to stop the program and show an error message
int error() {
    printf("Nespravny vstup.\n");
    return 0;
}

struct Contact
{
    char * name = NULL;
    char number [21]{};
};

typedef int (*comparator)(int c);

struct trieNode
{
    Contact * contacts;
    int count;
    int size;
    bool isWordEnd;
    trieNode * nextLetter [10];
};

struct phoneBook
{
    trieNode * root = NULL;
    int count = 0;
};

// Function to create a new trie node
trieNode * createNode() {
    auto * newNode = (trieNode *)malloc(sizeof(trieNode));
    if (!newNode) return NULL;

    newNode->count = 0;
    newNode->size = INITIAL_SIZE;
    newNode->isWordEnd = false;

    newNode->contacts = (Contact *)malloc (newNode->size * sizeof (Contact));
    if (!newNode->contacts) return NULL;



    for (int i = 0; i < 10; ++i) {
        newNode->nextLetter[i] = NULL;
    }
    return newNode;
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

void freeBook(phoneBook *book) {
    if (book == NULL || book->root == NULL) {
        return;
    }

    // Free the trie nodes starting from the root
    freeTrieNode(&book->root);

    // Set the root to NULL after freeing to avoid accidental access
    book->root = NULL;
}

enum Result {
    ACCEPTED = 0,
    ERROR = 1,
    EXISTS = 2
};


bool addName (char * name, int size, Contact * contact)
{
    // Allocate exactly the amount of memory needed
    contact->name = (char *)malloc(size + 1 * sizeof(char));
    if (!contact->name) return false;

    // Copy the content from the buffer to the final line
    strncpy(contact->name, name, size);
    contact->name[size] = '\0';

    return true;
}


bool readName (Contact * contact, comparator cmp) {
    int size = INITIAL_SIZE;
    int index = 0;
    char *buffer = (char *)malloc(size * sizeof(char));

    if (!buffer) return false;

    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (c == ' ') {
            if (index == 0 || buffer[index - 1] == ' ' ) return false;
        }
        if (!cmp(c) && !isspace(c)) return false;

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

    if (! addName(buffer, index, contact) || buffer[index - 1] == ' ') {
        free(buffer);
        return false;
    }

    return strlen(contact->name) > 0;
}

bool readNumber (char * number) {
    int index = 0;
    char buffer [21];

    char c;
    while ((c = getchar()) != ' ' && c != EOF) {
        if (!isdigit(c) || index >= 20) return false;
        buffer[index++] = c;
    }

    // Copy the content from the buffer to the final line
    strncpy(number, buffer, index);
    number[index] = '\0';

    return strlen(number) > 0;
}

bool equal(Contact * a, Contact *b) {
    return !strcmp(a->name, b->name) && !strcmp(a->number, b->number);
}

Contact copyContact(const Contact *original) {
    Contact copy;

    // Copy the number
    strcpy(copy.number, original->number);
    if(!addName(original->name, strlen(original->name), &copy))
        return {};
    // Allocate memory for the name and copy it

    return copy;
}


Result insertNumber(Contact contact, phoneBook *book) {
    trieNode * current = book->root;
    for (int i = 0; i < strlen(contact.number); ++i) {
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
    current->isWordEnd = true;
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
        }
    }
return 0;
}

Result insertName(Contact contact, phoneBook *book) {
    trieNode * current = book->root;
    for (int i = 0; i < strlen(contact.name); ++i) {
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

bool insertContact(phoneBook *book) {
    Contact contact;

    if(!readNumber(contact.number)) return false;
    if(!readName(&contact, isalpha))
    {
        freeContact(&contact);
        return false;
    }

    switch (insertNumber(copyContact(&contact) , book))
    {
        case ACCEPTED:
            printf("OK\n");
            insertName (copyContact(&contact) , book);
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

bool searchContact(phoneBook *book) {
    return true;
}

bool read_input (phoneBook * phone_book)
{
    bool error_flag = false;
   while (true)
   {
       char sign;
       if (scanf(" %c", &sign) != 1  || (sign != '+'  && sign != '?') || getchar() != ' ')break;

       switch (sign){
           case '+': error_flag = !insertContact (phone_book);
                        break;
           case '?': error_flag = !searchContact (phone_book);
       }
       if(error_flag) break;
}
   return  feof(stdin) && !error_flag;
}



int main ()
{
    phoneBook phone_book;
    phone_book.root = createNode();
    if (!read_input(&phone_book)) error();
    freeBook(&phone_book);
    return 0;
}
