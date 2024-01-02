#include <stdio.h>
#include <stdlib.h>
#include "arv23.h"


int main(){
    Artista *dadoArtista, *busca;
    Album *dadaAlbum, *buscaAlbum;
    Arv23_album *raiz;
    Arv23_artista *raizAlbum;
    char nome_artista[50], titulo;
    int opc;
    raiz = NULL; dadoArtista = NULL;busca = NULL;raizAlbum = NULL; buscaAlbum  = NULL; dadaAlbum = NULL;
    do
    {
        printf("Informe a opção desejada: \n");
        printf(
            "1 - Cadastrar Artista \n"
            "2 - Cadastrar Album \n"
            "3 - Cadastrar Musica \n"
            "4 - Buscar Artista \n"
            "5 - Buscar Album \n"
            "6 - Buscar Musica \n"

        );
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            dadoArtista = lerDadosArtista();
            if(dadoArtista != NULL)
                printf("Dado lido\n");
            raiz = insere_no_artista(&raiz,dadoArtista, NULL, NULL);
            if(raiz == NULL){
                printf("Dado inserido com sucesso \n");
            }else{
                printf("Não foi possivel inserir o dados ");
            }
            break;
        case 2:
            
            break;
        case 3:
            imprimirArtista(raiz, 0);
            break;
        case 4:
            printf("Digite o nome do artista que deseja remover \n");
            scanf("%s", nome_artista);
            busca = buscarArtista(raiz, nome_artista);
            imprimeDadoArtista(busca);
        default:
            printf("Informe uma opção válida");
            break;
        }

    } while (opc != 0);
    


    return 0;
}