#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct info {
    int inicio, fim;
    char status;
}Info;

typedef struct arv45 {
    struct info *Info1, *Info2, *Info3, *Info4;
    int NInfos;
    struct arv45 *esq, *cen1, *cen2, *cen3, *dir;
}Arv45;


Info *criaInfo(int inicio, int fim, char status) {
    Info *info = (Info*)malloc(sizeof(Info));
    info->inicio = inicio;
    info->fim = fim;
    info->status = status;
    return info;
}

Arv45 *criaNo(Info *info, Arv45 *NoEsq, Arv45 *noCentroEsq) {
    Arv45 *no = (Arv45*)malloc(sizeof(Arv45));
    no->Info1 = info;
    no->NInfos = 1;
    no->esq = NoEsq;
    no->cen1 = noCentroEsq;
    no->cen2 = NULL;
    no->cen3 = NULL;
    no->dir = NULL;
    return no;
}

int ehFolha(Arv45 *no) {
    return (no->esq == NULL);
}

void adicionaNo(Arv45 **No, Info *info, Arv45 *filho) {
    if ((*No)->NInfos == 1) {
        if (info->inicio > (*No)->Info1->inicio) {
            (*No)->Info2 = info;
            (*No)->cen2 = filho;
        } else {
            (*No)->Info2 = (*No)->Info1;
            (*No)->Info1 = info;
            (*No)->cen2 = (*No)->cen1;
            (*No)->cen1 = filho;
        }
        (*No)->NInfos = 2;
    } else if ((*No)->NInfos == 2) {
        if (info->inicio > (*No)->Info2->inicio) {
            (*No)->Info3 = info;
            (*No)->cen3 = filho;
        } else if (info->inicio > (*No)->Info1->inicio && info->inicio < (*No)->Info2->inicio) {
            (*No)->Info3 = (*No)->Info2;
            (*No)->Info2 = info;
            (*No)->cen3 = (*No)->cen2;
            (*No)->cen2 = filho;
        } else {
            (*No)->Info3 = (*No)->Info2;
            (*No)->Info2 = (*No)->Info1;
            (*No)->Info1 = info;
            (*No)->cen3 = (*No)->cen2;
            (*No)->cen2 = (*No)->cen1;
            (*No)->cen1 = filho;
        }
        (*No)->NInfos = 3;
    } else {
        if (info->inicio > (*No)->Info3->inicio) {
            (*No)->Info4 = info;
            (*No)->dir = filho;
        } else if (info->inicio > (*No)->Info2->inicio && info->inicio < (*No)->Info3->inicio) {
            (*No)->Info4 = (*No)->Info3;
            (*No)->Info3 = info;
            (*No)->dir = (*No)->cen3;
            (*No)->cen3 = filho;
        } else if (info->inicio > (*No)->Info1->inicio && info->inicio < (*No)->Info2->inicio) {
            (*No)->Info4 = (*No)->Info3;
            (*No)->Info3 = (*No)->Info2;
            (*No)->Info2 = info;
            (*No)->dir = (*No)->cen3;
            (*No)->cen3 = (*No)->cen2;
            (*No)->cen2 = filho;
        } else {
            (*No)->Info4 = (*No)->Info3;
            (*No)->Info3 = (*No)->Info2;
            (*No)->Info2 = (*No)->Info1;
            (*No)->Info1 = info;
            (*No)->dir = (*No)->cen3;
            (*No)->cen3 = (*No)->cen2;
            (*No)->cen2 = (*No)->cen1;
            (*No)->cen1 = filho;
        }
        (*No)->NInfos = 4;
    }
}

Arv45 *quebraNo(Arv45 **raiz, Info *info, Info **sobe, Arv45 *filho) {
    Arv45 *maiorNo;

    if (info->inicio > (*raiz)->Info4->inicio) {
        *sobe = (*raiz)->Info3;
        maiorNo = criaNo((*raiz)->Info4, (*raiz)->cen3, (*raiz)->dir);
        maiorNo->Info2 = info;
        maiorNo->cen2 = filho;
        maiorNo->NInfos = 2;
    } else if (info->inicio > (*raiz)->Info3->inicio) {
        *sobe = (*raiz)->Info3;
        maiorNo = criaNo(info, (*raiz)->cen3, filho);
        maiorNo->Info2 = (*raiz)->Info4;
        maiorNo->cen2 = (*raiz)->dir;
        maiorNo->NInfos = 2;
    } else if (info->inicio > (*raiz)->Info2->inicio) {
        *sobe = info;
        maiorNo = criaNo((*raiz)->Info3, (*raiz)->cen2, (*raiz)->cen3);
        maiorNo->Info2 = (*raiz)->Info4;
        maiorNo->cen2 = (*raiz)->dir;
        maiorNo->NInfos = 2;
    } else if (info->inicio > (*raiz)->Info1->inicio) {
        *sobe = (*raiz)->Info2;
        maiorNo = criaNo((*raiz)->Info3, (*raiz)->cen2, (*raiz)->cen3);
        maiorNo->Info2 = (*raiz)->Info4;
        maiorNo->cen2 = (*raiz)->dir;
        maiorNo->NInfos = 2;
        (*raiz)->Info2 = info;
        (*raiz)->cen2 = filho;
    } else {
        *sobe = (*raiz)->Info2;
        maiorNo = criaNo((*raiz)->Info3, (*raiz)->cen2, (*raiz)->cen3);
        maiorNo->Info2 = (*raiz)->Info4;
        maiorNo->cen2 = (*raiz)->dir;
        maiorNo->NInfos = 2;
        (*raiz)->Info2 = (*raiz)->Info1;
        (*raiz)->cen2 = (*raiz)->cen1;
        (*raiz)->Info1 = info;
        (*raiz)->cen1 = filho;
    }

    (*raiz)->NInfos = 2;
    (*raiz)->cen3 = NULL;
    (*raiz)->dir = NULL;

    (*raiz)->Info3 = NULL;
    (*raiz)->Info4 = NULL;

    return maiorNo;
}

Arv45 *inserir45(Arv45 **raiz, Arv45 *pai, Info **sobe, int inicio, int fim, char status, int *flag) {
    Arv45 *maiorNO;
    maiorNO = NULL;

    if (*raiz == NULL) {
        *raiz = criaNo(criaInfo(inicio, fim, status), NULL, NULL);
        *flag = 1; // informa que foi inserido
    } else {
        if (ehFolha(*raiz)) {
            *flag = 1; // informa que foi inserido
            if ((*raiz)->NInfos < 2) {
                adicionaNo(raiz, criaInfo(inicio, fim, status), NULL);
                maiorNO = NULL;
            } else {
                maiorNO = quebraNo(raiz, criaInfo(inicio, fim, status), sobe, NULL);

                if (pai == NULL) {
                    *raiz = criaNo(*sobe, *raiz, maiorNO);
                    maiorNO = NULL;
                }
            }
        } else {
            if (inicio < (*raiz)->Info1->inicio)
                maiorNO = inserir45(&((*raiz)->esq), *raiz, sobe, inicio, fim, status, flag);
            else if ((*raiz)->NInfos == 1 || ((*raiz)->NInfos <= 2 && inicio < (*raiz)->Info2->inicio))
                maiorNO = inserir45(&((*raiz)->cen1), *raiz, sobe, inicio, fim, status, flag);
            else if (((*raiz)->NInfos == 2) || ((*raiz)->NInfos <= 2 && inicio < (*raiz)->Info3->inicio))
                maiorNO = inserir45(&((*raiz)->cen2), *raiz, sobe, inicio, fim, status, flag);
            else
                maiorNO = inserir45(&((*raiz)->dir), *raiz, sobe, inicio, fim, status, flag);

            if (maiorNO) {
                if ((*raiz)->NInfos < 2) {
                    adicionaNo(raiz, *sobe, maiorNO);
                    maiorNO = NULL;
                } else {
                    maiorNO = quebraNo(raiz, *sobe, sobe, maiorNO);

                    if (pai == NULL) {
                        *raiz = criaNo(*sobe, *raiz, maiorNO);
                        maiorNO = NULL;
                    }
                }
            }
        }
    }
    return maiorNO;
}


// int main() {
//     Arv45 *root = NULL;
//     Info *sobe = NULL;
//     int flag = 0;

//     // Inserting elements into the 4-5 tree
//     inserir45(&root, NULL, &sobe, 10, 20, 'A', &flag);
//     inserir45(&root, NULL, &sobe, 30, 40, 'B', &flag);
//     inserir45(&root, NULL, &sobe, 15, 25, 'C', &flag);
//     inserir45(&root, NULL, &sobe, 5, 8, 'D', &flag);
//     inserir45(&root, NULL, &sobe, 35, 45, 'E', &flag);
//     inserir45(&root, NULL, &sobe, 50, 60, 'F', &flag);
//     inserir45(&root, NULL, &sobe, 55, 70, 'G', &flag);

//     // Printing the 4-5 tree
//     printf("4-5 Tree: ");
//     //printTree(root);
//     printf("\n");

//     // Freeing the memory allocated for the 4-5 tree
//     //freeTree(root);

//     return 0;
// }