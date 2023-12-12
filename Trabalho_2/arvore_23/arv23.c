#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arv23.h"

typedef struct artista{
      char nome_artista[50];
      char estilo_musical[50];
      int num_albuns;
      Album *album;
} Artista;

typedef struct arv23_artista{
      Artista *info1, *info2;
      int numinfo;
      Arv23_artista *esq, *dir, *centro;
}Arv23_artista;

typedef struct {
    char titulo[100];
    int anoLancamento;
    int qtdMusicas;
    Musica *musicas;
} Album;

typedef struct Arv23_album{
      Album info1, info2;
      int numinfo;
      Arv23_album *esq, *dir, *centro;
} Arv23_album;

typedef struct Musica {
    char titulo[100];
    int duracao;
    Musica* proximo;
    Musica* anterior;
} Musica;

typedef struct listaDupla{
    Musica* inicio;
    Musica* fim;
} ListaDupla;

Arv23_artista *cria_NO_Artista(Arv23_artista *no, Arv23_artista *esq, Arv23_artista *dir, Arv23_artista *centro){
      Arv23_artista *new;
      new = (Arv23_artista *)malloc(sizeof(Arv23_artista));
      if (new == NULL)
      {
            return NULL;
      }
      new->info1 = (Artista *)malloc(sizeof(Artista));
      new->info2 = (Artista *)malloc(sizeof(Artista));
      new->info1 = NULL;
      new->info2 = NULL;
      new->esq = esq;
      new->dir = dir;
      new->centro = centro;
      new->numinfo = 1;

      return new;
}

Arv23_artista *quebra_no(Arv23_artista **no, char nome_artista[], char sobe[], Arv23_artista *filho){
      Arv23_artista *new = NULL;

      if (strcmp(nome_artista, (*no)->info1->nome_artista) > 0)
      {
            strcpy(sobe,nome_artista);
            new = cria_NO_Artista((*no)->info2, filho, (*no)->dir, NULL);
      } else if (strcmp(nome_artista, (*no)->info2->nome_artista) > 0)
      {
            strcpy(sobe, (*no)->info2);
            new = cria_NO_Artista(nome_artista, (*no)->dir, filho, NULL);
      }else
      {
            strcpy(sobe, (*no)->info1);
            new = cria_NO_Artista((*no)->info2, (*no)->centro, (*no)->dir, NULL);
            strcpy((*no)->info1, nome_artista);
            (*no)->centro = filho;
      }

      (*no)->dir = NULL;
      (*no)->numinfo = 1;
      return new;

}

Arv23_artista *eh_folha_artista(Arv23_artista *raiz){
      if (raiz != NULL && raiz->esq == NULL)
      {
            return raiz;
      }
      return NULL;
}

Arv23_artista *adiciona_No_artista(Arv23_artista *raiz, char nome_artista[], Arv23_artista *filho_dir){
      if(strcmp(nome_artista,raiz->info1->estilo_musical) < 0){
            raiz->info1 = raiz->info2;
            strcpy(raiz->info2, raiz->info1);
            strcpy(raiz->info1->nome_artista, nome_artista);
            raiz->dir = raiz->centro;
            raiz->centro = raiz->dir;
      }else
      {
            strcpy(raiz->info2->nome_artista, nome_artista);
            raiz->dir = filho_dir;
      }
      raiz->numinfo = 2;

      return raiz;
}

Arv23_artista *insere_no_artista(Arv23_artista **raiz, char nome_artista[], Arv23_artista *pai, char sobe[]){

      Arv23_artista *maior_no = NULL;

      if (raiz != NULL)
            cria_NO_Artista(&(*raiz), NULL, NULL, NULL);
      else
      {
            if (eh_folha_artista(*raiz))
            {
                  if((*raiz)->numinfo == 1){
                        *raiz = adiciona_No_artista(*raiz, nome_artista, NULL);
                        maior_no = NULL;
                  }else
                  {
                        maior_no = quebra_no_artista(raiz, nome_artista, sobe, NULL);
                        if (pai == NULL)
                        {
                              *raiz = cria_NO_Artista(sobe,*raiz, maior_no, NULL);
                              maior_no = NULL;
                        }
                  }
            }
            else
            {
                  if (strcmp(nome_artista, (*raiz)->info1->nome_artista) < 0)
                  {
                        maior_no = insere_no_artista(&((*raiz)->esq), nome_artista, *raiz, sobe);
                  }else if ((*raiz)->numinfo == 1 || (*raiz)->numinfo == 2 && (strcmp(nome_artista, (*raiz)->info2->nome_artista) < 0))
                  {
                        maior_no = insere_no((&(*raiz)->centro), nome_artista, *raiz, sobe);
                  }else
                  {
                        maior_no = insere_no((&(*raiz)->dir), nome_artista, *raiz, sobe);
                  }

                  if (maior_no != NULL)
                  {
                        if ((*raiz)->numinfo == 1)
                        {
                              *raiz = adiciona_no(*raiz, sobe, maior_no);
                              maior_no = NULL;
                        }else
                        {
                              char aux[50];

                              strcpy(aux, sobe);
                              maior_no = quebra_no(raiz, aux, sobe, maior_no);
                              if (pai == NULL)
                              {
                                    *raiz = cria_NO_Artista(sobe,*raiz, maior_no, NULL);
                                    maior_no = NULL;
                              }
                        }
                  }
                  
            }
            
      }
      return maior_no;
}


