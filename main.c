#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

int main(){

    objeto cabeca, *lista;

    char comando[50];

    /* Criação da cabeça com nulo */
    cabeca.nextTime = NULL;
    cabeca.nextPrioridade = NULL;
    /* Apontando a lista para cabeça */
    lista = &cabeca;

    /* REALIZA A LEITURA DO PRIMEIRO COMANDO */
    /* APÓS A LEITURA DO COMANDO, TEMOS O LAÇO PARA ITERAR 
    ATÉ QUE O COMANDO SEJA IGUAL A QUIT E ENCERRA O PROGRAMA */
    scanf("%s", comando);
    while (strcmp(comando, "quit") != 0){
        menu(comando, lista);
    }

    return 0;
}