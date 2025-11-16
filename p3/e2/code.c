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
    char data;

    if (!scanf("%c", &data))
        return 0;

    // printf("%c", data);

    switch (data)
    {
    case '<':
        return 1;
    case '>':
        return 2;
    case '\n':
        return 0;
    case '.':
        return 3;
    default:
        return 4;
    }
}

int main()
{
    int caseLength = 0;
    scanf("%d\n", &caseLength);

    for (int caseI = 1; caseI <= caseLength; caseI++)
    {
        Node *headNode = NULL;
        int count = 0;

        int result;
        while ((result = searchDiamond()))
        {
            if (result == 1)
            {

                startInsert(&headNode, '<');
                continue;
            }

            if (result == 2 && headNode != NULL)
            {

                count++;
                endRemove(&headNode);
            }

            if (result == 4)
            {
                while (headNode != NULL)
                {
                    endRemove(&headNode);
                }
            }
        }

        printf("%d\n", count);
    }

    return 0;
}
