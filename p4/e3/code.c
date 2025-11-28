#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node
{
    int key;
    struct Node *right, *left;
} Node;

typedef Node *NodePoint;

NodePoint newNode(int key)
{

    NodePoint node = malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

NodePoint insert(NodePoint root, int key)
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
    printf("%d", root->key);

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
    printf("%d", root->key);
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
    printf("%d", root->key);

    *hasSpace = 1;
}

int isExist(NodePoint root, int key)
{
    if (root == NULL)
        return 0;

    if (root->key == key)
        return 1;

    return isExist(key > root->key ? root->right : root->left, key);
}

NodePoint encontrarMaior(NodePoint root)
{

    NodePoint node = root;
    while (node->right != NULL)
    {
        node = node->right;
    }

    return node;
}

NodePoint removeNode(NodePoint root, int key)
{

    if (root == NULL)
        return root;

    if (root->key > key)
    {
        root->left = removeNode(root->left, key);
    }
    else if (root->key < key)
    {
        root->right = removeNode(root->right, key);
    }
    else
    {
        // se encontrar

        if (root->left == NULL)
        {
            NodePoint temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL)
        {
            NodePoint temp = root->left;
            free(root);
            return temp;
        }

        NodePoint temp = encontrarMaior(root->left);
        root->key = temp->key;
        root->left = removeNode(root->left, temp->key);
    }

    return root;
}

int main()
{
    NodePoint root = NULL;

    char command[10];
    int value;
    while (scanf("%s", command) != EOF)
    {

        if (strcmp(command, "I") == 0)
        {
            scanf(" %d\n", &value);
            root = insert(root, value);
        }

        if (strcmp(command, "P") == 0)
        {
            scanf(" %d\n", &value);

            printf(isExist(root, value) ? "%d existe" : "%d nao existe", value);
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

        if (strcmp(command, "R") == 0)
        {
            scanf(" %d\n", &value);
            root = removeNode(root, value);
        }
    }

    return 0;
}
