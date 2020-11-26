#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

int main()
{

    objeto cabeca, *lista;

    celula componente;

    char comando[50], opcao[2];

    /* Criação da cabeça com nulo */
    cabeca.nextTime = NULL;
    cabeca.nextPrioridade = NULL;
    /* Apontando a lista para cabeça */
    lista = &cabeca;

    scanf("%s", comando);
    while (strcmp(comando, "quit") != 0){
        if(strcmp(comando, "next") == 0){
            scanf("%s", opcao);
            imprimeNext(lista, opcao);
            scanf("%s", comando);
        }else{
            scanf("%d", &(componente.prior));
            scanf("%d:%d:%d", &(componente.chegada.hh), &(componente.chegada.mm), &(componente.chegada.ss));
            scanf("%s", componente.descricao);
            cadastraProcesso(componente, lista);
            scanf("%s", comando);
        }
    }
    
    /*imprimeLista(lista, 0);
    imprimeLista(lista, 12);
    imprimeNext(lista, 12);
    imprimeNext(lista, 0);*/


    return 0;
}