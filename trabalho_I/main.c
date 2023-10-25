#include <stdio.h>
#include <stdlib.h>
#include "arvBin.h"
#include <string.h>

int main(){
    Serie *serie = NULL, *raizS = NULL;
    Temporada *temporada = NULL, *raizT = NULL;
    Participantes *particpante = NULL;


    int opc, codigo,numTemp,numTempo, quantEp;
    char titulo[50],ano[50],nomeArtista[50], nomeParticipante[50], descricao[50];

    do{
        printf( "1 - Cadastrar Série \n "
                "2 - Cadastrar Temporada \n"
                "3 - Inserir Participante\n"
                "4 - Imprimir os dados de todas as temporadas de uma série \n "
                "5 - Imprimir todos os personagens de uma determinada temporada \n"
                "6 - Imprimir o nome de todos os artistas que interpretaram um determinado personagem em todas as emporadas de uma dada série \n"
        );
        scanf("%d", &opc);
        switch (opc)
        {
        case 1:
            codigo = 10;
            strcpy(titulo, "Sem dinheiro");
            numTemp = 3;
            serie = criaNoSerie(codigo, titulo, numTemp);
            serie = (raizS, serie);
            break;
        case 2:
            numTempo = 2;
            strcpy(titulo, "sei la");
            quantEp = 4;
            strcpy(ano, "2023");
            temporada = criarTemporada(numTempo, titulo,quantEp, ano);
            temporada = (raizT, temporada);
            inserirTemporadaAserie(serie, temporada);
            break;
        case 3:
            break;
        case 4:
            listarTemporada(raizT);
            break;
 
        
        default:
            break;
        }

    }while(opc != 0);
    return 0;
}