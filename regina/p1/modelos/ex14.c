#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
typedef struct { int vet[MAX]; int topo; } TPilha;   /* topo = -1: vazia */

int push(TPilha *p, int x) {
    if (p->topo == MAX - 1) return -1;   /* overflow */
    p->topo++;
    p->vet[p->topo] = x;
    return 0;
}

int pop(TPilha *p, int *x) {
    if (p->topo == -1) return -1;        /* underflow */
    *x = p->vet[p->topo];
    p->topo--;
    return 0;
}

int main(void) {
    TPilha p;
    int n, bit;
    p.topo = -1;
    scanf("%d", &n);
    /* SEU CÓDIGO: empilhe os restos de n / 2 até n chegar a 0 (cuidado com n = 0); depois desempilhe imprimindo */
    printf("\n");
    return 0;
}
