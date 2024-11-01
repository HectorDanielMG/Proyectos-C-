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

Node* findMin(Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int data) {
    if (root == NULL) return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

int treeHeight(Node* root) {
    if (root == NULL) return -1;
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int findMax(Node* root) {
    while (root->right != NULL) root = root->right;
    return root->data;
}

int countNodes(Node* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int sumOfNodes(Node* root) {
    if (root == NULL) return 0;
    return root->data + sumOfNodes(root->left) + sumOfNodes(root->right);
}

bool isBalanced(Node* root) {
    if (root == NULL) return true;

    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);

    if (abs(leftHeight - rightHeight) <= 1 &&
        isBalanced(root->left) &&
        isBalanced(root->right))
        return true;

    return false;
}

void inOrder(Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void preOrder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    Node* root = NULL;
    int option, value;

    while (1) {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert\n2. Delete\n3. Find Minimum\n4. Find Maximum\n5. Tree Height\n6. Count Nodes\n");
        printf("7. Sum of Nodes\n8. Check if Balanced\n9. In-order Traversal\n10. Pre-order Traversal\n");
        printf("11. Post-order Traversal\n12. Exit\nChoose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;

            case 3:
                if (root != NULL)
                    printf("Minimum value: %d\n", findMin(root)->data);
                else
                    printf("Tree is empty.\n");
                break;

            case 4:
                if (root != NULL)
                    printf("Maximum value: %d\n", findMax(root));
                else
                    printf("Tree is empty.\n");
                break;

            case 5:
                printf("Tree height: %d\n", treeHeight(root));
                break;

            case 6:
                printf("Total nodes: %d\n", countNodes(root));
                break;

            case 7:
                printf("Sum of all nodes: %d\n", sumOfNodes(root));
                break;

            case 8:
                if (isBalanced(root))
                    printf("The tree is balanced.\n");
                else
                    printf("The tree is not balanced.\n");
                break;

            case 9:
                printf("In-order traversal: ");
                inOrder(root);
                printf("\n");
                break;

            case 10:
                printf("Pre-order traversal: ");
                preOrder(root);
                printf("\n");
                break;

            case 11:
                printf("Post-order traversal: ");
                postOrder(root);
                printf("\n");
                break;

            case 12:
                exit(0);

            default:
                printf("Invalid option.\n");
                break;
        }
    }
    return 0;
}
