#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    int info;
    struct no *prox;
} No;

typedef struct {
    No *ini, *fim;           /* fila vazia: ini = fim = NULL */
} Fila;

void insere(Fila *f, int x) {
    /* SEU CÓDIGO: novo nó com prox NULL; se a fila estava vazia ele também é o ini; senão engata atrás do fim */
}

int retira(Fila *f, int *x) {
    /* SEU CÓDIGO: tire do ini; se a fila esvaziar, fim = NULL */
    return -1;
}

int main(void) {
    Fila f = {NULL, NULL};
    No *p;
    char cmd;
    int x;
    while (scanf(" %c", &cmd) == 1) {
        if (cmd == 'I') {
            scanf("%d", &x);
            insere(&f, x);
        } else if (cmd == 'R') {
            if (retira(&f, &x) == 0) printf("%d\n", x);
            else printf("fila vazia\n");
        }
    }
    printf("fila:");
    for (p = f.ini; p != NULL; p = p->prox) printf(" %d", p->info);
    printf("\n");
    while (retira(&f, &x) == 0);          /* libera o que sobrou */
    return 0;
}
