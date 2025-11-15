#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int position;
    struct Node *next;
} Node;

// typedef int Callback(Node *head);

// void forEach(Node *head, Callback cb)
// {

//     Node *tmp = head;
//     while (tmp != NULL)
//     {
//         if (cb(tmp))
//         {
//             break;
//         }

//         tmp = head->next;
//     }
// }

void startInsert(Node *head, int newPosition)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->position = newPosition;
    newNode->next = head->next;

    head->next = newNode;
}

void removeNode(Node *head, int position)
{
    Node *tmp = head;
    while (tmp->next->position != -1)
    {
        Node *prev = tmp;
        Node *target = tmp->next;
        Node *next = tmp->next->next;

        if (position == target->position)
        {
            prev->next = next;

            free(target);
            return;
        }

        tmp = target;
    }
}

void main()
{
    int caseLength = 0;
    scanf("%d", &caseLength);

    for (size_t i = 0; i < caseLength; i++)
    {
        Node headNode = {
            -1, &headNode};

        Node *queueHead = &headNode;
        int queueLenght = 0;

        int size = 0;
        int jump = 0;

        scanf("%d %d", &size, &jump);

        for (size_t position = 1; position <= size; position++)
        {
            startInsert(queueHead, position);
            queueLenght++;
        }

        for (size_t count = 1; queueHead->next->next->position == -1; count = (count + jump) % queueLenght)
        {
            removeNode(queueHead, count);
            queueLenght--;
        }

        printf("Case %d: %d\n", i + 1, queueHead->next->position);
    }
}
