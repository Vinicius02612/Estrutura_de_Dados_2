#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "arv23.h"
// ... (definições de estruturas e funções)

int main() {
    Arv23_artista *raiz = NULL;
    Artista *sobe, *info;
    sobe = NULL; info = NULL;
    int num_elementos = 60;  // Número total de elementos na árvorea
    int num_buscas = 30;    // Número de buscas a serem realizadas

    // Inserção
    clock_t inicio_insercao = clock();

    for (int i = 0; i < num_elementos; i++) {
        info = lerDadosArtista();
        Artista *novo_artista = cria_NO_Artista(info,NULL,NULL,NULL);  
        insere_no_artista(&raiz, novo_artista, NULL, &sobe);
    }

    clock_t fim_insercao = clock();
    double tempo_insercao = ((double)(fim_insercao - inicio_insercao)) / CLOCKS_PER_SEC * 1000.0;  // Convertendo para milissegundos

    printf("Tempo de insercao: %.2f ms\n", tempo_insercao);

    // Busca
    clock_t inicio_busca = clock();

    for (int i = 0; i < num_buscas; i++) {
        // Suponha que você tenha uma função para gerar uma palavra-chave aleatória ou use dados existentes na árvore
        char palavra_chave[50];
        // ... gerar palavra-chave ou obter de dados existentes

        Artista *resultado = buscarArtista(raiz, palavra_chave);
        // Aqui você pode fazer algo com o resultado, como imprimir ou processar
    }

    clock_t fim_busca = clock();
    double tempo_busca = ((double)(fim_busca - inicio_busca)) / CLOCKS_PER_SEC * 1000.0;  // Convertendo para milissegundos

    printf("Tempo de busca: %.2f ms\n", tempo_busca);

    // ... (liberar memória, etc.)

    return 0;
}