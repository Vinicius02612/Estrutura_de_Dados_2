#include <stdlib.h>
#include <stdio.h>
#include "arvRN.h"




int main(){
    DadoArtista *dadoArtista = NULL;
    DadoAlbum *dadoAlb = NULL;
    Artista *artista, *raizArtista ;
    Album *album, *raizAlbum;
    Musica *musica, *raizMusica;
    char nome_artista[50], estilo_musical[50], titulo_Alum[50], titulo_Musica[50];
    int numAlbuns , numLamcamentoAlb, qtdMusica, duracaoMusicea, msc, opc;
    artista = NULL; album = NULL;musica = NULL;
    raizArtista = NULL; raizAlbum = NULL; raizMusica = NULL;

    raizArtista = cria_No_Artista();
    raizAlbum = cria_No_Album();

    do{
        printf("1- Cadastrar Artista\n2- Remover artisa\n3-Cadastrar Album\n4- Remover Album\n4 -  Imprimir tudo \n");
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
                    printf("artista removido com sucesso \n");
                break;
            case 3:
                dadoAlb = lerDadosAlbum();
                msc = insere_RB_album(&raizAlbum, dadoAlb);
                break;
            case 4:
                printf("Digite o nome do artista \n");
                scanf("%s", titulo_Alum);
                int resAlb =  remove_arvRB_Album(&raizAlbum, titulo_Alum);
                if(resAlb  != 0)
                    printf("album removido com sucesso \n");
                break;
            case 5:
                imprimirArtista(raizArtista,0);
                imprimeAlbum(raizAlbum, 0);
        default:
            break;
        }
    } while (opc != 0);
    return 0;

}