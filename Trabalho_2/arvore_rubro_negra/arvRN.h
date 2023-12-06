typedef struct artista Artista; //nome  do  artista,  o  estilo musical, o número de álbuns, e os Álbuns
typedef struct album Album;//título,  o  ano  de  lançamento,  a  quantidade  de  músicas  e  as  Músicas  (endereço  lista  ordenada).
typedef struct musica Musica;//título, e a quantidade de minutos.


// -----------------REFERENTE A ARTISTA-----------------
int cor_artista(Artista *raiz);
void cria_No_Artista(Artista **raiz, char nome_artista[], char *estilo_musical, int num_albuns);
void rotacao_esquerda_artista(Artista **raiz);
void rotacao_direita__artista(Artista **raiz);
void troca_Cor_artista(Artista *raiz);
Artista insere_NO(Artista **raiz, char nome_artista[], char estilo_musical[], int num_albuns);