#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// Estructuras de Nodo, Lista de Adyacencia, Grafo, Nodo MinHeap y MinHeap
typedef struct AdjListNode { int dest, weight; struct AdjListNode* next; } AdjListNode;
typedef struct { AdjListNode* head; } AdjList;
typedef struct { int V; AdjList* array; } Graph;
typedef struct { int v, dist; } MinHeapNode;
typedef struct { int size, capacity, *pos; MinHeapNode **array; } MinHeap;

// Funciones de MinHeap (Creación, Inserción y Extracción)
MinHeapNode* newMinHeapNode(int v, int dist) { MinHeapNode* n = (MinHeapNode*) malloc(sizeof(MinHeapNode)); n->v = v; n->dist = dist; return n; }
MinHeap* createMinHeap(int capacity) { MinHeap* heap = (MinHeap*) malloc(sizeof(MinHeap)); heap->pos = malloc(capacity * sizeof(int)); heap->size = 0; heap->capacity = capacity; heap->array = malloc(capacity * sizeof(MinHeapNode*)); return heap; }
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) { MinHeapNode* t = *a; *a = *b; *b = t; }
void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx, left = 2 * idx + 1, right = 2 * idx + 2;
    if (left < heap->size && heap->array[left]->dist < heap->array[smallest]->dist) smallest = left;
    if (right < heap->size && heap->array[right]->dist < heap->array[smallest]->dist) smallest = right;
    if (smallest != idx) { swapMinHeapNode(&heap->array[smallest], &heap->array[idx]); minHeapify(heap, smallest); }
}
MinHeapNode* extractMin(MinHeap* heap) { 
    if (heap->size == 0) return NULL; 
    MinHeapNode* root = heap->array[0], *lastNode = heap->array[--heap->size]; 
    heap->array[0] = lastNode; minHeapify(heap, 0); return root; 
}
void decreaseKey(MinHeap* heap, int v, int dist) {
    int i = heap->pos[v]; heap->array[i]->dist = dist;
    while (i && heap->array[i]->dist < heap->array[(i - 1) / 2]->dist) {
        heap->pos[heap->array[i]->v] = (i - 1) / 2; heap->pos[heap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&heap->array[i], &heap->array[(i - 1) / 2]); i = (i - 1) / 2;
    }
}
bool isInMinHeap(MinHeap* heap, int v) { return heap->pos[v] < heap->size; }

// Funciones de Grafo (Creación y Agregar Arista)
AdjListNode* newAdjListNode(int dest, int weight) { AdjListNode* node = malloc(sizeof(AdjListNode)); node->dest = dest; node->weight = weight; node->next = NULL; return node; }
Graph* createGraph(int V) { Graph* graph = (Graph*) malloc(sizeof(Graph)); graph->V = V; graph->array = malloc(V * sizeof(AdjList)); for (int i = 0; i < V; i++) graph->array[i].head = NULL; return graph; }
void addEdge(Graph* graph, int src, int dest, int weight) { 
    AdjListNode* node = newAdjListNode(dest, weight); node->next = graph->array[src].head; graph->array[src].head = node;
    node = newAdjListNode(src, weight); node->next = graph->array[dest].head; graph->array[dest].head = node;
}

// Algoritmo de Dijkstra
void dijkstra(Graph* graph, int src) {
    int V = graph->V, dist[V]; MinHeap* heap = createMinHeap(V);
    for (int v = 0; v < V; ++v) dist[v] = INT_MAX, heap->array[v] = newMinHeapNode(v, dist[v]), heap->pos[v] = v;
    heap->array[src] = newMinHeapNode(src, dist[src] = 0); decreaseKey(heap, src, 0); heap->size = V;
    
    while (heap->size) {
        int u = extractMin(heap)->v;
        for (AdjListNode* pCrawl = graph->array[u].head; pCrawl; pCrawl = pCrawl->next) {
            int v = pCrawl->dest;
            if (isInMinHeap(heap, v) && dist[u] != INT_MAX && dist[u] + pCrawl->weight < dist[v])
                dist[v] = dist[u] + pCrawl->weight, decreaseKey(heap, v, dist[v]);
        }
    }

    printf("Vértice   Distancia desde la fuente\n");
    for (int i = 0; i < V; ++i) printf("%d \t\t %d\n", i, dist[i]);
}

// Función principal
int main() {
    Graph* graph = createGraph(9);
    addEdge(graph, 0, 1, 4); addEdge(graph, 0, 7, 8); addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11); addEdge(graph, 2, 3, 7); addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4); addEdge(graph, 3, 4, 9); addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10); addEdge(graph, 5, 6, 2); addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6); addEdge(graph, 7, 8, 7);

    dijkstra(graph, 0);
    return 0;
}
