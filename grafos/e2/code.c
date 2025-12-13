#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int value;
    struct No *arestas;
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

p_No find_vertice(p_grafo grafo, int val)
{
    p_No tmp = grafo->adj;
    while (tmp != NULL)
    {
        if (tmp->value == val)
            return tmp;
        tmp = tmp->prox;
    }
    return NULL;
}

p_No add_vertice(p_grafo grafo, int uOrigem)
{
    p_No v = find_vertice(grafo, uOrigem);
    if (v)
        return v;

    grafo->adj = add_no(grafo->adj, uOrigem);
    grafo->n++;
    return find_vertice(grafo, uOrigem);
}

void add_aresta(p_grafo grafo, int uOrigem, int v)
{
    p_No vertU = add_vertice(grafo, uOrigem);
    p_No vertV = add_vertice(grafo, v);

    vertU->arestas = add_no(vertU->arestas, v);
    vertV->arestas = add_no(vertV->arestas, uOrigem);
}

void print_grafo(p_grafo grafo)
{
    if (!grafo)
        return;

    p_No tmpVertice = grafo->adj;

    while (tmpVertice != NULL)
    {
        printf("Vertice: %d\n", tmpVertice->value);

        p_No tmpAresta = tmpVertice->arestas;
        while (tmpAresta != NULL)
        {
            printf("  Aresta para: %d\n", tmpAresta->value);
            tmpAresta = tmpAresta->prox;
        }

        tmpVertice = tmpVertice->prox;
    }
}

void free_lista(p_No lista)
{
    while (lista)
    {
        p_No tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

void free_grafo(p_grafo grafo)
{
    p_No tmp = grafo->adj;
    while (tmp)
    {
        if (tmp->arestas)
            free_lista(tmp->arestas);
        tmp = tmp->prox;
    }
    free_lista(grafo->adj);
    free(grafo);
}

int main()
{
    char filename[200];
    scanf("%199s", filename);

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    fscanf(file, "%*s %*s %*s");

    int u, v, w;
    p_grafo grafo = init_grafo();

    while (fscanf(file, "%d %d %d", &u, &v, &w) == 3)
    {
        add_aresta(grafo, u, v);
    }

    fclose(file);

    print_grafo(grafo);

    free_grafo(grafo);

    return 0;
}
