#include "funcoes.h"

void carregar_Alfabeto(ArvBin *AB, const char* dicionario){
  FILE* arc = fopen(dicionario, "r");
  if(!arc){
      printf("ERROR 404! - FILE NOT FOUND\n");
      exit(1);
  }

  char linha[MAX_LINE], caracter, code[MAX_CODE];

  while(fgets(linha, sizeof(linha), arc)){
      if(linha[0] == '\0' || linha[0] == '\n'){
          continue; // Ignora linhas vazias
      } 
      if (sscanf(linha, "%c %s", &caracter, code) == 2) {
          insere_ArvBin(AB, caracter, code);
      }
  }
  fclose(arc);
}

void menu(ArvBin *AB){
  int opcao;
  char mensagem[MAX_MSG];

  do{
      printf("\n========== MENU ==========\n\n"
             "1. Codificar mensagem\n"
             "2. Decodificar mensagem\n"
             "3. Sair\n"
             "\n==========================\n"
             "Escolha uma opcao: ");
      scanf("%d", &opcao);
      getchar(); // Limpa o buffer do teclado

      switch(opcao){
          case 1:
              printf("Digite a mensagem a ser codificada: \n");
              fgets(mensagem, sizeof(mensagem), stdin);
              mensagem[strcspn(mensagem, "\n")] = '\0'; // Remove o newline
              
              // Chamar função de codificação
              printf("Mensagem codificada: ");
              for(int i = 0; mensagem[i]; i++){
                  char buffer[BUFFER];
                  if(mensagem[i] == ' '){
                      printf("/ ");
                  } else if(codifica(AB, mensagem[i], buffer, 0)){
                      printf("%s ", buffer);
                  } else {
                      printf("? ");
                  }
              }
              printf("\n");
              break;
          case 2:
              printf("Digite a mensagem em Morse (separar letras por espaço e palavras por /): \n");
              fgets(mensagem, sizeof(mensagem), stdin);
              mensagem[strcspn(mensagem, "\n")] = '\0'; // Remove o newline
              
              // Chamar função de decodificação
              printf("Mensagem decodificada: ");
              char *token = strtok(mensagem, " ");
              while(token){
                  if(strcmp(token, "/") == 0){
                      printf(" ");
                  } else {
                      char decodificado = decodifica(AB, token);
                      if(decodificado != '\0'){
                          printf("%c", decodificado);
                      } else {
                          printf("?");
                      }
                  }
                  token = strtok(NULL, " ");
              }
              printf("\n");
              break;
          case 3:
              system("clear");
              break;
          default:
              printf("Opcao invalida! Tente novamente.\n");
      }
  } while (opcao != 3);
}