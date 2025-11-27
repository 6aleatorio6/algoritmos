#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    char key;
    struct Node *right, *left;
} Node;

typedef Node *NodePoint;

NodePoint newNode(char key)
{

    NodePoint node = malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

NodePoint insert(NodePoint root, char key)
{
    if (root == NULL)
    {
        return newNode(key);
    }

    if (key > root->key)
    {
        root->right = insert(root->right, key);
    }
    else if (key < root->key)
    {
        root->left = insert(root->left, key);
    }

    return root;
}

void readEDR(NodePoint root)
{
    if (root == NULL)
        return;

    readEDR(root->left);
    readEDR(root->right);
    printf("%c", root->key);
}

NodePoint fac(int qntd, char *pre, char *in)
{
    if (qntd == 0)
        return NULL;

    NodePoint root = newNode(pre[0]);

    int sizeLeft = 0;
    while (in[sizeLeft] != root->key)
        sizeLeft++;

    int sizeRight = qntd - (sizeLeft + 1);

    root->left = fac(sizeLeft, pre + 1, in);

    root->right = fac(sizeRight, pre + 1 + sizeLeft, in + sizeLeft + 1);

    return root;
}

int main()
{

    int caase = 0;
    scanf("%d ", &caase);
    for (size_t o = 0; o < caase; o++)
    {
        NodePoint root = NULL;

        char key;
        int size;

        scanf("%d ", &size);

        char *preP = malloc(sizeof(char) * size);
        char *preI = malloc(sizeof(char) * size);

        for (size_t i = 0; scanf("%c", &key) && key != ' '; i++)
        {
            preP[i] = key;
        }

        for (size_t i = 0; scanf("%c", &key) != EOF && key != '\n'; i++)
        {
            preI[i] = key;
        }

        root = fac(size, preP, preI);

        readEDR(root);
        printf("\n");
    }

    return 0;
}
