#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int position;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    int length;
} Queue;

typedef int Callback(Node *head);

void init(Queue *queue)
{
    queue->head = malloc(sizeof(Node));
    queue->head->next = queue->head;
    queue->head->position = -1;
    queue->length = 0;
}

void startInsert(Queue *queue, int newPosition)
{
    Node *newNode = malloc(sizeof(Node));

    newNode->position = newPosition;
    newNode->next = queue->head->next;

    queue->head->next = newNode;
}

Node *removeNode(Node *node, int jump)
{
    Node *prev;
    Node *target;
    Node *next;

    Node *tmp = node;
    for (int index = 1; index <= jump; index++)
    {
        prev = tmp;

        tmp = target = prev->next;
        next = target->next;

        if (target->position == -1)
            index--;
    }

    prev->next = next;
    free(target);

    return prev;
}

void main()
{
    int caseLength = 0;
    scanf("%d", &caseLength);

    for (int caseI = 1; caseI <= caseLength; caseI++)
    {

        Queue *queue = malloc(sizeof(Queue));
        init(queue);

        int size = 0;
        int jump = 0;
        scanf("%d %d", &size, &jump);

        for (int position = 0; position < size; position++)
        {
            startInsert(queue, size - position);
            queue->length++;
        }

        Node *tmp = queue->head;
        while (queue->length != 1)
        {
            tmp = removeNode(tmp, jump);
            queue->length--;
        }

        printf("Case %d: %d\n", caseI, queue->head->next->position);
    }
}
