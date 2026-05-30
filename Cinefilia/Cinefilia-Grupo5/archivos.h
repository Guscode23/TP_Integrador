#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "structs.h"

int validar_campo(void *dato, int (*funcion_validadora)(void *));
int val_dni(void *dato);
int val_id_titulo(void *dato);
int val_stock(void *dato);


void procesar_archivo_miembros(const char *ruta_archivo, t_auditoria *arreglo_auditorias, int *cant_tipos_error, t_lista_miembros *lista_validos);
void procesar_archivo_titulos(const char *ruta_archivo, t_auditoria *arreglo_auditorias, int *cant_tipos_error, t_lista_titulos *lista_validos);


char* extraer_campo(char **cadena, const char *delimitador);


#endif // ARCHIVOS_H_INCLUDED
