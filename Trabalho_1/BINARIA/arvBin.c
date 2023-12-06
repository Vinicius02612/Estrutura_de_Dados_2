#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "arvBin.h"


// struct para criar lista de participantes
typedef struct participantes
{
    int id;
    char nomeArtista[50];
    char nomePersonagem[50];
    char descricao[50];
    Participantes *proximo;
}Participantes;


typedef struct arvoreSerie{
    int codigo;
    char titulo[50];
    int numeroDeTemporada;
    ArvoreTemporada *temporada;
    ArvoreSerie *esq, *dir;
}ArvoreSerie;


typedef struct arvoreTemporada{
    int codigo;
    int numTem;
    char titulo[50];
    int quantEp;
    char ano[50];
    Participantes *participante;
    ArvoreTemporada *esq, *dir;
}ArvoreTemporada;



ArvoreSerie *criarArvoreSerie(){
    return NULL;
}

ArvoreTemporada *criaAvoreTemporada(){
    return NULL;
}

Participantes *criaListaParticipante(){
    /* Participantes *lista = (Participantes*)malloc(sizeof(Participantes));
    if(lista != NULL)
        return lista; */
    return NULL;
}
// inserir participante da temporada

ArvoreSerie *lerDadosSerie(){
    ArvoreSerie *dado = (ArvoreSerie*)malloc(sizeof(ArvoreSerie));
    printf("Codigo:");
    scanf("%d", &dado->codigo);
    printf("Titulo da serie:");
    scanf("%s", dado->titulo);
    return dado;
}

ArvoreTemporada *lerDadoTemporada(){
    ArvoreTemporada *dado = (ArvoreTemporada*)malloc(sizeof(ArvoreTemporada));
    printf("Codigo da temporada: \n");
    scanf("%d", &dado->codigo);
    printf("Número da temporada: ");
    scanf("%d", &dado->numTem);
    printf("Quantidade de episódios: ");
    scanf("%d", &dado->quantEp);
    printf("Título da temporada: ");
    scanf("%s", dado->titulo);
    printf("Ano da temporada: ");
    scanf("%s", dado->ano);

    return dado;
}

Participantes *lerDadosParticipante(){
    Participantes *dado = (Participantes*)malloc(sizeof(Participantes));

    printf("Id do artista: \n");
    scanf("%d", &dado->id);
    printf("Nome do artista:\n");
    scanf("%s", dado->nomeArtista);
    printf("Nome do Personagem: \n");
    scanf("%s", dado->nomePersonagem);
    printf("Descricao: \n");
    scanf("%s", dado->descricao);

    return dado;

}

Participantes *insereParticipante(Participantes *lista, Participantes *dadoParticipante){
    Participantes *auxParicipante = (Participantes*)malloc(sizeof(Participantes));
    if(auxParicipante != NULL){
        
        auxParicipante = dadoParticipante;

        if(lista == NULL){ // caso a lista esteja vazia e é o primeiro elemento a ser inserido
            auxParicipante->proximo = NULL;
            lista = auxParicipante;
        }else{

            Participantes *ant, *atual = (Participantes*)malloc(sizeof(Participantes));
            while(atual != NULL && strcmp(atual->nomeArtista, lista->nomeArtista) < 0  ){
                ant = atual;
                atual = atual->proximo;
            }
            if(atual == NULL){
                auxParicipante->proximo = lista;
                lista = auxParicipante;
            }else{
                auxParicipante->proximo = atual;
                ant->proximo = auxParicipante;
            }
        }
        
    }

    return lista;
}


void buscaParticipantes(Participantes *lista,char nomePersonagem[]){
    Participantes *aux = lista;
    while (aux != NULL && aux->nomePersonagem == nomePersonagem)
    {
        imprimeParticipante(aux);
        aux = aux->proximo;
    }
}

// insere os dados da temporada
ArvoreTemporada *insereTemporada(ArvoreTemporada **raiz, ArvoreTemporada *Dado){
    Participantes  *lista =  criaListaParticipante();
    Participantes *dadoParicipante;
    int sco, i = 0;
    if(*raiz == NULL){
        (*raiz) = (ArvoreTemporada*)malloc(sizeof(ArvoreTemporada));
        (*raiz) = Dado;

        printf("Insira os dados do participante!\n\n Quantos participantes deseja inserir? \n");
        scanf("%d", &sco);
        while (i < sco)
        {
            dadoParicipante = lerDadosParticipante();
            (*raiz)->participante = insereParticipante(lista, dadoParicipante);
            i++;
        }
        
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
    }else{
        if((*Dado).numTem < (*raiz)->numTem)
            insereTemporada(&((*raiz)->esq), Dado);
        else
            insereTemporada(&((*raiz)->dir), Dado);
    }

    return *raiz;
}

// insere dados da serie na arvore
void inserirSeries(ArvoreSerie **raiz, ArvoreSerie *DadoSerie){
    ArvoreTemporada  *raizT = criaAvoreTemporada();
    ArvoreTemporada *dadoTemporada;
    int sco, i = 0;
    if(*raiz == NULL){
        (*raiz) = (ArvoreSerie*)malloc(sizeof(ArvoreSerie));
        (*raiz) = DadoSerie;
        (*raiz)->numeroDeTemporada = 0;
        
        printf("Insira os dados da temporada!\n\n Quantas temporadas deseja inserir? \n");
        scanf("%d", &sco);
        while (i < sco)
        {
            dadoTemporada = lerDadoTemporada();
            (*raiz)->temporada = insereTemporada(&raizT, dadoTemporada);
            (*raiz)->numeroDeTemporada += 1;

            i++;
        }
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
    }else{
        if((*DadoSerie).codigo < (*raiz)->codigo)
            inserirSeries(&((*raiz)->esq),DadoSerie );
        else
            inserirSeries(&((*raiz)->dir),DadoSerie );
    }
}

// funcão que buscar uma series com base em seu codigo
ArvoreSerie *BuscarSeries( ArvoreSerie *raizS, int codigo){
    ArvoreSerie *serieBusca;
    if(raizS !=NULL){
        if(codigo == raizS->codigo){
            serieBusca =  raizS;
        }else if(codigo < raizS->codigo){
            serieBusca = BuscarSeries(raizS->esq, codigo);
        }else{
            serieBusca = BuscarSeries(raizS->dir, codigo);
        }
    }
    
}


void imprimeParticipante(Participantes *lista){
    Participantes *aux = lista;
    if(lista != NULL){
        printf("\n");
        while (aux != NULL){
            printf("\nNome do artista: %s\nNome do Personagem: %s\nDescricao: %s\n", aux->nomeArtista, aux->nomePersonagem, aux->descricao);
            aux = aux->proximo;
        }
    }
}
// imprimindo os dados da arvore serie de forma crescente...
void imprimeArvoreSeries(ArvoreSerie *raiz){

    if(raiz != NULL){
        printf("\n");
        imprimeArvoreSeries(raiz->esq);
        printf("Codigo: %d\n", raiz->codigo);
        printf("Numero de temporada: %d\n", raiz->numeroDeTemporada);
        printf("Titulo: %s\n", raiz->titulo);
        printf("Temporada: ");
        imprimeArvoreTemporada(raiz->temporada);    
        imprimeArvoreSeries(raiz->dir);
        printf("\n");
    }
}

void imprimeArvoreTemporada(ArvoreTemporada *raiz){
    if(raiz != NULL){
        printf("\n");
        imprimeArvoreTemporada(raiz->esq);
        printf("\tNumero da temporada: %d \n", raiz->numTem);
        printf("\t  titulo: %s \n", raiz->titulo);
        printf("\t quantidade de epsodio: %d \n", raiz->quantEp);
        printf("\t Numero da ano: %s \n", raiz->ano);
        imprimeArvoreTemporada(raiz->dir);
        printf("\n");
    }
}

// b Imprimir os dados de todas as temporadas de uma série, cujo o usuário informe o código da série.
void imprimeTemporadaDeUmaSerie(ArvoreSerie *raizS, int codigo){
    ArvoreSerie *aux =  BuscarSeries(raizS, codigo);
    if(aux != NULL){
        imprimeArvoreTemporada(aux->temporada);
    }
}

// personagem de uma temporara pelo codigo e numero da temporada
void imprimirPersonagensDeUmaTemporada(ArvoreSerie *raizS, int codigo, int NumeroTemporada ){
    if(raizS != NULL){
        if(raizS->codigo == codigo && raizS->temporada->numTem == NumeroTemporada){
            imprimeParticipante(raizS->temporada->participante);
        }
    }
}

// 
void imprimirNomeDeUmArtista(ArvoreSerie *raizS, char nomePersonagem[]){
    if(raizS != NULL ){
        imprimeParticipante(raizS->temporada->participante);
    }
}

void imprimeTemporada(ArvoreTemporada temporada){
    printf("\n\tNumero da temporada: %d\n\tTitulo: %s\n\tQuantidade de episódios: %d\n\tAno: %s\n", temporada.numTem, temporada.titulo, temporada.quantEp, temporada.ano);
}

void imprimeSeries(ArvoreSerie serie){
    printf(" Codigo: %d\n Titulo: %s\n Numero de temporadas: %d\n Temporadas:\n",serie.codigo, serie.titulo, serie.numeroDeTemporada);
    imprimeArvoreTemporada(serie.temporada);
}


void imprimeSeriesPeloCodigo(ArvoreSerie *raiz, int codigo){
    ArvoreSerie *aux = BuscarSeries(raiz, codigo);
    if(aux->codigo == codigo){
        printf(" Codigo: %d\n Titulo: %s\n Quantidade de Epsodio: %d\n Temporadas:\n",aux->codigo, aux->titulo, aux->numeroDeTemporada);
        imprimeArvoreTemporada(aux->temporada);
    }
   
}



/* 

void imprimir_participantes_determinada_temp(ArvoreTemporada *raiz){
      Participantes *atual = raiz->temporada;
      
      printf("\nParticipantes da Temporada %d:\n", temp->numTem);

      while (atual != NULL){
      {
            imprimeParticipante(atual);
      }
} */