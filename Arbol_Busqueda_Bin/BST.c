 
#include <stdio.h>
#include <stdlib.h>

// Estructura para un nodo del árbol
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Crear un nuevo nodo
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Insertar un nodo en el árbol
struct Node* insert(struct Node* node, int data) {
    if (node == NULL) return newNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);

    return node;
}

// Recorrido en orden (inorder)
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Buscar un valor en el árbol
struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data)
        return search(root->left, data);

    return search(root->right, data);
}

int main() {
    struct Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Recorrido en orden (inorder): ");
    inorder(root);
    printf("\n");

    int key = 40;
    struct Node* found = search(root, key);
    if (found != NULL)
        printf("Nodo %d encontrado.\n", key);
    else
        printf("Nodo %d no encontrado.\n", key);

    return 0;
}
