typedef struct serie{
      int codigo;
      char titulo[50];
      int numTemp;
      Temporada *arvTemp;
      Serie *esq, *dir;
}Serie;
//código, título, número de temporadas

typedef struct temporada{
      int numTem;
      char titulo[50];
      int quantEp;
      char ano;
      Part participantes;
      Temporada *esq, *dir;
}Temporada;
//número da temporada, título, quantidade de episódios, ano, endereço para ula lista simples  de participantes.

typedef struct participantes
{
      char nome[50];
      Part *prox; 
}Part;

Serie *criaNoSerie(int codigo, char titulo[], int numTemp);
Serie *busca_Serie(Serie **serie, int codigo);
Serie *endereco(Serie *raiz);
void insere_Serie(Serie **raiz, Serie *serie);
void imprime_Serie(Serie *raiz);
int imprime_Serie_Por_Codigo(Serie *raiz, int codigo);
void imprime_Todos_Personagens(Serie *raiz, int codigo);
void imprime_Personagens_Determinada_Temp(Serie *raiz, int codigo);
void remover_serie(Serie **raiz, int codigo);
void busca_folha(Serie **filho_1, Serie *filho_2);

Temporada criaNoTemp(int numTemp, char titulo[], int quantidade_Ep, char ano, Part *list);