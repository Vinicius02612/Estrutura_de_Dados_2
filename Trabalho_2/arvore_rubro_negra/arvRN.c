#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <time.h>
#include "arvRN.h"

#define RED 1
#define BLACK 0



typedef struct musica {
    char titulo[100];
    int duracao;
}Musica;

typedef struct dadoArtista{
    char nome_artista[50];
    char estilo_musical[50];
    int num_albuns;
}DadoArtista;

typedef struct dadoAlbum{
    char titulo[100];
    int anoLancamento;
    int qtdMusicas;
}DadoAlbum;

typedef struct listaDupla{
    Musica *muicas;
    ListaDupla* anterior;
    ListaDupla* proximo;
}ListaDupla;

typedef struct album{
    DadoAlbum *info;
    ListaDupla *musicas;
    int cor;
    Album *esq, *dir;
} Album;
//avore artista
typedef struct artista{
    DadoArtista *info;
    Album *album; 
    int cor;
    Artista *esq, *dir;
}Artista;


// -----------------REFERENTE A ARTISTA-----------------
int cor(Artista *raiz){
   if(raiz == NULL){
        return BLACK;
   }else{
        return raiz->cor;
   }
}


Artista *cria_No_Artista(){
    Artista *raiz = (Artista*)malloc(sizeof(Artista));
    if(raiz != NULL)
        raiz = NULL;
    return raiz; 
}

Artista* rotacao_esquerda_artista(Artista *raiz){
      Artista *aux;

      aux = raiz->dir;
      raiz->dir = aux->esq;
      aux->esq = raiz;
      aux->cor = raiz->cor;
      raiz->cor = RED;

      return aux;
}

Artista* rotacao_direita_artista(Artista *raiz){
    Artista *aux;

      aux = raiz->esq;
      raiz->esq = aux->dir;
      aux->dir = raiz;
      aux->cor = raiz->cor;
      raiz->cor = RED;

    return aux;
}

void troca_Cor_artista(Artista *raiz){
    raiz->cor = !raiz->cor;
    if(raiz->esq  !=  NULL)
        raiz->esq->cor = !raiz->esq->cor;
    if(raiz->dir != NULL)
        raiz->dir->cor = !raiz->dir->cor;
}

Artista* balanceia_artista(Artista *raiz){
    // no vermelho é sempre filho á esquerda
    if(cor(raiz->dir) == RED){
        raiz = rotacao_esquerda_artista(raiz);
    }
    //Filho da esquerda e neto da esquerda são vermelhos
    if(raiz->esq != NULL && cor(raiz->esq) == RED && cor(raiz->esq->esq) == RED){
        raiz = rotacao_direita_artista(raiz);
    }

    // 2 filhos são vermelhos
    if(cor(raiz->esq) == RED && cor(raiz->dir) == RED){
        troca_Cor_artista(raiz);
    }

    return raiz;
}

DadoArtista *lerInformacaoArtista(){
    DadoArtista *infoArtista = (DadoArtista*)malloc(sizeof(DadoArtista));
    char nome_artista[50], estilo_musical[50], titulo_Alum[50], titulo_Musica[50];
    printf("Nome do Artista: \n");
    scanf("%s", nome_artista);
    strcpy(infoArtista->nome_artista,nome_artista);
    printf("Estilo Musical \n");
    scanf("%s", estilo_musical);
    strcpy(infoArtista->estilo_musical,estilo_musical);
    infoArtista->num_albuns = 0;
    return infoArtista;
}

// lembrar de passar para implementação com ponteiros de ponteiro
Artista *insere_NO_artista(Artista **raiz, DadoArtista *InfoArtista){
    if(*raiz == NULL){
        Artista *novoArtista;
        novoArtista = (Artista*)malloc(sizeof(Artista));
        novoArtista->info = InfoArtista;
        novoArtista->album = NULL;
        novoArtista->cor = RED;
        novoArtista->dir = NULL;
        novoArtista->esq = NULL;

        return novoArtista;

    }else{
    /* 
     A função strcmp devolve um valor inteiro que indica o relacionamento entre string1 e string2:
     Um valor menor que zero significa que string1 é menor que string2. 
     Um valor zero significa que ambas as strings são iguais.
     Um valor maior que zero significa que string1 é maior que string2.
    
    */
        if(strcmp(InfoArtista->nome_artista, (*raiz)->info->nome_artista) == 0){
            printf("Um os Artista não podem ter nome iguais\n");
        }else{
            if(strcmp(InfoArtista->nome_artista, (*raiz)->info->nome_artista) < 0){
                (*raiz)->esq = insere_NO_artista(&((*raiz)->esq), InfoArtista);
            }else if(strcmp(InfoArtista->nome_artista, (*raiz)->info->nome_artista) > 0){
                (*raiz)->dir = insere_NO_artista(&((*raiz)->dir), InfoArtista);
            }
        }
    }
    *raiz = balanceia_artista(*raiz);
    return *raiz;

}

int insere_RB(Artista **raiz, DadoArtista *InfoArtista){
    int resposta = 0;
    *raiz = insere_NO_artista(raiz, InfoArtista);
    if(*raiz != NULL){
        (*raiz)->cor = BLACK;
        resposta = 1;
    }
    return resposta;
}

Artista * buscaArtista(Artista **raiz, char nome_artista[]){
    Artista *achou;
    achou = NULL;
    if(*raiz != NULL){
        if(strcmp(nome_artista, (*raiz)->info->nome_artista) == 0){
            achou = *raiz;
        }else{
            if(strcmp( nome_artista , (*raiz)->info->nome_artista) < 0){
               achou = buscaArtista(&((*raiz)->esq), nome_artista);
            }else if(strcmp( nome_artista , (*raiz)->info->nome_artista) > 0){
               achou = buscaArtista(&((*raiz)->dir), nome_artista);
            }
        }
    }
    return achou ;
}

// função que adiciona o album ao artista selecionado pelo nome.
Artista *adcionaAlbumEmArtista( Artista *artista,char nome_artista[], Album *album){
    if(artista != NULL){
        artista->album = album;
        artista->info->num_albuns += 1;
    }
    return artista;
}

Artista* move_esq_red(Artista *raiz){
    troca_Cor_artista(raiz);
    if (cor(raiz->dir->esq) == RED)
    {   
            raiz->dir = rotacao_esquerda_artista(raiz->dir);
            raiz = rotacao_esquerda_artista(raiz);
            troca_Cor_artista(raiz);
    }
    return raiz;
}

Artista* move_dir_red(Artista *raiz){
      troca_Cor_artista(raiz);
      if (cor(raiz->esq->esq) == RED)
      {
            raiz = rotacao_direita_artista(raiz);
            troca_Cor_artista(raiz);
      }
      return raiz;
}

Artista* remove_menor(Artista *raiz){
      if (raiz->esq == NULL)
      {
            free(raiz);
            return NULL;
      }if (cor(raiz->esq) == BLACK && cor(raiz->esq->esq) == BLACK)
      {
            move_esq_red(raiz);
      }
      
      raiz->esq = remove_menor(raiz->esq);
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

Artista* buscarFolha_artista(Artista **ultimo){
    // vai procurar o maior filho a esquerda do no.
    // quando encontra-lo a variavel aux vai pegar esse valor.
    if((*ultimo)->dir != NULL){
        buscarFolha_artista(&(*ultimo)->dir);
    }else{
        return NULL;
    }
}

Artista *remove_NO_artista(Artista **raiz, char nome_artista[]){
    if(*raiz != NULL){
        if(strcmp(nome_artista, (*raiz)->info->nome_artista) < 0){
            if(cor((*raiz)->esq) == BLACK && cor((*raiz)->esq->esq) == BLACK){
                (*raiz) = move_esq_red(*raiz);

            }
            (*raiz)->esq = remove_NO_artista((&(*raiz)->esq), nome_artista);
        }else{
            if(cor((*raiz)->esq) == RED){
                (*raiz) = rotacao_direita_artista(*raiz);
            }

            if(strcmp(nome_artista, (*raiz)->info->nome_artista) == 0 && ((*raiz)->dir == NULL)){ 
                free(*raiz);
                return NULL;
            }

            if(cor((*raiz)->dir) == BLACK && cor((*raiz)->esq) == BLACK){
                (*raiz) = move_dir_red(*raiz);
            }
            if(strcmp(nome_artista, (*raiz)->info->nome_artista) == 0){
                Artista *aux = procuraMenor((*raiz)->dir);
                (*raiz)->info = aux->info;
                (*raiz)->dir = remove_menor((*raiz)->dir);
            }else{
                (*raiz)->dir = remove_NO_artista(&((*raiz)->dir), nome_artista);
            }

        }
    }else{
        printf("Arvore vazia\n");
    }
    *raiz = balanceia_artista(*raiz);
    return  *raiz;
}

int remove_arvRB(Artista **raiz, char nome_artista[]){
    *raiz = remove_NO_artista(raiz, nome_artista);
    if(*raiz != NULL){
        (*raiz)->cor = BLACK;
        return 1;
    }else{
        return 0;
    }
}



void imprimirArtista(Artista *raiz, int nivel){
    if(raiz != NULL){
        imprimirArtista(raiz->esq, nivel + 1);

        if((*raiz).cor == RED){
            printf("\nNome artista:%s \nEstilo musical: %s\n Quantidade de Albuns: %d \n",raiz->info->nome_artista,raiz->info->estilo_musical,raiz->info->num_albuns );
            printf("\n");
        }else{
            printf("Nome artista:%s \nEstilo musical: %s\n Quantidade de Albuns: %d \n",raiz->info->nome_artista,raiz->info->estilo_musical,raiz->info->num_albuns );
            printf("\n");
            if(raiz->album != NULL){
                imprimeAlbum(raiz->album, 0);
            }
        }
        imprimirArtista(raiz->dir, nivel + 1);
    }
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

Album* cria_No_Album() {
    Album *raiz = (Album *)malloc(sizeof(Album));
    if(raiz != NULL){
        raiz = NULL;
    }
    
    return raiz;
}

DadoAlbum *lerDadosAlbum(){

    DadoAlbum *infoAlbum;
    infoAlbum = (DadoAlbum*)malloc(sizeof(DadoAlbum));
    char titulo[100];
    int anoLancamento;
    int qtdMusicas;

    printf("Titulo \n");
    scanf("%s", titulo);
    strcpy(infoAlbum->titulo,titulo);

    printf("Ano de lançamento: \n");
    scanf("%d", &anoLancamento);
    infoAlbum->anoLancamento = anoLancamento;
    infoAlbum->qtdMusicas = 0;

    return infoAlbum;
}

Album* rotacao_esquerda_album(Album *raiz) {
    Album *aux;
    aux = raiz->dir;
    raiz->dir = aux->esq;
    aux->esq = raiz;
    aux->cor = raiz->cor;
    raiz->cor = RED;
    return aux;
}

Album* rotacao_direita_album(Album *raiz) {
    Album *aux;
    aux = raiz->esq;
    raiz->esq = aux->dir;
    aux->dir = raiz;
    aux->cor = raiz->cor;
    raiz->cor = RED;
    return aux;
}

void troca_Cor_album(Album *raiz) {
    if (raiz != NULL) {
        raiz->cor = !raiz->cor;
        if (raiz->esq != NULL)
            raiz->esq->cor = !raiz->esq->cor;
        else if (raiz->dir != NULL)
            raiz->dir->cor = !raiz->dir->cor;
    }
}

Album *balanceia_album(Album *raiz){
     if (cor_album(raiz->dir) == RED && cor_album(raiz->esq) == BLACK){
        raiz = rotacao_esquerda_album(raiz);
    }
        

    if (cor_album(raiz->esq) == RED && cor_album(raiz->esq->esq) == RED){
        raiz = rotacao_direita_album(raiz);
    }
        

    if (cor_album(raiz->esq) == RED && cor_album(raiz->dir) == RED){
        troca_Cor_album(raiz);
    }
        
    return raiz;
}

Album *insere_NO_album(Album **raiz, DadoAlbum *dado) {
    Album *novoAlbum;
    if (*raiz == NULL) {
        novoAlbum = (Album*)malloc(sizeof(Album));
        novoAlbum->info = dado;
        novoAlbum->musicas = NULL;
        novoAlbum->cor = RED;
        novoAlbum->dir = NULL;
        novoAlbum->esq = NULL;

        return novoAlbum;
    }else{
        if (strcmp((*raiz)->info->titulo, dado->titulo) < 0) {
            (*raiz)->esq = insere_NO_album(&((*raiz)->esq), dado);
        } else if (strcmp((*raiz)->info->titulo,  dado->titulo) > 0) {
            (*raiz)->dir = insere_NO_album(&((*raiz)->dir),dado);
        }
    }
    
    *raiz = balanceia_album(*raiz);
        
    return *raiz;
}

int insere_RB_album(Album **raiz, DadoAlbum *dado) {
    int resposta;
    *raiz = insere_NO_album(raiz, dado);
    if (*raiz != NULL)
        (*raiz)->cor = BLACK;
        resposta = 1;
    return resposta;
}

Album  *buscaAlbum(Album **raiz, char titulo[]){
    Album *achou;
    achou = NULL;
    if(*raiz != NULL){
        if(strcmp(titulo, (*raiz)->info->titulo) == 0){
            achou = *raiz;
        }else{
            if(strcmp( titulo , (*raiz)->info->titulo) < 0){
               achou = buscaAlbum(&((*raiz)->esq), titulo);
            }else if(strcmp( titulo , (*raiz)->info->titulo) > 0){
               achou = buscaAlbum(&((*raiz)->dir), titulo);
            }
        }
    }
    return achou ;
}

Album *adicionaMusicaAoAlbum( Album *album,char titulo[], ListaDupla *musica){
    if(album != NULL){
        album->musicas = musica;
        album->info->qtdMusicas += 1;
    }
    return album;
}

Album* move_esq_red_album(Album *raiz) {
    troca_Cor_album(raiz);
    if (cor_album(raiz->dir->esq) == RED) {
        raiz->dir =  rotacao_direita_album(raiz->dir);
        raiz = rotacao_esquerda_album(raiz);
        troca_Cor_album(raiz);
    }
    return raiz;
}

Album* move_dir_red_album(Album *raiz) {
    troca_Cor_album(raiz);
    if (cor_album(raiz->esq->esq) == RED) {
        raiz = rotacao_direita_album(raiz);
        troca_Cor_album(raiz);
    }
    return raiz;
}

Album* remove_menor_album(Album *raiz) {
    if (raiz->esq == NULL) {
        free(raiz);
        return NULL;
    }
    if (cor_album(raiz->esq) == BLACK && cor_album(raiz->esq->esq) == BLACK) {
        raiz = move_esq_red_album(raiz);
    }

    raiz->esq = remove_menor_album(raiz->esq);
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
    
    Album *aux;
    aux = NULL;

    if (*raiz != NULL) {
        if(strcmp(titulo, (*raiz)->info->titulo) < 0){
            if(cor_album((*raiz)->esq) == BLACK && cor_album((*raiz)->esq->esq) == BLACK){
                (*raiz) = move_esq_red_album(*raiz);
            }
            (*raiz)->esq = remove_NO_album((&(*raiz)->esq), titulo);
        }else{
            if(cor_album((*raiz)->esq) == RED){
                (*raiz)= rotacao_direita_album(*raiz);
            }

            if(strcmp(titulo, (*raiz)->info->titulo) == 0 && (*raiz)->dir == NULL){
                free(*raiz);
                return NULL;
            }

            if(cor_album((*raiz)->dir) == BLACK && cor_album((*raiz)->esq) == BLACK){
                (*raiz) =  move_dir_red_album(*raiz);
            }
            if(strcmp(titulo, (*raiz)->info->titulo) == 0){
                aux = procuraMenor_album((*raiz)->dir);
                (*raiz)->info = aux->info;
                (*raiz)->dir = remove_menor_album((*raiz)->dir);
            }else{
                (*raiz)->dir = remove_NO_album(&((*raiz)->dir), titulo);
            }
        }
    }

    balanceia_album(*raiz);

    return *raiz;
}
int remove_arvRB_Album(Album **raiz, char titulo[]){
    *raiz = remove_NO_album(raiz, titulo);
    if(*raiz != NULL){
        (*raiz)->cor = BLACK;
        return 1;
    }else{
        return 0;
    }
}

void imprimeAlbum(Album *raiz, int nivel){
    if(raiz != NULL){
        imprimeAlbum(raiz->esq, nivel + 1);

        if((*raiz).cor == RED){
            printf("\nTitulo:%s \nAno de Lançamento: %d\n Quantidade de Musicas: %d \n",raiz->info->titulo,raiz->info->anoLancamento,raiz->info->qtdMusicas );
            printf("\n");
        }else{
            printf("Titulo:%s \nAno de Lançamento: %d\n Quantidade de Musicas: %d \n",raiz->info->titulo,raiz->info->anoLancamento,raiz->info->qtdMusicas );
            printf("\n");
            if(raiz->musicas != NULL){
                imprimirLista(raiz->musicas);
            }
        }
        imprimeAlbum(raiz->dir, nivel + 1);
    }
}

// -----------------REFERENTE A MUSICA-----------------


ListaDupla *inicializarLista() {
    ListaDupla *lista;
    lista = (ListaDupla*)malloc(sizeof(ListaDupla));
    lista->muicas = NULL;
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

        novoNo->muicas = novaMusica;
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


ListaDupla *removerMusica(ListaDupla **lista, char titulo[]){
    ListaDupla *aux, *remove;
    remove = NULL;

    if(*lista != NULL){
        if(strcmp((*lista)->muicas->titulo, titulo) == 0){
            remove = *lista;
            *lista = remove->proximo;
            (*lista)->anterior = NULL;
        }else{
            aux = *lista;
            while (aux->proximo != NULL && strcmp((*lista)->muicas->titulo, titulo) != 0)
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


// Função para imprimir todas as músicas na lista
void imprimirLista(ListaDupla *lista) {
    ListaDupla *aux;
    aux = lista;
    printf("informações da musica \n");
    if(lista != NULL){
        while (aux != NULL) {
            printf("Título: %s, Duração: %d min\n",aux->muicas->titulo, aux->muicas->duracao);
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