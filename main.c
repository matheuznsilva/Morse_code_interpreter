#include "funcoes.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Uso: %s <dicionario>\n", argv[0]);
        return 1;
    }

    ArvBin *AB = cria_ArvBin();
    carregar_Alfabeto(AB, argv[1]);

    menu(AB);
    libera_ArvBin(AB);
    return 0;
}