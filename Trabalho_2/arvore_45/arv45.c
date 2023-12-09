#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv45.h"


typedef struct endereco{
    char status;
    int endeInicio, endeFim
}Enderecos;

typedef struct bloco45
{
    //         S    INIC  FIM    -   
    Enderecos end1, end2, end3, end4; // passa a ser uma arvore B de ordem 3, ja que não tem a info 4
    Bloco45 *esq, *esqCentro, *centro, *dirCentro, *dir; 
    int quantInfo;
}Bloco45;

Enderecos *criaEnderecos(char status, int inicio, int fim){
    Enderecos *novoEndereco;
    novoEndereco = (Enderecos*)malloc(sizeof(Enderecos));

    novoEndereco->status = status;
    novoEndereco->endeInicio = inicio;
    novoEndereco->endeFim = fim;

    return novoEndereco;
}



Bloco45 *criaBloco( Enderecos end, Bloco45 *esq, Bloco45 *esqCentro, Bloco45  *centro, Bloco45 *centroDir, Bloco45 *dir){
    Bloco45 *novoBloco;
    novoBloco = (Bloco45*)malloc(sizeof(Bloco45));

    novoBloco->end1 = end;
    novoBloco->quantInfo = 1;
    novoBloco->esq = esq;
    novoBloco->esqCentro = esqCentro;
    novoBloco->centro = centro;
    novoBloco->dirCentro = centroDir;
    novoBloco->dir = dir;

    return novoBloco;
}


int eFolha(Bloco45 *raiz){
    int efolha = 0; // não é folha
    if(raiz->esq == NULL && raiz->dir == NULL && raiz->esqCentro == NULL && raiz->centro == NULL)
        efolha = 1;
    return (eFolha);
}




void adiconaBloco(Bloco45 **raiz, Enderecos info, Bloco45 *maiorNo){
        if((*raiz)->quantInfo == 1){
            if( info.endeInicio < (*raiz)->end1.endeFim){
                (*raiz)->end2 = (*raiz)->end1;
                (*raiz)->centro = (*raiz)->esqCentro;
            }else if(info.endeInicio >  (*raiz)->end1.endeFim){
                (*raiz)->end2 = info;
                (*raiz)->centro = maiorNo;
            }
            (*raiz)->quantInfo = 2;
        }else if((*raiz)->quantInfo == 2){
            if(info.endeInicio > (*raiz)->end2.endeFim){
                (*raiz)->end3 = info;
                (*raiz)->dirCentro = maiorNo;
            }else if(info.endeFim < (*raiz)->end2.endeInicio){
               
            }

        }
    
}

