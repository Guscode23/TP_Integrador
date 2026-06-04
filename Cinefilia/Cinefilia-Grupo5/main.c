#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "indice.h"
#include "structs.h"
#include "fecha.h"
#include "archivos.h"
#include "auditoria.h"
#include "menu.h"

#define MAX_REGISTROS 1000

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
    //t_lista_alquileres lista_a = {NULL, 0, 100}; // Esto hay que pasarlo al menú para que pueda usar la lista de alquileres


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
        cargar_miembros_desde_binario(archivo_bin_miembros, &lista_m);
        cargar_titulos_desde_binario(archivo_bin_titulos, &lista_t);

    } else {

        // --- CAMINO B: NO HAY BINARIOS. HAY QUE PROCESAR LOS CSV ---
        printf("[INFO] No se encontraron binarios para esta fecha. Procesando archivos CSV...\n");

        t_auditoria auditoria_miembros[20];
        int cant_errores_miembros = 0;
        t_auditoria auditoria_titulos[20];
        int cant_errores_titulos = 0;

        // 1. Procesamos y auditamos (Lo que ya programamos)
        procesar_archivo_miembros("Lotes Prueba/miembros.csv", auditoria_miembros, &cant_errores_miembros, &lista_m, &fecha_proceso);
        generar_reporte_auditoria("Resultados Auditoria/auditoria_miembros.txt", auditoria_miembros, cant_errores_miembros, "DNI");

        procesar_archivo_titulos("Lotes Prueba/titulos.csv", auditoria_titulos, &cant_errores_titulos, &lista_t);
        generar_reporte_auditoria("Resultados Auditoria/auditoria_titulos.txt", auditoria_titulos, cant_errores_titulos, "ID");

    }

    // =========================================================================

    printf("\n--- CARGA COMPLETADA ---\n");
    printf("Miembros listos para usar: %d\n", lista_m.cantidad);
    printf("Titulos listos para usar: %d\n", lista_t.cantidad);


    // =========================================================
    // 1. INICIALIZAR Y CARGAR ÍNDICE DE MIEMBROS
    // =========================================================
    t_indice indice_miembros;
    indice_miembros.vindice = NULL;
    indice_miembros.cantidad_elementos_actual = 0;
    indice_miembros.cantidad_elementos_maxima = 0;

    // Llamamos a la función que extrae los DNIs de la lista y arma las fichas
    generar_indice_miembros(&lista_m, &indice_miembros);

    // ORDENAMIENTO VITAL: Ordenamos el índice para habilitar Búsqueda Binaria
    if (indice_miembros.cantidad_elementos_actual > 0) {
        qsort(indice_miembros.vindice, indice_miembros.cantidad_elementos_actual, sizeof(t_reg_indice), cmp_miembros_dni);
    }

    // =========================================================
    // 2. INICIALIZAR Y CARGAR ÍNDICE DE TÍTULOS
    // =========================================================
    t_indice indice_titulos;
    indice_titulos.vindice = NULL;
    indice_titulos.cantidad_elementos_actual = 0;
    indice_titulos.cantidad_elementos_maxima = 0;

    // Llamamos a la función análoga para extraer los IDs de los títulos
    // (Asegúrate de haber creado esta función basándote en la de miembros)
    generar_indice_titulos(&lista_t, &indice_titulos);

    // ORDENAMIENTO VITAL
    if (indice_titulos.cantidad_elementos_actual > 0) {
        qsort(indice_titulos.vindice, indice_titulos.cantidad_elementos_actual, sizeof(t_reg_indice), cmp_titulos_id);
    }

    printf("Indices generados y ordenados correctamente.\n");

    // =========================================================
    // 3. TRANSFERIR EL CONTROL AL USUARIO (EL MENÚ)
    // =========================================================

    // Ahora le pasamos las listas llenas y los índices ordenados


    t_lista_alquileres lista_a; // REVISAR

    menu_operaciones(&lista_m, &indice_miembros, &lista_t, &indice_titulos, &lista_a, fecha_proceso);

    // =========================================================
    // 4. LIMPIEZA FINAL (Al salir del menú)
    // =========================================================
    if (lista_m.array != NULL) free(lista_m.array);
    if (indice_miembros.vindice != NULL) free(indice_miembros.vindice);
    if (lista_t.array != NULL) free(lista_t.array);
    if (indice_titulos.vindice != NULL) free(indice_titulos.vindice);

    return 0;
}
