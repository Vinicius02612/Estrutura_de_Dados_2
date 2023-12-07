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

Artista rotacao_esquerda_artista(Artista **raiz){
      Artista *aux;

      aux = (*raiz)->dir;
      (*raiz)->dir = aux->esq;
      aux->esq = *raiz;
      *raiz = aux;

      (*raiz)->cor = (*raiz)->esq->cor;
      (*raiz)->esq->cor = RED;
}

Artista rotacao_direita_artista(Artista **raiz){
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

Artista balanceia_artista(Artista *raiz){

      if (cor((raiz)->dir) == RED && cor((raiz)->esq) == BLACK)
             rotacao_esquerda_artista(&raiz);

      if(cor((raiz)->esq) == RED && cor((raiz)->esq->esq) == RED)
            rotacao_direita_artista(&raiz);

      if(cor((raiz)->esq) == RED && cor((raiz)->dir) == RED)
            troca_Cor_artista(raiz);

      //return raiz;
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

Artista move_esq_red(Artista *raiz){
      troca_Cor_artista(raiz);
      if (cor_artista(raiz->dir->esq) == RED)
      {
            rotacao_direita_artista(raiz->dir);
            rotacao_esquerda_artista(raiz);
            troca_Cor_artista(raiz);
      }
      //return raiz;
}

Artista move_dir_red(Artista *raiz){
      troca_Cor_artista(raiz);
      if (cor_artista(raiz->esq->esq) == RED)
      {
            rotacao_direita_artista(raiz);
            troca_Cor_artista(raiz);
      }
      //return raiz;
}

Artista remove_menor(Artista *raiz){
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

Artista* remove_NO_artista(Artista** raiz, char nome_artista[]) {
    int removeu = 0;
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
                aux = buscarFolha(&(*raiz)->esq);
                (*raiz)->nome_artista = aux->nome_artista;
                remove_NO_artista(&(*raiz)->esq, aux->nome_artista);
            }

            removeu = 1;
        } else if (strcmp((*raiz)->nome_artista, nome_artista) < 0) {
            removeu = remove_NO_artista(&((*raiz)->dir), nome_artista);
        } else if (strcmp((*raiz)->nome_artista, nome_artista) > 0) {
            removeu = remove_NO_artista(&((*raiz)->esq), nome_artista);
        }
    }

    // Não esqueça de chamar a função de balanceamento após a remoção
    balanceia_artista(*raiz);

    return *raiz;
}

// Artista* remove_NO_artista(struct Artista** raiz, char nome_artista[]){
//       int removeu = 0;
//       Artista *aux = NULL;
//       if (*raiz != NULL)
//       {
//             if (strcmp((*raiz)->nome_artista, nome_artista) == 0)
//             {
//             if((*raiz)->esq == NULL && (*raiz)->dir == NULL){
//                 aux = *raiz;
//                 (*raiz) = NULL;
//             }else if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
//                 if((*raiz)->esq != NULL){
//                     aux = *raiz;
//                     *raiz = (*raiz)->esq;
//                 }else{
//                     aux = *raiz;
//                     *raiz = (*raiz)->dir;
//                 }
//             }else{
//                 aux = buscrFolh((*raiz)->esq);
//                 *raiz = aux;
//                 aux = NULL;
//             }
//             free(aux);
//             removeu = 1;
//         }else if(strcmp((*raiz)->info->nome_artista, nome_artista) < 0){
//             removeu = remove_NO_artista(&((*raiz)->dir), nome_artista);
//         }else if(strcmp((*raiz)->info->nome_artista, nome_artista) > 0){
//             removeu = remove_NO_artista(&((*raiz)->esq), nome_artista);
//         }
//       }
//       balanceia_artista(*raiz);
//       return removeu;
// }











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