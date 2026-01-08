#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    char data;
    struct Node *next;
} Node;

typedef Node *pNode;

pNode addStart(pNode head, char newValue)
{
    pNode newNode = malloc(sizeof(newValue));

    newNode->data = newValue;
    newNode->next = head;

    return newNode;
}

pNode removeStart(pNode head)
{
    pNode newHead = head->next;

    free(head);

    return newHead;
}

void freeStack(pNode head)
{
    pNode tmp = head;
    pNode tmp2;
    while (tmp != NULL)
    {
        tmp2 = tmp;

        tmp = tmp->next;

        free(tmp2);
    }
}

int main(int argc, char const *argv[])
{
    pNode head = NULL;

    // head = addStart(head, '1');
    // head = addStart(head, '2');
    // head = removeStart(head);
    // head = removeStart(head);

    // printf("%c", head->data);

    char buffer[1001];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        int isInvalid = 0;

        for (size_t i = 0; buffer[i] != '\0'; i++)
        {

            if (buffer[i] == '(')
            {
                head = addStart(head, '(');
            }

            if (buffer[i] == ')')
            {
                if (head == NULL)
                {
                    isInvalid = 1;
                    continue;
                }

                head = removeStart(head);
            }
        }

        printf(head == NULL && !isInvalid ? "correct" : "incorrect");
        printf("\n");

        freeStack(head);
        head = NULL;
    }

    return 0;
}