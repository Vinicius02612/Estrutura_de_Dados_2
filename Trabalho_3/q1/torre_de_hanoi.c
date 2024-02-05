#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define NVERTICES 81
#define LENVERTICES 5

// Função para inicializar a matriz de adjacência
void inicializarGrafo(int grafo[NVERTICES][NVERTICES]) {
    for (int i = 0; i < NVERTICES; i++) {
        for (int j = 0; j < NVERTICES; j++) {
            grafo[i][j] = 0; // Inicializa todas as arestas como 0 (sem conexão)
        }
    }
}

// Função para adicionar aresta ao grafo
void adicionarAresta(int grafo[NVERTICES][NVERTICES], int origem, int destino) {
    grafo[origem][destino] = 1; // Adiciona uma aresta de origem para destino com peso 1
}

// Função para exibir a matriz de adjacência (apenas para visualização)
void exibirMatrizAdjacencia(int grafo[NVERTICES][NVERTICES]) {
    for (int i = 0; i < NVERTICES; i++) {
        for (int j = 0; j < NVERTICES; j++) {
            printf("%d ", grafo[i][j]);
        }
        printf("\n");
    }
}

// Função para encontrar o menor caminho usando o Algoritmo de Bellman-Ford
void bellmanFord(int grafo[NVERTICES][NVERTICES], int origem, int destino) {
    int distancias[NVERTICES];
    clock_t tempoInicio, tempoFim;

    tempoInicio = clock();
    for (int i = 0; i < NVERTICES; i++) {
        distancias[i] = INT_MAX;
    }

    distancias[origem] = 0;

    for (int k = 0; k < NVERTICES - 1; k++) {
        for (int i = 0; i < NVERTICES; i++) {
            for (int j = 0; j < NVERTICES; j++) {
                if (grafo[i][j] == 1 && distancias[i] != INT_MAX && distancias[i] + 1 < distancias[j]) {
                    distancias[j] = distancias[i] + 1;
                }
            }
        }
    }
    tempoFim = clock();

    printf("Tempo de busca: %.2f microsegundos\n", (double)(tempoFim - tempoInicio) * 1000000 / CLOCKS_PER_SEC);
    printf("Menor número de movimentos da configuração inicial para a configuração final: %d\n", distancias[destino]);
}

int main() {
    int grafo[NVERTICES][NVERTICES];
    int origem = 0; // Configuração inicial
    int destino = NVERTICES - 1; // Configuração final

    inicializarGrafo(grafo);

    // Adiciona as arestas do grafo representando as possibilidades de movimentos
    for (int i = 0; i < NVERTICES; i++) {
        for (int j = 0; j < NVERTICES; j++) {
            // Verifica se a configuração j é alcançável a partir da configuração i
            if (i != j && ((i % 3 != j % 3) || (i % 3 == j % 3 && i / 3 < j / 3))) {
                adicionarAresta(grafo, i, j);
            }
        }
    }

    printf("Matriz de adjacência:\n");
    exibirMatrizAdjacencia(grafo);

    bellmanFord(grafo, origem, destino);

    return 0;
}