#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    int valor;
    struct Nodo* izquierda;
    struct Nodo* derecha;
};

// Crear un nuevo nodo en el árbol
struct Nodo* nuevoNodo(int valor) {
    struct Nodo* nodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nodo->valor = valor;
    nodo->izquierda = nodo->derecha = NULL;
    return nodo;
}

// Insertar un valor en el BST
struct Nodo* insertar(struct Nodo* nodo, int valor) {
    if (nodo == NULL) {
        return nuevoNodo(valor);
    }
    if (valor < nodo->valor) {
        nodo->izquierda = insertar(nodo->izquierda, valor);
    } else if (valor > nodo->valor) {
        nodo->derecha = insertar(nodo->derecha, valor);
    }
    return nodo;
}

// Buscar un nodo en el BST
struct Nodo* buscar(struct Nodo* nodo, int valor) {
    if (nodo == NULL || nodo->valor == valor) {
        return nodo;
    }
    if (valor < nodo->valor) {
        return buscar(nodo->izquierda, valor);
    } else {
        return buscar(nodo->derecha, valor);
    }
}

// Encontrar el nodo con el valor mínimo (para eliminación)
struct Nodo* minValorNodo(struct Nodo* nodo) {
    struct Nodo* actual = nodo;
    while (actual && actual->izquierda != NULL) {
        actual = actual->izquierda;
    }
    return actual;
}

// Eliminar un nodo en el BST
struct Nodo* eliminarNodo(struct Nodo* nodo, int valor) {
    if (nodo == NULL) {
        return nodo;
    }
    if (valor < nodo->valor) {
        nodo->izquierda = eliminarNodo(nodo->izquierda, valor);
    } else if (valor > nodo->valor) {
        nodo->derecha = eliminarNodo(nodo->derecha, valor);
    } else {
        // Nodo con un solo hijo o sin hijos
        if (nodo->izquierda == NULL) {
            struct Nodo* temp = nodo->derecha;
            free(nodo);
            return temp;
        } else if (nodo->derecha == NULL) {
            struct Nodo* temp = nodo->izquierda;
            free(nodo);
            return temp;
        }

        // Nodo con dos hijos
        struct Nodo* temp = minValorNodo(nodo->derecha);
        nodo->valor = temp->valor;
        nodo->derecha = eliminarNodo(nodo->derecha, temp->valor);
    }
    return nodo;
}

// Recorrido en orden
void enOrden(struct Nodo* nodo) {
    if (nodo != NULL) {
        enOrden(nodo->izquierda);
        printf("%d ", nodo->valor);
        enOrden(nodo->derecha);
    }
}

// Recorrido en preorden
void preOrden(struct Nodo* nodo) {
    if (nodo != NULL) {
        printf("%d ", nodo->valor);
        preOrden(nodo->izquierda);
        preOrden(nodo->derecha);
    }
}

// Recorrido en postorden
void postOrden(struct Nodo* nodo) {
    if (nodo != NULL) {
        postOrden(nodo->izquierda);
        postOrden(nodo->derecha);
        printf("%d ", nodo->valor);
    }
}

int main() {
    struct Nodo* raiz = NULL;
    int opcion, valor;

    do {
        printf("\nOpciones:\n1. Insertar\n2. Buscar\n3. Eliminar\n4. Recorrido en orden\n5. Recorrido en preorden\n6. Recorrido en postorden\n7. Salir\nElige una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingresa el valor a insertar: ");
                scanf("%d", &valor);
                raiz = insertar(raiz, valor);
                break;
            case 2:
                printf("Ingresa el valor a buscar: ");
                scanf("%d", &valor);
                struct Nodo* encontrado = buscar(raiz, valor);
                if (encontrado != NULL) {
                    printf("Valor %d encontrado en el árbol.\n", valor);
                } else {
                    printf("Valor %d no encontrado en el árbol.\n", valor);
                }
                break;
            case 3:
                printf("Ingresa el valor a eliminar: ");
                scanf("%d", &valor);
                raiz = eliminarNodo(raiz, valor);
                printf("Nodo eliminado (si existía).\n");
                break;
            case 4:
                printf("Recorrido en orden: ");
                enOrden(raiz);
                printf("\n");
                break;
            case 5:
                printf("Recorrido en preorden: ");
                preOrden(raiz);
                printf("\n");
                break;
            case 6:
                printf("Recorrido en postorden: ");
                postOrden(raiz);
                printf("\n");
                break;
            case 7:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 7);

    return 0;
}
