#include <stdlib.h>
#include <stdio.h>

typedef struct No
{
    int value;
    struct No *next;
} No;

void inserir_inicio(No **cabeca, int value)
{
    No *novo_no = malloc(sizeof(No));
    novo_no->next = *cabeca;
    novo_no->value = value;

    *cabeca = novo_no;
}

void inserir_fim(No **cabeca, int value)
{
    No *novo_no = malloc(sizeof(No));
    novo_no->next = NULL;
    novo_no->value = value;

    if (*cabeca == NULL)
    {
        *cabeca = novo_no;
    }
    else
    {
        No *temp = *cabeca;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = novo_no;
    }
}

void listagem(No **cabeca)
{
    No *temp = *cabeca;

    while (temp != NULL)
    {
        printf("%d ", temp->value);
        temp = temp->next;
    }
}

int main()
{
    No *lista = NULL;

    inserir_inicio(&lista, 20);
    inserir_fim(&lista, 30);
    inserir_fim(&lista, 30);
    inserir_inicio(&lista, 230);

    listagem(&lista);

    return 0;
}
