#include <stdio.h>

void troca(int *a, int *b) {
    /* SEU CÓDIGO: troque os valores apontados por a e b */
}

int main(void) {
    int x, y;
    scanf("%d %d", &x, &y);
    troca(&x, &y);
    printf("%d %d\n", x, y);
    return 0;
}
