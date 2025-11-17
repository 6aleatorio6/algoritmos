#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    char data;
    struct Node *next;
} Node;

void startInsert(Node **node, char newData)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = *node;

    *node = newNode;
}

void endRemove(Node **node)
{
    if (*node == NULL)
        return;

    if ((*node)->next == NULL)
    {
        free(*node);
        *node = NULL;
        return;
    }

    Node *oldNode = *node;
    *node = oldNode->next;
    free(oldNode);
}

// 0 = end | 1 = diamondL | 2 = diamondR | 3 = trash
int searchDiamond()
{
    int data = getchar();
    if (data == EOF)
        return 0;

    // printf("%c", data);

    switch (data)
    {
    case '(':
        return 1;
    case ')':
        return 2;
    case '\n':
        return 3;
    default:
        return 4;
    }
}

int main()
{

    Node *headNode = NULL;
    Node *headNodeR = NULL;

    int isCorrect = 1;
    int result;
    int outraFlag = 0;
    while ((result = searchDiamond()))
    {

        if (result == 1)
        {

            startInsert(&headNode, '(');
            outraFlag = 0;

            continue;
        }

        if (result == 2)
        {
            if (headNode == NULL)
            {
                startInsert(&headNodeR, 'F');
                isCorrect = 0;
            }
            else
                endRemove(&headNode);
        }

        if (result == 3)
        {

            if (outraFlag)
            {
                break;
            }

            if (isCorrect)
                startInsert(&headNodeR, 'V');

            isCorrect = 1;

            while (headNode != NULL)
            {
                endRemove(&headNode);
            }

            outraFlag = 1;
        }
    }

    for (Node *tmp = headNodeR; tmp != NULL; tmp = tmp->next)
    {
        printf("%s\n", tmp->data != 'V' ? "correct" : "incorrect");
    }

    return 0;
}
