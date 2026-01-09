#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct
{
    char **data;
    int length;
    int size;
} Array;

typedef Array *pArray;

pArray init(int size)
{
    pArray newArray = malloc(sizeof(Array));

    newArray->length = 0;
    newArray->size = size;
    newArray->data = malloc(sizeof(char *) * size);

    return newArray;
}

void add(pArray array, char *newString)
{

    if (array->length - 1 == array->size)
    {
        array->size *= 2;
        array->data = realloc(array->data, sizeof(char *) * array->size);
    }

    char *newStringCopy = malloc(sizeof(char) * strlen(newString));
    strcpy(newStringCopy, newString);
    array->data[array->length++] = newStringCopy;
}

void ordenarAlfa(pArray array)
{
    for (size_t i = 0; i < array->length; i++)
    {
        for (size_t j = 0; j < array->length - 1; j++)
        {
            char *dataSwap = array->data[j];

            if (strcmp(dataSwap, array->data[j + 1]) > 0)
            {
                array->data[j] = array->data[j + 1];
                array->data[j + 1] = dataSwap;
            }
        }
    }
}

void freeArray(pArray array)
{

    for (size_t i = 0; i < array->length; i++)
    {
        free(array->data[i]);
    }

    free(array->data);
    free(array);
}

int main(int argc, char const *argv[])
{

    int P = -1, A = -1, R = -1;
    scanf("%d %d %d\n", &P, &A, &R);
    while (P + A + R != 0)
    {
        pArray APerolas = init(P);
        pArray AAlunos = init(A);
        pArray ARespostas = init(A * R);
        pArray AResultado = init(A * R);

        for (size_t i = 0; i < P; i++)
        {
            char perola[10001];
            fgets(perola, sizeof(perola), stdin);
            add(APerolas, perola);
        }

        for (size_t i = 0; i < A * (R + 1); i++)
        {
            if (i % (R + 1) == 0)
            {
                char nome[10001];
                fgets(nome, sizeof(nome), stdin);

                add(AAlunos, nome);
                continue;
            }

            char resposta[10001];
            fgets(resposta, sizeof(resposta), stdin);
            add(ARespostas, resposta);
        }

        int qntdMaior = -1;

        char *resposta = ARespostas->data[0];
        int qntdDeErroDoALuno = 0;
        for (int i = 0; i < ARespostas->length; resposta = ARespostas->data[++i])
        {
            for (size_t i = 0; i < APerolas->length; i++)
            {
                if (strcmp(APerolas->data[i], resposta) == 0)
                {
                    qntdDeErroDoALuno++;
                }
            }

            if ((i + 1) % R == 0 && i != 0)
            {

                char *nomeAluno = AAlunos->data[i / R];

                if (qntdMaior < qntdDeErroDoALuno)
                {
                    qntdMaior = qntdDeErroDoALuno;
                    AResultado->length = 0;
                    add(AResultado, nomeAluno);
                }
                else if (qntdMaior == qntdDeErroDoALuno)
                {
                    add(AResultado, nomeAluno);
                }
                qntdDeErroDoALuno = 0;
            }
        }

        ordenarAlfa(AResultado);
        int isRepetido = 0;
        char *charSwap = "asd";
        for (size_t i = 0; i < AResultado->length; i++)
        {
            isRepetido = 0;

            AResultado->data[i][strcspn(AResultado->data[i], "\n")] = '\0';
            if (strcmp(AResultado->data[i], charSwap) == 0)
                isRepetido = 1;

            if (!isRepetido)
            {
                printf("%.101s", AResultado->data[i]);
            }

            charSwap = AResultado->data[i];

            if (i < AResultado->length - 1)
            {
                if (!isRepetido)
                {
                    printf(", ");
                }
            }
            else
            {
                printf("\n");
            }
        }

        freeArray(APerolas);
        freeArray(AAlunos);
        freeArray(ARespostas);
        freeArray(AResultado);
        scanf("%d %d %d\n", &P, &A, &R);
    }

    return 0;
}
