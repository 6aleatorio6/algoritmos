#include <stdio.h>
#include <stdlib.h>

/* SEU CÓDIGO: declare Data, Horario e Compromisso com typedef */

int main(void) {
    int n, i, d, m, a;
    Compromisso *v;
    scanf("%d", &n);
    v = (Compromisso *) malloc(n * sizeof(Compromisso));
    if (v == NULL) return 1;
    for (i = 0; i < n; i++)
        scanf("%d %d %d %d %d %49[^\n]", &v[i].data.dia, &v[i].data.mes,
              &v[i].data.ano, &v[i].hora.hora, &v[i].hora.minuto, v[i].desc);
    scanf("%d %d %d", &d, &m, &a);
    for (i = 0; i < n; i++) {
        /* SEU CÓDIGO: se a data de v[i] for d/m/a, imprima "HH:MM desc" */
    }
    free(v);
    return 0;
}
