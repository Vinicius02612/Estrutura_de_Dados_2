typedef struct artista Artista;
typedef struct dadoArtista DadoArtista;
typedef struct dadoAlbum DadoAlbum;
typedef  struct  album Album;

 //nome  do  artista,  o  estilo musical, o número de álbuns, e os Álbuns
//título,  o  ano  de  lançamento,  a  quantidade  de  músicas  e  as  Músicas  (endereço  lista  ordenada).
typedef struct musica Musica;//título, e a quantidade de minutos.
typedef struct listaDupla  ListaDupla;

// -----------------REFERENTE A ARTISTA-----------------
int cor(Artista *raiz);
Artista *cria_No_Artista();
Artista* rotacao_esquerda_artista(Artista *raiz);
Artista* rotacao_direita_artista(Artista *raiz);
void troca_Cor_artista(Artista *raiz);
DadoArtista *lerInformacaoArtista();
Artista *insere_NO_artista(Artista **raiz, DadoArtista *infoArtista);
int insere_RB(Artista **raiz, DadoArtista *infoAtista);
Artista *  buscaArtista(Artista **raiz, char nome_artista[]);
Artista *adcionaAlbumEmArtista( Artista *artista,char nome_artista[], Album *album);
Artista* balanceia_artista(Artista *raiz);
Artista* move_esq_red(Artista *raiz);
Artista* move_dir_red(Artista *raiz);
Artista* remove_menor(Artista *raiz);
Artista* procuraMenor(Artista *atual);
Artista* remove_NO_artista(Artista **raiz, char nome_artista[]);
int remove_arvRB(Artista **raiz, char nome_artista[]);
void imprimirArtista(Artista *raiz, int nivel);
Artista* buscarFolha_artista(Artista **ultimo);
// -----------------REFERENTE A ALBUM-----------------

Album *cria_No_Album();
DadoAlbum *lerDadosAlbum();
Album *rotacao_esquerda_album(Album *raiz);
Album *rotacao_direita_album(Album *raiz);
void troca_Cor_album(Album *raiz);
Album *balanceia_album(Album *raiz);
Album *insere_NO_album(Album **raiz, DadoAlbum *dado );
int insere_RB_album(Album **raiz,DadoAlbum *dado);
Album *adicionaMusicaAoAlbum( Album *album,char titulo[], ListaDupla *musica);
Album  *buscaAlbum(Album **raiz, char titulo[]);
Album *move_esq_red_album(Album *raiz);
Album *move_dir_red_album(Album *raiz);
Album *remove_menor_album(Album *raiz);
Album *procuraMenor_album(Album *atual);
Album *buscarFolha_album(Album *ultimo);
Album *remove_NO_album(Album **raiz, char titulo[]);
int remove_arvRB_Album(Album **raiz, char titulo[]);
void imprimeAlbum(Album *raiz, int nivel);

// -----------------REFERENTE A MUSICA-----------------
ListaDupla *inicializarLista();
Musica *lerDadosMusica();
ListaDupla *removerMusica(ListaDupla **lista, char titulo[]);
ListaDupla *adicionarMusica(ListaDupla **lista, Musica *novaMusica);
void imprimirLista(ListaDupla *lista);
void liberarLista(ListaDupla *lista);
