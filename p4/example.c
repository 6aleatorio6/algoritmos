#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definindo a estrutura da árvore binária de busca
typedef struct No
{
    int chave;
    struct No *esquerda, *direita;
} No;

// Protótipo da função auxiliar necessária para a remoção
No *encontrarMinimo(No *raiz);

No *novoNo(int item)
{
    No *temp = (No *)malloc(sizeof(No));
    temp->chave = item;
    temp->esquerda = temp->direita = NULL;
    return temp;
}

No *inserir(No *no, int chave)
{
    if (no == NULL)
        return novoNo(chave);

    if (chave < no->chave)
        no->esquerda = inserir(no->esquerda, chave);
    else if (chave > no->chave) // Evita duplicatas na BST padrão
        no->direita = inserir(no->direita, chave);

    return no;
}

// Percursos

// Pré-Ordem (Raiz -> Esquerda -> Direita)
void preOrdem(No *raiz)
{
    if (raiz != NULL)
    {
        printf("%d ", raiz->chave);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

// Em-Ordem (Esquerda -> Raiz -> Direita)
void emOrdem(No *raiz)
{
    if (raiz != NULL)
    {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->chave);
        emOrdem(raiz->direita);
    }
}

// Pós-Ordem (Esquerda -> Direita -> Raiz)
void posOrdem(No *raiz)
{
    if (raiz != NULL)
    {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d ", raiz->chave);
    }
}

// Em Largura (Por nível)
// Implementação usando uma Fila simples com array dinâmico
void emLargura(No *raiz)
{
    if (raiz == NULL)
        return;

    // Criando uma fila de ponteiros para Nós
    // Tamanho máximo estimado para o exemplo
    int capacidade = 2000;
    No **fila = (No **)malloc(sizeof(No *) * capacidade);
    int inicio = 0;
    int fim = 0;

    // Enfileira a raiz
    fila[fim++] = raiz;

    while (inicio < fim)
    {
        // Desenfileira
        No *atual = fila[inicio++];

        printf("%d ", atual->chave);

        // Enfileira os filhos se existirem
        if (atual->esquerda != NULL)
        {
            fila[fim++] = atual->esquerda;
        }
        if (atual->direita != NULL)
        {
            fila[fim++] = atual->direita;
        }
    }

    free(fila);
}

int altura(No *raiz)
{
    if (raiz == NULL)
        return 0;
    int alturaEsquerda = altura(raiz->esquerda);
    int alturaDireita = altura(raiz->direita);
    return 1 + (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita);
}

No *encontrarMinimo(No *raiz)
{
    while (raiz->esquerda != NULL)
    {
        raiz = raiz->esquerda;
    }
    return raiz;
}

// Função para remover um nó e rearranjar a árvore
No *removeNo(No *raiz, int chave)
{
    // Caso base
    if (raiz == NULL)
        return raiz;

    // Navegar até encontrar o elemento
    if (chave < raiz->chave)
    {
        raiz->esquerda = removeNo(raiz->esquerda, chave);
    }
    else if (chave > raiz->chave)
    {
        raiz->direita = removeNo(raiz->direita, chave);
    }
    else
    {
        // Nó encontrado

        // Caso 1 e 2: Nó com um filho ou nenhum
        if (raiz->esquerda == NULL)
        {
            No *temp = raiz->direita;
            free(raiz);
            return temp;
        }
        else if (raiz->direita == NULL)
        {
            No *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Caso 3: Nó com dois filhos
        No *temp = encontrarMinimo(raiz->direita);            // Sucessor
        raiz->chave = temp->chave;                            // Copia o valor
        raiz->direita = removeNo(raiz->direita, temp->chave); // Remove o sucessor
    }
    return raiz;
}

int buscarArvore(No *raiz, int chave)
{
    if (raiz == NULL)
        return 0;
    if (raiz->chave == chave)
        return 1;
    else if (chave < raiz->chave)
        return buscarArvore(raiz->esquerda, chave);
    else
        return buscarArvore(raiz->direita, chave);
}

int main()
{
    No *raiz = NULL;
    int N, i, valor;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    printf("Digite a quantidade de elementos (N) para a arvore com N <=100: ");
    scanf("%d", &N);

    printf("\nGerando %d numeros aleatorios e inserindo na arvore...\n", N);
    for (i = 0; i < N; i++)
    {
        // Gera número entre 0 e 99
        valor = rand() % 1000;
        printf("%d ", valor); // Mostra o valor gerado para conferência
        raiz = inserir(raiz, valor);
    }
    printf("\n\n---------------- RESULTADOS ----------------\n");

    printf("Altura da arvore: %d\n", altura(raiz));

    printf("\n1. Impressao Em-Ordem (Ordenado):\n");
    emOrdem(raiz);
    printf("\n");

    printf("\n2. Impressao Pre-Ordem:\n");
    preOrdem(raiz);
    printf("\n");

    printf("\n3. Impressao Pos-Ordem:\n");
    posOrdem(raiz);
    printf("\n");

    printf("\n4. Impressao em Largura (Por Nivel):\n");
    emLargura(raiz);
    printf("\n");

    return 0;
}