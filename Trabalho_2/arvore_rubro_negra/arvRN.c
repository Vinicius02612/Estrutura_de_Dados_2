#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvRN.h"

#define RED 1
#define BLACK 0

typedef struct artista{
      char nome_artista[50];
      char estilo_musical[50];
      int num_albuns;
      int cor;
      Artista *esq, *dir;
} Artista;
//nome  do  artista,  o  estilo musical, o número de álbuns, e os Álbuns

int cor_artista(Artista *raiz){
      int cor;
      if (raiz==NULL) 
      {
            cor = BLACK;
      }else
      {
            cor = raiz->cor;
      }
      return cor;
}

void cria_No_Artista(Artista **raiz, char nome_artista[], char estilo_musical[], int num_albuns){
      Artista *new = (Artista *)malloc(sizeof(Artista));
      strcpy(new->nome_artista, nome_artista);
      strcpy(new->estilo_musical, estilo_musical);
      new->num_albuns = num_albuns;
      (*raiz)->cor = RED;
      (*raiz)->esq = NULL;
      (*raiz)->dir = NULL;
      return new;
}

void rotacao_esquerda_artista(Artista **raiz){
      Artista *aux;

      aux = (*raiz)->dir;
      (*raiz)->dir = aux->esq;
      aux->esq = *raiz;
      *raiz = aux;

      (*raiz)->cor = (*raiz)->esq->cor;
      (*raiz)->esq->cor = RED;
}

void rotacao_direita__artista(Artista **raiz){
            Artista *aux;

      aux = (*raiz)->esq;
      (*raiz)->esq = aux->dir;
      aux->dir = *raiz;
      *raiz = aux;

      (*raiz)->cor = (*raiz)->dir->cor;
      (*raiz)->dir->cor = RED;
}

void troca_Cor_artista(Artista *raiz){
      if (raiz != NULL)
      {
            raiz->cor = !raiz->cor;
            if (raiz->dir)
                  raiz->dir->cor = !raiz->dir->cor;
            else if (raiz->esq)
                  raiz->esq->cor = !raiz->esq->cor;
      }
}

Artista insere_NO(Artista **raiz, char nome_artista[], char estilo_musical[], int num_albuns){
      if (raiz == NULL)
      {
            cria_No_Artista(raiz, nome_artista, estilo_musical, num_albuns);
      }
      if (strcmp((*raiz)->nome_artista, nome_artista) == 0)
      {
            
      }
      

}