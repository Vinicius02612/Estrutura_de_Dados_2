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

typedef struct arv23_album{
      Album info1, info2;
      int numinfo;
      Arv23_album *esq, *dir, *centro;
} Arv23_album;

typedef struct musica {
    char titulo[100];
    int duracao;
    Musica* proximo;
    Musica* anterior;
} Musica;

typedef struct listaDupla{
    Musica* inicio;
    Musica* fim;
} ListaDupla;


Artista *lerDadosArtista(){
    // essa função retorna um os dados do artista preechidos para inserir na arvore
    Artista *dado;
    char nome[50], estilo[50];
    int num_albuns;
    dado = (Artista*)malloc(sizeof(Artista));

    printf("Nome: \n");
    scanf("%s", nome);
    strcpy(dado->nome_artista, nome);
    printf("Estilo Musical: \n");
    scanf("%s", estilo);
    strcpy(dado->estilo_musical, estilo);
    dado->album = NULL;
    num_albuns = 0;

    return dado;
}

Arv23_artista *cria_NO_Artista(Artista *info, Arv23_artista *esq, Arv23_artista *dir, Arv23_artista *centro){
    printf("Entrou aqui na criar no \n");
    Arv23_artista *new;
    new = (Arv23_artista*)malloc(sizeof(Arv23_artista));
    if(new != NULL){
        new->info1 = info;
        new->info2 = NULL;
        new->esq = esq;
        new->dir = dir;
        new->centro = centro;
        new->numinfo = 1;
    }
    

    return new;
}

Arv23_artista *quebra_no(Arv23_artista **no, Artista *info, Artista *sobe, Arv23_artista *filho){
    // Aqui ao invés de passar somente o nome do artista para realizar as comparações, passei a informação em si (info)
    //Dessa forma eu posso adicionar a estrutura info de artista no novo nó
    //O código anterior  estava passando apenas o nome do artista, sem o resto das informações
      Arv23_artista *new = NULL;

      if (strcmp(info->nome_artista, (*no)->info1->nome_artista) > 0)
      {
            sobe = info; // a informação sobre por inteira, e não apenas o nome do artista
            new = cria_NO_Artista((*no)->info2, filho, (*no)->dir, NULL);
      } else if (strcmp(info->nome_artista, (*no)->info2->nome_artista) > 0)
      {
            sobe = (*no)->info2;
            new = cria_NO_Artista(info, (*no)->dir, filho, NULL); // cria um no para o info de artista e não apenas o nome
      }else
      {
            sobe = (*no)->info1;
            new = cria_NO_Artista((*no)->info2, (*no)->centro, (*no)->dir, NULL);
            (*no)->info1 = info;
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

 void adiciona_No_artista(Arv23_artista **raiz, Artista *info, Arv23_artista *filho_dir){
      if(strcmp(info->nome_artista,(*raiz)->info1->nome_artista) < 0){
            (*raiz)->info2 = (*raiz)->info1;
            (*raiz)->info1 = info;
            (*raiz)->dir = (*raiz)->centro;
            (*raiz)->centro = (*raiz)->dir;
      }else
      {
            (*raiz)->info2 = info;
            (*raiz)->dir = filho_dir;
      }
      (*raiz)->numinfo = 2;
}

Arv23_artista *insere_no_artista(Arv23_artista **raiz, Artista *info, Arv23_artista *pai, Artista *sobe){
    printf("Entrou aqui na insere artista \n");
    Arv23_artista *maior_no = NULL;
    
    if (*raiz == NULL){
        printf("Condição de primeiro elemento \n");
        *raiz = cria_NO_Artista(info, NULL, NULL, NULL);
        if(*raiz != NULL){
                printf("No criado com sucesso! \n");
        }
    }else{
        if (eh_folha_artista(*raiz) != NULL){
            if((*raiz)->numinfo == 1){
                adiciona_No_artista(raiz, info, NULL);
                maior_no = NULL;
            }else{
                maior_no = quebra_no(raiz, info, sobe, NULL);
                if (pai == NULL){
                    *raiz = cria_NO_Artista(sobe,*raiz, maior_no, NULL);
                    maior_no = NULL;
                }
            }
        }else{ // da erro quando vai inserir uma terceira pessoa na arvore
            if (strcmp(info->nome_artista, (*raiz)->info1->nome_artista) < 0) {
                // se o nome do artista a ser inserido tiver um tamanho menor que
                // o nome que ja esta na arvore, inserir na esquerda
                maior_no = insere_no_artista(&((*raiz)->esq), info, *raiz, sobe);

            }else if ((*raiz)->numinfo == 1 || (*raiz)->numinfo == 2 && (strcmp(info->nome_artista, (*raiz)->info2->nome_artista) < 0)){
                // quantidade de informação do no ja esta com duas informações porem, é menor que info 2
                // inserir no centro
                maior_no = insere_no_artista((&(*raiz)->centro), info, *raiz, sobe);
            }else{
                //se for maior, inserir no centro
                maior_no = insere_no_artista((&(*raiz)->dir), info, *raiz, sobe);
            }             
        }
            
    }
    if (maior_no != NULL){
        if ((*raiz)->numinfo == 1){
            adiciona_No_artista(raiz, sobe, maior_no);
            maior_no = NULL;
        }else{
            maior_no = quebra_no(raiz, info, info, maior_no);
            if (pai == NULL){
                *raiz = cria_NO_Artista(sobe,*raiz, maior_no, NULL);
                maior_no = NULL;
            }
        }
    }
    return *raiz;
}


void RemoveMaiorInfoEsq(Arv23_artista** RaizArv23, Arv23_artista** PaiMaior, Arv23_artista** MaiorInfoRemove, int LocalInfo, char* Situacao) {
    if (*MaiorInfoRemove != NULL) {
        if (eh_folha_artista(*MaiorInfoRemove) != NULL) {
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
                if (eh_folha_artista(*RaizArv23) != NULL) {
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
                    RemoveMaiorInfoEsq(RaizArv23, PaiMaior, MaiorInfoRemove, 1, Situacao);
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
                if (eh_folha_artista(*RaizArv23) != NULL) {
                    free((*RaizArv23)->info2);
                    (*RaizArv23)->info2 = NULL;
                    (*RaizArv23)->numinfo = 1;
                }
                else {
                    Arv23_artista **MaiorInfoRemove = &((*RaizArv23)->centro);
                    Arv23_artista **PaiMaior = RaizArv23;
                    RemoveMaiorInfoEsq(RaizArv23, PaiMaior, MaiorInfoRemove, 2, Situacao);
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
/* 
     A função strcmp devolve um valor inteiro que indica o relacionamento entre string1 e string2:
     Um valor menor que zero significa que string1 é menor que string2. 
     Um valor zero significa que ambas as strings são iguais.
     Um valor maior que zero significa que string1 é maior que string2.
    
*/
Arv23_artista *buscarArtista(Arv23_artista **raiz, char nome_artista[]){
    Arv23_artista *auxBusca;
    auxBusca = NULL;
    if(raiz != NULL){
        if(strcmp(nome_artista, (*raiz)->info1->nome_artista) == 0){
            auxBusca = *raiz;
        }else if(strcmp(nome_artista, (*raiz)->info1->nome_artista) < 0 ){
            auxBusca = buscarArtista(&(*raiz)->esq, nome_artista);
        }else if(strcmp(nome_artista, (*raiz)->info1->nome_artista) > 0 && strcmp(nome_artista, (*raiz)->info2->nome_artista) < 0){
            auxBusca = buscarArtista(&(*raiz)->centro, nome_artista);
        }else{
            auxBusca = buscarArtista(&(*raiz)->dir, nome_artista);
        }
    }

    return auxBusca;
}

void imprimirArtista(Arv23_artista *raiz, int nivel){
    if(raiz != NULL){
        // mostra info 1
        printf("Nome  %s\n", raiz->info1->nome_artista);
        printf("Estilo Musical  %s\n", raiz->info1->estilo_musical);
        printf("Quantidade de Albuns  %d\n", raiz->info1->num_albuns);

        // se tiver 2 info, mostra a info 2 
        if(raiz->numinfo == 2){
            printf("Nome  %s\n", raiz->info2->nome_artista);
            printf("Estilo Musical  %s\n", raiz->info2->estilo_musical);
            printf("Quantidade de Albuns  %d\n", raiz->info2->num_albuns);           
        }

        imprimirArtista(raiz->esq, nivel+1);
        imprimirArtista(raiz->centro,nivel+1);
        imprimirArtista(raiz->dir,  nivel+1);

        printf("\n");
    }
}