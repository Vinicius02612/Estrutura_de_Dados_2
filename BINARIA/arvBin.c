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

//struct para armazenar dados da temporada
typedef struct dadoTemporada{
    int numTem;
    char titulo[50];
    int quantEp;
    char ano[50];
    Participantes *participante;
}DadoTemporada;


// struct para armazenar apenas os dados de cada series
typedef struct dadoSerie{
    int codigo;
    char titulo[50];
    int numeroDeTemporada;
    ArvoreTemporada *temporada;
}DadoSeries;


// arvore da serie que tem como dado  a TAD do tipo DadoSerie
typedef struct arvoreSerie{
    DadoSeries dado;
    ArvoreSerie *esq, *dir;
}ArvoreSerie;

//arvore temporada que tem como dado a TAD do tipo DadoTemporada
typedef struct arvoreTemporada{
    DadoTemporada  temporada;
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
Participantes *insereParticipante(Participantes *lista, int id, char nomeDoArtista[], char nomeDoPersongem[], char descricao[]){
    Participantes *auxParicipante = (Participantes*)malloc(sizeof(Participantes));
    if(auxParicipante != NULL){
        auxParicipante->id = id;
        strcpy(auxParicipante->nomeArtista, nomeDoArtista);
        strcpy(auxParicipante->nomePersonagem, nomeDoPersongem);
        strcpy(auxParicipante->descricao, descricao);

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

Participantes *buscaParticipantes(Participantes *lista, int id){
    Participantes *aux = lista;
    while (aux != NULL)
    {
        if(aux->id == id){
            return aux;
        }
        aux = aux->proximo;
    }
}

// insere os dados da temporada
void insereTemporada(ArvoreTemporada **raiz,int numTemp, char tituloTemp[], int quantEpisodio, char ano[]){

    if(*raiz == NULL){
        (*raiz) = (ArvoreTemporada*)malloc(sizeof(ArvoreTemporada));
        (*raiz)->temporada.numTem = numTemp;
        strcpy((*raiz)->temporada.titulo, tituloTemp);
        (*raiz)->temporada.quantEp = quantEpisodio;
        strcpy((*raiz)->temporada.ano, ano);
        (*raiz)->temporada.participante = NULL;

        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
    }else{
        if(numTemp < (*raiz)->temporada.numTem)
            insereTemporada(&((*raiz)->esq), numTemp, tituloTemp, quantEpisodio, ano);
        else
            insereTemporada(&((*raiz)->dir), numTemp, tituloTemp, quantEpisodio, ano);
    }
}

// insere dados da serie na arvore
void inserirSeries(ArvoreSerie **raiz, int codigo, int numeroTemporada, char titulo[]){
    if(*raiz == NULL){
        (*raiz) = (ArvoreSerie*)malloc(sizeof(ArvoreSerie));
        (*raiz)->dado.codigo = codigo;
        (*raiz)->dado.numeroDeTemporada = numeroTemporada;
        strcpy((*raiz)->dado.titulo, titulo);
        (*raiz)->dado.codigo = codigo;
        (*raiz)->dado.temporada = NULL;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
    }else{
        if(codigo < (*raiz)->dado.codigo)
            inserirSeries(&((*raiz)->esq), codigo, numeroTemporada, titulo);
        else
            inserirSeries(&((*raiz)->dir),codigo, numeroTemporada, titulo );
    }
}

// funcão que buscar uma series com base em seu codigo
ArvoreSerie *BuscarSeries( ArvoreSerie *raizS, int codigo){
    if(raizS !=NULL){
        if(codigo == raizS->dado.codigo){
            return raizS;
        }else if(codigo < raizS->dado.codigo){
            return BuscarSeries(raizS->esq, codigo);
        }else{
            return BuscarSeries(raizS->dir, codigo);
        }
    }
}

// função que insere a temporada na arvore de seires
ArvoreSerie *insereTemporadaNaSerie(ArvoreSerie *raizS, ArvoreTemporada *raizT, int codigo){
    ArvoreSerie *aux = BuscarSeries(raizS, codigo);
    printf(" Codigo encontrado: %d\n", aux->dado.codigo);
    if(aux != NULL && aux->dado.codigo == codigo){
        aux->dado.temporada = raizT;
    }
    return aux;
}

void imprimeParticipante(Participantes *lista){
    Participantes *aux = lista;
    if(lista != NULL){
        while (aux != NULL){
            printf("Nome do artista: %s\nNome do Personagem: %s\nDescricao: %s\n", aux->nomeArtista, aux->nomePersonagem, aux->descricao);
            aux = aux->proximo;
        }
    }
}

void imprimeTemporada(DadoTemporada temporada){
    printf("\n\tNumero da temporada: %d\n\tTitulo: %s\n\tQuantidade de episódios: %d\n\tAno: %s\n", temporada.numTem, temporada.titulo, temporada.quantEp, temporada.ano);
}

void imprimeSeries(DadoSeries serie){
    printf(" Codigo: %d\n Titulo: %s\n Quantidade de Epsodio: %d\n Temporadas:\n",serie.codigo, serie.titulo, serie.numeroDeTemporada);
    imprimeArvoreTemporada(serie.temporada);
}


void imprimeSeriesPeloCodigo(ArvoreSerie *raiz, int codigo){
    ArvoreSerie *aux = BuscarSeries(raiz, codigo);
    if(aux){
         printf(" Codigo: %d\n Titulo: %s\n Quantidade de Epsodio: %d\n Temporadas:\n",aux->dado.codigo, aux->dado.titulo, aux->dado.numeroDeTemporada);
        imprimeArvoreTemporada(aux->dado.temporada);
    }
   
}


//Imprimir os dados de todas as temporadas de uma série, cujo o usuário informe o código da série.


// imprimindo os dados da arvore serie de forma crescente...
void imprimeArvoreSeries(ArvoreSerie *raiz){

    if(raiz != NULL){
      imprimeArvoreSeries(raiz->esq);
      imprimeSeries(raiz->dado);
      imprimeArvoreSeries(raiz->dir);
      printf("\n");
    }
}

void imprimeArvoreTemporada(ArvoreTemporada *raiz){
    if(raiz != NULL){
        imprimeArvoreTemporada(raiz->esq);
        imprimeTemporada(raiz->temporada);
        imprimeArvoreTemporada(raiz->dir);
        printf("\n");
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