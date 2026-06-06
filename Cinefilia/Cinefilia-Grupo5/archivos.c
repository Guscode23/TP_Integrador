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

    fgets(linea, sizeof(linea), archivo);

    while (fgets(linea, sizeof(linea), archivo)) {
        *(linea + strcspn(linea, "\n")) = 0;

        bool registro_valido = true;
        int columna = 0;
        char motivo_error[50] = "";

        miembro miembro_temp;
        memset(&miembro_temp, 0, sizeof(miembro));

        char *resto_linea = linea;
        char *token;

        while ((token = extraer_campo(&resto_linea, ";")) != NULL && registro_valido) {

            switch (columna) {
                case 0:
                    miembro_temp.dni = atol(token);
                    if (validar_campo(&miembro_temp, validarDNI) == ERROR) {
                        strcpy(motivo_error, "DNI fuera de rango");
                        registro_valido = false;
                    }
                    else if(insertarEnVector(&idsDNI, &cantidadDNI, miembro_temp.dni) < 0) {
                        strcpy(motivo_error, "DNI duplicado");
                        registro_valido = false;
                    }
                    break;

                case 1:
                    strcpy(miembro_temp.CUIL, token);
                    break;

                case 2:
                    strcpy(miembro_temp.apeNom, token);
                    normalizarApel_Nombre(miembro_temp.apeNom);
                    if (strcmp(miembro_temp.apeNom, "") == 0){
                        strcpy(motivo_error, "Nombre y apellido vacio");
                        registro_valido = false;
                    }
                    break;

                case 3:
                    miembro_temp.fechNac = parsearFecha(token);
                    if(es_Fecha_Valida(&miembro_temp.fechNac) == ERROR){
                        strcpy(motivo_error, "Fecha de nacimiento invalida");
                        registro_valido = false;
                    }
                    else if(validarFechaNacimiento(&miembro_temp.fechNac, fecha_proceso) == ERROR){
                        strcpy(motivo_error, "Fecha de nacimiento invalida");
                        registro_valido = false;
                    }
                    break;

                case 4:
                    miembro_temp.sexo = token[0];
                    if (validar_campo(&miembro_temp, validarSexo) == ERROR) {
                        strcpy(motivo_error, "Sexo invalido");
                        registro_valido = false;
                    }
                    if (validar_campo(&miembro_temp, validarCUIL) == ERROR) {
                        strcpy(motivo_error, "CUIL invalido");
                        registro_valido = false;
                    }
                    break;

                case 5:
                    miembro_temp.fechAfil = parsearFecha(token);
                    if(es_Fecha_Valida(&miembro_temp.fechAfil) == ERROR){
                        strcpy(motivo_error, "Fecha de afiliacion invalida");
                        registro_valido = false;
                    }
                    else if(validarFechaAfiliacion(&miembro_temp.fechAfil,&miembro_temp.fechNac,fecha_proceso) == ERROR){
                        strcpy(motivo_error, "Fecha de afiliacion invalida");
                        registro_valido = false;
                    }
                    break;

                case 6:
                    strcpy(miembro_temp.cat, token);
                    edad = calcularEdad(fecha_proceso, &miembro_temp.fechNac);
                    if (validarCAT(miembro_temp.cat, edad) == ERROR) {
                        strcpy(motivo_error, "Categoria incorrecta");
                        registro_valido = false;
                    }
                    break;

                case 7:
                    miembro_temp.fechUltCuot = parsearFecha(token);
                    if(es_Fecha_Valida(&miembro_temp.fechUltCuot) == ERROR){
                        strcpy(motivo_error, "Fecha de ultima cuota paga invalida");
                        registro_valido = false;
                    }
                    else if(validar_UltimaCuota_Paga(&miembro_temp.fechAfil,&miembro_temp.fechUltCuot,fecha_proceso) == ERROR){
                        strcpy(motivo_error, "Fecha de ultima cuota paga invalida");
                        registro_valido = false;
                    }
                    break;

                case 8:
                    miembro_temp.estado = token[0];
                    if (validar_campo(&miembro_temp, validarEstado) == ERROR) {
                        strcpy(motivo_error, "Estado invalido");
                        registro_valido = false;
                    }
                    break;

                case 9:
                    strcpy(miembro_temp.plan, token);
                    if (validar_campo(&miembro_temp, validarPlan) == ERROR) {
                        strcpy(motivo_error, "Plan invalido");
                        registro_valido = false;
                    }
                    break;

                case 10:
                    strcpy(miembro_temp.emailTutor, token);
                    if (strcmp(miembro_temp.cat, "MENOR") == 0){
                        if (validar_campo(&miembro_temp, validarCorreo) == ERROR) {
                            strcpy(motivo_error, "Correo invalido");
                            registro_valido = false;
                        }
                    }

                    break;
            }
            columna++;
        }

        if (registro_valido && columna >= 11) {

            if (lista_validos->cantidad == lista_validos->capacidad) {
                int nueva_capacidad = (lista_validos->capacidad == 0) ? 10 : lista_validos->capacidad * 2;
                miembro *temp = (miembro *)realloc(lista_validos->array, nueva_capacidad * sizeof(miembro));
                if (temp == NULL) {
                    printf("Error fatal: No hay memoria suficiente.\n");
                    break;
                }
                lista_validos->array = temp;
                lista_validos->capacidad = nueva_capacidad;
            }

            *(lista_validos->array + lista_validos->cantidad) = miembro_temp;
            lista_validos->cantidad++;
        }

        else if (!registro_valido) {
            bool error_encontrado = false;
            for (int i = 0; i < *cant_tipos_error; i++) {
                if (strcmp((arreglo_auditorias + i)->tipo_error, motivo_error) == 0) {
                    int indice_dni = (*(arreglo_auditorias+ i)).cantidad_incidencias;
                    *((*(arreglo_auditorias + i)).identificadores_rechazados + indice_dni) = miembro_temp.dni;
                    (*(arreglo_auditorias + i)).cantidad_incidencias++;
                    error_encontrado = true;
                    break;
                }
            }

            if (!error_encontrado) {
              strcpy((*(arreglo_auditorias + *cant_tipos_error)).tipo_error, motivo_error);
              *((*(arreglo_auditorias + *cant_tipos_error)).identificadores_rechazados + 0) = miembro_temp.dni;
              (*(arreglo_auditorias + *cant_tipos_error)).cantidad_incidencias = 1;
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

    fgets(linea, sizeof(linea), archivo);

    while (fgets(linea, sizeof(linea), archivo)) {

        *(linea + strcspn(linea, "\n")) = 0;

        bool registro_valido = true;
        int columna = 0;
        char motivo_error[50] = "";

        titulo titulo_temp;
        memset(&titulo_temp, 0, sizeof(titulo));

        char *resto_linea = linea;
        char *token;

        while ((token = extraer_campo(&resto_linea, ";")) != NULL && registro_valido) {

            switch (columna) {
                case 0:
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

                case 1:
                    strcpy(titulo_temp.titulo, token);
                    normalizarTitulo(titulo_temp.titulo);
                    if (strcmp(titulo_temp.titulo, "") == 0){
                        strcpy(motivo_error, "Titulo vacio");
                        registro_valido = false;
                    }
                    break;

                case 2:
                    strcpy(titulo_temp.genero, token);
                    if (validar_campo(&titulo_temp, validarGenero) == ERROR) {
                        strcpy(motivo_error, "Genero invalido");
                        registro_valido = false;
                    }
                    break;

                case 3:
                    titulo_temp.stock = atoi(token);
                    validarStock(&titulo_temp.stock);
                    break;
            }
            columna++;
        }

        if (registro_valido && columna >= 4) {

            if (lista_validos->cantidad == lista_validos->capacidad) {
                int nueva_capacidad = (lista_validos->capacidad == 0) ? 10 : lista_validos->capacidad * 2;
                titulo *temp = (titulo *)realloc(lista_validos->array, nueva_capacidad * sizeof(titulo));

                if (temp == NULL) {
                    printf("Error fatal: No hay memoria suficiente para titulos.\n");
                    break;
                }
                lista_validos->array = temp;
                lista_validos->capacidad = nueva_capacidad;
            }

            *(lista_validos->array + lista_validos->cantidad) = titulo_temp;
            lista_validos->cantidad++;
        }

         else if (!registro_valido) {
            bool error_encontrado = false;
            for (int i = 0; i < *cant_tipos_error; i++) {
                if (strcmp(arreglo_auditorias[i].tipo_error, motivo_error) == 0) {
                    int indice_id = (*(arreglo_auditorias + i)).cantidad_incidencias;
                    *((*(arreglo_auditorias + i)).identificadores_rechazados + indice_id) = (long)titulo_temp.ID;
                    (*(arreglo_auditorias + i)).cantidad_incidencias++;
                    error_encontrado = true;
                    break;
                }
            }

           if (!error_encontrado) {
             strcpy((*(arreglo_auditorias + *cant_tipos_error)).tipo_error, motivo_error);
             *((*(arreglo_auditorias + *cant_tipos_error)).identificadores_rechazados + 0) = (long)titulo_temp.ID;
             (*(arreglo_auditorias + *cant_tipos_error)).cantidad_incidencias = 1;
             (*cant_tipos_error)++;
           }
        }
    }

    free(idsTitulos);
    fclose(archivo);
}

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
