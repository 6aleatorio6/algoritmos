#include <stdio.h>
#include <stdlib.h>

/* remove os repetidos mantendo a 1ª ocorrência; devolve quantos removeu */
int remove_dup(int v[], int *n) {
    /* SEU CÓDIGO: use um índice k para o fim da parte sem repetidos; no fim, *n = k */
    return 0;
}

int main(void) {
    int n, i, *v, *tmp;
    scanf("%d", &n);
    v = (int *) malloc(n * sizeof(int));
    if (v == NULL) return 1;
    for (i = 0; i < n; i++) scanf("%d", &v[i]);
    remove_dup(v, &n);
    /* SEU CÓDIGO: encolha v para n inteiros com realloc (use tmp) */
    for (i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
    free(v);
    return 0;
}
