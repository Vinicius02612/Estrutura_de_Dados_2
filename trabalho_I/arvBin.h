typedef struct serie Serie;

typedef struct temporada Temporada;

typedef struct participantes Participantes;

Serie *criaNoSerie();
void insere_Serie(Serie **raiz, int codigo, char titulo[], int numTemp);

Temporada *criarTemporada();
void insere_Temporada(Temporada **raiz,int numTemporada, char titulo[], int quantEp, char an);


Serie *busca_Serie(Serie **serie, int codigo);
Serie *endereco(Serie *raiz);

Participantes *criar_Participantes();
Participantes *inserir_Participante(Participantes *lista,char nomeDoArtista,char nomeParticipante,char descricao );


void inserirTemporadaAserie(Serie *serie, Temporada *temporada);
void listarParticipante(Participantes *lista);
void listarTemporada(Temporada *raiz);

void imprime_Serie(Serie *raiz);
int imprime_Serie_Por_Codigo(Serie *raiz, int codigo);
void imprime_Todos_Personagens(Serie *raiz, int codigo);
void imprime_Personagens_Determinada_Temp(Serie *raiz, int codigo);
void remover_serie(Serie **raiz, int codigo);
void busca_folha(Serie **filho_1, Serie *filho_2);

