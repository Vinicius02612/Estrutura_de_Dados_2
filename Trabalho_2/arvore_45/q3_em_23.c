#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define QTD_EXPERIMENTOS 30

typedef struct endeMem endeMem;
struct endeMem
{
    int inicio, fim;
    char estado;
};

typedef struct blocoMem blocoMem;
struct blocoMem
{
    int nInfo;
    endeMem info1, info2;
    blocoMem *esq, *cen, *dir;
};

void menu(blocoMem **raiz, int maximoBlocoMen);
endeMem *criaEnd(char estado, int inicio, int fim);
blocoMem *criaBloco(endeMem info1, blocoMem *esq, blocoMem *cen, blocoMem *dir);
void adicionaBloco(blocoMem **raiz, endeMem info, blocoMem *maiorNo);
int ehFolha(blocoMem *no);
int buscaBloco(blocoMem *raiz, int inicio, int fim);
blocoMem *quebraBloco(blocoMem **raiz, endeMem bloco, endeMem *sobe, blocoMem *maiorNo);
blocoMem *insere(blocoMem **no, endeMem bloco, endeMem *promove, blocoMem **pai);
void mostraEmOrdem(blocoMem *Raiz);
void inverteEstadoBloco(endeMem *info);
int remover23(blocoMem **Pai, blocoMem **Raiz, endeMem valor);
void menorInfoDir(blocoMem *Raiz, blocoMem **no, blocoMem **paiNo);
void maiorInfoEsq(blocoMem *Raiz, blocoMem **no, blocoMem **paiNo);
void alocarMemoria(blocoMem **raiz, blocoMem **pai, int qtdBlocosAloc, int maximoBlocoMen, int* alocou);
int removeInfo2ComDirFolha(blocoMem **Raiz, blocoMem **paiNo);
void liberarMemoria(blocoMem **raiz, blocoMem **pai, endeMem liberarEspaco, int maximoBlocoMen, int *liberou);
int blocoValido(int inicio, int fim, int qtdBlocosMaximo);
void preenchePosicoesMemoria(blocoMem **raiz, blocoMem **pai, int *qntBlocoMem);
void definicaoMemoria(int *qntBlocoMem,char *estadoBlocoInicial);
void imprimirNo(blocoMem *raiz);
endeMem maiorInfo(blocoMem *raiz);
endeMem menorInfo(blocoMem *raiz);
blocoMem* raiz_global = NULL;

int main()
{
    blocoMem *raiz,*pai;
    raiz = NULL;
    pai = NULL;
    int qntBlocoMem;
    preenchePosicoesMemoria(&raiz,&pai,&qntBlocoMem);
    raiz_global = raiz;
    menu(&raiz, qntBlocoMem);
    return 0;
}

void menu(blocoMem **raiz, int maximoBlocoMen)
{
    int opcao, alocou = 0, liberou = 0, qtdBlocos4Aloc, liberInicio, liberFim;
    int inicio, fim, encontrou = 0, i;
    double tempo_total = 0.0;
    blocoMem *pai;
    pai = NULL;
    endeMem *blocoParaLiberar;
    clock_t tempo_inicio,tempo_fim;
    do
    {
        printf("\nO que deseja fazer?\n  1 - Alocar blocos de memoria\n  2 - Liberar Blocos de memoria\n  3 - Visualizar memoria\n  4 - Buscar bloco\n  0 - Encerrar programa\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            tempo_total = 0.0;
            // alocar blocos de memória
            printf("Quantos blocos deseja alocar? ");
            scanf("%d", &qtdBlocos4Aloc);


            tempo_inicio = clock();
            alocarMemoria(raiz, &pai, qtdBlocos4Aloc, maximoBlocoMen, &alocou);
            tempo_fim = clock();
            tempo_total = (double)(tempo_fim - tempo_inicio) * 1000000; // transformar para microsegundos

            if (!alocou)
                printf("\nNao foi possivel alocar os blocos de memoria!\nMemoria insuficiente\n\n");
            else
                printf("\nBlocos de memoria alocados com sucesso!\n\nTempo de execucao: %lf microsegundos\n", tempo_total);
            alocou = 0;
            tempo_total = 0.0;
            break;
        case 2:
            // liberar blocos de memória
            printf("Onde deve iniciar a desalocar? ");
            scanf("%d",&liberInicio);
            printf("Onde deve parar de desalocar? ");
            scanf("%d",&liberFim);
            if(blocoValido(liberInicio,liberFim,maximoBlocoMen)){
                blocoParaLiberar = criaEnd('L',liberInicio,liberFim);
                tempo_total = 0.0;
                tempo_inicio = clock();
                liberarMemoria(raiz,&pai,*blocoParaLiberar,maximoBlocoMen,&liberou);
                tempo_fim = clock();
                tempo_total = (double)(tempo_fim - tempo_inicio) * 1000000; // transformar para microsegundos

                if(!liberou)
                    printf("Nao foi possivel desalocar os blocos de memoria informados!\n\n");
                else
                    printf("Blocos de memoria desalocados com sucesso!\n\nTempo de execucao: %lf microsegundos\n", tempo_total);
            }
            else
                printf("Valores para desalocar invalidos\n");
            liberou = 0;   
            tempo_total = 0.0;
            break;
        case 3:
            mostraEmOrdem(*raiz);
            break;
        case 4:
            // buscar um valor
            printf("\nBUSCAR BLOCO\n");
            printf("Inicio do bloco: ");
            scanf("%d", &inicio);
            printf("Fim do bloco: ");
            scanf("%d", &fim);

            tempo_total = 0.0;
            for (i = 0; i < QTD_EXPERIMENTOS; i++)
            {
                tempo_inicio = clock();
                encontrou = buscaBloco(*raiz, inicio, fim);
                tempo_fim = clock();
                tempo_total += (double)(tempo_fim - tempo_inicio);
            }
        
            tempo_total *= 1000000; // trasnforma para microsegundos
            tempo_total /= QTD_EXPERIMENTOS;
            if (encontrou)
            {
                printf("\nBloco encontrado!\n\ntempo medio para buscar: %lf microssegundos\n\n", tempo_total);
            } else {
                printf("\nBloco nao encontrado!\n\n");
            }

            tempo_total = 0.0;
            break;
        default:
            break;
        }
        raiz_global = *raiz;
   
    } while (opcao != 0);
}

void preenchePosicoesMemoria(blocoMem **raiz, blocoMem **pai, int *qntBlocoMem){
    endeMem *promove,*primeiroEnd;
    promove = (endeMem *)calloc(1, sizeof(endeMem));
    primeiroEnd = NULL;
    int inicioBlocoMem = 0, fimBlocoMem = 0;
    char estadoBlocoInicial;

    definicaoMemoria(qntBlocoMem, &estadoBlocoInicial);
    // Insere o primeiro bloco
    while (fimBlocoMem < *qntBlocoMem - 1)
    {
        // Lê o final de cada bloco e insere
        printf("Bloco iniciando na posicao %d ", inicioBlocoMem);
        printf("Informe a posicao do fim do bloco de memoria : ");
        scanf("%d", &fimBlocoMem); // Fim do bloco atual
        while (fimBlocoMem >= *qntBlocoMem)
        { // Permite apenas valores válidos de fim do bloco
            printf("Extouro de memoria, ultima posicao disponivel %dmb\n", *qntBlocoMem - 1);
            printf("Insira novamente a ultima posicao do bloco : ");
            scanf("%d", &fimBlocoMem);
        }
        primeiroEnd = criaEnd(estadoBlocoInicial, inicioBlocoMem, fimBlocoMem);
        insere(raiz, *primeiroEnd, promove, pai);
        if (estadoBlocoInicial == 'L')
            estadoBlocoInicial = 'O';
        else
            estadoBlocoInicial = 'L';
        
        inicioBlocoMem = fimBlocoMem + 1;
    }

}

void definicaoMemoria(int *qntBlocoMem,char *estadoBlocoInicial){
    printf("Quantidade de memoria disponivel em megabyte : ");
    scanf("%d", qntBlocoMem);
    printf("Qual o estado do primeiro bloco(L/O)? ");
    setbuf(stdin, NULL);
    scanf("%c", estadoBlocoInicial);
    *estadoBlocoInicial = toupper(*estadoBlocoInicial);
    while (*estadoBlocoInicial != 'L' && *estadoBlocoInicial != 'O')
    {
        setbuf(stdin, NULL);
        printf("Valor invalido, por favor informe L ou O : ");
        scanf("%c", estadoBlocoInicial);
        *estadoBlocoInicial = toupper(*estadoBlocoInicial);
    }
}

void alocarMemoria(blocoMem **raiz, blocoMem **pai, int qtdBlocosAloc, int maximoBlocoMen, int *alocou)
{
    int removeu = 0, novoInicio, novoFim;
    endeMem *aux, *aux2, *promove, maior, menor;
    blocoMem *no, *paiAux;
    aux = NULL, promove = NULL, paiAux = NULL;
    if (*raiz != NULL)
    {
        if (!*alocou)
        {
            alocarMemoria(&((*raiz)->esq), raiz, qtdBlocosAloc, maximoBlocoMen, alocou);    
        }

        if (!*alocou && (*raiz)->info1.estado == 'L')
        {   
            int qtdBlocoDisp = ((*raiz)->info1.fim - (*raiz)->info1.inicio) + 1;

            if (qtdBlocoDisp == qtdBlocosAloc) // quantidade de blocos exata que deseja alocar
            {
                // insercao no inicio
                if ((*raiz)->info1.inicio == 0)
                {
                    if (*pai != NULL)
                    {
                        (*pai)->info1.inicio = (*raiz)->info1.inicio;
                        // Remove o nó pois só havia 1 informação
                        removeu = remover23(pai, raiz, (*raiz)->info1);
                        *alocou = 1;
                    }
                    else if ((*raiz)->nInfo == 2)
                    { // Se tiver info2
                        (*raiz)->info2.inicio = (*raiz)->info1.inicio;
                        (*raiz)->info1 = (*raiz)->info2;
                        (*raiz)->info2.inicio = -1;
                        (*raiz)->info2.fim = -1;
                        (*raiz)->nInfo = 1;
                        // Altera a info2 e move info 2 pra info 1, libera Info2
                        *alocou = 1;
                    }
                    else
                    { // Não tem pai e não tem info 2
                        inverteEstadoBloco(&((*raiz)->info1));
                        *alocou = 1;
                    }
                } else if ((*raiz)->info1.fim == maximoBlocoMen - 1){
                    // insercao no fim
                    // Se tem 1 info, olha pro pai
                    if ((*pai)->nInfo == 2){
                        (*pai)->info2.fim = (*raiz)->info1.fim;
                        removeu = remover23(pai, raiz, (*raiz)->info1);
                    }
                    else {
                        (*pai)->info1.fim = (*raiz)->info1.fim;
                        removeu = remover23(pai, raiz, (*raiz)->info1);
                    }
                    *alocou = 1;
                } else {
                    // insercao no meio
                
                    if (ehFolha(*raiz)){
                        // eh uma folha no meio da memoria, tem pai
                        // verifica de onde estou vindo do pai
                        if ((*raiz)->nInfo == 2)
                        {
                            if ((*pai)->esq == *raiz)
                            {
                                // no eh filho da esquerda
                                (*raiz)->info1.fim = (*raiz)->info2.fim;
                                removeu = remover23(pai, raiz, (*raiz)->info2);
                            } else if ((*pai)->cen == *raiz){
                                // no eh filho do centro
                                (*pai)->info1.fim = (*raiz)->info2.fim;
                                maior = (*raiz)->info2;
                                removeu = remover23(pai, raiz, (*raiz)->info1);
                                removeu = remover23(&paiAux, &raiz_global, maior);
                            } else {
                                // no eh filho da direita
                                (*raiz)->info1.fim = (*raiz)->info2.fim;
                                removeu = remover23(pai, raiz, (*raiz)->info2);
                            }
                        } else {
                            if ((*pai)->esq == *raiz)
                            {
                                // no eh filho da esquerda
                                (*pai)->info1.inicio = (*raiz)->info1.inicio;
                                removeu = remover23(pai, raiz, (*raiz)->info1);
                            } else if ((*pai)->cen == *raiz){
                                // no eh filho do centro
                                if ((*pai)->nInfo == 2)
                                {
                                    (*pai)->info1.fim = (*pai)->info2.fim;
                                    maior = (*pai)->info2;
                                    removeu = remover23(pai, raiz, (*raiz)->info1);
                                    removeu = remover23(&paiAux, &raiz_global, maior);
                                } else {
                                    /* code */
                                    (*pai)->info1.fim = (*raiz)->info1.fim;
                                    removeu = remover23(pai, raiz, (*raiz)->info1);
                                }
                            } else {
                                // no eh filho da direita
                                (*pai)->info2.fim = (*raiz)->info1.fim;
                                removeu = remover23(pai, raiz, (*raiz)->info1);
                            }
                        }
                        *alocou = 1;
                        
                    } else {
                        // nao eh folha

                        // busca maior info da esquerda
                        maiorInfoEsq((*raiz)->esq, &no, pai);
                        menor = menorInfo((*raiz)->cen);

                        if(no->nInfo == 2){
                            // tem duas infos
                            no->info2.fim = menor.fim;
                        }
                        else {
                            no->info1.fim = menor.fim;
                        }

                        // remove raiz e menor
                        removeu = remover23(pai, &raiz_global, (*raiz)->info1);
                        removeu = remover23(pai, &raiz_global, menor);

                        *alocou = 1;
                    }
                }
                
            } else if (qtdBlocoDisp > qtdBlocosAloc) // Resta blocos na alocação
            {
                // insercao no inicio
                if ((*raiz)->info1.inicio == 0)
                {
                    if (*pai != NULL)
                    {
                        (*pai)->info1.inicio = (*pai)->info1.inicio - qtdBlocosAloc;
                        (*raiz)->info1.fim = (*raiz)->info1.fim - qtdBlocosAloc;
                        
                    }
                    else if ((*raiz)->nInfo == 2)
                    { // Se tiver info2

                        (*raiz)->info2.inicio = (*raiz)->info2.inicio - qtdBlocosAloc;
                        (*raiz)->info1.fim = (*raiz)->info1.fim - qtdBlocosAloc;
                        // Altera a info2 e move info 2 pra info 1, libera Info2
                    }
                    else
                    { // Tem uma info apenas e não tem pai
                        // Subtrai os espaço de  memoria de info1 e cria um nó ocupado com o valor subtraido
                        novoFim = (*raiz)->info1.fim;
                        (*raiz)->info1.fim = (*raiz)->info1.fim - qtdBlocosAloc;
                        novoInicio = (*raiz)->info1.fim + 1;
                        aux = criaEnd('O', novoInicio, novoFim);
                        insere(raiz, *aux, promove, pai);
                    }
                } else if ((*raiz)->info1.fim == maximoBlocoMen - 1){
                    // insercao no fim
                    if ((*pai)->nInfo == 2) // Pai tem duas informações, altera info2
                        (*pai)->info2.fim = (*pai)->info2.fim + qtdBlocosAloc;
                    else // Pai tem uma info, altera info1
                        (*pai)->info1.fim = (*pai)->info1.fim + qtdBlocosAloc;
                    (*raiz)->info1.inicio = (*raiz)->info1.inicio + qtdBlocosAloc;
                } else {
                    // insercao no meio
                    if(ehFolha(*raiz)){
                        if ((*raiz)->nInfo == 2)
                        {
                            (*raiz)->info2.inicio = (*raiz)->info2.inicio - qtdBlocosAloc;
                            (*raiz)->info1.fim = (*raiz)->info1.fim - qtdBlocosAloc;
                        } else {
                            if ((*pai)->esq == *raiz)
                            {
                                (*raiz)->info1.fim = (*raiz)->info1.fim - qtdBlocosAloc;
                                (*pai)->info1.inicio = (*pai)->info1.inicio - qtdBlocosAloc;
                            } else if ((*pai)->cen == *raiz)
                            {
                                (*pai)->info1.fim += qtdBlocosAloc;
                                (*raiz)->info1.inicio += qtdBlocosAloc;
                            }
                        }
                    } else {
                        maiorInfoEsq((*raiz)->esq, &no, pai);    
                        if (no->nInfo == 2)
                        {
                            no->info2.fim += qtdBlocosAloc;
                        }else {
                            no->info1.fim += qtdBlocosAloc;
                        }
                        (*raiz)->info1.inicio += qtdBlocosAloc;
                    }
                }
                *alocou = 1;
            }
        }
        
        if (!*alocou)
        {
            alocarMemoria(&((*raiz)->cen), raiz, qtdBlocosAloc, maximoBlocoMen, alocou);
        }

        // Analisar a info2, caso tenha
        if (!*alocou && (*raiz)->nInfo == 2)
        { // Raiz tem dois filhos, checa a info 2
            if ((*raiz)->info2.estado == 'L')
            {
                
                int qtdBlocoDisp = (*raiz)->info2.fim - (*raiz)->info2.inicio + 1;
                
                if (qtdBlocoDisp == qtdBlocosAloc)
                {
                    // verificar se tem filho do centro
                    // verificar se o centro tem duas infos 

                    if ((*raiz)->cen != NULL)
                    {
                        // tem filho do centro

                        // busca a maior info do centro
                        maiorInfoEsq((*raiz)->cen, &no, pai);

                        // busca a menor info da direita
                        menor = menorInfo((*raiz)->dir);

                        // altera tamanho da maior info do centro
                        if (no->nInfo == 2)
                        {
                            // tem duas infos
                            no->info2.fim = menor.fim;
                        }
                        else
                        {
                            no->info1.fim = menor.fim;
                        }

                        // remove raiz e menor info da direita
                        removeu = remover23(pai, &raiz_global, menor);
                        removeu = remover23(pai, &raiz_global, (*raiz)->info2);
                        *alocou = 1;
                    }
                    else
                    {
                        // Altera o tamanho da info1 e remove a info2
                        (*raiz)->info1.fim = (*raiz)->info2.fim;
                        removeu = remover23(pai, raiz, (*raiz)->info2);  
                        *alocou = 1;                  
                    }

                    
                }
                else if (qtdBlocoDisp > qtdBlocosAloc)
                {
                    if (ehFolha(*raiz))
                    {
                        (*raiz)->info1.fim = (*raiz)->info1.fim + qtdBlocosAloc;
                        (*raiz)->info2.inicio = (*raiz)->info2.inicio + qtdBlocosAloc;
                    }else {
                        // busca maior info do centro
                        maiorInfoEsq((*raiz)->cen, &no, pai);
                        if (no->nInfo == 2)
                        {
                            no->info2.fim += qtdBlocosAloc;
                        }else {
                            no->info1.fim += qtdBlocosAloc;
                        }
                        (*raiz)->info2.inicio += qtdBlocosAloc;
                    }
                    *alocou = 1;
                }
            }
        }
        
        if (!*alocou)
        {
            alocarMemoria(&((*raiz)->dir), raiz, qtdBlocosAloc, maximoBlocoMen, alocou);
        }
    }
}

int blocoValido(int inicio, int fim, int qtdBlocosMaximo){
    int ehValido = 0;
    if(inicio <= fim && inicio >= 0 && inicio <= qtdBlocosMaximo - 1 && fim <= qtdBlocosMaximo - 1){
       ehValido = 1; 
    }
    return ehValido;
}

void liberarMemoria(blocoMem **raiz, blocoMem **pai, endeMem liberarEspaco, int maximoBlocoMen, int *liberou){
    int removeu = 0, novoInicio, novoFim;
    endeMem auxMaior, auxMenor, auxMaiorInfo2;
    endeMem *aux, *aux2, *promove;
    aux = NULL;
    blocoMem *paiAux,*no;
    paiAux = NULL;
    no = NULL;

    promove = (endeMem*)calloc(1,sizeof(endeMem));
    if (*raiz != NULL)
    {
        int qtdBlocosDesalocar = liberarEspaco.fim - liberarEspaco.inicio + 1;
        if (!*liberou)
            liberarMemoria(&((*raiz)->esq), raiz, liberarEspaco, maximoBlocoMen, liberou);    
        if (!*liberou && (*raiz)->info1.estado == 'O'){
            int qtdBlocoDispInfo1 = ((*raiz)->info1.fim - (*raiz)->info1.inicio) + 1;

            if (qtdBlocoDispInfo1 >= qtdBlocosDesalocar){ //Tem a exata quantidade de memória desejada
                if((*raiz)->info1.inicio == liberarEspaco.inicio && (*raiz)->info1.fim == liberarEspaco.fim){//Caso perfeito, o espaço a ser liberado é a info1
                    if(ehFolha(*raiz))
                    { 
                        // quantidade de infos da raiz
                        if((*raiz)->nInfo == 1){
                            // verifica se tem pai
                            if (*pai != NULL)
                            {
                                // tem pai
                                // de onde a raiz veio
                                if ((*pai)->esq == *raiz)
                                {
                                    // filho da esquerda
                                    aux = criaEnd('L', (*raiz)->info1.inicio, (*pai)->info1.fim);
                                    auxMenor = (*raiz)->info1;
                                    auxMaior = (*pai)->info1;
                                    removeu = remover23(pai, raiz, auxMenor);
                                    removeu = remover23(pai, raiz, auxMaior);

                                    insere(raiz, *aux, promove, pai);

                                    *liberou = 1;

                                } else if ((*pai)->cen == *raiz)
                                {
                                    // filho do centro
                    
                                    if ((*pai)->nInfo == 2)
                                    {
                                        auxMaior = (*raiz)->info1;
                                        auxMaiorInfo2 = (*pai)->info2;
                                        aux = criaEnd('L', (*pai)->info1.inicio, (*pai)->info2.fim);
                
                                        paiAux = NULL;
                                        removeu = remover23(pai, raiz, auxMaior);
                                        paiAux = NULL;
                                        removeu = remover23(&paiAux, &raiz_global, auxMaiorInfo2);

                                        (*pai)->info1.fim = auxMaiorInfo2.fim;

                                        *liberou = 1;
                                    } else {
                                        aux = criaEnd('L', (*pai)->info1.inicio, (*raiz)->info1.fim);
                                        auxMenor = (*pai)->info1;
                                        auxMaior = (*raiz)->info1;
                                        removeu = remover23(pai, raiz, auxMaior);
                                        removeu = remover23(&paiAux, &raiz_global, auxMenor);

                                        insere(&raiz_global, *aux, promove, &paiAux);
                                        *liberou = 1;
                                    }
                                    
                                } else {
                                    // filho da direita
                                    aux = criaEnd('L', (*pai)->info2.inicio, (*raiz)->info1.fim);
                                    auxMenor = (*pai)->info2;
                                    auxMaior = (*raiz)->info1;
                                    paiAux = NULL;
                                    removeu = remover23(pai, raiz, auxMaior);
                                    removeu = remover23(&paiAux, &raiz_global, auxMenor);

                                    insere(raiz, *aux, promove, pai);
                                    *liberou = 1;
                                }
                                
                                
                            } else {
                                // não tem pai
                                // inverter estado
                                inverteEstadoBloco(&((*raiz)->info1));
                                *liberou = 1;
                            }
                            
                        } else {
                            // tem duas info
                            aux = criaEnd('L', (*raiz)->info1.inicio, (*raiz)->info2.fim);
                            if (*pai != NULL)
                            {
                                // tem pai
                                // de onde a raiz veio
                                if ((*pai)->esq == *raiz)
                                {
                                    // filho da esquerda
                                    auxMenor = (*raiz)->info1;
                                    auxMaior = (*raiz)->info2;
                                    removeu = remover23(pai, raiz, auxMenor);
                                    removeu = remover23(pai, raiz, auxMaior);

                                    insere(raiz, *aux, promove, pai);

                                } else if ((*pai)->cen == *raiz)
                                {
                                    // filho do centro
                                    aux->inicio = (*pai)->info2.inicio;
                                    auxMenor = (*pai)->info1;
                                    auxMaior = (*raiz)->info1;
                                    auxMaiorInfo2 = (*raiz)->info2;
                                    paiAux = NULL;
                                    removeu = remover23(&raiz_global, pai, auxMenor); // Perigo: removendo info do pai   
                                    removeu = remover23(pai, raiz, auxMaior);
                                    removeu = remover23(pai, raiz, auxMaiorInfo2);

                                    insere(raiz, *aux, promove, pai);
                                    
                                } else {
                                    // filho da direita
                                    aux->inicio = (*pai)->info2.inicio; 
                                    auxMenor = (*pai)->info2;
                                    auxMaior = (*raiz)->info1;
                                    auxMaiorInfo2 = (*raiz)->info2;
                                    removeu = remover23(&raiz_global, raiz, auxMenor);
                                    removeu = remover23(pai, raiz, auxMaior);
                                    removeu = remover23(pai, raiz, auxMaiorInfo2);

                                    insere(raiz, *aux, promove, pai);
                                    *liberou = 1;
                                }
                            } else {
                                // não tem pai
                                removeu = remover23(&paiAux, &raiz_global, (*raiz)->info2);
                                (*raiz)->info1.fim = aux->fim;
                                (*raiz)->info1.estado = 'L'; 
                                *liberou = 1;
                            }
                        }
                    }else {
                        // buscar maior valor da esquerda
                        
                        auxMaior = maiorInfo((*raiz)->esq);
                        auxMenor = menorInfo((*raiz)->cen);
                        aux = criaEnd('L', auxMaior.inicio, auxMenor.fim);

                        removeu = remover23(pai, raiz, auxMenor);
                        removeu = remover23(pai, raiz, auxMaior);

                        (*raiz)->info1.inicio = auxMaior.inicio;
                        (*raiz)->info1.fim = auxMenor.fim;
                        (*raiz)->info1.estado = 'L';

                        *liberou = 1;
                    }
                }
                // Info1 é ocupado, tem a quantidade necessário pra desalocar porém deve retirar uma parte da info1
                else if((*raiz)->info1.inicio == liberarEspaco.inicio){
                    // verifica se esta no inicio da memoria
                    if((*raiz)->info1.inicio == 0){
                        // inicio da memoria
                        (*raiz)->info1.inicio = (*raiz)->info1.inicio + qtdBlocosDesalocar;
                        aux = criaEnd('L',liberarEspaco.inicio,liberarEspaco.fim);
                        insere(raiz, *aux, promove, pai);
                    } else{
                        // não esta no inicio da memoria
                        // verifica sou filho do centro ou da direita
                        
                        // verifica se tem pai
                        if(*pai != NULL){
                            if ((*pai)->cen == *raiz) // raiz eh filho do centro
                                (*pai)->info1.fim = (*pai)->info1.fim + qtdBlocosDesalocar;   
                            else // raiz eh filho da direita 
                                (*pai)->info2.fim = (*pai)->info2.fim + qtdBlocosDesalocar;
                        } else {
                            // se ele nao tem pai, ele eh a raiz e tem filho da esquerda
                            // verifica se filho da esquerda tem duas infos
                            if((*raiz)->esq->nInfo == 2){
                                // filho da esquerda tem duas infos
                                // altera info2
                                (*raiz)->esq->info2.fim = (*raiz)->esq->info2.fim + qtdBlocosDesalocar;
                            } else {
                                // filho da esquerda tem uma info
                                // altera info1
                                (*raiz)->esq->info1.fim = (*raiz)->esq->info1.fim + qtdBlocosDesalocar;
                            }
                        }                    
                        (*raiz)->info1.inicio = (*raiz)->info1.inicio + qtdBlocosDesalocar;
                    }
                    *liberou = 1;
                }
                else if((*raiz)->info1.fim == liberarEspaco.fim){
                    // No fim do bloco

                    // verifica se esta no fim da memoria
                    if((*raiz)->info1.fim == maximoBlocoMen - 1){
                        // fim da memoria
                        (*raiz)->info1.fim = (*raiz)->info1.fim - qtdBlocosDesalocar;
                        aux = criaEnd('L',liberarEspaco.inicio,liberarEspaco.fim);
                        insere(raiz, *aux, promove, pai);
                    } else{
                        // não esta no fim da memoria
                        // verifica sou filho do centro ou da esquerda

                        if ((*pai)->cen == *raiz){ // raiz eh filho do centro
                            if((*pai)->nInfo == 2){
                                (*raiz)->info1.fim = (*raiz)->info1.fim - qtdBlocosDesalocar;
                                (*pai)->info2.inicio = (*pai)->info2.inicio - qtdBlocosDesalocar;    
                            }
                            else{
                                (*raiz)->info1.fim = (*raiz)->info1.fim - qtdBlocosDesalocar;
                                aux = criaEnd('L',liberarEspaco.inicio,liberarEspaco.fim);
                                insere(raiz, *aux, promove, pai);   
                            }
                        }
                        else if((*pai)->esq == *raiz){
                            (*raiz)->info1.fim = (*raiz)->info1.fim - qtdBlocosDesalocar;
                            (*pai)->info1.inicio = (*pai)->info1.inicio - qtdBlocosDesalocar;
                        } // raiz eh filho da esquerda 
                    }
                    *liberou = 1;
                } else if ((*raiz)->info1.inicio < liberarEspaco.inicio && (*raiz)->info1.fim > liberarEspaco.fim)
                {
                    // desalocando no meio de um bloco
                    if ((*raiz)->info1.inicio == 0)
                    {
                        // inicio da memoria
                        // verifica se tem pai
                        aux = criaEnd('O', (*raiz)->info1.inicio, liberarEspaco.inicio - 1);
                        aux2 = criaEnd('L', liberarEspaco.inicio, liberarEspaco.fim);
                        (*raiz)->info1.inicio = liberarEspaco.fim + 1; 
                        insere(raiz, *aux2, promove, pai);
                        
                        insere(pai, *aux, promove, &paiAux); 
                        
                    }else if ((*raiz)->info1.fim == maximoBlocoMen - 1){
                        // fim da memoria
                        aux2 = criaEnd('L', liberarEspaco.inicio, liberarEspaco.fim);
                        aux = criaEnd('O', liberarEspaco.fim + 1, (*raiz)->info1.fim);
                        (*raiz)->info1.fim = liberarEspaco.inicio - 1; 
                        insere(raiz, *aux2, promove, pai);
                        insere(pai, *aux, promove, &paiAux);
                    } else {
                        // meio da memoria
                        aux2 = criaEnd('L', liberarEspaco.inicio, liberarEspaco.fim);
                        aux = criaEnd('O', liberarEspaco.fim + 1, (*raiz)->info1.fim);
                        (*raiz)->info1.fim = liberarEspaco.inicio - 1;
                        insere(raiz, *aux2, promove, pai);
                        insere(pai, *aux, promove, &paiAux);
                    }
                    *liberou = 1;
                }
            }
        }
        if (!*liberou)
            liberarMemoria(&((*raiz)->cen), raiz, liberarEspaco, maximoBlocoMen, liberou);  
        if (!*liberou && (*raiz)->info2.estado == 'O'){
            int qtdBlocoDispInfo2 = ((*raiz)->info2.fim - (*raiz)->info2.inicio) + 1;
            if (qtdBlocoDispInfo2 >= qtdBlocosDesalocar){//Tem a quantidade necessária de blocos
                if((*raiz)->info2.inicio == liberarEspaco.inicio && (*raiz)->info2.fim == liberarEspaco.fim){//quer toda a info2
                    if(ehFolha(*raiz)){//Se for folha
                        if((*raiz)->info1.estado == 'L'){// e info1 for livre, junta as infos
                            (*raiz)->info1.fim = (*raiz)->info2.fim;
                            (*raiz)->info2.inicio = -1; 
                            (*raiz)->info2.fim = -1; 
                            (*raiz)->nInfo = 1;

                            if(*pai != NULL){//Se tiver pai, junta a info 1 da raiz com a do pai
                            //Nó veio da esq do pai
                                if((*pai)->nInfo == 2){
                                    (*pai)->info1.inicio = (*pai)->info2.inicio;
                                    removeu = remover23(pai, raiz, (*raiz)->info1);
                                }
                            
                            }
                        }
                    }
                    else{    
                        endeMem maior,menor, auxRaiz;
                        maior = maiorInfo((*raiz)->cen);
                        menor = menorInfo((*raiz)->dir);
                        
                        auxRaiz.inicio = (*raiz)->info2.inicio;
                        auxRaiz.fim = (*raiz)->info2.fim;
                        
                        removeu = remover23(pai, raiz, menor);
                        removeu = remover23(pai, raiz, maior);
                        removeu = remover23(pai, raiz, auxRaiz);

                        auxRaiz.estado = 'L';
                        auxRaiz.inicio = maior.inicio;
                        auxRaiz.fim = menor.fim;

                        insere(raiz, auxRaiz, promove, pai);
                    }
                    *liberou = 1;
                }
                else if((*raiz)->info2.inicio <= liberarEspaco.inicio && (*raiz)->info2.fim >= liberarEspaco.fim){//Quer parte da info2
                    if(ehFolha(*raiz)){//Apenas redimensiona as infos
                        if((*raiz)->info2.inicio == liberarEspaco.inicio){//Inicio da info2
                            (*raiz)->info1.fim = (*raiz)->info1.fim + qtdBlocosDesalocar; 
                            (*raiz)->info2.inicio = (*raiz)->info2.inicio + qtdBlocosDesalocar; 
                        }
                        else if((*raiz)->info2.fim == liberarEspaco.fim){//fim da info2
                            (*raiz)->info2.fim = (*raiz)->info2.fim - qtdBlocosDesalocar;
                            aux = criaEnd('L',liberarEspaco.inicio,liberarEspaco.fim);
                            paiAux = NULL;
                            insere(raiz,*aux,promove,&paiAux);
                        }
                        else{//Meio da info2
                            aux = criaEnd('O',liberarEspaco.fim + 1,(*raiz)->info2.fim);//3
                        
                            (*raiz)->info2.fim = liberarEspaco.inicio - 1;//1

                            aux2 = criaEnd('L',liberarEspaco.inicio,liberarEspaco.fim);//2

                            paiAux = NULL;
                            insere(raiz,*aux2,promove,&paiAux);
                            paiAux = NULL;
                            insere(raiz,*aux,promove,&paiAux);
                        }
                    }
                    else{//Se não for folha
                        if((*raiz)->info2.inicio == liberarEspaco.inicio){//Inicio da info2
                            if((*raiz)->cen->nInfo == 2)//Se o centro diver duas infos
                                (*raiz)->cen->info2.fim = (*raiz)->cen->info2.fim + qtdBlocosDesalocar;
                            else//Se o centro tiver 1 info só
                                (*raiz)->cen->info1.fim = (*raiz)->cen->info1.fim + qtdBlocosDesalocar;
                            (*raiz)->info2.inicio = (*raiz)->info2.inicio + qtdBlocosDesalocar; 
                        }
                        else if((*raiz)->info2.fim == liberarEspaco.fim){//Fim da info2
                            (*raiz)->dir->info1.inicio = (*raiz)->dir->info1.inicio - qtdBlocosDesalocar;
                            (*raiz)->info2.fim = (*raiz)->info2.fim - qtdBlocosDesalocar; 
                        }
                        else{//Meio da info2
                            aux2 = criaEnd('O',liberarEspaco.fim+1,(*raiz)->info2.fim);//2
                           
                            (*raiz)->info2.fim = liberarEspaco.inicio - 1;//1

                            aux = criaEnd('L',liberarEspaco.inicio,liberarEspaco.fim);//3

                            paiAux = NULL;
                            insere(raiz,*aux2,promove,&paiAux);
                            paiAux = NULL;
                            insere(raiz,*aux,promove,&paiAux);
                        }
                    }
                    *liberou = 1;
                }
            }
        } 
        if (!*liberou)
            liberarMemoria(&((*raiz)->dir), raiz, liberarEspaco, maximoBlocoMen, liberou);  
    }
}

endeMem maiorInfo(blocoMem *raiz){
    endeMem maiorInf;
    maiorInf.inicio = -1;
    maiorInf.fim = -1;
    if(raiz != NULL){
        if(ehFolha(raiz)){
            if(raiz->nInfo == 2){
                maiorInf = raiz->info2;
            }    
            else
                maiorInf = raiz->info1;
        }
        else{
            if(raiz->nInfo == 1){
                maiorInf = maiorInfo(raiz->cen);    
            }
            else{
                maiorInf = maiorInfo(raiz->dir);
            }
        }
    }
    return maiorInf;
}

endeMem menorInfo(blocoMem *raiz){
    endeMem menorInf;
    menorInf.inicio = -1;
    menorInf.fim = -1;
    if(raiz != NULL){
        if(ehFolha(raiz)){    
            menorInf = raiz->info1;
        }
        else{    
            menorInf = maiorInfo(raiz->esq);    
        }
    }
    return menorInf;
}

void inverteEstadoBloco(endeMem *info)
{
    if (info->estado == 'L')
        info->estado = 'O';
    else
        info->estado = 'L';
}

endeMem *criaEnd(char estado, int inicio, int fim)
{
    endeMem *novoEnd;
    novoEnd = (endeMem *)malloc(sizeof(endeMem));
    novoEnd->estado = estado;
    novoEnd->inicio = inicio;
    novoEnd->fim = fim;
    return novoEnd;
}

blocoMem *criaBloco(endeMem info1, blocoMem *esq, blocoMem *cen, blocoMem *dir)
{
    blocoMem *novoNo;
    novoNo = (blocoMem *)malloc(sizeof(blocoMem));
    novoNo->info1 = info1;
    novoNo->info2.inicio = -1;
    novoNo->info2.fim = -1;
    novoNo->esq = esq;
    novoNo->cen = cen;
    novoNo->dir = dir;
    novoNo->nInfo = 1;
    return novoNo;
}

void adicionaBloco(blocoMem **raiz, endeMem info, blocoMem *maiorNo)
{
    if (info.inicio > ((*raiz)->info1.fim))
    {
        (*raiz)->info2 = info;
        (*raiz)->dir = maiorNo;
    } // Checar se precisa da outra condição
    else
    {
        (*raiz)->info2 = (*raiz)->info1;
        (*raiz)->info1 = info;
        (*raiz)->dir = (*raiz)->cen;
        (*raiz)->cen = maiorNo;
    }
    (*raiz)->nInfo = 2;
}

int ehFolha(blocoMem *no)
{
    int ehFolha = 0;
    if (no->esq == NULL && no->cen == NULL && no->dir == NULL)
        ehFolha = 1;
    return ehFolha;
}

blocoMem *insere(blocoMem **no, endeMem bloco, endeMem *promove, blocoMem **pai)
{
    blocoMem *maiorNo;
    maiorNo = NULL;
    endeMem promove1;
    if (*no == NULL)                              // Se a raiz for nula
        *no = criaBloco(bloco, NULL, NULL, NULL); // Info1, Esq, Cen, Dir
    else
    { // Se for folha
        if (ehFolha(*no))
        {
            if ((*no)->nInfo == 1) // Se tiver uma informação adiciona
                adicionaBloco(no, bloco, NULL);
            else
            { // Se estiver cheio, quebra o nó e sobe a info do meio pro pai, se não tiver pai cria um nó
                maiorNo = quebraBloco(no, bloco, promove, NULL);//3
                if (*pai == NULL)
                {
                    *no = criaBloco(*promove, *no, maiorNo, NULL);
                    maiorNo = NULL;
                }
            }
        }
        else
        { // Raiz não é nula e não é folha, chama recursivo para um dos filhos
            if (bloco.fim < (*no)->info1.inicio)
                maiorNo = insere(&((*no)->esq), bloco, promove, no);
            else if (((*no)->nInfo == 1) || (bloco.fim < (*no)->info2.inicio))
                maiorNo = insere(&((*no)->cen), bloco, promove, no);//1
            else
                maiorNo = insere(&((*no)->dir), bloco, promove, no);//2

            if (maiorNo != NULL)
            {
                if ((*no)->nInfo == 1)
                { // Se tiver inserido e o nó só tiver uma informação adiciona
                    adicionaBloco(no, *promove, maiorNo);
                    maiorNo = NULL;
                }
                else
                { 
                    maiorNo = quebraBloco(no, *promove, &promove1, maiorNo);
                    if (*pai == NULL)
                    {
                        *no = criaBloco(promove1, *no, maiorNo, NULL);
                        maiorNo = NULL;
                    }
                    else{
                        *promove = promove1;
                    }
                }
            }
        }
    }
    return maiorNo;
}

blocoMem *quebraBloco(blocoMem **raiz, endeMem bloco, endeMem *sobe, blocoMem *maiorNo)
{
    blocoMem *novoNo;
    if (bloco.fim < (*raiz)->info1.inicio)
    {
        *sobe = (*raiz)->info1; // Testar esse caso
        //*sobeGlobal = (*raiz)->info1; 
        novoNo = criaBloco((*raiz)->info2, (*raiz)->cen, (*raiz)->dir, NULL);
        (*raiz)->info1 = bloco;
        (*raiz)->cen = maiorNo;
    }
    else if (bloco.fim < (*raiz)->info2.inicio)
    {
        *sobe = bloco; // Testar esse caso
        //*sobeGlobal = bloco; 
        novoNo = criaBloco((*raiz)->info2, maiorNo, (*raiz)->dir, NULL);
    }
    else
    {
        *sobe = (*raiz)->info2; // Linha perigosa
        //*sobeGlobal = (*raiz)->info2; 
        novoNo = criaBloco(bloco, (*raiz)->dir, maiorNo, NULL);
    }
    (*raiz)->info2.inicio = -1;
    (*raiz)->info2.fim = -1;
    (*raiz)->nInfo = 1;
    (*raiz)->dir = NULL;
    return novoNo;
}

void mostraEmOrdem(blocoMem *Raiz)
{
    if (Raiz != NULL)
    {
        mostraEmOrdem(Raiz->esq);
        printf("Estado1 : %c\n", Raiz->info1.estado);
        printf("Inicio1 : %d\n", Raiz->info1.inicio);
        printf("Fim1 : %d\n", Raiz->info1.fim);
        mostraEmOrdem(Raiz->cen);
        if (Raiz->info2.inicio >= 0)
        {
            printf("Estado2 : %c\n", Raiz->info2.estado);
            printf("Inicio2 : %d\n", Raiz->info2.inicio);
            printf("Fim2 : %d\n", Raiz->info2.fim);
        }
        mostraEmOrdem(Raiz->dir);
    }
}

int buscaBloco(blocoMem *raiz, int inicio, int fim)
{   
    int encontrou = 0;
    if (raiz != NULL)
    {
        // verifica se o bloco esta a esquerda da info1
        if (fim < (*raiz).info1.inicio)
            encontrou = buscaBloco((*raiz).esq, inicio, fim);
        else if ((*raiz).info1.inicio == inicio && (*raiz).info1.fim == fim)
            encontrou = 1;
        else if ((*raiz).nInfo == 1 || (fim < (*raiz).info2.inicio))
            encontrou = buscaBloco((*raiz).cen, inicio, fim);
        else if ((*raiz).info2.inicio == inicio && (*raiz).info2.fim == fim)
            encontrou = 1;
        else
            encontrou = buscaBloco((*raiz).dir, inicio, fim);   
    }
    return encontrou;
}

int remover23(blocoMem **Pai, blocoMem **Raiz, endeMem valor)
{
    int removeu = 0;
    blocoMem *no = NULL, *no1, *paiNo = NULL, *paiNo1 = NULL, **aux;
    aux = (blocoMem **)malloc(sizeof(blocoMem *));
    no1 = (blocoMem *)malloc(sizeof(blocoMem));

    if (*Raiz != NULL)
    {
        if (ehFolha(*Raiz) == 1)
        {
            if ((*Raiz)->nInfo == 2) // Quando é folhac e tem duas informações
            {
                if (((*Raiz)->info2.inicio == valor.inicio) && ((*Raiz)->info2.fim == valor.fim))
                { // quando é folha, tem duas informações e o numero ta na segunda posição
                    (*Raiz)->info2.inicio = -1;
                    (*Raiz)->info2.fim = -1;
                    (*Raiz)->nInfo = 1;
                    removeu = 1;
                }
                else if (((*Raiz)->info1.inicio == valor.inicio) && ((*Raiz)->info1.fim == valor.fim))
                { // quando é folha, tem duas informações e o numero ta na primeira posição do nó
                    (*Raiz)->info1 = (*Raiz)->info2;
                    (*Raiz)->info2.inicio = -1;
                    (*Raiz)->info2.fim = -1;
                    (*Raiz)->nInfo = 1;
                    removeu = 1;
                }
            }
            else if (((*Raiz)->info1.inicio == valor.inicio) && ((*Raiz)->info1.fim == valor.fim)) // Quando é folha e tem uma informação
            {
                if (*Pai == NULL) // Se não tem pai é pq é o último elemento do nó
                {
                    free(*Raiz);
                    *Raiz = NULL;
                    removeu = 1;
                }
                else if (*Raiz == (*Pai)->esq) // Verifica se sou filho da esquerda
                {
                    (*Raiz)->info1 = (*Pai)->info1;
                    paiNo = *Pai;
                    menorInfoDir((*Pai)->cen, &no, &paiNo);
                    (*Pai)->info1 = no->info1;
                    removeu = 1;

                    if (no->nInfo == 2)
                    {
                        no->info1 = no->info2;
                        no->info2.inicio = -1;
                        no->info2.fim = -1;
                        no->nInfo = 1;
                    }
                    else
                    {
                        if (paiNo->nInfo == 1)
                        {
                            (*Raiz)->info2 = no->info1;
                            (*Raiz)->nInfo = 2;
                            free(no);
                            *Pai = *Raiz;
                        }
                        else
                        {
                            no->info1 = paiNo->info2;
                            paiNo1 = paiNo;
                            menorInfoDir(paiNo->dir, &no1, &paiNo1);
                            paiNo->info2 = no1->info1;

                            if (no1->nInfo == 2)
                            {
                                no1->info1 = no1->info2;
                                no1->info2.inicio = -1;
                                no1->info2.fim = -1;
                                no1->nInfo = 1;
                            }
                            else
                            {
                                no->info2 = paiNo->info2;
                                no->nInfo = 2;
                                paiNo->info2.inicio = -1;
                                paiNo->info2.fim = -1;
                                paiNo->nInfo = 1;
                                free(no1);
                                paiNo1->dir = NULL;
                            }
                        }
                    }
                }
                else if (*Raiz == (*Pai)->cen) // Verifica se razi e filho do centro
                {
                    removeu = 1;
                    if ((*Pai)->nInfo == 1) // O pai tem só uma informação
                    {
                        if (((*Pai)->esq)->nInfo == 2) // O filho a esquerda do pai tem duas informações
                        {
                            (*Raiz)->info1 = (*Pai)->info1;
                            (*Pai)->info1 = ((*Pai)->esq)->info2;
                            ((*Pai)->esq)->info2.inicio = -1;
                            ((*Pai)->esq)->info2.fim = -1;
                            ((*Pai)->esq)->nInfo = 1;
                        }
                        else // O filho a esquerda do pai tem uma informação
                        {
                            ((*Pai)->esq)->info2 = (*Pai)->info1;
                            free(*Raiz);
                            ((*Pai)->esq)->nInfo = 2;
                            *aux = (*Pai)->esq;
                            free(*Pai);
                            *Pai = *aux;
                        }
                    }
                    else // O pai tem duas informações
                    {
                        (*Raiz)->info1 = (*Pai)->info2;
                        paiNo = *Pai;
                        menorInfoDir((*Pai)->dir, &no, &paiNo);
                        (*Pai)->info2 = no->info1;

                        if (no->nInfo == 2)
                        {
                            no->info1 = no->info2;
                            no->info2.inicio = -1;
                            no->info2.fim = -1;
                            no->nInfo = 1;
                        }
                        else
                        {
                            (*Raiz)->nInfo = 2;
                            (*Raiz)->info2 = (*Pai)->info2;
                            (*Pai)->info2.inicio = -1;
                            (*Pai)->info2.fim = -1;
                            (*Pai)->nInfo = 1;
                            free(no);
                            (*Pai)->dir = NULL;
                        }
                    }
                }
                else // Raiz e filho da direita
                {
                    removeu = 1;
                    paiNo = *Pai;
                    maiorInfoEsq((*Pai)->cen, &no, &paiNo);

                    if (no->nInfo == 1)
                    {
                        no->info2 = (*Pai)->info2;
                        (*Pai)->info2.inicio = -1;
                        (*Pai)->info2.fim = -1;
                        (*Pai)->nInfo = 1;
                        no->nInfo = 2;
                        free(*Raiz);
                        *Raiz = NULL;
                    }
                    else
                    {
                        (*Raiz)->info1 = (*Pai)->info2;
                        (*Pai)->info2 = no->info2;
                        no->info2.inicio = -1;
                        no->info2.fim = -1;
                        no->nInfo = 1;
                    }
                }
            }
        }
        else
        { // se nao é folha
            if (valor.fim < (*Raiz)->info1.inicio)
                removeu = remover23(Raiz, &(*Raiz)->esq, valor);
            else if (((*Raiz)->info1.inicio == valor.inicio) && ((*Raiz)->info1.fim == valor.fim))
            {
                paiNo = *Raiz;
                menorInfoDir((*Raiz)->cen, &no, &paiNo);
                (*Raiz)->info1 = no->info1;
                remover23(Raiz, &(*Raiz)->cen, (*Raiz)->info1);
                removeu = 1;
            }
            else if (((*Raiz)->nInfo == 1) || (valor.fim < (*Raiz)->info2.inicio))
            {
                removeu = remover23(Raiz, &(*Raiz)->cen, valor);
            }
            else if (((*Raiz)->info2.inicio == valor.inicio) && ((*Raiz)->info2.fim == valor.fim)) // info2 a ser removida
            {
                // verifica se é folha
                if(ehFolha(*Raiz)){
                    (*Raiz)->info1.fim = (*Raiz)->info2.fim;
                    (*Raiz)->info2.inicio = -1;
                    (*Raiz)->info2.fim = -1;
                    (*Raiz)->nInfo = 1;
                    removeu = 1;
                } else if(ehFolha((*Raiz)->dir)) // verificar se o filho da direita eh folha
                {
                    // remover info2 com direita folha
                    removeu = removeInfo2ComDirFolha(Raiz, Pai);
                }else {
                    // direita nao eh folha
                    // obter no com menor info da direita
                    // trocar info2 com menor info da direita
                    menorInfoDir((*Raiz)->dir, &no, &paiNo);
                    (*Raiz)->info2 = no->info1;

                    // remover menor info da direita
                    removeu = remover23(Raiz, &(*Raiz)->dir, no->info1);
                }
            }
            else
            {
                removeu = remover23(Raiz, &(*Raiz)->dir, valor);
            }
        }
    }
    return removeu;
}

int removeInfo2ComDirFolha(blocoMem **Raiz, blocoMem **paiNo){
    // decobrir se filho da direita tem 2 info
    if ((*Raiz)->dir->nInfo == 2)
    {
        // trocar info2 com filho da direita
        (*Raiz)->info2 = (*Raiz)->dir->info1;
        // remover info2 do filho da direita
        (*Raiz)->dir->info1 = (*Raiz)->dir->info2;
        (*Raiz)->dir->info2.inicio = -1;
        (*Raiz)->dir->info2.fim = -1;
        (*Raiz)->dir->nInfo = 1;
    }
    else
    {
        // filho da direita tem 1 info
        // verificar se centro tem duas info
        if ((*Raiz)->cen->nInfo == 2)
        {
            // centro tem duas info
            // trocar info2 com centro
            (*Raiz)->info2 = (*Raiz)->cen->info2;
            // remover info2 do centro
            (*Raiz)->cen->info2.inicio = -1;
            (*Raiz)->cen->info2.fim = -1;
            (*Raiz)->cen->nInfo = 1;
        }
        else
        {

            // Info da direita vai para info 2 do centro
            (*Raiz)->cen->info2 = (*Raiz)->dir->info1;
            (*Raiz)->cen->nInfo = 2;

            // remove info2 da raiz
            (*Raiz)->info2.inicio = -1;
            (*Raiz)->info2.fim = -1;
            (*Raiz)->nInfo = 1;

            // remove info da direita
            int removeu = remover23(Raiz, &(*Raiz)->dir, (*Raiz)->dir->info1);
        }
        
    }
    
}

void menorInfoDir(blocoMem *Raiz, blocoMem **no, blocoMem **paiNo)
{
    if (Raiz->esq != NULL)
    {
        *paiNo = Raiz;
        menorInfoDir(Raiz->esq, no, paiNo);
    }
    else
        *no = Raiz;
}

void maiorInfoEsq(blocoMem *Raiz, blocoMem **no, blocoMem **paiNo)
{
    if(Raiz != NULL){
        if(ehFolha(Raiz))
            *no = Raiz;
        else{
            if(Raiz->nInfo == 1){
                maiorInfoEsq(Raiz->cen, no, paiNo);    
            }
            else{
                maiorInfoEsq(Raiz->dir, no, paiNo);    
            }
        }
    }
}


void imprimirNo(blocoMem *raiz)
{
    if(raiz != NULL){
        printf("info1 -> Inicio %d Fim %d Estado %c\n",raiz->info1.inicio,raiz->info1.fim,raiz->info1.estado);
        if(raiz->nInfo == 2){
            printf("info2 -> Inicio %d Fim %d Estado %c\n",raiz->info2.inicio,raiz->info2.fim,raiz->info2.estado);
        }
    }
}