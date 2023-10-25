#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvBin.h"


// Testar usando ponteiro para ponteiro

typedef struct serie{
      int codigo;
      char titulo[50];
      int numTemp;
      Temporada *arvTemp;
      Serie *esq, *dir;
}Serie;
//código, título, número de temporadas

typedef struct temporada{
      int numTem;
      char titulo[50];
      int quantEp;
      char ano;
      Participantes *participantes;
      Temporada *esq, *dir;
}Temporada;
//número da temporada, título, quantidade de episódios, ano, endereço para ula lista simples  de participantes.

typedef struct participantes
{
      char nomeDoArtista[50];
      char nomeParticipante[50];
      char descricao[100];
      Participantes *prox; 
}Participantes;

//CRIA A ARVORE PARA AS SERIES
Serie *criaNoSerie(){
      return NULL;
      
}
Participantes *criar_Participantes(){
      return NULL;
}


Participantes *inserir_Participante(Participantes *lista, char nomeDoArtista,char nomeParticipante,char descricao ){
      Participantes *aux = (Participantes*)malloc(sizeof(Participantes));
      if(lista == NULL){
            strcpy(aux->nomeDoArtista, nomeDoArtista);
            strcpy(aux->nomeParticipante, nomeParticipante);
            strcpy(aux->descricao, descricao);
            aux->prox =  lista;
            return aux;
      }
      return NULL;
}

//INSERE UMA SERIE A PARTIR DO CODIGO
void insere_Serie(Serie **raiz, int codigo, char titulo[], int numTemp){
      if (*raiz == NULL){
            (*raiz)->codigo = codigo;
            (*raiz)->numTemp = numTemp;
            strcpy((*raiz)->titulo, titulo);
            (*raiz)->esq = NULL;
            (*raiz)->dir = NULL;
      }
      if (codigo < (*raiz)->codigo){
            insere_Serie(&((*raiz)->esq), codigo, titulo, numTemp);
      }else{
            insere_Serie(&((*raiz)->dir), codigo, titulo, numTemp);

      }
}

Temporada *criarTemporada(){
      return NULL;
}

void insere_Temporada(Temporada **raiz, int numTemporada, char titulo[], int quantEp, char ano){

      if(*raiz == NULL){

            (*raiz)->numTem = numTemporada;
            strcpy((*raiz)->titulo, titulo);
            (*raiz)->quantEp = quantEp;
            (*raiz)->participantes = NULL;
            (*raiz)->esq = NULL;
            (*raiz)->dir = NULL;
      }
      if(numTemporada < (*raiz)->numTem){
            insere_Temporada(&((*raiz)->esq), numTemporada,titulo,quantEp,ano);
      }else{
            insere_Temporada(&((*raiz)->dir), numTemporada,titulo,quantEp,ano);
      }
}



void listarParticipante(Participantes *lista){
      while (lista != NULL)
      {
            printf("Nome do artista: %s\n Nome do Personagem: %s\n Descricao: %s\n", lista->nomeDoArtista, lista->nomeParticipante, lista->descricao);
            lista = lista->prox;
      }
      
}

void imprime_Serie(Serie *raiz){
      if(raiz != NULL){
            imprime_Serie(raiz->esq);
            printf("Codigo: %d\nTitulo: %s\n Numero de temporadas: %d\n", raiz->codigo, raiz->titulo, raiz->numTemp);
            imprime_Serie(raiz->dir);
      }
}

void listarTemporada(Temporada *raiz){
      if(raiz  != NULL){
            listarTemporada(raiz->esq);
            printf("Numero da temporada: %d\n Titulo:  %s\n Quantidade de Episodio: %d\n Ano: %d\n Participantes da Tempora: \n", raiz->numTem, raiz->titulo, raiz->quantEp, raiz->ano);
            listarParticipante(raiz->participantes);
            printf("\n");
            listarTemporada(raiz->dir);
      }
}


// ver uma outra forma defazer essa função
/* void inserirTemporadaAserie(Serie *serie, Temporada *temporada){
      insere_Temporada(serie->arvTemp,temporada);
}
 */