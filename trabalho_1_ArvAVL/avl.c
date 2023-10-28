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

void imprime(Serie *raiz){
       printf("\nDados da série:\nCodigo: %d\nTitulo: %s\nNumero de temporadas: %d\n\n", raiz->codigo, raiz->titulo, raiz->numTemp);
}

void imprime_todas_Series(Serie *raiz){
      if (raiz != NULL)
      {
            imprime_Serie(raiz->esq);
            imprime(raiz);
            imprime_Serie(raiz->dir);
      }
}

void imprime_Serie_Por_Codigo(Serie *raiz, int codigo){
      if (raiz != NULL)
      {
            if (raiz->codigo == codigo)
            {
                  imprime(raiz);
            }else
            {
                  if (raiz->esq == codigo)
                  {
                        imprime_Serie_Por_Codigo(raiz->esq, codigo);
                  }else{
                        imprime_Serie_Por_Codigo(raiz->dir, codigo);
                  }
            }
      }
}

Temporada criaNoTemp(int cod,int numTemp, char titulo[], int quantidade_Ep, char ano, Part *list){
      Temporada *new = (Temporada*) malloc(sizeof(Temporada));
      new->codigo = cod;
      new->numTem = numTemp;
      new->participantes = *list;
      new->ano = ano;
      strcpy(new->titulo, titulo);
      new->quantEp = quantidade_Ep;
      new->esq = new->dir = new->alt = NULL;
      return *new;
}

int calcula_Altura_temp(Temporada *no){
      int i = -1;
      if (no != -1)
      {
            i = no->alt;
      }
      return i;
}

void atualizar_Altura_temp(Temporada *no){

      int altura_esq = calcula_Altura_temp(no->esq);
      int altura_dir = calcula_Altura_temp(no->dir);
      no->alt = (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
}

int fator_Balanciamento_temp(Temporada *no){
      int i = 0;
      int alt_esq, alt_dir;
      if (no != NULL)
      {
            alt_esq = calcula_Altura_temp(no->esq);
            alt_dir = calcula_Altura_temp(no->dir);
            i = (alt_esq) - (alt_dir);
      }
      return i;
}

void rotacao_Direita_temp(Temporada **no){
      Temporada *aux = (*no)->esq;
      (*no)->esq = aux->dir;
      aux->dir = (*no);
      atualizar_Altura_temp(*no);
      atualizar_Altura_temp(aux);

      (*no) = aux;
}

void rotacao_Esquerda_temp(Temporada **no){
      Temporada *aux = (*no)->dir;
      (*no)->dir = aux->esq;
      aux->esq = (*no);

      atualizar_Altura_temp(*no);
      atualizar_Altura_temp(aux);

      (*no) = aux;      
}

void insere_Temp(Temporada **raiz, Temporada *temp){
      int fator_de_Balanceamento;

      if (*raiz == NULL)
      {
            *raiz = temp;
      } else if (temp->codigo < (*raiz)->codigo)
      {
            insere_Temp(&(*raiz)->esq, temp);
      }else
      {
            insere_Temp(&(*raiz)->dir, temp);
      }

      fator_de_Balanceamento = fator_Balanciamento_temp(*raiz);

      if (fator_de_Balanceamento == 2)
      {
            int fator_balanceamento_esq;

            fator_balanceamento_esq = fator_Balanciamento_temp((*raiz)->esq);
            if (fator_balanceamento_esq < 0)
            {
                  rotacao_Esquerda_temp(&((*raiz)->esq));
            }
            rotacao_Direita_temp(*raiz);
      }else if (fator_de_Balanceamento == -2)
      {
             int fator_balanceamento_dir;

             fator_balanceamento_dir = fator_Balanciamento_temp((*raiz)->dir);
             if (fator_balanceamento_dir > 0)
             {
                  rotacao_Direita_temp(&((*raiz)->dir));
             }
             rotacao_Esquerda_temp(*raiz);
      }
      atualizar_Altura_temp(*raiz);
}

void busca_folha_temp(Temporada **filho_1, Temporada *filho_2){
      if (*filho_1)
      {
            busca_folha_Serie(&((*filho_1)->dir), filho_2);
      }else
      {
            (*filho_1) = filho_2;
      }
}

void remover_temporada(Temporada **raiz, int codigo){
      if (*raiz == NULL)
      {
            Temporada *aux;
            if ((*raiz)->codigo == codigo)
            {
                  if ((*raiz)->esq == NULL && (*raiz)->dir == NULL)
                  {
                        free(*raiz);
                        (*raiz) = NULL;
                  }else if ((*raiz)->esq == NULL || (*raiz)->dir == NULL)
                  {
                        Temporada *id_filho;
                        if ((*raiz)->esq != NULL)
                        {
                              aux = (*raiz);
                              id_filho = (*raiz)->esq;
                              (*raiz) = id_filho;
                              free(aux);
                              aux = NULL;
                        }else
                        {
                              aux = *raiz;
                              id_filho = (*raiz)->dir;
                              *raiz = id_filho;
                              free(aux);
                              aux = NULL;                              
                        }
                  }else
                  {
                        Temporada *filho;
                        aux = *raiz;
                        filho = (*raiz)->esq;
                        busca_folha_temp(&((*raiz)->esq), (*raiz)->dir);
                        *raiz = filho;
                        free(aux);      
                        aux = NULL;                          
                  }
                  
            }
            else if ((*raiz)->codigo < codigo)
            {
                  remover_temporada(&(*raiz)->esq, codigo);
            }else
            {
                  remover_temporada(&(*raiz)->dir, codigo);
            }
            
            if (*raiz != NULL){
              int fb;
              fb = fator_Balanciamento_temp(*raiz);
              if (fb == 2){
                  if (fator_Balanciamento_temp((*raiz)->esq) == -1){
                      rotacao_Esquerda_temp(&((*raiz)->esq));
                  }
                  rotacao_Direita_temp((raiz));

              } else if (fb == -2){
                  if (fator_Balanciamento_temp((*raiz)->esq) == 1){
                      rotacao_Direita_temp(&((*raiz)->dir));
                  }
                  rotacao_Esquerda_temp((raiz));

              }
              atualizar_Altura_temp(*raiz);
            }      
      }
}