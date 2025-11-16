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

    for (Node *tmp = *head, *headNext = NULL; 1; tmp = tmp->next)
    {

        if (headNext == NULL)
        {

            if (order == 'a' ? (*head)->num < num : (*head)->num > num)
            {
                // add na frente
                newNode->next = tmp->next;
                tmp->next = newNode;
            }
            else
            {
                // add atras
                newNode->next = *head;
                *head = newNode;
            }

            break;
        }

        if (order == 'a' ? tmp->next->num > num : tmp->next->num < num)
        {
            newNode->next = tmp->next;
            tmp->next = newNode;
            break;
        }

        headNext->next = tmp->next;
    };
}

int main()
{
    Node *headNode = NULL;
    insert(&headNode, 1, 'a');
    insert(&headNode, 2, 'a');
    insert(&headNode, 0, 'a');

    printf("%d", headNode->num);

    // int input;

    // while (scanf("%d", &input) && input)
    // {

    //     Queue *queue = malloc(sizeof(Queue));
    //     init(queue);

    //     for (size_t i = 1; i <= input; i++)
    //     {
    //         endInsert(queue, i);
    //     }

    //     printf("Discarded cards:");
    //     while (queue->length >= 2)
    //     {

    //         printf(" %d",
    //                removeFirstNode(queue));

    //         endInsert(queue,
    //                   removeFirstNode(queue));

    //         if (queue->length >= 2)
    //             printf(",");
    //     }
    //     printf("\nRemaining card: %d\n", queue->head->card);
    // }

    return 0;
}