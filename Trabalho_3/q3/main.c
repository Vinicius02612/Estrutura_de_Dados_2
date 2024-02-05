#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_DESTINO_1 101
#define TAMANHO_DESTINO_2 150
#define NUM_FUNCIONARIOS 1000

struct Funcionario {
    char matricula[7];
    char nome[50];
    char funcao[50];
    float salario;
};

typedef struct Hash {
    int qtd, tamanho;
    struct Funcionario **vetor_destino;
} Hash;

// Função de hashing (a)
int funcao_hash_a(char *matricula, int tamanho) {
    int rotacao = ((matricula[0] - '0') * 10 + (matricula[1] - '0')) << 2;
    int resultado = (rotacao % 1000) / 10;
    int restoDivisao = resultado % tamanho;
    int primeiroDigito = matricula[0] - '0';
    int indiceFinal = (restoDivisao + primeiroDigito) % tamanho;
    return indiceFinal;
}

// Tratamento de colisões para a função de hashing (a)
int trata_colisao_a(int hash, char *digito) {
    int colidiu = hash + atoi(digito);
    return colidiu;
}

// Função de hashing (b)
int funcao_hash_b(char *matricula, int tamanho) {
    int shift1 = (matricula[0] - '0') << 5 | (matricula[2] - '0') << 2 | (matricula[5] - '0');
    int shift2 = (matricula[1] - '0') << 5 | (matricula[3] - '0') << 2 | (matricula[4] - '0');
    int resultado = (shift1 + shift2) % tamanho;
    int indiceFinal = (resultado + 7) % tamanho;
    return indiceFinal;
}

// Tratamento de colisões para a função de hashing (b)
int trata_colisao_b(int hash) {
    return (hash + 7) % TAMANHO_DESTINO_1;
}

// Criação da tabela hash
Hash *cria_tabela_hash(int tamanho) {
    Hash *hs = (Hash *)malloc(sizeof(Hash));

    if (hs != NULL) {
        int i;
        hs->tamanho = tamanho;
        hs->vetor_destino = (struct Funcionario **)malloc(tamanho * sizeof(struct Funcionario *));

        if (hs->vetor_destino != NULL) {
            hs->qtd = 0;
            for (i = 0; i < hs->tamanho; i++) {
                hs->vetor_destino[i] = NULL;
            }
        }
    }
    return hs;
}

// Função para inserir funcionário na tabela hash
void insere_funcionario(Hash *hs, struct Funcionario func, int (*funcao_hash)(char *, int), int (*trata_colisao)(int, char *)) {
    int posicao = funcao_hash(func.matricula, hs->tamanho);
    int colisoes = 0;

    while (hs->vetor_destino[posicao] != NULL) {
        colisoes++;
        posicao = trata_colisao(posicao, func.matricula);
    }

    hs->vetor_destino[posicao] = (struct Funcionario *)malloc(sizeof(struct Funcionario));
    *hs->vetor_destino[posicao] = func;
    hs->qtd++;

    printf("Funcionário inserido na posição %d com %d colisões.\n", posicao, colisoes);
}

// Função principal
int main() {
    Hash *hs_a_1 = cria_tabela_hash(TAMANHO_DESTINO_1);
    Hash *hs_a_2 = cria_tabela_hash(TAMANHO_DESTINO_2);
    Hash *hs_b_1 = cria_tabela_hash(TAMANHO_DESTINO_1);
    Hash *hs_b_2 = cria_tabela_hash(TAMANHO_DESTINO_2);

    // Inicialização dos funcionários (exemplo)
    struct Funcionario funcionarios[NUM_FUNCIONARIOS];
    for (int i = 0; i < NUM_FUNCIONARIOS; i++) {
        sprintf(funcionarios[i].matricula, "%06d", i + 1);
        sprintf(funcionarios[i].nome, "Funcionario%d", i + 1);
        sprintf(funcionarios[i].funcao, "Funcao%d", i + 1);
        funcionarios[i].salario = 10000.0;
    }

    // Inserção na tabela hash usando função de hashing (a) e vetor de destino de tamanho 101
    printf("\nInserindo com a função de hashing (a) e vetor destino de tamanho 101:\n");
    for (int i = 0; i < NUM_FUNCIONARIOS; i++) {
        insere_funcionario(hs_a_1, funcionarios[i], funcao_hash_a, trata_colisao_a);
    }

    // Inserção na tabela hash usando função de hashing (a) e vetor de destino de tamanho 150
    printf("\nInserindo com a função de hashing (a) e vetor destino de tamanho 150:\n");
    for (int i = 0; i < NUM_FUNCIONARIOS; i++) {
        insere_funcionario(hs_a_2, funcionarios[i], funcao_hash_a, trata_colisao_a);
    }

    // Inserção na tabela hash usando função de hashing (b) e vetor de destino de tamanho 101
    printf("\nInserindo com a função de hashing (b) e vetor destino de tamanho 101:\n");
    for (int i = 0; i < NUM_FUNCIONARIOS; i++) {
        insere_funcionario(hs_b_1, funcionarios[i], funcao_hash_b, trata_colisao_b);
    }

    // Inserção na tabela hash usando função de hashing (b) e vetor de destino de tamanho 150
    printf("\nInserindo com a função de hashing (b) e vetor destino de tamanho 150:\n");
    for (int i = 0; i < NUM_FUNCIONARIOS; i++) {
        insere_funcionario(hs_b_2, funcionarios[i], funcao_hash_b, trata_colisao_b);
    }

    return 0;
}