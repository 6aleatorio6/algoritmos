#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int info;
    struct no *prox;
} No;

No *novo_no(int v, No *prox) {
    /* SEU CÓDIGO: aloque um nó, preencha info e prox e devolva-o */
    return NULL;
}

int main(void) {
    No *lista = NULL, *p, *aux;
    int x;
    while (scanf("%d", &x) == 1)
        lista = novo_no(x, lista);      /* cada novo entra no início */
    /* SEU CÓDIGO: percorra a lista do início ao fim imprimindo os valores */
    printf("\n");
    while (lista != NULL) {             /* libera */
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
    return 0;
}
