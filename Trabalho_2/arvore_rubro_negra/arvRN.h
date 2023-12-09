typedef struct artista Artista; //nome  do  artista,  o  estilo musical, o número de álbuns, e os Álbuns
 struct  Album;//título,  o  ano  de  lançamento,  a  quantidade  de  músicas  e  as  Músicas  (endereço  lista  ordenada).
typedef struct musica Musica;//título, e a quantidade de minutos.


// -----------------REFERENTE A ARTISTA-----------------
int cor_artista(Artista *raiz);
int cria_No_Artista(Artista **raiz, char nome_artista[], char *estilo_musical, int num_albuns);
Artista* rotacao_esquerda_artista(Artista **raiz);
Artista* rotacao_direita_artista(Artista **raiz);
void troca_Cor_artista(Artista *raiz);
int insere_NO_artista(Artista **raiz, char nome_artista[], char estilo_musical[], int num_albuns);
int insere_RB(Artista **raiz, char nome_artista[], char estilo_musical[], int num_albuns);

Artista* balanceia_artista(Artista *raiz);
Artista* move_esq_red(Artista *raiz);
Artista* move_dir_red(Artista *raiz);
Artista* remove_menor(Artista *raiz);
Artista* procuraMenor(Artista *atual);
Artista* buscarFolha_artista(Artista *ultimo);
Artista* remove_NO_artista(Artista** raiz, char nome_artista[]);

// -----------------REFERENTE A ALBUM-----------------

Album *cria_No_Album(Album **raiz, char titulo[], int anoLancamento, int qtdMusicas);
Album *rotacao_esquerda_album(Album **raiz);
Album *rotacao_direita_album(Album **raiz);
void troca_Cor_album(Album *raiz);
Album *balanceia_album(Album *raiz) int insere_NO_album(Album **raiz, char titulo[], int anoLancamento, int qtdMusicas);
int insere_RB_album(Album **raiz, char titulo[], int anoLancamento, int qtdMusicas);
Album *move_esq_red_album(Album *raiz);
Album *move_dir_red_album(Album *raiz);
Album *remove_menor_album(Album *raiz);
Album *procuraMenor_album(Album *atual);
Album *buscarFolha_album(Album *ultimo);
Album *remove_NO_album(Album **raiz, char titulo[]);

// -----------------REFERENTE A MUSICA-----------------
void inicializarLista(ListaDupla *lista);
void adicionarMusica(ListaDupla *lista, Musica novaMusica);
void imprimirLista(ListaDupla lista);
void liberarLista(ListaDupla *lista);
