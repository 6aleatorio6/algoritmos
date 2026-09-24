#include <stdio.h>

#define MAX 100
typedef struct { int vet[MAX]; int topo; } TPilha;

int push(TPilha *p, int x) {
    /* SEU CÓDIGO: teste cheia; suba o topo e grave */
    return 0;
}

int pop(TPilha *p, int *x) {
    /* SEU CÓDIGO: teste vazia; leia e desça o topo */
    return 0;
}

int main(void) {
    TPilha p;
    char cmd;
    int x;
    p.topo = -1;
    while (scanf(" %c", &cmd) == 1) {
        if (cmd == 'P') {
            scanf("%d", &x);
            if (push(&p, x) != 0) printf("overflow\n");
        } else if (cmd == 'R') {
            if (pop(&p, &x) == 0) printf("%d\n", x);
            else printf("underflow\n");
        }
    }
    return 0;
}
