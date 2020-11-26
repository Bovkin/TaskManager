#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

void cadastraProcesso(celula componente, objeto *lista){
    objeto *novoObjeto, *aux;

    int tempo;

    novoObjeto = alocaNovoObjeto(componente);
    /* Prioridade */
    if (lista->nextPrioridade == NULL){
        lista->nextPrioridade = novoObjeto;
    }
    else{
        /* Cabeça */
        aux = lista;
        while (aux->nextPrioridade != NULL && aux->nextPrioridade->cel.prior > novoObjeto->cel.prior){
            aux = aux->nextPrioridade;
        }
        novoObjeto->nextPrioridade = aux->nextPrioridade;
        aux->nextPrioridade = novoObjeto;
    }
    /* Time */
    if (lista->nextTime == NULL){
        lista->nextTime = novoObjeto;
    }
    else{
        /* Cabeça */
        aux = lista;
        tempo = converteHmsEmSegundos(novoObjeto->cel.chegada.hh, novoObjeto->cel.chegada.mm, novoObjeto->cel.chegada.ss);
        while (aux->nextTime != NULL && converteHmsEmSegundos(aux->nextTime->cel.chegada.hh, aux->nextTime->cel.chegada.mm, aux->nextTime->cel.chegada.ss) < tempo){
            aux = aux->nextTime;
        }
        novoObjeto->nextTime = aux->nextTime;
        aux->nextTime = novoObjeto;
    }
}

objeto *alocaNovoObjeto(celula componente){
    objeto *novoObjeto;

    novoObjeto = (objeto *)malloc(sizeof(objeto));
    if (novoObjeto != NULL)
    {
        novoObjeto->cel = componente;
        novoObjeto->nextPrioridade = NULL;
        novoObjeto->nextTime = NULL;
    }
    else
    {
        printf("Erro ao alocar memória\n");
    }
    return novoObjeto;
}

/* Função que realiza a impressão da lista inteira */
void imprimeLista(objeto *lista, int i){
    objeto *aux;

    if (i == 0)
    {
        for (aux = lista->nextPrioridade; aux != NULL; aux = aux->nextPrioridade){
            printf("%d", aux->cel.prior);
            printf(" %d", aux->cel.chegada.hh);
            printf(":%d", aux->cel.chegada.mm);
            printf(":%d", aux->cel.chegada.ss);
            printf(" %s\n", aux->cel.descricao);
        }
    }
    else{
        for (aux = lista->nextTime; aux != NULL; aux = aux->nextTime){
            printf("%d", aux->cel.prior);
            printf(" %d", aux->cel.chegada.hh);
            printf(":%d", aux->cel.chegada.mm);
            printf(":%d", aux->cel.chegada.ss);
            printf(" %s\n", aux->cel.descricao);
        }
    }
}

/* Função que realiza a impressão através do comando NEXT */
void imprimeNext(objeto *lista, char *opcao){
    objeto *aux;

    if (strcmp(opcao, "-p") == 0){
        aux = lista->nextPrioridade;
        printf("%d", aux->cel.prior);
        printf(" %d", aux->cel.chegada.hh);
        printf(":%d", aux->cel.chegada.mm);
        printf(":%d", aux->cel.chegada.ss);
        printf(" %s\n", aux->cel.descricao);
    }
    else{
        aux = lista->nextTime;
        printf("%d", aux->cel.prior);
        printf(" %d", aux->cel.chegada.hh);
        printf(":%d", aux->cel.chegada.mm);
        printf(":%d", aux->cel.chegada.ss);
        printf(" %s\n", aux->cel.descricao);
    }
}

/* Função utilizada para deixar a base de horarios igualitaria e assim realizar a comparação. */
/* Utilizamos a conversão para segundos */
int converteHmsEmSegundos(int hr, int mn, int sg){
	return (hr*3600) + (mn*60) + sg;
}