#include "archivos.h"
#include "Validaciones.h"

void procesar_archivo_miembros(const char *ruta_archivo, t_auditoria *arreglo_auditorias, int *cant_tipos_error, t_lista_miembros *lista_validos) {
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
        if (registro_valido && columna >= 1) {

            // --- INICIO MEMORIA DINÁMICA ---
            // Si la cantidad alcanzó la capacidad máxima, necesitamos agrandar el arreglo
            if (lista_validos->cantidad == lista_validos->capacidad) {

                // Si la capacidad era 0, arrancamos con 10. Si no, la duplicamos.
                int nueva_capacidad = (lista_validos->capacidad == 0) ? 10 : lista_validos->capacidad * 2;

                // Pedimos la nueva memoria
                miembro *temp = (miembro *)realloc(lista_validos->array, nueva_capacidad * sizeof(miembro));

                if (temp == NULL) {
                    printf("Error fatal: No hay memoria suficiente.\n");
                    // Aquí deberías manejar el error, por ahora salimos
                    break;
                }

                // Actualizamos nuestro contenedor con la nueva memoria y capacidad
                lista_validos->array = temp;
                lista_validos->capacidad = nueva_capacidad;
            }
            // --- FIN MEMORIA DINÁMICA ---

            // 1. Guardamos el struct temporal en la posición actual del arreglo dinámico
            lista_validos->array[lista_validos->cantidad] = miembro_temp;

            // 2. Sumamos 1 al contador
            lista_validos->cantidad++;

            printf("Registro DNI %ld procesado con exito.\n", miembro_temp.dni);

        }

        else if (!registro_valido) {
           // --- INICIO LÓGICA DE AUDITORÍA ---
            bool error_encontrado = false;

            // ADVERTENCIA LÍNEA 55: Agregamos el * antes de cant_tipos_error
            for (int i = 0; i < *cant_tipos_error; i++) {

                if (strcmp(arreglo_auditorias[i].tipo_error, motivo_error) == 0) {
                    int indice_dni = arreglo_auditorias[i].cantidad_incidencias;
                    arreglo_auditorias[i].identificadores_rechazados[indice_dni] = miembro_temp.dni;
                    arreglo_auditorias[i].cantidad_incidencias++;
                    error_encontrado = true;
                    break;
                }
            }

            if (!error_encontrado) {
                // ERRORES LÍNEA 66 a 68: Agregamos el * para usar el valor como índice
                strcpy(arreglo_auditorias[*cant_tipos_error].tipo_error, motivo_error);
                arreglo_auditorias[*cant_tipos_error].identificadores_rechazados[0] = miembro_temp.dni;
                arreglo_auditorias[*cant_tipos_error].cantidad_incidencias = 1;

                // Y para sumarle 1, los paréntesis son OBLIGATORIOS por el orden de precedencia en C
                (*cant_tipos_error)++;
            }
            }
        }

    free(idsDNI);
    fclose(archivo);
}

void procesar_archivo_titulos(const char *ruta_archivo, t_auditoria *arreglo_auditorias, int *cant_tipos_error, t_lista_titulos *lista_validos) {
    FILE *archivo = fopen(ruta_archivo, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir %s.\n", ruta_archivo);
        return;
    }

    char linea[1024];
    int cantidadPeliculas = 0;
    int *idsPeliculas = NULL;

    fgets(linea, sizeof(linea), archivo); // Descartar cabecera ("ID Pelicula;Titulo;...")

    // BUCLE PRINCIPAL (Por Fila)
    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = 0; // Limpiar salto de línea

        bool registro_valido = true;
        int columna = 0;
        char motivo_error[50] = "";

        // Estructura temporal específica para Títulos
        pelicula pelicula_temp;
        memset(&pelicula_temp, 0, sizeof(pelicula));

        char *resto_linea = linea;
        char *token;

        // BUCLE DE EXTRACCIÓN (Por Columna)
        while ((token = extraer_campo(&resto_linea, ";")) != NULL && registro_valido) {

            switch (columna) {
                case 0: // ID
                    pelicula_temp.ID = atol(token);
                    if(insertarEnVector(&idsPeliculas, &cantidadPeliculas, pelicula_temp.ID) == INSERCION_DUPLICADA) {
                        strcpy(motivo_error, "ID duplicado");
                        registro_valido = false;
                    }
                    else if(insertarEnVector(&idsPeliculas, &cantidadPeliculas, pelicula_temp.ID) == INSERCION_INVALIDA) {
                        strcpy(motivo_error, "ID invalido");
                        registro_valido = false;
                    }
                    break;

                case 1: // TITULO
                    strcpy(pelicula_temp.titulo, token);
                    printf("Se recibe: %s\n", pelicula_temp.titulo);
                    normalizarTitulo(pelicula_temp.titulo);
                    printf("Se transforma a: %s\n", pelicula_temp.titulo);
                    break;

                case 2: // GENERO
                    strcpy(pelicula_temp.genero, token);
                    if (validar_campo(&pelicula_temp, validarGenero) == ERROR) {
                        strcpy(motivo_error, "Genero invalido");
                        registro_valido = false;
                    }
                    break;

                case 3: // Stock
                    pelicula_temp.stock = atoi(token);
                    validarStock(&pelicula_temp.stock);
                    break;
            }
            columna++;
        }

        // VEREDICTO FINAL
        if (registro_valido && columna >= 4) {

            // --- INICIO MEMORIA DINÁMICA ---
            // Si la cantidad alcanzó la capacidad máxima, necesitamos agrandar el arreglo
            if (lista_validos->cantidad == lista_validos->capacidad) {

                // Si la capacidad era 0, arrancamos con 10. Si no, la duplicamos.
                int nueva_capacidad = (lista_validos->capacidad == 0) ? 10 : lista_validos->capacidad * 2;

                // Pedimos la nueva memoria (¡Usamos titulo aquí!)
                pelicula *temp = (pelicula *)realloc(lista_validos->array, nueva_capacidad * sizeof(pelicula));

                if (temp == NULL) {
                    printf("Error fatal: No hay memoria suficiente para titulos.\n");
                    // Salimos del bucle si explota la RAM
                    break;
                }

                // Actualizamos nuestro contenedor con la nueva memoria y capacidad
                lista_validos->array = temp;
                lista_validos->capacidad = nueva_capacidad;
            }
            // --- FIN MEMORIA DINÁMICA ---

            // 1. Guardamos el struct temporal en la posición actual del arreglo dinámico
            lista_validos->array[lista_validos->cantidad] = pelicula_temp;

            // 2. Sumamos 1 al contador
            lista_validos->cantidad++;

            // Cambiamos el mensaje para reflejar que es un Título y usamos el ID (entero)
            printf("ID %d, titulo: %s, genero: %s, stock: %d procesado con exito.\n", pelicula_temp.ID, pelicula_temp.titulo, pelicula_temp.genero, pelicula_temp.stock);
            //printf("Titulo: %s procesado con exito.\n", pelicula_temp.titulo);

        }

         else if (!registro_valido) {
            // ERROR: Lógica de Auditoría reutilizada
            bool error_encontrado = false;

            for (int i = 0; i < *cant_tipos_error; i++) {
                if (strcmp(arreglo_auditorias[i].tipo_error, motivo_error) == 0) {
                    int indice_id = arreglo_auditorias[i].cantidad_incidencias;

                    // Guardamos el ID (se convierte a long automáticamente)
                    arreglo_auditorias[i].identificadores_rechazados[indice_id] = (long)pelicula_temp.ID;

                    arreglo_auditorias[i].cantidad_incidencias++;
                    error_encontrado = true;
                    break;
                }
            }

            if (!error_encontrado) {
                strcpy(arreglo_auditorias[*cant_tipos_error].tipo_error, motivo_error);
                arreglo_auditorias[*cant_tipos_error].identificadores_rechazados[0] = (long)pelicula_temp.ID;
                arreglo_auditorias[*cant_tipos_error].cantidad_incidencias = 1;
                (*cant_tipos_error)++;
            }
        }
    }

    free(idsPeliculas);
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

int val_dni(void *dato) {
    // 1. Desenmascaramos el dato
    miembro *m = (miembro *)dato;

    // 2. Aplicamos la regla de negocio (Ej: DNI entre 1 millón y 100 millones)
    if (m->dni > 1000000 && m->dni < 100000000) {
        return TODO_OK;
    }

    return ERROR;
}
