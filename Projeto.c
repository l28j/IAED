/* iaed-23 - ist1106221 - project1 */

/*Joao Lucas Morais Cardoso Tavares Rodrigues*/

/*Bibliotecas*/


#include <string.h>
#include <stdio.h>

/*Constantes*/

#define COM_MAX_CARREIRA 20
#define COM_MAX_PARAGEM 50
#define CARREIRA_MAX 200
#define PARAGEM_MAX 10000
#define LIGACAO_MAX 30000
#define INPUT_MAX 81927
#define TRUE 1
#define FALSE 0

/*Estruturas*/

typedef struct{
    int id;
    char nome[COM_MAX_PARAGEM];   /*Struct de Paragens*/
    double lat;
    double lon;
}Paragem;

typedef struct{
    char nome[COM_MAX_CARREIRA];
    double custo_total_carreira;
    double duracao_total_carreira;      /*Struct de Carreiras*/
    int n_paragens_carreira;
    int id_paragens_carreira[PARAGEM_MAX];
}Carreira;

/*---------------------------------------------------------------------------*/

/*Variaveis Globais*/

int numero_carreiras = 0;
Carreira all_carreiras[CARREIRA_MAX];  /*Vetor que armazena todas as Carreiras*/
int id = 0;
int numero_paragens = 0;
Paragem all_paragens[PARAGEM_MAX];     /*Vetor que armazena todas as Paragens*/
    

/*---------------------------------------------------------------------------*/

/*Funcoes Auxiliares*/

/*Funcao le_palavras ignora todos os espacos/tabs e guarda 
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
    return (c != '\n');     /* retorna 1 se nao chegou ao fim da linha */

}


/*Funcao Inverso recebe um vetor sendo uma string e retorna TRUE ou FALSE,se 
a palavra inserida for correspondente a inverso ou a uma abreviacao do mesmo*/
int Inverso(char str[]){

    if(strcmp(str,"inverso")==0 ||strcmp(str,"invers")==0 
    ||strcmp(str,"inver")==0 ||strcmp(str,"inve")==0      
    ||strcmp(str,"inv")==0){
        return TRUE;                    
    }
    return FALSE;
}

/*Funcao busca_nome_p recebe o indice da paragem e retorna o nome correspondente */
char * busca_nome_p(int id, char nome_paragem[]){
    int i;
    for (i=0;i<numero_paragens;i++){  /*Procura o nome da paragem correspondente ao id*/
        if (all_paragens[i].id==id){
            strcpy(nome_paragem,all_paragens[i].nome); /*Copia o nome da paragem para a string nome_paragem*/
        }
    }
    return nome_paragem;
}


/*Funcao busca_id_paragem recebe o nome da paragem e retorna o id correspondente*/
int busca_id_paragem(char nome_paragem[]){
    int i;
    for (i=0;i<numero_paragens;i++){ /*Procura o id da paragem correspondente ao nome*/
        if (strcmp(all_paragens[i].nome,nome_paragem)==0){ /*Compara o nome inserido*/
            return all_paragens[i].id; 
        }
    }
    return -1;
}

int busca_n_paragens_carreira(int id_c){
    int n_paragens=all_carreiras[id_c].n_paragens_carreira;
    return n_paragens;
}

int busca_id_carreira(char nome_carreira[]){
    int i;
    for(i=0;i<numero_carreiras;i++){
        if (strcmp(nome_carreira,all_carreiras[i].nome)==0)
            return i;
    }
    return 0;
}


int count_carreiras(char nome_paragem[]){
    int i,j;
    int count=0;
    int id=busca_id_paragem(nome_paragem);

    for(i=0;i<numero_carreiras;i++){
        for(j=0;j<all_carreiras[i].n_paragens_carreira;j++){
            if (id==all_carreiras[i].id_paragens_carreira[j]){
                count ++;
                break;
            }
        }
    }
    return count;
}

/*---------------------------------------------------------------------------*/

/*____________________________Carreiras______________________________________*/


void mostracarreira(int i){
    char nome_paragem_origem[COM_MAX_PARAGEM];
    char nome_paragem_destino[COM_MAX_PARAGEM];
    if ((all_carreiras[i].n_paragens_carreira)!=0){
        printf("%s %s %s ",all_carreiras[i].nome,
        busca_nome_p(all_carreiras[i].id_paragens_carreira[0],nome_paragem_origem),
        busca_nome_p(all_carreiras[i].id_paragens_carreira[all_carreiras[i].n_paragens_carreira-1],nome_paragem_destino));
        printf("%d %.2f %.2f\n",all_carreiras[i].n_paragens_carreira,
        all_carreiras[i].custo_total_carreira,all_carreiras[i].duracao_total_carreira);
    }
    else
        printf("%s %d %.2f %.2f\n",all_carreiras[i].nome,all_carreiras[i].n_paragens_carreira,
        all_carreiras[i].custo_total_carreira,all_carreiras[i].duracao_total_carreira);

}

void lista_carreiras_sistema(){
    int i;
    for (i=0;i<numero_carreiras;i++){
        mostracarreira(i);
    }
}

int verifica_carreira_existente(char nome_carreira[]){
    int i;
    for (i=0;i<numero_carreiras;i++){
        if (strcmp(all_carreiras[i].nome,nome_carreira)==0){
            return TRUE;
        }
    }
    return FALSE;
}


void lista_paragens_carreira(char nome_carreira[]){
    int i;
    char nome_paragem[COM_MAX_PARAGEM];
        for (i=0;i<numero_carreiras;i++){
            if (strcmp(all_carreiras[i].nome,nome_carreira)==0 && all_carreiras[i].n_paragens_carreira!=0){
                int j;
                printf("%s",busca_nome_p(all_carreiras[i].id_paragens_carreira[0],nome_paragem));
                for (j=1;j<all_carreiras[i].n_paragens_carreira;j++){
                    printf(", %s",busca_nome_p(all_carreiras[i].id_paragens_carreira[j],nome_paragem));           
                }
                putchar('\n');
            }
        }
}


void lista_paragens_carreira_inv(char nome_carreira[]){
    int i;
    char nome_paragem[COM_MAX_PARAGEM];
    for (i=0;i<numero_carreiras;i++){
        if (strcmp(all_carreiras[i].nome,nome_carreira)==0 && all_carreiras[i].n_paragens_carreira!=0){
            int j;
            printf("%s",busca_nome_p(all_carreiras[i].id_paragens_carreira[all_carreiras[i].n_paragens_carreira-1],nome_paragem));
            for (j=all_carreiras[i].n_paragens_carreira-2;j>=0;j--){
                printf(", %s",busca_nome_p(all_carreiras[i].id_paragens_carreira[j],nome_paragem));            
                
            }
            putchar('\n');
        }
    }

}
void add_carreiras(char nome_carreira[]){
    
    strcpy(all_carreiras[numero_carreiras].nome,nome_carreira);
    all_carreiras[numero_carreiras].custo_total_carreira=0;
    all_carreiras[numero_carreiras].duracao_total_carreira=0;
    all_carreiras[numero_carreiras].n_paragens_carreira=0;
    numero_carreiras++;
}



void carreiras(){
    int c;
    if ((c=getchar())=='\n'){
        lista_carreiras_sistema();
    }
    else{
        char nome_carreira[COM_MAX_CARREIRA];
        if(!le_palavra(nome_carreira)){
            if (verifica_carreira_existente(nome_carreira)==TRUE){
                lista_paragens_carreira(nome_carreira);
            }
            else{
                add_carreiras(nome_carreira);
            }
        }
        else{
            char ordem[INPUT_MAX];
            le_palavra(ordem);
            if (Inverso(ordem)==TRUE){
                lista_paragens_carreira_inv(nome_carreira);
            }
            else{
                printf("incorrect sort option.\n");
            }
        }
    }
}

                
/*---------------------------------------------------------------------------*/

/*____________________________Paragens______________________________________*/

void lista_paragens_sistema(){
    int i;
    for (i=0;i<numero_paragens;i++){
        printf("%s: %16.12f %16.12f %d\n",all_paragens[i].nome,all_paragens[i].lat,all_paragens[i].lon,
        count_carreiras(all_paragens[i].nome));
    }
}

int verifica_paragem_exis(char nome_paragem[]){
    int i;
    for (i=0;i<numero_paragens;i++){
        if (strcmp(all_paragens[i].nome,nome_paragem)==0){
            return TRUE;
        }
    }
    return FALSE;
}

void add_paragem(char nome_paragem[],double latitude,double longitude){

    strcpy(all_paragens[numero_paragens].nome,nome_paragem);
    all_paragens[numero_paragens].lat=latitude;
    all_paragens[numero_paragens].lon=longitude;
    all_paragens[numero_paragens].id=id;
    id++;
    numero_paragens++;
}

void mostraparagem(char nome_paragem[]){
    int i;
    for (i=0;i<numero_paragens;i++){
        if (strcmp(all_paragens[i].nome,nome_paragem)==0){
            printf("%16.12f %16.12f\n",all_paragens[i].lat,all_paragens[i].lon);
        }
    }
}
    


void paragens(){
    int c;
    if ((c=getchar())=='\n'){
        lista_paragens_sistema();
    }
    else{
        char nome_paragem[COM_MAX_PARAGEM];
        if (le_palavra(nome_paragem)){
            if (verifica_paragem_exis
        (nome_paragem)==TRUE){
                printf("%s: stop already exists.\n",nome_paragem);
            }
            else{
                int in;
                double latitude,longitude;
                in = scanf("%lf %lf",&latitude,&longitude);
                if (in==2){
                    add_paragem(nome_paragem,latitude,longitude);
                }
            }
        }
        else {
            if (verifica_paragem_exis
        (nome_paragem)==TRUE){
                mostraparagem(nome_paragem); 
            }
            else{
                printf("%s: no such stop.\n",nome_paragem);
            }
        }
    }
}


/*---------------------------------------------------------------------------*/

/*____________________________Ligacoes_______________________________________*/

void add_ligacao(int id_c,char nome_paragem_origem[],char nome_paragem_destino[],double custo,double duracao){

    int id_origem;
    int id_destino;
    int numero_paragens;
    int id_nova_origem;
    int id_novo_destino;

    numero_paragens=busca_n_paragens_carreira(id_c);
    
    id_origem=all_carreiras[id_c].id_paragens_carreira[0];
    id_destino=all_carreiras[id_c].id_paragens_carreira[numero_paragens-1];

    id_nova_origem=busca_id_paragem(nome_paragem_origem);
    id_novo_destino=busca_id_paragem(nome_paragem_destino);

    if (numero_paragens==0){
        all_carreiras[id_c].id_paragens_carreira[0]=busca_id_paragem(nome_paragem_origem);
        all_carreiras[id_c].id_paragens_carreira[1]=busca_id_paragem(nome_paragem_destino);
        all_carreiras[id_c].custo_total_carreira+=custo;
        all_carreiras[id_c].duracao_total_carreira+=duracao;
        all_carreiras[id_c].n_paragens_carreira+=2;

    }
    else if( id_destino==id_nova_origem && id_origem==id_novo_destino){
        all_carreiras[id_c].id_paragens_carreira[numero_paragens]=id_novo_destino;
        all_carreiras[id_c].custo_total_carreira+=custo;
        all_carreiras[id_c].duracao_total_carreira+=duracao;
        all_carreiras[id_c].n_paragens_carreira+=1;
    }

    else if( id_destino==id_nova_origem){
        all_carreiras[id_c].id_paragens_carreira[numero_paragens]=id_novo_destino;
        all_carreiras[id_c].custo_total_carreira+=custo;
        all_carreiras[id_c].duracao_total_carreira+=duracao;
        all_carreiras[id_c].n_paragens_carreira+=1;
    }

    else if( id_origem==id_novo_destino){
        int j;
        for(j=numero_paragens;j>0;j--){
            all_carreiras[id_c].id_paragens_carreira[j]=all_carreiras[id_c].id_paragens_carreira[j-1];
        }
        all_carreiras[id_c].id_paragens_carreira[0]=id_nova_origem;
        all_carreiras[id_c].custo_total_carreira+=custo;
        all_carreiras[id_c].duracao_total_carreira+=duracao;
        all_carreiras[id_c].n_paragens_carreira+=1;

    }
}



int verifica_destino(int id_c,char novo_destino[]){
    int id_p=busca_id_paragem(novo_destino);

    if(all_carreiras[id_c].id_paragens_carreira[0]==id_p)
        return TRUE;
    return FALSE;
}

int verifica_origem(int id_c,char nova_origem[],int num_paragens){
    int id_p=busca_id_paragem(nova_origem);

    if(all_carreiras[id_c].id_paragens_carreira[num_paragens-1]==id_p)
        return TRUE;
    return FALSE;
}


void ligacoes(){
    char nome_carreira[COM_MAX_CARREIRA];
    char nome_paragem_origem[COM_MAX_PARAGEM];
    char nome_paragem_destino[COM_MAX_PARAGEM];

    double custo,duracao;

    le_palavra(nome_carreira);
    le_palavra(nome_paragem_origem);
    le_palavra(nome_paragem_destino);


    scanf("%lf %lf",&custo,&duracao);


    if(verifica_carreira_existente(nome_carreira)==FALSE){
        printf("%s: no such line.\n",nome_carreira);
    }
    else{
        if(verifica_paragem_exis(nome_paragem_origem)==FALSE)
            printf("%s: no such stop.\n",nome_paragem_origem);
        else if(verifica_paragem_exis(nome_paragem_destino)==FALSE)
            printf("%s: no such stop.\n",nome_paragem_destino);
        else{
            int id_c=busca_id_carreira(nome_carreira);
            int num_paragens=busca_n_paragens_carreira(id_c);
            if(num_paragens==0){
                if(custo<0 || duracao<0){
                    printf("negative cost or duration.\n");
                }
                else
                    add_ligacao(id_c,nome_paragem_origem,nome_paragem_destino,custo,duracao);
            }
            else{
                if( verifica_destino(id_c,nome_paragem_destino)==TRUE  
                    || verifica_origem(id_c,nome_paragem_origem,num_paragens)==TRUE)
                        if(custo<0 || duracao<0)
                            printf("negative cost or duration.\n");
                        else
                            add_ligacao(id_c,nome_paragem_origem,nome_paragem_destino,custo,duracao);
                else
                    printf("link cannot be associated with bus line.\n");
            }
        }
    }
}


/*---------------------------------------------------------------------------*/

/*___________________________________Nos_____________________________________*/



int paragens_c_nos(char nome_paragens[][COM_MAX_PARAGEM]){
    int i,count=0;
    int n_paragens=0;

    for(i=0;i<numero_paragens;i++){

        count=count_carreiras(all_paragens[i].nome);

        if (count!=1){
            strcpy(nome_paragens[n_paragens],all_paragens[i].nome);
            n_paragens++;
        }
    }
    return n_paragens;
}
int verifica_paragem_carreira(char nome_paragem[],char nome_carreira[]){
    int i,id_p,id_c;
    id_p=busca_id_paragem(nome_paragem);
    id_c=busca_id_carreira(nome_carreira);
    for(i=0;i<all_carreiras[id_c].n_paragens_carreira;i++){
        if(all_carreiras[id_c].id_paragens_carreira[i]==id_p)
            return TRUE;
    }
    return FALSE;
}

int carreiras_paragem(char nome_carreiras[][COM_MAX_CARREIRA],char nome_paragem[]){
    int i;
    int n_carreiras=0;
    for(i=0;i<numero_carreiras;i++){
        if(verifica_paragem_carreira(nome_paragem,all_carreiras[i].nome)==TRUE){
            strcpy(nome_carreiras[n_carreiras],all_carreiras[i].nome);
            n_carreiras++;
        }
    }
    return n_carreiras;
}



void insertionSort(char arr[][COM_MAX_CARREIRA], int n_carreiras) {
   int i, j;
   char key[COM_MAX_CARREIRA];

   for (i = 1; i < n_carreiras; i++) {
       strcpy(key, arr[i]);
       j = i - 1;

       while (j >= 0 && strcmp(arr[j], key) > 0) {
           strcpy(arr[j + 1], arr[j]);
           j = j - 1;
       }

       strcpy(arr[j + 1], key);
    }

}


void nos(){
    char nomes_paragens[PARAGEM_MAX][COM_MAX_PARAGEM];
    char nomes_carreiras[CARREIRA_MAX][COM_MAX_CARREIRA];
    int n_paragens;
    int i,j;
    int n_carreiras;
    n_paragens =paragens_c_nos(nomes_paragens);

    for (i=0;i<n_paragens;i++){

        n_carreiras=carreiras_paragem(nomes_carreiras,nomes_paragens[i]);

        if (n_carreiras>1) {
            insertionSort(nomes_carreiras,n_carreiras);
            printf("%s %d:",nomes_paragens[i],n_carreiras);

            for(j=0;j<n_carreiras;j++){
                printf(" %s",nomes_carreiras[j]);
            }
            printf("\n");
        }
    }

}
    
/*---------------------------------------------------------------------------*/

/*____________________________Main___________________________________________*/


int main(){
    int c;
	while ((c = getchar()) != EOF) {
        switch (c) {
        case 'q':
            return 0;
            break;
        case 'c':
            carreiras();
            break;
        case 'p':
            paragens();
            break;
        case 'l':
           ligacoes();
            break;
        case 'i':
            nos();
            break;
        }
    }
	return 0;
}

/*---------------------------------------------------------------------------*/