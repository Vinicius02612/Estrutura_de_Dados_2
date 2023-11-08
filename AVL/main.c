#include <stdio.h>
#include <stdlib.h>
#include "avl.h"




int main(){

    int opc,id, codigo, numTemporadas, codigoSerie;
    int numTemp,quantEpisodio;
    char titulo[50], ano[50], tituloTemoporada[50], nomeDoArtista[50],  nomeDoPersongem[50],  descricao[50];
    Serie *raizS, *DadoSerie = NULL;
    Temporada  *raizT, *DadoTemporada = NULL;
    Participantes *listaParticipante = NULL;


    do{
        printf("1 - Inserir Serie\n2 - Imprimir Series por código\n3 - Inserir Temporada\n4 - Imprimir Temporada\n5 - Inserir Participantes\n6 - Imprimir Participantes\n7 - imprimir todas as series\n");
        scanf("%d", &opc);
        switch (opc)
        {
            case 1:
                printf("Codigo:");
                scanf(" %d", &codigo);
                printf("Numero da serie: \n");
                scanf(" %d", &numTemporadas);
                printf("Titulo da serie:");
                scanf(" %s", titulo);
                DadoSerie = criaNoSerie(codigo, titulo, numTemporadas);
                insere_Serie(&raizS, DadoSerie);
                break;
            case 2:
                printf("Insira o codigo da series: \n");
                scanf(" %d", &codigoSerie);
                imprime_Serie_Por_Codigo(raizS, codigoSerie);
                break;
            case 3:
                imprime_todas_Series(raizS);
                printf("Insira o codigo da serie que deseja cadastrar temporada: \n");
                scanf(" %d", &codigoSerie);
                printf("Número da temporada: ");
                scanf(" %d", &numTemp);
                printf("Quantidade de episódios: ");
                scanf(" %d", &quantEpisodio);
                printf("Título da temporada: ");
                scanf(" %s", tituloTemoporada);
                printf("Ano da temporada: ");
                scanf(" %s", ano);
                DadoTemporada  = criaNoTemp(codigoSerie,numTemp, titulo, quantEpisodio, ano, listaParticipante );
                insere_Temp(&raizT, DadoTemporada);
                inserirTemporada(raizS, raizT);
                break;
            case 4:
                imprime_temporada(raizT);
                break;
            case 5:
                printf("Voce escolheu inserir participante: \n");
                printf("Id do artista: \n");
                scanf("%d", &id);
                printf("Nome do artista:\n");
                scanf("%s", nomeDoArtista);
                printf("Nome do Personagem: \n");
                scanf("%s", nomeDoPersongem);
                printf("Descricao: \n");
                scanf("%s", descricao);
                listaParticipante = insereParticipante(listaParticipante, id, nomeDoArtista, nomeDoPersongem, descricao);
                break;
            case 6:
                imprimeParticipante(listaParticipante);
                break;
            case 7:
                imprime_todas_Series(raizS);
                break;
            default:
                break;
        }
    }while(opc != 0);

    return 0;
}
