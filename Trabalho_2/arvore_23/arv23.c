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
      Album *info1, *info2;
      int numinfo;
      Arv23_album *esq, *dir, *centro;
} Arv23_album;

typedef struct musica {
    char titulo[100];
    int duracao;
} Musica;

typedef struct listaDupla{
    Musica *info;
    ListaDupla *anterior, *proximo;
}ListaDupla;

Arv23_artista *inicializaArtista(){
    Arv23_artista *raiz = (Arv23_artista*)malloc(sizeof(Arv23_artista));
    if(raiz != NULL){
        raiz = NULL;
    }
    return raiz;
}

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

Arv23_artista *quebra_no(Arv23_artista **no, Artista *info, Artista **sobe, Arv23_artista *filho){
    // Aqui ao invés de passar somente o nome do artista para realizar as comparações, passei a informação em si (info)
    //Dessa forma eu posso adicionar a estrutura info de artista no novo nó
    //O código anterior  estava passando apenas o nome do artista, sem o resto das informações
      Arv23_artista *new;
      new = NULL;

      if(strcmp(info->nome_artista, (*no)->info2->nome_artista) > 0){
            *sobe = (*no)->info2;
            new = cria_NO_Artista(info, (*no)->dir, filho, NULL); 
      }else if (strcmp(info->nome_artista, (*no)->info1->nome_artista) < 0){
            *sobe = (*no)->info1;
            new = cria_NO_Artista((*no)->info2, (*no)->centro, (*no)->dir, NULL);
            (*no)->info1 = info;
            (*no)->centro = filho;
      }else{
            *sobe = (*no)->info1;
            new = cria_NO_Artista((*no)->info2, filho, (*no)->dir, NULL);
      }

      (*no)->info2 = NULL;
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
    if(strcmp(info->nome_artista,(*raiz)->info1->nome_artista) > 0){
        (*raiz)->info2 = info;
        (*raiz)->dir = filho_dir;
    }else if(strcmp(info->nome_artista,(*raiz)->info1->nome_artista) < 0){
        (*raiz)->info2 = (*raiz)->info1;
        (*raiz)->info1 = info;
        (*raiz)->dir = (*raiz)->centro;
        (*raiz)->centro = filho_dir;
    }
      (*raiz)->numinfo = 2;
}

Arv23_artista *insere_no_artista(Arv23_artista **raiz, Artista *info, Arv23_artista *pai, Artista **sobe){
    Arv23_artista *maior_no = NULL;
    
    if (*raiz == NULL){
        *raiz = cria_NO_Artista(info, NULL, NULL, NULL);
    }else{
        if (eh_folha_artista(*raiz) != NULL){
            if((*raiz)->numinfo == 1){
                adiciona_No_artista(raiz, info, NULL);
                maior_no = NULL;
            }else{
                maior_no = quebra_no(raiz, info, sobe, NULL);
                if (pai == NULL){
                    *raiz = cria_NO_Artista(*sobe,*raiz, maior_no, NULL);
                    maior_no = NULL;
                }
            }
        }else{ 
            if (strcmp(info->nome_artista, (*raiz)->info1->nome_artista) < 0) {
                // se o nome do artista a ser inserido tiver um tamanho menor que
                // o nome que ja esta na arvore, inserir na esquerda
                maior_no = insere_no_artista(&((*raiz)->esq), info, *raiz, sobe);

            }else if ((strcmp(info->nome_artista, (*raiz)->info1->nome_artista) > 0) && (strcmp(info->nome_artista, (*raiz)->info2->nome_artista) < 0)){
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
            adiciona_No_artista(raiz, *sobe, maior_no);
            maior_no = NULL;
        }else{
            maior_no = quebra_no(raiz, *sobe, sobe, maior_no);
            if (pai == NULL){
                *raiz = cria_NO_Artista(*sobe,*raiz, maior_no, NULL);
                maior_no = NULL;
            }       
        }
    } 
    
    return maior_no;
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


void RemoveArtista23(Arv23_artista** RaizArv23, Arv23_artista** Pai, char* NomeArtista, int LinhaArtista, char* Situacao){
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


Artista* buscarArtista(Arv23_artista* RaizArv23, char* Palavra) {
    Artista* InfoBusca;
    if (RaizArv23 != NULL) {
        int ValorPalavra1 = strcasecmp(Palavra, RaizArv23->info1->nome_artista);
        int ValorPalavra2; ValorPalavra2 = -1;
        if (RaizArv23->numinfo == 2)
            ValorPalavra2 = strcasecmp(Palavra, RaizArv23->info2->nome_artista);    

        if (ValorPalavra1 == 0) {
            InfoBusca = RaizArv23->info1;
        }
        else if(ValorPalavra2 == 0) {
            InfoBusca = RaizArv23->info2;
        }
        else if (ValorPalavra1 < 1) {
            InfoBusca = buscarArtista(RaizArv23->esq, Palavra);
        }
        else if (RaizArv23->numinfo >= 1 && ValorPalavra2 < 0) {
            InfoBusca = buscarArtista(RaizArv23->centro, Palavra);   
        }
        else {
            InfoBusca = buscarArtista(RaizArv23->dir, Palavra);
        }
    }
    else {
        InfoBusca = NULL;
    }

    return(InfoBusca);
}

void imprimeDadoArtista(Artista *dado){
    printf("Nome %s\n", dado->nome_artista);
    printf("Estilo musical%s\n", dado->estilo_musical);
    printf(" Quantidade de albums %d\n", dado->num_albuns);
}



void imprimirArtista(Arv23_artista *raiz, int nivel){
    if(raiz != NULL){
        // mostra info 1
        imprimeDadoArtista(raiz->info1);

        // se tiver 2 info, mostra a info 2 
        if(raiz->numinfo == 2){
           imprimeDadoArtista(raiz->info2);          
        }

        imprimirArtista(raiz->esq, nivel+1);
        imprimirArtista(raiz->centro,nivel+1);
        imprimirArtista(raiz->dir,  nivel+1);

        printf("\n");
    }
}

// -----------------REFERENTE A ALBUM-----------------

Arv23_album *inicializAlbum(){
    Arv23_album *raiz = (Arv23_album*)malloc(sizeof(Arv23_album));

    if(raiz != NULL){
        raiz = NULL;
    }
    return raiz;
}   

Album *lerDadoAlbum(){
    char titulo[100];
    int anoLancamento;
    Album *dado = (Album*)malloc(sizeof(Album));

    printf("Titulo: \n");
    scanf("%s", titulo);
    strcpy(dado->titulo, titulo);

    printf("Ano de lançamento: \n");
    scanf("%d", &anoLancamento);
    dado->anoLancamento = anoLancamento;

    dado->qtdMusicas = 0;

    return dado;

}


Arv23_album *cria_NO_Album(Album *info, Arv23_album *esq, Arv23_album *dir, Arv23_album *centro){
    Arv23_album *new;
    new = (Arv23_album*)malloc(sizeof(Arv23_album));
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


Arv23_album *eh_folha_album(Arv23_album *raiz){
    if (raiz != NULL && raiz->esq == NULL){
        return raiz;
    }
    return NULL;
}

Arv23_album *quebra_no_Album(Arv23_album **no, Album *info, Album *sobe, Arv23_album *filho){
      Arv23_album *new = NULL;

      if (strcmp(info->titulo, (*no)->info1->titulo) > 0 && strcmp(info->titulo, (*no)->info2->titulo) < 0)
      {
            sobe = info;
            new = cria_NO_Album((*no)->info2, filho, (*no)->dir, NULL);
      } else if (strcmp(info->titulo, (*no)->info2->titulo) > 0)
      {
            sobe = (*no)->info2;
            new = cria_NO_Album(info, (*no)->dir, filho, NULL); 
      }else
      {
            sobe = (*no)->info1;
            new = cria_NO_Album((*no)->info2, (*no)->centro, (*no)->dir, NULL);
            (*no)->info1 = info;
            (*no)->centro = filho;
      }

      (*no)->dir = NULL;
      (*no)->numinfo = 1;
      return new;
}

void adiciona_No_album(Arv23_album **raiz, Album *info, Arv23_album *filho_dir){
    if(strcmp(info->titulo,(*raiz)->info1->titulo) < 0){
        (*raiz)->info2 = (*raiz)->info1;
        (*raiz)->info1 = info;
        (*raiz)->dir = (*raiz)->centro;
        (*raiz)->centro = (*raiz)->dir;
    }else{
        (*raiz)->info2 = info;
        (*raiz)->dir = filho_dir;
    }
      (*raiz)->numinfo = 2;
}

Arv23_album *insere_no_album(Arv23_album **raiz, Album *info, Arv23_album *pai, Album *sobe){
    Arv23_album *maior_no = NULL;
    
    if (*raiz == NULL){
        *raiz = cria_NO_Album(info, NULL, NULL, NULL);
    }else{
        if (eh_folha_album(*raiz) != NULL){
            if((*raiz)->numinfo == 1){
                adiciona_No_album(raiz, info, NULL);
                maior_no = NULL;
            }else{
                maior_no = quebra_no_Album(raiz, info, sobe, NULL);
                if (pai == NULL){
                    *raiz = cria_NO_Album(sobe,*raiz, maior_no, NULL);
                    maior_no = NULL;
                }
            }
        }else{ 
            if (strcmp(info->titulo, (*raiz)->info1->titulo) < 0) {
                maior_no = insere_no_album(&((*raiz)->esq), info, *raiz, sobe);

            }else if ((strcmp(info->titulo, (*raiz)->info2->titulo) < 0) && (strcmp(info->titulo, (*raiz)->info1->titulo) > 0)){
                maior_no = insere_no_album((&(*raiz)->centro), info, *raiz, sobe);
            }else{
                maior_no = insere_no_album((&(*raiz)->dir), info, *raiz, sobe);
            }             
        }
            
    }
    if (maior_no != NULL){
        if ((*raiz)->numinfo == 1){
            adiciona_No_album(raiz, sobe, maior_no);
            maior_no = NULL;
        }else{
            maior_no = quebra_no_Album(raiz, info, info, maior_no);
            if (pai == NULL){
                *raiz = cria_NO_Album(sobe,*raiz, maior_no, NULL);
                maior_no = NULL;
            }
        }
    }
    return *raiz;
}



void RemoveMaiorInfoEsqAlbum(Arv23_album** RaizArv23, Arv23_album** PaiMaior, Arv23_album **MaiorInfoRemove, int LocalInfo, char* Situacao) {
    if ((*MaiorInfoRemove) != NULL) {
        if (eh_folha_album(*MaiorInfoRemove) != NULL) {
            Arv23_album* Aux;
            Aux = NULL;
            if (LocalInfo == 1) {
                Aux->info1 = (*RaizArv23)->info1;

                if ((*MaiorInfoRemove)->numinfo == 2) {
                    (*RaizArv23)->info1 = (*MaiorInfoRemove)->info2;
                    (*MaiorInfoRemove)->info2 = Aux->info1;
                }
                else {
                    (*RaizArv23)->info1 = (*MaiorInfoRemove)->info1;
                    (*MaiorInfoRemove)->info1 = Aux->info1;
                }

            }
            else if (LocalInfo == 2) {
                Aux->info2 = (*RaizArv23)->info2;

                if ((*MaiorInfoRemove)->numinfo == 2 && (*MaiorInfoRemove)->info2 != NULL) {
                    (*RaizArv23)->info2 = (*MaiorInfoRemove)->info2;
                    (*MaiorInfoRemove)->info2 = Aux->info2;
                }
                else {
                    (*RaizArv23)->info2 = (*MaiorInfoRemove)->info1;
                    (*MaiorInfoRemove)->info1 = Aux->info2;
                }

            }

            RemoveAlbum23(MaiorInfoRemove, PaiMaior, Aux->info1->titulo, -1, Situacao);
        }
        else {
            if ((*MaiorInfoRemove)->numinfo == 2) {
                RemoveMaiorInfoEsqAlbum(RaizArv23, MaiorInfoRemove, &((*MaiorInfoRemove)->dir), LocalInfo, Situacao);
            }
            else if ((*MaiorInfoRemove)->numinfo == 1) {
                RemoveMaiorInfoEsqAlbum(RaizArv23, MaiorInfoRemove, &((*MaiorInfoRemove)->centro), LocalInfo, Situacao);
            }
        } 
    }
    RedistribuiArv23Album(MaiorInfoRemove, PaiMaior);
}

void RemoveAlbum23(Arv23_album** RaizArv23, Arv23_album** Pai, char* titulo, int LinhaAlbum, char* Situacao) {
    printf("Entrou na função de remover \n");
    if (*RaizArv23 != NULL) {
        if (strcasecmp(titulo, (*RaizArv23)->info1->titulo) == 0) {
            if (LinhaAlbum == -1) {
                printf("Linha = -1\n");

                if (eh_folha_album(*RaizArv23) != NULL){
                    printf("Entrou na condição de  no folha\n");
                    if ((*RaizArv23)->numinfo == 2){
                        printf("Tem 2 informaçoes");
                        free((*RaizArv23)->info1);
                        (*RaizArv23)->info1 = (*RaizArv23)->info2;
                        (*RaizArv23)->info2 = NULL;
                        (*RaizArv23)->numinfo = 1;
                    }
                    else if ((*RaizArv23)->numinfo == 1){
                        printf("Tem 1 informaçao");

                        free((*RaizArv23)->info1);
                        (*RaizArv23)->info1 = NULL;
                        (*RaizArv23)->numinfo = 0;
                    }
                }else{
                    Arv23_album **MaiorInfoRemove = &((*RaizArv23)->esq);
                    Arv23_album **PaiMaior = RaizArv23;
                    RemoveMaiorInfoEsqAlbum(RaizArv23, PaiMaior, MaiorInfoRemove, 1, Situacao);
                }
            }
            else {
                if ((*RaizArv23)->info1 == NULL) {
                    RemoveAlbum23(RaizArv23, Pai, titulo, -1, Situacao);
                }
            }
            strcpy(Situacao, "Operacao realizada com sucesso!");
        }else if ((*RaizArv23)->numinfo == 2 && strcasecmp(titulo, (*RaizArv23)->info2->titulo) == 0) {
            
            if (LinhaAlbum == -1) {
                if (eh_folha_album(*RaizArv23) != NULL) {
                    free((*RaizArv23)->info2);
                    (*RaizArv23)->info2 = NULL;
                    (*RaizArv23)->numinfo = 1;
                }
                else {
                    Arv23_album **MaiorInfoRemove = &((*RaizArv23)->centro);
                    Arv23_album **PaiMaior = RaizArv23;
                    RemoveMaiorInfoEsqAlbum(RaizArv23, PaiMaior, MaiorInfoRemove, 2, Situacao);
                }
            }
            else {
                if ((*RaizArv23)->info2 == NULL) {
                    RemoveAlbum23(RaizArv23, Pai, titulo, -1, Situacao);
                }
            }
            strcpy(Situacao, "Operacao realizada com sucesso!");
        }
        else if (strcasecmp(titulo, (*RaizArv23)->info1->titulo) < 0) {
            RemoveAlbum23(&((*RaizArv23)->esq), RaizArv23, titulo, LinhaAlbum, Situacao);
        }
        else if ((*RaizArv23)->numinfo == 1 || ((*RaizArv23)->numinfo == 2 && strcasecmp(titulo, (*RaizArv23)->info2->titulo) < 0)) {
            RemoveAlbum23(&((*RaizArv23)->centro), RaizArv23, titulo, LinhaAlbum, Situacao);
        }
        else {
            RemoveAlbum23(&((*RaizArv23)->dir), RaizArv23, titulo, LinhaAlbum, Situacao);
        }
    }
    RedistribuiArv23Album(RaizArv23, Pai);
}

Album* buscarAlbum(Arv23_album* RaizArv23, char titulo[50]) {
    Album* InfoBusca;
    if (RaizArv23 != NULL) {
        int Valortitulo1 = strcasecmp(titulo, RaizArv23->info1->titulo);
        int Valortitulo2; Valortitulo2 = -1;
        if (RaizArv23->numinfo == 2)
            Valortitulo2 = strcasecmp(titulo, RaizArv23->info2->titulo);    

        if (Valortitulo1 == 0) {
            InfoBusca = RaizArv23->info1;
        }
        else if(Valortitulo2 == 0) {
            InfoBusca = RaizArv23->info2;
        }
        else if (Valortitulo1 < 1) {
            InfoBusca = buscarAlbum(RaizArv23->esq, titulo);
        }
        else if (RaizArv23->numinfo >= 1 && Valortitulo2 < 0) {
            InfoBusca = buscarAlbum(RaizArv23->centro, titulo);   
        }
        else {
            InfoBusca = buscarAlbum(RaizArv23->dir, titulo);
        }
    }
    else {
        InfoBusca = NULL;
    }

    return(InfoBusca);
}

void RedistribuiArv23Album(Arv23_album** RaizArv23, Arv23_album** Pai) {
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

void imprimeDadoAlbum(Album *dado){
    printf("titulo %s\n", dado->titulo);
    printf("ano de lancamento %d\n", dado->anoLancamento);
    printf(" Quantidade de musicas %d\n", dado->qtdMusicas);
}



void imprimirAlbum(Arv23_album *raiz, int nivel){
    if(raiz != NULL){
        // mostra info 1
        imprimeDadoAlbum(raiz->info1);

        // se tiver 2 info, mostra a info 2 
        if(raiz->numinfo == 2){
            imprimeDadoAlbum(raiz->info2);          
        }

        imprimirAlbum(raiz->esq, nivel+1);
        imprimirAlbum(raiz->centro,nivel+1);
        imprimirAlbum(raiz->dir,  nivel+1);

        printf("\n");
    }
}



ListaDupla *inicializarLista() {
    ListaDupla *lista;
    lista = (ListaDupla*)malloc(sizeof(ListaDupla));
    lista->info = NULL;
    lista->anterior = NULL;
    lista->proximo = NULL;
    return lista;

}

Musica *lerDadosMusica(){
    Musica *msc;
    msc = (Musica*)malloc(sizeof(Musica));
    char nome_musica[50];
    int duracao;
    printf("Nome da musica: \n");
    scanf("%s", nome_musica);
    strcpy(msc->titulo, nome_musica );
    printf("Duração: \n");
    scanf("%d", &duracao);
    msc->duracao = duracao;

    return msc;
    
}


ListaDupla *adicionarMusica(ListaDupla **lista, Musica *novaMusica) {
    ListaDupla *novoNo = (ListaDupla *)malloc(sizeof(ListaDupla));

    if(novoNo!= NULL){

        novoNo->info = novaMusica;
        novoNo->proximo = NULL;

        if(*lista == NULL){
            *lista = novoNo;
            novoNo->anterior = NULL;
        }else{
            ListaDupla *aux;
            aux = *lista;
            while (aux->proximo != NULL)
            {
                aux = aux->proximo;
            }
            aux->proximo = novoNo;
            novoNo->anterior = aux;
            
        }
    }

    return novoNo;
}

Musica *buscarMusica(ListaDupla *lista, char titulo[]){

    ListaDupla *aux = lista;
    Musica *achou = NULL;
    while (aux->proximo != NULL && aux->info->titulo != titulo){
        aux = aux->proximo;
    }
    if(aux != NULL){
        achou = aux->info;
    }

    return achou;

}

ListaDupla *removerMusica(ListaDupla **lista, char titulo[]){
    ListaDupla *aux, *remove;
    remove = NULL;

    if(*lista != NULL){
        if(strcmp((*lista)->info->titulo, titulo) == 0){
            remove = *lista;
            *lista = remove->proximo;
            (*lista)->anterior = NULL;
        }else{
            aux = *lista;
            while (aux->proximo != NULL && strcmp((*lista)->info->titulo, titulo) != 0)
            {
               aux = aux->proximo;
            }
            if(aux->proximo){
                remove = aux->proximo;
                aux->proximo = remove->proximo;
                aux->proximo->anterior = aux;
            }
            
        }
    }

    return remove;
}

void imprimeDadoMusica(Musica *msc){
    printf("Titulo: %s", msc->titulo);
    printf("Duracao: %d", msc->duracao);
    printf("\n");
}


// Função para imprimir todas as músicas na lista
void imprimirLista(ListaDupla *lista) {
    ListaDupla *aux;
    aux = lista;
    if(lista != NULL){
        while (aux != NULL) {
            imprimeDadoMusica(aux->info);
            aux = aux->proximo;
        }
        printf("\n\n");
    }else{
        printf("Nenhuma musica foi adicionada");
    }
  
}

// Função para liberar a memória alocada para a lista
void liberarLista(ListaDupla* lista) {
    ListaDupla* atual = lista;
    while (atual->proximo != NULL) {
        free(atual);
        atual = atual->proximo;
    }

    lista->anterior = NULL;
    lista->proximo = NULL;
}