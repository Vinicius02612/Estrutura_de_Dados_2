typedef struct endereco Enderecos;

typedef struct bloco45 Bloco45;

Enderecos *criaEnderecos(char status, int inicio, int fim);
Bloco45 *criaBloco( Enderecos end, Bloco45 *esq, Bloco45 *esqCentro, Bloco45  *centro, Bloco45 *centroDir, Bloco45 *dir);
int eFolha(Bloco45 *raiz);
void adiconaBloco(Bloco45 **raiz, Enderecos info, Bloco45 *maiorNo);