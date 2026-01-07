#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int *data;
    int length;
    int maxLength;
    char name;
} Stack;

typedef Stack *pStack;

pStack init(int maxLength, char name)
{
    pStack stack = malloc(sizeof(Stack));

    stack->data = malloc(sizeof(int) * maxLength);
    stack->length = 0;
    stack->maxLength = maxLength;
    stack->name = name;

    return stack;
}

int pop(pStack stack)
{
    if (!stack->length)
        return -1;

    return stack->data[--stack->length];
}

void push(pStack stack, int newValue)
{
    stack->data[stack->length++] = newValue;
}

int hanoi(int length, pStack origem, pStack aux, pStack dest)
{

    if (length == 1)
    {
        push(dest, pop(origem));
        // printf("| %c-%d %c-%d %c-%d\n", origem->name, origem->length, aux->name, aux->length, dest->name, dest->length);

        return 1;
    }

    int countAux = hanoi(length - 1, origem, dest, aux);

    push(dest, pop(origem));
    // printf("| %c-%d %c-%d %c-%d\n", origem->name, origem->length, aux->name, aux->length, dest->name, dest->length);

    int countDest = hanoi(length - 1, aux, origem, dest);

    return countAux + countDest + 1;
}

int main(int argc, char const *argv[])
{

    for (int i = 1, qntd; scanf("%d", &qntd) != EOF; i++)
    {
        if (!qntd)
            continue;

        pStack stack1 = init(qntd, 'O');
        pStack stack2 = init(qntd, 'A');
        pStack stack3 = init(qntd, 'D');

        for (size_t i = qntd; i > 0; i--)
        {
            push(stack1, i);
        }

        // sem logica, apenas calcula a qntd de mov com eficiencia max
        // int mov = 0;
        // for (size_t i = 0; i < qntd; i++)
        // {
        //     mov *= 2;
        //     mov += 1;
        // }

        // printf("%d\n", mov);
        // printf("\n");

        printf("Teste %d\n", i);
        printf("%d\n", hanoi(qntd, stack1, stack2, stack3));
        printf("\n");

        free(stack1);
        free(stack2);
        free(stack3);
    }

    return 0;
}
