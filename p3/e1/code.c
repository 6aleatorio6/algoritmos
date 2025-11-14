#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int position;
    struct Node *next;
} Node;

typedef int Callback(Node *head);

void forEach(Node *head, Callback cb)
{

    Node *tmp = head;
    while (tmp != NULL)
    {
        if (cb(tmp))
        {
            break;
        }

        tmp = head->next;
    }
}

int printNode(Node *node)
{
    printf("position: %d\n", node->position);

    return 0;
}

Callback remove(Node *node, int position)
{

    int removeCb(Node * nodeCb)
    {
        return nodeCb->position
    }

    return removeCb
}

void main()
{
    Node initialNode = {
        1, NULL};

    Node *queueHead = &initialNode;

    // forEach(queueHead, printNode);
}
