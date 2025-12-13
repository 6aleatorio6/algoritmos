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
    int index;
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
    newVertice->edgeCount = 0;
    newVertice->index = grafo->vertexCount;

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

FILE *prepareFile()
{
    char filepath[100];
    scanf("%s", filepath);

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

int getTotalAresta(pGrafo grafo)
{
    return grafo->vertexCount;
}

int getTotalVertices(pGrafo grafo)
{
    int count = 0;

    pVertice vertice = grafo->vertices;
    while (vertice != NULL)
    {
        count += vertice->edgeCount;
        vertice = vertice->prox;
    }

    return count / 2;
}

int getGrauMedio(pGrafo grafo)
{
    int count = 0;

    pVertice vertice = grafo->vertices;
    while (vertice != NULL)
    {
        count += vertice->edgeCount;
        vertice = vertice->prox;
    }

    return count / grafo->vertexCount;
}

int getMaiorHub(pGrafo grafo)
{
    int max = 0;

    pVertice vertice = grafo->vertices;
    while (vertice != NULL)
    {

        if (max < vertice->edgeCount)
            max = vertice->edgeCount;

        vertice = vertice->prox;
    }

    return max;
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
    int count = 0;

    pVertice vertice = grafo->vertices;
    while (vertice != NULL)
    {
        pAresta aresta = vertice->arestas;
        while (aresta != NULL)
        {
            printf("DE %d PARA %d\n", vertice->u, aresta->v);
            aresta = aresta->prox;
        }

        count += vertice->edgeCount;
        vertice = vertice->prox;
    }
    printf("qntd de arestas: %d\n", count / 2);
}

typedef struct
{
    int dist;
    int u;
} MenorCaminho;

// todo esse codigo é pensando no céu azul
MenorCaminho *getMenoresCaminhos(pGrafo grafo, int u)
{
    MenorCaminho *menoresCaminhos = calloc(sizeof(MenorCaminho), grafo->vertexCount);

    pVertice *fila = malloc(sizeof(pVertice) * grafo->vertexCount);
    int inicio = 0, fim = 0;

    // origem
    pVertice vertice = findVertice(grafo, u);
    fila[fim++] = vertice;
    menoresCaminhos[vertice->index].dist = 0;
    menoresCaminhos[vertice->index].u = u;

    while (inicio < fim)
    {
        pVertice verticeAtual = fila[inicio++];

        pAresta tmpAresta = verticeAtual->arestas;
        while (tmpAresta != NULL)
        {
            pVertice verticeDaPonta = findVertice(grafo, tmpAresta->v);

            // apenas origem deve ser 0
            bool jaFoiVisitado = menoresCaminhos[verticeDaPonta->index].dist != 0 || verticeDaPonta->u == u;
            if (!jaFoiVisitado)
            {
                fila[fim++] = verticeDaPonta;
                // printf("vertice: %d | dist: %d\n", tmpAresta->v, menoresCaminhos[verticeAtual->index].dist + 1);

                menoresCaminhos[verticeDaPonta->index].dist = menoresCaminhos[verticeAtual->index].dist + 1;
                menoresCaminhos[verticeDaPonta->index].u = tmpAresta->v;
            }

            tmpAresta = tmpAresta->prox;
        }
    }

    return menoresCaminhos;
}

MenorCaminho getExcentricidade(pGrafo grafo, int u)
{
    pVertice vertice = findVertice(grafo, u);
    MenorCaminho maiorCaminho = {-1, -1};

    MenorCaminho *minCaminhos = getMenoresCaminhos(grafo, u);
    int index = 0;
    while (index < grafo->vertexCount)
    {
        if (maiorCaminho.dist < minCaminhos[index].dist)
        {
            maiorCaminho = minCaminhos[index];
        }

        index++;
    }

    return maiorCaminho;
}

int getDiametro(pGrafo grafo)
{
    MenorCaminho excentricidade1 = getExcentricidade(grafo, grafo->vertices->u);
    MenorCaminho excentricidade2 = getExcentricidade(grafo, excentricidade1.u);

    return excentricidade2.dist;
}

int main()
{
    pGrafo grafo = initGrafo();

    int s, t;
    FILE *file = prepareFile();
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

    printf("RESULTADO\n");
    printf("- total de arestas: %d\n", getTotalAresta(grafo));
    printf("- total de vertices: %d\n", getTotalVertices(grafo));
    printf("- grau medio: %d\n", getGrauMedio(grafo));
    printf("- maior hub: %d\n", getMaiorHub(grafo));
    printf("- diametro: %d\n", getDiametro(grafo));

    // debugReadV(grafo, file);
    // debugReadA(grafo, file);

    freeAll(file, grafo);
    return 0;
}
