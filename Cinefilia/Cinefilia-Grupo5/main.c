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

#define MAX_REGISTROS 1000 // Un límite seguro para tus arreglos en RAM

int main() {
    printf("--- INICIANDO SISTEMA DE MIGRACION DE DATOS ---\n\n");

    // 1. SOLICITAR LA FECHA DE PROCESO
    t_fecha fecha_proceso;
    solicitar_Fecha_Proceso(&fecha_proceso);
    printf("\n");

    // 2. CONSTRUIR LOS NOMBRES DE LOS ARCHIVOS BINARIOS ESPERADOS
    // Usamos sprintf para concatenar texto con los números de la fecha
    char archivo_bin_miembros[50];
    char archivo_bin_titulos[50];

    // Quedará algo como: "miembros_15102023.dat"
    sprintf(archivo_bin_miembros, "miembros_%02d%02d%04d.dat", fecha_proceso.dia, fecha_proceso.mes, fecha_proceso.anio);
    sprintf(archivo_bin_titulos, "titulos_%02d%02d%04d.dat", fecha_proceso.dia, fecha_proceso.mes, fecha_proceso.anio);


    // 3. INICIALIZAR NUESTRAS LISTAS DINÁMICAS (En blanco)
    t_lista_miembros lista_m = {NULL, 0, 0};
    t_lista_titulos lista_t = {NULL, 0, 0};


    // =========================================================================
    //                    EVALUACIÓN DE RUTAS (CSV vs DAT)
    // =========================================================================

    // Intentamos abrir el archivo binario en modo lectura ("rb" = read binary)
    FILE *verificador_binario = fopen(archivo_bin_miembros, "rb");

    if (verificador_binario != NULL) {

        // --- CAMINO A: LOS BINARIOS YA EXISTEN PARA ESTA FECHA ---
        fclose(verificador_binario); // Lo cerramos porque solo queríamos ver si existía

        printf("[INFO] Archivos binarios detectados para la fecha seleccionada.\n");
        printf("Cargando datos directamente desde %s y %s...\n", archivo_bin_miembros, archivo_bin_titulos);

        // Aquí llamarás a las futuras funciones que cargan directo a tu lista dinámica
        // cargar_miembros_desde_binario(archivo_bin_miembros, &lista_m);
        // cargar_titulos_desde_binario(archivo_bin_titulos, &lista_t);

    } else {

        // --- CAMINO B: NO HAY BINARIOS. HAY QUE PROCESAR LOS CSV ---
        printf("[INFO] No se encontraron binarios para esta fecha. Procesando archivos CSV...\n");

        t_auditoria auditoria_miembros[20];
        int cant_errores_miembros = 0;
        t_auditoria auditoria_titulos[20];
        int cant_errores_titulos = 0;

        // 1. Procesamos y auditamos (Lo que ya programamos)
        procesar_archivo_miembros("Lotes Prueba/miembros.csv", auditoria_miembros, &cant_errores_miembros, &lista_m);
        generar_reporte_auditoria("auditoria_miembros.txt", auditoria_miembros, cant_errores_miembros, "DNI");

        procesar_archivo_titulos("Lotes Prueba/titulos.csv", auditoria_titulos, &cant_errores_titulos, &lista_t);
        generar_reporte_auditoria("auditoria_titulos.txt", auditoria_titulos, cant_errores_titulos, "ID");

        // 2. Guardamos las listas válidas en los nuevos archivos .dat para el futuro
        printf("\nGuardando registros validos en archivos binarios (.dat)...\n");
        // guardar_miembros_en_binario(archivo_bin_miembros, &lista_m);
        // guardar_titulos_en_binario(archivo_bin_titulos, &lista_t);
    }

    // =========================================================================

    printf("\n--- CARGA COMPLETADA ---\n");
    printf("Miembros listos para usar: %d\n", lista_m.cantidad);
    printf("Titulos listos para usar: %d\n", lista_t.cantidad);

    // menu_operaciones(&lista_m, &lista_t);

    // Limpieza
    if (lista_m.array != NULL) free(lista_m.array);
    if (lista_t.array != NULL) free(lista_t.array);

    return 0;
}
