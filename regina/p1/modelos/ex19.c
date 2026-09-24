#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    int info;
    struct no *prox;
} No;

No *push(No *pilha, int x) {
    No *novo = (No *) malloc(sizeof(No));
    novo->info = x;
    novo->prox = pilha;
    return novo;
}

void g(No *p) {                       /* imprime do fundo ao topo */
    if (p == NULL) return;
    g(p->prox);
    printf("%d ", p->info);
}

void libera_rec(No *p) {
    if (p == NULL) return;
    libera_rec(p->prox);
    free(p);
}

void incrementa(No *p) {
    /* SEU CÓDIGO: 0 vira 1 e para; 1 vira 0 e segue para p->prox (ou cria um nó 1 no fim) */
}

int main(void) {
    No *pilha = NULL;
    char s[65];
    int i;
    scanf("%64s", s);                        /* ex.: 1011 */
    for (i = 0; s[i] != '\0'; i++)
        pilha = push(pilha, s[i] - '0');    /* '1' vira 1 */
    incrementa(pilha);
    g(pilha);
    printf("\n");
    libera_rec(pilha);
    return 0;
}
