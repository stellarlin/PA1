
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

struct SETI
{
    Message  signal_storage [MAX_MESSAGES];
    int message_counter = 0;
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
    while (true)
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
    //
    //
    printf("remainder and word: %lld  + %lld\n", message->remainder,  message->word);
    return message->word != 0;
}

bool readData (SETI * data)
{
    char c;
    printf ("Zpravy:\n");
    while (1) {

        // ending condition
        //________________________________________
        if (data->message_counter == MAX_MESSAGES) break;
        if ((c = getchar()) == EOF) break;
        else ungetc(c, stdin);
        //________________________________________

        // referenced to message_counter message in SETI signal storage to better code understanding
        Message * current_message = &data->signal_storage[data->message_counter];

        //try to read message from input, check if format is correct and decode symbols into 2 values
        if (!readMessage(current_message)) return false;

        // word with lenght of 1 isn't count
        if (current_message->word > 1) data->message_counter++;
        else  current_message->word = 0, current_message->remainder = 0;
    }
    return data->message_counter > 1;
}


long long int gcd ( long long int  a, long long int  b)
{
    if (b == 0) return a;
    return gcd (b, a % b);
}

long long int ext_gcd ( long long int a,  long long  int b,  long long int * x,  long long  int * y) {

    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    long long int x1, y1; // To store results of recursive call
    int gcd = ext_gcd ( b % a, a, &x1, &y1);

    // Update x and y using results of
    // recursive call
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

bool CRT_condition ( SETI * data)
{
    for (Message *current = &data->signal_storage[0]; current < &data->signal_storage[data->message_counter]; current++)
    {
        for(Message *next = current + 1; next < &data->signal_storage[data->message_counter]; next++)
        {
            long long int g = gcd (current->word, next->word);
            //
            //
            printf ("gcd of %lld and % lld is %lld\n", current->word, next->word, g);

            if ((current->remainder - next->remainder) % g != 0) return false;
        }
    }
    return true;
}
/*
long long int mInv ( long long int num,  long long int mod)
{
    long long int  inv = 1;
    for ( long long int i = 1; i < mod; i++)
    {
        if ((num * i) % mod == 1) return i;
    }
    return inv;
}

long long int gMod (SETI * data)
{
    long long int global_module;
    for (Message *current = &data->signal_storage[0]; current != &data->signal_storage[data->message_counter]; current++)
    {
        if (current == &data->signal_storage[0]) {
            global_module = current->word;
            continue;
        }
        global_module = ( (current->word * global_module)/ (gcd(current->word, global_module)));
    }
    return global_module;
}
*/

long long int CRT_evaluate (SETI * data)
{
    long long int module /*= gMod(data)*/, curr_coeff,  next_coeff;
//
//
//    printf ("Global module is %lld\n", global_module);

    Message *main_equation = &data->signal_storage[0];

    for (Message *current_equation = ++main_equation; current_equation != &data->signal_storage[data->message_counter]; current_equation++) {
        long long int g = gcd(main_equation->word, current_equation->word);
        if ((main_equation->remainder - current_equation->remainder) % g != 0) return -1;


        ext_gcd(main_equation->word / g, current_equation->word / g, &curr_coeff, &next_coeff);
        module = main_equation->word / g * current_equation->word;

        main_equation->remainder = (main_equation->remainder * (current_equation->word / g) * next_coeff
                              + current_equation->remainder * (main_equation->word / g) * curr_coeff) % module;


        if (main_equation->remainder < 0) main_equation->remainder += module; /** Result is not suppose to be negative*/
        main_equation->word = module;
    }





/*
        long long int module = global_module / current->word;
        //
        //
        printf ("Module of %lld is %lld\n"
                "Inverse of %lld is %lld\n", current->word, module, module, mInv(module, current->word));


       total += mInv(module, current->word) * current->remainder * module;
       printf ("Now total is  %lld\n", total);
    }

    total = (total % global_module);
    printf ("Total is  %lld\n", total); */
    return main_equation->remainder % main_equation->word;
}

void calculateSynchronization (SETI * data)
{
    long long int total = CRT_evaluate(data);
    total < 0 ? printf("Nelze dosahnout.\n")
              : printf("Synchronizace za: %lld\n", total);

}

int main (void)
{
    SETI data;
    if (!readData(&data)) return error();
    calculateSynchronization (&data);
    return 0;
}

