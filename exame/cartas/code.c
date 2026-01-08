#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

typedef Node *pNode;

typedef struct
{
    pNode start;
    pNode end;
} Queue;

typedef Queue *pQueue;

pQueue initQueue()
{
    pQueue newQueue = malloc(sizeof(Queue));

    newQueue->end = NULL;
    newQueue->start = NULL;
    return newQueue;
}

void addEnd(pQueue queue, int newValue)
{
    pNode newNode = malloc(sizeof(Node));
    newNode->value = newValue;
    newNode->next = NULL;

    if (queue->end == NULL)
    {
        queue->start = newNode;
        queue->end = newNode;
        return;
    }

    queue->end->next = newNode;
    queue->end = newNode;
}

pNode removeStart(pQueue queue)
{

    pNode oldNode = queue->start;

    if (oldNode == NULL)
    {
        return NULL;
    }

    int value = oldNode->value;

    queue->start = oldNode->next;

    if (queue->start == NULL)
    {
        queue->end = NULL;
    }

    return oldNode;
}

int main(int argc, char const *argv[])
{

    // pQueue queue = initQueue();

    // testar addEnd

    // addEnd(queue, 1);
    // printf("%d", queue->start->value);
    // printf("%d", queue->end->value);
    // addEnd(queue, 2);
    // printf("%d", queue->end->value);
    // printf("%d", queue->start->value);

    // testar removeStart

    // addEnd(queue, 1);
    // addEnd(queue, 2);
    // removeStart(queue);
    // printf("a%d", queue->start->value);
    // printf("%d", removeStart(queue)->value);

    int n;
    scanf("%d", &n);
    while (n != 0)
    {
        // printf("%d\n", n);
        pQueue queue = initQueue();

        for (int i = 0; i < n; i++)
        {
            // printf("%d", i);
            addEnd(queue, i + 1);
        }

        printf("Discarded cards: ");
        int isStart = 1;
        while (queue->start != NULL && queue->start->next != NULL)
        {
            if (isStart)
            {
                isStart = 0;
            }
            else
            {
                printf(", ");
            }

            pNode nodeRemoved = removeStart(queue);
            printf("%d", nodeRemoved->value);

            free(nodeRemoved);

            pNode node = removeStart(queue);
            addEnd(queue, node->value);

            free(node);
        }

        printf("\nRemaining card: %d\n", queue->start->value);

        scanf("%d", &n);
    }

    /* code */
    return 0;
}
