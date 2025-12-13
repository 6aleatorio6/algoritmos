#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int value;
    No *arestas;
    struct No *prox;
} No;

typedef No *p_No;

p_No add_no(p_No no, int uOrigem)
{
    p_No newNo = malloc(sizeof(No));
    newNo->prox = NULL;
    newNo->arestas = NULL;
    newNo->value = uOrigem;

    if (no == NULL)
        return newNo;

    p_No tmp = no;
    while (tmp->prox != NULL)
        tmp = tmp->prox;

    tmp->prox = newNo;

    return no;
}

typedef struct
{
    p_No adj;
    int n;
} Grafo;

typedef Grafo *p_grafo;

p_grafo init_grafo()
{
    p_grafo grafo = malloc(sizeof(Grafo));
    grafo->n = 0;
    grafo->adj = NULL;
    return grafo;
}

p_No add_vertice(p_grafo grafo, int uOrigem)
{
    p_No tmp = grafo->adj;
    while (tmp != NULL)
    {
        tmp = tmp->prox;
    }

    p_No newVertice = add_no(tmp, uOrigem);
    if (grafo->adj == NULL)
        grafo->adj = newVertice;

    return newVertice;
}

void add_aresta(p_grafo grafo, int uOrigem, int v)
{
    p_No tmp = grafo->adj;
    while (tmp != NULL && tmp->value != uOrigem)
    {
        tmp = tmp->prox;
    }

    if (tmp == NULL)
    {
        tmp = add_vertice(grafo, uOrigem);
    }

    tmp->arestas = add_no(tmp->arestas, v);
}
