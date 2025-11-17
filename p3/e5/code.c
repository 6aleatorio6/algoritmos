#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct Node
{
    char *word;
    struct Node *next;
} Node;

void insert(Node **head, char word[20])
{
    Node *newNode = malloc(sizeof(Node));
    newNode->word = malloc(sizeof(char) * 20);
    strcpy(newNode->word, word);
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    for (Node *prev = NULL, *tmp = *head; 1; prev = tmp, tmp = tmp->next)
    {
        if (tmp == NULL)
        {
            prev->next = newNode;
            break;
        }

        if (strcmp(word, tmp->word) >= 0)
            continue;

        newNode->next = tmp;

        if (prev != NULL)
        {
            prev->next = newNode;
        }
        else
        {
            *head = newNode;
        }

        break;
    };
}

int main()
{

    int caseLength = 0;
    scanf("%d\n", &caseLength);

    Node **filasPaia = malloc(sizeof(Node *) * caseLength);

    for (int caseI = 1; caseI <= caseLength; caseI++)
    {
        Node *frase = NULL;

        char result[21];
        char space;

        while (scanf("%s", result) && scanf("%c", &space) && space != '\n')
        {
            int isRepetido = 0;
            for (Node *tmp = frase; tmp != NULL; tmp = tmp->next)
            {
                if (!strcmp(result, tmp->word))
                {
                    isRepetido = 1;
                    break;
                }
            }

            if (!isRepetido)
            {
                insert(&frase, result);
            }
        }

        filasPaia[caseI - 1] = frase;
    }

    for (size_t i = 0; i < caseLength; i++)
    {
        for (Node *tmp = filasPaia[i]; tmp != NULL; tmp = tmp->next)
        {
            printf("%s", tmp->word);
            if (tmp->next != NULL)
                printf(" ");
        }
        printf("\n");
    }

    return 0;
}