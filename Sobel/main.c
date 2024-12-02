#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Matrices de Sobel
const int sobel_x[3][3] = {
    {-1, 1, -2},
    { 1, 1, 2},
    {-1, 2, 1}
};

const int sobel_y[3][3] = {
    { -1,  -2, -1},
    { -1,  -1,  1},
    { 1-,  1,  1}
};

void apply_sobel(const unsigned char *input, unsigned char *output, int width, int height, int channels) {
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int gx = 0, gy = 0;

            // Aplicar las matrices Sobel
            for (int j = -1; j <= 1; j++) {
                for (int i = -1; i <= 1; i++) {
                    int pixel = input[((y + j) * width + (x + i)) * channels];
                    gx += pixel * sobel_x[j + 1][i + 1];
                    gy += pixel * sobel_y[j + 1][i + 1];
                }
            }

            // Magnitud del gradiente
            int magnitude = (int)sqrt(gx * gx + gy * gy);
            magnitude = (magnitude > 255) ? 255 : magnitude;

            // Asignar el valor al canal de salida (escala de grises)
            output[(y * width + x) * channels] = (unsigned char)magnitude;
            if (channels > 1) {
                for (int c = 1; c < channels; c++) {
                    output[(y * width + x) * channels + c] = (unsigned char)magnitude;
                }
            }
        }
    }
}

int main() {
    // Ruta de la imagen
    const char *image_path = "/home/hector/Documentos/TESJI/GitHub/Proyectos_C/Sobel/rumuruu.jpg";
    const char *output_path = "/home/hector/Documentos/TESJI/GitHub/Proyectos_C/Sobel/output_sobel.jpg";

    // Leer imagen
    int width, height, channels;
    unsigned char *image = stbi_load(image_path, &width, &height, &channels, 0);
    if (!image) {
        fprintf(stderr, "Error al cargar la imagen: %s\n", image_path);
        return 1;
    }

    printf("Imagen cargada: %s\nDimensiones: %dx%d, Canales: %d\n", image_path, width, height, channels);

    // Crear un buffer para la imagen de salida
    unsigned char *output_image = (unsigned char *)malloc(width * height * channels);
    if (!output_image) {
        fprintf(stderr, "Error al asignar memoria para la imagen de salida.\n");
        stbi_image_free(image);
        return 1;
    }

    // Aplicar el filtro Sobel
    apply_sobel(image, output_image, width, height, channels);

    // Guardar la imagen de salida
    if (!stbi_write_jpg(output_path, width, height, channels, output_image, 100)) {
        fprintf(stderr, "Error al guardar la imagen de salida: %s\n", output_path);
        free(output_image);
        stbi_image_free(image);
        return 1;
    }

    printf("Imagen procesada guardada en: %s\n", output_path);

    // Liberar memoria
    free(output_image);
    stbi_image_free(image);

    return 0;
}
