 #include <stdio.h>

// Prototipo de la función para ordenar el arreglo
void selectionSort(int *arr, int size);

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Arreglo original:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }

    selectionSort(arr, size);

    printf("\nArreglo ordenado:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }

    return 0;
}

// Función para realizar el ordenamiento por selección
void selectionSort(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;

        // Encontrar el valor mínimo en el arreglo no ordenado
        for (int j = i + 1; j < size; j++) {
            if (*(arr + j) < *(arr + min_idx)) {
                min_idx = j;
            }
        }

        // Intercambiar el valor mínimo encontrado con el primer elemento
        int temp = *(arr + min_idx);
        *(arr + min_idx) = *(arr + i);
        *(arr + i) = temp;
    }
}

