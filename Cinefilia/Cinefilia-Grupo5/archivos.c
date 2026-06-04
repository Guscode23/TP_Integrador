#include "archivos.h"
#include "Validaciones.h"

void procesar_archivo_miembros(const char *ruta_archivo, t_auditoria *arreglo_auditorias, int *cant_tipos_error, t_lista_miembros *lista_validos, t_fecha *fecha_proceso) {
    FILE *archivo = fopen(ruta_archivo, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir %s.\n", ruta_archivo);
        return;
    }

    char linea[1024];
    int cantidadDNI = 0;
    int *idsDNI = NULL;
    int edad;

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
                case 0: // DNI
                    miembro_temp.dni = atol(token);
                    if (validar_campo(&miembro_temp, validarDNI) == ERROR) {
                        printf("DNI fuera de rango\n\n");
                        strcpy(motivo_error, "DNI fuera de rango");
                        registro_valido = false;
                    }
                    else if(insertarEnVector(&idsDNI, &cantidadDNI, miembro_temp.dni) < 0) {
                        printf("DNI duplicado\n\n");
                        strcpy(motivo_error, "DNI duplicado");
                        registro_valido = false;
                    }
                    break;

                case 1: // CUIL
                    strcpy(miembro_temp.CUIL, token);
                    break;

                case 2: // Apellidos y Nombres
                    strcpy(miembro_temp.apeNom, token);
                    printf("Se recibe: %s\n", miembro_temp.apeNom);
                    normalizarApel_Nombre(miembro_temp.apeNom);
                    printf("Se transforma a: %s\n", miembro_temp.apeNom);
                    if (strcmp(miembro_temp.apeNom, "") == 0){
                        strcpy(motivo_error, "Nombre y apellido vacio");
                        printf("Nombre vacio\n\n");
                        registro_valido = false;
                    }
                    break;

                case 3: // Fecha de Nacimiento
                    miembro_temp.fechNac = parsearFecha(token);
                    if(es_Fecha_Valida(&miembro_temp.fechNac) == ERROR){
                        //printf("Error en fecha valida");
                        strcpy(motivo_error, "Fecha de nacimiento invalida");
                        registro_valido = false;
                    }
                    else if(validarFechaNacimiento(&miembro_temp.fechNac, fecha_proceso) == ERROR){
                        //printf("Error en comparacion de fecha");
                        strcpy(motivo_error, "Fecha de nacimiento invalida");
                        registro_valido = false;
                    }
                    break;

                case 4: // Sexo
                    miembro_temp.sexo = token[0];
                    if (validar_campo(&miembro_temp, validarSexo) == ERROR) {
                        printf("Error en sexo\n\n");
                        strcpy(motivo_error, "Sexo invalido");
                        registro_valido = false;
                    }
                    if (validar_campo(&miembro_temp, validarCUIL) == ERROR) {
                        printf("Error en CUIL\n\n");
                        strcpy(motivo_error, "CUIL invalido");
                        registro_valido = false;
                    }
                    break;

                case 5: // Fecha de Afiliación
                    miembro_temp.fechAfil = parsearFecha(token);
                    if(es_Fecha_Valida(&miembro_temp.fechAfil) == ERROR){
                        printf("Error en fecha valida de afiliacion 1\n\n");
                        strcpy(motivo_error, "Fecha de afiliacion invalida");
                        registro_valido = false;
                    }
                    else if(validarFechaAfiliacion(&miembro_temp.fechAfil,&miembro_temp.fechNac,fecha_proceso) == ERROR){
                        printf("Error en fecha valida de afiliacion 2\n\n");
                        strcpy(motivo_error, "Fecha de afiliacion invalida");
                        registro_valido = false;
                    }
                    break;

                case 6: // Categoria
                    strcpy(miembro_temp.cat, token);
                    edad = calcularEdad(fecha_proceso, &miembro_temp.fechNac);
                    //printf("La edad es: %d\n", edad);
                    if (validarCAT(miembro_temp.cat, edad) == ERROR) {
                        printf("Error en categoria\n\n");
                        strcpy(motivo_error, "Categoria incorrecta");
                        registro_valido = false;
                    }
                    break;

                case 7: // Fecha de última cuota paga
                    miembro_temp.fechUltCuot = parsearFecha(token);
                    if(es_Fecha_Valida(&miembro_temp.fechUltCuot) == ERROR){
                        printf("Error en 1ra validacion de fecha de ult cuota\n\n");
                        strcpy(motivo_error, "Fecha de ultima cuota paga invalida");
                        registro_valido = false;
                    }
                    else if(validar_UltimaCuota_Paga(&miembro_temp.fechAfil,&miembro_temp.fechUltCuot,fecha_proceso) == ERROR){
                        printf("Error en 2da validacion de fecha de ult cuota\n\n");
                        strcpy(motivo_error, "Fecha de ultima cuota paga invalida");
                        registro_valido = false;
                    }
                    break;

                case 8: // Estado
                    miembro_temp.estado = token[0];
                    if (validar_campo(&miembro_temp, validarEstado) == ERROR) {
                        printf("Error en validacion de fecha de estado\n\n");
                        strcpy(motivo_error, "Estado invalido");
                        registro_valido = false;
                    }
                    break;

                case 9: // Plan
                    strcpy(miembro_temp.plan, token);
                    if (validar_campo(&miembro_temp, validarPlan) == ERROR) {
                        printf("Error en validacion de fecha de plan\n\n");
                        strcpy(motivo_error, "Plan invalido");
                        registro_valido = false;
                    }
                    break;

                case 10: // Email tutor
                    strcpy(miembro_temp.emailTutor, token);
                    if (strcmp(miembro_temp.cat, "MENOR") == 0){
                        if (validar_campo(&miembro_temp, validarCorreo) == ERROR) {
                            printf("Error en validacion de mail\n\n");
                            strcpy(motivo_error, "Correo invalido");
                            registro_valido = false;
                        }
                    }

                    break;
            }
            columna++;
        }
        // VEREDICTO FINAL
        if (registro_valido && columna >= 11) {

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
    int cantidadTitulos = 0;
    int *idsTitulos = NULL;

    fgets(linea, sizeof(linea), archivo); // Descartar cabecera ("ID Pelicula;Titulo;...")

    // BUCLE PRINCIPAL (Por Fila)
    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = 0; // Limpiar salto de línea

        bool registro_valido = true;
        int columna = 0;
        char motivo_error[50] = "";

        // Estructura temporal específica para Títulos (CORREGIDO A titulo)
        titulo titulo_temp;
        memset(&titulo_temp, 0, sizeof(titulo));

        char *resto_linea = linea;
        char *token;

        // BUCLE DE EXTRACCIÓN (Por Columna)
        while ((token = extraer_campo(&resto_linea, ";")) != NULL && registro_valido) {

            switch (columna) {
                case 0: // ID
                    titulo_temp.ID = atol(token);
                    if(insertarEnVector(&idsTitulos, &cantidadTitulos, titulo_temp.ID) == INSERCION_DUPLICADA) {
                        strcpy(motivo_error, "ID duplicado");
                        registro_valido = false;
                    }
                    else if(insertarEnVector(&idsTitulos, &cantidadTitulos, titulo_temp.ID) == INSERCION_INVALIDA) {
                        strcpy(motivo_error, "ID invalido");
                        registro_valido = false;
                    }
                    break;

                case 1: // TITULO
                    strcpy(titulo_temp.titulo, token);
                    normalizarTitulo(titulo_temp.titulo);
                    if (strcmp(titulo_temp.titulo, "") == 0){
                        strcpy(motivo_error, "Titulo vacio");
                        printf("Titulo vacio\n\n");
                        registro_valido = false;
                    }
                    break;

                case 2: // GENERO
                    strcpy(titulo_temp.genero, token);
                    if (validar_campo(&titulo_temp, validarGenero) == ERROR) {
                        strcpy(motivo_error, "Genero invalido");
                        registro_valido = false;
                    }
                    break;

                case 3: // Stock
                    titulo_temp.stock = atoi(token);
                    validarStock(&titulo_temp.stock);
                    break;
            }
            columna++;
        }

        // VEREDICTO FINAL
        if (registro_valido && columna >= 4) {

            // --- INICIO MEMORIA DINÁMICA ---
            if (lista_validos->cantidad == lista_validos->capacidad) {
                int nueva_capacidad = (lista_validos->capacidad == 0) ? 10 : lista_validos->capacidad * 2;

                // Pedimos la nueva memoria (CORREGIDO A titulo)
                titulo *temp = (titulo *)realloc(lista_validos->array, nueva_capacidad * sizeof(titulo));

                if (temp == NULL) {
                    printf("Error fatal: No hay memoria suficiente para titulos.\n");
                    break;
                }

                lista_validos->array = temp;
                lista_validos->capacidad = nueva_capacidad;
            }
            // --- FIN MEMORIA DINÁMICA ---

            // 1. Guardamos el struct temporal
            lista_validos->array[lista_validos->cantidad] = titulo_temp;

            // 2. Sumamos 1 al contador
            lista_validos->cantidad++;

            printf("ID %d, titulo: %s, genero: %s, stock: %d procesado con exito.\n",
                   titulo_temp.ID, titulo_temp.titulo, titulo_temp.genero, titulo_temp.stock);
        }

         else if (!registro_valido) {
            // ERROR: Lógica de Auditoría reutilizada
            bool error_encontrado = false;

            for (int i = 0; i < *cant_tipos_error; i++) {
                if (strcmp(arreglo_auditorias[i].tipo_error, motivo_error) == 0) {
                    int indice_id = arreglo_auditorias[i].cantidad_incidencias;
                    arreglo_auditorias[i].identificadores_rechazados[indice_id] = (long)titulo_temp.ID;
                    arreglo_auditorias[i].cantidad_incidencias++;
                    error_encontrado = true;
                    break;
                }
            }

            if (!error_encontrado) {
                strcpy(arreglo_auditorias[*cant_tipos_error].tipo_error, motivo_error);
                arreglo_auditorias[*cant_tipos_error].identificadores_rechazados[0] = (long)titulo_temp.ID;
                arreglo_auditorias[*cant_tipos_error].cantidad_incidencias = 1;
                (*cant_tipos_error)++;
            }
        }
    }

    free(idsTitulos);
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
