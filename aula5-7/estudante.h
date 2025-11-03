#ifndef ESTUDANTE_H
#define ESTUDANTE_H

typedef struct
{
    char name[50];
    int age;
} Estudante;

Estudante *incluir_estudante(Estudante *students, int *tam);
void apagar_estudante(Estudante *students, char *name, int *tam);
void listar_estudantes(Estudante *students, int tam);
void salvar_estudantes_arquivo(Estudante *students, int tam, char *nomeArquivo);
Estudante *carregar_estudantes_arquivo(int *tam, char *nomeArquivo);

#endif