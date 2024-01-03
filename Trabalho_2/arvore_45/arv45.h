typedef struct info Info;
typedef struct arv45 Arv45;


Info *criaInfo(int inicio, int fim, char status);
Arv45 *criaNo(Info *info, Arv45 *NoEsq, Arv45 *noCentroEsq);
int ehFolha(Arv45 *no);
void adicionaNo(Arv45 **No, Info *info, Arv45 *filho);
Arv45 *quebraNo(Arv45 **raiz, Info *info, Info **sobe, Arv45 *filho);
Arv45 *inserir45(Arv45 **raiz, Arv45 *pai, Info **sobe, int inicio, int fim, char status, int *flag);
void MaiorInfoRemoveEsq(Arv45 **raiz, Arv45 **PaiMaior, Arv45 **MaiorInfoRemove, int LocalInfo, int *ValorRemover);
