#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define NVERTICES 81
#define LENVERTICES 10

void exibirMenu();
void realizarBusca(int arestas[NVERTICES][NVERTICES], char configuracoes[NVERTICES][LENVERTICES], int algoritmo);
void lerCsv(char vertices[NVERTICES][LENVERTICES], int arestas[NVERTICES][NVERTICES]);
int encontrarIndiceConfiguracao(char config[LENVERTICES], char configuracoes[NVERTICES][LENVERTICES]);
int distanciaMinima(int distancias[NVERTICES], int visitados[NVERTICES]);
void dijkstra(int grafo[NVERTICES][NVERTICES], char inicio[LENVERTICES], char fim[LENVERTICES], char configuracoes[NVERTICES][LENVERTICES]);
void bellmanFord(int grafo[NVERTICES][NVERTICES], char inicio[LENVERTICES], char fim[LENVERTICES], char configuracoes[NVERTICES][LENVERTICES]);

int main()
{
    char vertices[NVERTICES][LENVERTICES];
    int arestas[NVERTICES][NVERTICES], opcao;
    
    lerCsv(vertices, arestas); 

    do
    {
        exibirMenu();
        printf("\n-> ");
        scanf("%d", &opcao);
        switch(opcao)
        {
            case 1:
                realizarBusca(arestas, vertices, 1);
                break;

            case 2:
                realizarBusca(arestas, vertices, 2);
                break;

            case 3:
                break;
            
            default:
                printf("Insira uma opcao valida!");
                break;
        }
    } while (opcao != 3);

    return 0;
}

void exibirMenu()
{
    printf("\n-------------------------------------------------------Torre de Hanoi-------------------------------------------------------");
    printf("\nAs jogadas sao descritas seguindo este padrao: '[A,A,A,A]'");
    printf("\nEste padrao indica que os 4 discos estao no poste A, sendo que a esquerda ficam os maiores discos e a direita os menores.");
    printf("\n\n1. Pesquisa do menor caminho com Dijkistra.");
    printf("\n2. Pesquisa do menor caminho com Bellman.");
    printf("\n3. Sair.");

}

void realizarBusca(int arestas[NVERTICES][NVERTICES], char configuracoes[NVERTICES][LENVERTICES], int algoritmo)
{
    char inicio[LENVERTICES], fim[LENVERTICES];
    printf("\nInsira um ponto de partida no seguinte formato: [A,A,A,A]\n-> ");
    scanf("%s", inicio);
    printf("\nInsira um ponto de destino no seguinte formato: [A,A,A,A]\n-> ");
    scanf("%s", fim);

    if(algoritmo == 1)
        dijkstra(arestas, inicio, fim, configuracoes);
    else 
        bellmanFord(arestas, inicio, fim, configuracoes);
}

void lerCsv(char vertices[NVERTICES][LENVERTICES], int arestas[NVERTICES][NVERTICES])
{
    FILE *arquivoDados;
    int valor;
    arquivoDados = fopen("vertices.txt", "r");

    if(arquivoDados)
    {
        for(int indiceVertice = 0; indiceVertice < NVERTICES; indiceVertice++)
            fscanf(arquivoDados, "%s", vertices[indiceVertice]);

        fclose(arquivoDados);
    }

    arquivoDados = fopen("matrix.txt", "r");

    if(arquivoDados)
    {
        for(int linha = 0; linha < NVERTICES; linha++)
        {
            for(int coluna = 0; coluna < NVERTICES; coluna++)
            {
                fscanf(arquivoDados, "%d,", &arestas[linha][coluna]);
            }
        }

        fclose(arquivoDados);
    }
}

int encontrarIndiceConfiguracao(char config[LENVERTICES], char configuracoes[NVERTICES][LENVERTICES]) 
{
    int indiceEncontrado = -1;

    for(int indiceConfig = 0; indiceConfig < NVERTICES && indiceEncontrado == -1; indiceConfig++) 
        if(strcmp(config, configuracoes[indiceConfig]) == 0)
            indiceEncontrado = indiceConfig;

    return indiceEncontrado;
}

int distanciaMinima(int distancias[NVERTICES], int visitados[NVERTICES]) 
{
    int minimo = INT_MAX;
    int indiceMinimo = -1;

    for(int i = 0; i < NVERTICES; i++) {
        if(!visitados[i] && distancias[i] <= minimo) 
        {
            minimo = distancias[i];
            indiceMinimo = i;
        }
    }

    return indiceMinimo;
}

void dijkstra(int grafo[NVERTICES][NVERTICES], char inicio[LENVERTICES], char fim[LENVERTICES], char configuracoes[NVERTICES][LENVERTICES]) {
    int indiceInicio = encontrarIndiceConfiguracao(inicio, configuracoes);
    int indiceFim = encontrarIndiceConfiguracao(fim, configuracoes);
    int distancias[NVERTICES];
    int visitados[NVERTICES];
    int predecessores[NVERTICES];
    clock_t tempoInicio, tempoFim;

    tempoInicio = clock();
    for(int i = 0; i < NVERTICES; i++) {
        distancias[i] = INT_MAX;
        visitados[i] = 0;
        predecessores[i] = -1; 
    }

    distancias[indiceInicio] = 0;

    for(int contador = 0; contador < NVERTICES - 1; contador++) {
        int i = distanciaMinima(distancias, visitados);
        visitados[i] = 1;

        for (int j = 0; j < NVERTICES; j++) {
            if (!visitados[j] && grafo[i][j] && distancias[i] != INT_MAX && distancias[i] + grafo[i][j] < distancias[j]) {
                distancias[j] = distancias[i] + grafo[i][j];
                predecessores[j] = i; 
            }
        }
    }
    tempoFim = clock();

    printf("\nTempo de busca: %.2f microsegundos", (double)(tempoFim - tempoInicio) * 1000000 / CLOCKS_PER_SEC);
    printf("\nMenor número de movimentos de %s até %s: %d\n", inicio, fim, distancias[indiceFim]);

    printf("Caminho percorrido: ");
    int atual = indiceFim;
    while (atual != indiceInicio) {
        printf("%s <- ", configuracoes[atual]);
        atual = predecessores[atual];
    }
    printf("%s\n", configuracoes[indiceInicio]);
}

void bellmanFord(int grafo[NVERTICES][NVERTICES], char inicio[LENVERTICES], char fim[LENVERTICES], char configuracoes[NVERTICES][LENVERTICES]) {
    int indiceInicio = encontrarIndiceConfiguracao(inicio, configuracoes);
    int indiceFim = encontrarIndiceConfiguracao(fim, configuracoes);
    int distancias[NVERTICES];
    int predecessores[NVERTICES];
    clock_t tempoInicio, tempoFim;

    tempoInicio = clock();
    for(int i = 0; i < NVERTICES; i++) {
        distancias[i] = INT_MAX;
        predecessores[i] = -1;
    }
    distancias[indiceInicio] = 0;

    for(int k = 0; k < NVERTICES - 1; k++) {
        for(int i = 0; i < NVERTICES; i++) {
            for(int j = 0; j < NVERTICES; j++) {
                if(grafo[i][j] == 1 && distancias[i] != INT_MAX && distancias[i] + 1 < distancias[j]) {
                    distancias[j] = distancias[i] + grafo[i][j];
                    predecessores[j] = i;
                }
            }
        }
    }
    tempoFim = clock();

    printf("\nTempo de busca: %.2f microsegundos", (double)(tempoFim - tempoInicio) * 1000000 / CLOCKS_PER_SEC);
    printf("\nMenor número de movimentos de %s até %s: %d\n", configuracoes[indiceInicio], configuracoes[indiceFim], distancias[indiceFim]);

    printf("Caminho percorrido: %s", configuracoes[indiceFim]);
    int atual = indiceFim;
    while (predecessores[atual] != -1) {
        printf(" <- %s", configuracoes[predecessores[atual]]);
        atual = predecessores[atual];
    }
    printf("\n");
}
