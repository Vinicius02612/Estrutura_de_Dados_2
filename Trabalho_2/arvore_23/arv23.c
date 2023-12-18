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

typedef struct album{
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


void RemoveMaiorInfoEsq(Arv23_artista** RaizArv23, Arv23_artista** PaiMaior, Arv23_artista** MaiorInfoRemove, int LocalInfo, char* Situacao) {
    if (*MaiorInfoRemove != NULL) {
        if (VerificaFolhaArtista(*MaiorInfoRemove) == 1) {
            Artista* Aux;
            if (LocalInfo == 1) {
                Aux = (*RaizArv23)->info1;

                if ((*MaiorInfoRemove)->numinfo == 2) {
                    (*RaizArv23)->info1 = (*MaiorInfoRemove)->info2;
                    (*MaiorInfoRemove)->info2 = Aux;
                }
                else {
                    (*RaizArv23)->info1 = (*MaiorInfoRemove)->info1;
                    (*MaiorInfoRemove)->info1 = Aux;
                }

            }
            else if (LocalInfo == 2) {
                Aux = (*RaizArv23)->info2;

                if ((*MaiorInfoRemove)->numinfo == 2) {
                    (*RaizArv23)->info2 = (*MaiorInfoRemove)->info2;
                    (*MaiorInfoRemove)->info2 = Aux;
                }
                else {
                    (*RaizArv23)->info2 = (*MaiorInfoRemove)->info1;
                    (*MaiorInfoRemove)->info1 = Aux;
                }

            }

            RemoveArtista23(MaiorInfoRemove, PaiMaior, Aux->nome_artista, -1, Situacao);
        }
        else {
            if ((*MaiorInfoRemove)->numinfo == 2) {
                RemoveMaiorInfoEsq(RaizArv23, MaiorInfoRemove, &((*MaiorInfoRemove)->dir), LocalInfo, Situacao);
            }
            else if ((*MaiorInfoRemove)->numinfo == 1) {
                RemoveMaiorInfoEsq(RaizArv23, MaiorInfoRemove, &((*MaiorInfoRemove)->centro), LocalInfo, Situacao);
            }
        } 
    }
    RedistribuiArv23Artista(MaiorInfoRemove, PaiMaior);
}


void RemoveArtista23(Arv23_artista** RaizArv23, Arv23_artista** Pai, char* NomeArtista, int LinhaArtista, char* Situacao) {
    if (*RaizArv23 != NULL) {
        if (strcasecmp(NomeArtista, (*RaizArv23)->info1->nome_artista) == 0) {
            if (LinhaArtista == -1) {
                if (VerificaFolhaArtista(*RaizArv23) == 1) {
                    if ((*RaizArv23)->numinfo == 2) {
                        free((*RaizArv23)->info1);
                        (*RaizArv23)->info1 = (*RaizArv23)->info2;
                        (*RaizArv23)->info2 = NULL;
                        (*RaizArv23)->numinfo = 1;
                    }
                    else if ((*RaizArv23)->numinfo == 1) {
                        free((*RaizArv23)->info1);
                        (*RaizArv23)->info1 = NULL;
                        (*RaizArv23)->numinfo = 0;
                    }
                }
                else {
                    Arv23_artista **MaiorInfoRemove = &((*RaizArv23)->esq);
                    Arv23_artista **PaiMaior = RaizArv23;
                    RemoveMaiorInfoEsqArtista(RaizArv23, PaiMaior, MaiorInfoRemove, 1, Situacao);
                }
            }
            else {
                if ((*RaizArv23)->info1 == NULL) {
                    RemoveArtista23(RaizArv23, Pai, NomeArtista, -1, Situacao);
                }
            }
            strcpy(Situacao, "Operacao realizada com sucesso!");
        }
        else if ((*RaizArv23)->numinfo == 2 && strcasecmp(NomeArtista, (*RaizArv23)->info2->nome_artista) == 0) {
            
            if (LinhaArtista == -1) {
                if (VerificaFolhaArtista(*RaizArv23) == 1) {
                    free((*RaizArv23)->info2);
                    (*RaizArv23)->info2 = NULL;
                    (*RaizArv23)->numinfo = 1;
                }
                else {
                    Arv23_artista **MaiorInfoRemove = &((*RaizArv23)->centro);
                    Arv23_artista **PaiMaior = RaizArv23;
                    RemoveMaiorInfoEsqArtista(RaizArv23, PaiMaior, MaiorInfoRemove, 2, Situacao);
                }
            }
            else {
                if ((*RaizArv23)->info2 == NULL) {
                    RemoveArtista23(RaizArv23, Pai, NomeArtista, -1, Situacao);
                }
            }
            strcpy(Situacao, "Operacao realizada com sucesso!");
        }
        else if (strcasecmp(NomeArtista, (*RaizArv23)->info1->nome_artista) < 0) {
            RemoveArtista23(&((*RaizArv23)->esq), RaizArv23, NomeArtista, LinhaArtista, Situacao);
        }
        else if ((*RaizArv23)->numinfo == 1 || ((*RaizArv23)->numinfo == 2 && strcasecmp(NomeArtista, (*RaizArv23)->info2->nome_artista) < 0)) {
            RemoveArtista23(&((*RaizArv23)->centro), RaizArv23, NomeArtista, LinhaArtista, Situacao);
        }
        else {
            RemoveArtista23(&((*RaizArv23)->dir), RaizArv23, NomeArtista, LinhaArtista, Situacao);
        }
    }
    RedistribuiArv23Artista(RaizArv23, Pai);
}

void RedistribuiArv23Artista(Arv23_artista** RaizArv23, Arv23_artista** Pai) {
    if (*RaizArv23 != NULL) {
        if ((*RaizArv23)->numinfo == 0) {
            if (Pai != NULL) {
                if ((*RaizArv23) == ((*Pai)->dir)) {
                    if ((*Pai)->centro->numinfo == 2) {
                        (*RaizArv23)->info1 = (*Pai)->info2;
                        (*RaizArv23)->numinfo = 1;
                        (*Pai)->info2 = (*Pai)->centro->info2;
                        (*Pai)->centro->numinfo = 1;
                        (*Pai)->centro->info2 = NULL;
                        (*RaizArv23)->esq = (*Pai)->centro->dir;
                        (*Pai)->centro->dir = NULL;
                    }
                    else if ((*Pai)->centro->numinfo == 1) {
                        (*RaizArv23)->info2 = (*Pai)->info2;
                        (*RaizArv23)->dir = (*RaizArv23)->centro;
                        (*RaizArv23)->info1 = (*Pai)->centro->info1;
                        (*RaizArv23)->numinfo = 2;
                        (*Pai)->numinfo = 1;
                        (*RaizArv23)->centro = (*Pai)->centro->centro;
                        (*RaizArv23)->esq = (*Pai)->centro->esq;
                        free((*Pai)->centro);
                        (*Pai)->centro = (*RaizArv23);
                        (*Pai)->dir = NULL;
                    }
                }
                else if ((*RaizArv23) == (*Pai)->centro) {
                    if ((*Pai)->esq->numinfo == 2) {
                        (*RaizArv23)->info1 = (*Pai)->info1;
                        (*RaizArv23)->numinfo = 1;
                        (*Pai)->info1 = (*Pai)->esq->info2;
                        (*Pai)->esq->numinfo = 1;
                        (*RaizArv23)->esq = (*Pai)->esq->dir;
                        (*Pai)->esq->dir = NULL;
                    }
                    else if ((*Pai)->esq->numinfo == 1) {
                        if ((*Pai)->numinfo == 2) {
                            (*RaizArv23)->info2 = (*Pai)->info1;
                            (*RaizArv23)->info1 = (*Pai)->esq->info1;
                            (*RaizArv23)->numinfo = 2;
                            (*RaizArv23)->dir = (*RaizArv23)->centro;
                            (*RaizArv23)->centro = (*Pai)->esq->centro;
                            (*RaizArv23)->esq = (*Pai)->esq->esq;
                            free((*Pai)->esq);
                            (*Pai)->esq = (*RaizArv23);
                            (*Pai)->info1 = (*Pai)->info2;
                            (*Pai)->numinfo = 1;
                            (*Pai)->centro = (*Pai)->dir;
                            (*Pai)->dir = NULL;
                        }
                        else if ((*Pai)->numinfo == 1) {
                            (*RaizArv23)->info2 = (*Pai)->info1;
                            (*RaizArv23)->info1 = (*Pai)->esq->info1;
                            (*RaizArv23)->numinfo = 2;
                            (*Pai)->numinfo = 0;
                            (*RaizArv23)->dir = (*RaizArv23)->centro;
                            (*RaizArv23)->centro = (*Pai)->esq->centro;
                            (*RaizArv23)->esq = (*Pai)->esq->esq;
                            free((*Pai)->esq);
                            (*Pai)->esq = NULL;
                        }
                    }
                }
                else if ((*RaizArv23) == (*Pai)->esq) {
                    if ((*Pai)->centro->numinfo == 2) {
                        (*RaizArv23)->info1 = (*Pai)->info1;
                        (*RaizArv23)->numinfo = 1;
                        (*Pai)->info1 = (*Pai)->centro->info1;
                        (*Pai)->centro->numinfo = 1;
                        (*Pai)->centro->info1 = (*Pai)->centro->info2;
                        (*RaizArv23)->esq = (*RaizArv23)->centro;
                        (*RaizArv23)->centro = (*Pai)->centro->esq;
                        (*Pai)->centro->esq = (*Pai)->centro->centro;
                        (*Pai)->centro->centro = (*Pai)->centro->dir;
                        (*Pai)->centro->dir = NULL;
                    }
                    else if ((*Pai)->centro->numinfo == 1) {
                        if ((*Pai)->numinfo == 2) {
                            (*RaizArv23)->info1 = (*Pai)->info1;
                            (*RaizArv23)->info2 = (*Pai)->centro->info1;
                            (*RaizArv23)->numinfo = 2;
                            (*RaizArv23)->esq = (*RaizArv23)->centro;
                            (*RaizArv23)->centro = (*Pai)->centro->esq;
                            (*RaizArv23)->dir = (*Pai)->centro->centro;
                            (*Pai)->info1 = (*Pai)->info2;
                            (*Pai)->numinfo = 1;
                            free((*Pai)->centro);
                            (*Pai)->centro = (*Pai)->dir;
                            (*Pai)->dir = NULL;
                        }
                        else if ((*Pai)->numinfo == 1) {
                            (*RaizArv23)->info1 = (*Pai)->info1;
                            (*RaizArv23)->esq = (*RaizArv23)->centro;
                            (*RaizArv23)->info2 = (*Pai)->centro->info1;
                            (*RaizArv23)->centro = (*Pai)->centro->esq;
                            (*RaizArv23)->dir = (*Pai)->centro->centro;
                            (*Pai)->numinfo = 0;
                            (*RaizArv23)->numinfo = 2;
                            free((*Pai)->centro);
                            (*Pai)->centro = (*RaizArv23);
                            (*Pai)->esq = NULL;
                        }
                    }
                }
            }
            else if (Pai == NULL) {
                (*RaizArv23) = (*RaizArv23)->centro;
            }  
        }
    }
}
