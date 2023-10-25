#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arvBin.h"

//CRIA A ARVORE PARA AS SERIES
Serie *criaNoSerie(int codigo, char titulo[], int numTemp){

      Serie *new;
      new = (Serie*)malloc(sizeof(Serie));
      new->codigo = codigo;
      strcpy(new->titulo, titulo);
      new->numTemp = numTemp;
      new->arvTemp = NULL;
      new->esq = NULL;
      new->dir = NULL;
      return new;

}

//INSERE UMA SERIE A PARTIR DO CODIGO
void insere_Serie(Serie **raiz, Serie *serie){

      if (*raiz == NULL)
      {
            *raiz = serie;
      }
      else if (serie->codigo < (*raiz)->codigo)
      {
            insere_Serie(&(*raiz)->esq, serie);
      }
      else
      {
            insere_Serie(&(*raiz)->dir, serie);
      }
}

Serie *busca_Serie(Serie **serie, int codigo){

      Serie **idEncontrado;
      if((*serie) != NULL){
            if ((*serie)->codigo > codigo)
            {
                  idEncontrado = busca_Serie(&(*serie)->esq, codigo);
            }
            else if ((*serie)->codigo < codigo)
            {
                  idEncontrado = busca_Serie(&(*serie)->dir, codigo);
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

void busca_folha(Serie **filho_1, Serie *filho_2){
      if (*filho_1)
      {
            busca_folha(&((*filho_1)->dir), filho_2);
      }
      else
      {
            (*filho_1) = filho_2;
      }
}

void remover_serie(Serie **raiz, int codigo){
      if (*raiz != NULL)
      {
            Serie *aux;
            if ((*raiz)->codigo == codigo)
            {
                  if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) // se nao tem filhos
                  {
                        free(*raiz);
                        (*raiz) = NULL;                        
                  }
                  else if ((*raiz)->esq == NULL || (*raiz)->dir == NULL)
                  {
                        Serie *id_filho;
                        if ((*raiz)->esq != NULL)
                        {
                              aux = *raiz;
                              id_filho = (*raiz)->esq;
                              *raiz = id_filho;
                              free(aux);
                              aux = NULL;
                        }
                        else
                        {
                              aux = *raiz;
                              id_filho = (*raiz)->dir;
                              *raiz = id_filho;
                              free(aux);
                              aux = NULL;                              
                        }
                  }
                  else
                  {
                        Serie *serie;
                        aux = *raiz;
                        serie = (*raiz)->esq;
                        busca_folha(&((*raiz)->esq), (*raiz)->dir);
                        *raiz = serie;
                        aux = NULL;
                  }
            }
            else if (codigo < (*raiz)->codigo)
            {
                  remover_serie((*raiz)->esq, codigo);
            }
            else
            {
                  remover_serie((*raiz)->dir, codigo);
            }
      }
}

void imprime_Serie(Serie *raiz){
          if (raiz != NULL) {
        imprimirSeries(raiz->esq);
        printf("\nDados da série:\nCodigo: %d\nTitulo: %s\nNumero de temporadas: %d\n\n", raiz->codigo, raiz->titulo, raiz->numTemp);
        imprimirSeries(raiz->dir);
    }
}

