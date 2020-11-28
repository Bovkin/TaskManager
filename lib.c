#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

void cadastraProcesso(celula componente, objeto *lista){
    objeto *novoObjeto, *aux;

    int tempoObjeto;

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
        tempoObjeto = converteHmsEmSegundos(novoObjeto->cel.chegada.hh, novoObjeto->cel.chegada.mm, novoObjeto->cel.chegada.ss);
        while (aux->nextTime != NULL && converteHmsEmSegundos(aux->nextTime->cel.chegada.hh, aux->nextTime->cel.chegada.mm, aux->nextTime->cel.chegada.ss) < tempoObjeto){
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
        printf("ERRO AO ALOCAR MEMORIA\n");
    }
    return novoObjeto;
}

/* Função que realiza a impressão da lista inteira */
void imprimeLista(objeto *lista, char *opcao){
    objeto *aux = NULL;

    if(lista->nextTime != NULL){
        if (strcmp(opcao, "-p") == 0)
        {
            for (aux = lista->nextPrioridade; aux != NULL; aux = aux->nextPrioridade){
                printf("%02d", aux->cel.prior);
                printf(" %02d", aux->cel.chegada.hh);
                printf(":%02d", aux->cel.chegada.mm);
                printf(":%02d", aux->cel.chegada.ss);
                printf(" %s\n", aux->cel.descricao);
            }
        }else{
            for (aux = lista->nextTime; aux != NULL; aux = aux->nextTime){
                printf("%02d", aux->cel.prior);
                printf(" %02d", aux->cel.chegada.hh);
                printf(":%02d", aux->cel.chegada.mm);
                printf(":%02d", aux->cel.chegada.ss);
                printf(" %s\n", aux->cel.descricao);
            }
        }
    }else{
        printf("LISTA VAZIA!\n");
    }
}

/* Função que realiza a impressão através do comando NEXT */
void imprimeNext(objeto *lista, char *opcao){
    objeto *aux = NULL;
    if(lista->nextPrioridade != NULL){
        if (strcmp(opcao, "-p") == 0){
            aux = lista->nextPrioridade;
            printf("%02d", aux->cel.prior);
            printf(" %02d", aux->cel.chegada.hh);
            printf(":%02d", aux->cel.chegada.mm);
            printf(":%02d", aux->cel.chegada.ss);
            printf(" %s\n", aux->cel.descricao);
        }else{
            aux = lista->nextTime;
            printf("%02d", aux->cel.prior);
            printf(" %02d", aux->cel.chegada.hh);
            printf(":%02d", aux->cel.chegada.mm);
            printf(":%02d", aux->cel.chegada.ss);
            printf(" %s\n", aux->cel.descricao);
        }
    }else{
        printf("LISTA VAZIA\n");
    }
}

/* Função utilizada para deixar a base de horarios igualitaria e assim realizar a comparação. */
/* Utilizamos a conversão para segundos */
int converteHmsEmSegundos(int hr, int mn, int sg){
	return (hr*3600) + (mn*60) + sg;
}

void re_T(objeto *lista, char *opcao){
    objeto *lixo, *aux;

    if(lista->nextTime != NULL){
        aux = lista;

        lixo = lista->nextTime;
        lista->nextTime = lixo->nextTime;
        while (aux->nextPrioridade != NULL && aux->nextPrioridade->cel.prior != lixo->cel.prior){
            aux = aux->nextPrioridade;
        }
        aux->nextPrioridade = aux->nextPrioridade->nextPrioridade;
        free(lixo);
    }else{
        printf("NAO HA PROCESSOS PARA EXECUTAR!\n");
    }
}

void re_P(objeto *lista, char *opcao){
    objeto *lixo, *aux;

    if(lista->nextPrioridade != NULL){
        aux = lista;
        
        lixo = lista->nextPrioridade;
        lista->nextPrioridade = lixo->nextPrioridade;
        while (aux->nextTime != NULL && aux->nextTime->cel.prior != lixo->cel.prior){
            aux = aux->nextTime;
        }
        aux->nextTime = aux->nextTime->nextTime;
        free(lixo);
    }else{
        printf("NAO HA PROCESSOS PARA EXECUTAR!\n");
    }
}

void modificaProcessoPrioridade(celula componente, celula componenteNovo, objeto *lista){
    objeto *aux, *objetoAntigo;
    aux = lista;
    
    while (aux->nextPrioridade != NULL && aux->nextPrioridade->cel.prior > componente.prior){
        aux = aux->nextPrioridade;
    }
    objetoAntigo = aux->nextPrioridade;
    objetoAntigo->cel.prior = componenteNovo.prior;
    aux->nextPrioridade = aux->nextPrioridade->nextPrioridade;
    inserePrioridade(objetoAntigo, lista);
}

void modificaProcessoTempo(celula componente, celula componenteNovo, objeto *lista){
    objeto *aux, *objetoAntigo;
    int tempoProcesso2;

    aux = lista;

    tempoProcesso2 = converteHmsEmSegundos(componente.chegada.hh, componente.chegada.mm, componente.chegada.ss);
    while (aux->nextTime != NULL && converteHmsEmSegundos(aux->nextTime->cel.chegada.hh, aux->nextTime->cel.chegada.mm, aux->nextTime->cel.chegada.ss) != tempoProcesso2){
        aux = aux->nextTime;
    }
    objetoAntigo = aux->nextTime;
    objetoAntigo->cel.chegada.hh = componenteNovo.chegada.hh;
    objetoAntigo->cel.chegada.mm = componenteNovo.chegada.mm;
    objetoAntigo->cel.chegada.ss = componenteNovo.chegada.ss;
    aux->nextTime = aux->nextTime->nextTime;
    insereTempo(objetoAntigo, lista);
}

void inserePrioridade(objeto *novoObjeto, objeto *lista){

    objeto *aux;

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
}

void insereTempo(objeto *novoObjeto, objeto *lista){

    objeto *aux;

    int tempo;

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

/*  */
void menu(char *comando, objeto *lista){

    char opcao[2];
    celula componente, componenteNovo;

    if(strcmp(comando, "next") == 0){
        scanf("%s", opcao);
        imprimeNext(lista, opcao);
        printf("\n");
        scanf("%s", comando);
    }else if(strcmp(comando, "add") == 0){
        scanf("%d", &(componente.prior));
        scanf("%d:%d:%d", &(componente.chegada.hh), &(componente.chegada.mm), &(componente.chegada.ss));
        scanf("%s", componente.descricao);
        cadastraProcesso(componente, lista);
        scanf("%s", comando);
    }else if(strcmp(comando, "print") == 0){
        scanf("%s", opcao);
        imprimeLista(lista, opcao);
        printf("\n");
        scanf("%s", comando);
    }else if(strcmp(comando, "exec") == 0){
        scanf("%s", opcao);
        if(strcmp(opcao, "-p") == 0){
            re_P(lista, opcao);
        }else{
            re_T(lista, opcao);
        }
        scanf("%s", comando);
    }else if(strcmp(comando, "change") == 0){
        scanf("%s", opcao);
        if(strcmp(opcao, "-t") == 0){
            scanf("%d:%d:%d|%d:%d:%d", &(componente.chegada.hh), &(componente.chegada.mm), &(componente.chegada.ss), &(componenteNovo.chegada.hh), &(componenteNovo.chegada.mm), &(componenteNovo.chegada.ss));
            modificaProcessoTempo(componente, componenteNovo, lista);
        }else{
            scanf("%d|%d", &(componente.prior), &(componenteNovo.prior));
            modificaProcessoPrioridade(componente, componenteNovo, lista);
        }
        scanf("%s", comando);
    }
}