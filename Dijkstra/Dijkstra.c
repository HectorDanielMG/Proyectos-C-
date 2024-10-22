#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Definición de la estructura para representar un nodo en la lista de adyacencia
typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;

// Estructura para representar una lista de adyacencia
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

// Estructura para representar un grafo
typedef struct Graph {
    int V;
    AdjList* array;
} Graph;

// Estructura para representar un nodo en la cola de prioridad (min heap)
typedef struct MinHeapNode {
    int v;
    int dist;
} MinHeapNode;

// Estructura para representar una cola de prioridad (min heap)
typedef struct MinHeap {
    int size;
    int capacity;
    int *pos;
    MinHeapNode **array;
} MinHeap;

// Crea un nuevo nodo en la lista de adyacencia
AdjListNode* newAdjListNode(int dest, int weight) {
    AdjListNode* newNode = (AdjListNode*) malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Crea un grafo con V vértices
Graph* createGraph(int V) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = V;

    // Crear una lista de adyacencia para cada vértice
    graph->array = (AdjList*) malloc(V * sizeof(AdjList));

    // Inicializar la lista de adyacencia para cada vértice
    for (int i = 0; i < V; i++)
        graph->array[i].head = NULL;

    return graph;
}

// Agrega un borde al grafo dirigido
void addEdge(Graph* graph, int src, int dest, int weight) {
    // Agrega un borde de src a dest. Un nuevo nodo se agrega a la lista de adyacencia de src.
    AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Como el grafo es no dirigido, también agregamos un borde de dest a src
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Crea un nodo de min heap
MinHeapNode* newMinHeapNode(int v, int dist) {
    MinHeapNode* minHeapNode = (MinHeapNode*) malloc(sizeof(MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

// Crea una cola de prioridad (min heap)
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*) malloc(sizeof(MinHeap));
    minHeap->pos = (int*) malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (MinHeapNode**) malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

// Intercambia dos nodos de min heap
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Función para hacer un heapify (ajustar el heap)
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        MinHeapNode* smallestNode = minHeap->array[smallest];
        MinHeapNode* idxNode = minHeap->array[idx];

        // Intercambia posiciones
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Intercambia nodos
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// Función para verificar si el heap está vacío
int isEmpty(MinHeap* minHeap) {
    return minHeap->size == 0;
}

// Extrae el vértice con la distancia mínima del heap
MinHeapNode* extractMin(MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    // Guarda el nodo raíz
    MinHeapNode* root = minHeap->array[0];

    // Reemplaza la raíz con el último nodo
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Actualiza la posición de los nodos
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    // Reduce el tamaño del heap y ajusta la estructura del heap
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Disminuye la distancia de un vértice v a una nueva distancia dist
void decreaseKey(MinHeap* minHeap, int v, int dist) {
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;

    // Ajusta la estructura del heap si es necesario
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        // Intercambia el nodo con su padre
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

// Verifica si un vértice está en el heap
bool isInMinHeap(MinHeap *minHeap, int v) {
    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}

// Función que imprime las distancias más cortas
void printArr(int dist[], int n) {
    printf("Vértice   Distancia desde la fuente\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Función principal que implementa el algoritmo de Dijkstra con min heap
void dijkstra(Graph* graph, int src) {
    int V = graph->V;
    int dist[V]; // dist[i] guardará la distancia más corta desde src a i

    // Cola de prioridad (min heap)
    MinHeap* minHeap = createMinHeap(V);

    // Inicializa el heap con todos los vértices y la distancia infinita
    for (int v = 0; v < V; ++v) {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    // Distancia del nodo fuente a sí mismo es siempre 0
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    // Inicializa el tamaño del heap con todos los vértices
    minHeap->size = V;

    // Mientras el heap no esté vacío
    while (!isEmpty(minHeap)) {
        // Extrae el vértice con la distancia mínima
        MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
    }