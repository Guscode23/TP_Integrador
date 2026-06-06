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

    t_fecha fecha_proceso;

    char archivo_bin_miembros[50];
    char archivo_bin_titulos[50];

    t_lista_miembros lista_m = {NULL, 0, 0};
    t_lista_titulos lista_t = {NULL, 0, 0};
    t_lista_alquileres lista_a = {NULL, 0, 0};

    t_indice indice_miembros;
    t_indice indice_titulos;

    printf("------------------------\n------------------------\n\tCINEFILIA\n------------------------\n------------------------\n\n");

    solicitar_Fecha_Proceso(&fecha_proceso);

    sprintf(archivo_bin_miembros, "Archivos binarios/miembros_%02d%02d%04d.dat", fecha_proceso.dia, fecha_proceso.mes, fecha_proceso.anio);
    sprintf(archivo_bin_titulos, "Archivos binarios/titulos_%02d%02d%04d.dat", fecha_proceso.dia, fecha_proceso.mes, fecha_proceso.anio);


    FILE *verificador_binario = fopen(archivo_bin_miembros, "rb");

    if (verificador_binario != NULL) {

        fclose(verificador_binario);

        printf("\n[INFO] Archivos binarios detectados para la fecha seleccionada.\n");
        printf("\nCargando datos directamente desde archivos binarios...\n");

        cargar_miembros_desde_binario(archivo_bin_miembros, &lista_m);
        cargar_titulos_desde_binario(archivo_bin_titulos, &lista_t);

    } else {

        printf("[INFO] No se encontraron binarios para esta fecha.\n\nProcesando archivos CSV...\n");

        t_auditoria auditoria_miembros[20];
        int cant_errores_miembros = 0;
        t_auditoria auditoria_titulos[20];
        int cant_errores_titulos = 0;

        procesar_archivo_miembros("CSV/miembros.csv", auditoria_miembros, &cant_errores_miembros, &lista_m, &fecha_proceso);
        generar_reporte_auditoria("Auditoria/auditoria_miembros.txt", auditoria_miembros, cant_errores_miembros, "DNI");

        procesar_archivo_titulos("CSV/titulos.csv", auditoria_titulos, &cant_errores_titulos, &lista_t);
        generar_reporte_auditoria("Auditoria/auditoria_titulos.txt", auditoria_titulos, cant_errores_titulos, "ID");

        printf("\nSe genero archivo de auditoria para los registros invalidos\n\n");

    }

    indice_crear(&indice_miembros,MAX_REGISTROS,sizeof(t_reg_indice));
    indice_crear(&indice_titulos,MAX_REGISTROS,sizeof(t_reg_indice));

    generar_indice_miembros(&lista_m, &indice_miembros);
    generar_indice_titulos(&lista_t, &indice_titulos);

    menu_operaciones(&lista_m, &indice_miembros, &lista_t, &indice_titulos, &lista_a, &fecha_proceso);

    if (lista_m.array != NULL) free(lista_m.array);
    indice_vaciar(&indice_miembros);
    if (lista_t.array != NULL) free(lista_t.array);
    indice_vaciar(&indice_titulos);

    return 0;
}
