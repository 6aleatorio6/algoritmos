#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *fc, *fr;
    char cmd[50], linha[50];
    int achou = 0;
    /* SEU CÓDIGO: abra os dois arquivos (teste NULL), leia cmd, procure, e grave o resultado */


    fc = fopen("comandos.txt","r");
    fr = fopen("resultado.txt","w");

    if(fc == NULL|| fr ==NULL) return 1;

    scanf("%49s", cmd);

    while(fscanf(fc, "%49s", linha) != EOF){
        if(strcmp(linha, cmd) == 0) {

            achou =1;
            break;
        }
    }

    if(achou){
        fprintf(fr,"Comando encontrado.\n");
    } else{
        rewind(fc);

        while(fscanf(fc, "%49s", linha) != EOF){
            fprintf(fr,"%s\n", linha);
        }
    }

    
    fclose(fc);
    fclose(fr);


    return 0;
}
