#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int card;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    Node *tail;
    int length;
} Queue;

void init(Queue *queue)
{
    queue->head = malloc(sizeof(Node));
    queue->head = NULL;
    queue->tail = NULL;

    queue->length = 0;
}

void endInsert(Queue *queue, int newCard)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->card = newCard;
    newNode->next = NULL;

    if (queue->tail == NULL)
    {
        queue->tail = newNode;
        queue->head = newNode;
    }
    else
    {
        queue->tail->next = newNode;
        queue->tail = newNode;
    }
}

void removeFirstNode(Queue *queue)
{
    Node *oldNode = queue->head;

    if (oldNode == queue->tail)
    {
        queue->tail = NULL;
    }

    if (oldNode != NULL)
    {
        queue->head = oldNode->next;

        free(oldNode);
    }
}

int main()
{
    Queue *queue = malloc(sizeof(Queue));
    init(queue);

    endInsert(queue, 1);
    endInsert(queue, 1);
    endInsert(queue, 2);
    removeFirstNode(queue);
    printf("%d |", queue->tail->card);

    // int caseLength = 0;
    // scanf("%d\n", &caseLength);

    // for (int caseI = 1; caseI <= caseLength; caseI++)
    // {
    //     Node *headNode = NULL;
    //     int count = 0;

    //     int result;
    //     while ((result = searchDiamond()))
    //     {
    //         if (result == 1)
    //         {

    //             startInsert(&headNode, '<');
    //             continue;
    //         }

    //         if (result == 2 && headNode != NULL)
    //         {

    //             count++;
    //             endRemove(&headNode);
    //         }

    //         if (result == 4)
    //         {
    //             while (headNode != NULL)
    //             {
    //                 endRemove(&headNode);
    //             }
    //         }
    //     }

    //     printf("%d\n", count);
    // }

    return 0;
}