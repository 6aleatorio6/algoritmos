#include <stdio.h>
#include <math.h>

int main()
{
    int x = -1;
    int y = -1;
    int count = 0;

    scanf("%d %d", &x, &y);

    if (2 > x || x >= y || y > 10000000)
    {
        printf("valor invalido\n");
        return 1;
    }

    int i = 0;

    while (1)
    {
        i++;

        // calculando fatorial de i
        long fatorialI = 1;
        for (int j = 1; j <= i; j++)
        {
            fatorialI *= j;
        }

        if (fatorialI > y)
        {
            break;
        }

        if (fatorialI >= x)
        {
            count++;
        }
    }

    // forma mais eficiente
    // int i = 0;
    // long fatorialI = 1;
    // while (1)
    // {
    //     i++;

    //     fatorialI *= i;

    //     if (fatorialI > y)
    //         break;

    //     if (fatorialI >= x)
    //         count++;
    // }

    printf("\n%d\n", count);
}