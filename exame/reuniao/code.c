#include <stdio.h>
#include <stdlib.h>

typedef struct Arestas
{
    struct Arestas *prox;
    int value;
    int weigth;
} Arestas;
typedef Arestas *pAresta;

typedef struct Vertices
{
    int value;
    struct Vertices *prox;
    pAresta arestas;
} Vertices;
typedef Vertices *pVertices;

typedef struct Grafo
{
    pVertices vertices;
} Grafo;
typedef Grafo *pGrafo;

pGrafo initGrafo()
{
    pGrafo grafo = malloc(sizeof(Grafo));

    grafo->vertices = NULL;

    return grafo;
}

void addVertice(pGrafo grafo, int value)
{
    pVertices newVertice = malloc(sizeof(Vertices));
    newVertice->value = value;

    newVertice->prox = grafo->vertices;
    grafo->vertices = newVertice;

    newVertice->arestas = NULL;
}

pVertices searchVertice(pGrafo grafo, int value)
{
    pVertices tmp = grafo->vertices;

    while (tmp != NULL && tmp->value != value)
    {
        tmp = tmp->prox;
    }

    return tmp;
}

void addAresta(pGrafo grafo, int u, int v, int w)
{
    pVertices vert = searchVertice(grafo, u);

    pAresta newAresta = malloc(sizeof(Arestas));
    newAresta->prox = vert->arestas;
    vert->arestas = newAresta;

    newAresta->value = v;
    newAresta->weigth = w;
}

int main()
{

    int verticesLength = 0;
    int arestasParaSeremLidas = 0;

    scanf("%d %d", &verticesLength, &arestasParaSeremLidas);

    pGrafo grafo = initGrafo();

    for (size_t i = 0; i < verticesLength; i++)
    {
        addVertice(grafo, i);
    }

    int u, v, w;
    while (arestasParaSeremLidas > 0)
    {
        scanf("%d %d %d", &u, &v, &w);
        addAresta(grafo, u, v, w);
        addAresta(grafo, v, u, w);
        arestasParaSeremLidas--;
    }

    return 0;
}
