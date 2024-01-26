#include <stdio.h>
#include <stdlib.h>
#include "arv23.h"


int main(){
    Artista *dadoArtista, *buscaArtista;
    Album *dadaAlbum, *buscaAlbum;
    Musica *dadoMusica, *buscaMusica;
    ListaDupla  *listaMusica;
    Arv23_album *raizAlbum;
    Arv23_artista *raizArtista;
    char nome_artista[50], titulo[50];
    int opc;
    raizArtista = inicializaArtista();
    raizAlbum = inicializAlbum();
    listaMusica = inicializarLista();
    do
    {
        printf("Informe a opção desejada: \n");
        printf(
            "1 - Cadastrar Artista\n"
            "2 - Cadastrar Album\n"
            "3 - Cadastrar Musica\n"
            "\n"
            "4 - Buscar Artista\n"
            "5 - Buscar Album\n"
            "6 - Buscar Musica\n"
            "\n"
            "7 - Remover Artista\n"
            "8 - Remover Album\n"
            "9 - Remover Musica\n"
            "\n"
        );
        scanf("%d", &opc);
        switch (opc)
        {
            case 1:
                dadoArtista = lerDadosArtista();
                raizArtista = insere_no_artista(&raizArtista,dadoArtista, NULL, NULL);
                if(raizArtista != NULL){
                    printf("Dado inserido com sucesso \n");
                }else{
                    printf("Não foi possivel inserir o dados ");
                }
                break;
            case 2:
                printf("Digite o nome do artista que deseja cadastrar o album \n");
                scanf("%s", nome_artista);
                buscaArtista = buscarArtista(raizArtista, nome_artista);
                if(buscaArtista != NULL){
                    dadaAlbum = lerDadoAlbum();
                    raizAlbum = insere_no_album(&raizAlbum, dadaAlbum, NULL, NULL);
                }else{
                    printf("nenhum dado encontrado com esse nome \n");
                }
                break;
            case 3:
                printf("Digite o titulo do album que deseja cadastrar a musica \n");
                scanf("%s", titulo);
                buscaAlbum = buscarAlbum(raizAlbum, titulo);
                if(buscaAlbum != NULL){
                    dadoMusica = lerDadosMusica();
                    listaMusica = adicionarMusica(&listaMusica, dadoMusica);
                }else{
                    printf("Nenhum album econtrada com esse titulo \n");
                }
                break;
            case 4:
                printf("Digite o nome do artista que deseja buscar \n");
                scanf("%s", nome_artista);
                buscaArtista = buscarArtista(raizArtista, nome_artista);
                imprimeDadoArtista(buscaArtista);
                break;
            case 5:
                printf("Digite o titulo do album que deseja buscar\n ");
                scanf("%s", titulo);
                buscaAlbum = buscarAlbum(raizAlbum, titulo);
                imprimeDadoAlbum(buscaAlbum);
                break;
            case 6:
                printf("Digite o nome da musica\n");
                scanf("%s", titulo);
                buscaMusica = buscarMusica(listaMusica, titulo);
                imprimeDadoMusica(buscaMusica);
                break;
            case 7:
                printf("Digite o nome do artista que deseja remover\n");
                scanf("%s", nome_artista);
                RemoveArtista23(&raizArtista, NULL, nome_artista, -1, "");
            default:
                printf("Informe uma opção válida");
                break;
            }

    } while (opc != 0);
    


    return 0;
}