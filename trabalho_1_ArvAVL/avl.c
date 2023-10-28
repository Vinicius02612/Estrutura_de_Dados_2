#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

Serie *criaNoSerie(int codigo, char titulo[], int numTemp){

      Serie *new = (Serie *) malloc(sizeof(Serie));
      new->codigo = codigo;
      strcpy(new->titulo, titulo);
      new->numTemp = numTemp;
      new->arvTemp = NULL;
      new->alt = 0;
      new->esq = NULL;
      new->dir = NULL;
      return new;
}

int calcula_Altura(Serie *no){
      int i = -1;
      if (no != -1)
      {
            i = no->alt;
      }
      return i;
}

void atualizar_Altura(Serie *no){

      int altura_esq = calcula_Altura(no->esq);
      int altura_dir = calcula_Altura(no->dir);
      no->alt = (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
}

int fator_Balanciamento(Serie *no){
      int i = 0;
      int alt_esq, alt_dir;
      if (no != NULL)
      {
            alt_esq = calcula_Altura(no->esq);
            alt_dir = calcula_Altura(no->dir);
            i = (alt_esq) - (alt_dir);
      }
      return i;
}

void rotacao_Direita(Serie **no){
      Serie *aux = (*no)->esq;
      (*no)->esq = aux->dir;
      aux->dir = (*no);

      atualizar_Altura(*no);
      atualizar_Altura(aux);

      (*no) = aux;
}

void rotacao_Esquerda(Serie **no){
      Serie *aux = (*no)->dir;
      (*no)->dir = aux->esq;
      aux->esq = (*no);

      atualizar_Altura(*no);
      atualizar_Altura(aux);

      (*no) = aux;      
}

void insere_Serie(Serie **raiz, Serie *serie){
      int fator_de_Balanceamento;

      if (*raiz == NULL)
      {
            *raiz = serie;
      } else if (serie->codigo < (*raiz)->codigo)
      {
            insere_Serie(&(*raiz)->esq, serie);
      }else
      {
            insere_Serie(&(*raiz)->dir, serie);
      }

      fator_de_Balanceamento = fator_Balanciamento(*raiz);

      if (fator_de_Balanceamento == 2)
      {
            int fator_balanceamento_esq;

            fator_balanceamento_esq = fator_Balanciamento((*raiz)->esq);
            if (fator_balanceamento_esq < 0)
            {
                  rotacao_Esquerda(&((*raiz)->esq));
            }
            rotacao_Direita(*raiz);
      }else if (fator_de_Balanceamento == -2)
      {
             int fator_balanceamento_dir;

             fator_balanceamento_dir = fator_Balanciamento((*raiz)->dir);
             if (fator_balanceamento_dir > 0)
             {
                  rotacao_Direita(&((*raiz)->dir));
             }
             rotacao_Esquerda(*raiz);
      }
      atualizar_Altura(*raiz);
}

void *busca_Serie_remove(Serie **serie, int codigo, int codigo_temp){
      if (*serie != NULL)
      {
            if ((*serie)->codigo == codigo)
            {
                  remover_temporada(&(*serie)->arvTemp, codigo_temp);
            }else if (codigo < (*serie)->codigo)
            {
                  busca_Serie_remove(&(*serie)->esq, codigo, codigo_temp);
            }else
            {
                  busca_Serie_remove(&(*serie)->dir, codigo, codigo_temp);
            }     
      }
}

Serie *busca_Serie_Codigo(Serie **serie, int codigo){

      Serie **idEncontrado;
      if((*serie) != NULL){
            if ((*serie)->codigo > codigo)
            {
                  idEncontrado = busca_Serie_Codigo(&(*serie)->esq, codigo);
            }
            else if ((*serie)->codigo < codigo)
            {
                  idEncontrado = busca_Serie_Codigo(&(*serie)->dir, codigo);
            }
            else
            {
                  idEncontrado = serie;
            }
      }
      else
      {
            idEncontrado = serie;
      }    
}

void busca_folha_Serie(Serie **ultimo, Serie *no_Filho){
      if (*ultimo)
      {
            busca_folha_Serie(&((*ultimo)->dir), no_Filho);
      }else
      {
            (*ultimo) = no_Filho;
      }
}

Serie *endereco(Serie *raiz){
      Serie *aux;
      if (raiz->esq)
      {
            aux = raiz->esq;
      }
      else
      {
            aux = raiz->dir;
      }
      return aux;
}

void remover_serie(Serie **raiz, int codigo){
      if ((*raiz) != NULL)
      {
            Serie *aux;
            if ((*raiz)->codigo == codigo)
            {
                  if ((*raiz)->arvTemp == NULL)
                  {
                        if ((*raiz)->esq == NULL && (*raiz)->dir == NULL)
                        {
                              free(*raiz);
                              *raiz = NULL;
                        }else if ((*raiz)->esq == NULL || (*raiz)->dir == NULL)
                        {
                              Serie *id_filho;
                              id_filho =  endereco(*raiz);
                              aux = *raiz;
                              *raiz = id_filho;
                              free(aux);
                              aux = NULL;
                        }else
                        {
                              Serie *id_filho_1;
                              aux = *raiz;
                              id_filho_1 = (*raiz)->esq;
                              busca_folha_Serie(&(*raiz)->esq, &(*raiz)->dir);
                              *raiz = id_filho_1;
                              free(aux);
                              aux = NULL;
                        }
                  }
                  
            }else if ((*raiz)->codigo > codigo)
            {
                  remover_serie(&(*raiz)->esq, codigo);
            }else
            {
                  remover_serie(&(*raiz)->dir, codigo);
            }

            if (*raiz != NULL)
            {
                  int fb;
                  fb = fator_Balanciamento(*raiz);
                  if(fb == 2){
                        if (fator_Balanciamento((*raiz)->esq) == -1)
                        {
                              rotacao_Esquerda(&((*raiz)->esq));
                        }
                        rotacao_Direita((raiz));
                  }else if (fb == -2)
                  {
                        if (fator_Balanciamento((*raiz)->esq) == 1)
                        {
                              rotacao_Direita(&((*raiz)->dir));
                        }
                        rotacao_Esquerda((raiz));
                  }
            }
            atualizar_Altura(*raiz);
      }
}


