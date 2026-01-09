#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char data;
    struct Node *l;
    struct Node *r;
} Node;

typedef Node *pNode;

pNode addNode(pNode root, char newChar)
{
    if (root == NULL)
    {
        pNode newNode = malloc(sizeof(Node));

        newNode->data = newChar;
        newNode->l = NULL;
        newNode->r = NULL;

        return newNode;
    }

    if (newChar > root->data)
    {
        root->r = addNode(root->r, newChar);
    }
    else
    {
        root->l = addNode(root->l, newChar);
    }

    return root;
}

pNode montRoot(char *infixo, char *prefixo, int length)
{

    if (length == 0)
    {
        return NULL;
    }

    int i = 0;
    while (i < length && infixo[i] != prefixo[0])
        i++;

    pNode newNode = malloc(sizeof(Node));

    newNode->data = prefixo[0];
    newNode->l = montRoot(infixo, prefixo + 1, i);
    newNode->r = montRoot(infixo + i + 1, prefixo + i + 1, length - i - 1);

    return newNode;
}

// posfixo
void readEDR(pNode root)
{
    if (root == NULL)
        return;

    readEDR(root->l);
    readEDR(root->r);
    printf("%c", root->data);
}

int main(int argc, char const *argv[])
{
    pNode root = NULL;

    int qntd = 0;
    scanf("%d\n", &qntd);

    for (size_t i = 0; i < qntd; i++)
    {
        int stringLength;
        char infixo[53];
        char prefixo[53];

        scanf("%d %52s %52s", &stringLength, prefixo, infixo);

        root = montRoot(infixo, prefixo, stringLength);

        readEDR(root);
        printf("\n");

        // printf("%d %s %s\n", stringLength, prefixo, infixo);
    }

    return 0;
}
