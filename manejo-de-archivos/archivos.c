#include "archivos.h"
#include <string.h>

int csv_leer_fila(FILE *archivo, char delimitador, char *columnas[], int max_columnas, char *buffer, int tam_buffer) {
    if (fgets(buffer, tam_buffer, archivo) == NULL) {
        return 0; // Fin del archivo
    }

    // Limpiar el salto de línea al final
    buffer[strcspn(buffer, "\r\n")] = '\0';

    int contador_columnas = 0;

    // ptr será nuestro cursor moviéndose por el texto
    char *ptr = buffer;

    while (ptr != NULL && contador_columnas < max_columnas) {
        // Guardamos el inicio de la columna actual
        columnas[contador_columnas] = ptr;
        contador_columnas++;

        // Buscamos el próximo delimitador (ej: el próximo ';')
        char *siguiente = strchr(ptr, delimitador);

        if (siguiente != NULL) {
            // Si encontramos un delimitador, lo cortamos (reemplazamos por \0)
            *siguiente = '\0';
            // Movemos el cursor justo después del delimitador cortado
            ptr = siguiente + 1;
        } else {
            // Si no hay más delimitadores, es la última columna. Terminamos.
            ptr = NULL;
        }
    }

    return contador_columnas;
}
