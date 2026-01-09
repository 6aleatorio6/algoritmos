#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char data;
    struct Node *l, *r;
} Node;

typedef Node *pNode;

pNode addNode(pNode root, char value)
{
    if (root == NULL)
    {
        pNode newNode = malloc(sizeof(Node));
        newNode->data = value;
        newNode->l = NULL;
        newNode->r = NULL;

        return newNode;
    }

    if (value > root->data)
    {
        root->r = addNode(root->r, value);
    }

    if (value < root->data)
    {
        root->l = addNode(root->l, value);
    }

    return root;
}

void readIn(pNode root, int *isFirst)
{
    if (root == NULL)
        return;

    readIn(root->l, isFirst);

    if (!*isFirst)
    {
        printf(" ");
    }
    else
    {
        *isFirst = 0;
    }
    printf("%c", root->data);
    readIn(root->r, isFirst);
}

void readPre(pNode root, int *isFirst)
{
    if (root == NULL)
        return;

    if (!*isFirst)
    {
        printf(" ");
    }
    else
    {
        *isFirst = 0;
    }
    printf("%c", root->data);
    readPre(root->l, isFirst);
    readPre(root->r, isFirst);
}

void readPos(pNode root, int *isFirst)
{
    if (root == NULL)
        return;

    readPos(root->l, isFirst);
    readPos(root->r, isFirst);
    if (!*isFirst)
    {
        printf(" ");
    }
    else
    {
        *isFirst = 0;
    }
    printf("%c", root->data);
}

void search(pNode root, char value)
{
    if (root == NULL)
    {
        printf("%c nao existe", value);
        return;
    }
    if (value == root->data)
    {
        printf("%c existe", value);
        return;
    }

    if (value > root->data)
    {
        search(root->r, value);
    }

    if (value < root->data)
    {
        search(root->l, value);
    }
}

int main(int argc, char const *argv[])
{

    pNode root = NULL;

    // root = addNode(root, 'a');
    // root = addNode(root, 'c');
    // root = addNode(root, 'b');

    // readIn(root);
    // printf("\n");
    // readPre(root);
    // printf("\n");
    // readPos(root);
    // printf("\n");
    // search(root, 't');

    char comando[10];
    char value;

    int count = 0;
    while (scanf("%9s", comando) != EOF)
    {
        int isFirst = 1;

        if (strcmp(comando, "I") == 0)
        {
            scanf(" %c", &value);
            root = addNode(root, value);
            count++;
        }

        if (strcmp(comando, "P") == 0)
        {
            scanf(" %c", &value);
            search(root, value);
            printf("\n");
        }

        if (strcmp(comando, "INFIXA") == 0)
        {
            readIn(root, &isFirst);
            printf("\n");
        }

        if (strcmp(comando, "PREFIXA") == 0)
        {
            readPre(root, &isFirst);
            printf("\n");
        }

        if (strcmp(comando, "POSFIXA") == 0)
        {
            readPos(root, &isFirst);
            printf("\n");
        }
    }

    return 0;
}
