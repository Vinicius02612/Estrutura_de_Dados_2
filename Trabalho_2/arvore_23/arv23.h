typedef struct artista Artista;
typedef struct album Album;
typedef struct musica Musica;

typedef struct arv23_artista Arv23_artista;
typedef struct arv23_album Arv23_album;
typedef struct listaDupla ListaDupla;

// -----------------REFERENTE A ARTISTA-----------------
Arv23_artista *inicializaArtista();
Artista *lerDadosArtista();
Arv23_artista *cria_NO_Artista(Artista *info, Arv23_artista *esq, Arv23_artista *dir, Arv23_artista *centro);
Arv23_artista *quebra_no(Arv23_artista **no, Artista *info, Artista **sobe, Arv23_artista *filho);
Arv23_artista *eh_folha_artista(Arv23_artista *raiz);
 void adiciona_No_artista(Arv23_artista **raiz, Artista *info, Arv23_artista *filho_dir);
Arv23_artista *insere_no_artista(Arv23_artista **raiz, Artista *info, Arv23_artista *pai, Artista **sobe);
Artista *buscarArtista(Arv23_artista *raiz, char nome_artista[]);
void RemoveMaiorInfoEsq(Arv23_artista **RaizArv23, Arv23_artista **PaiMaior, Arv23_artista **MaiorInfoRemove, int LocalInfo, char *Situacao);
void RemoveArtista23(Arv23_artista **RaizArv23, Arv23_artista **Pai, char *NomeArtista, int LinhaArtista, char *Situacao);
void RedistribuiArv23Artista(Arv23_artista **RaizArv23, Arv23_artista **Pai);
void imprimirArtista(Arv23_artista *raiz, int nivel);
void imprimeDadoArtista(Artista *dado);

// -----------------REFERENTE A ALBUM-----------------
Arv23_album *inicializAlbum();
Album *lerDadoAlbum();
Arv23_album *cria_NO_Album(Album *info, Arv23_album *esq, Arv23_album *dir, Arv23_album *centro);
Arv23_album *eh_folha_album(Arv23_album *raiz);
Arv23_album *quebra_no_Album(Arv23_album **no, Album *info, Album *sobe, Arv23_album *filho);
void adiciona_No_album(Arv23_album **raiz, Album *info, Arv23_album *filho_dir);
Arv23_album *insere_no_album(Arv23_album **raiz, Album *info, Arv23_album *pai, Album *sobe);
void RemoveMaiorInfoEsqAlbum(Arv23_album** RaizArv23, Arv23_album** PaiMaior, Arv23_album** MaiorInfoRemove, int LocalInfo, char* Situacao);
void RemoveAlbum23(Arv23_album** RaizArv23, Arv23_album** Pai, char* titulo, int LinhaAlbum, char* Situacao);
void RedistribuiArv23Album(Arv23_album** RaizArv23, Arv23_album** Pai);
Album* buscarAlbum(Arv23_album* RaizArv23, char* titulo);
void imprimeDadoAlbum(Album *dado);
void imprimirAlbum(Arv23_album *raiz, int nivel);
Arv23_artista *insereAlbumEmArtista(Artista *artista, Arv23_album *dadoAlbum, char nome_artista[50]);

// -----------------REFERENTE A MUSICA-----------------
ListaDupla *inicializarLista();
Musica *lerDadosMusica();
ListaDupla *adicionarMusica(ListaDupla **lista, Musica *novaMusica);
ListaDupla *removerMusica(ListaDupla **lista, char titulo[]);
Musica *buscarMusica(ListaDupla *lista, char titulo[]);
void imprimirLista(ListaDupla *lista);
void imprimeDadoMusica(Musica *msc);
void liberarLista(ListaDupla* lista);
