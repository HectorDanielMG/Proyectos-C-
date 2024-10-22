#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 9 // Número de vértices en el gráfico

// Estructura para representar un par de vértice y distancia
typedef struct {
    int vertex;
    int distance;
} Node;

// Función para encontrar el vértice con la distancia mínima que aún no ha sido procesado
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }

    return min_index;
}

// Función para imprimir la ruta más corta desde el nodo fuente
void printSolution(int dist[], int n) {
    printf("Nodo\t\tDistancia desde la fuente\n");
    for (int i = 0; i < n; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Función que implementa el algoritmo de Dijkstra
void dijkstra(int graph[V][V], int src) {
    int dist[V];      // Array para guardar las distancias más cortas desde src
    bool sptSet[V];   // sptSet[i] será verdadero si el vértice i está incluido en el conjunto más corto

    // Inicializar todas las distancias como INFINITO y el conjunto sptSet[] como falso
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // La distancia del nodo origen a sí mismo es siempre 0
    dist[src] = 0;

    // Encuentra el camino más corto para todos los vértices
    for (int count = 0; count < V - 1; count++) {
        // Elige el vértice de distancia mínima del conjunto de vértices aún no procesados
        int u = minDistance(dist, sptSet);

        // Marca el vértice como procesado
        sptSet[u] = true;

        // Actualiza el valor de distancia de los vértices adyacentes al vértice elegido
        for (int v = 0; v < V; v++) {
            // Actualiza dist[v] si no está en sptSet, hay un camino desde u a v, y el
            // costo total del camino desde src a v a través de u es menor que el valor actual de dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Imprime la solución
    printSolution(dist, V);
}

int main() {
    // Ejemplo de gráfico de adyacencia representado como una matriz
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    dijkstra(graph, 0); // Llamada al algoritmo con el nodo 0 como fuente

    return 0;
}
