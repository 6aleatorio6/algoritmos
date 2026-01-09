#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *l, *r;
} Node;

typedef Node *pNode;

typedef struct Queue
{
    pNode *data;
    int s;
    int t;
} Queue;

typedef Queue *pQueue;

pQueue initQueue(int size)
{
    pQueue newQueue = malloc(sizeof(Queue));

    newQueue->data = malloc(sizeof(pNode) * size);
    newQueue->s = -1;
    newQueue->t = 0;

    return newQueue;
}

void enqueue(pQueue queue, pNode newValue)
{
    queue->data[queue->t++] = newValue;

    if (queue->s == -1)
    {
        queue->s++;
    }
}
pNode denqueue(pQueue queue)
{
    return queue->data[queue->s++];
}

pNode addNode(pNode root, int newValue)
{

    if (root == NULL)
    {
        pNode newNode = malloc(sizeof(Node));

        newNode->data = newValue;
        newNode->l = NULL;
        newNode->r = NULL;
        return newNode;
    }

    if (newValue > root->data)
    {
        root->r = addNode(root->r, newValue);
    }

    if (newValue < root->data)
    {
        root->l = addNode(root->l, newValue);
    }

    return root;
}

// void readLarge(pNode root, int size)
// {

//     pQueue queue = initQueue(size);

//     enqueue(queue, root);

//     while (queue->s != queue->t)
//     {
//         pNode node = denqueue(queue);

//         if (node->l != NULL)
//         {
//             enqueue(queue, node->l);
//         }

//         if (node->r != NULL)
//         {
//             enqueue(queue, node->r);
//         }

//         printf("%d", node->data);
//         if (queue->s < queue->t)
//         {
//             printf(" ");
//         }
//     }
//     printf("\n");
// }

void readLarge(pNode root, int size)
{

    pNode *queue = malloc(sizeof(pNode) * size);
    int s = -1, t = 0;

    s++;
    queue[t++] = root;

    while (s != t)
    {
        pNode node = queue[s++];

        if (node->l != NULL)
        {
            queue[t++] = node->l;
        }

        if (node->r != NULL)
        {
            queue[t++] = node->r;
        }

        printf("%d", node->data);
        if (s < t)
        {
            printf(" ");
        }
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{

    int qntd;
    scanf("%d\n", &qntd);

    for (int i = 0; i < qntd; i++)
    {
        pNode root = NULL;

        int qntdByLine;

        scanf("%d\n", &qntdByLine);
        printf("Case %d:\n", i + 1);
        for (size_t i = 0; i < qntdByLine; i++)
        {
            int newValue;
            scanf("%d", &newValue);
            root = addNode(root, newValue);
        }

        readLarge(root, qntdByLine);
        printf("\n");
    }

    return 0;
}
