#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int data;
    struct Node *l, *r;
} Node;

typedef Node *pNode;

pNode addNode(pNode root, int value)
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
    printf("%d", root->data);
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
    printf("%d", root->data);
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
    printf("%d", root->data);
}

pNode search(pNode root, int value)
{

    if (root != NULL && value > root->data)
    {
        return search(root->r, value);
    }

    if (root != NULL && value < root->data)
    {
        return search(root->l, value);
    }

    return root;
}

pNode removerNo(pNode root, int value)
{

    if (root == NULL)
    {
        return root;
    }

    if (value > root->data)
    {
        root->r = removerNo(root->r, value);
        return root;
    }

    if (value < root->data)
    {
        root->l = removerNo(root->l, value);
        return root;
    }

    //

    if (root->l == NULL)
    {
        pNode tmp = root->r;
        free(root);

        return tmp;
    }
    else if (root->r == NULL)
    {
        pNode tmp = root->l;
        free(root);

        return tmp;
    }

    pNode ant = root->l;
    while (ant->r != NULL)
    {
        ant = ant->r;
    }

    root->data = ant->data;
    root->l = removerNo(root->l, ant->data);

    return root;
}

int altura(pNode root)
{
    if (root == NULL)
    {
        return -1;
    }

    int hl = altura(root->l);
    int hr = altura(root->r);

    return (hl > hr ? hl : hr) + 1;
}

int alturaIt(pNode root)
{
    if (root == NULL)
        return -1; // ou 0, depende do critério

    pNode fila[1000];
    int s = -1, t = 0;

    fila[++s] = root;
    t++;

    int h = -1;

    while (s < t)
    {
        int qntd = t - s;
        h++;

        while (qntd--)
        {
            pNode current = fila[s++];

            if (current->l != NULL)
            {
                fila[t++] = current->l;
            }

            if (current->r != NULL)
            {
                fila[t++] = current->r;
            }
        }
    }

    return h;
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
    int value;

    while (scanf("%9s", comando) != EOF)
    {
        int isFirst = 1;

        if (strcmp(comando, "I") == 0)
        {
            scanf(" %d", &value);
            root = addNode(root, value);
        }

        if (strcmp(comando, "R") == 0)
        {
            scanf(" %d", &value);
            root = removerNo(root, value);
        }

        if (strcmp(comando, "P") == 0)
        {
            scanf(" %d", &value);
            pNode nodeSearched = search(root, value);

            if (nodeSearched != NULL)
            {
                printf("%d existe", value);
            }
            else
            {
                printf("%d nao existe", value);
            }

            printf("\n");
        }

        if (strcmp(comando, "INFIXA") == 0)
        {
            readIn(root, &isFirst);
            printf("\n");
        }

        if (strcmp(comando, "H") == 0)
        {
            printf("%d", alturaIt(root));

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
