#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *data;
    int topo;
    int capacidade;
} Pilha;

void push(Pilha *pilha, char newElem)
{
    pilha->capacidade++;
    pilha->data = realloc(pilha->data, sizeof(char) * pilha->capacidade);
    pilha->data[++(pilha->topo)] = newElem;
}

char pop(Pilha *pilha)
{
    return pilha->data[(pilha->topo)--];
}

int main()
{
    int malFormado = 0;

    Pilha pilhaOBJ = {NULL, -1, 0};
    Pilha *pilha = &pilhaOBJ;

    while (1)
    {
        char e;
        scanf("%c", &e);

        if (e == '!')
        {
            break;
        }

        if (e == '{' || e == '}' || e == '(' || e == ')' || e == '[' || e == ']')
        {
            if (e == '{' || e == '(' || e == '[')
            {
                push(pilha, e);
            }
            else
            {
                if (pilha->topo == -1)
                {
                    malFormado = 1;
                    break;
                }

                char topo = pop(pilha);
                if ((e == '}' && topo != '{') || (e == ')' && topo != '(') || (e == ']' && topo != '['))
                {
                    malFormado = 1;
                    break;
                }
            }
        }
    }

    if (pilha->topo != -1)
    {
        malFormado = 1;
    }

    if (malFormado)
    {
        printf("mal formado");
    }
    else
    {
        printf("bem formado");
    }

    free(pilha->data);
    return 0;
}