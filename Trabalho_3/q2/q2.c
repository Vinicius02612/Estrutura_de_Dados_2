#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

typedef struct {
    int destino;
    double confiabilidade;
} Aresta;

typedef struct {
    int vertice;
    double confiabilidade;
} Vertice;

typedef struct {
    Aresta arestas[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Grafo;

void inicializarGrafo(Grafo *grafo, int numVertices) {
    grafo->numVertices = numVertices;

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            grafo->arestas[i][j].destino = -1;
            grafo->arestas[i][j].confiabilidade = 0.0;
        }
    }
}

void adicionarAresta(Grafo *grafo, int origem, int destino, double confiabilidade) {
    grafo->arestas[origem][destino].destino = destino;
    grafo->arestas[origem][destino].confiabilidade = confiabilidade;
}

void dijkstra(Grafo *grafo, int origem, int destino) {
    Vertice vertices[MAX_VERTICES];
    double distancias[MAX_VERTICES];
    int visitados[MAX_VERTICES];

    for (int i = 0; i < grafo->numVertices; i++) {
        vertices[i].vertice = i;
        vertices[i].confiabilidade = 0.0;
        distancias[i] = 0.0;
        visitados[i] = 0;
    }

    vertices[origem].confiabilidade = 1.0;

    for (int i = 0; i < grafo->numVertices - 1; i++) {
        int u = -1;
        double confiabilidadeMax = 0.0;

        for (int j = 0; j < grafo->numVertices; j++) {
            if (!visitados[j] && vertices[j].confiabilidade > confiabilidadeMax) {
                u = j;
                confiabilidadeMax = vertices[j].confiabilidade;
            }
        }

        visitados[u] = 1;

        for (int v = 0; v < grafo->numVertices; v++) {
            if (!visitados[v] && grafo->arestas[u][v].destino != -1) {
                double novaConfiabilidade = vertices[u].confiabilidade * grafo->arestas[u][v].confiabilidade;

                if (novaConfiabilidade > vertices[v].confiabilidade) {
                    vertices[v].confiabilidade = novaConfiabilidade;
                    distancias[v] = distancias[u] + 1;  // Pode ser ajustado conforme necessário
                }
            }
        }
    }

    printf("Caminho mais confiável de %d para %d:\n", origem, destino);
    printf("Confiabilidade: %lf\n", vertices[destino].confiabilidade);
    printf("Distância: %lf\n", distancias[destino]);
}

int main() {
    Grafo grafo;
    int numVertices, origem, destino;

    printf("Informe o número de vértices no grafo: ");
    scanf("%d", &numVertices);

    inicializarGrafo(&grafo, numVertices);

    // Exemplo de entrada de arestas com confiabilidade
    adicionarAresta(&grafo, 0, 1, 0.8);
    adicionarAresta(&grafo, 1, 2, 0.9);
    adicionarAresta(&grafo, 0, 2, 0.7);
    adicionarAresta(&grafo, 2, 3, 0.95);

    printf("Informe o vértice de origem: ");
    scanf("%d", &origem);

    printf("Informe o vértice de destino: ");
    scanf("%d", &destino);

    dijkstra(&grafo, origem, destino);

    return 0;
}