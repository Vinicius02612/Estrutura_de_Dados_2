#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvBin.h"

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
Serie *criaNoSerie(int codigo, char titulo[], int numTemp ){
      Serie *novaSerie = (Serie*)malloc(sizeof(Serie));
      if(novaSerie != NULL){
            novaSerie->codigo = codigo;
            strcpy(novaSerie->titulo, titulo);
            novaSerie->numTemp;
            novaSerie->arvTemp = NULL;
            novaSerie->esq = NULL;
            novaSerie->dir = NULL;
            return novaSerie;
      }
      return NULL;
      
}

//INSERE UMA SERIE A PARTIR DO CODIGO
Serie *insere_Serie(Serie *raiz, Serie *novaSerie){

      if (raiz == NULL){
            return novaSerie;
      }
      if (novaSerie->codigo < raiz->codigo){
            raiz->esq = insere_Serie(raiz->esq, novaSerie);
      }else if(novaSerie->codigo > raiz->codigo){
            raiz->dir = insere_Serie(raiz->dir, novaSerie);
      }
      return raiz;
}

Temporada *criarTemporada(int numeroTemp, char titulo[], int quantEp, char ano[] ){
      Temporada *novaTemp = (Temporada*)malloc(sizeof(Temporada));
      if(novaTemp != NULL){
            novaTemp->numTem;
            strcpy(novaTemp->titulo, titulo);
            novaTemp->quantEp =  quantEp;
            strcpy(novaTemp->ano, ano);
            novaTemp->participantes = NULL;
            return novaTemp;
      }
      return NULL;
}

Temporada *insere_Temporada(Temporada *raiz, Temporada *novaTempora){
      if(raiz == NULL){
            return novaTempora;
      }
      if(novaTempora->numTem < raiz->numTem){
            raiz->esq = insere_Temporada(raiz->esq, novaTempora);
      }else if(novaTempora->numTem > raiz->numTem){
            raiz->dir = insere_Temporada(raiz->esq, novaTempora);
      }
      return raiz;
}

Participantes *criar_Participantes(char nomeArtista[], char nomeParticipante, char descricao[]){
      Participantes *novoParticipante = (Participantes*)malloc(sizeof(Participantes));
      if(novoParticipante != NULL){
            strcpy(novoParticipante->nomeDoArtista, nomeArtista);
            strcpy(novoParticipante->nomeParticipante, nomeParticipante);
            strcpy(novoParticipante->descricao, descricao);
            return novoParticipante;
      }
      return NULL;
}

Participantes *inserir_Participante(Participantes *lista, Participantes *novoParticipante){
      if(lista == NULL || strcmp(novoParticipante->nomeDoArtista, lista->nomeDoArtista) < 0){
            novoParticipante->prox =  lista;
            return novoParticipante;
      }else{
            lista->prox = inserir_Participante(lista->prox, novoParticipante);
            return lista;
      }
      return NULL;
}

void listarParticipante(Participantes *lista){
      while (lista != NULL)
      {
            printf("Nome do artista: %s\n Nome do Personagem: %s\n Descricao: %s\n", lista->nomeDoArtista, lista->nomeParticipante, lista->descricao);
            lista = lista->prox;
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

void inserirTemporadaAserie(Serie *serie, Temporada *temporada){
      serie->arvTemp = insere_Temporada(serie->arvTemp,temporada);
}
