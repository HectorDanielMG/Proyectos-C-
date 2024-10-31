#include <stdio.h>

void ordenarAscendente(int arr[], int n);
void ordenarDescendente(int arr[], int n);
void imprimirArreglo(int arr[], int n);

int main() {
    int n;

    printf("Ingrese el tamaño del arreglo: ");
    scanf("%d", &n);

    int arr[n];
    printf("Ingrese los elementos del arreglo:\n");
    for (int i = 0; i < n; i++) {
        printf("Elemento %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    printf("\nArreglo original:\n");
    imprimirArreglo(arr, n);

    ordenarAscendente(arr, n);
    printf("\nArreglo en orden ascendente:\n");
    imprimirArreglo(arr, n);

    ordenarDescendente(arr, n);
    printf("\nArreglo en orden descendente:\n");
    imprimirArreglo(arr, n);

    return 0;
}

void ordenarAscendente(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void ordenarDescendente(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void imprimirArreglo(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
