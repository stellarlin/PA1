#include <cstdio>

// Function to stop the program and show an error message
int error() {
    printf("Nespravny vstup.\n");
    return 0;
}

enum results { correct, wrong, undefined };

// Structure to represent a message with a remainder and a word
struct Message {
    long long int remainder = 0;
    long long int word = 0;
};

// Structure to hold SetiData data, including the main equation, storage status, and message counter
struct SetiData {
    Message main_equation;
    bool main_stored = false;
    long long int message_counter = 0;
};

// Function to decode a symbol into its numeric value
long long int decodeSymbol(char symbol) {
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
long long int gcd(long long int a, long long int b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

// Extended Euclidean algorithm to find the coefficients x and y for the equation ax + by = gcd(a, b)
void ext_gcd(long long int a, long long int b, long long int *x, long long int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return;
    }

    long long int x1, y1; // To store results of recursive call
    ext_gcd(b % a, a, &x1, &y1);

    // Update x and y using results of recursive call
    *x = y1 - (b / a) * x1;
    *y = x1;
}

// Function to perform the Chinese Remainder Theorem (CRT) evaluation and meld new equation into main equation
bool CRT_evaluate(SetiData *data, Message *new_message) {
    long long int module, main_coeff, next_coeff;
    Message &main_equation = data->main_equation;

    long long int g = gcd(main_equation.word, new_message->word); //calculate gcd of current message and new to check
                                                                       // the correctness

    // Check if the difference of remainders is divisible by the GCD - if they're not, synchronization isn't possible
    if ((main_equation.remainder - new_message->remainder) % g != 0)
        return false;

    ext_gcd(main_equation.word / g, new_message->word / g, &main_coeff, &next_coeff); // find coefficient
                                            // of  the equation a_word/g x + b_word/g y = 1
    module = main_equation.word / g * new_message->word; // LCM ow main and new equations

    // Update the main equation with new values x = (a1 * m2/g * p + a2 * m1/g * q) mod LCM (m1, m2)
    main_equation.remainder = (main_equation.remainder * (new_message->word / g) * next_coeff +
                               new_message->remainder * (main_equation.word / g) * main_coeff) % module;

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
                return undefined;
        }
    }

    return data->message_counter > 1 ? correct : wrong;
}

int main(void) {
    SetiData data;
    results result = readData(&data);

    if (result == wrong)
        return error();
    result == undefined ? printf("Nelze dosahnout.\n")
                        : printf("Synchronizace za: %lld\n", data.main_equation.remainder % data.main_equation.word);

    return 0;
}
