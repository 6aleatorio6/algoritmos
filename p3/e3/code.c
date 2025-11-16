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

    queue->length++;
}

int removeFirstNode(Queue *queue)
{
    Node *oldNode = queue->head;
    int card = oldNode->card;

    if (oldNode == queue->tail)
    {
        queue->tail = NULL;
    }

    if (oldNode != NULL)
    {
        queue->head = oldNode->next;

        free(oldNode);
        queue->length--;
    }

    return card;
}

int main()
{
    int input;

    while (scanf("%d", &input) && input)
    {

        Queue *queue = malloc(sizeof(Queue));
        init(queue);

        for (size_t i = 1; i <= input; i++)
        {
            endInsert(queue, i);
        }

        printf("Discarded cards:");
        while (queue->length >= 2)
        {

            printf(" %d",
                   removeFirstNode(queue));

            endInsert(queue,
                      removeFirstNode(queue));

            if (queue->length >= 2)
                printf(",");
        }
        printf("\nRemaining card: %d\n", queue->head->card);
    }

    return 0;
}