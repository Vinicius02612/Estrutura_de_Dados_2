typedef struct hash Hash;
typedef struct funcionario Funcionario;

Hash *cria_tabela_hash(int tamanho);
int chave_de_divisao(int chave, int tamanho);
int sondagem_linear(int pos, int i, int tamanho);
int insere_func_hash(Hash *hs, Funcionario func);
int busca_hash__func(Hash *hs, int matricula, Funcionario *func);
void libera_hash(Hash *hs);
