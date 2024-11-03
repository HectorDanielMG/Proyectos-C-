#include <stdio.h>
#include <string.h>

void invertirCadena(char *cadena)
{
    int longitud = strlen(cadena);
    for (int i = 0; i < longitud / 2; i++)
    {
        char temp = cadena[i];
        cadena[i] = cadena[longitud - i - 1];
        cadena[longitud - i - 1] = temp;
    }
}

void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    char cadena[100];
    
    printf("Ingrese una cadena (máximo 99 caracteres): ");
    fgets(cadena, sizeof(cadena), stdin);
    
    // Eliminar el salto de línea generado por fgets si existe
    cadena[strcspn(cadena, "\n")] = '\0';

    printf("Cadena original: %s\n", cadena);
    
    invertirCadena(cadena);

    printf("Cadena invertida: %s\n", cadena);

    return 0;
}
