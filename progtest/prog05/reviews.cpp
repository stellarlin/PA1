
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>

#define INIT_SIZE 10
#define BEGIN_YEAR 1800
#define END_YEAR 3000
#define YEAR 365
#define MAX_MESSAGE 4096

struct Review
{
    int evaluation;
    char message [MAX_MESSAGE + 1];
};

struct Date
{
    int year = 0;
    int month = 0;
    int day = 0;

    int coeff = -1;
};

struct Day
{
    Date date {};
    int rev_sum = 0;
    int rev_count = 0;
    int rev_size = 0;
    Review * reviews = NULL;
};

struct Storage
{
    Day * data;
    int count;
    int size;
    int sum;
    bool empty () const { return count == 0;}
};

int error() {
    printf("Nespravny vstup.\n");
    return 0;
}


// check if year is leap year
bool isLeap (int year)
{
    if(year % 4 == 0 && (year % 100 != 0 || (year % 100 == 0 && year % 400 == 0 && year % 4000 !=0))) return true;
    return false;
}

//return number of days
int month_days(int m, int y)
{
    switch(m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;

        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return !isLeap(y) ? 28 : 29;
    }
    return 0;
}


bool readDate (Date * date)
{
    return scanf("%d-%d-%d", &date->year, &date->month, &date->day) == 3
        && date->year >= BEGIN_YEAR && date->year <= END_YEAR
        && date->month > 0 && date->month <=12
        && date->day >=1 && date->day <=month_days(date->month, date->year);
}

long long int  calculateCoeff (Date * date) {
    if (date->coeff != -1) return date->coeff;
    date->coeff = 0;
    // Calculate days for full years
    int fullYears = date->year - BEGIN_YEAR;
    date->coeff = fullYears * YEAR + (fullYears / 4) - (fullYears / 100) + (fullYears / 400) - (fullYears / 4000);
    // Calculate days for full months
    for (int m = 1; m < date->month; m++)  date->coeff += month_days(m, date->year);
    // Add days of the current month
    date->coeff += date->day;
    return date->coeff;
}

enum Result { ERROR = 0, PREV = 1, NEW = 2};
Result isDateAfter (Storage * storage, Date * newDate) {
    if (storage->empty()) return NEW;

    Date & prevDate =  storage->data[storage->count - 1].date;
    if (calculateCoeff(&prevDate) > calculateCoeff(newDate)) return ERROR;
    else if (prevDate.coeff == newDate->coeff) return PREV;

    return NEW;
}

bool initDay(Day * day, Date *date) {

    day->date = *date;
    day->rev_sum = 0;
    day->rev_count = 0;
    day->rev_size = INIT_SIZE;
    day->reviews = (Review *) malloc(day->rev_size * sizeof (Review));
    return day->reviews;
}

bool reallocStorage(Storage *storage) {
    storage->size *= 2;
    Day * newData = (Day *) realloc(storage->data, storage->size * sizeof (Day));
    if (!newData) return false;
    storage->data = newData;
    return true;
}

bool insertDay(Storage *storage, Date * date) {
    if (!initDay (&storage->data[storage->count++], date)) return false;
    if (storage->count == storage->size && !reallocStorage (storage)) return false;
    return true;
}

bool readReview(Review *review) {
    if ( scanf (" %d", &review->evaluation) != 2
    &&  review->evaluation < 1) return false;

    char c;
    bool start_reading = false, end_reading = false;
    char * current = &review->message[0];

    if(getchar() != ' ') return false;

    while ((c = getchar()) != EOF && c != '\n'  )
    {
        if (!start_reading && !isspace (c)) start_reading = true;

        if (start_reading && !end_reading)
        {
            if (isspace(c)) {
                end_reading = true;
                *current = '\0';
                continue;
            }
            else if (current == &review->message[MAX_MESSAGE]) return false;
            *current = c;
            ++current;
        }
        else if (end_reading && !isspace(c)) return false;
    }
    *current = '\0';
    auto len = strlen(review->message);
    return len > 0 && len <= MAX_MESSAGE;
}

bool reallocRevies(Day *currentDay) {
    currentDay->rev_size *= 2;
    Review * newReviews = (Review *) realloc (currentDay->reviews, currentDay->rev_size * sizeof(Review));
    if (!newReviews) return false;
    currentDay->reviews = newReviews;
    return true;
}

bool insertReview(Day *currentDay, Review *review) {
    currentDay->reviews[currentDay->rev_count++] = *review;
    currentDay->rev_sum += review->evaluation;

    if (currentDay->rev_count == currentDay->rev_size
    && !reallocRevies (currentDay)) return false;
    return true;
}

bool insert(Storage * storage ) {
    Review review;
      Date date;

      if(!readDate(&date)) return false;
      switch (isDateAfter(storage, &date)) {
          case ERROR: return false;
          case PREV: break;
          case NEW: if (!insertDay(storage, &date)) return false;
              break;
      }
      Day * current = &storage->data[storage->count - 1];
      if (!readReview (&review)) return false;
    if (!insertReview(current, &review)) return false;

    storage->sum += review.evaluation;
    return true;
}


struct Interval {
    int start;
    int end;
    int diff;
    int sum;
};

struct Interval findClosestInterval(Storage * storage,  int target) {
    int start = 0;
    int end = 0;
    int prevDiff;
    int prevSum = 0;
    int currDiff = -1;
    int currSum = 0;

    Interval result = {-1, -1, -1, 0};
    Interval tmp;

    if (target >= storage->sum) return {0, storage->count - 1, 0, storage->sum};
    while (start <= end && end < storage->count)
    {
        //copy previous interval
        currSum += storage->data[end].rev_sum;

        prevDiff = currDiff;
        currDiff =  currSum - target;

        if(currDiff >= 0) {
            prevDiff < 0 || abs(currDiff) <= abs(prevDiff) ? tmp = {start, end, abs(currDiff), currSum}
                                            : tmp = {start,  end - (end != 0), abs(prevDiff), prevSum};
            prevSum =currSum;
            currSum -= storage->data[start].rev_sum;
            if (start == end) end++;
            else currSum -= storage->data[end].rev_sum;
            start++;
        }
        else
        {
            tmp = {start, end, abs(currDiff), currSum};
            prevSum =currSum;
            end++;
        }

        if (result.diff < 0 || tmp.diff  < result.diff) result = tmp;
        if (tmp.diff == result.diff) {
            if (tmp.end > result.end
            || (tmp.end == result.end && tmp.sum  > result.sum)) result = tmp;
        }
        }
    return result;
    }


void printDate(Date *date) {
    printf ("%4d-%02d-%02d", date->year, date->month, date->day);

}
void printInterval (Interval  interval, Storage * storage, bool print)
{
    printDate (&storage->data[interval.start].date);
    printf (" - ");
    printDate(&storage->data[interval.end].date);
    printf (": %d\n", interval.sum);

    if(print) {
        for (int day = interval.start; day <= interval.end; day++)
        {
            for (auto rev = &storage->data[day].reviews[0];
            rev != &storage->data[day].reviews[storage->data[day].rev_count]; ++rev)
            {
                printf ("  %d: %s\n", rev->evaluation, rev->message);
            }
        }
    }
    }

bool calculateClosest(Storage * storage, bool print_flag) {
    int search_value;
    if (scanf ("%d", &search_value) != 1 || search_value < 1 || storage->empty()) return false;
    char c;
    while ((c = getchar())!= EOF && c != '\n')
    {if (!isspace(c)) return false;}

    printInterval(findClosestInterval(storage, search_value), storage, print_flag);

    return true;
}


bool read_input (Storage * storage )
{
    printf("Recenze:\n");
    bool error_flag;
    while (true) {
        char sign = getchar();

        if (sign == EOF) break;
        if ((sign != '+' && sign != '?' && sign !='#') || (getchar()) != ' ') break;

            switch (sign) {
                case '+':
                    error_flag = !insert(storage);
                    break;
                case '?':
                    error_flag = !calculateClosest(storage, true);
                    break;
                case '#':
                    error_flag = !calculateClosest (storage, false);
                    break;
            }
            if(error_flag)break;
        }
        return (feof(stdin) && !error_flag);
}


bool initStorage(Storage *storage) {

    storage->count = 0;
    storage->size = INIT_SIZE;
    storage->sum = 0;
    storage->data = (Day *) malloc (storage->size * sizeof (Day));
    if (!storage->data) return false;

    return true;
}



void freeStorage(Storage *storage) {

    for (int i = 0; i < storage->count; i++) free(storage->data[i].reviews);
    free(storage->data);
    storage->count = 0;
    storage->size = 0;
}

int main ()
{
    Storage storage;
    if (!initStorage(&storage)) return error();

    if(!read_input(&storage)) return  error();
    freeStorage (&storage);
    return 0;
}
/*
int main() {
    const int length = 4096;
    char randomString[length + 1];  // +1 for null terminator

    // Seed for randomization
    std::srand(std::time(0));

    // Generate a random string with digits and letters
    for (int i = 0; i < length; ++i) {
        // ASCII values for digits (48-57) and uppercase letters (65-90)
        int randomChar = std::rand() % 36 + 48;
        if (randomChar > 57) {
            // Skip ASCII values between 58 and 64
            randomChar += 7;
        }
        randomString[i] = static_cast<char>(randomChar);
    }

    randomString[length] = '\0';  // Null terminator

    // Print the generated string
    std::cout << randomString << std::endl;

    return 0;
}*/