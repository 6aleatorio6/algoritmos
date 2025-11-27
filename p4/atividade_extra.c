#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int SIZE_VETOR = 10 * 1000;

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

int *createVetor()
{
    int *vetor = malloc(sizeof(int) * SIZE_VETOR);

    for (size_t i = 0, value; i < SIZE_VETOR; i++)
    {
        vetor[i] = rand() % SIZE_VETOR;
    }

    return vetor;
}

NodePoint createArvore()
{
    NodePoint root = NULL;

    for (size_t i = 0, value; i < SIZE_VETOR; i++)
    {
        root = insert(root, rand() % SIZE_VETOR);
    }

    return root;
}

int *ordenarVetor(int *vetor)
{
    int *vetorCpy = malloc(sizeof(int) * SIZE_VETOR);
    memcpy(vetorCpy, vetor, sizeof(int) * SIZE_VETOR);

    // por ser um vetor não muito grande
    for (size_t j = 0; j < SIZE_VETOR; j++)
    {
        for (size_t i = 0; i < SIZE_VETOR; i++)

            if (vetorCpy[i] > vetorCpy[i + 1])
            {
                int aux = vetorCpy[i];
                vetorCpy[i] = vetorCpy[i + 1];

                vetorCpy[i + 1] = aux;
            }
    }

    return vetorCpy;
}

int buscarArvore(NodePoint root, int key)
{
    if (root == NULL)
        return 0;
    if (root->key == key)
        return 1;
    else if (key < root->key)
        return buscarArvore(root->left, key);
    else
        return buscarArvore(root->right, key);
}

int altura(NodePoint root)
{
    if (root == NULL)
        return 0;
    int alturaEsquerda = altura(root->left);
    int alturaDireita = altura(root->right);
    return 1 + (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita);
}

void printTempo(clock_t inicio, clock_t fim, char *msg)
{
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("%s: %.8f segundos\n", msg, tempo);
}

int main()
{
    clock_t init, end;

    init = clock();
    int *vetor = createVetor();
    end = clock();
    printTempo(init, end, "Criar vetor");

    init = clock();
    NodePoint root = createArvore();
    end = clock();
    printTempo(init, end, "Criar arvore");

    init = clock();
    buscarArvore(root, 50);
    end = clock();
    printTempo(init, end, "Buscar 50 na arvore");

    init = clock();
    buscarArvore(root, 5000);
    end = clock();
    printTempo(init, end, "Buscar 5000 na arvore");

    printf("altura esquerda: %d\n", altura(root->left) + 1);
    printf("altura direita: %d\n", altura(root->right) + 1);

    return 0;
}
