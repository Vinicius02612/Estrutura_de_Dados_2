#include <stdio.h>
#include <stdlib.h>
#include "arv23.h"


int main(){
    Artista *dadoArtista;
    Arv23_artista *raiz, *busca;
    char nome_artista[50];
    int opc;
    raiz = NULL; dadoArtista = NULL;busca = NULL;
    do
    {
        printf("Informe a opção desejada: \n");
        printf(
            "1 - Cadastrar Artista \n"
            "2 - Remover Artista \n"
            "3 - Imprimir artista \n"
            "4 - Buscar Artista \n"
        );
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            dadoArtista = lerDadosArtista();
            if(dadoArtista != NULL)
                printf("Dado lido\n");
            raiz = insere_no_artista(&raiz,dadoArtista, NULL, NULL);
            if(raiz != NULL){
                printf("Dado inserido com sucesso \n");
            }else{
                printf("Não foi possivel inserir o dados ");
            }
            break;
        case 2:
            printf("Digite o nome do artista que deseja remover \n");
            scanf("%s", nome_artista);
            RemoveArtista23(&raiz, NULL, nome_artista, 0, "n");
        case 3:
            imprimirArtista(raiz, 0);
            break;
        case 4:
            printf("Digite o nome do artista que deseja remover \n");
            scanf("%s", nome_artista);
            busca = buscarArtista(&raiz, nome_artista);
            imprimirArtista(raiz, 0);


        default:
            printf("Informe uma opção válida");
            break;
        }

    } while (opc != 0);
    


    return 0;
}