
#include <cstdio>

// Stop the program and show error message
int error () {
    printf("Nespravny vstup.\n");
    return 0;
}

enum results  {correct, wrong, undefined};


struct Message
{
    long long int  remainder = 0;
    long long int word = 0;
};

struct SETI
{
    Message  main_equation;
    bool main_stored = false;
    long long int message_counter = 0;
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


long long int gcd ( long long int  a, long long int  b)
{
    if (a == 0) return b;
    return gcd (b % a, a);
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


bool CRT_evaluate (SETI * data, Message * new_message)
{
    long long int module, main_coeff,  next_coeff;

        Message & main_equation = data->main_equation;
        long long int g = gcd(main_equation.word, new_message->word);
//
//
//    printf ("GCD of %lld and %lld is %lld\n", main_equation.word, new_message->word, g);

        if ((main_equation.remainder - new_message->remainder) % g != 0) return false;


        ext_gcd(main_equation.word / g, new_message->word / g, &main_coeff, &next_coeff);
        module = main_equation.word / g * new_message->word;

        main_equation.remainder = (main_equation.remainder * (new_message->word / g) * next_coeff
                              + new_message->remainder * (main_equation.word / g) * main_coeff) % module;


        if (main_equation.remainder < 0) main_equation.remainder += module; // Result isn't suppose to be negative
        main_equation.word = module;
return true;
}



bool readMessage (Message * message)
{
    char symbol;
    bool start_detected = false, remainder_reading = true;
    while (true)
    {
        if ((symbol = getchar()) == EOF || symbol == '\n') break;
        else ungetc(symbol, stdin);

        if (scanf ( "%c", &symbol)!= 1 ) return false;
        else if (symbol == '|')
        {
            if(start_detected) return false;
            start_detected = true;
            message->word += message->remainder;
            remainder_reading = false;
        }
        else if (symbol <'a' || symbol > 'z') return false;
        else {
            (remainder_reading ? message->remainder : message->word) += decodeSymbol(symbol);
        }
    }
    //
    //
    // printf("remainder and word: %lld  + %lld\n", message->remainder,  message->word);
    return message->word != 0;
}

results readData (SETI * data)
{
    char c;
    printf ("Zpravy:\n");
    while (1) {

        // ending condition
        //________________________________________
        if ((c = getchar()) == EOF) break;
        else ungetc(c, stdin);
        //________________________________________


        // referenced to message_counter message in SETI signal storage to better code understanding
        Message  current_message;
        //try to read message from input, check if format is correct and decode symbols into 2 values
        if (!readMessage(&current_message)) return wrong;

        data->message_counter++;

        // word with lenght of 1 isn't count
        if (current_message.word < 2) continue;
        if(!data->main_stored)
        {
            data->main_equation = current_message;
            data->main_stored = true;
        }
        else
        {
            if (!CRT_evaluate(data, &current_message)) return undefined;
            //
            //
            // printf("remainder = %lld, word = %lld\n", data->main_equation.remainder, data->main_equation.word);
        }
    }
    return data->message_counter > 1 ? correct : wrong;
}



int main (void)
{
    SETI data;
    results result = readData(&data);
    if (result == wrong) return error();
    result == undefined ?  printf("Nelze dosahnout.\n")
    : printf("Synchronizace za: %lld\n", data.main_equation.remainder % data.main_equation.word);

    return 0;
}

