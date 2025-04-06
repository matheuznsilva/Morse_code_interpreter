#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef ArvoreBinaria_h
#define ArvoreBinaria_h

#define BUFFER 10
#define MAX_LINE 100
#define MAX_MSG 1000
#define MAX_CODE 6

struct NO{
    char caracter;
    struct NO *ponto;
    struct NO *traco;
};

typedef struct NO* ArvBin;

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin* raiz, char caracter, const char* code);
int remove_ArvBin(ArvBin *raiz, int valor);
//int estaVazia_ArvBin(ArvBin *raiz);
//int altura_ArvBin(ArvBin *raiz);
//int totalNO_ArvBin(ArvBin *raiz);
//int consulta_ArvBin(ArvBin *raiz, int valor);

void preOrdem_ArvBin(ArvBin *raiz);
//void emOrdem_ArvBin(ArvBin *raiz);
//void posOrdem_ArvBin(ArvBin *raiz);

char decodifica(ArvBin *raiz, const char* code);
int codifica(ArvBin *raiz, char caracter, char* buffer, int index);

#endif