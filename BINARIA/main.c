#include <stdio.h>
#include <stdlib.h>
#include "arvBin.h"



// novo arquivo
int main(){

    int opc,id, codigo, numTemporadas, codigoSerie;
    int numTemp,quantEpisodio;
    char titulo[50], ano[50], tituloTemoporada[50], nomeDoArtista[50],  nomeDoPersongem[50],  descricao[50], quant = 30;
    ArvoreSerie *raizS = criarArvoreSerie();
    ArvoreTemporada  *raizT = criaAvoreTemporada();
    Participantes *listaParticipante =criaListaParticipante();
    
    ArvoreSerie *s;
    ArvoreSerie *Dado =  NULL;
    ArvoreTemporada *DadoTemp=  NULL;


    do{
        
        printf("1  Inserir Serie\n"
                "2 Imprimir em ordem pelo codigo da serie: o titulo, o numero de temporadas.\n"
                "3 Imprimir os dados de todas as temporadas de uma serie, cujo o usuario informe o codigo da serie.\n"
                "4 Imprimir  todos  os  personagens  de  uma  determinada  temporada  de  uma  dada  serie,  cujo  o  usuario informe o codigo da serie e o numero da temporada.\n"
                "5 Imprimir  o  nome  de  todos  os  artistas  que  interpretaram  um  determinado  personagem  em  todas  as temporadas de uma dada serie, cujo o usuario informe o codigo da serie\n"
            );
        scanf("%d", &opc);
        switch (opc)
        {
            case 1:
                Dado = lerDadosSerie();
                inserirSeries(&raizS, Dado);
                break;
            case 2:
                imprimeArvoreSeries(raizS);
                break;
            case 3:
                printf("Informe o codigo da serie: \n");
                scanf("%d", &codigoSerie);
                imprimeTemporadaDeUmaSerie(raizS, codigoSerie);
                break;
            case 4:
                printf("Informe o codigo da serie: \n");
                scanf("%d", &codigoSerie);
                printf("Numero da temporada:\n");
                scanf("%d", &numTemp);
                imprimirPersonagensDeUmaTemporada(raizS, codigoSerie, numTemp);
                break;
            case 5:
                printf("Digite o nome do personagem: \n");
                scanf("%s", nomeDoPersongem);
                imprimirNomeDeUmArtista(raizS, nomeDoPersongem);
                break;
            case 6:
                realizaTesteDeInsercaoDaSerie(raizS,quant);
                break;
            case 7: 
                realizaTesteDeBusca(&raizT,quant);
                break;
            case 8:

                break;
            default:
                break;
        }  
    }while(opc != 0);
   

    return 0;
}

/* 
// Função auxiliar para inserir uma temporada na árvore de uma série, mantendo a ordem pelo número da temporada
void inserirTemporadaAux(Temporada *raiz, Temporada *t, Temporada **pai) {
    if (raiz == NULL) { // Se a árvore estiver vazia ou chegar a uma folha
        *pai = t; // Fazer o pai apontar para a temporada
    } else if (t->numero < raiz->numero) { // Se o número da temporada for menor que o da raiz
        inserirTemporadaAux(raiz->esq, t, &(raiz->esq)); // Inserir na subárvore esquerda
    } else if (t->numero > raiz->numero) { // Se o número da temporada for maior que o da raiz
        inserirTemporadaAux(raiz->dir, t, &(raiz->dir)); // Inserir na subárvore direita
    } else { // Se o número da temporada for igual ao da raiz
        printf("Temporada ja existe na serie.\n");
        //return;
    }
}

// Função para inserir uma temporada na árvore de uma série, mantendo a ordem pelo número da temporada
void inserirTemporada(Serie *s, Temporada *t) {
    if (s == NULL) { // Verificar se a série é válida
        printf("Serie invalida.\n");
        //return;
    }
    if (t == NULL) { // Verificar se a temporada é válida
        printf("Temporada invalida.\n");
        //return;
    }
    inserirTemporadaAux(s->temporadas, t, &(s->temporadas)); // Inserir a temporada na árvore de temporadas da série
}












 */