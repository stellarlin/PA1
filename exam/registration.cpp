
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define INIT_SIZE 10
#define NAME_SIZE 53
#define NAME_COUNT 3

struct CName
{
    char names [NAME_COUNT][NAME_SIZE] = {"\0", "\0", "\0"};
    size_t count = 0;
};
struct CPerson
{
    CName name;
    bool registered = false;
    bool presented = false;
};

struct CStudents
{
    CPerson * students;
    size_t size;
    size_t count;
    void initStudents ()
    {
        size = INIT_SIZE;
        count = 0;
        students = (CPerson *) malloc (size * sizeof(CPerson));
    }

    void reallocStudents ()
    {
        size = 2 * size;
        auto new_data = (CPerson *) realloc (students, size * sizeof(CPerson)) ;
        students = new_data;
    }
    void freeStudents () const
    {
        free (students);
    }
};

bool readName (char * name)
{
  char * letter = name;
  while (true)
  {
      if (letter == &name[NAME_SIZE]) return false;
      *letter = (char)getchar();
      if (*letter == EOF || *letter == '\n' || *letter == ' ')
      {
          ungetc(*letter, stdin);
          break;
      }

      ++letter;
  }
  *letter = '\0';
    return true;
}

CPerson *insertName(CStudents *data, CName * name) {
    auto & student = data->students[data->count];
    student.name = *name;
    data->count++;
    if (data->count == data->size)
    {
        data->reallocStudents();
    }
    return &student;
}

CPerson *findName(CStudents *data, CName name) {
    return nullptr;
}

bool readStudents (CStudents * data)
{
    printf ("Studenti:\n");
    bool registration_end = false;
    while (true)
    {
        char mode;
        char space;
        CName name;
        if ((mode = (char)getchar()) == EOF) break;
        else ungetc(mode, stdin);

        if(scanf(" %c:", &mode)!=1
        || (mode != 'R' && mode != 'P')
        || (mode == 'R' && registration_end)) return false;

        if(mode == 'P') registration_end = true;



        for (size_t i = 0; i < NAME_COUNT && name.count < NAME_COUNT; i++)
        {
            if ((space = (char)getchar()) == EOF || space == '\n') break;
            if (space != ' ') return false;

            if(!readName(name.names[i]) || !strcmp(name.names[i],"")) return false;
            name.count++;
        }

        CPerson * person;
        switch (mode)
        {
            case 'R':  person = insertName (data, &name);
            person->registered = true;
                break;
            case 'P': person = findName(data, name);
                if (!person) person = insertName (data, &name);
                person->presented = true;
                break;
            default: return false;
        }
    }
    return feof(stdin);
}

int error()
{
    printf ("Nespravny vstup.\n");
    return 0;
}
int main()
{
    CStudents data{};
    data.initStudents();
    if(!data.students) return error();
    if (!readStudents(&data)) return error();
    data.freeStudents();
    return 0;
}