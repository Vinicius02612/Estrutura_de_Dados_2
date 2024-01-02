#include <stdio.h>
#include <stdlib.h>

typedef struct arvore45 Arv45;
struct arvore45 {
    int info1, info2, info3, info4, NInfos;
    Arv45 *esq, *centroesq, *centro, *centrodir, *dir;
};

int EhFolha(Arv45 *no);
Arv45* InsereArv45(Arv45 **raiz, int info, Arv45 *pai, int *sobe);
Arv45* CriaNo(int info, Arv45* esq, Arv45* centroesq, Arv45* centro, Arv45* centrodir, Arv45* dir);
Arv45* quebraNo(Arv45 **no, int info, int *sobe, Arv45* filho);
void adicionaNo(Arv45** node, int info, Arv45* filho);
void ImprimirArvore(Arv45* Raiz, int nivel);
void MaiorInfoRemoveEsq(Arv45 **raiz, Arv45** PaiMaior, Arv45** MaiorInfoRemove, int LocalInfo, int* ValorRemover);
void remover45(Arv45 **pai, Arv45 **raiz, int valor);

int main() {
    Arv45* RaizArv; RaizArv = NULL;

    int cont = 0;
    // Inserir valores na árvore
    int valores[] = {100, 200, 250, 300, 500, 600, 700, 750, 800, 850, 900, 890,
    950, 1000};
    int numValores = sizeof(valores) / sizeof(valores[0]);
    int i;
	int sobe;
    for (i = 0; i < 100; i++) {
        InsereArv45(&RaizArv, i, NULL, &sobe);
    }

    ImprimirArvore(RaizArv, 0);

    return 0;
}

int EhFolha(Arv45 *no) {
    int EhFolha; EhFolha = 0;
    if (no->esq == NULL && no->centroesq == NULL && no->centro == NULL) {
        EhFolha = 1;
    }

    return (EhFolha);
}

Arv45* InsereArv45(Arv45 **raiz, int info, Arv45 *pai, int *sobe) {
    Arv45 *MaiorNo; MaiorNo = NULL;

    if (*raiz == NULL) {
        *raiz = CriaNo(info, NULL, NULL, NULL, NULL, NULL);
    }
    else {
        if(EhFolha(*raiz) == 1) {
            if((*raiz)->NInfos == 1 || (*raiz)->NInfos == 2 || (*raiz)->NInfos == 3) {
                adicionaNo(raiz, info, NULL);
            }
            else {
                MaiorNo = quebraNo(raiz, info, sobe, NULL);
                if (pai == NULL) {
                    *raiz = CriaNo(*sobe, *raiz, MaiorNo, NULL, NULL, NULL);
                    MaiorNo = NULL;
                }
            }
        }
        else {
            if (info < (*raiz)->info1) {
                MaiorNo = InsereArv45(&((*raiz)->esq), info, *raiz, sobe);
            } else if ((*raiz)->NInfos == 1 || info < (*raiz)->info2) {
                MaiorNo = InsereArv45(&((*raiz)->centroesq), info, *raiz, sobe);
            } else if ((*raiz)->NInfos == 2 || info < (*raiz)->info3) {
                MaiorNo = InsereArv45(&((*raiz)->centro), info, *raiz, sobe);    
            } else if ((*raiz)->NInfos == 3 || info < (*raiz)->info4) {
                MaiorNo = InsereArv45(&((*raiz)->centrodir), info, *raiz, sobe);   
            } else {
                MaiorNo = InsereArv45(&((*raiz)->dir), info, *raiz, sobe);
            }

            if (MaiorNo != NULL) {
                if ((*raiz)->NInfos == 1 || (*raiz)->NInfos == 2 || (*raiz)->NInfos == 3) {
                    adicionaNo(raiz, *sobe, MaiorNo);
                    MaiorNo = NULL;
                }
                else {
                    MaiorNo = quebraNo(raiz, *sobe, sobe, MaiorNo);

                    if (pai == NULL) {
                        *raiz = CriaNo(*sobe, *raiz, MaiorNo, NULL, NULL, NULL);
                        MaiorNo = NULL;
                    }          
                }
            }
        }
    }
    return (MaiorNo);
}

Arv45* quebraNo(Arv45 **no, int info, int *sobe, Arv45* filho) {
    Arv45* MaiorNO;

    if (info > (*no)->info4) {
        *sobe = (*no)->info3;
        MaiorNO = CriaNo(info, (*no)->centrodir, filho, NULL, NULL, NULL);
        adicionaNo(&MaiorNO, (*no)->info4, (*no)->dir);
    }
    else if (info > (*no)->info3 && info < (*no)->info4) {
        *sobe = (*no)->info3;
        MaiorNO = CriaNo((*no)->info4, (*no)->centrodir, (*no)->dir, NULL, NULL, NULL);
        adicionaNo(&MaiorNO, info, filho);
    }
    else if (info > (*no)->info2 && info < (*no)->info3) {
        *sobe = info;
        MaiorNO = CriaNo((*no)->info4, filho, (*no)->dir, NULL, NULL, NULL);
        adicionaNo(&MaiorNO, (*no)->info3, (*no)->centrodir);
    }
    else if (info > (*no)->info1 && info < (*no)->info2) {
        *sobe = (*no)->info2;
        (*no)->info2 = info;
        MaiorNO = CriaNo((*no)->info4, (*no)->centro, (*no)->dir, NULL, NULL, NULL);
        adicionaNo(&MaiorNO, (*no)->info3, (*no)->centrodir);
        (*no)->centro = filho;
    }
    else {
        *sobe = (*no)->info2;
        (*no)->info2 = (*no)->info1;
        MaiorNO = CriaNo((*no)->info4, (*no)->centro, (*no)->dir, NULL, NULL, NULL);
        adicionaNo(&MaiorNO, (*no)->info3, (*no)->centrodir);
        (*no)->centro = (*no)->centroesq;
        (*no)->info1 = info;
        (*no)->centroesq = filho;
    }


    (*no)->centrodir = NULL;
    (*no)->dir = NULL;
    (*no)->NInfos = 2;
    return (MaiorNO);
}

Arv45* CriaNo(int info, Arv45* esq, Arv45* centroesq, Arv45* centro, Arv45* centrodir, Arv45* dir) {
    Arv45* NovoNo = (Arv45*)malloc(sizeof(Arv45));
    
    NovoNo->info1 = info;
    NovoNo->NInfos = 1;
    NovoNo->esq = esq;
    NovoNo->centroesq = centroesq;
    NovoNo->centro = centro;
    NovoNo->centrodir = centrodir;
    NovoNo->dir = dir;

    return NovoNo;
}

void adicionaNo(Arv45** node, int info, Arv45* filho) {
    if ((*node)->NInfos == 1) {
        if (info < (*node)->info1) {
            (*node)->info2 = (*node)->info1;
            (*node)->centro = (*node)->centroesq;
            (*node)->centroesq = filho;
            (*node)->info1 = info;
        }
        else {
            (*node)->info2 = info;
            (*node)->centro = filho;
        }
        (*node)->NInfos = 2;
    }
    else if ((*node)->NInfos == 2) {
        if (info > (*node)->info2) {
            (*node)->info3 = info;
            (*node)->centrodir = filho;
        }
        else if (info < (*node)->info1) {
            (*node)->info3 = (*node)->info2;
            (*node)->centrodir = (*node)->centro;
            (*node)->info2 = (*node)->info1;
            (*node)->centro = (*node)->centroesq;
            (*node)->info1 = info;
            (*node)->centroesq = filho;
        }
        else {
            (*node)->info3 = (*node)->info2;
            (*node)->centrodir = (*node)->centro;
            (*node)->info2 = info;
            (*node)->centro = filho;
        }
        (*node)->NInfos = 3;
    }
    else if ((*node)->NInfos == 3) {
        if (info > (*node)->info3) {
            (*node)->info4 = info;
            (*node)->dir = filho;
        }
        else if (info > (*node)->info2) {
            (*node)->info4 = (*node)->info3;
            (*node)->dir = (*node)->centrodir;
            (*node)->info3 = info;
            (*node)->centrodir = filho;
        }
        else if (info > (*node)->info1) {
            (*node)->info4 = (*node)->info3;
            (*node)->dir = (*node)->centrodir;
            (*node)->info3 = (*node)->info2;
            (*node)->centrodir = (*node)->centro;
            (*node)->info2 = info;
            (*node)->centro = filho;
        }
        else {
            (*node)->info4 = (*node)->info3;
            (*node)->dir = (*node)->centrodir;
            (*node)->info3 = (*node)->info2;
            (*node)->centrodir = (*node)->centro;
            (*node)->info2 = (*node)->info1;
            (*node)->centro = (*node)->centroesq;
            (*node)->info1 = info;
            (*node)->centroesq = filho;
        }
        (*node)->NInfos = 4;
    }
}

void ImprimirArvore(Arv45* Raiz, int nivel) {
    if (Raiz != NULL) {
        // Imprimir os valores do nível atual
        for (int i = 0; i < nivel; i++) {
            printf("\t");
        }

        printf("Nivel %d: ", nivel);
        
        // Imprimir os valores de acordo com o número de informações presentes no nó
        printf("%d ", Raiz->info1);
        if (Raiz->NInfos == 2) {
            printf("%d ", Raiz->info2);
        }
        if (Raiz->NInfos == 3) {
            printf("%d ", Raiz->info2);
            printf("%d ", Raiz->info3);
        }
        if (Raiz->NInfos == 4) {
            printf("%d ", Raiz->info2);
            printf("%d ", Raiz->info3);
            printf("%d ", Raiz->info4);
        }

        printf("NInfos %d\n", Raiz->NInfos);

        // Recursivamente imprimir os filhos
        ImprimirArvore(Raiz->esq, nivel + 1);
        ImprimirArvore(Raiz->centroesq, nivel + 1);
        ImprimirArvore(Raiz->centro, nivel + 1);
        ImprimirArvore(Raiz->centrodir, nivel + 1);
        ImprimirArvore(Raiz->dir, nivel + 1);
    }
}

void MaiorInfoRemoveEsq(Arv45 **raiz, Arv45** PaiMaior, Arv45** MaiorInfoRemove, int LocalInfo, int* ValorRemover) {
    if (MaiorInfoRemove != NULL) {
        if ((*MaiorInfoRemove)->esq == NULL) {
            int aux = 0;
            if (LocalInfo == 1) {
                aux = (*raiz)->info1;

                if ((*MaiorInfoRemove)->NInfos == 1) {
                    (*raiz)->info1 = (*MaiorInfoRemove)->info1;
                    (*MaiorInfoRemove)->info1 = aux;
                }
                else if ((*MaiorInfoRemove)->NInfos == 2) {
                    (*raiz)->info1 = (*MaiorInfoRemove)->info2;
                    (*MaiorInfoRemove)->info2 = aux;
                }
                else if ((*MaiorInfoRemove)->NInfos == 3) {
                    (*raiz)->info1 = (*MaiorInfoRemove)->info3;
                    (*MaiorInfoRemove)->info3 = aux;    
                }
                else {
                    (*raiz)->info1 = (*MaiorInfoRemove)->info4;
                    (*MaiorInfoRemove)->info4 = aux;    
                }

            }
            
            else if (LocalInfo == 2) {
                aux = (*raiz)->info2;

                if ((*MaiorInfoRemove)->NInfos == 1) {
                    (*raiz)->info2 = (*MaiorInfoRemove)->info1;
                    (*MaiorInfoRemove)->info1 = aux;
                }
                else if ((*MaiorInfoRemove)->NInfos == 2) {
                    (*raiz)->info2 = (*MaiorInfoRemove)->info2;
                    (*MaiorInfoRemove)->info2 = aux;
                }
                else if ((*MaiorInfoRemove)->NInfos == 3) {
                    (*raiz)->info2 = (*MaiorInfoRemove)->info3;
                    (*MaiorInfoRemove)->info3 = aux;    
                }
                else {
                    (*raiz)->info2 = (*MaiorInfoRemove)->info4;
                    (*MaiorInfoRemove)->info4 = aux;    
                }

            }
            else if (LocalInfo == 3) {
                aux = (*raiz)->info3;

                if ((*MaiorInfoRemove)->NInfos == 1) {
                    (*raiz)->info3 = (*MaiorInfoRemove)->info1;
                    (*MaiorInfoRemove)->info1 = aux;
                }
                else if ((*MaiorInfoRemove)->NInfos == 2) {
                    (*raiz)->info3 = (*MaiorInfoRemove)->info2;
                    (*MaiorInfoRemove)->info2 = aux;
                }
                else if ((*MaiorInfoRemove)->NInfos == 3) {
                    (*raiz)->info3 = (*MaiorInfoRemove)->info3;
                    (*MaiorInfoRemove)->info3 = aux;    
                }
                else {
                    (*raiz)->info3 = (*MaiorInfoRemove)->info4;
                    (*MaiorInfoRemove)->info4 = aux;    
                }
            }
            else if (LocalInfo == 4) {
                aux = (*raiz)->info4;

                if ((*MaiorInfoRemove)->NInfos == 1) {
                    (*raiz)->info4 = (*MaiorInfoRemove)->info1;
                    (*MaiorInfoRemove)->info1 = aux;
                }
                else if ((*MaiorInfoRemove)->NInfos == 2) {
                    (*raiz)->info4 = (*MaiorInfoRemove)->info2;
                    (*MaiorInfoRemove)->info2 = aux;
                }
                else if ((*MaiorInfoRemove)->NInfos == 3) {
                    (*raiz)->info4 = (*MaiorInfoRemove)->info3;
                    (*MaiorInfoRemove)->info3 = aux;    
                }
                else {
                    (*raiz)->info4 = (*MaiorInfoRemove)->info4;
                    (*MaiorInfoRemove)->info4 = aux;    
                }
            }

            *ValorRemover = aux;
        }
        else {
            if ((*MaiorInfoRemove)->NInfos == 1) {
                MaiorInfoRemoveEsq(raiz, MaiorInfoRemove, &((*MaiorInfoRemove)->centroesq), LocalInfo, ValorRemover);
            }
            else if ((*MaiorInfoRemove)->NInfos == 2) {
                MaiorInfoRemoveEsq(raiz, MaiorInfoRemove, &((*MaiorInfoRemove)->centro), LocalInfo, ValorRemover);
            }
            else if ((*MaiorInfoRemove)->NInfos == 3) {
                MaiorInfoRemoveEsq(raiz, MaiorInfoRemove, &((*MaiorInfoRemove)->centrodir), LocalInfo, ValorRemover);
            }
            else if ((*MaiorInfoRemove)->NInfos == 4) {
                MaiorInfoRemoveEsq(raiz, MaiorInfoRemove, &((*MaiorInfoRemove)->dir), LocalInfo, ValorRemover);
            }
        } 
    }
}

void remover45(Arv45 **pai, Arv45 **raiz, int valor)
{

    if (*raiz != NULL) {
        int ValorRemover = 0;
        if (valor == (*raiz)->info1) {
            // Valor 1
            if (EhFolha(*raiz) == 0) {
                if ((*raiz)->NInfos == 1) {
                    (*raiz)->NInfos = 0;
                }
                else if ((*raiz)->NInfos == 2) {
                    (*raiz)->info1 = (*raiz)->info2;
                    (*raiz)->NInfos = 1;
                }
                else if ((*raiz)->NInfos == 3) {
                    (*raiz)->info1 = (*raiz)->info2;
                    (*raiz)->info2 = (*raiz)->info3;
                    (*raiz)->NInfos == 2;
                }
                else if ((*raiz)->NInfos == 4) {
                    (*raiz)->info1 = (*raiz)->info2;
                    (*raiz)->info2 = (*raiz)->info3;
                    (*raiz)->info3 = (*raiz)->info4;
                    (*raiz)->NInfos = 3;
                }
                
            }
            else {
                Arv45 **MaiorInfoRemove = &((*raiz)->esq);
                Arv45 **PaiMaior = raiz;
                MaiorInfoRemoveEsq(raiz, PaiMaior, MaiorInfoRemove, 1, &ValorRemover);
                remover23(PaiMaior, MaiorInfoRemove, ValorRemover);
            }
        }
        
        else if (valor < (*raiz)->info1) {
            // Valor para a esquerda
            remover45(raiz, &((*raiz)->esq), valor);  
        }
        
        else if ((*raiz)->NInfos == 1 || valor < (*raiz)->info2) {
            // Valor vai para o centro esquerda
            remover45(raiz, &((*raiz)->centroesq), valor);    
        }
        
        else if ((*raiz)->NInfos >= 2 && valor == (*raiz)->info2) {
            // Valor 2
            if (EhFolha(*raiz) == 0) {
                if ((*raiz)->NInfos == 2) {
                    (*raiz)->NInfos = 1;
                }
                else if ((*raiz)->NInfos == 3) {
                    (*raiz)->info2 = (*raiz)->info3;
                    (*raiz)->NInfos == 2;
                }
                else if ((*raiz)->NInfos == 4) {
                    (*raiz)->info2 = (*raiz)->info3;
                    (*raiz)->info3 = (*raiz)->info4;
                    (*raiz)->NInfos = 3;
                }
                
            }
            else {
                Arv45 **MaiorInfoRemove = &((*raiz)->centroesq);
                Arv45 **PaiMaior = raiz;
                MaiorInfoRemoveEsq(raiz, PaiMaior, MaiorInfoRemove, 2, &ValorRemover);
                remover23(PaiMaior, MaiorInfoRemove, ValorRemover);
            }
        }
        
        else if ((*raiz)->NInfos == 2 || valor < (*raiz)->info3) {
            // Valor vai para o centro
            remover45(raiz, &((*raiz)->centro), valor);   
        }
        
        else if ((*raiz)->NInfos >= 3 && valor == (*raiz)->info3) {
            // Valor 3
            if (EhFolha(*raiz) == 0) {
                if ((*raiz)->NInfos == 3) {
                    (*raiz)->NInfos == 2;
                }
                else if ((*raiz)->NInfos == 4) {
                    (*raiz)->info3 = (*raiz)->info4;
                    (*raiz)->NInfos = 3;
                } 
            }
            else {
                Arv45 **MaiorInfoRemove = &((*raiz)->esq);
                Arv45 **PaiMaior = raiz;
                MaiorInfoRemoveEsq(raiz, PaiMaior, MaiorInfoRemove, 3, &ValorRemover);
                remover23(PaiMaior, MaiorInfoRemove, ValorRemover);
            }   
        }
        
        else if ((*raiz)->NInfos == 3 || valor < (*raiz)->info4) {
            // Valor vai para o centro direita
            remover45(raiz, &((*raiz)->centrodir), valor);    
        }
        
        else if ((*raiz)->NInfos == 4 && valor == (*raiz)->info4){
            // Valor 4
            if (EhFolha(*raiz) == 0) {
                (*raiz)->NInfos = 3;
            }
            else {
                Arv45 **MaiorInfoRemove = &((*raiz)->esq);
                Arv45 **PaiMaior = raiz;
                MaiorInfoRemoveEsq(raiz, PaiMaior, MaiorInfoRemove, 4, &ValorRemover);
                remover23(PaiMaior, MaiorInfoRemove, ValorRemover);
            } 
        }
        
        else {
            // Valor vai para a direita
            remover45(raiz, &((*raiz)->dir), valor);    
        }    
    }

    Redistribui(raiz, pai);
}

void Redistribui(Arv45 **raiz, Arv45 **pai) {
    if (*raiz != NULL)
        if ((*raiz)->NInfos == 0) {
            if (pai != NULL) {
                if (*raiz == ((*pai)->dir)) {
                    // Agora verifica o número de informações do pai, e do irmão, e rotaciona se precisar, ou mescla, fazer isso para todos os casos
                }
                else if (*raiz == (*pai)->centrodir) {

                }
                else if (*raiz == (*pai)->centro) {

                }   
                else if (*raiz == (*pai)->centroesq) {

                }
                else if (*raiz == (*pai)->esq) {

                } 
                    
            }
            else if (pai == NULL) {
                (*raiz) = (*raiz)->centro;
            }   
        }
}