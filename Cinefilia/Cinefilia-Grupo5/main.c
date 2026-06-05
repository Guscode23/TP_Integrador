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

// =========================================================================
// FUNCIÓN DE DEBUG: MOSTRAR EL ESTADO DE UN ÍNDICE EN MEMORIA
// =========================================================================
void mostrar_indice(t_indice *indice, const char *nombre_indice) {
    printf("\n==================================================\n");
    printf("           ESTADO DEL INDICE: %s\n", nombre_indice);
    printf("==================================================\n");

    if (indice->cantidad_elementos_actual == 0 || indice->vindice == NULL) {
        printf("-> El indice esta vacio o no ha sido inicializado.\n");
        printf("==================================================\n");
        return;
    }

    t_reg_indice *fichas = (t_reg_indice *)indice->vindice;

    printf("%-10s | %-15s | %-15s\n", "POSICION", "CLAVE (DNI/ID)", "NRO REG (FISICO)");
    printf("--------------------------------------------------\n");

    for (unsigned i = 0; i < indice->cantidad_elementos_actual; i++) {
        printf("Idx[%-4u]  | %-15ld | %-15d\n",
               i,
               fichas[i].dni,
               fichas[i].nro_reg);
    }

    printf("--------------------------------------------------\n");
    printf("Total de elementos en el indice: %u\n", indice->cantidad_elementos_actual);
    printf("==================================================\n");
}

int main() {
    printf("--- INICIANDO SISTEMA DE MIGRACION DE DATOS ---\n\n");

    t_fecha fecha_proceso;
    solicitar_Fecha_Proceso(&fecha_proceso);
    printf("\n");

    char archivo_bin_miembros[50];
    char archivo_bin_titulos[50];

    sprintf(archivo_bin_miembros, "miembros_%02d%02d%04d.dat", fecha_proceso.dia, fecha_proceso.mes, fecha_proceso.anio);
    sprintf(archivo_bin_titulos, "titulos_%02d%02d%04d.dat", fecha_proceso.dia, fecha_proceso.mes, fecha_proceso.anio);

    t_lista_miembros lista_m = {NULL, 0, 0};
    t_lista_titulos lista_t = {NULL, 0, 0};
    t_lista_alquileres lista_a = {NULL, 0, 0};

    FILE *verificador_binario = fopen(archivo_bin_miembros, "rb");

    if (verificador_binario != NULL) {

        fclose(verificador_binario);

        printf("[INFO] Archivos binarios detectados para la fecha seleccionada.\n");
        printf("Cargando datos directamente desde %s y %s...\n", archivo_bin_miembros, archivo_bin_titulos);

        cargar_miembros_desde_binario(archivo_bin_miembros, &lista_m);
        cargar_titulos_desde_binario(archivo_bin_titulos, &lista_t);

    } else {

        printf("[INFO] No se encontraron binarios para esta fecha. Procesando archivos CSV...\n");

        t_auditoria auditoria_miembros[20];
        int cant_errores_miembros = 0;
        t_auditoria auditoria_titulos[20];
        int cant_errores_titulos = 0;

        procesar_archivo_miembros("Lotes Prueba/miembros.csv", auditoria_miembros, &cant_errores_miembros, &lista_m, &fecha_proceso);
        generar_reporte_auditoria("Resultados Auditoria/auditoria_miembros.txt", auditoria_miembros, cant_errores_miembros, "DNI");

        procesar_archivo_titulos("Lotes Prueba/titulos.csv", auditoria_titulos, &cant_errores_titulos, &lista_t);
        generar_reporte_auditoria("Resultados Auditoria/auditoria_titulos.txt", auditoria_titulos, cant_errores_titulos, "ID");

    }

    printf("\n--- CARGA COMPLETADA ---\n");
    printf("Miembros listos para usar: %d\n", lista_m.cantidad);
    printf("Titulos listos para usar: %d\n", lista_t.cantidad);

    t_indice indice_miembros;
    t_indice indice_titulos;

    indice_crear(&indice_miembros,MAX_REGISTROS,sizeof(t_reg_indice));
    indice_crear(&indice_titulos,MAX_REGISTROS,sizeof(t_reg_indice));

    generar_indice_miembros(&lista_m, &indice_miembros);
    generar_indice_titulos(&lista_t, &indice_titulos);

    printf("Indices generados y ordenados correctamente.\n");

    mostrar_indice(&indice_miembros, "MIEMBROS");
    mostrar_indice(&indice_titulos, "TITULOS");

    menu_operaciones(&lista_m, &indice_miembros, &lista_t, &indice_titulos, &lista_a, &fecha_proceso);

    if (lista_m.array != NULL) free(lista_m.array);
    indice_vaciar(&indice_miembros);
    if (lista_t.array != NULL) free(lista_t.array);
    indice_vaciar(&indice_titulos);

    return 0;
}
