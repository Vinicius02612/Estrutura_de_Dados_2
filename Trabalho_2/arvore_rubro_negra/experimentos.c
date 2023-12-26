#include <stdlib.h>
#include <stdio.h>
#include "arvRN.h"


int main(){
    DadoArtista *dadoArtista;
    DadoAlbum *dadoAlb;
    Artista *artista, *raizArtista, *bscArtista ;
    Album *album, *raizAlbum, *busca;
    Musica *musica;
    ListaDupla *listaDupMusica, *remove;



    char nome_artista[50], estilo_musical[50], titulo_Alum[50], titulo_Musica[50];
    int numAlbuns , numLamcamentoAlb, qtdMusica, duracaoMusicea, msc, opc, res = 0;
    artista = NULL; album = NULL;musica = NULL;dadoArtista = NULL; dadoAlb = NULL;
    raizArtista = NULL; raizAlbum = NULL; bscArtista = NULL;remove = NULL;

    raizArtista = cria_No_Artista();
    raizAlbum = cria_No_Album();
    listaDupMusica = inicializarLista();

    dadoArtista = lerInformacaoArtista();
    insere_RB(raizArtista,dadoArtista);


    buscaArtista(raizAlbum, "vini");
    return 0;
}