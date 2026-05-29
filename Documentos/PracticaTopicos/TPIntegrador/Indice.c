#include <stdlib.h>
#include <string.h>
#include "Indidce.h


int indice_vacio(const t_indice *indice) {
    return (!indice || indice->cantidad_elementos_actual == 0) ? OK : 0;
}

int indice_lleno(const t_indice *indice) {
    if (!indice) return 0;
    return (indice->cantidad_elementos_actual >= indice->cantidad_elementos_maxima) ? OK : 0;
}

/**************************************************************************
 * Vaciar: deja el índice sin elementos (conserva la memoria)
 **************************************************************************/
void indice_vaciar(t_indice* indice) {
    if (!indice) return;
    indice->cantidad_elementos_actual = 0;
}
