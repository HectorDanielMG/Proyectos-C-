 #include <stdio.h>
#include <string.h>

// Función para invertir la cadena usando apuntadores
void invertirCadena(char *inicio, char *fin) {
    char temp;
    while (inicio < fin) {
        // Intercambiar los valores a los que apuntan 'inicio' y 'fin'
        temp = *inicio;
        *inicio = *fin;
        *fin = temp;

        // Mover los apuntadores hacia el centro
        inicio++;
        fin--;
    }
}

int main() {
    char cadena[100];

    // Solicitar la cadena al usuario
    printf("Ingrese una cadena de caracteres: ");
    fgets(cadena, sizeof(cadena), stdin);

    // Eliminar el salto de línea si lo hay
    cadena[strcspn(cadena, "\n")] = 0;

    // Puntero al inicio y fin de la cadena
    char *inicio = cadena;
    char *fin = cadena + strlen(cadena) - 1;

    // Invertir la cadena
    invertirCadena(inicio, fin);

    // Mostrar la cadena invertida
    printf("La cadena invertida es: %s\n", cadena);

    return 0;
}

