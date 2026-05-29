#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>

#define MAX_LINEA_CSV 1024

/**
 * Lee una fila del archivo y la divide en columnas.
 * - archivo: el puntero al archivo ya abierto con fopen().
 * - delimitador: el carácter que separa los datos (ej: ';').
 * - columnas: array donde se guardarán los punteros a cada texto.
 * - max_columnas: tamaño del array 'columnas'.
 * - buffer: array donde se almacena la línea cruda.
 * - tam_buffer: tamaño máximo del buffer.
 * Retorna: El número de columnas leídas, o 0 si llegó al final del archivo.
 */
int csv_leer_fila(FILE *archivo, char delimitador, char *columnas[], int max_columnas, char *buffer, int tam_buffer);



#endif // ARCHIVOS_H_INCLUDED
