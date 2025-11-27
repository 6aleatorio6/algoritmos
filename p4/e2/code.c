#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

// Em-Ordem (Esquerda -> Raiz -> Direita)
void readERD(NodePoint root, int *hasSpace)
{

    if (root == NULL)
        return;

    readERD(root->left, hasSpace);

    if (*hasSpace)
    {
        printf(" ");
        *hasSpace = 0;
    }
    printf("%c", root->key);

    *hasSpace = 1;

    readERD(root->right, hasSpace);
}

// Pré-Ordem (Raiz -> Esquerda -> Direita)
void readRED(NodePoint root, int *hasSpace)
{
    if (root == NULL)
        return;

    if (*hasSpace)
    {
        printf(" ");
        *hasSpace = 0;
    }
    printf("%c", root->key);
    *hasSpace = 1;

    readRED(root->left, hasSpace);
    readRED(root->right, hasSpace);
}

// Pós-Ordem (Esquerda -> Direita -> Raiz)
void readEDR(NodePoint root, int *hasSpace)
{
    if (root == NULL)
        return;

    readEDR(root->left, hasSpace);
    readEDR(root->right, hasSpace);

    if (*hasSpace)
    {
        printf(" ");
        *hasSpace = 0;
    }
    printf("%c", root->key);

    *hasSpace = 1;
}

int isExist(NodePoint root, char key)
{
    if (root == NULL)
        return 0;

    if (root->key == key)
        return 1;

    return isExist(key > root->key ? root->right : root->left, key);
}

int main()
{
    NodePoint root = NULL;

    char command[10];
    char value;
    while (scanf("%s", command) != EOF)
    {

        if (strcmp(command, "I") == 0)
        {
            scanf(" %c\n", &value);
            root = insert(root, value);
        }

        if (strcmp(command, "P") == 0)
        {
            scanf(" %c\n", &value);

            printf(isExist(root, value) ? "%c existe" : "%c nao existe", value);
            printf("\n");
        }

        if (strcmp(command, "INFIXA") == 0)
        {
            int aux = 0;
            readERD(root, &aux);
            printf("\n");
        }

        if (strcmp(command, "PREFIXA") == 0)
        {

            int aux = 0;
            readRED(root, &aux);
            printf("\n");
        }

        if (strcmp(command, "POSFIXA") == 0)
        {
            int aux = 0;
            readEDR(root, &aux);
            printf("\n");
        }
    }

    return 0;
}
