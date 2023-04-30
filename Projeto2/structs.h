
#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__


typedef struct Nome {
    char *nome;
    struct Nome *next;
}Nome;

typedef struct{
    Nome *cabeca;
    Nome *cauda;
}Lista_Nomes;


typedef struct Paragem{
    int id ;
    char *nome;
    double lat;
    double lon;
    struct Paragem *next;
}Paragem;

typedef struct{
    Paragem *cabeca;
    Paragem *cauda;
} Lista_P;

typedef struct ID{
    int id;
    struct ID *next;
    struct ID *previous;
}ID;

typedef struct{
    ID *cabeca;
    ID *cauda;
}Lista_ID;

typedef struct Carreira{
    int id;
    char *nome;
    double custo_total;
    double duracao_total;
    int n_paragens;
    Lista_ID *id_ligacoes;
    Lista_ID *id_paragens;
    struct Carreira *next;
}Carreira;

typedef struct{
    Carreira *cabeca;
    Carreira *cauda;
} Lista_C;

typedef struct Ligacao{
    int id;
    int id_carreira;
    int id_origem;
    int id_destino;
    double custo;
    double duracao;
    struct Ligacao *next;
}Ligacao;

typedef struct{
    Ligacao *cabeca;
    Ligacao *cauda;
} Lista_L;

typedef struct{
   
    int n_paragens;
    Lista_P *paragens;

    int n_carreiras;
    Lista_C *carreiras;

    int n_ligacoes;
    Lista_L *ligacoes;
}BaseDados;


#endif