typedef struct serie{
      int codigo;
      char titulo[50];
      int numTemp;
      Temporada *arvTemp;
      Serie *esq, *dir, *alt;
}Serie;
//código, título, número de temporadas

typedef struct temporada{
      int codigo;
      int numTem;
      char titulo[50];
      int quantEp;
      char ano;
      Part participantes;
      Temporada *esq, *dir, *alt;
}Temporada;
//número da temporada, título, quantidade de episódios, ano, endereço para ula lista simples  de participantes.

typedef struct participantes
{
      char nome[50];
      Part *prox; 
}Part;

Serie *criaNoSerie(int codigo, char titulo[], int numTemp);
Serie *busca_Serie_Codigo(Serie **serie, int codigo);
void *busca_Serie_remove(Serie **serie, int codigo, int codigo_temp);
void busca_folha_Serie(Serie **ultimo, Serie *no_Filho);
void remover_serie(Serie **raiz, int codigo);
Serie *endereco(Serie *raiz);
void insere_Serie(Serie **raiz, Serie *serie);
void imprime_todas_Series(Serie *raiz);
int calcula_Altura(Serie *no);
void atualizar_Altura(Serie *no);
int fator_Balanciamento(Serie *no);
void rotacao_Direita(Serie **no);
void rotacao_Esquerda(Serie **no);

void imprime(Serie *raiz);

void imprime_Serie_Por_Codigo(Serie *raiz, int codigo);
void imprime_Todos_Personagens(Serie *raiz, int codigo);
void imprime_Personagens_Determinada_Temp(Serie *raiz, int codigo);

void busca_folha_temp(Temporada **filho_1, Temporada *filho_2);
Temporada criaNoTemp(int cod,int numTemp, char titulo[], int quantidade_Ep, char ano, Part *list);
void insere_Temp(Temporada **raiz, Temporada *temp);
void remover_temporada(Temporada **raiz, int codigo);
int calcula_Altura_temp(Temporada *no);
void atualizar_Altura_temp(Temporada *no);
int fator_Balanciamento_temp(Temporada *no);
void rotacao_Direita_temp(Temporada **no);
void rotacao_Esquerda_temp(Temporada **no);