#include <stdio.h>
#include <math.h>

int main(void) {
    double x, termo = 1, soma = 1;       /* termo 0: 1 */
    int k = 1;
    scanf("%lf", &x);
    /* SEU CÓDIGO: enquanto |termo| >= 0.001: calcule o próximo termo a partir do anterior e some */
    printf("e^%.2f = %.3f\n", x, soma);
    return 0;
}
