#include <stdio.h>
#include <stdlib.h>

/* remove os repetidos mantendo a 1ª ocorrência; devolve quantos removeu */
int remove_dup(int v[], int *n) {
    /* SEU CÓDIGO: use um índice k para o fim da parte sem repetidos; no fim, *n = k */


    int k = 0;
    for(int i = 0; i < *n; i++){
        int isRepetido = 0;
        for(int j =0; j < k; j++){
            if(v[j] != v[i]) continue;
            
            isRepetido = 1;

        }

        if(isRepetido) continue;
        v[k++] = v[i];
    }
    int removido = *n-k;
    *n = k;
    return removido;
}

int main(void) {
    int n, i, *v, *tmp;
    scanf("%d", &n);
    v = (int *) malloc(n * sizeof(int));
    if (v == NULL) return 1;
    for (i = 0; i < n; i++) scanf("%d", &v[i]);
    remove_dup(v, &n);
    /* SEU CÓDIGO: encolha v para n inteiros com realloc (use tmp) */

    v = (int*) realloc(v,n * sizeof(int));

    for (i = 0; i < n; i++) printf("%d ", v[i]);
    printf("\n");
    free(v);
    return 0;
}
