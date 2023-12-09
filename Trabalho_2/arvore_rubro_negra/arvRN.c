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
      Album *album;
      int cor;
      Artista *esq, *dir;
} Artista;
//nome  do  artista,  o  estilo musical, o número de álbuns, e os Álbuns

typedef struct {
    char titulo[100];
    int anoLancamento;
    int qtdMusicas;
    Musica *musicas;
    int cor;
    Album *esq, *dir;
} Album;

typedef struct Musica {
    char titulo[100];
    int duracao;
    struct Musica* proximo;
    struct Musica* anterior;
} Musica;

typedef struct {
    Musica* inicio;
    Musica* fim;
} ListaDupla;


// -----------------REFERENTE A ARTISTA-----------------
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

int cria_No_Artista(Artista **raiz, char nome_artista[], char estilo_musical[], int num_albuns){
      Artista *new = (Artista *)malloc(sizeof(Artista));
      strcpy(new->nome_artista, nome_artista);
      strcpy(new->estilo_musical, estilo_musical);
      new->num_albuns = num_albuns;
      (*raiz)->cor = RED;
      (*raiz)->esq = NULL;
      (*raiz)->dir = NULL;
      return new;
}

Artista* rotacao_esquerda_artista(Artista **raiz){
      Artista *aux;

      aux = (*raiz)->dir;
      (*raiz)->dir = aux->esq;
      aux->esq = *raiz;
      *raiz = aux;

      (*raiz)->cor = (*raiz)->esq->cor;
      (*raiz)->esq->cor = RED;
}

Artista* rotacao_direita_artista(Artista **raiz){
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

Artista* balanceia_artista(Artista *raiz){

      if (cor((raiz)->dir) == RED && cor((raiz)->esq) == BLACK)
             rotacao_esquerda_artista(&raiz);

      if(cor((raiz)->esq) == RED && cor((raiz)->esq->esq) == RED)
            rotacao_direita_artista(&raiz);

      if(cor((raiz)->esq) == RED && cor((raiz)->dir) == RED)
            troca_Cor_artista(raiz);

      return raiz;
}

int insere_NO_artista(Artista **raiz, char nome_artista[], char estilo_musical[], int num_albuns){
      int criou_no = 0;
      if (*raiz == NULL)
      {
            criou_no = cria_No_Artista(raiz, nome_artista, estilo_musical, num_albuns);
      }
      if (strcmp((*raiz)->nome_artista, nome_artista) == 0)
      {
            criou_no = 2; //Nó já existe
      }else if (strcmp((*raiz)->nome_artista, nome_artista) < 0)
      {
            criou_no = insere_NO_artista(&((*raiz)->dir), nome_artista, estilo_musical, num_albuns);
      }else if (strcmp((*raiz)->nome_artista, nome_artista) >  0){
            criou_no = insere_NO_artista(&((*raiz)->esq), nome_artista, estilo_musical, num_albuns);
      }

      balanceia_artista(raiz);

      return criou_no;
}

int insere_RB(Artista **raiz, char nome_artista[], char estilo_musical[], int num_albuns){
      int resposta;

      *raiz = insere_NO_artista(*raiz, nome_artista, estilo_musical, num_albuns);
          if((*raiz) != NULL)
            (*raiz)->cor = BLACK;

      return resposta;
}

Artista* move_esq_red(Artista *raiz){
      troca_Cor_artista(raiz);
      if (cor_artista(raiz->dir->esq) == RED)
      {
            rotacao_direita_artista(raiz->dir);
            rotacao_esquerda_artista(raiz);
            troca_Cor_artista(raiz);
      }
      return raiz;
}

Artista* move_dir_red(Artista *raiz){
      troca_Cor_artista(raiz);
      if (cor_artista(raiz->esq->esq) == RED)
      {
            rotacao_direita_artista(raiz);
            troca_Cor_artista(raiz);
      }
      return raiz;
}

Artista* remove_menor(Artista *raiz){
      if (raiz->esq == NULL)
      {
            free(raiz);
      }if (cor_artista(raiz->esq) == BLACK && cor_artista(raiz->esq->esq) == BLACK)
      {
            move_esq_red(raiz);
      }
      
      remove_menor(raiz->esq);
      return balanceia_artista(raiz);
}

Artista* procuraMenor(Artista* atual){
      Artista *no1 = atual;
      Artista *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

Artista* buscarFolha_artista(Artista *ultimo){
    // vai procurar o maior filho a esquerda do no.
    // quando encontra-lo a variavel aux vai pegar esse valor.
    if(ultimo->dir != NULL){
        buscarFolha_artista(ultimo->dir);
    }else{
        return ultimo;
    }
}

Artista* remove_NO_artista(Artista** raiz, char nome_artista[]){
    int remove = 0;
    Artista *aux = NULL;

    if (*raiz != NULL) {
        if (strcmp((*raiz)->nome_artista, nome_artista) == 0) {
            aux = *raiz;

            if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
                // Caso 1: Nó sem filhos
                free(aux);
                *raiz = NULL;
            } else if ((*raiz)->esq == NULL || (*raiz)->dir == NULL) {
                // Caso 2: Nó com um filho
                *raiz = ((*raiz)->esq != NULL) ? (*raiz)->esq : (*raiz)->dir;
                free(aux);
            } else {
                // Caso 3: Nó com dois filhos
                aux = buscarFolha_artista(&(*raiz)->esq);
                strcpy(&(*raiz)->nome_artista,aux->nome_artista);
                remove_NO_artista(&(*raiz)->esq, aux->nome_artista);
            }

            remove = 1;
        } else if (strcmp((*raiz)->nome_artista, nome_artista) < 0) {
            remove = remove_NO_artista(&((*raiz)->dir), nome_artista);
        } else if (strcmp((*raiz)->nome_artista, nome_artista) > 0) {
            remove = remove_NO_artista(&((*raiz)->esq), nome_artista);
        }
    }

    balanceia_artista(*raiz);

    return *raiz;
}

// -----------------REFERENTE A ALBUM-----------------

int cor_album(Album *raiz) {
    int cor;
    if (raiz == NULL) {
        cor = BLACK;
    } else {
        cor = raiz->cor;
    }
    return cor;
}

Album* cria_No_Album(Album **raiz, char titulo[], int anoLancamento, int qtdMusicas) {
    Album *new = (Album *)malloc(sizeof(Album));
    strcpy(new->titulo, titulo);
    new->anoLancamento = anoLancamento;
    new->qtdMusicas = qtdMusicas;
    new->cor = RED;
    new->esq = NULL;
    new->dir = NULL;
    return new;
}


Album* rotacao_esquerda_album(Album **no) {
    Album *aux;
    aux = (*no)->dir;
    (*no)->dir = aux->esq;
    aux->esq = *no;
    *no = aux;
    (*no)->cor = (*no)->esq->cor;
    (*no)->esq->cor = RED;
    return *no;
}

Album* rotacao_direita_album(Album **raiz) {
    Album *aux;
    aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;
    *raiz = aux;
    (*raiz)->cor = (*raiz)->dir->cor;
    (*raiz)->dir->cor = RED;
    return *raiz;
}

void troca_Cor_album(Album *raiz) {
    if (raiz != NULL) {
        raiz->cor = !raiz->cor;
        if (raiz->dir)
            raiz->dir->cor = !raiz->dir->cor;
        else if (raiz->esq)
            raiz->esq->cor = !raiz->esq->cor;
    }
}

Album* balanceia_album(Album *raiz) {
    if (cor_album(raiz->dir) == RED && cor_album(raiz->esq) == BLACK)
        raiz = rotacao_esquerda_album(&raiz);

    if (cor_album(raiz->esq) == RED && cor_album(raiz->esq->esq) == RED)
        raiz = rotacao_direita_album(&raiz);

    if (cor_album(raiz->esq) == RED && cor_album(raiz->dir) == RED)
        troca_Cor_album(raiz);

    return raiz;
}

int insere_NO_album(Album **raiz, char titulo[], int anoLancamento, int qtdMusicas) {
    int criou_no = 0;
    if (*raiz == NULL) {
        criou_no = cria_No_Album(raiz, titulo, anoLancamento, qtdMusicas);
    }
    if (strcmp((*raiz)->titulo, titulo) == 0) {
        criou_no = 2; // Nó já existe
    } else if (strcmp((*raiz)->titulo, titulo) < 0) {
        criou_no = insere_NO_album(&((*raiz)->dir), titulo, anoLancamento, qtdMusicas);
    } else if (strcmp((*raiz)->titulo, titulo) > 0) {
        criou_no = insere_NO_album(&((*raiz)->esq), titulo, anoLancamento, qtdMusicas);
    }

    balanceia_album(*raiz);

    return criou_no;
}

int insere_RB_album(Album **raiz, char titulo[], int anoLancamento, int qtdMusicas) {
    int resposta;
    *raiz = insere_NO_album(*raiz, titulo, anoLancamento, qtdMusicas);
    if ((*raiz) != NULL)
        (*raiz)->cor = BLACK;
    return resposta;
}

Album* move_esq_red_album(Album *raiz) {
    troca_Cor_album(raiz);
    if (cor_album(raiz->dir->esq) == RED) {
        rotacao_direita_album(raiz->dir);
        rotacao_esquerda_album(raiz);
        troca_Cor_album(raiz);
    }
    return raiz;
}

Album* move_dir_red_album(Album *raiz) {
    troca_Cor_album(raiz);
    if (cor_album(*raiz->esq->esq) == RED) {
        rotacao_direita_album(raiz);
        troca_Cor_album(raiz);
    }
    return raiz;
}

Album* remove_menor_album(Album *raiz) {
    if (raiz->esq == NULL) {
        free(raiz);
    }
    if (cor_album(raiz->esq) == BLACK && cor_album(raiz->esq->esq) == BLACK) {
        raiz = move_esq_red_album(raiz);
    }

    remove_menor_album(raiz->esq);
    return balanceia_album(raiz);
}

Album* procuraMenor_album(Album* atual) {
    Album *no1 = atual;
    Album *no2 = atual->esq;
    while (no2 != NULL) {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

Album* buscarFolha_album(Album *ultimo) {
    if (ultimo->dir != NULL) {
        buscarFolha_album(ultimo->dir);
    } else {
        return ultimo;
    }
}

Album* remove_NO_album(Album** raiz, char titulo[]) {
    int remove = 0;
    Album *aux = NULL;

    if (*raiz != NULL) {
        if (strcmp((*raiz)->titulo, titulo) == 0) {
            aux = *raiz;

            if ((*raiz)->esq == NULL && (*raiz)->dir == NULL) {
                free(aux);
                *raiz = NULL;
            } else if ((*raiz)->esq == NULL || (*raiz)->dir == NULL) {
                *raiz = ((*raiz)->esq != NULL) ? (*raiz)->esq : (*raiz)->dir;
                free(aux);
            } else {
                aux = buscarFolha_album(&(*raiz)->esq);
                strcpy((*raiz)->titulo,aux->titulo);
                remove_NO_album(&(*raiz)->esq, aux->titulo);
            }

            remove = 1;
        } else if (strcmp((*raiz)->titulo, titulo) < 0) {
            remove = remove_NO_album(&((*raiz)->dir), titulo);
        } else if (strcmp((*raiz)->titulo, titulo) > 0) {
            remove = remove_NO_album(&((*raiz)->esq), titulo);
        }
    }

    balanceia_album(*raiz);

    return *raiz;
}

// -----------------REFERENTE A MUSICA-----------------


void inicializarLista(ListaDupla* lista) {
    lista->inicio = NULL;
    lista->fim = NULL;
}

// Função para adicionar uma música no final da lista
void adicionarMusica(ListaDupla* lista, Musica novaMusica) {
    Musica* novoNo = (Musica*)malloc(sizeof(Musica));
    if (novoNo == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        exit(EXIT_FAILURE);
    }

    novoNo->proximo = NULL;
    novoNo->anterior = NULL;
    novoNo->duracao = novaMusica.duracao;
    strcpy(novoNo->titulo, novaMusica.titulo);

    if (lista->inicio == NULL) {
        // Lista vazia
        lista->inicio = novoNo;
        lista->fim = novoNo;
    } else {
        // Adiciona o novo nó no final da lista
        novoNo->anterior = lista->fim;
        lista->fim->proximo = novoNo;
        lista->fim = novoNo;
    }
}

// Função para imprimir todas as músicas na lista
void imprimirLista(ListaDupla lista) {
    if (lista.inicio == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    Musica* atual = lista.inicio;
    while (atual != NULL) {
        printf("Título: %s, Duração: %d\n", atual->titulo, atual->duracao);
        atual = atual->proximo;
    }
}

// Função para liberar a memória alocada para a lista
void liberarLista(ListaDupla* lista) {
    Musica* atual = lista->inicio;
    while (atual != NULL) {
        Musica* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    lista->inicio = NULL;
    lista->fim = NULL;
}