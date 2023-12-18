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

    do{
        printf(
                "1 - Cadastrar Artista\n"
                "2 - Cadastrar Album\n"
                "3 - Cadastrar Musica\n"
                "4 - Remover Artista\n"
                "5 - Remover Album\n"
                "6 - Remover Musica\n"
                "7 - Imprimir Artista\n"
                "8 - Imprimir Album\n"
                "9 - Imprimir Musica\n"

            );
        scanf("%d", &opc);
        switch (opc)
        {
            case 1: // cadastrar artista
                dadoArtista = lerInformacaoArtista();
                msc = insere_RB(&raizArtista, dadoArtista);
                if(msc != 0)
                    printf("inserção arvore realizada com sucesso!\n");
                break;
            case 2: // cadastrar album, album só deve ser cadastrado se houver artista cadastrado
                printf("Digite o nome do artista para qual deseja cadastrar o album \n");
                scanf("%s", nome_artista);
                
                bscArtista = buscaArtista(&raizArtista, nome_artista);
                if(bscArtista != NULL){
                    dadoAlb = lerDadosAlbum();
                    msc = insere_RB_album(&raizAlbum, dadoAlb);
                    if(msc == 1)
                        raizArtista = adcionaAlbumEmArtista(bscArtista,nome_artista, raizAlbum);
                        printf("Album cadastrado com sucesso!\n");
                }else{
                    printf("Não existe nenhum artista cadastrado com esse nome\n");
                }
                break;
            case 3:// cadastrar musica0  
                // função para inserir musica, musica so deve ser inserida se houver musica cadastrada
                printf("Digite o titulo do album para qual deseja cadastrar uma musica \n"); // ver uma forma de ligar musica ao album
                scanf("%s", titulo_Alum);
                busca = buscaAlbum(&raizAlbum, titulo_Alum);
                if(busca != NULL){
                    musica = lerDadosMusica();
                    listaDupMusica = adicionarMusica(&listaDupMusica, musica);
                    if(listaDupMusica != NULL){
                        raizAlbum = adicionaMusicaAoAlbum(busca,titulo_Alum,listaDupMusica);
                        printf("Musica inserida com sucesso! \n");
                    }
                }else{
                    printf("não foi possivel inserir musica \n");
                }
                break;
            case 4: // remover um artista
                 printf("Digite o nome do artista \n");
                scanf("%s", nome_artista);
                res = remove_arvRB(&raizArtista, nome_artista);
                if(res != 0)
                    printf("artista removido com sucesso \n");
                break;
            case 5:
                printf("Digite o titulo do album \n");
                scanf("%s", titulo_Alum);
                res =  remove_arvRB_Album(&raizAlbum, titulo_Alum);
                if(res != 0)
                    printf("album removido com sucesso \n");
                break;
            case 6:
                printf("Digite o nome da musica que deseja remover\n");
                scanf("%s", nome_artista);
                remove = removerMusica(&listaDupMusica, titulo_Musica);
                if(remove != NULL){
                    printf("Musica removida com sucesso");
                }
                break;
            case 7:
                imprimirArtista(raizArtista, 0);
                break;
            case 8:
                imprimeAlbum(raizAlbum, 0);
                break;
            case 9:
                imprimirLista(listaDupMusica);
                break;
        default:
            break;
        }
    } while (opc != 0);
    return 0;

}