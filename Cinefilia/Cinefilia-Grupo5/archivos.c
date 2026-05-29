#include "archivos.h"
#include "Validaciones.h"

void procesar_archivo_miembros(const char *ruta_archivo, t_auditoria *arreglo_auditorias, int *cant_tipos_error) {
    FILE *archivo = fopen(ruta_archivo, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir %s.\n", ruta_archivo);
        return;
    }

    char linea[1024];
    int cantidadDNI = 0;
    int *idsDNI = NULL;

    fgets(linea, sizeof(linea), archivo); // Descartar cabecera

    // BUCLE PRINCIPAL (Por Fila)
    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = 0;

        bool registro_valido = true;
        int columna = 0;
        char motivo_error[50] = "";

        miembro miembro_temp;
        memset(&miembro_temp, 0, sizeof(miembro));

        char *resto_linea = linea;
        char *token;

        // BUCLE DE EXTRACCIÓN (Por Columna)
        while ((token = extraer_campo(&resto_linea, ";")) != NULL && registro_valido) {

            switch (columna) {
                case 0: // ESTACIÓN DNI
                    miembro_temp.dni = atol(token);
                    if (validar_campo(&miembro_temp, val_dni) == ERROR) {
                        strcpy(motivo_error, "DNI fuera de rango");
                        registro_valido = false;
                    }
                    else if(insertarEnVector(&idsDNI, &cantidadDNI, miembro_temp.dni) < 0) {
                        strcpy(motivo_error, "DNI duplicado");
                        registro_valido = false;
                    }
                    break;

                // case 1: // CUIL
                // case 2: // Apellidos y Nombres...
                // (Aquí agregarás el resto de tus case llamando a tus funciones)
            }
            columna++;
        }

        // VEREDICTO FINAL
        if (registro_valido && columna >= 1) { // Cambiar a >= 10 cuando tengas todas las columnas
            // ÉXITO: Aquí lo guardas en tu lista/arreglo final
            printf("Registro DNI %ld procesado con exito.\n", miembro_temp.dni);

        } else if (!registro_valido) {
           // --- INICIO LÓGICA DE AUDITORÍA ---
            bool error_encontrado = false;

            // ADVERTENCIA LÍNEA 55: Agregamos el * antes de cant_tipos_error
            for (int i = 0; i < *cant_tipos_error; i++) {

                if (strcmp(arreglo_auditorias[i].tipo_error, motivo_error) == 0) {
                    int indice_dni = arreglo_auditorias[i].cantidad_incidencias;
                    arreglo_auditorias[i].dnis_rechazados[indice_dni] = miembro_temp.dni;
                    arreglo_auditorias[i].cantidad_incidencias++;
                    error_encontrado = true;
                    break;
                }
            }

            if (!error_encontrado) {
                // ERRORES LÍNEA 66 a 68: Agregamos el * para usar el valor como índice
                strcpy(arreglo_auditorias[*cant_tipos_error].tipo_error, motivo_error);
                arreglo_auditorias[*cant_tipos_error].dnis_rechazados[0] = miembro_temp.dni;
                arreglo_auditorias[*cant_tipos_error].cantidad_incidencias = 1;

                // Y para sumarle 1, los paréntesis son OBLIGATORIOS por el orden de precedencia en C
                (*cant_tipos_error)++;
            }
            }
        }

    free(idsDNI);
    fclose(archivo);
}

// Extrae campos respetando los vacios (;;), reemplaza a strtok
char* extraer_campo(char **cadena, const char *delimitador) {
    if (*cadena == NULL) return NULL;
    char *inicio = *cadena;
    char *fin = strpbrk(inicio, delimitador);
    if (fin != NULL) {
        *fin = '\0';
        *cadena = fin + 1;
    } else {
        *cadena = NULL;
    }
    return inicio;
}

int validar_campo(void *dato, int (*funcion_validadora)(void *)) {
    return funcion_validadora(dato);
}

int val_dni(void *dato) {
    // 1. Desenmascaramos el dato
    miembro *m = (miembro *)dato;

    // 2. Aplicamos la regla de negocio (Ej: DNI entre 1 millón y 100 millones)
    if (m->dni > 1000000 && m->dni < 100000000) {
        return TODO_OK;
    }

    return ERROR;
}
