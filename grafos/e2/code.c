#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// beecrowd | 1923
// Rerisson e o Churrasco
// Por Gustavo Ribeiro, IFPB - Campina Grande BR Brazil

typedef struct StringArray
{
    char **items;
    int length;
} StringArray;
typedef StringArray *pStringArray;

typedef struct Vertice
{
    struct Vertice *prox;
    int arestasCount;
    char **arestas;
    char *name;
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

pVertice addVertice(pGrafo grafo, int maxArestas, char *name)
{
    pVertice newVertice = malloc(sizeof(Vertice));
    newVertice->name = malloc(sizeof(char) * 21);
    strcpy(newVertice->name, name);

    newVertice->prox = grafo->vertices;
    newVertice->index = grafo->vertexCount;

    newVertice->arestas = malloc(sizeof(char *) * maxArestas);
    newVertice->arestasCount = 0;

    grafo->vertexCount++;
    grafo->vertices = newVertice;

    return newVertice;
}

void addAresta(pVertice vertice, char *name)
{
    char *nameA = malloc(sizeof(char) * 21);
    strcpy(nameA, name);
    vertice->arestas[vertice->arestasCount++] = nameA;
}

pVertice findVertice(pGrafo grafo, char *name)
{
    pVertice tmp = grafo->vertices;
    while (tmp != NULL && strcmp(name, tmp->name) != 0)
    {
        tmp = tmp->prox;
    }

    return tmp;
}

typedef struct
{
    int dist;
    char *name;
} MenorCaminho;

MenorCaminho *getMenoresCaminhos(pGrafo grafo, char *name)
{
    MenorCaminho *menoresCaminhos = calloc(sizeof(MenorCaminho), grafo->vertexCount);

    pVertice *fila = malloc(sizeof(pVertice) * grafo->vertexCount);
    int inicio = 0, fim = 0;

    // origem
    pVertice vertice = findVertice(grafo, name);
    fila[fim++] = vertice;
    menoresCaminhos[vertice->index].dist = 0;
    menoresCaminhos[vertice->index].name = name;

    while (inicio < fim)
    {
        pVertice verticeAtual = fila[inicio++];

        for (size_t i = 0; i < verticeAtual->arestasCount; i++)
        {
            pVertice verticeDaPonta = findVertice(grafo, verticeAtual->arestas[i]);

            bool jaFoiVisitado = menoresCaminhos[verticeDaPonta->index].dist != 0 || strcmp(name, verticeDaPonta->name) == 0;
            if (!jaFoiVisitado)
            {
                fila[fim++] = verticeDaPonta;
                // printf("vertice: %d | dist: %d\n", tmpAresta->v, menoresCaminhos[verticeAtual->index].dist + 1);

                menoresCaminhos[verticeDaPonta->index].dist = menoresCaminhos[verticeAtual->index].dist + 1;
                menoresCaminhos[verticeDaPonta->index].name = verticeDaPonta->name;
            }
        }
    }

    return menoresCaminhos;
}

StringArray *filterByDist(pGrafo grafo, int maxDist)
{

    MenorCaminho *menoresCaminhos = getMenoresCaminhos(grafo, "Rerisson");

    StringArray *convidados = malloc(sizeof(StringArray));
    convidados->items = malloc(sizeof(char *) * grafo->vertexCount);
    convidados->length = 0;

    for (size_t i = 0; i < grafo->vertexCount; i++)
    {
        MenorCaminho menorCaminho = menoresCaminhos[i];

        if (menorCaminho.dist <= maxDist && menorCaminho.dist != 0)
        {
            int index = convidados->length++;
            convidados->items[index] = menorCaminho.name;
        }
    }

    // totalmente ineficiente

    for (size_t i = 0; i < convidados->length; i++)
    {
        int indexMenor = i;

        for (size_t j = i + 1; j < convidados->length; j++)
        {

            if (strcmp(convidados->items[j], convidados->items[i]) < 0)
            {
                indexMenor = j;
            }
        }

        char *swapString = convidados->items[i];
        convidados->items[i] = convidados->items[indexMenor];
        convidados->items[indexMenor] = swapString;
    }

    return convidados;
}

int main()
{
    int distMax, maxArestas;
    scanf("%d %d", &maxArestas, &distMax);

    pGrafo grafo = initGrafo();

    char uName[21], vName[21];
    while (scanf("%20s %20s", uName, vName) != EOF)
    {

        pVertice verticeS = findVertice(grafo, uName);

        if (!verticeS)
            verticeS = addVertice(grafo, maxArestas, uName);

        addAresta(verticeS, vName);

        //

        pVertice verticeT = findVertice(grafo, vName);

        if (!verticeT)
            verticeT = addVertice(grafo, maxArestas, vName);

        addAresta(verticeT, uName);
    }

    StringArray *convidados = filterByDist(grafo, distMax);

    printf("%d\n", convidados->length);
    for (size_t i = 0; i < convidados->length; i++)
    {
        printf("%s\n", convidados->items[i]);
    }

    /* code */
    return 0;
}
