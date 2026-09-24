#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    int info;
    struct no *prox;
} No;

No *push(No *pilha, int x) {
    /* SEU CÓDIGO: novo nó apontando para o topo antigo; devolva o novo topo */
    return pilha;
}

No *pop(No *pilha, int *x) {
    /* SEU CÓDIGO: guarde o topo, leia o valor, avance e só então dê free */
    return pilha;
}

void imprime(No *pilha) {
    No *p;
    for (p = pilha; p != NULL; p = p->prox)
        printf("%d ", p->info);
}

No *libera(No *pilha) {
    /* SEU CÓDIGO: libere nó por nó, avançando antes de cada free */
    return NULL;
}

int main(void) {
    No *pilha = NULL;
    int x;
    while (scanf("%d", &x) == 1)
        pilha = push(pilha, x);
    imprime(pilha);
    printf("\n");
    pilha = pop(pilha, &x);
    printf("pop: %d\n", x);
    imprime(pilha);
    printf("\n");
    pilha = libera(pilha);
    return 0;
}
