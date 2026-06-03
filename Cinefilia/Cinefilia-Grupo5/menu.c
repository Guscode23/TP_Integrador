#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "Validaciones.h"
#include <string.h>

#define NO_EXISTE -1


/*char iniciarMenu();
char menuConErr(const char *mensaje, const char *opciones);
void menu_operaciones(char opcion);


int main(){

    char opcion;

    do{
        opcion = iniciarMenu();
        //menu_operaciones(&lista_m, &lista_t);
    }while (toupper(opcion) != 'K');

    fflush(stdin);

    return 0;
}*/

char iniciarMenu(){

    char opcion;
    opcion = menuConErr ("Elija una opcion \n\n"
                         "A - Alta de miembro\n"
                         "B - Alta de un titulo\n"
                         "C - Baja de un miembro\n"
                         "D - Baja de un titulo\n"
                         "E - Modificacion de un miembro\n"
                         "F - Modificacion de un titulo\n"
                         "G - Mostrar informacion de un miembro\n"
                         "H - Alquiler de un titulo\n"
                         "I - Listado de miembros ordenados por DNI\n"
                         "J - Listado miembros por Plan\n"
                         "K - Salir\n",
                         "ABCDEFGHIJKabcdefghik"
                         );
    opcion = toupper(opcion);
    printf("\nOpcion elegida: %c\n\n", opcion);

    return opcion;
}

char menuConErr(const char *mensaje, const char *opciones){

    char esOpcion;
    int priVez = 1;

    do{
        printf("%s%s", priVez ? priVez = 0, "" : "ERROR - OPCION NO VALIDA.\n",mensaje);
        fflush(stdin);
        scanf("%c", &esOpcion);
       }while(strchr(opciones, esOpcion)==NULL);

    return esOpcion;
}


void menu_operaciones(char opcion){

    switch (toupper(opcion))
    {
    case 'A':
        //altaMiembro();
        break;
    case 'B':
        //altaTitulo();
        break;
    case 'C':
        //bajaMiembro();
        break;
    case 'D':
        //bajaTitulo();
        break;
    case 'E':
        //modificarMiembro();
        break;
    case 'F':
        //modificartitulo();
        break;
    case 'G':
        //mostrarInfoMiembro();
        break;
    case 'H':
        //alquilerTitulo();
        break;
    case 'I':
        //listarMiembrosPorDNI();
        break;
    case 'J':
        //listarMiembrosPorPlan();
        break;
    case 'K':
        printf("Saliendo del sistema...\n");
        break;
    default:
        printf("Opcion no valida.\n");
        break;
    }
}

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int cmpDNI(const void* d1, const void* d2)
{
  long int dif= *(long int*)d1 - *(long int*)d2;
  return dif;

}

int cmp_titulos_id(const void *a, const void *b) {
    const t_reg_indice *regA = (const t_reg_indice *)a;
    const t_reg_indice *regB = (const t_reg_indice *)b;

    if (regA->dni < regB->dni) return -1;
    if (regA->dni > regB->dni) return 1;
    return 0;
}

int cmp_miembros_dni(const void *a, const void *b) {
    const t_reg_indice *regA = (const t_reg_indice *)a;
    const t_reg_indice *regB = (const t_reg_indice *)b;

    if (regA->dni < regB->dni) return -1;
    if (regA->dni > regB->dni) return 1;
    return 0;
}

void altaMiembro(miembro *miembroOficial,t_indice* indice,t_fecha* fechProceso) {

  miembro miemTemp; ///Variable temporal de miembros que ira guardando los datos ingresados por teclado
  int pasoAlta = 1;
  int opcionPlan;

    printf("\n--- FORMULARIO DE ALTA: MIEMBRO ---\n");

    while (pasoAlta > 0 && pasoAlta <= 10) {
        switch (pasoAlta) {
            case 1:
                printf("Ingrese DNI: ");
                if (scanf("%ld", &miemTemp.dni) != 1) {
                    limpiarBuffer();
                    printf("[ERROR] Entrada de DNI invalida.\n");
                    pasoAlta = -1;
                    break;
                }
                limpiarBuffer();

                if (indice_buscar(indice,&miemTemp.dni,indice->cantidad_elementos_actual,sizeof(long int),cmpDNI)!=NO_EXISTE) {
                    printf("[ERROR] El DNI ya existe en el indice. Operacion cancelada.\n");
                    pasoAlta = -1;
                    break;
                }

                pasoAlta++;
                break;

            case 2:
                printf("Ingrese CUIL: ");
                fgets(miemTemp.CUIL, sizeof(miemTemp.CUIL), stdin);

                if(validarCUIL(miemTemp.CUIL)<0){
                    printf("Error al ingresar CUIL");
                    pasoAlta-=1;
                    break;
                }

                pasoAlta++;
                break;

            case 3:
                printf("Ingrese Apellidos y Nombres: ");
                fgets(miemTemp.apeNom, sizeof(miemTemp.apeNom), stdin);

                normalizarApel_Nombre(miemTemp.apeNom);

                pasoAlta++;
                break;

            case 4:
                printf("Ingrese Fecha de Nacimiento (DD MM AAAA): ");
                if (scanf("%d %d %d", &miemTemp.fechNac.dia, &miemTemp.fechNac.mes, &miemTemp.fechNac.anio) != 3) {
                    limpiarBuffer();
                    printf("[ERROR] Formato de fecha invalido.\n");
                    pasoAlta = -1;
                    break;
                }
                limpiarBuffer();

                ///LLamar a función de validar Fecha de Nacimiento

                pasoAlta++;
                break;

            case 5:
                printf("Ingrese Sexo ('F', 'M', 'O'): ");
                scanf("%c", &miemTemp.sexo);
                limpiarBuffer();

                if(validarSexo(&miemTemp.sexo)<0){
                    printf("Sexo inválido");
                    pasoAlta-=1;
                    break;
                }

                pasoAlta++;
                break;

            case 6:
                printf("Ingrese Fecha de Afiliacion (DD MM AAAA): ");
                if (scanf("%d %d %d", &miemTemp.fechAfil.dia, &miemTemp.fechAfil.mes, &miemTemp.fechAfil.anio) != 3) {
                    limpiarBuffer();
                    printf("[ERROR] Formato de fecha invalido.\n");
                    pasoAlta = -1;
                    break;
                }
                limpiarBuffer();

                ///Llamar a función validar fecha de afiliacion

                pasoAlta++;
                break;

            case 7:
                if ((2026 - miemTemp.fechNac.anio) < 18) {
                    strcpy(miemTemp.cat, "MENOR");
                    printf("[MENOR DETECTADO] Ingrese Email del Tutor: ");
                    fgets(miemTemp.emailTutor,sizeof(miemTemp.emailTutor),stdin);
                } else {
                    strcpy(miemTemp.cat, "ADULTO");
                    strcpy(miemTemp.emailTutor, "N/A");
                }

                ///Llamar a funcion de validar categoria y correo

                pasoAlta++;
                break;

            case 8:
                printf("Ingrese Fecha de Ultima Cuota Paga (DD MM AAAA): ");
                if (scanf("%d %d %d", &miemTemp.fechUltCuot.dia, &miemTemp.fechUltCuot.mes, &miemTemp.fechUltCuot.anio) != 3) {
                    limpiarBuffer();
                    printf("[ERROR] Formato de fecha invalido.\n");
                    pasoAlta = -1;
                    break;
                }
                limpiarBuffer();

                ///LLamar a funcion para validar fecha de ultima cuota paga

                pasoAlta++;
                break;

            case 9:
                printf("\nSeleccione el Plan:\n1. BASIC\n2. PREMIUM\n3. VIP\n4. FAMILY\nOpcion: ");
                if (scanf("%d", &opcionPlan) != 1) {
                    limpiarBuffer();
                    pasoAlta = -1;
                    break;
                }
                limpiarBuffer();

                switch (opcionPlan) {
                    case 1: strcpy(miemTemp.plan, "BASIC"); break;
                    case 2: strcpy(miemTemp.plan, "PREMIUM"); break;
                    case 3: strcpy(miemTemp.plan, "VIP"); break;
                    case 4: strcpy(miemTemp.plan, "FAMILY"); break;
                    default:
                        printf("[ERROR] Opcion de plan invalida.\n");
                        pasoAlta = -1;
                        break;
                }

                if (pasoAlta != -1) {
                    miemTemp.estado = 'A';
                    pasoAlta++;
                }
                break;
        }
    }

    ///Una vez que están todos los registros válidos
    if (pasoAlta ==9) {
        miemTemp.estado='A';

        ///Acá podemos llamar a una funcion que vaya grabando el registro en memoria o lo podemos aplicar después

        ///Llamamos a funcion de insertarOrdenado
        indice_insertar(indice,&miemTemp,sizeof(miemTemp),cmpDNI);

        printf("\n>>> ¡ALTA EXITOSA! <<<\n");
    } else {
        printf("\n>>> [SISTEMA] Se detectaron errores. Se ha ignorado todo lo ingresado. <<<\n");
    }
}


// =========================================================================
// FUNCIÓN DE ALTA DE MIEMBRO (CON BUCLES DE VALIDACIÓN)
// =========================================================================
void alta_miembro(t_lista_miembros *lista_m, t_indice *indice_m) {
    printf("\n--- ALTA DE NUEVO MIEMBRO ---\n");

    miembro nuevo_miembro;
    memset(&nuevo_miembro, 0, sizeof(miembro));

    // ---------------------------------------------------------
    // 1. BUCLE DE DNI (Valida reglas y existencia en el índice)
    // ---------------------------------------------------------
    bool dni_valido = false;
    while (!dni_valido) {
        printf("Ingrese el DNI: ");
        if (scanf("%ld", &nuevo_miembro.dni) != 1) {
            printf("Error: Debe ingresar solo numeros.\n");
            while(getchar() != '\n'); // Limpiar buffer
            continue;
        }

        // A. Validar regla matemática (Ej: que tenga 8 dígitos)
        if (validar_campo(&nuevo_miembro, validarDNI) == ERROR) {
            printf("Error: DNI invalido segun las reglas del sistema. Intente de nuevo.\n");
            continue;
        }

        // B. Validar existencia en el Índice
        t_reg_indice ficha_busqueda;
        ficha_busqueda.dni = nuevo_miembro.dni;

        if (indice_buscar(indice_m, &ficha_busqueda, indice_m->cantidad_elementos_actual, sizeof(t_reg_indice), cmp_miembros_dni) != NO_EXISTE) {
            printf("Error: El DNI %ld ya esta registrado. Ingrese uno distinto.\n", nuevo_miembro.dni);
            continue;
        }

        dni_valido = true; // Si pasa todo, rompemos el bucle
    }
    while(getchar() != '\n'); // Limpiar el Enter que quedó en el buffer


    // ---------------------------------------------------------
    // 2. INGRESO DE NOMBRE Y NORMALIZACIÓN
    // ---------------------------------------------------------
    printf("Ingrese Apellido y Nombres: ");
    fgets(nuevo_miembro.apeNom, sizeof(nuevo_miembro.apeNom), stdin);
    nuevo_miembro.apeNom[strcspn(nuevo_miembro.apeNom, "\n")] = 0;
    strcpy(nuevo_miembro.apeNom, normalizarApel_Nombre(nuevo_miembro.apeNom));


    // ---------------------------------------------------------
    // 3. BUCLE DE SEXO
    // ---------------------------------------------------------
    // (Pedimos el sexo antes que el CUIL para que la función validarCUIL_Completo pueda cruzarlos)
    bool sexo_valido = false;
    while (!sexo_valido) {
        printf("Ingrese Sexo (M/F/O): ");
        scanf(" %c", &nuevo_miembro.sexo);
        while(getchar() != '\n');

        if (validar_campo(&nuevo_miembro, validarSexo) == TODO_OK) {
            sexo_valido = true;
        } else {
            printf("Error: Sexo invalido. Solo se permite M, F u O.\n");
        }
    }


    // ---------------------------------------------------------
    // 4. BUCLE DE CUIL
    // ---------------------------------------------------------
    bool cuil_valido = false;
    while (!cuil_valido) {
        printf("Ingrese CUIL (formato XX-XXXXXXXX-X): ");
        fgets(nuevo_miembro.CUIL, sizeof(nuevo_miembro.CUIL), stdin);
        nuevo_miembro.CUIL[strcspn(nuevo_miembro.CUIL, "\n")] = 0;

        if (validar_campo(&nuevo_miembro, validarCUIL) == TODO_OK) {
            cuil_valido = true;
        } else {
            printf("Error: El CUIL es invalido o no coincide con su DNI/Sexo.\n");
        }
    }


    // ---------------------------------------------------------
    // 5. BUCLE DE CORREO
    // ---------------------------------------------------------
    bool correo_valido = false;
    while (!correo_valido) {
        printf("Ingrese Correo Electronico: ");
        fgets(nuevo_miembro.email, sizeof(nuevo_miembro.email), stdin);
        nuevo_miembro.email[strcspn(nuevo_miembro.email, "\n")] = 0;

        if (validar_campo(&nuevo_miembro, validarCorreo) == TODO_OK) {
            correo_valido = true;
        } else {
            printf("Error: Formato de correo electronico invalido.\n");
        }
    }


    // ---------------------------------------------------------
    // 6. BUCLE DE PLAN
    // ---------------------------------------------------------
    bool plan_valido = false;
    while (!plan_valido) {
        printf("Ingrese Plan (Ej: Basico, Premium): ");
        fgets(nuevo_miembro.plan, sizeof(nuevo_miembro.plan), stdin);
        nuevo_miembro.plan[strcspn(nuevo_miembro.plan, "\n")] = 0;

        if (validar_campo(&nuevo_miembro, validarPlan) == TODO_OK) {
            plan_valido = true;
        } else {
            printf("Error: El plan ingresado no existe en el sistema.\n");
        }
    }


    // ---------------------------------------------------------
    // 7. BUCLE DE ESTADO
    // ---------------------------------------------------------
    bool estado_valido = false;
    while (!estado_valido) {
        printf("Ingrese Estado (Ej: Activo, Inactivo): ");
        fgets(nuevo_miembro.estado, sizeof(nuevo_miembro.estado), stdin);
        nuevo_miembro.estado[strcspn(nuevo_miembro.estado, "\n")] = 0;

        if (validar_campo(&nuevo_miembro, validarEstado) == TODO_OK) {
            estado_valido = true;
        } else {
            printf("Error: Estado invalido.\n");
        }
    }


    // =========================================================================
    // 8. GUARDADO DEFINITIVO EN MEMORIA
    // =========================================================================
    // Llegar a esta línea significa que TODOS los bucles fueron superados con éxito.

    // A. Lista Principal
    if (lista_m->cantidad == lista_m->capacidad) {
        int nueva_cap = (lista_m->capacidad == 0) ? 10 : lista_m->capacidad * 2;
        miembro *temp = (miembro *)realloc(lista_m->array, nueva_cap * sizeof(miembro));
        if (temp == NULL) {
            printf("Error fatal: Memoria insuficiente al guardar.\n");
            return;
        }
        lista_m->array = temp;
        lista_m->capacidad = nueva_cap;
    }

    // B. Índice
    if (indice_m->cantidad_elementos_actual == indice_m->cantidad_elementos_maxima) {
        unsigned nueva_cap_idx = (indice_m->cantidad_elementos_maxima == 0) ? 10 : indice_m->cantidad_elementos_maxima * 2;
        void *temp_idx = realloc(indice_m->vindice, nueva_cap_idx * sizeof(t_reg_indice));
        if (temp_idx == NULL) {
            printf("Error fatal: Memoria insuficiente en indice.\n");
            return;
        }
        indice_m->vindice = temp_idx;
        indice_m->cantidad_elementos_maxima = nueva_cap_idx;
    }

    // C. Almacenar
    int pos_lista = lista_m->cantidad;
    lista_m->array[pos_lista] = nuevo_miembro;
    lista_m->cantidad++;

    t_reg_indice *fichas = (t_reg_indice *)indice_m->vindice;
    fichas[indice_m->cantidad_elementos_actual].dni = nuevo_miembro.dni;
    fichas[indice_m->cantidad_elementos_actual].nro_reg = pos_lista;
    indice_m->cantidad_elementos_actual++;

    printf("\n-> ALTA EXITOSA: El miembro %s ha sido registrado correctamente.\n", nuevo_miembro.apeNom);

    // D. Reordenar índice para mantener búsquedas rápidas operativas
    qsort(indice_m->vindice, indice_m->cantidad_elementos_actual, sizeof(t_reg_indice), cmp_miembros_dni);
}

// =========================================================================
// FUNCIÓN DE ALTA DE TÍTULO (CON ID AUTOINCREMENTAL)
// =========================================================================
void alta_titulo(t_lista_titulos *lista_t, t_indice *indice_t) {
    printf("\n--- ALTA DE NUEVO TITULO (PELICULA) ---\n");

    titulo nuevo_titulo;
    memset(&nuevo_titulo, 0, sizeof(titulo));

    // ---------------------------------------------------------
    // 1. GENERACIÓN AUTOMÁTICA DEL ID (Autoincremental)
    // ---------------------------------------------------------
    int id_generado = 1; // Valor por defecto si la lista está vacía

    if (lista_t->cantidad > 0) {
        // Buscamos el ID de la última película guardada físicamente y le sumamos 1
        id_generado = lista_t->array[lista_t->cantidad - 1].ID + 1;
    }

    nuevo_titulo.ID = id_generado;
    printf("-> ID asignado automaticamente: %d\n\n", nuevo_titulo.ID);


    // ---------------------------------------------------------
    // 2. INGRESO DE TÍTULO Y NORMALIZACIÓN
    // ---------------------------------------------------------
    printf("Ingrese el Titulo (Max 60 caracteres): ");
    fgets(nuevo_titulo.titulo, sizeof(nuevo_titulo.titulo), stdin);
    nuevo_titulo.titulo[strcspn(nuevo_titulo.titulo, "\n")] = 0;

    strcpy(nuevo_titulo.titulo, normalizarTitulo(nuevo_titulo.titulo));


    // ---------------------------------------------------------
    // 3. BUCLE DE GÉNERO
    // ---------------------------------------------------------
    bool genero_valido = false;
    while (!genero_valido) {
        printf("Ingrese el Genero (Accion, Drama, Comedia, Terror): ");
        fgets(nuevo_titulo.genero, sizeof(nuevo_titulo.genero), stdin);
        nuevo_titulo.genero[strcspn(nuevo_titulo.genero, "\n")] = 0;

        if (validar_campo(&nuevo_titulo, validarGenero) == TODO_OK) {
            genero_valido = true;
        } else {
            printf("Error: Genero invalido. Debe ser una de las categorias permitidas.\n");
        }
    }


    // ---------------------------------------------------------
    // 4. INGRESO Y VALIDACIÓN DE STOCK
    // ---------------------------------------------------------
    printf("Ingrese el Stock disponible (VHS): ");
    while (scanf("%d", &nuevo_titulo.stock) != 1) {
        printf("Error: Ingrese un numero valido para el stock: ");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');

    validarStock(&nuevo_titulo.stock);


    // =========================================================================
    // 5. GUARDADO DEFINITIVO EN MEMORIA
    // =========================================================================

    // A. Lista Principal
    if (lista_t->cantidad == lista_t->capacidad) {
        int nueva_cap = (lista_t->capacidad == 0) ? 10 : lista_t->capacidad * 2;
        titulo *temp = (titulo *)realloc(lista_t->array, nueva_cap * sizeof(titulo));
        if (temp == NULL) {
            printf("Error fatal: Memoria insuficiente.\n");
            return;
        }
        lista_t->array = temp;
        lista_t->capacidad = nueva_cap;
    }

    // B. Índice
    if (indice_t->cantidad_elementos_actual == indice_t->cantidad_elementos_maxima) {
        unsigned nueva_cap_idx = (indice_t->cantidad_elementos_maxima == 0) ? 10 : indice_t->cantidad_elementos_maxima * 2;
        void *temp_idx = realloc(indice_t->vindice, nueva_cap_idx * sizeof(t_reg_indice));
        if (temp_idx == NULL) {
            printf("Error fatal: Memoria insuficiente en el indice.\n");
            return;
        }
        indice_t->vindice = temp_idx;
        indice_t->cantidad_elementos_maxima = nueva_cap_idx;
    }

    // C. Guardar en Lista
    int pos_lista = lista_t->cantidad;
    lista_t->array[pos_lista] = nuevo_titulo;
    lista_t->cantidad++;

    // D. Guardar en Índice
    t_reg_indice *fichas = (t_reg_indice *)indice_t->vindice;
    fichas[indice_t->cantidad_elementos_actual].dni = (long)nuevo_titulo.ID;
    fichas[indice_t->cantidad_elementos_actual].nro_reg = pos_lista;
    indice_t->cantidad_elementos_actual++;

    printf("\n-> ALTA EXITOSA: La pelicula '%s' ha sido registrada con ID %d.\n", nuevo_titulo.titulo, nuevo_titulo.ID);

    // E. Reordenar índice
    qsort(indice_t->vindice, indice_t->cantidad_elementos_actual, sizeof(t_reg_indice), cmp_titulos_id);
}


// =========================================================================
// FUNCIÓN DE BAJA DE MIEMBRO (ACTUALIZADA A ESTADOS 'A' / 'B')
// =========================================================================
void baja_miembro(t_lista_miembros *lista_m, t_indice *indice_m) {
    long dni_baja;
    printf("\n--- BAJA DE MIEMBRO ---\n");
    printf("Ingrese el DNI del miembro a dar de baja: ");

    if (scanf("%ld", &dni_baja) != 1) {
        printf("Error: Formato de DNI invalido.\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');

    // 1. BUSCAMOS EN EL ÍNDICE
    t_reg_indice ficha_busqueda;
    ficha_busqueda.dni = dni_baja;

    int pos_en_indice = indice_buscar(
        indice_m,
        &ficha_busqueda,
        indice_m->cantidad_elementos_actual,
        sizeof(t_reg_indice),
        cmp_miembros_dni
    );

    if (pos_en_indice == NO_EXISTE) {
        printf("Error: El DNI %ld no existe en el sistema o ya tiene estado 'B'.\n", dni_baja);
        return;
    }

    // 2. RECUPERAMOS LOS DATOS
    t_reg_indice *fichas = (t_reg_indice *)indice_m->vindice;
    int pos_lista = fichas[pos_en_indice].nro_reg;

    // 3. CONFIRMACIÓN AL USUARIO
    char confirmacion;
    printf("\nSe encontro al miembro: %s (CUIL: %s)\n",
           lista_m->array[pos_lista].apeNom,
           lista_m->array[pos_lista].CUIL);

    printf("Esta seguro que desea cambiar su estado a 'B' (Baja)? (S/N): ");
    scanf(" %c", &confirmacion);

    if (confirmacion != 'S' && confirmacion != 's') {
        printf("-> Operacion cancelada. El estado se mantiene en 'A'.\n");
        return;
    }

    // =========================================================================
    // 4. PROCEDEMOS CON LA BAJA
    // =========================================================================

    // ACCIÓN 1: Baja lógica en la lista principal (Cambiamos el estado a 'B')

    lista_m->array[pos_lista].estado = 'B';

    // ACCIÓN 2: Eliminamos del Índice (Desplazamiento a la izquierda)
    for (unsigned i = pos_en_indice; i < indice_m->cantidad_elementos_actual - 1; i++) {
        fichas[i] = fichas[i + 1];
    }

    indice_m->cantidad_elementos_actual--;

    printf("\n-> BAJA EXITOSA: El miembro ha sido dado de baja (Estado 'B').\n");
}

// =========================================================================
// FUNCIÓN DE BAJA DE TÍTULO (BAJA LÓGICA POR ÍNDICE) -- PORQUE EL STRUCT DE TITULO NO TIENE UN CAMPO ESTADO
// =========================================================================
void baja_titulo(t_lista_titulos *lista_t, t_indice *indice_t) {
    int id_baja;
    printf("\n--- BAJA DE TITULO ---\n");
    printf("Ingrese el ID del titulo a dar de baja: ");

    if (scanf("%d", &id_baja) != 1) {
        printf("Error: Formato de ID invalido.\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');

    // 1. BUSCAMOS EN EL ÍNDICE (Usando el campo .dni como contenedor del ID)
    t_reg_indice ficha_busqueda;
    ficha_busqueda.dni = (long)id_baja;

    int pos_en_indice = indice_buscar(
        indice_t,
        &ficha_busqueda,
        indice_t->cantidad_elementos_actual,
        sizeof(t_reg_indice),
        cmp_titulos_id
    );

    if (pos_en_indice == NO_EXISTE) {
        printf("Error: El ID %d no existe en el sistema.\n", id_baja);
        return;
    }

    // 2. RECUPERAMOS LOS DATOS PARA CONFIRMACIÓN
    t_reg_indice *fichas = (t_reg_indice *)indice_t->vindice;
    int pos_lista = fichas[pos_en_indice].nro_reg;

    char confirmacion;
    printf("\nSe encontro el titulo: '%s' (Stock actual: %d)\n",
           lista_t->array[pos_lista].titulo,
           lista_t->array[pos_lista].stock);

    printf("Esta seguro que desea eliminar este titulo del sistema? (S/N): ");
    scanf(" %c", &confirmacion);

    if (confirmacion != 'S' && confirmacion != 's') {
        printf("-> Operacion cancelada. El titulo se mantiene activo.\n");
        return;
    }

    // =========================================================================
    // 3. PROCEDEMOS CON LA BAJA (SOLO EN EL ÍNDICE)
    // =========================================================================

    // Eliminamos del Índice pisando la ficha (Desplazamiento a la izquierda)
    for (unsigned i = pos_en_indice; i < indice_t->cantidad_elementos_actual - 1; i++) {
        fichas[i] = fichas[i + 1];
    }

    // Achicamos el contador del índice
    indice_t->cantidad_elementos_actual--;

    // Nota: lista_t->array[pos_lista] queda intacto en memoria RAM,
    // pero ya no es accesible a través del buscador.

    printf("\n-> BAJA EXITOSA: El titulo ha sido eliminado del acceso publico.\n");
}
