#include <stdio.h>
#include <stdlib.h>

void resumo(float *v, int n, float *menor, float *maior, float *media) {
    /* SEU CÓDIGO: percorra v e escreva em *menor, *maior e *media */
}

int main(void) {
    int n, i;
    float *v, mn, mx, md;
    scanf("%d", &n);
    /* SEU CÓDIGO: aloque v com malloc (n floats) e teste NULL */
    for (i = 0; i < n; i++) scanf("%f", &v[i]);
    resumo(v, n, &mn, &mx, &md);
    printf("menor %.2f, maior %.2f, media %.2f\n", mn, mx, md);
    /* SEU CÓDIGO: libere v */
    return 0;
}
