#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_NODES 100

void dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int startNode, bool directed) {
    int distance[MAX_NODES];
    bool visited[MAX_NODES];
    int parent[MAX_NODES];
    
    for (int i = 0; i < n; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    distance[startNode] = 0;

    for (int i = 0; i < n - 1; i++) {
        int minDist = INT_MAX, minIndex;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && distance[j] <= minDist) {
                minDist = distance[j];
                minIndex = j;
            }
        }

        int u = minIndex;
        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && distance[u] != INT_MAX &&
                distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("Nodo \tDistancia desde el Nodo Inicial \tRuta\n");
    for (int i = 0; i < n; i++) {
        if (i != startNode) {
            printf("%d \t\t%d \t\t\t", i, distance[i]);
            int j = i;
            printf("%d", i);
            while (parent[j] != -1) {
                printf(" <- %d", parent[j]);
                j = parent[j];
            }
            printf("\n");
        }
    }
}

int main() {
    int graph[MAX_NODES][MAX_NODES];
    int n, startNode;
    bool directed;

    printf("Ingrese el número de nodos en el grafo (máximo %d): ", MAX_NODES);
    scanf("%d", &n);

    printf("¿El grafo es dirigido? (1 = Sí, 0 = No): ");
    scanf("%d", &directed);

    printf("Ingrese la matriz de adyacencia del grafo:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Peso de la arista %d -> %d: ", i, j);
            scanf("%d", &graph[i][j]);
            if (!directed && i != j) {
                graph[j][i] = graph[i][j];
            }
        }
    }

    printf("Ingrese el nodo inicial: ");
    scanf("%d", &startNode);

    dijkstra(graph, n, startNode, directed);

    return 0;
}
