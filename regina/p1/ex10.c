#include <stdio.h>

int main(void) {
    FILE *f;
    int c, linhas = 0, vezes = 0;
    char alvo;
    scanf(" %c", &alvo);
    /* SEU CÓDIGO: fopen("texto.txt", "r") e teste NULL; leia com fgetc até EOF contando; fclose */

    f = fopen("texto.txt", "r");
    if(f==NULL) return 1;

    while((c = fgetc(f) )  != EOF){
        if(c == '\n') linhas++;
        if(c == alvo) vezes++;
    }

    fclose(f);


    printf("%d linhas; '%c' aparece %d vezes\n", linhas, alvo, vezes);
    return 0;
}
