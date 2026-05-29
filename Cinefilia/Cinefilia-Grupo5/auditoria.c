#include "auditoria.h"

void generar_reporte_auditoria(const char *ruta_txt, t_auditoria *arreglo_auditorias, int cant_tipos_error) {
    FILE *archivo_salida = fopen(ruta_txt, "w");
    if (archivo_salida == NULL) return;

    fprintf(archivo_salida, "========================================\n");
    fprintf(archivo_salida, "      REPORTE DE AUDITORIA DE DATOS     \n");
    fprintf(archivo_salida, "========================================\n\n");

    if (cant_tipos_error == 0) {
        fprintf(archivo_salida, "No se encontraron registros invalidos.\n");
    } else {
        for (int i = 0; i < cant_tipos_error; i++) {
            fprintf(archivo_salida, "Motivo de rechazo: %s\n", arreglo_auditorias[i].tipo_error);
            fprintf(archivo_salida, "Cantidad de incidencias: %d\n", arreglo_auditorias[i].cantidad_incidencias);
            fprintf(archivo_salida, "Registros afectados (DNI):\n");

            for (int j = 0; j < arreglo_auditorias[i].cantidad_incidencias; j++) {
                fprintf(archivo_salida, "  - %ld\n", arreglo_auditorias[i].dnis_rechazados[j]);
            }
            fprintf(archivo_salida, "----------------------------------------\n");
        }
    }

    fclose(archivo_salida);
    printf("\nReporte de auditoria generado en: %s\n", ruta_txt);
}


