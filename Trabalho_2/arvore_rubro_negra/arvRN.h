typedef struct artista Artista; //nome  do  artista,  o  estilo musical, o número de álbuns, e os Álbuns
typedef struct album Album;//título,  o  ano  de  lançamento,  a  quantidade  de  músicas  e  as  Músicas  (endereço  lista  ordenada).
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
Artista* remove_NO_artista(struct Artista** raiz, char nome_artista[])







// -----------------REFERENTE A MUSICA-----------------
void inicializarLista(ListaDupla *lista);
void adicionarMusica(ListaDupla *lista, Musica novaMusica);
void imprimirLista(ListaDupla lista);
void liberarLista(ListaDupla *lista);
