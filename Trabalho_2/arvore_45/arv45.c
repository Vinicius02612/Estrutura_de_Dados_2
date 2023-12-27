#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv45.h"

struct info {
    int inicio, fim;
    char status;
};

struct arv45 {
    struct info *Info1, *Info2, *Info3, *Info4;
    int NInfos;
    struct arv45 *esq, *cen1, *cen2, *cen3, *dir;
};

struct arv45 *criaNo(struct info *Info1, struct info *Info2, struct info *Info3, struct info *Info4, struct arv45 *FEsq, struct arv45 *FCen1, struct arv45 *FCen2, struct arv45 *FCen3, struct arv45 *FDir) {
    struct arv45 *No;
    No = (struct arv45 *)malloc(sizeof(struct arv45));

    No->Info1 = Info1;
    No->Info2 = Info2;
    No->Info3 = Info3;
    No->Info4 = Info4;
    No->NInfos = 4;
    No->esq = FEsq;
    No->cen1 = FCen1;
    No->cen2 = FCen2;
    No->cen3 = FCen3;
    No->dir = FDir;

    return No;
}

int ehFolha(struct arv45 *Raiz){
  int folha = 0;
  if(Raiz->esq == NULL)
    folha = 1;
  return folha;  
}

struct arv45 *adicionaNo(struct arv45 *No, struct info *Info, struct arv45 *Filho1,struct arv45 *Filho2, struct arv45 *Filho3, struct arv45 *Filho4) {

    if (Info->inicio > No->Info1->fim) {
        No->Info4 = Info;
        No->dir = Filho4;
    } else if (Info->inicio > No->Info2->fim) {
        No->Info4 = No->Info3;
        No->dir = No->cen3;
        No->Info3 = No->Info2;
        No->cen3 = No->cen2;
        No->Info2 = Info;
        No->cen2 = Filho4;
    } else if (Info->inicio > No->Info3->fim) {
        No->Info4 = No->Info3;
        No->dir = No->cen3;
        No->Info3 = Info;
        No->cen3 = Filho4;
    } else {
        No->Info4 = No->Info3;
        No->dir = No->cen3;
        No->Info3 = No->Info2;
        No->cen3 = No->cen2;
        No->Info2 = No->Info1;
        No->cen2 = No->cen1;
        No->Info1 = Info;
        No->cen1 = Filho4;
    }

    No->NInfos = 4;

    return No;
}

void quebraNo(struct arv45 **No, struct info *Info, struct arv45 *FilhoMaior, struct info **Sobe, struct arv45 **Novo) {
    if (Info->fim < (*No)->Info1->inicio) {
        *Sobe = (*No)->Info1;
        *Novo = criaNo((*No)->Info1, (*No)->Info2, (*No)->Info3, (*No)->Info4, (*No)->esq, (*No)->cen1, (*No)->cen2, (*No)->cen3, (*No)->dir);
        (*No)->Info1 = Info;
        (*No)->cen1 = FilhoMaior;
        (*No)->Info2 = NULL;
        (*No)->Info3 = NULL;
        (*No)->Info4 = NULL;
        (*No)->cen2 = NULL;
        (*No)->cen3 = NULL;
        (*No)->dir = NULL;
        (*No)->NInfos = 1;
    } else if (Info->fim < (*No)->Info2->inicio) {
        *Sobe = Info;
        *Novo = criaNo((*No)->Info1, (*No)->Info2, (*No)->Info3, (*No)->Info4, (*No)->esq, FilhoMaior, (*No)->cen2, (*No)->cen3, (*No)->dir);
        (*No)->cen1 = FilhoMaior;
        (*No)->Info2 = NULL;
        (*No)->Info3 = NULL;
        (*No)->Info4 = NULL;
        (*No)->cen2 = NULL;
        (*No)->cen3 = NULL;
        (*No)->dir = NULL;
        (*No)->NInfos = 1;
    } else if (Info->fim < (*No)->Info3->inicio) {
        *Sobe = (*No)->Info2;
        *Novo = criaNo((*No)->Info1, (*No)->Info2, (*No)->Info3, (*No)->Info4, NULL, FilhoMaior, (*No)->cen3, NULL, (*No)->dir);
        (*No)->Info2 = Info;
        (*No)->Info3 = NULL;
        (*No)->Info4 = NULL;
        (*No)->cen2 = FilhoMaior;
        (*No)->cen3 = NULL;
        (*No)->dir = NULL;
        (*No)->NInfos = 2;
    } else {
        *Sobe = (*No)->Info2;
        *Novo = criaNo(Info, (*No)->Info1, (*No)->Info3, (*No)->Info4, (*No)->esq, FilhoMaior, (*No)->cen2, (*No)->cen3, (*No)->dir);
        (*No)->Info2 = (*No)->Info1;
        (*No)->Info3 = NULL;
        (*No)->Info4 = NULL;
        (*No)->cen2 = (*No)->cen1;
        (*No)->cen3 = NULL;
        (*No)->dir = NULL;
        (*No)->NInfos = 2;
    }
}
