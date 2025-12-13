#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool readST(FILE *file, int *pSource, int *pTarget)
{
    return fscanf(file, "%d %d %*d\n", pSource, pTarget) != EOF;
}

int main()
{
    char filepath[100];
    scanf("%s", &filepath);

    FILE *file = fopen(filepath, "r");
    fscanf(file, "%*s %*s %*s");

    int s, t;
    while (readST(file, &s, &t))
    {
        // printf("%d %d\n", s, t);
    }

    /* code */
    return 0;
}
