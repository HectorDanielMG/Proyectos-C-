 
#include <stdio.h>
#include <limits.h>

#define V 5 // Número de vértices

// Encuentra el vértice con la distancia mínima
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Imprime la solución
void printSolution(int dist[]) {
    printf("Nodo\tDistancia desde el origen\n");
    for (int i = 0; i < V; i++)
        printf("%d\t\t%d\n", i, dist[i]);
}

// Implementación del algoritmo de Dijkstra
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // La distancia más corta desde src a cada nodo
    int sptSet[V]; // true si el nodo i está en el conjunto de caminos más cortos

    // Inicialización de todas las distancias como infinitas
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = 0;

    // La distancia del nodo origen a sí mismo es 0
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet); // Nodo con distancia mínima
        sptSet[u] = 1;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printSolution(dist);
}

int main() {
    // Representación de un gráfico como una matriz de adyacencia
    int graph[V][V] = {
        {0, 10, 0, 30, 100},
        {10, 0, 50, 0, 0},
        {0, 50, 0, 20, 10},
        {30, 0, 20, 0, 60},
        {100, 0, 10, 60, 0}
    };

    dijkstra(graph, 0); // Nodo origen 0

    return 0;
}
