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


ArvoreSerie *lerDadosSerie();
ArvoreSerie *lerDadosSerie2(int codigo, char titulo[]);
ArvoreTemporada *lerDadoTemporada();
ArvoreTemporada *lerDadoTemporada2(int codigo, int numtemporada, int quantEp, char titulo[], char ano[]);

Participantes *criaListaParticipante();
Participantes *insereParticipante(Participantes *lista, Participantes *dadoParticipante);
void imprimeParticipante(Participantes *lista);
void buscaParticipantes(Participantes *lista,char nomePersonagem[]);
void imprimirPersonagensDeUmaTemporada(ArvoreSerie *raizS, int codigo, int NumeroTemporada );
void imprimirNomeDeUmArtista(ArvoreSerie *raizS, char nomePersonagem[]);

void inserirSeries(ArvoreSerie **raiz, ArvoreSerie *Dado);
void imprimeSeries(ArvoreSerie s);
void imprimeArvoreSeries(ArvoreSerie *raiz);
void imprimeSeriesPeloCodigo(ArvoreSerie *raiz, int codigo);
ArvoreSerie *BuscarSeries( ArvoreSerie *raizS, int codigo);

ArvoreTemporada *insereTemporada(ArvoreTemporada **raiz, ArvoreTemporada *Dado);
void imprimeArvoreTemporada(ArvoreTemporada *raiz);

void imprimeTemporadaDeUmaSerie(ArvoreSerie *raizS, int codigo);
void imprimeTemporada(ArvoreTemporada temporada);

void imprimirTemporada(ArvoreSerie *raiz);
void imprimirTemporadaDeUmaSerie(ArvoreSerie *raiz, int codigo, int numTemporada);

void embaralharOsDados(int *dados, int n);
void calcularTempo(double inicio, double fim );
void realizaTesteDeInsercaoDaSerie(ArvoreSerie *raizS, int quant);
void realizaTesteDeBusca(ArvoreTemporada **raizT, int quant);