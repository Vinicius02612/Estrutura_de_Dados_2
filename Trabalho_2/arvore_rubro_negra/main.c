#include <stdlib.h>
#include <stdio.h>
#include "arvRN.h"




int main(){
    DadoArtista *dadoArtista = NULL;
    Artista *artista, *raizArtista ;
    Album *album, *raizAlbum;
    Musica *musica, *raizMusica;
    char nome_artista[50], estilo_musical[50], titulo_Alum[50], titulo_Musica[50];
    int numAlbuns , numLamcamentoAlb, qtdMusica, duracaoMusicea, msc, opc;
    artista = NULL; album = NULL;musica = NULL;
    raizArtista = NULL; raizAlbum = NULL; raizMusica = NULL;

    raizArtista = cria_No_Artista();

    do{
        printf("1- Cadastrar Artista\n2- Remover artisa\n3-Cadastrar Musica\n4- Imprime Artista\n");
        scanf("%d", &opc);
        switch (opc)
        {
            case 1:
                dadoArtista = lerInformacaoArtista();
                msc = insere_RB(&raizArtista, dadoArtista);
                if(msc != 0)
                    printf("inserção arvore realizada com sucesso!\n");
                break;
            case 2:
                printf("Digite o nome do artista \n");
                scanf("%s", nome_artista);
                int res = remove_arvRB(&raizArtista, nome_artista);
                if(res != 0)
                    printf("no removido com sucesso \n");

                break;
            case 3:
                break;
            case 4:
                imprimirArtista(raizArtista, 0);
                break;
        default:
            break;
        }
    } while (opc != 0);
    return 0;

}