#include <stdlib.h>
#include <stdio.h>
#define OK 1

///ACLACION:SE AGREGA PRIMITIVAS DE INDICES  A LO QUE HIZO GUSTAVO
/**************************************************************************
Descripción: determina si el índice contiene 0 (cero) elementos.
Parámetros: indice: TDA índice.
Retorno: OK si está vacío, cualquier otro valor si no lo está.
Observaciones: -
**************************************************************************/
int indice_vacio(const t_indice *indice);
/**************************************************************************
descripción: determina si el índice contiene el tamaño máximo posible.
Parámetros: indice: TDA índice.
Retorno: OK si está lleno, cualquier otro valor si no lo está.
Observaciones: -
**************************************************************************/
int indice_lleno(const t_indice *indice);
/**************************************************************************
Descripción: deja el índice vacío.
Parámetros: indice: TDA indice.
Retorno: No posee.
Observaciones: -
**************************************************************************/
void indice_vaciar(t_indice* indice);
/**************************************************************************
