#include <stdio.h>
#include <stdlib.h>

void resumo(float *v, int n, float *menor, float *maior, float *media) {
    // tinha colocado 1, ao invés de, falhando em vetores com 1 elem
    *menor = *maior =* media = v[0];
    
    float soma = 0;

    for(int i = 0; i < n; i++){
        float elem = v[i];


        if(elem < *menor) *menor = elem;

        if(elem > *maior) *maior = elem;

        soma += elem;
    }

    *media = soma / n;
}

int main(void) {
    int n, i;
    float *v, mn, mx, md;
    scanf("%d", &n);
    /* SEU CÓDIGO: aloque v com malloc (n floats) e teste NULL */

    v = (float*)malloc(n * sizeof(float));

    if(v ==NULL) return 1;

    for (i = 0; i < n; i++) scanf("%f", &v[i]);
    resumo(v, n, &mn, &mx, &md);
    printf("menor %.2f, maior %.2f, media %.2f\n", mn, mx, md);


    free(v);


    return 0;
}
