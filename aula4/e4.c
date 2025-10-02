#include <stdio.h>
#include <stdlib.h>

typedef struct Student
{
    char name[50];
    unsigned int age;
} Student;

int main() {
};

Student *studentCreate()
{
    Student *students = calloc(1, sizeof(Student));

    if (students == NULL)
    {
        printf('Sem memoria para iniciar o loop');
        exit(EXIT_FAILURE);
    }

    for (int i = 0, isFinish; isFinish != 1; i++)
    {

        Student student;

        printf('digite o nome e a idade');
        scanf('%50c %d', &student.name, &student.age);

        students = realloc(students, (1 + i) * sizeof(students));
        if (students == NULL)
        {
            printf('Sem memoria para inclementar o array');
            exit(EXIT_FAILURE);
        }

        *(students + i) = student;

        printf('terminou? (0 | 1)');
        scanf('%d', &isFinish);
    }

    return students;
};
