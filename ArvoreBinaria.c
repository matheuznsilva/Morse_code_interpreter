#include "ArvoreBinaria.h" //inclui os Prototipos

ArvBin* cria_ArvBin(){
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if(raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}

struct NO* cria_NO(char caracter){
    struct NO* novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo != NULL){
        novo->caracter = caracter;
        novo->ponto = NULL;
        novo->traco = NULL;
    }
    return novo;
};

void libera_NO(struct NO* no){
    if(no == NULL){
        return;
    }
    libera_NO(no->ponto);
    libera_NO(no->traco);
    free(no);
}

void libera_ArvBin(ArvBin* raiz){
    if(raiz == NULL){
        return;
    }
    libera_NO(*raiz);//libera cada n�
    free(raiz);//libera a raiz
}

int insere_ArvBin(ArvBin* raiz, char caracter, const char* code){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        *raiz = cria_NO('\0');
    }

    struct NO *atual = *raiz;
    
    for(int i = 0; code[i] != '\0'; i++){
        if(code[i] == '.'){
            if(atual->ponto == NULL){
                atual->ponto = cria_NO('\0');
            }
            atual = atual->ponto;
        } else if(code[i] == '-'){
            if(atual->traco == NULL){
                atual->traco = cria_NO('\0');
            }
            atual = atual->traco;
        } 
    }
    atual->caracter = caracter;
    return 1;
}

/* struct NO* remove_atual(struct NO* atual) {
    struct NO *no1, *no2;
    if(atual->ponto == NULL){
        no2 = atual->traco;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->ponto;
    while(no2->traco != NULL){
        no1 = no2;
        no2 = no2->traco;
    }
    
    if(no1 != atual){
        no1->traco = no2->ponto;
        no2->ponto = atual->ponto;
    }
    no2->traco = atual->traco;
    free(atual);
    return no2;
}

int remove_ArvBin(ArvBin *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            if(atual == *raiz)
                *raiz = remove_atual(atual);
            else{
                if(ant->traco == atual)
                    ant->traco = remove_atual(atual);
                else
                    ant->ponto = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;
        if(valor > atual->info)
            atual = atual->traco;
        else
            atual = atual->ponto;
    }
    return 0;
} */

void preOrdem_ArvBin_rec(struct NO* no, char* path, int index){
    if(no == NULL){
        return;
    }
    if(no->caracter != '\0'){
        path[index] = '\0'; // Adiciona o caracter ao caminho
        printf("Caracter: %c, Path: %s\n", no->caracter, path);
    }
    path[index] = '.'; // Adiciona o ponto para o próximo nível
    preOrdem_ArvBin_rec(no->ponto, path, index + 1);
    path[index] = '-'; // Adiciona o traço para o próximo nível
    preOrdem_ArvBin_rec(no->traco, path, index + 1);
}

void preOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL || *raiz == NULL){
        return;
    }
    char path[BUFFER]; // Buffer para armazenar o caminho
   preOrdem_ArvBin_rec(*raiz, path, 0); // Chama a função recursiva
}
/* 
void emOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvBin(&((*raiz)->ponto));
        printf("%d\n",(*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->traco));
    }
}

void posOrdem_ArvBin(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvBin(&((*raiz)->ponto));
        posOrdem_ArvBin(&((*raiz)->traco));
        printf("%d\n",(*raiz)->info);
    }
} */

char decodifica(ArvBin *raiz, const char* code){
    if(raiz == NULL || *raiz == NULL){
        return '?';
    }
    struct NO* atual = *raiz;
    for(int i = 0; code[i] != '\0'; i++){
        if(code[i] == '.'){
            atual = atual->ponto;
        } else if(code[i] == '-'){
            atual = atual->traco;
        } else {
            return '\0'; // Caractere inválido
        }
        if(atual == NULL){
            return '\0'; // Caminho inválido
        }
    }
    return atual->caracter;
}

char codifica_rec(struct NO* no, char caracter, char* buffer, int index){
    if(no == NULL){
        return 0;
    }

    if(no->caracter == caracter){
        buffer[index] = '\0'; // Adiciona o terminador de string
        return 1; // Encontrou o caractere
    }

    buffer[index] = '.'; // Adiciona o ponto para o próximo nível
    if(codifica_rec(no->ponto, caracter, buffer, index + 1)){
        return 1; // Encontrou na subárvore esquerda
    }

    buffer[index] = '-'; // Adiciona o traço para o próximo nível
    if(codifica_rec(no->traco, caracter, buffer, index + 1)){
        return 1; // Encontrou na subárvore direita
    }

    return 0; // Não encontrou o caractere
}

int codifica(ArvBin *raiz, char caracter, char* buffer, int index){
    if(raiz == NULL || *raiz == NULL){
        return 0;
    }
    return codifica_rec(*raiz, toupper(caracter), buffer, index);
}