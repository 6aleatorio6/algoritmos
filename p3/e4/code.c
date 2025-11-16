#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int *num;
    int length;
    struct Node *next;
} Node;

int cmpAsc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int cmpDesc(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}

void insert(Node **head, int *num, int length, char order)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->num = num;
    newNode->next = NULL;
    newNode->length = length;

    qsort(num, length, sizeof(int), order == 'a' ? cmpAsc : cmpDesc);

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        newNode->next = (*head)->next;
        (*head)->next = newNode;
    }
}

int main()
{

    int caseLength = 0;
    scanf("%d\n", &caseLength);

    Node *headNodeImpar = NULL;
    Node *headNodePar = NULL;

    int sizeBatch = caseLength;

    int *arrayPar = malloc(sizeof(int) * sizeBatch);
    int countPar = 0;

    int *arrayImpar = malloc(sizeof(int) * sizeBatch);
    int countImpar = 0;

    for (int caseI = 1; caseI <= caseLength; caseI++)
    {
        int result;
        scanf("%d", &result);

        if (result % 2)
        {
            arrayImpar[countImpar++] = result;

            if (countImpar >= sizeBatch)
            {
                insert(&headNodeImpar, arrayImpar, countImpar, 'd');
                arrayImpar = malloc(sizeof(int) * sizeBatch);
                countImpar = 0;
            }
        }
        else
        {
            arrayPar[countPar++] = result;

            if (countPar >= sizeBatch)
            {
                insert(&headNodePar, arrayPar, countPar, 'a');
                arrayPar = malloc(sizeof(int) * sizeBatch);
                countPar = 0;
            }
        }
    }

    if (countImpar)
    {
        insert(&headNodeImpar, arrayImpar, countImpar, 'd');
    }
    if (countPar)
    {
        insert(&headNodePar, arrayPar, countPar, 'a');
    }

    for (Node *tmp = headNodePar; tmp != NULL; tmp = tmp->next)
    {
        for (size_t i = 0; i < tmp->length; i++)
        {
            printf("%d\n", tmp->num[i]);
        }
    }

    for (Node *tmp = headNodeImpar; tmp != NULL; tmp = tmp->next)
    {

        for (size_t i = 0; i < tmp->length; i++)
        {
            printf("%d\n", tmp->num[i]);
        }
    }

    return 0;
}