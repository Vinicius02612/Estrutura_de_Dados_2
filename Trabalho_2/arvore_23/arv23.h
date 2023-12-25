typedef struct artista Artista;
typedef struct album Album;
typedef struct musica Musica;

typedef struct arv23_artista Arv23_artista;
typedef struct Arv23_album Arv23_album;
typedef struct listaDupla ListaDupla;

// -----------------REFERENTE A ARTISTA-----------------

Arv23_artista *cria_NO_Artista(Arv23_artista *no, Arv23_artista *esq, Arv23_artista *dir, Arv23_artista *centro);
Arv23_artista *quebra_no(Arv23_artista **no, char nome_artista[], char sobe[], Arv23_artista *filho);
Arv23_artista *eh_folha_artista(Arv23_artista *raiz);
Arv23_artista *adiciona_No_artista(Arv23_artista *raiz, char nome_artista[], Arv23_artista *filho_dir);

void RemoveMaiorInfoEsq(Arv23_artista **RaizArv23, Arv23_artista **PaiMaior, Arv23_artista **MaiorInfoRemove, int LocalInfo, char *Situacao);
void RemoveArtista23(Arv23_artista **RaizArv23, Arv23_artista **Pai, char *NomeArtista, int LinhaArtista, char *Situacao);
void RedistribuiArv23Artista(Arv23_artista **RaizArv23, Arv23_artista **Pai);
