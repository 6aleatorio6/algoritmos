#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int s;     // inicio da fila
    int t;     // lugar do proximo item
    int N;     // capacidade
    int *data; // vetor
} Fila;

void init(Fila *fila, int tam)
{

    fila->s = 0;
    fila->t = 0;
    fila->N = tam;
    fila->data = malloc(sizeof(int) * tam);
};

int isFull(Fila *fila, int t)
{
    return (t + 1) % fila->N == fila->s;
}

// ------

void INCREASE(Fila *fila, int inc)
{

    fila->N += inc;
    fila->data = realloc(fila->data, sizeof(int) * fila->N);

    if (fila->s <= fila->t)
    {
        return;
    }

    if (fila->N - fila->s > fila->t)
    {
        // esquerda
        for (int i = 0; i < fila->t; i++)
        {
            fila->data[(fila->N + i - inc) % fila->N] = fila->data[i];
        }
        fila->t = (fila->t - inc + fila->N) % fila->N;
    }
    else
    {
        // direita
        for (int i = (fila->N - inc) - 1; i >= fila->s; i--)
        {
            fila->data[i + inc] = fila->data[i];
        }
        fila->s += inc;
    }
}

void REMOVE(Fila *fila)
{
    if (fila->t == fila->s)
    {
        printf("CLEAR\n");

        return;
    }

    printf("%d\n", fila->data[fila->s]);

    if (++fila->s == fila->N)
    {
        fila->s = 0;
    }
}

void ADD(Fila *fila, int newValue)
{
    if (isFull(fila, fila->t))
    {
        if (++fila->s == fila->N)
        {
            fila->s = 0;
        }
    }

    fila->data[(fila->t)] = newValue;
    fila->t = (fila->t + 1) % fila->N;
}

void PRINT(Fila *fila)
{

    for (int i = 0; i < fila->N; i++)
    {

        // fila->s > fila->t ? (i >= fila->t && i < fila->s) : (i < fila->s && i >= fila->t)
        if (fila->s <= fila->t ? (i >= fila->s && i < fila->t) : (i < fila->t || i >= fila->s))
        {
            printf("%d", fila->data[i]);
        }
        else
        {
            printf("-");
        }

        if (i != fila->N - 1)
        {
            printf(" ");
        };
    }

    printf("\n");
}

void LIST(Fila *fila)
{
    if (fila->t == fila->s)
    {
        printf("EMPTY\n");

        return;
    }

    for (int i = fila->s; i != fila->t; i = (i + 1) % fila->N)
    {

        printf("%d", fila->data[i % fila->N]);

        if ((i + 1) % fila->N != fila->t)
        {
            printf(" ");
        };
    }
    printf("\n");
}

int main()
{

    Fila fila;

    int N;
    scanf("%d", &N);

    init(&fila, N);

    while (1)
    {
        char command[30];
        scanf("%s", command);

        if (strcmp(command, "END") == 0)
        {
            return 0;
        }
        else if (strcmp(command, "LIST") == 0)
        {
            LIST(&fila);
        }
        else if (strcmp(command, "PRINT") == 0)
        {
            PRINT(&fila);
        }
        else if (strcmp(command, "REMOVE") == 0)
        {
            REMOVE(&fila);
        }
        else if (strcmp(command, "ADD") == 0)
        {
            int value;
            scanf(" %d", &value);

            ADD(&fila, value);
        }
        else if (strcmp(command, "INCREASE") == 0)
        {
            int value;
            scanf(" %d", &value);

            INCREASE(&fila, value);
        };
    };

    // init(&fila, 10);

    // teste init ---
    // printf("s: %d, t: %d, N: %d\n", fila.s, fila.t, fila.N);

    // teste insert ---
    // insert(&fila, 2);
    // insert(&fila, 6);
    // printf("s: %d, t: %d, N: %d | elem1: %d elem2: %d  |\n", fila.s, fila.t, fila.N, fila.data[fila.t - 2], fila.data[fila.t - 1]);

    // printf("s: %d, t: %d, N: %d\n", fila.s, fila.t, fila.N);

    // insert(&fila, 2);
    // insert(&fila, 6);
    // insert(&fila, 2);
    // insert(&fila, 6);

    // ADD(&fila, 10);
    // ADD(&fila, 15);
    // ADD(&fila, 14);
    // //
    // PRINT(&fila);
    // printf("\n");
    // LIST(&fila);
}