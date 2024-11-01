#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL) return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

int treeHeight(Node* root) {
    if (root == NULL) return -1;
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int countNodes(Node* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Helper function to find the k-th smallest element
void kthSmallestHelper(Node* root, int* k, int* result) {
    if (root == NULL || *k == 0) return;

    kthSmallestHelper(root->left, k, result);
    (*k)--;
    if (*k == 0) {
        *result = root->data;
        return;
    }
    kthSmallestHelper(root->right, k, result);
}

int findKthSmallest(Node* root, int k) {
    int result = -1;
    kthSmallestHelper(root, &k, &result);
    return result;
}

// Calculate the depth of each node
void calculateDepth(Node* root, int depth) {
    if (root == NULL) return;
    printf("Node %d is at depth %d\n", root->data, depth);
    calculateDepth(root->left, depth + 1);
    calculateDepth(root->right, depth + 1);
}

// Print leaf nodes
void printLeafNodes(Node* root) {
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL) {
        printf("%d ", root->data);
        return;
    }
    printLeafNodes(root->left);
    printLeafNodes(root->right);
}

void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

int main() {
    Node* root = NULL;
    int option, value, k;

    while (1) {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert\n2. Tree Height\n3. Count Nodes\n4. Find k-th Smallest\n5. Print Depths\n6. Print Leaf Nodes\n");
        printf("7. In-order Traversal\n8. Exit\nChoose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;

            case 2:
                printf("Tree height: %d\n", treeHeight(root));
                break;

            case 3:
                printf("Total nodes: %d\n", countNodes(root));
                break;

            case 4:
                printf("Enter k to find k-th smallest element: ");
                scanf("%d", &k);
                value = findKthSmallest(root, k);
                if (value != -1)
                    printf("The %d-th smallest element is %d\n", k, value);
                else
                    printf("There are less than %d elements in the tree.\n", k);
                break;

            case 5:
                printf("Depth of each node:\n");
                calculateDepth(root, 0);
                break;

            case 6:
                printf("Leaf nodes: ");
                printLeafNodes(root);
                printf("\n");
                break;

            case 7:
                printf("In-order traversal: ");
                inOrder(root);
                printf("\n");
                break;

            case 8:
                exit(0);

            default:
                printf("Invalid option.\n");
                break;
        }
    }
    return 0;
}
