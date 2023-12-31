
#include <cstdlib>
#include <cstdio>

#define INIT_SIZE 10
#define SIDES_COUNT 4

struct Name
{
    char id;
    int values [SIDES_COUNT];
};
struct Domino
{
    Name name;
    char * duplicates;
    size_t count;
    size_t size;

    void initDomino ()
    {
        size = INIT_SIZE;
        count = 0;

        duplicates = (char *)malloc (size * sizeof(char));
    }

    void insert (char duplicate){
        duplicates[count++] = duplicate;
        if (count == size) reallocDomino();
    }

    void print()
    {
        if(!count) return;
        printf("%c", name.id);
        for (size_t i = 0; i < count; i++)
        {
            printf(" = %c", duplicates[i]);
        }
        printf("\n");
    }
    bool compare ( Name * other)  {

        int * start = &name.values[0];
        int * oth_begin = &other->values[0];
        int * oth_end =  &other->values[SIDES_COUNT];
        int * end = &name.values[SIDES_COUNT];
        int * oth = &other->values[0];
        size_t  seen = 0;

        // abcd = abcd
        // abcd = bcda
        // abcd = cdab
        // abcd = dabc

        while (start != end)
        {
            if (seen == 4) return true;

            auto curr = start + seen - (start + seen >= end) * SIDES_COUNT;

             if (*oth  == *curr)
             {
                 ++oth;
                 if (oth == oth_end) oth = oth_begin;
                 seen++;
             }
             else
             {
                 oth = oth_begin;
                 seen = 0;
                 start++;
             }
        }
        return false;
    }

    void reallocDomino()
    {
        size *= 2;
        char *  new_duplicate = (char * ) realloc (duplicates, size);
        duplicates = new_duplicate;
    }

    void freeDomino () const
    {
        free(duplicates);
    }
};

struct Data {
    Domino *dominoes;
    size_t size;
    size_t count;

    void initData() {
        size = INIT_SIZE;
        count = 0;
        dominoes = (Domino *) malloc(size * sizeof(Domino));
    }

    Domino * find (Name * req_name) const
    {
        for (size_t i = 0; i < count; i++)
        {
            if (dominoes[i].compare(req_name)) return &dominoes[i];
        }
        return nullptr;
    }

   void insert (Name * req_name)
    {
        dominoes[count++].initDomino();
        dominoes[count - 1].name = *req_name;
        if (count == size) reallocData();
    }

    void print () const{
        printf("Unikatni: %zu\n", count);
        printf("Duplikaty:\n");
        for (int i = 0; i<count; i++)
        {
            dominoes[i].print();
        }

    }

    void reallocData()
    {
        size *= 2;
        auto *  new_dominoes = (Domino * ) realloc (dominoes, size);
        dominoes = new_dominoes;
    }

    void freeData() const
    {
        for (size_t i = 0; i < count; i++) dominoes[i].freeDomino();
        free(dominoes);
    }
};

bool readData(Data *data) {

    while(true)
    {
        Name name{};
        if(scanf(" %c", &name.id) != 1) break;
        if(scanf(" [ %d , %d , %d , %d ]",
                 &name.values[0], &name.values[1],
                 &name.values[2], &name.values[3]) != 4) return false;
        Domino * find_result = data->find(&name);
        if (!find_result) data->insert(&name);
        else  find_result->insert(name.id);

    }
    return feof(stdin);
}

int main ()
{
    Data data{};
    data.initData();
    if(readData(&data)) data.print();
    else printf("Nespravny vstup.\n");
    data.freeData();
    return 0;
}