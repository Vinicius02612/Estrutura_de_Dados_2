typedef struct artista Artista;
typedef struct album Album;
typedef struct musica Musica;

typedef struct arv23_artista Arv23_artista;
typedef struct arv23_album Arv23_album;
typedef struct listaDupla ListaDupla;

// -----------------REFERENTE A ARTISTA-----------------
Artista *lerDadosArtista();
Arv23_artista *cria_NO_Artista(Artista *info, Arv23_artista *esq, Arv23_artista *dir, Arv23_artista *centro);
Arv23_artista *quebra_no(Arv23_artista **no, Artista *info, Artista *sobe, Arv23_artista *filho);
Arv23_artista *eh_folha_artista(Arv23_artista *raiz);
 void adiciona_No_artista(Arv23_artista **raiz, Artista *info, Arv23_artista *filho_dir);
Arv23_artista *insere_no_artista(Arv23_artista **raiz, Artista *info, Arv23_artista *pai, Artista *sobe);
Artista *buscarArtista(Arv23_artista *raiz, char nome_artista[]);
void RemoveMaiorInfoEsq(Arv23_artista **RaizArv23, Arv23_artista **PaiMaior, Arv23_artista **MaiorInfoRemove, int LocalInfo, char *Situacao);
void RemoveArtista23(Arv23_artista **RaizArv23, Arv23_artista **Pai, char *NomeArtista, int LinhaArtista, char *Situacao);
void RedistribuiArv23Artista(Arv23_artista **RaizArv23, Arv23_artista **Pai);
void imprimirArtista(Arv23_artista *raiz, int nivel);

void imprimeDadoArtista(Artista *dado);
// -----------------REFERENTE A ALBUM-----------------

// -----------------REFERENTE A MUSICA-----------------
