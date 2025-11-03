#include "estudante.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Estudante *carregar_estudantes_arquivo(int *tam, char *nomeArquivo)
{
    FILE *file;

    file = fopen(nomeArquivo, "rb");

    if (file == NULL)
    {
        printf("Arquivo Vazio");

        return 0;
    }

    Estudante *students = NULL;

    while (1)
    {
        Estudante student;
        if (fread(&student, sizeof(Estudante), 1, file) == 0)
        {
            break;
        }

        students = realloc(students, sizeof(Estudante) * (*tam + 1));
        *(students + *tam) = student;

        (*tam)++;
    }

    fclose(file);

    return students;
}

void salvar_estudantes_arquivo(Estudante *students, int tam, char *filename)
{
    FILE *file;

    file = fopen(filename, "ab");

    fwrite(students, sizeof(Estudante), tam, file);

    fclose(file);
}

void listar_estudantes(Estudante *students, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        printf("%d. %s -  %d anos\n", i + 1, (students + i)->name, (students + i)->age);
    }
};

Estudante *incluir_estudante(Estudante *students, int *tam)
{

    Estudante newStudent;

    printf("name");
    scanf("%s", newStudent.name);

    printf("age");
    scanf("%d", &newStudent.age);

    students = realloc(students, sizeof(Estudante) * ++(*tam));

    *(students + (*tam - 1)) = newStudent;

    return students;
};

void apagar_estudante(Estudante *students, char *name, int *tam)
{
    for (int i = 0; i < *tam; i++)
    {
        if (strcmp((students + i)->name, name) == 0)
        {
            students[i] = students[*tam - 1];

            students = realloc(students, sizeof(Estudante) * --(*tam));
            printf("apagado");
            return;
        }
    }
};
