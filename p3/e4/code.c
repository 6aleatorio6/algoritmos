#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int num;
    struct Node *next;
} Node;

void insert(Node **head, int num, char order)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->num = num;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    for (Node *prev = NULL, *tmp = *head; 1; prev = tmp, tmp = tmp->next)
    {
        if (tmp == NULL)
        {
            prev->next = newNode;
            break;
        }

        if (num > tmp->num)
            continue;

        newNode->next = tmp;

        if (prev != NULL)
        {
            prev->next = newNode;
        }
        else
        {
            *head = newNode;
        }

        break;
    };
}

int main()
{

    int caseLength = 0;
    scanf("%d\n", &caseLength);

    Node *headNodeImpar = NULL;
    Node *headNodePar = NULL;

    for (int caseI = 1; caseI <= caseLength; caseI++)
    {
        int result;
        scanf("%d", &result);

        if (result % 2)
        {
            insert(&headNodeImpar, result, 'd');
        }
        else
        {
            insert(&headNodePar, result, 's');
        }
    }

    for (Node *tmp = headNodePar; tmp != NULL; tmp = tmp->next)
    {
        printf("%d\n", tmp->num);
    }

    // for (Node *tmp = headNodeImpar; tmp != NULL; tmp = tmp->next)
    // {
    //     printf("%d\n", tmp->num);
    // }

    return 0;
}