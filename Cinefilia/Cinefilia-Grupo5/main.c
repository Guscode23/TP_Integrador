#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "structs.h"
#include "fecha.h"
#include "archivos.h"
#include "auditoria.h"

//// ============================================================================
////                       1. FUNCIONES DE VALIDACION ESPECIFICAS
//// ============================================================================
//
//*  EJEMPLO DE VALIDACION: DNI
// * Todas tus futuras funciones deben verse exactamente así: recibir void*,
// * castearlo a miembro*, y devolver TODO_OK o ERROR.
// */
//int val_dni(void *dato) {
//    // 1. Desenmascaramos el dato
//    miembro *m = (miembro *)dato;
//
//    // 2. Aplicamos la regla de negocio (Ej: DNI entre 1 millón y 100 millones)
//    if (m->dni > 1000000 && m->dni < 100000000) {
//        return TODO_OK;
//    }
//
//    return ERROR;
//}
//
//// Aquí agregarás val_cuil, val_nombres, val_fechas, etc... siguiendo el mismo patrón.
//
//
//// El Motor Generico exigido por el TP
//int validar_campo(void *dato, int (*funcion_validadora)(void *)) {
//    return funcion_validadora(dato);
//}




int main() {

    t_auditoria arreglo_auditorias[20];
    int cant_tipos_error = 0;


    procesar_archivo_miembros("Lotes Prueba/miembros.csv", arreglo_auditorias, &cant_tipos_error);

    generar_reporte_auditoria("Lotes Prueba/auditoria.txt", arreglo_auditorias, cant_tipos_error);

    return 0;

}
