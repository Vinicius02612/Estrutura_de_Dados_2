/* 
(a) Séries: código, título, número de temporadas, um endereço para uma árvore binária de busca contendo
informações de cada temporada. A árvore deve ser organizada pelo código da série.

********
(a) Imprimir em ordem pelo código da série: o título, o número de temporadas.
(b) Imprimir os dados de todas as temporadas de uma série, cujo o usuário informe o código da série.
(c) Imprimir todos os personagens de uma determinada temporada de uma dada série, cujo o usuário
informe o código da série e o número da temporada.
(d) Imprimir o nome de todos os artistas que interpretaram um determinado personagem em todas as
temporadas de uma dada série, cujo o usuário informe o código da série. 
*/

typedef struct participantes Participantes;

typedef struct dadoSerie DadoSeries;
typedef struct arvoreSerie ArvoreSerie;

typedef struct dadoTemporada DadoTemporada;
typedef struct arvoreTemporada ArvoreTemporada;


ArvoreSerie *criarArvoreSerie();
ArvoreTemporada *criaAvoreTemporada();

DadoSeries lerDadosSerie();

Participantes *criaListaParticipante();
Participantes *insereParticipante(Participantes *lista, int id, char nomeDoArtista[], char nomeDoPersongem[], char descricao[]);
void imprimeParticipante(Participantes *lista);
Participantes *buscaParticipantes(Participantes *lista, int id);

void inserirSeries(ArvoreSerie **raiz, int codigo, int numeroTemporada, char titulo[]);

void imprimeSeries(DadoSeries s);
void imprimeArvoreSeries(ArvoreSerie *raiz);
void imprimeSeriesPeloCodigo(ArvoreSerie *raiz, int codigo);
ArvoreSerie *BuscarSeries( ArvoreSerie *raizS, int codigo);

void insereTemporada(ArvoreTemporada **raiz, int numTem, char tituloTemp[], int quantEpisodio, char ano[]);
void imprimeArvoreTemporada(ArvoreTemporada *raiz);

ArvoreSerie *insereTemporadaNaSerie(ArvoreSerie *raizS, ArvoreTemporada *raizT, int codigo);

void imprimeTemporada(DadoTemporada temporada);

void imprimirTemporada(ArvoreSerie *raiz);
void imprimirTemporadaDeUmaSerie(ArvoreSerie *raiz, int codigo, int numTemporada);
