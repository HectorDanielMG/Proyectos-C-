#include <stdio.h>
#include <stdlib.h>

// Prototipo de la función para ordenar el arreglo
void selectionSort(int *arr, int size);

int main() {
    int size;

    // Solicitar al usuario el tamaño del arreglo
    printf("Ingrese el tamaño del arreglo: ");
    scanf("%d", &size);

    // Reservar memoria para el arreglo
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Error al reservar memoria.\n");
        return 1; // Salir si no se pudo reservar memoria
    }

    // Solicitar al usuario que ingrese los elementos del arreglo
    printf("Ingrese los elementos del arreglo:\n");
    for (int i = 0; i < size; i++) {
        printf("Elemento %d: ", i + 1);
        scanf("%d", arr + i); // Usando apuntadores para asignar valores
    }

    printf("Arreglo original:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }

    selectionSort(arr, size);

    printf("\nArreglo ordenado:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }

    // Liberar la memoria reservada
    free(arr);
    
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
