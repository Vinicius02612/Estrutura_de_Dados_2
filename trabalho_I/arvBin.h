typedef struct serie Serie;

typedef struct temporada Temporada;

typedef struct participantes Participantes;

Serie *criaNoSerie(int codigo, char titulo[], int numTemp);
Serie *insere_Serie(Serie *raiz, Serie *novaSerie);

Temporada *criarTemporada(int numeroTemp, char titulo[], int quantEp, char ano[] );
Temporada *insere_Temporada(Temporada *raiz, Temporada *novaTempora);


Serie *busca_Serie(Serie **serie, int codigo);
Serie *endereco(Serie *raiz);

Participantes *criar_Participantes(char nomeArtista[], char nomeParticipante, char descricao[]);
Participantes *inserir_Participante(Participantes *lista, Participantes *novoParticipante);


void inserirTemporadaAserie(Serie *serie, Temporada *temporada);
void listarParticipante(Participantes *lista);
void listarTemporada(Temporada *raiz);

void imprime_Serie(Serie *raiz);
int imprime_Serie_Por_Codigo(Serie *raiz, int codigo);
void imprime_Todos_Personagens(Serie *raiz, int codigo);
void imprime_Personagens_Determinada_Temp(Serie *raiz, int codigo);
void remover_serie(Serie **raiz, int codigo);
void busca_folha(Serie **filho_1, Serie *filho_2);

