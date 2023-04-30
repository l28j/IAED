/* iaed-23 - ist1106221 - project2 */

/*João Lucas Morais Cardoso Tavares Rodrigues*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "prototypes.h"

#define TRUE 1
#define FALSE 0
#define INPUT_MAX 65536

/*---------------------------------------------------------------------------*/
/*Funções Auxiliares*/

/*Função le_palavras recebe um array e ignora todos os espacos/tabs, guardando
num vetor apenas os caracteres de uma palavra dentro ou fora de aspas */
int le_palavra(char str[]) {
    int i = 0;
    int c = getchar();

    while (c == ' ' || c == '\t')   /* ignora espacos e tabs */
        c = getchar();
    
    if (c == '"') {
        c = getchar();
        while (c != '"' && c != '\n') {     /* le uma string entre " " */
            str[i++] = c;
            c = getchar();
        }
    }
    
    else {
        while (c != ' ' && c != '\t' && c != '\n') {    /* le uma palavra */
            str[i++] = c;
            c = getchar();
        }
    }   
    str[i] = '\0';
    return (c != '\n');     /* retorna 1 se não chegou ao fim da linha */
}

/*Função Inverso recebe um vetor sendo uma string e retorna TRUE ou FALSE,se 
a palavra inserida for correspondente a inverso ou a uma abreviação do mesmo*/
int Inverso(char str[]){
    if(strcmp(str,"inverso")==0 || strcmp(str,"invers")==0 
    || strcmp(str,"inver")==0 || strcmp(str,"inve")==0      
    || strcmp(str,"inv")==0){
        return TRUE;                    
    }
    return FALSE;
}

/*Função para alocação de memória caso programa não consiga alocar
mais memória o mesmo para e limpa a memória ja alocada printando
uma mensagem de erro*/
void* malloc_controlado(BaseDados* db, unsigned int tamanho) {
    void* ponteiro = malloc(tamanho);
    if (ponteiro == NULL) {
        free_all(db);
        printf("No memory.\n");
        exit(1);
    }
    return ponteiro;
}

/*---------------------------------------------------------------------------*/
/*Funções Carreiras*/

/*Função verifica_carreira_exis recebe uma base de dados e uma string
e retorna TRUE ou FALSE,se a carreira inserida já existe ou não*/
int verifica_carreira_exis(BaseDados *db,char *nome_carreira){
    Carreira *c = db->carreiras->cabeca;
    while (c!=NULL){
        if (strcmp(c->nome,nome_carreira)==0){
            return TRUE;
        }
        c = c->next;
    }
    return FALSE;
}

/*Função busca_n_p_carreira recebe uma base de dados e um inteiro
e retorna o número de paragens de uma carreira*/
int busca_n_p_carreira(BaseDados *db,int id_carreira){
    Carreira *c = db->carreiras->cabeca;
    while (c!=NULL){
        if (c->id == id_carreira){
            return c->n_paragens;
        }
        c = c->next;
    }
    return FALSE;
}

/*Função busca_id_carreira recebe uma base de dados e uma string
e retorna o id de uma carreira*/
int busca_id_carreira(BaseDados *db, char *nome_carreira){
    Carreira *c = db->carreiras->cabeca;
    while (c!=NULL){
        if (strcmp(c->nome,nome_carreira)==0){
            return c->id;
        }
        c = c->next;
    }
    return FALSE;
}

/*Função add_carreiras recebe uma base de dados e uma string
e adiciona/cria uma carreira a base de dados*/
void add_carreiras(BaseDados *db,char *nome_carreira){
    Carreira *c = (Carreira*)malloc_controlado(db,sizeof(Carreira));
    c->nome = (char*)malloc_controlado(db,strlen(nome_carreira)+1);
    strcpy(c->nome,nome_carreira);
    c->custo_total = 0;
    c->duracao_total = 0;
    c->n_paragens = 0;
    c->id = db->n_carreiras;
    c->id_paragens = inicializa_lista_ID(db);
    c->id_ligacoes = inicializa_lista_ID(db);
    db->n_carreiras++;
    insere_cauda_c(db->carreiras,c);
}

/*Funcao insere_cauda_c recebe uma lista de carreiras e uma carreira
e insere a carreira na cauda da lista de carreiras*/
void insere_cauda_c(Lista_C *lista,Carreira *c){
    if (lista->cabeca==NULL){
        lista->cabeca = c;
        lista->cauda = c;
        c->next = NULL;
    }
    else{
        lista->cauda->next = c;
        lista->cauda = c;
        c->next = NULL;
    }
}

/*Função çista_carreiras_sistema recebe uma base de dados e imprime
todas as carreiras do sistema*/
void lista_carreiras_sistema(BaseDados *db){
    Carreira *c = db->carreiras->cabeca;
    while (c!=NULL){
        if (c->n_paragens==0){
            printf("%s %d %.2f %.2f\n",c->nome,c->n_paragens,c->custo_total,c->duracao_total);
        }
        else{
            printf("%s %s %s ",c->nome,busca_n_paragem(db,c->id_paragens->cabeca->id),
            busca_n_paragem(db,c->id_paragens->cauda->id));
            printf("%d %.2f %.2f\n",c->n_paragens,c->custo_total,c->duracao_total);
        }
        c = c->next;
    }
}

/*Função lista_para_carreira recebe uma base de dados e uma string
e imprime todas as paragens de uma carreira*/
void lista_paragens_carreira(BaseDados *db,char *nome_carreira){
    Carreira *c = db->carreiras->cabeca;
    while (c!=NULL){
        if (strcmp(c->nome,nome_carreira)==0 && c->n_paragens!=0){
            ID *id_p = c->id_paragens->cabeca;
            printf("%s",busca_n_paragem(db,id_p->id));
            id_p = id_p->next;
            while (id_p!=NULL){
                printf(", %s",busca_n_paragem(db,id_p->id));
                id_p = id_p->next;
            }
            printf("\n");
        }
        c = c->next;
    }
}

/*Função lista_paragens_carreira_inv recebe uma base de dados e uma string
e imprime todas as paragens de uma carreira de forma inversa*/
void lista_paragens_carreira_inv(BaseDados *db,char *nome_carreira){
    Carreira *c = db->carreiras->cabeca;
    while (c!=NULL){
        if (strcmp(c->nome,nome_carreira)==0 && c->n_paragens!=0){
            ID *id_p = c->id_paragens->cauda;
            printf("%s",busca_n_paragem(db,id_p->id));
            id_p = id_p->previous;
            while (id_p!=NULL){
                printf(", %s",busca_n_paragem(db,id_p->id));
                id_p = id_p->previous;
            }
            printf("\n");
        }
        c = c->next;
    }
}

/*Função carreiras faz a respetiva avaliacao dos inputs do 
utilizador e executa as respetivas Funções consuante as ordens
de input, imprimindo os erros possiveis para essas ordens*/
void carreiras(BaseDados *db){
    int c;
    if ((c=getchar())=='\n'){
        lista_carreiras_sistema(db);
    }
    else{
        char nome_carreira[INPUT_MAX];
        if(!le_palavra(nome_carreira)){
            if (verifica_carreira_exis(db,nome_carreira)==TRUE){
                lista_paragens_carreira(db,nome_carreira);
            }
            else{
                add_carreiras(db,nome_carreira);
            }
        }
        else{
            char ordem[INPUT_MAX];
            le_palavra(ordem);
            if (Inverso(ordem)==TRUE){
                lista_paragens_carreira_inv(db,nome_carreira);
            }
            else{
                printf("incorrect sort option.\n");
            }
        }
    }
}

/*---------------------------------------------------------------------------*/
/*Funções Paragem*/

/*Função busca_n_paragem recebe uma base de dados e um id de uma paragem
e devolve o nome da paragem com esse id*/
char *busca_n_paragem(BaseDados *db,int id){
    Paragem *p = db->paragens->cabeca;
    while (p!=NULL){
        if (p->id==id){
            return p->nome;
        }
        p = p->next;
    }
    return NULL;
}

/*Funcao busca_id_paragem recebe uma base de dados e uma string
e devolve o id da paragem com esse nome*/
int busca_id_paragem(BaseDados *db,char *nome_paragem){
    Paragem *p = db->paragens->cabeca;
    while (p!=NULL){
        if (strcmp(p->nome,nome_paragem)==0){
            return p->id;
        }
        p = p->next;
    }
    return -1;
}

/*Função count_carreiras recebe uma base de dados e um id de uma paragem
e devolve o numero de carreiras que passam por essa paragem*/
int count_carreiras(BaseDados*db,int id ){
    Carreira *c = db->carreiras->cabeca;
    int count = 0;
    while (c!=NULL){
        ID *id_p = c->id_paragens->cabeca;
        while (id_p!=NULL){
            if (id_p->id==id){
                count++;
                break;
            }
            id_p = id_p->next;
        }
        c = c->next;
    }
    return count;
}

/*Função verifica_paragem_exis recebe uma base de dados e uma string
e devolve TRUE se a paragem com esse nome existe e FALSE se nao existe*/
int verifica_paragem_exis(BaseDados *db,char *nome_paragem){
    Paragem *p = db->paragens->cabeca;
    while (p!=NULL){
        if (strcmp(p->nome,nome_paragem)==0){
            return TRUE;
        }
        p = p->next;
    }
    return FALSE;
}

/*Funçâo insere_cauda_p recebe uma lista de paragens e uma paragem
e insere a paragem na cauda da lista*/
void insere_cauda_p(Lista_P *lista,Paragem *p){
    if (lista->cabeca==NULL){
        lista->cabeca = p;
        lista->cauda = p;
        p->next = NULL;
    }
    else{
        lista->cauda->next = p;
        lista->cauda = p;
        p->next = NULL;
    }
}

/*Função add_paragem recebe uma base de dados, uma string, dois doubles
e adiciona/cria uma paragem com o nome, latitude e longitude dados*/
void add_paragem(BaseDados *db,char *nome_paragem,double latitude,double longitude){
    Paragem *p = (Paragem*)malloc_controlado(db,sizeof(Paragem));
    p->nome = (char*)malloc_controlado(db,strlen(nome_paragem)+1);
    strcpy(p->nome,nome_paragem);
    p->lat = latitude;
    p->lon = longitude;
    p->id = db->n_paragens;
    db->n_paragens++;
    insere_cauda_p(db->paragens,p);
}

/*Função lista_paragens_sistema recebe uma base de dados e imprime
todas as paragens do sistema*/
void lista_paragens_sistema(BaseDados *db){
    Paragem *p = db->paragens->cabeca;
    while (p!=NULL){
        printf("%s: %16.12f %16.12f %d\n",p->nome,p->lat,p->lon,count_carreiras(db,p->id));
        p = p->next;
    }
}

/*Função mostraparagem recebe uma base de dados e uma string
e imprime a latitude e longitude da paragem com esse nome*/
void mostraparagem(BaseDados *db,char *nome_paragem){
    Paragem *p = db->paragens->cabeca;
    while (p!=NULL){
        if (strcmp(p->nome,nome_paragem)==0){
            printf("%16.12f %16.12f\n",p->lat,p->lon);  
        }
        p = p->next;
    }
}

/*Função paragens faz a respetiva avaliacao dos inputs do
utilizador e executa as respetivas Funções consuante as ordens
de input, imprimindo os erros possiveis para essas ordens*/
void paragens(BaseDados *db){
    int c;
    if ((c=getchar())=='\n'){
        lista_paragens_sistema(db);
    }
    else{
        char nome_paragem[INPUT_MAX];
        if (le_palavra(nome_paragem)){
            if (verifica_paragem_exis(db,nome_paragem)==TRUE){
                printf("%s: stop already exists.\n",nome_paragem);
            }
            else{
                double latitude,longitude;
                scanf("%lf %lf",&latitude,&longitude);
                add_paragem(db,nome_paragem,latitude,longitude);
                
            }
        }
        else {
            if (verifica_paragem_exis(db,nome_paragem)==TRUE){
                mostraparagem(db,nome_paragem); 
            }
            else{
                printf("%s: no such stop.\n",nome_paragem);
            }
        }
    }
}

/*---------------------------------------------------------------------------*/
/*Funçôes Ligações*/


/*Função verifica_origem recebe uma base de dados, um id de uma carreira
e um id de uma paragem e devolve TRUE se a paragem com esse id é a origem
da carreira com esse id e FALSE se nao é*/
int verifica_origem(BaseDados *db,int id_c,int id_origem){
    Carreira *c = db->carreiras->cabeca;
    while (c!=NULL){
        if (c->id==id_c){
            ID *id_p = c->id_paragens->cauda;
            if (id_p->id==id_origem){
                return TRUE;
            }
        }
        c = c->next;
    }
    return FALSE;
}

/*Função verifica_destino recebe uma base de dados, um id de uma carreira
e um id de uma paragem e devolve TRUE se a paragem com esse id é o destino
da carreira com esse id e FALSE se nao é*/
int verifica_destino(BaseDados *db,int id_c,int id_destino){
    Carreira *c = db->carreiras->cabeca;
    while (c!=NULL){
        if (c->id==id_c){
            ID *id_p = c->id_paragens->cabeca;
            if (id_p->id==id_destino){
                return TRUE;
            }
        }
        c = c->next;

    }
    return FALSE;
}

/*Função insere_cauda_l recebe uma lista de ligacoes e uma ligacao
e insere a ligacao na cauda da lista*/
void insere_cauda_l(Lista_L *lista,Ligacao *l){
    if (lista->cabeca==NULL){
        lista->cabeca = l;
        lista->cauda = l;
        l->next = NULL;
    }
    else{
        lista->cauda->next = l;
        lista->cauda = l;
        l->next = NULL;
    }
}

/*Função insere_ID_ligacao_fim recebe uma lista de ids e um id
e insere o id na cauda da lista*/
void insere_ID_ligacao_fim(Lista_ID * id_ligacoes ,int id){
    ID *id_l = (ID*)malloc(sizeof(ID));
    id_l->id = id;
    if (id_ligacoes->cabeca==NULL){
        id_ligacoes->cabeca = id_l;
        id_ligacoes->cauda = id_l;
        id_l->next = NULL;
        id_l->previous = NULL;
    }
    else{
        id_l->previous = id_ligacoes->cauda;
        id_l->next = NULL;
        id_ligacoes->cauda->next = id_l;
        id_ligacoes->cauda = id_l;
    }
}

/*Função insere_ID_ligacao_inicio recebe uma lista de ids e um id
e insere o id na cabeca da lista*/
void insere_ID_ligacao_inicio(Lista_ID * id_ligacoes ,int id){
    ID *id_l = (ID*)malloc(sizeof(ID));
    id_l->id = id;
    if (id_ligacoes->cabeca==NULL){
        id_ligacoes->cabeca = id_l;
        id_ligacoes->cauda = id_l;
        id_l->next = NULL;
        id_l->previous = NULL;
    }
    else{
        id_l->next = id_ligacoes->cabeca;
        id_l->previous = NULL;
        id_ligacoes->cabeca->previous = id_l;
        id_ligacoes->cabeca = id_l;
    }
}

/*Função cria_ligacao recebe uma base de dados, um id de uma carreira,
um id de uma paragem de origem, um id de uma paragem de destino,
um custo e uma duracao e cria uma ligacao com esses dados e devolve
um apontador para essa ligacao*/
Ligacao * cria_ligacao(BaseDados *db,int id_c,int id_origem,int id_destino,double custo,double duracao){
    Ligacao *l = (Ligacao*)malloc_controlado(db,sizeof(Ligacao));
    l->id_carreira = id_c;
    l->id_origem = id_origem;
    l->id_destino = id_destino;
    l->custo = custo;
    l->duracao = duracao;
    l->id = db->n_ligacoes;
    db->n_ligacoes++;
    insere_cauda_l(db->ligacoes,l);
    return l;
}
/*Função add_primeira_ligacao recebe uma base de dados, um id de uma carreira,
um id de uma paragem de origem, um id de uma paragem de destino,
um custo e uma duracao e cria uma ligacao com esses dados e insere-a
na carreira com esse id*/
void add_primeira_ligacao(BaseDados *db,int id_c,int id_origem,int id_destino,double custo,double duracao){
    Carreira *c =db->carreiras->cabeca;
    while (c!=NULL){
        if (c->id==id_c){
            ID *id_p_o = (ID*)malloc_controlado(db,sizeof(ID));
            ID *id_p_d = (ID*)malloc_controlado(db,sizeof(ID));

            Ligacao *l = cria_ligacao(db,id_c,id_origem,id_destino,custo,duracao);
            insere_ID_ligacao_inicio(c->id_ligacoes,l->id);
            
            id_p_o->id = id_origem;
            id_p_d->id = id_destino;
            
            c->id_paragens->cabeca = id_p_o;
            c->id_paragens->cauda = id_p_d;

            id_p_o->next = id_p_d;
            id_p_d->previous = id_p_o;

            id_p_o->previous = NULL;
            id_p_d->next = NULL;

            c->n_paragens = 2;
            c->custo_total += custo;
            c->duracao_total += duracao;

            break;
        }
        c = c->next;
    }
}
/*Função add_fim recebe uma base de dados, um id de uma carreira,
um id de uma paragem e insere a paragem com esse id no fim da carreira
com esse id*/
void add_fim(BaseDados *db,int id_c,int id_destino){
    Carreira *c =db->carreiras->cabeca;
    while (c!=NULL){
        if (c->id==id_c){
            ID *id_p = (ID*)malloc_controlado(db,sizeof(ID));
            id_p->id = id_destino;
            id_p->next = NULL;
            id_p->previous = c->id_paragens->cauda;
            c->id_paragens->cauda->next = id_p;
            c->id_paragens->cauda = id_p;
            break;
        }
        c = c->next;
    }
}

/*Função add_inicio recebe uma base de dados, um id de uma carreira,
um id de uma paragem e insere a paragem com esse id no inicio da carreira
com esse id*/
void add_inicio(BaseDados *db,int id_c,int id_origem){
    Carreira *c =db->carreiras->cabeca;
    while (c!=NULL){
        if (c->id==id_c){
            ID *id_p = (ID*)malloc_controlado(db,sizeof(ID));
            id_p->id = id_origem;
            id_p->next = c->id_paragens->cabeca;
            id_p->previous = NULL;
            c->id_paragens->cabeca->previous = id_p;
            c->id_paragens->cabeca = id_p;
            break;
        }
        c = c->next;
    }
}

/*Função add_ligacao recebe uma base de dados, um id de uma carreira,
um id de uma paragem de origem, um id de uma paragem de destino,
um custo e uma duracao e cria uma ligacao com esses dados e insere-a
na carreira com esse id*/
void add_ligacao(BaseDados *db,int id_c,int id_origem,int id_destino,double custo,double duracao){
    Carreira *c =db->carreiras->cabeca;
    while (c!=NULL){
        if (c->id==id_c){
            ID * old_origem = c->id_paragens->cabeca;
            ID * old_destino = c->id_paragens->cauda;
            
            Ligacao *l = cria_ligacao(db,id_c,id_origem,id_destino,custo,duracao);

            c->custo_total += custo;
            c->duracao_total += duracao;
            c->n_paragens++;
            
            if (old_origem->id==id_destino && old_destino->id==id_origem){
                add_fim(db,id_c,id_destino);
                insere_ID_ligacao_fim(c->id_ligacoes,l->id);
            }
            else if (old_origem->id==id_destino){
                add_inicio(db,id_c,id_origem);
                insere_ID_ligacao_inicio(c->id_ligacoes,l->id);
            }
            else if (old_destino->id==id_origem){
                add_fim(db,id_c,id_destino);
                insere_ID_ligacao_fim(c->id_ligacoes,l->id);
            }
            
            break;
        }
        c = c->next;
    }
}

/*Função ligacoes recebe o nome da carreira e verifica se
a carreira existe,receve um nome de paragem_origem e destino e paragem_destino
e verifica se ambas existem e se podem ser associadas a carreira, recebe tambem
um custo e duracao associado a esta ligacao*/
void ligacoes(BaseDados *db){
    char nome_carreira[INPUT_MAX];
    char nome_origem[INPUT_MAX];
    char nome_destino[INPUT_MAX];

    double custo,duracao;

    le_palavra(nome_carreira);
    le_palavra(nome_origem);
    le_palavra(nome_destino);
    
    scanf("%lf %lf",&custo,&duracao);
    
    if(verifica_carreira_exis(db,nome_carreira)==FALSE){
        printf("%s: no such line.\n",nome_carreira);
    }
    else{
        if(verifica_paragem_exis(db,nome_origem)==FALSE)
            printf("%s: no such stop.\n",nome_origem);
        else if(verifica_paragem_exis(db,nome_destino)==FALSE)
            printf("%s: no such stop.\n",nome_destino);
        else{
            
            int id_c=busca_id_carreira(db,nome_carreira);
            int num_p=busca_n_p_carreira(db,id_c);
            
            int id_origem = busca_id_paragem(db,nome_origem);
            int id_destino = busca_id_paragem(db,nome_destino);

            if(num_p==0){
                if(custo<0 || duracao<0){
                    printf("negative cost or duration.\n");
                }
                else
                    add_primeira_ligacao(db,id_c,id_origem,id_destino,custo,duracao);
            }
            else{
                if( verifica_destino(db,id_c,id_destino)==TRUE  
                    || verifica_origem(db,id_c,id_origem)==TRUE)
                        if(custo<0 || duracao<0)
                            printf("negative cost or duration.\n");
                        else
                            add_ligacao(db,id_c,id_origem,id_destino,custo,duracao);
                else
                    printf("link cannot be associated with bus line.\n");
            }
        }
    }
}

/*---------------------------------------------------------------------------*/
/*Comando I*/

/*Função sort recebe uma lista de nomes e ordena-a por ordem alfabetica*/
void sort(Lista_Nomes* nomes) {
    Nome *atual = nomes->cabeca;

    while (atual != NULL) {
        Nome *proximo = atual->next;

        while (proximo != NULL) {
            if (strcmp(atual->nome, proximo->nome) > 0) {
                char *temp = atual->nome;
                atual->nome = proximo->nome;
                proximo->nome = temp;
            }

            proximo = proximo->next;
        }

        atual = atual->next;
    }
}

/*Função insere_nome recebe uma lista de nomes e um nome e insere o nome
na lista de nomes*/
void insere_nome(Lista_Nomes * nomes,Nome *n){
    if (nomes->cabeca==NULL){
        nomes->cabeca = n;
        nomes->cauda = n;
        n->next = NULL;
    }
    else{
        nomes->cauda->next = n;
        nomes->cauda = n;
        n->next = NULL;
    }
}

/*Função add_nome recebe uma lista de nomes e um nome e adiciona o nome
na lista de nomes*/
void add_nome(BaseDados *db,Lista_Nomes * nomes,char *nome){
    Nome *n = (Nome*)malloc_controlado(db,sizeof(Nome));
    n->nome = (char*)malloc_controlado(db,strlen(nome)+1);
    strcpy(n->nome,nome);
    insere_nome(nomes,n);
}

/*Função carreiras_paragem recebe uma lista de nomes e uma paragem e
adiciona as carreiras que passam pela paragem na lista de nomes*/
Lista_Nomes * carreiras_paragem(BaseDados *db,int id_p){
    Lista_Nomes * nomes = inicializa_lista_nomes(db);
    Carreira *c = db->carreiras->cabeca;
    while (c!=NULL){
        ID *id = c->id_paragens->cabeca;
        while (id!=NULL){
            if (id->id==id_p){
                add_nome(db,nomes,c->nome);
                break;
            }
            id = id->next;
        }
        c = c->next;
    }
    return nomes;
}

/*Função nos recebe uma lista de nomes e uma paragem e adiciona as paragens
que sao ligadas a paragem na lista de nomes*/
void limpar_lista_nomes(Lista_Nomes * nomes){
    Nome *n = nomes->cabeca;
    Nome *aux;
    while (n!=NULL){
        free(n->nome);
        aux = n;
        n = n->next;
        free(aux);
    }
    free(nomes);
}

/*Função print_lista_nomes recebe uma lista de nomes e imprime os nomes
da lista de nomes*/
void print_lista_nomes(Lista_Nomes *nomes){
    Nome *n = nomes->cabeca;
    while (n!=NULL){
        printf(" %s",n->nome);
        n = n->next;
    }
    printf("\n");
}


/*Função não contêm elementos de input e ira realizar a ordenacao de todas
as paragens que tenham mais de uma carreira e ira imprimir o nome da paragem
por ordem de criacao e as carreiras que passam pela mesma por odem alfabetica
atraves de um algoritmo de ordenacao de sort */
void nos(BaseDados*db){
    Paragem *p = db->paragens->cabeca;
    while (p!=NULL){
        if(count_carreiras(db,p->id)>1){
            Lista_Nomes* nomes_carreiras = carreiras_paragem(db,p->id);
            sort(nomes_carreiras);
            printf("%s ",p->nome);
            printf("%d:",count_carreiras(db,p->id));
            print_lista_nomes(nomes_carreiras);
            limpar_lista_nomes(nomes_carreiras);
        }
        p = p->next;
    }
}

/*---------------------------------------------------------------------------*/
/*Funções remoção Carreiras*/

/*Função remove_carreira recebe uma base de dados e um id de uma carreira
e remove a carreira da base de dados*/
void remove_carreira(BaseDados *db, int id_c){
    Carreira *c = db->carreiras->cabeca;
    while (c->id != id_c){
        c = c->next;
    }
    if (db->carreiras->cabeca->id==id_c){
        db->carreiras->cabeca = db->carreiras->cabeca->next;
        free(c->nome);
        free_lista_ID(c->id_paragens);
        free_lista_ID(c->id_ligacoes);
        free(c);
    }
    else{
        Carreira *ant = db -> carreiras->cabeca;
        while (ant->next->id!=id_c){
            ant = ant->next;
        }
        if(db->carreiras->cauda->id==id_c){
            db->carreiras->cauda = ant;
            ant->next = NULL;
        }
        else
            ant->next = c->next;
        free(c->nome);
        free_lista_ID(c->id_paragens);
        free_lista_ID(c->id_ligacoes);
        free(c);
    }
}

/*Função remove_ligacoes_carreira recebe uma base de dados e um id de uma
carreira e remove as ligacoes da carreira da base de dados*/
void remove_ligacoes_carreira(BaseDados *db, int id_c) {
    Ligacao *ligacao = db->ligacoes->cabeca;
    Ligacao *l_anterior = NULL;

    while (ligacao != NULL) {
        Ligacao *aux = ligacao;
        if (ligacao->id_carreira == id_c) {
            if (l_anterior == NULL) 
                db->ligacoes->cabeca = ligacao->next;
            else 
                l_anterior->next = ligacao->next;
            
            if (ligacao == db->ligacoes->cauda) 
                db->ligacoes->cauda = l_anterior;
            
            ligacao = ligacao->next;
            free(aux);
        } else {
            l_anterior= ligacao;
            ligacao = ligacao->next;
        }
    }
}

/*Função e_carreira comando principal de remoção de carreiras
recebe uma base de dados e um nome de uma carreira e remove a carreira*/
void e_carreira(BaseDados *db){
    char nome_carreira[INPUT_MAX];
    le_palavra(nome_carreira);
    if (verifica_carreira_exis(db,nome_carreira)==FALSE)
        printf("%s: no such line.\n",nome_carreira);
    else{
        int id_c = busca_id_carreira(db,nome_carreira);
        remove_ligacoes_carreira(db,id_c);
        remove_carreira(db,id_c);
    }
}

/*---------------------------------------------------------------------------*/
/*Funções remoção Paragens*/
/*Função remove_paragem recebe uma base de dados e um id de uma paragem
e remove a paragem da base de dados*/
void remove_paragem(BaseDados *db, int id_p){
    Paragem *p = db->paragens->cabeca;
    while (p->id != id_p){
        p = p->next;
    }
    if (db->paragens->cabeca->id==id_p){
        db->paragens->cabeca = db->paragens->cabeca->next;
        free(p->nome);
        free(p);
    }
    else{
        Paragem *ant = db -> paragens->cabeca;
        while (ant->next->id!=id_p){
            ant = ant->next;
        }
        if(db->paragens->cauda->id==id_p){
            db->paragens->cauda = ant;
            ant->next = NULL;
        }
        else
            ant->next = p->next;
        free(p->nome);
        free(p);
    }
}

/*Função reset_carreira recebe uma base de dados e uma carreira
e reinicia a carreira*/
void reset_carreira(BaseDados *db, Carreira * c){
    free_lista_ID(c->id_paragens);
    c->id_paragens = inicializa_lista_ID(db);
    c->n_paragens = 0;
    c->custo_total = 0;
    c->duracao_total = 0;
}

/*Função paragem_next recebe uma carreira e um id de uma paragem
e retorna o id da paragem seguinte*/
ID * paragem_next(Carreira *c, int id_p){
    ID *id = c->id_paragens->cabeca;
    while (id!=NULL){
        if (id->id==id_p)
            return id->next;
        id = id->next;
    }    return NULL;
}

/*Função paragem_ant recebe uma carreira e um id de uma paragem
e retorna o id da paragem anterior*/
ID* paragem_ant(Carreira *c, int id_p){
    ID *id = c->id_paragens->cabeca;
    ID *id_ant = NULL;
    while (id!=NULL){
        if (id->id==id_p)
            return id_ant;
        id_ant = id;
        id = id->next;
    }
    return NULL;
}
/*Função custo_ligacao recebe uma base de dados e um id de uma ligação
e retorna o custo da ligação*/ 
int custo_ligacao(BaseDados *db,int id_l){
    Ligacao *l = db->ligacoes->cabeca;
    while (l!=NULL){
        if (l->id==id_l)
            return l->custo;
        l = l->next;
    }
    return 0;
}
/*Função duracao_ligacao recebe uma base de dados e um id de uma ligação
e retorna a duração da ligação*/
int duracao_ligacao(BaseDados *db,int id_l){
    Ligacao *l = db->ligacoes->cabeca;
    while (l!=NULL){
        if (l->id==id_l)
            return l->duracao;
        l = l->next;
    }
    return 0;
}

/*Função busca_ligação recebe uma base de dados e um id de uma ligação
e retorna a ligação com o id dado*/
Ligacao * busca_ligacao(BaseDados *db, int id_l){
    Ligacao *l = db->ligacoes->cabeca;
    while (l!=NULL){
        if (l->id==id_l)
            return l;
        l = l->next;
    }
    return NULL;
}

/*Função ID_ligacao recebe uma base de dados, um id de uma carreira, 
um id de uma origem e um id de um destino e uma lista de ids de ligacoes
e retorna o id da ligacao que liga a origem ao destino*/
ID * ID_ligacao(BaseDados *db, int id_c, int id_origem, int id_destino, Lista_ID *l){
    ID *ID = l->cabeca;
    while (ID!=NULL){
        Ligacao *ligacao = busca_ligacao(db,ID->id);
        if (ligacao->id_carreira==id_c && ligacao->id_origem==id_origem && ligacao->id_destino==id_destino){
            return ID;
        }
        ID = ID->next;
    }
    return NULL;
}

/*Função cria_id cria um novo id para uma paragem ou ligação
recebe uma base de dados e um id e retorna um novo id*/
ID * cria_id (BaseDados *db ,int id){
    ID * novo_ID = malloc_controlado(db,sizeof(ID));
    novo_ID->id = id;
    return novo_ID;
}

/*Função remove_id_fim remove a última paragem da carreira e a sua ligação
recebe uma base de dados, uma carreira e um id de uma paragem*/
void remove_id_fim(BaseDados *db,Carreira *c, int id_p){
    ID *id_ant = paragem_ant(c,id_p);
    ID *ligacao = c->id_ligacoes->cauda;
    ID *paragem_remover = id_ant->next;

    int custo = custo_ligacao(db,ligacao->id);
    int duracao = duracao_ligacao(db,ligacao->id);
    
    c->n_paragens--;
    c->custo_total -= custo;
    c->duracao_total -= duracao;

    c->id_ligacoes->cauda = ligacao->previous;
    c->id_paragens->cauda = id_ant;
    id_ant->next = NULL;    
    c->id_ligacoes->cauda->next = NULL;

    free(ligacao);
    free(paragem_remover);
}

/*Função remove_id_inicio remove a primeira paragem da carreira 
e a primeira ligação da lista de ligações da carreira*/
void remove_id_inicio(BaseDados *db,Carreira *c, int id_p){
    ID *id_next = paragem_next(c,id_p);
    ID *ligacao = c->id_ligacoes->cabeca;
    ID *paragem_remover = c->id_paragens->cabeca;

    int custo = custo_ligacao(db,ligacao->id);
    int duracao = duracao_ligacao(db,ligacao->id);

    c->n_paragens--;
    c->custo_total -= custo;
    c->duracao_total -= duracao;
    
    c->id_ligacoes->cabeca = ligacao->next;
    c->id_paragens->cabeca = id_next;
    id_next->previous = NULL;
    c->id_ligacoes->cabeca->previous = NULL;

    free(ligacao);
    free(paragem_remover);
}

/*Função remove_id_meio recebe a carreira onde se vai remover a paragem,
e o id da paragem a remover.
A função liberta as ligações adjacentes à paragem a remover, e cria uma nova ligação
que irá ligar as duas ligacoes adjacentes às ligações a remover.*/
void liberta_id_meio(ID * id_ligacao_ant, ID* id_ligacao_next, ID * nova_ligacao_id){
    id_ligacao_ant->previous->next = nova_ligacao_id;
    nova_ligacao_id->previous = id_ligacao_ant->previous;
    id_ligacao_next->next->previous = nova_ligacao_id;
    nova_ligacao_id->next = id_ligacao_next->next;
    free(id_ligacao_ant);
    free(id_ligacao_next);
}

/*Função unica_ligacao recebe a carreira onde se vai remover a paragem,
e o id da nova ligação que irá subestituir as duas ligações removidas.
A nova ligação é colocada no inicio da lista de ligações da carreira, e será a unica
pois as ligações adjacentes à paragem a remover serão libertadas e estas os extremos da lista.*/
void unica_ligacao(Carreira *c , ID * nova_ligacao_id){
    c->id_ligacoes->cabeca = nova_ligacao_id;
    c->id_ligacoes->cauda = nova_ligacao_id;
    nova_ligacao_id->previous = NULL;
    nova_ligacao_id->next = NULL;
}
/*Função liberta_id_inicial recebe a base de dados e a carreira onde se vai remover a paragem,
e os ids das ligações adjacentes à paragem a remover. Recebe também o id da nova ligação
que irá subestituir as duas ligações removidas.Libertando as ligações adjacentes,
sendo um dos ids removidos do inicio da lista de ligações da carreira.*/
void liberta_id_inicial(Carreira *c ,ID * id_ligacao_ant, ID* id_ligacao_next, ID * nova_ligacao_id){
    c->id_ligacoes->cabeca = nova_ligacao_id;
    nova_ligacao_id->previous = NULL;
    free(id_ligacao_ant);
    id_ligacao_next->next->previous = nova_ligacao_id;                        
    nova_ligacao_id->next = id_ligacao_next->next;
    free(id_ligacao_next);
}

/*Função liberta_id_final recebe a base de dados e a carreira onde se vai remover a paragem,
e os ids das ligações adjacentes à paragem a remover. Recebe também o id da nova ligação
que irá subestituir as duas ligações removidas.Libertando as ligações adjacentes,
sendo um dos ids removidos do fim da lista de ligações*/
void liberta_id_final(Carreira *c ,ID * id_ligacao_ant, ID* id_ligacao_next, ID * nova_ligacao_id){
    c->id_ligacoes->cauda = nova_ligacao_id;
    nova_ligacao_id->next = NULL;
    free(id_ligacao_next);
    id_ligacao_ant->previous->next = nova_ligacao_id;
    nova_ligacao_id->previous = id_ligacao_ant->previous;
    free(id_ligacao_ant);
}

/*Função remove_id_meio recebe a base de dados e a carreira onde se vai remover a paragem, 
e o id da paragem a remover. Esta função irá criar uma nova ligação que corresponde à 
remoção dessa paragem inserida, sendo a nova origem e destino as paragens adjacentes 
à removida. Depois irá libertar os ids das ligações e a paragem que for removida, 
analisando a posição do id da paragem a remover na lista de ids das paragens.*/
void remove_id_meio(BaseDados *db,Carreira *c, int id_p){
    ID *id_ant = paragem_ant(c,id_p);
    ID *id_next = paragem_next(c,id_p);

    ID * id_ligacao_ant = ID_ligacao(db,c->id,id_ant->id,id_p,c->id_ligacoes);
    ID * id_ligacao_next = ID_ligacao(db,c->id,id_p,id_next->id,c->id_ligacoes);
    Ligacao * ligacao_ant = busca_ligacao(db,id_ligacao_ant->id);
    Ligacao * ligacao_next = busca_ligacao(db,id_ligacao_next->id);

    ID * paragem_remover;

    int duracao_ant = duracao_ligacao(db,ligacao_ant->id);
    int duracao_next = duracao_ligacao(db,ligacao_next->id);
    int custo_ant = custo_ligacao(db,ligacao_ant->id);
    int custo_next = custo_ligacao(db,ligacao_next->id);
    
    Ligacao *nova_ligacao;
    ID *nova_ligacao_id;

    int duracao = duracao_ant + duracao_next;
    int custo = custo_ant + custo_next;
    
    nova_ligacao = cria_ligacao(db,c->id,id_ant->id,id_next->id,duracao,custo);
    nova_ligacao_id = cria_id(db,nova_ligacao->id);

    c->n_paragens--;
    
    paragem_remover = id_ant->next;
    id_ant->next = id_next;
    id_next->previous = id_ant;
    
    free(paragem_remover);

    if (id_ligacao_ant->previous!=NULL && id_ligacao_next->next != NULL) {
        liberta_id_meio(id_ligacao_ant,id_ligacao_next,nova_ligacao_id);
    }
    else if (id_ligacao_ant->previous==NULL && id_ligacao_next->next == NULL){
        unica_ligacao(c,nova_ligacao_id);
        free(id_ligacao_ant);
        free(id_ligacao_next);
    }
    else if (id_ligacao_ant->previous==NULL && id_ligacao_next->next != NULL){
        liberta_id_inicial(c,id_ligacao_ant,id_ligacao_next,nova_ligacao_id);
    }
    else if (id_ligacao_ant->previous!=NULL && id_ligacao_next->next == NULL){
        liberta_id_final(c,id_ligacao_ant,id_ligacao_next,nova_ligacao_id);
    }
}

/*Função remove_id recebe a base de dados, a carreira e o id da paragem a remover
e analisa que caso se aplica para a remoção da paragem*/
void remove_id(BaseDados *db, Carreira *c, int id_p){
    ID*  id_next = paragem_next(c,id_p);
    ID* id_ant = paragem_ant(c,id_p);
    if (id_next==NULL && id_ant!=NULL){
        remove_id_fim(db,c,id_p);
    }
    else if (id_ant==NULL && id_next!=NULL){
        remove_id_inicio(db,c,id_p);
    }
    else if (id_next!=NULL && id_ant!=NULL){
        remove_id_meio(db,c,id_p);
    }
}
/*Função remove_ligacoes_paragem recebe a base de dados e o id da paragem a remover
iterando por todas as carreiras e por todos os ids das paragens de cada carreira
e removendo o id da paragem a remover*/
void remove_ligacoes_paragem(BaseDados *db, int id_p){
    Carreira *c = db->carreiras->cabeca;
    while (c!=NULL){
        ID *id = c->id_paragens->cabeca;
        while (id!=NULL){
            ID *id_next_to_remove = id->next;
            if (id->id==id_p){
                if (c->n_paragens==2){
                    reset_carreira(db,c);
                    break;
                }
                else
                    remove_id(db,c,id_p);
            }
            id = id_next_to_remove;
        }
        c = c->next;
    }
}

/*Função e_paragem recebe a base de dados e o nome da paragem a remover*/
void e_paragem(BaseDados *db){  
    char nome_paragem[INPUT_MAX];
    le_palavra(nome_paragem);
    if (verifica_paragem_exis(db,nome_paragem)==FALSE)
        printf("%s: no such stop.\n",nome_paragem);
    else{
        int id_p = busca_id_paragem(db,nome_paragem);
        remove_ligacoes_paragem(db,id_p);
        remove_paragem(db,id_p);
    }
}


/*---------------------------------------------------------------------------*/

/*Função comandos recebe a data base e encarrega-se de avaliar os comandos
inseridos pelo utilizador levando assim às funções respetivas*/
int comandos(BaseDados *db){
    char c;
    while ((c = getchar()) != EOF) {
        switch (c) {
        case 'q':
            free_all(db); /*Comando Limpa*/
            return FALSE; /*Fim do Programa*/
        case 'c':
            carreiras(db); /*Coamndo Carreiras*/
            return TRUE;
        case 'p':
            paragens(db); /*Comando Paragens*/
            return TRUE;
        case 'l':
            ligacoes(db); /*Comando Ligacoes*/
            return TRUE;
        case 'i':
            nos(db);   /*Comando Nos*/
            return TRUE;
        case 'r':
            e_carreira(db); /*Comando Remover Carreira*/
            return TRUE;
        case 'e':
            e_paragem(db); /*Comando Remover Paragem*/
            return TRUE;
        case 'a':
            reset(db); /*Comando Apaga todos dados*/
            return TRUE;
        }
    }
    return 0;
}

/*---------------------------------------------------------------------------*/
/*Funções de limpeza*/

void free_all(BaseDados *db){
    free_lista_carreiras(db);
    free_lista_paragens(db);
    free_lista_ligacoes(db);
    free(db);
}

void free_lista_paragens(BaseDados *db){
    Paragem *p = db->paragens->cabeca;
    Paragem *aux;
    while (p!=NULL){
        free(p->nome);
        aux = p;
        p = p->next;
        free(aux);
    }
    free(db->paragens);
}

void free_lista_carreiras(BaseDados *db){
    Carreira *c = db->carreiras->cabeca;
    Carreira *aux;
    while (c!=NULL){
        free_lista_ID(c->id_paragens);
        free_lista_ID(c->id_ligacoes);
        free(c->nome);
        aux = c;
        c = c->next;
        free(aux);
    }
    free(db->carreiras);
}
        
void free_lista_ID(Lista_ID *lista){
    ID *id = lista->cabeca;
    while (id!=NULL){
        ID *aux = id;
        id = id->next;
        free(aux);
    }
    free(lista);
}

void free_lista_ligacoes(BaseDados *db){
    Ligacao *l = db->ligacoes->cabeca;
    while (l!=NULL){
        Ligacao *aux = l;
        l = l->next;
        free(aux);
    }
    free(db->ligacoes);
}

/*Função reser rescebe a base de dados e faz reset da mesma*/
void reset(BaseDados *db){
    free_lista_carreiras(db);
    free_lista_paragens(db);
    free_lista_ligacoes(db);
    db->n_carreiras = 0;
    db->n_paragens = 0;
    db->n_ligacoes = 0;
    db->carreiras = inicializa_lista_carreiras(db);
    db->paragens = inicializa_lista_paragens(db);
    db->ligacoes = inicializa_lista_ligacoes(db);
}
   
/*---------------------------------------------------------------------------*/
/*Funções de inicialização*/

/*Todas as funções seguintes recebem a data base e irâo inicializar todo o tipo
de listas usadas ao longo do codigo*/

Lista_C *inicializa_lista_carreiras(BaseDados *db){
    Lista_C * lista= (Lista_C*)malloc_controlado(db,sizeof(Lista_C));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    return lista;
}

Lista_P *inicializa_lista_paragens(BaseDados *db){
    Lista_P * lista= (Lista_P*)malloc_controlado(db,sizeof(Lista_P));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    return lista;
}

Lista_ID *inicializa_lista_ID(BaseDados *db){
    Lista_ID * lista= (Lista_ID*)malloc_controlado(db,sizeof(Lista_ID));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    return lista;
}

Lista_L *inicializa_lista_ligacoes(BaseDados *db){
    Lista_L * lista= (Lista_L*)malloc_controlado(db,sizeof(Lista_L));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    return lista;
}

Lista_Nomes *inicializa_lista_nomes(BaseDados *db){
    Lista_Nomes * lista= (Lista_Nomes*)malloc_controlado(db,sizeof(Lista_Nomes));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    return lista;
}

/*---------------------------------------------------------------------------*/
/*Main*/

/*Função main irá inicializar a data base e as respetivas listas da mesma*/
int main(){
    BaseDados *db= (BaseDados*)malloc(sizeof(BaseDados));

    db->n_carreiras = 0;
    db->n_paragens = 0;
    db->n_ligacoes = 0;

    db->paragens = inicializa_lista_paragens(db);
    db->carreiras = inicializa_lista_carreiras(db);
    db->ligacoes = inicializa_lista_ligacoes(db);

    while(comandos(db)==TRUE);
    
    return 0;
}
/*---------------------------------------------------------------------------*/