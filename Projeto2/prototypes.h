#ifndef __PROTOTYPES_H__
#define __PROTOTYPES_H__

#include "structs.h"

/*---------------------------------------------------------------------------*/

int le_palavra(char str[]);

int Inverso(char str[]);

void* malloc_controlado(BaseDados* db, unsigned int tamanho);

/*---------------------------------------------------------------------------*/
int verifica_carreira_exis(BaseDados *db,char *nome_carreira);

int busca_n_p_carreira(BaseDados *db,int id_carreira);

int busca_id_carreira(BaseDados *db, char *nome_carreira);

void add_carreiras(BaseDados *db,char *nome_carreira);

void insere_cauda_c(Lista_C *lista,Carreira *c);

void lista_carreiras_sistema(BaseDados *db);

void lista_paragens_carreira(BaseDados *db,char *nome_carreira);

void lista_paragens_carreira_inv(BaseDados *db,char *nome_carreira);

void carreiras(BaseDados *db);

/*---------------------------------------------------------------------------*/

char *busca_n_paragem(BaseDados *db,int id);

int busca_id_paragem(BaseDados *db,char *nome_paragem);

int count_carreiras(BaseDados*db,int id );

int verifica_paragem_exis(BaseDados *db,char *nome_paragem);

void insere_cauda_p(Lista_P *lista,Paragem *p);

void add_paragem(BaseDados *db,char *nome_paragem,double latitude,double longitude);

void lista_paragens_sistema(BaseDados *db);

void mostraparagem(BaseDados *db,char *nome_paragem);

void paragens(BaseDados *db);

/*---------------------------------------------------------------------------*/

int verifica_origem(BaseDados *db,int id_c,int id_origem);

int verifica_destino(BaseDados *db,int id_c,int id_destino);

void insere_cauda_l(Lista_L *lista,Ligacao *l);

void insere_ID_ligacao_fim(Lista_ID * id_ligacoes ,int id);

void insere_ID_ligacao_inicio(Lista_ID * id_ligacoes ,int id);
 
Ligacao * cria_ligacao(BaseDados *db,int id_c,int id_origem,int id_destino,double custo,double duracao);

void add__primeira_ligacao(BaseDados *db,int id_c,int id_origem,int id_destino,double custo,double duracao);

void add_fim(BaseDados *db,int id_c,int id_destino);

void add_inicio(BaseDados *db,int id_c,int id_origem);

void add_ligacao(BaseDados *db,int id_c,int id_origem,int id_destino,double custo,double duracao);

void ligacoes(BaseDados *db);

/*---------------------------------------------------------------------------*/

void sort(Lista_Nomes* nomes);

void insere_nome(Lista_Nomes * nomes,Nome *n);

void add_nome(BaseDados *db,Lista_Nomes * nomes,char *nome);

Lista_Nomes * carreiras_paragem(BaseDados *db,int id_p);

void limpar_lista_nomes(Lista_Nomes * nomes);

void print_lista_nomes(Lista_Nomes *nomes);
    
void nos(BaseDados*db);

/*---------------------------------------------------------------------------*/

void remove_carreira(BaseDados *db, int id_c);

void remove_ligacoes_carreira(BaseDados *db, int id_c);

void e_carreira(BaseDados *db);

/*---------------------------------------------------------------------------*/


void remove_paragem(BaseDados *db, int id_p);

void reset_carreira(BaseDados *db, Carreira * c);

ID * paragem_next(Carreira *c, int id_p);

ID* paragem_ant(Carreira *c, int id_p);

int custo_ligacao(BaseDados *db,int id_l);

int duracao_ligacao(BaseDados *db,int id_l);

Ligacao * busca_ligacao(BaseDados *db, int id_l);

ID * ID_ligacao(BaseDados *db, int id_c, int id_origem, int id_destino, Lista_ID *l);
       
ID * cria_id (BaseDados *db ,int id);

void remove_id_fim(BaseDados *db,Carreira *c, int id_p);

void remove_id_inicio(BaseDados *db,Carreira *c, int id_p);

void liberta_id_meio(ID * id_ligacao_ant, ID* id_ligacao_next, ID * nova_ligacao_id);

void unica_ligacao(Carreira *c , ID * nova_ligacao_id);

void liberta_id_inicial(Carreira *c ,ID * id_ligacao_ant, ID* id_ligacao_next, ID * nova_ligacao_id);

void liberta_id_final(Carreira *c ,ID * id_ligacao_ant, ID* id_ligacao_next, ID * nova_ligacao_id);

void remove_id_meio(BaseDados *db,Carreira *c, int id_p);

void remove_id(BaseDados *db, Carreira *c, int id_p);
    
void remove_ligacoes_paragem(BaseDados *db, int id_p);

void e_paragem(BaseDados *db);

/*---------------------------------------------------------------------------*/

int comandos(BaseDados *db);

/*---------------------------------------------------------------------------*/

void free_all(BaseDados *db);

void free_lista_paragens(BaseDados *db);

void free_lista_carreiras(BaseDados *db);
        
void free_lista_ID(Lista_ID *lista);

void free_lista_ligacoes(BaseDados *db);

void reset(BaseDados *db);
   
/*---------------------------------------------------------------------------*/

Lista_C *inicializa_lista_carreiras(BaseDados *db);

Lista_P *inicializa_lista_paragens(BaseDados *db);

Lista_ID *inicializa_lista_ID(BaseDados *db);

Lista_L *inicializa_lista_ligacoes(BaseDados *db);

Lista_Nomes *inicializa_lista_nomes(BaseDados *db);

int main();

/*---------------------------------------------------------------------------*/

#endif