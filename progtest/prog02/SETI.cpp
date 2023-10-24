
#include <cstdio>
#include <cstdlib>
#include <cstring>


#define MAX_MESSAGES 100000
// Stop the program and show error message
int error () {
    printf("Nespravny vstup.\n");
    return 0;
}

struct Message
{
    long long int  remainder = 0;
    long long int word = 0;
};

long long int decodeSymbol (char symbol)
{
    int result = 1;
    int exp = symbol - 'a';
    int base = 2;
    for (;;)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }
    return result;
}


bool readMessage (Message * message)
{
    char symbol;
    bool start_detected = false, remainder_reading = true;
    while (1)
    {
        if ((symbol = getchar()) == EOF || symbol == '\n') break;
        else ungetc(symbol, stdin);

        if (scanf ( " %c", &symbol)!= 1 ) return false;
        else if (symbol == '|')
        {
            if(start_detected) return false;
            start_detected = true;
            message->word += message->remainder;
            remainder_reading = false;
        }
        else if (symbol <'a' || symbol > 'z') return false;
        else {
            //
            // printf("symbol: %c  -> %lld\n", symbol,  decodeSymbol(symbol));
            //
                    (remainder_reading ? message->remainder : message->word) += decodeSymbol(symbol);
        }
        }
    //printf("remainder and word: %lld  + %lld\n ", message->remainder,  message->word);
    return message->word != 0;
}



bool calculateSynchronization ()
{
    Message messages[MAX_MESSAGES], *current_message = &messages[0];

    char c;
    printf ("Zpravy:\n");
    while (1) {

        // ending condition
        if (current_message == & messages[MAX_MESSAGES]) break;
        if ((c = getchar()) == EOF) break;
        else ungetc(c, stdin);

        if (!readMessage(current_message)) return false;
        if (current_message->word > 1) current_message++;
        else  current_message->word = 0, current_message->remainder = 0;
    }
   return true;
}

int main (void)
{
    return calculateSynchronization () ? 0 : error();
}

