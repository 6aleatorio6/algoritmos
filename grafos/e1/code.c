#include <stdio.h>
#include <stdlib.h>

// beecrowd | 2372
// Reunião
// Por OBI - Olimpíada Brasileira de Informática 2010 BR Brazil

typedef struct
{
    int **adj;
    int n;
} Grafo;

typedef Grafo *p_grafo;

p_grafo criarGrafo(int n)
{
    int i, j;
    p_grafo g = malloc(sizeof(Grafo));
    g->n = n;

    g->adj = malloc(n * sizeof(int *));

    for (size_t i = 0; i < n; i++)
    {
        g->adj[i] = calloc(n, sizeof(int));
    }

    return g;
}

void destroi_grafo(p_grafo g)
{
    int i;

    for (size_t i = 0; i < g->n; i++)
    {
        free(g->adj[i]);
    }

    free(g->adj);
    free(g);
}

void remove_aresta(p_grafo g, int u, int v)
{
    g->adj[u][v] = 0;
    g->adj[v][u] = 0;
}

void insere_aresta(p_grafo g, int u, int v, int w)
{
    g->adj[u][v] = w;
    g->adj[v][u] = w;
}

int tem_aresta(p_grafo g, int u, int v)
{
    return g->adj[u][v];
}

int *dijkstra(Grafo *g, int origem)
{
    int *dist = malloc(sizeof(int) * g->n);
    int *visitados = malloc(sizeof(int) * g->n);

    for (size_t i = 0; i < g->n; i++)
    {
        dist[i] = 9999;
        visitados[i] = 0;
    }

    dist[origem] = 0;

    // percorro todas as arstas da origem
    for (size_t i = 0; i < g->n; i++)
    {

        // encontro a aresta com menor valor
        int u = -1;
        for (size_t j = 0; j < g->n; j++)
        {
            if (!visitados[j] && (u == -1 || dist[j] < dist[u]))
            {
                u = j;
            }
        }

        visitados[u] = 1;

        for (size_t v = 0; v < g->n; v++)
        {
            if (g->adj[u][v] > 0 && !visitados[v])
            {
                int novaDist = dist[u] + g->adj[u][v];

                if (novaDist < dist[v])
                {
                    dist[v] = novaDist;
                }
            }
        }
    }

    return dist;
}

int *gerar_caminhos_minimos(p_grafo grafo, int uOrigem)
{
    // proximos a serem percorridos
    int *fila = malloc(sizeof(int) * grafo->n);
    int inicio = 0;
    int fim = 0;

    // valor da distancia
    int *dist = malloc(sizeof(int) * grafo->n);

    // se já foi visitado (obs: tem que dar -1 )
    int *visitado = malloc(sizeof(int) * grafo->n);

    int *pai = malloc(sizeof(int) * grafo->n);

    for (size_t i = 0; i < grafo->n; i++)
    {
        visitado[i] = 0;
        dist[i] = -1;
        pai[i] = -1;
    }

    // origem
    visitado[uOrigem] = 1;
    dist[uOrigem] = -1;
    fila[fim++] = uOrigem;

    while (inicio < fim)
    {
        int u = fila[inicio++];

        for (size_t v = 0; v < grafo->n; v++)
        {
            if (!grafo->adj[u][v])
                continue;

            int distAtual = dist[u] + grafo->adj[u][v];
            // printf("%d %d\n", dist[v], distAtual);
            if (dist[v] == -1 || dist[v] > distAtual)
            {

                visitado[v] = 1;
                dist[v] = distAtual;
                pai[v] = u;
                fila[fim++] = v;
            }
        }
    }

    free(fila);
    free(visitado);

    return dist;
}

int excentricidade(p_grafo grafo, int uOrigem)
{
    int *caminhosMinimos = dijkstra(grafo, uOrigem);
    int maiorCaminhoMinimo = -1;

    for (size_t i = 0; i < grafo->n; i++)
    {
        int dist = caminhosMinimos[i];
        if (maiorCaminhoMinimo < dist)
            maiorCaminhoMinimo = dist;
    }

    return maiorCaminhoMinimo;
}

int calcCentro(p_grafo grafo)
{

    int menorExcentricidade = -1;

    int index = 0;
    while (index < grafo->n)
    {
        int excenAtual = excentricidade(grafo, index);
        if (menorExcentricidade == -1 || excenAtual < menorExcentricidade)
        {
            menorExcentricidade = excenAtual;
        }
        index++;
    }

    return menorExcentricidade;
}

int main()
{
    int verticesLength = 0;
    int arestasParaSeremLidas = 0;

    scanf("%d %d", &verticesLength, &arestasParaSeremLidas);

    p_grafo grafo = criarGrafo(verticesLength);

    int u, v, w;
    while (arestasParaSeremLidas > 0)
    {
        scanf("%d %d %d", &u, &v, &w);
        insere_aresta(grafo, u, v, w);
        arestasParaSeremLidas--;
    }

    printf("%d\n", calcCentro(grafo));

    return 0;
}
