#include <stdio.h>

int soma(int *v, int n) {
    /* SEU CÓDIGO: caso base: n == 0; senão, *v + soma do resto */
    return 0;
}

int main(void) {
    int n, i, v[100];
    scanf("%d", &n);
    for (i = 0; i < n; i++) scanf("%d", &v[i]);
    printf("%d\n", soma(v, n));
    return 0;
}
