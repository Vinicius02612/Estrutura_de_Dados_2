#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct info{
    //cria uma estrutura para armazenar as informações sobre um nó da árvore
    int inicio, fim;
    char status;
};

struct arv23{
    //cria uma estrutura para armazenar a arvore 2-3
    struct info *Info1, *Info2; 
    int NInfos;
  struct arv23 *esq, *cen, *dir;
};

//prótotipos das funções
struct arv23 *criaNo(struct info *Info, struct arv23 *FEsq, struct arv23 *FCen);
int ehFolha(struct arv23 *Raiz);
struct arv23 *adicionaNo(struct arv23 *No, struct info *Info, struct arv23 *Filho);
struct info *cria_info(int infoInicio, int infoFim, char status);
void quebraNo(struct arv23 **No, struct info *Info, struct arv23 *FilhoMaior, struct info **Sobe, struct arv23 **Novo);
struct arv23 *insereArv23(struct arv23 **Pai,struct arv23 **Raiz, struct info *Info, struct info **Sobe);
void imprimeArvore23(struct arv23 *Raiz);
void existe_NO(struct arv23 *Raiz, int qtd, struct info **res);
struct info *add_new(struct arv23 **Pai,struct arv23 **Raiz, struct info *Info, int qtd);
int buscaEndereco(struct arv23* raiz, int endereco);
int menu();


int main() {
    srand(time(NULL));

    //cria variaveis para armazenar a arvore 2-3
    struct arv23 *Raiz;
    struct arv23 *Pai;
    struct info *res;
    struct info *Sobe;
    Raiz = NULL;
    Sobe = NULL;
    Pai = NULL;  
    res = NULL;  

    int escolha = 1, q_bloco, flag;
    char status_bloco;

    int memoria_nao_armazenada, n_final, qtd;
    memoria_nao_armazenada = 0;

    clock_t tempo[2]; //variável para armazenar tempo de insercao
    clock_t tempoaloca[2];//variavel para armazenar tempo de alteração
    clock_t tempoimprime[2];//variavel para armazenar tempo de impressao
    clock_t tempobusca[2];//variavel para armazenar tempo de busca
   

    do{
        escolha = menu();
        switch (escolha)
        {
        case 1:
            printf("Informe a quantidade total de blocos na memoria: ");
            scanf("%d",&q_bloco);
            do{
              printf("Digite 1 para bloco livre ou digite 0 para bloco ocupado: \n");
              scanf("%d",&flag);
              if(flag == 1){
                status_bloco = 'L';
              }
              else{
                status_bloco = 'O';
              }
            }while(flag > 1  flag < 0);
            do{
                do{
                    printf("Endereco final do bloco : ");
                    scanf("%d",&n_final);
                    if(n_final < memoria_nao_armazenada){
                        printf("Endereco final nao valido.\n");
                    }
                }while(n_final < memoria_nao_armazenada  n_final > q_bloco);
                tempo[0] = clock();
                insereArv23(&Pai,&Raiz, cria_info(memoria_nao_armazenada, n_final, status_bloco), &Sobe);
                tempo[1] = clock();
                printf("\nTempo de insercao: %f\n\n", (double)(tempo[1] - tempo[0]) / CLOCKS_PER_SEC);
                if(status_bloco == 'L'){
                    status_bloco = 'O';
                }else{
                    status_bloco = 'L';
                }
                memoria_nao_armazenada = n_final + 1;   
            }while(memoria_nao_armazenada < q_bloco);  

            tempoimprime[0] = clock();
            imprimeArvore23(Raiz);
            tempoimprime[1] = clock();
            printf("\nTempo de impressao: %f\n\n", (double)(tempoimprime[1] - tempoimprime[0]) / CLOCKS_PER_SEC);
            break;

case 2:
            printf("Quantidade de blocos que deseja alocar: ");
            scanf("%d",&qtd);
            Pai = NULL;
            res = NULL;
            Sobe = NULL;
            existe_NO(Raiz, qtd, &res);
            if(res != NULL){
                printf("%c - %d, %d\n", res->status, res->inicio, res->fim);
                tempoaloca[0] = clock();
                res = add_new(&Pai,&Raiz, res, qtd);
                insereArv23(&Pai,&Raiz,res,&Sobe);
                tempoaloca[1] = clock();
                printf("Alocado!\n");
                printf("\nTempo de alocacao: %f\n\n", (double)(tempoaloca[1] - tempoaloca[0]) / CLOCKS_PER_SEC);
            }
            else{
                printf("Nao tem espaco!\n\n");
            }
            tempoimprime[0] = clock();
            imprimeArvore23(Raiz);
            tempoimprime[1] = clock();
            printf("\nTempo de impressao: %f\n\n", (double)(tempoimprime[1] - tempoimprime[0]) / CLOCKS_PER_SEC);
            break;
        case(3):
            printf("Digite um endereco para buscar:");
            scanf("%d", &qtd);
            tempobusca[0] = clock();
            int num = buscaEndereco(Raiz, qtd);
            tempobusca[1] = clock();
            if(num != 0){
              printf("Bloco de memoria existe!\n");
            }
            else{
              printf("Bloco de memoria nao encontrado!\n");
            }
            printf("\nTempo de busca: %f\n\n", (double)(tempobusca[1] - tempobusca[0]) / CLOCKS_PER_SEC);

            break;
        case(4):
            printf("\n\n\t\tERROR 404\n\n");
            break;
        default:
            if(escolha < 0  escolha > 3){
                printf("Opcao nao encontrada.\n\n");
            }
            break;

        }

    }while(escolha != 0);

    return 0;

}

int menu(){
    int escolha;
    printf("\nMenu\n");
    printf("1 - Alocar Memoria\n2 - Alocar Espaco\n3 - Buscar Elemento\n4 - Remover\n0 - Sair.\n");
    printf("Informe aqui: ");
    scanf("%d", &escolha);

    return escolha;
}

//Retorna uma strutura do tipo info
struct info *cria_info(int infoInicio, int infoFim, char status){
    struct info *info;
    info = NULL;
    info = (struct info*)malloc(sizeof(struct info));
    info->inicio = infoInicio;
    info->fim = infoFim;
    info->status = status;

    return info;
}

//Retorna uma estrutura do tipo arv23 com a inserção de uma informação
struct arv23 *criaNo(struct info *Info, struct arv23 *FEsq, struct arv23 *FCen){
  struct arv23 *No;
  No = NULL;
  No = (struct arv23 *) malloc(sizeof(struct arv23));

  (*No).Info1 = NULL;
  (*No).Info2 = NULL;
  (*No).Info1 = Info;
  (*No).NInfos = 1;
  (*No).esq = NULL;
  (*No).esq = (struct arv23 *) malloc(sizeof(struct arv23));
  (*No).esq = FEsq;
  (*No).cen = NULL;
  (*No).cen = (struct arv23 *) malloc(sizeof(struct arv23));
  (*No).cen = FCen;
  (*No).dir = NULL;
  
  return No;  
}

//Verifica se a estrutura passada por parametro é uma folha ou não (1 == É folha; 0 == Não é folha).
int ehFolha(struct arv23 *Raiz){
  int folha = 0;
  if((*Raiz).esq == NULL && (*Raiz).cen == NULL && (*Raiz).dir == NULL)
    folha =1;
  
  return folha;  
}

//Realiza a adição da informação a um No retornando a estrutura com a nova informação adicionada.
struct arv23 *adicionaNo(struct arv23 *No, struct info *Info, struct arv23 *Filho){

  if (Info->inicio > (*No).Info1->fim){
      (*No).Info2 = Info;
      (*No).dir = Filho;
    }else{
      (*No).Info2 = (*No).Info1;
      (*No).dir = (*No).cen;
      (*No).Info1 = Info;
      (*No).cen = Filho;
    }
    (*No).NInfos = 2;
  
  return No;  
}

//Realiza a operação de quebra de no não tendo nada como retorno, as variaveis utilizadas futuramente (No, Sobe) são ponteiros de ponteiros.
void quebraNo(struct arv23 **No, struct info *Info, struct arv23 *FilhoMaior, struct info **Sobe, struct arv23 **Novo)
{
  if(Info->fim < (*No)->Info1->inicio)
  {
    *Sobe = (*No)->Info1;
    *Novo = criaNo((*No)->Info2, (*No)->cen,(*No)->dir);
    (*No)->Info1 = Info;
    (*No)->cen = FilhoMaior;
    (*No)->dir = NULL;
    (

*No)->NInfos = 1;
  }
  else if (Info->fim < (*No)->Info2->inicio)
      {
        *Sobe = Info;
        *Novo = criaNo((*No)->Info2, FilhoMaior,(*No)->dir);
        (*No)->cen = FilhoMaior;
        (*No)->dir = NULL;
        (*No)->NInfos = 1;
      }
      else
      {
          *Sobe = ((*No)->Info2); 
          *Novo = criaNo(Info,(*No)->dir,FilhoMaior);
          (*No)->dir = NULL;
          (*No)->NInfos = 1;
        
      }
}

//Realiza a inserção de uma nova informação na arvore, retornando a arvore com o valor inserido.
struct arv23 *insereArv23(struct arv23 **Pai,struct arv23 **Raiz, struct info *Info, struct info **Sobe){ 
  struct arv23 *No;
  No = NULL;

    if (*Raiz == NULL){
      *Raiz = criaNo(Info,NULL,NULL);     
    }
    else{
        
      if(ehFolha(*Raiz)){
        if((**Raiz).NInfos == 1){
          *Raiz = adicionaNo(*Raiz, Info,NULL);
        }
        else {
          quebraNo(Raiz, Info, NULL,Sobe, &No);
          if(*Pai == NULL){
            struct arv23 *Novo;
            Novo = criaNo(*Sobe,*Raiz,No);
            *Raiz = Novo;
            No = NULL;
          }
        }
      }
      else{
        if(Info->inicio < (**Raiz).Info1->inicio){
          No = insereArv23(Raiz,&((*Raiz)->esq), Info, Sobe);
        }
        else{
          if((**Raiz).NInfos == 1){
            if(Info->inicio > (**Raiz).Info1->fim)
              No = insereArv23(Raiz,&((*Raiz)->cen), Info, Sobe);
          }
          else{
            if(Info->inicio > (**Raiz).Info2->fim){ 
              No = insereArv23(Raiz,&((*Raiz)->dir), Info, Sobe);
            }else if(Info->fim < (**Raiz).Info2->inicio){
              No = insereArv23(Raiz,&((*Raiz)->cen), Info, Sobe);
            }
          }
        }

        if(No != NULL){  
          if((**Raiz).NInfos == 1){
              *Raiz = adicionaNo(*Raiz,*Sobe, No);
              No = NULL;
            }  
          else{ 
            struct info *NovoSobe;
            NovoSobe = NULL;
            struct arv23 *NovoNo;
            quebraNo(Raiz,*Sobe, No, &NovoSobe, &NovoNo);
            *Sobe = NovoSobe;
            if(*Pai == NULL){ 
              struct arv23 *Novo;
              Novo = criaNo(NovoSobe,*Raiz,NovoNo);
              *Raiz = Novo;
              No = NULL;
            }
            else No = NovoNo;
          }
        
        }      
      }
    }
 return No;  
}      

void imprimeArvore23(struct arv23 *Raiz){
    if (Raiz != NULL){
      printf("(");
      imprimeArvore23(Raiz->esq);
      printf(")");
      printf(" Esse bloco eh %c ",Raiz->Info1->status);
      printf(" [%d",Raiz->Info1->inicio);
      printf(",%d] ",Raiz->Info1->fim);
      printf("(");
      imprimeArvore23(Raiz->cen);
      printf(")");
      if(Raiz->NInfos == 2){
        printf(" Esse bloco eh %c ",Raiz->Info2->status);
        printf(" [%d",Raiz->Info2->inicio);
        printf(",%d] ",Raiz->Info2->fim);
        printf("(");
        imprimeArvore23(Raiz->dir);
        printf(")");
      }
    }
    else{
      printf(" NULL ");
    }
}


//Buscar bloco livre
void existe_NO(struct arv23 *Raiz, int qtd, struct info **res){
  int espacos;
  int flag = 1;
  if(Raiz != NULL){
    espacos = Raiz->Info1->fim - Raiz->Info1->inicio;

    if(espacos+1 >= qtd && Raiz->Info1->status == 'L'){
      *res = Raiz->Info1;
      flag = 0;
    }
    else if(Raiz->NInfos == 2){
      espacos = Raiz->Info2->fim - Raiz->Info2->inicio;
      if(espacos+1 >= qtd && Raiz->Info2->status == 'L'){
        *res = Raiz->Info2;
        flag = 0;
      }
    }
    if(flag == 1){
      existe_NO(Raiz->esq, qtd, res);
      existe_NO(Raiz->cen, qtd, res);
      existe_NO(Raiz->dir, qtd, res);
    }
  }
}

//Re-arranja bloco livre que de modo que seja possivel inserir um novo bloco
struct info *add_new(struct arv23 **Pai,struct arv23 **Raiz, struct info *Info, int qtd){
  struct info *aux, *sobe;
  int flag = 1;
  if(*Raiz != NULL){
    if((*Raiz)->Info1->inicio == Info->inicio){
      //encontra o No
      if(qtd == (((*Raiz)->Info1->fim - (*Raiz)->Info1->inicio))+1){
        (*Raiz)->Info1->status = 'O';
        flag = 0;
      }else{
        aux = cria_info((*Raiz)->Info1->inicio, (*Raiz)->Info1->inicio+(qtd-1), 'O');
        (*Raiz)->Info1->inicio += qtd;
        flag = 0;
        if((*Raiz)->NInfos == 2){
          sobe = (*Raiz)->Info1;
          //insereArv23(Pai, Raiz, aux, &sobe);
          flag = 0;
        }else{
          sobe = NULL;
          //insereArv23(Pai, Raiz, aux, &sobe);
          flag = 0;
        }
      }
    }
    else if((*Raiz)->NInfos == 2){
      if((*Raiz)->Info2->inicio == Info->inicio){
        if(qtd == ((*Raiz)->Info2->fim - (*Raiz)->Info2->inicio) + 1){
          (*Raiz)->Info2->status = 'O';
        }else{
          aux = cria_info((*Raiz)->Info2->fim - (qtd-1),(*Raiz)->Info2->fim, 'O');
          (*Raiz)->Info2->fim -= qtd;
          //insereArv23(Pai, Raiz, aux, &(*Raiz)->Info2);
          flag = 0;
          aux = NULL;   
        }
      
      }
    }
    if(flag == 1){
        if((*Raiz)->Info1->inicio > Info->inicio){
          aux = add_new(Raiz, &(*Raiz)->esq,Info, qtd);
        }
        else if((*Raiz)->NInfos==1){
          aux = add_new(Raiz, &(*Raiz)->cen,Info, qtd);
        }
        else if((*Raiz)->Info2->inicio > Info->inicio){
          aux = add_new(Raiz, &(*Raiz)->cen,Info, qtd);
        }
        else if((*Raiz)->Info2->inicio < Info->inicio){
          aux = add_new(Raiz, &(*Raiz)->dir,Info, qtd);
        }
    }
  }
  return aux;
}

int buscaEndereco(struct arv23* raiz, int endereco){
  int num = 0;
  if (raiz != NULL) {
    if (endereco >= raiz->Info1->inicio && endereco <= raiz->Info1->fim) {
        num = raiz;
    } 
    else if (raiz->NInfos == 2 && endereco >= raiz->Info2->inicio && endereco <= raiz->Info2->fim) {
        num = raiz;
    } 
    else if (endereco < raiz->Info1->inicio) {
        num = buscaEndereco(raiz->esq, endereco);
    } 
    else if (raiz->NInfos == 1  endereco < raiz->Info2->inicio) {
        num = buscaEndereco(raiz->cen, endereco);
    } 
    else {
        num = buscaEndereco(raiz->dir, endereco);
    }
  }
  return num;
}