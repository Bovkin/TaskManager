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
void imprimeLista(objeto *lista, int i);
int converteHpS(int hr, int mn, int sg);