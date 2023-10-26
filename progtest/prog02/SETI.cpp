#include <cstdio>

// Function to stop the program and show an error message
int error() {
    printf("Nespravny vstup.\n");
    return 0;
}

enum results { correct, wrong, undefined };

// Structure to represent a message with a remainder and a word
struct Message {
    __int128_t remainder = 0;
    __int128_t word = 0;
};

// Structure to hold SetiData data, including the main equation, storage status, and message counter
struct SetiData {
    Message main_equation;
    bool main_stored = false;
    __int128_t message_counter = 0;
};


void print_int128 ( __int128_t n)
{
    if (n < 0) {
        putchar('-');
        n = -n;
    }

    if (n > 9) {
        print_int128(n / 10);
    }
    putchar((n % 10) + '0');
}

// Function to decode a symbol into its numeric value
__int128_t decodeSymbol(char symbol) {
    int result = 1;
    int exp = symbol - 'a';
    int base = 2;
    for (;;) {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }
    return result;
}

// Function to calculate the greatest common divisor (GCD) of two numbers using Euclidean algorithm
__int128_t gcd(__int128_t a, __int128_t b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

// Extended Euclidean algorithm to find the coefficients x and y for the equation ax + by = gcd(a, b)
void ext_gcd(__int128_t a, __int128_t b, __int128_t *x, __int128_t *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return;
    }

    __int128_t x1, y1; // To store results of recursive call
    ext_gcd(b % a, a, &x1, &y1);

    // Update x and y using results of recursive call
    *x = y1 - (b / a) * x1;
    *y = x1;
}

// Function to perform the Chinese Remainder Theorem (CRT) evaluation and meld new equation into main equation
bool CRT_evaluate(SetiData *data, Message *new_message) {
    __int128_t module, main_coeff, next_coeff;
    Message &main_equation = data->main_equation;

    __int128_t g = gcd(main_equation.word, new_message->word); //calculate gcd of current message and new to check
                                                                       // the correctness
    if ((main_equation.remainder - new_message->remainder) % g != 0)
        return false;

    ext_gcd(main_equation.word / g, new_message->word / g, &main_coeff, &next_coeff); // find coefficient
                                            // of  the equation a_word/g x + b_word/g y = 1
    module = (main_equation.word / g) * new_message->word; // LCM ow main and new equations

    // Update the main equation with new values x = (a1 * m2/g * p + a2 * m1/g * q) mod LCM (m1, m2)
    main_equation.remainder = main_equation.remainder % module * (new_message->word / g) % module * next_coeff % module  +
                               new_message->remainder % module  * (main_equation.word / g) % module * main_coeff % module;

    if (main_equation.remainder < 0)
        main_equation.remainder += module; // Ensure the result isn't negative


    main_equation.word = module;
    return true;
}

// Function to read a message from input and decode it into a Message structure
bool readMessage(Message *message) {
    char symbol;
    bool start_detected = false, remainder_reading = true;
    while (true) {

        // Ending condition
        //--------------------------------------------------
        if ((symbol = getchar()) == EOF || symbol == '\n')
            break;
        else
            ungetc(symbol, stdin);
        //--------------------------------------------------

        if (scanf("%c", &symbol) != 1)
            return false;

        else if (symbol == '|') {

            if (start_detected) // must be the only one starting symbol '|'  in the row
                return false;
            start_detected = true;

            message->word += message->remainder; // calculate whole word length
            remainder_reading = false; //start reading the second part of the word
        }

        else if (symbol < 'a' || symbol > 'z') // if symbol isn't a small letter
            return false;

        else {
            (remainder_reading ? message->remainder : message->word) += decodeSymbol(symbol);
        }
    }
   return message->word != 0; // word can't be empty
}

// Function to read data, update the SetiData structure, and determine the result
results readData(SetiData *data) {
    char c;
    printf("Zpravy:\n");
    while (1) {
        // Ending condition
        //---------------------------
        if ((c = getchar()) == EOF)
            break;
        else
            ungetc(c, stdin);
        //---------------------------
        // Message counter within SetiData signal storage for better code understanding
        Message current_message;

        // Try to read a message from input, check if the format is correct, and decode symbols into two values
        if (!readMessage(&current_message))
            return wrong;

        data->message_counter++;

        // Words with a length of 1 aren't counted
        if (current_message.word < 2)
            continue;

        // store the first equation into SetiData
        if (!data->main_stored) {
            data->main_equation = current_message;
            data->main_stored = true;
        } else {
            // mild equation into the main equation
            if (!CRT_evaluate(data, &current_message))
                return undefined;}

    }

    return data->message_counter > 1 ? correct : wrong;
}

int main(void) {
    SetiData data;
    results result = readData(&data);

    if (result == wrong)
        return error();
    else if (result == undefined) printf("Nelze dosahnout.\n");
    else
    {
        printf("Synchronizace za: ");
        !data.main_equation.word ? print_int128(0): print_int128( data.main_equation.remainder % data.main_equation.word);
        printf("\n");
    }

    return 0;
}
