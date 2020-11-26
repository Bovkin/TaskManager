#define MAX_DESCR 50

/* Armazena um horário de chegada */
typedef struct{
    int hh;
    int mm;
    int ss;
} horario;
/* Armazena informaçoes de um processo */
typedef struct{
    int prior;
    horario chegada;
    char descricao[MAX_DESCR + 1];
} celula;

typedef struct objeto{
    celula cel;
    struct objeto *nextPrioridade;
    struct objeto *nextTime;
} objeto;

void cadastraProcesso(celula componente, objeto *lista);
objeto* alocaNovoObjeto(celula componente);
void imprimeLista(objeto *lista, char *opcao);
void imprimeNext(objeto *lista, char *opcao);
int converteHmsEmSegundos(int hr, int mn, int sg);
void re_C(objeto *lista, char *opcao);