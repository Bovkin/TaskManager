#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

int main()
{

    objeto cabeca, *lista;

    celula componente;

    char texto[50];

    /* Criação da cabeça com nulo */
    cabeca.nextTime = NULL;
    cabeca.nextPrioridade = NULL;
    /* Apontando a lista para cabeça */
    lista = &cabeca;

    scanf("%s", texto);
    while (strcmp(texto, "quit") != 0){
        scanf("%d", &(componente.prior));
        scanf("%d:%d:%d", &(componente.chegada.hh), &(componente.chegada.mm), &(componente.chegada.ss));
        scanf("%s", componente.descricao);
        cadastraProcesso(componente, lista);
        scanf("%s", texto);
    }
    
    imprimeLista(lista, 0);
    imprimeLista(lista, 12);


    return 0;
}