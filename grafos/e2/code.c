#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Aresta
{
    struct Aresta *prox;
    int v;
} Aresta;
typedef Aresta *pAresta;

typedef struct Vertice
{
    struct Vertice *prox;
    Aresta *arestas;
    int edgeCount;
    int u;
} Vertice;
typedef Vertice *pVertice;

typedef struct Grafo
{
    pVertice vertices;
    int vertexCount;
} Grafo;
typedef Grafo *pGrafo;

pGrafo initGrafo()
{
    pGrafo grafo = malloc(sizeof(Grafo));
    grafo->vertexCount = 0;
    grafo->vertices = NULL;
    return grafo;
}

pVertice addVertice(pGrafo grafo, int u)
{
    pVertice newVertice = malloc(sizeof(Vertice));
    newVertice->u = u;
    newVertice->prox = grafo->vertices;
    newVertice->arestas = NULL;

    grafo->vertexCount++;
    grafo->vertices = newVertice;

    return newVertice;
}

void addAresta(pVertice vertice, int v)
{
    pAresta newAresta = malloc(sizeof(Aresta));
    newAresta->prox = vertice->arestas;
    newAresta->v = v;

    vertice->arestas = newAresta;
    vertice->edgeCount++;
}

pVertice findVertice(pGrafo grafo, int u)
{
    pVertice tmp = grafo->vertices;
    while (tmp != NULL && tmp->u != u)
    {
        tmp = tmp->prox;
    }

    return tmp;
}

pAresta findAresta(pVertice vertice, int v)
{
    pAresta tmp = vertice->arestas;
    while (tmp != NULL && tmp->v != v)
    {
        tmp = tmp->prox;
    }

    return tmp;
}

FILE *getFile()
{
    char filepath[100];
    scanf("%s", &filepath);

    FILE *file = fopen(filepath, "r");
    fscanf(file, "%*s %*s %*s");

    return file;
}

bool readST(FILE *file, int *pSource, int *pTarget)
{
    return fscanf(file, "%d %d %*d\n", pSource, pTarget) != EOF;
}

void freeAll(FILE *file, pGrafo grafo)
{
    fclose(file);

    while (grafo->vertices != NULL)
    {
        pVertice tmpVertice = grafo->vertices;

        while (tmpVertice->arestas != NULL)
        {
            pAresta tmpAresta = tmpVertice->arestas;
            tmpVertice->arestas = tmpAresta->prox;

            free(tmpAresta);
        }

        grafo->vertices = tmpVertice->prox;
        free(tmpVertice);
    }

    free(grafo);
}

void debugReadV(pGrafo grafo, FILE *file)
{
    pVertice tmp = grafo->vertices;
    while (tmp != NULL)
    {
        printf("vertice: %d\n", tmp->u);
        tmp = tmp->prox;
    }
    printf("qntd de vertices: %d\n", grafo->vertexCount);
}

void debugReadA(pGrafo grafo, FILE *file)
{
    pVertice vertice = grafo->vertices;
    while (vertice != NULL)
    {
        pAresta aresta = vertice->arestas;
        while (aresta != NULL)
        {
            printf("DE %d PARA %d\n", vertice->u, aresta->v);
            aresta = aresta->prox;
        }

        vertice = vertice->prox;
    }
}

int main()
{
    pGrafo grafo = initGrafo();

    int s, t;
    FILE *file = getFile();
    while (readST(file, &s, &t))
    {
        // printf("read: %d %d\n", s, t);

        pVertice verticeS = findVertice(grafo, s);

        if (!verticeS)
            verticeS = addVertice(grafo, s);

        addAresta(verticeS, t);

        //
        pVertice verticeT = findVertice(grafo, t);

        if (!verticeT)
            verticeT = addVertice(grafo, t);

        addAresta(verticeT, s);
    }

    debugReadV(grafo, file);
    debugReadA(grafo, file);

    freeAll(file, grafo);
    return 0;
}
