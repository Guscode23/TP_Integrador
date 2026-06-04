#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "Validaciones.h"
#include <string.h>
#include <ctype.h>

void menu_operaciones(t_lista_miembros *lista_m, t_indice *indice_m, t_lista_titulos *lista_t, t_indice *indice_t, t_lista_alquileres *lista_a, t_fecha fecha_proceso)
{
    char opcion;

    do
    {
        printf("\n==================================================\n");
        printf("                MENU DE OPERACIONES               \n");
        printf("==================================================\n");
        printf("a. Alta de miembro\n");
        printf("b. Alta de un titulo\n");
        printf("c. Baja de un miembro\n");
        printf("d. Baja de un titulo\n");
        printf("e. Modificacion de un miembro\n");
        printf("f. Modificacion de un titulo\n");
        printf("g. Mostrar informacion de un miembro\n");
        printf("h. Alquiler de un titulo\n");
        printf("i. Listado de miembros ordenados por DNI\n");
        printf("j. Listado miembros por Plan\n");
        printf("k. Salir\n");
        printf("==================================================\n");
        printf("Seleccione una opcion (a-k): ");

        // El espacio antes de %c es un truco vital en C para ignorar enter previos en el buffer
        scanf(" %c", &opcion);
        while(getchar() != '\n'); // Limpiamos el buffer de entrada inmediatamente

        switch (opcion)
        {
        case 'a':
        case 'A':
            altaMiembro(lista_m, indice_m);
            break;

        case 'b':
        case 'B':
            altaTitulo(lista_t, indice_t);
            break;

        case 'c':
        case 'C':
            bajaMiembro(lista_m, indice_m);
            break;

        case 'd':
        case 'D':
            bajaTitulo(lista_t, indice_t);
            break;

        case 'e':
        case 'E':
            printf("\n[PROXIMAMENTE] Modificacion de miembro.\n");
            // modificacion_miembro(lista_m, indice_m);
            break;

        case 'f':
        case 'F':
            printf("\n[PROXIMAMENTE] Modificacion de titulo.\n");
            // modificacion_titulo(lista_t, indice_t);
            break;

        case 'g':
        case 'G':
            printf("\n[PROXIMAMENTE] Mostrar informacion de un miembro.\n");
            break;

        case 'h':
        case 'H':
            printf("\n[PROXIMAMENTE] Alquiler de un titulo.\n");
            break;

        case 'i':
        case 'I':
            printf("\n[PROXIMAMENTE] Listado de miembros ordenados por DNI.\n");
            break;

        case 'j':
        case 'J':
            printf("\n[PROXIMAMENTE] Listado de miembros por Plan.\n");
            break;

        case 'k':
        case 'K':
            printf("\nSaliendo del sistema...\n");
            guardar_datos_sesion(lista_m, lista_t, lista_a, fecha_proceso);
            break;

        default:
            printf("\nError: Opcion invalida. Por favor, seleccione una letra de la 'a' a la 'k'.\n");
            break;
        }

    }
    while (opcion != 'k' && opcion != 'K');
}

void limpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//int cmpDNI(const void* d1, const void* d2){
//  long int dif= *(long int*)d1 - *(long int*)d2;
//  return dif;
//
//}

//int cmpID(const void* d1, const void* d2){
//  int dif= *(int*)d1 - *(int*)d2;
//  return dif;
//}

//void altaMiembro(miembro *miembroOficial,t_indice* indice,t_fecha* fechProceso) {
//
//  miembro miemTemp; ///Variable temporal de miembros que ira guardando los datos ingresados por teclado
//  int pasoAlta = 1;
//  int opcionPlan;
//
//    printf("\n--- FORMULARIO DE ALTA: MIEMBRO ---\n");
//
//    while (pasoAlta > 0 && pasoAlta <= 10) {
//        switch (pasoAlta) {
//            case 1:
//                printf("Ingrese DNI: ");
//                if (scanf("%ld", &miemTemp.dni) != 1) {
//                    limpiarBuffer();
//                    printf("[ERROR] Entrada de DNI invalida.\n");
//                    pasoAlta = -1;
//                    break;
//                }
//                limpiarBuffer();
//
//                if (indice_buscar(indice,&miemTemp.dni,indice->cantidad_elementos_actual,sizeof(long int),cmpDNI)!=NO_EXISTE) {
//                    printf("[ERROR] El DNI ya existe en el indice. Operacion cancelada.\n");
//                    pasoAlta = -1;
//                    break;
//                }
//
//                pasoAlta++;
//                break;
//
//            case 2:
//                printf("Ingrese CUIL: ");
//                fgets(miemTemp.CUIL, sizeof(miemTemp.CUIL), stdin);
//
//                if(validarCUIL(miemTemp.CUIL)<0){
//                    printf("Error al ingresar CUIL");
//                    pasoAlta-=1;
//                    break;
//                }
//
//                pasoAlta++;
//                break;
//
//            case 3:
//                printf("Ingrese Apellidos y Nombres: ");
//                fgets(miemTemp.apeNom, sizeof(miemTemp.apeNom), stdin);
//
//                normalizarApel_Nombre(miemTemp.apeNom);
//
//                pasoAlta++;
//                break;
//
//            case 4:
//                printf("Ingrese Fecha de Nacimiento (DD MM AAAA): ");
//                if (scanf("%d %d %d", &miemTemp.fechNac.dia, &miemTemp.fechNac.mes, &miemTemp.fechNac.anio) != 3) {
//                    limpiarBuffer();
//                    printf("[ERROR] Formato de fecha invalido.\n");
//                    pasoAlta = -1;
//                    break;
//                }
//                limpiarBuffer();
//
//                ///LLamar a función de validar Fecha de Nacimiento
//
//                pasoAlta++;
//                break;
//
//            case 5:
//                printf("Ingrese Sexo ('F', 'M', 'O'): ");
//                scanf("%c", &miemTemp.sexo);
//                limpiarBuffer();
//
//                if(validarSexo(&miemTemp.sexo)<0){
//                    printf("Sexo inválido");
//                    pasoAlta-=1;
//                    break;
//                }
//
//                pasoAlta++;
//                break;
//
//            case 6:
//                printf("Ingrese Fecha de Afiliacion (DD MM AAAA): ");
//                if (scanf("%d %d %d", &miemTemp.fechAfil.dia, &miemTemp.fechAfil.mes, &miemTemp.fechAfil.anio) != 3) {
//                    limpiarBuffer();
//                    printf("[ERROR] Formato de fecha invalido.\n");
//                    pasoAlta = -1;
//                    break;
//                }
//                limpiarBuffer();
//
//                ///Llamar a función validar fecha de afiliacion
//
//                pasoAlta++;
//                break;
//
//            case 7:
//                if ((2026 - miemTemp.fechNac.anio) < 18) {
//                    strcpy(miemTemp.cat, "MENOR");
//                    printf("[MENOR DETECTADO] Ingrese Email del Tutor: ");
//                    fgets(miemTemp.emailTutor,sizeof(miemTemp.emailTutor),stdin);
//                } else {
//                    strcpy(miemTemp.cat, "ADULTO");
//                    strcpy(miemTemp.emailTutor, "N/A");
//                }
//
//                ///Llamar a funcion de validar categoria y correo
//
//                pasoAlta++;
//                break;
//
//            case 8:
//                printf("Ingrese Fecha de Ultima Cuota Paga (DD MM AAAA): ");
//                if (scanf("%d %d %d", &miemTemp.fechUltCuot.dia, &miemTemp.fechUltCuot.mes, &miemTemp.fechUltCuot.anio) != 3) {
//                    limpiarBuffer();
//                    printf("[ERROR] Formato de fecha invalido.\n");
//                    pasoAlta = -1;
//                    break;
//                }
//                limpiarBuffer();
//
//                ///LLamar a funcion para validar fecha de ultima cuota paga
//
//                pasoAlta++;
//                break;
//
//            case 9:
//                printf("\nSeleccione el Plan:\n1. BASIC\n2. PREMIUM\n3. VIP\n4. FAMILY\nOpcion: ");
//                if (scanf("%d", &opcionPlan) != 1) {
//                    limpiarBuffer();
//                    pasoAlta = -1;
//                    break;
//                }
//                limpiarBuffer();
//
//                switch (opcionPlan) {
//                    case 1: strcpy(miemTemp.plan, "BASIC"); break;
//                    case 2: strcpy(miemTemp.plan, "PREMIUM"); break;
//                    case 3: strcpy(miemTemp.plan, "VIP"); break;
//                    case 4: strcpy(miemTemp.plan, "FAMILY"); break;
//                    default:
//                        printf("[ERROR] Opcion de plan invalida.\n");
//                        pasoAlta = -1;
//                        break;
//                }
//
//                if (pasoAlta != -1) {
//                    miemTemp.estado = 'A';
//                    pasoAlta++;
//                }
//                break;
//        }
//    }
//
//    ///Una vez que están todos los registros válidos
//    if (pasoAlta ==9) {
//        miemTemp.estado='A';
//
//        ///Acá podemos llamar a una funcion que vaya grabando el registro en memoria o lo podemos aplicar después
//
//        ///Llamamos a funcion de insertarOrdenado
//        indice_insertar(indice,&miemTemp,sizeof(miemTemp),cmpDNI);
//
//        printf("\n>>> ¡ALTA EXITOSA! <<<\n");
//    } else {
//        printf("\n>>> [SISTEMA] Se detectaron errores. Se ha ignorado todo lo ingresado. <<<\n");
//    }
//}

///Funciones de modificación de registros

void modificarMiembro(t_lista_miembros *lista_m, t_indice *indice, t_fecha *fechProceso)
{

    miembro miemTemp;
    long int dniBuscado;
    int opcionPlan, pos, edad;
    char fechaNacimiento[11], fechaAfiliacion[11], fechaUltimaCuota[11];

    printf("\n--- FORMULARIO DE MODIFICACION: MIEMBRO ---\n");

    // Busca el miembro por DNI
    printf("Ingrese DNI del miembro a modificar: ");
    if (scanf("%ld", &dniBuscado) != 1)
    {
        limpiarBuffer();
        printf("[ERROR] Entrada de DNI invalida.\n");
        return;
    }
    limpiarBuffer();

    //pos = indice_buscar(indice, &dniBuscado, indice->cantidad_elementos_actual, sizeof(long int), cmpDNI);
    if (pos == NO_EXISTE)
    {
        printf("[ERROR] El DNI no existe en el indice. Operacion cancelada.\n");
        return;
    }

    t_reg_indice *reg = (t_reg_indice *)indice->vindice + pos;
    miemTemp = lista_m->array[reg->nro_reg];

    // Menú de campos a modificar
    int opcion = 0;

    while (1)
    {
        printf("\n¿Qué campo desea modificar?\n");
        printf("1.  CUIL\n");
        printf("2.  Apellidos y Nombres\n");
        printf("3.  Fecha de Nacimiento\n");
        printf("4.  Sexo\n");
        printf("5.  Fecha de Afiliacion\n");
        printf("6.  Fecha de Ultima Cuota Paga\n");
        printf("7.  Plan\n");
        printf("8.  Estado\n");
        printf("9. Confirmar y guardar cambios\n");
        printf("0.  Cancelar\n");
        printf("Opcion: ");

        if (scanf("%d", &opcion) != 1)
        {
            limpiarBuffer();
            printf("[ERROR] Opcion invalida.\n");
            continue;
        }
        limpiarBuffer();

        switch (opcion)
        {
        case 1:
            printf("Ingrese nuevo CUIL: ");
            fgets(miemTemp.CUIL, sizeof(miemTemp.CUIL), stdin);
            if (validarCUIL(miemTemp.CUIL) < 0)
            {
                printf("[ERROR] CUIL invalido. No se modifico.\n");
                strcpy(miemTemp.CUIL, lista_m->array[reg->nro_reg].CUIL);
            }
            break;

        case 2:
            printf("Ingrese nuevos Apellidos y Nombres: ");
            fgets(miemTemp.apeNom, sizeof(miemTemp.apeNom), stdin);
            normalizarApel_Nombre(miemTemp.apeNom);
            if (strcmp(miemTemp.apeNom, "") == 0)
            {
                strcpy(miemTemp.apeNom, lista_m->array[reg->nro_reg].apeNom);
                printf("[ERROR] Nombre y apellido vacios. No se modifico.\n");
            }
            break;

        case 3:
            printf("Ingrese nueva Fecha de Nacimiento (DD/MM/AAAA): ");
            scanf("%s", fechaNacimiento);
            miemTemp.fechNac = parsearFecha(fechaNacimiento);
            if(es_Fecha_Valida(&miemTemp.fechNac) == ERROR)
            {
                miemTemp.fechNac = lista_m->array[reg->nro_reg].fechNac;
                printf("[ERROR] Fecha de nacimiento invalida. No se modifico.\n");
                break;
            }
            else if(validarFechaNacimiento(&miemTemp.fechNac, fechProceso) == ERROR)
            {
                miemTemp.fechNac = lista_m->array[reg->nro_reg].fechNac;
                printf("[ERROR] Fecha de nacimiento invalida. No se modifico.\n");
                break;
            }
            limpiarBuffer();

            edad = calcularEdad(fechProceso, &miemTemp.fechNac);
            if (edad >= 18)
            {
                strcpy(miemTemp.cat, "ADULTO");
            }
            else
            {
                strcpy(miemTemp.cat, "MENOR");
                if (strcmp(miemTemp.cat, lista_m->array[reg->nro_reg].cat) != 0)
                {
                    printf("La categoria cambio a MENOR. Por favor, ingrese Email del Tutor: ");
                    fgets(miemTemp.emailTutor, sizeof(miemTemp.emailTutor), stdin);
                }
                if(validar_campo(&miemTemp, validarCorreo) == ERROR)
                {
                    miemTemp.fechNac = lista_m->array[reg->nro_reg].fechNac;
                    strcpy(miemTemp.emailTutor, lista_m->array[reg->nro_reg].emailTutor);
                    printf("[ERROR] Mail invalido. No se modifico el mail ni la edad.\n");
                }
            }
            break;

        case 4:
            printf("Ingrese nuevo Sexo ('F', 'M', 'O'): ");
            scanf("%c", &miemTemp.sexo);
            limpiarBuffer();
            if (validarSexo(&miemTemp.sexo) < 0)
            {
                printf("[ERROR] Sexo invalido. No se modifico.\n");
                miemTemp.sexo = lista_m->array[reg->nro_reg].sexo;
            }
            break;

        case 5:
            printf("Ingrese nueva Fecha de Afiliacion (DD/MM/AAAA): ");
            scanf("%s", fechaAfiliacion);
            miemTemp.fechAfil = parsearFecha(fechaAfiliacion);
            if(es_Fecha_Valida(&miemTemp.fechAfil) == ERROR)
            {
                miemTemp.fechAfil = lista_m->array[reg->nro_reg].fechAfil;
                printf("[ERROR] Fecha de afiliacion invalida. No se modifico.\n");
                break;
            }
            else if(validarFechaAfiliacion(&miemTemp.fechAfil,&miemTemp.fechNac,fechProceso) == ERROR)
            {
                miemTemp.fechAfil = lista_m->array[reg->nro_reg].fechAfil;
                printf("[ERROR] Fecha de afiliacion invalida. No se modifico.\n");
                break;
            }
            limpiarBuffer();
            break;

        case 6:
            printf("Ingrese nueva Fecha de Ultima Cuota Paga (DD/MM/AAAA): ");
            scanf("%s", fechaUltimaCuota);
            miemTemp.fechUltCuot = parsearFecha(fechaUltimaCuota);
            if(es_Fecha_Valida(&miemTemp.fechUltCuot) == ERROR)
            {
                miemTemp.fechUltCuot = lista_m->array[reg->nro_reg].fechUltCuot;
                printf("[ERROR] Fecha de ultima cuota invalida. No se modifico.\n");
                break;
            }
            else if(validar_UltimaCuota_Paga(&miemTemp.fechAfil,&miemTemp.fechUltCuot,fechProceso) == ERROR)
            {
                miemTemp.fechUltCuot = lista_m->array[reg->nro_reg].fechUltCuot;
                printf("[ERROR] Fecha de ultima cuota invalida. No se modifico.\n");
                break;
            }
            limpiarBuffer();
            break;

        case 7:
            printf("Seleccione el nuevo Plan:\n1. BASIC\n2. PREMIUM\n3. VIP\n4. FAMILY\nOpcion: ");
            if (scanf("%d", &opcionPlan) != 1)
            {
                limpiarBuffer();
                printf("[ERROR] Opcion invalida. No se modifico.\n");
                break;
            }
            limpiarBuffer();
            switch (opcionPlan)
            {
            case 1:
                strcpy(miemTemp.plan, "BASIC");
                break;
            case 2:
                strcpy(miemTemp.plan, "PREMIUM");
                break;
            case 3:
                strcpy(miemTemp.plan, "VIP");
                break;
            case 4:
                strcpy(miemTemp.plan, "FAMILY");
                break;
            default:
                printf("[ERROR] Opcion de plan invalida. No se modifico.\n");
                strcpy(miemTemp.plan, lista_m->array[reg->nro_reg].plan);
            }
            break;

        case 8:
            printf("Ingrese nuevo Estado ('A' = Activo, 'B' = Baja): ");
            scanf("%c", &miemTemp.estado);
            limpiarBuffer();
            if (miemTemp.estado != 'A' && miemTemp.estado != 'B')
            {
                printf("[ERROR] Estado invalido. No se modifico.\n");
                miemTemp.estado = lista_m->array[reg->nro_reg].estado;
            }
            break;

        case 9:
            // Confirmar cambios
            lista_m->array[reg->nro_reg] = miemTemp;
            printf("\n>>> ¡MODIFICACION EXITOSA! <<<\n");
            return;

        case 0:
            printf("\n>>> [SISTEMA] Modificacion cancelada. <<<\n");
            return;

        default:
            printf("[ERROR] Opcion invalida.\n");
            break;
        }
    }
}

void modificacion_titulo(t_lista_titulos *lista_t, t_indice *indice_t)
{
    titulo tituloTemp;
    int idBuscado;
    int opcionGenero;

    printf("\n--- FORMULARIO DE MODIFICACION: TITULO ---\n");

    // 1. BUSCAR LA PELÍCULA POR ID
    printf("Ingrese ID de la pelicula a modificar: ");
    if (scanf("%d", &idBuscado) != 1)
    {
        while(getchar() != '\n');
        printf("Error: Entrada de ID invalida.\n");
        return;
    }
    while(getchar() != '\n'); // Limpiar buffer

    // Armamos la ficha falsa para el buscador de la cátedra
    t_reg_indice ficha_busqueda;
    ficha_busqueda.dni = (long)idBuscado;

    int pos_en_indice = indice_buscar(
                            indice_t,
                            &ficha_busqueda,
                            indice_t->cantidad_elementos_actual,
                            sizeof(t_reg_indice),
                            cmp_titulos_id
                        );

    if (pos_en_indice == NO_EXISTE)
    {
        printf("Error: El ID %d no existe en el sistema. Operacion cancelada.\n", idBuscado);
        return;
    }

    // 2. RECUPERAR EL REGISTRO
    t_reg_indice *fichas = (t_reg_indice *)indice_t->vindice;
    int pos_lista = fichas[pos_en_indice].nro_reg;

    // Clonamos los datos reales a la variable temporal
    tituloTemp = lista_t->array[pos_lista];

    // 3. SUBMENÚ DE MODIFICACIÓN
    int opcion = 0;

    while (1)
    {
        printf("\n====================================\n");
        printf(" MODIFICANDO TITULO ID: %d\n", tituloTemp.ID);
        printf("====================================\n");
        printf("1. Titulo actual: %s\n", tituloTemp.titulo);
        printf("2. Genero actual: %s\n", tituloTemp.genero);
        printf("3. Stock actual:  %d\n", tituloTemp.stock);
        printf("------------------------------------\n");
        printf("4. Confirmar y guardar cambios\n");
        printf("0. Cancelar y salir sin guardar\n");
        printf("Opcion: ");

        if (scanf("%d", &opcion) != 1)
        {
            while(getchar() != '\n');
            printf("Error: Opcion invalida.\n");
            continue;
        }
        while(getchar() != '\n');

        switch (opcion)
        {
        case 1:
            printf("Ingrese nuevo titulo: ");
            fgets(tituloTemp.titulo, sizeof(tituloTemp.titulo), stdin);
            tituloTemp.titulo[strcspn(tituloTemp.titulo, "\n")] = 0; // Quitar \n
            normalizarTitulo(tituloTemp.titulo);

            if (strcmp(tituloTemp.titulo, "") == 0)
            {
                // Si lo deja vacío, restauramos el original
                strcpy(tituloTemp.titulo, lista_t->array[pos_lista].titulo);
                printf("Error: Titulo vacio. No se realizo la modificacion.\n");
            }
            else
            {
                printf("-> Titulo actualizado temporalmente.\n");
            }
            break;

        case 2:
            printf("Seleccione el nuevo genero:\n1. Accion\n2. Drama\n3. Comedia\n4. Terror\nOpcion: ");
            if (scanf("%d", &opcionGenero) != 1)
            {
                while(getchar() != '\n');
                printf("Error: Opcion invalida.\n");
                break;
            }
            while(getchar() != '\n');

            switch (opcionGenero)
            {
            case 1:
                strcpy(tituloTemp.genero, "Accion");
                printf("-> Genero actualizado temporalmente.\n");
                break;
            case 2:
                strcpy(tituloTemp.genero, "Drama");
                printf("-> Genero actualizado temporalmente.\n");
                break;
            case 3:
                strcpy(tituloTemp.genero, "Comedia");
                printf("-> Genero actualizado temporalmente.\n");
                break;
            case 4:
                strcpy(tituloTemp.genero, "Terror");
                printf("-> Genero actualizado temporalmente.\n");
                break;
            default:
                printf("Error: Opcion de genero invalida.\n");
            }
            break;

        case 3:
            printf("Ingrese nueva cantidad de stock: ");
            if (scanf("%d", &tituloTemp.stock) != 1)
            {
                while(getchar() != '\n');
                printf("Error: Entrada de stock invalida.\n");
                break;
            }
            while(getchar() != '\n');

            validarStock(&tituloTemp.stock);
            printf("-> Stock actualizado temporalmente.\n");
            break;

        case 4: // GUARDADO DEFINITIVO
            // Pisamos el registro real con nuestra variable temporal
            lista_t->array[pos_lista] = tituloTemp;
            printf("\n>>> MODIFICACION EXITOSA <<<\n");
            return; // Cortamos la función y volvemos al menú principal

        case 0: // CANCELAR
            printf("\n>>> Operacion cancelada. Los datos originales se mantienen intactos. <<<\n");
            return; // Cortamos la función sin guardar

        default:
            printf("Error: Seleccione una opcion valida (0-4).\n");
            break;
        }
    }
}

///Funciones de mostrado de información

void mostrarMiembro(t_lista_miembros *lista_m, t_indice *indice)
{

    long int dniBuscado;
    int pos;

    printf("\n--- CONSULTA DE MIEMBRO ---\n");

    printf("Ingrese DNI del miembro a consultar: ");
    if (scanf("%ld", &dniBuscado) != 1)
    {
        limpiarBuffer();
        printf("[ERROR] Entrada de DNI invalida.\n");
        return;
    }
    limpiarBuffer();

    // Buscamos en el índice
//    pos = indice_buscar(indice, &dniBuscado, indice->cantidad_elementos_actual, sizeof(long int), cmpDNI);
    if (pos == NO_EXISTE)
    {
        printf("[ERROR] El DNI no existe en el indice.\n");
        return;
    }

    // Obtenemos el miembro real a través del nro_reg
    t_reg_indice *reg = (t_reg_indice *)indice->vindice + pos;
    miembro *m = &lista_m->array[reg->nro_reg];

    // Mostramos los datos
    printf("\n---------- DATOS DEL MIEMBRO ----------\n");
    printf("DNI:                    %ld\n",   m->dni);
    printf("CUIL:                   %s\n",    m->CUIL);
    printf("Apellidos y Nombres:    %s\n",    m->apeNom);
    printf("Fecha de Nacimiento:    %d/%d/%d\n", m->fechNac.dia, m->fechNac.mes, m->fechNac.anio);
    printf("Sexo:                   %c\n",    m->sexo);
    printf("Fecha de Afiliacion:    %d/%d/%d\n", m->fechAfil.dia, m->fechAfil.mes, m->fechAfil.anio);
    printf("Categoria:              %s\n",    m->cat);
    printf("Fecha Ultima Cuota:     %d/%d/%d\n", m->fechUltCuot.dia, m->fechUltCuot.mes, m->fechUltCuot.anio);
    printf("Estado:                 %c\n",    m->estado);
    printf("Plan:                   %s\n",    m->plan);
    printf("Email Tutor:            %s\n",    m->emailTutor);
    printf("----------------------------------------\n");
}

void mostrarSocios_DNI(miembro* t_miembro, int cantidad)
{
    ///Llamar a funcion de ordenamiento, o ordenar antes

    // Encabezado con todos los campos encolumnados
    printf("\n%-10s %-13s %-25s %-11s %-4s %-11s %-5s %-11s %-4s %-6s %-25s\n",
           "DNI", "CUIL", "APELLIDO Y NOMBRE", "F. NAC", "SEXO", "F. AFIL", "CAT", "F. ULT CUO", "EST", "PLAN", "EMAIL TUTOR");

    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < cantidad; i++)
    {
        if ((t_miembro + i)->estado == 'A')
        {
            printf("%-10ld %-13s %-25s %02d/%02d/%04d  %-4c %02d/%02d/%04d  %-5s %02d/%02d/%04d  %-4c %-6s %-25s\n",
                   (t_miembro + i)->dni,
                   (t_miembro + i)->CUIL,
                   (t_miembro + i)->apeNom,

                   // t_fecha fechNac
                   (t_miembro + i)->fechNac.dia, (t_miembro + i)->fechNac.mes, (t_miembro + i)->fechNac.anio,

                   (t_miembro + i)->sexo,

                   // t_fecha fechAfil
                   (t_miembro + i)->fechAfil.dia, (t_miembro + i)->fechAfil.mes, (t_miembro + i)->fechAfil.anio,

                   (t_miembro + i)->cat,

                   // t_fecha fechUltCuot
                   (t_miembro + i)->fechUltCuot.dia, (t_miembro + i)->fechUltCuot.mes, (t_miembro + i)->fechUltCuot.anio,

                   (t_miembro + i)->estado,
                   (t_miembro + i)->plan,
                   (t_miembro + i)->emailTutor);
        }
    }

    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

///Mostrar Miembros por plan
void listarMiembrosPorPlan(miembro* t_miembro, int cantidad)
{
    ///Llamar a funcion de ordenamiento (Por Apellido y Nombre) o hacerlo antes

    printf("\n%-20s %-12s %-12s %-12s %-12s\n", "Plan / Índice", "(BASIC)", "(PREMIUM)", "(VIP)", "(FAMILY)");
    printf("-----------------------------------------------------------------------\n");

    for (int i = 0; i < cantidad; i++)
    {
        printf("%-20s ", (t_miembro + i)->apeNom);

        if (strcmp((t_miembro + i)->plan, "BASIC") == 0)
        {
            printf("%-12ld ", (t_miembro + i)->dni);
        }
        else
        {
            printf("%-12s ", "0");
        }

        if (strcmp((t_miembro + i)->plan, "PREMIUM") == 0)
        {
            printf("%-12ld ", (t_miembro + i)->dni);
        }
        else
        {
            printf("%-12s ", "0");
        }

        if (strcmp((t_miembro + i)->plan, "VIP") == 0)
        {
            printf("%-12ld ", (t_miembro + i)->dni);
        }
        else
        {
            printf("%-12s ", "0");
        }

        if (strcmp((t_miembro + i)->plan, "FAMILY") == 0)
        {
            printf("%-12ld\n", (t_miembro + i)->dni);
        }
        else
        {
            printf("%-12s\n", "0");
        }
    }
    printf("-----------------------------------------------------------------------\n");
}

///Funciones para alquiler
int buscarAlquiler(t_lista_alquileres *lista, long dni, int idPelicula)
{
    for (int i = 0; i < lista->cantidad; i++)
    {
        if (lista->array[i].dni == dni && lista->array[i].idPelicula == idPelicula)
            return i; // devuelve la posición si existe
    }
    return NO_EXISTE;
}

int registrarAlquiler(t_lista_alquileres *lista_a, t_lista_miembros *lista_m, t_lista_titulos *lista_t, t_indice *indice_m, t_indice *indice_t)
{
    long int dniBuscado;
    int idPelicula, pos, posAlq;

    printf("\n--- REGISTRAR ALQUILER ---\n");

    // =========================================================
    // 1. BUSCAR Y VALIDAR MIEMBRO
    // =========================================================
    printf("Ingrese DNI del miembro: ");
    if (scanf("%ld", &dniBuscado) != 1)
    {
        while(getchar() != '\n');
        printf("[ERROR] DNI invalido.\n");
        return ERROR;
    }
    while(getchar() != '\n');

    // Armamos la ficha falsa y buscamos en el índice
    t_reg_indice ficha_m;
    ficha_m.dni = dniBuscado;
    pos = indice_buscar(indice_m, &ficha_m, indice_m->cantidad_elementos_actual, sizeof(t_reg_indice), cmp_miembros_dni);

    if (pos == NO_EXISTE)
    {
        printf("[ERROR] El miembro con DNI %ld no existe.\n", dniBuscado);
        return ERROR;
    }

    t_reg_indice *regMiembro = (t_reg_indice *)indice_m->vindice + pos;
    miembro *m = &lista_m->array[regMiembro->nro_reg];

    // Verifica que el miembro esté activo
    if (m->estado != 'A')
    {
        printf("[ERROR] El miembro no esta activo en el sistema.\n");
        return ERROR;
    }

    // Verifica límite de alquileres activos para plan BASIC
    if (strcmp(m->plan, "BASIC") == 0)
    {
        int activos = 0;
        for (int i = 0; i < lista_a->cantidad; i++)
        {
            if (lista_a->array[i].dni == dniBuscado && lista_a->array[i].estado == 'A')
                activos++;
        }
        if (activos >= 2)
        {
            printf("[ERROR] El miembro tiene plan BASIC y ya alcanzo el limite de 2 alquileres activos.\n");
            return ERROR;
        }
    }

    // =========================================================
    // 2. BUSCAR Y VALIDAR TÍTULO
    // =========================================================
    printf("Ingrese ID de la pelicula a alquilar: ");
    if (scanf("%d", &idPelicula) != 1)
    {
        while(getchar() != '\n');
        printf("[ERROR] ID invalido.\n");
        return ERROR;
    }
    while(getchar() != '\n');

    // Armamos la ficha falsa (Guardamos el ID en el campo DNI)
    t_reg_indice ficha_t;
    ficha_t.dni = (long)idPelicula;
    pos = indice_buscar(indice_t, &ficha_t, indice_t->cantidad_elementos_actual, sizeof(t_reg_indice), cmp_titulos_id);

    if (pos == NO_EXISTE)
    {
        printf("[ERROR] La pelicula con ID %d no existe.\n", idPelicula);
        return ERROR;
    }

    t_reg_indice *regPelicula = (t_reg_indice *)indice_t->vindice + pos;
    titulo *p = &lista_t->array[regPelicula->nro_reg]; // Usamos 'titulo' en lugar de 'pelicula'

    // Verifica si hay stock disponible
    if (p->stock <= 0)
    {
        printf("[ERROR] No hay stock disponible para esta pelicula en este momento.\n");
        return ERROR;
    }

    // =========================================================
    // 3. REGISTRAR ALQUILER
    // =========================================================
    posAlq = buscarAlquiler(lista_a, dniBuscado, idPelicula);

    if (posAlq == NO_EXISTE)
    {
        // Es una relación nueva, la agregamos
        if (lista_a->cantidad == lista_a->capacidad)
        {
            // Validación para inicializar en 10 si la capacidad era 0
            int nueva_cap = (lista_a->capacidad == 0) ? 10 : lista_a->capacidad * 2;

            t_alquiler *temp = realloc(lista_a->array, nueva_cap * sizeof(t_alquiler));
            if (temp == NULL)
            {
                printf("[ERROR] Error fatal de memoria al registrar el alquiler.\n");
                return ERROR;
            }
            lista_a->array = temp;
            lista_a->capacidad = nueva_cap;
        }

        lista_a->array[lista_a->cantidad].dni = dniBuscado;
        lista_a->array[lista_a->cantidad].idPelicula = idPelicula;
        lista_a->array[lista_a->cantidad].estado = 'A';
        lista_a->array[lista_a->cantidad].cantAlquileres = 1;

        posAlq = lista_a->cantidad; // Guardamos la posición para el printf final
        lista_a->cantidad++;
    }
    else
    {
        // La relación ya existe, actualizamos
        lista_a->array[posAlq].estado = 'A';
        lista_a->array[posAlq].cantAlquileres++;
    }

    // Descuenta stock
    p->stock--;

    // =========================================================
    // 4. CONFIRMACIÓN
    // =========================================================
    printf("\n>>> ¡ALQUILER REGISTRADO EXITOSAMENTE! <<<\n");
    printf("Miembro: %s | Pelicula: %s | Alquileres historicos de este titulo: %d\n",
           m->apeNom, p->titulo, lista_a->array[posAlq].cantAlquileres);

    return TODO_OK;
}



// FUNCIONES DE ABM

void altaMiembro(t_lista_miembros *lista_m, t_indice *indice_m)
{
    printf("\n--- ALTA DE NUEVO MIEMBRO ---\n");

    miembro nuevo_miembro;
    memset(&nuevo_miembro, 0, sizeof(miembro));

    // ---------------------------------------------------------
    // 1. BUCLE DE DNI (Valida reglas y existencia en el índice)
    // ---------------------------------------------------------
    bool dni_valido = false;
    while (!dni_valido)
    {
        printf("Ingrese el DNI: ");
        if (scanf("%ld", &nuevo_miembro.dni) != 1)
        {
            printf("Error: Debe ingresar solo numeros.\n");
            while(getchar() != '\n'); // Limpiar buffer
            continue;
        }

        // A. Validar regla matemática (Ej: que tenga 8 dígitos)
        if (validar_campo(&nuevo_miembro, validarDNI) == ERROR)
        {
            printf("Error: DNI invalido segun las reglas del sistema. Intente de nuevo.\n");
            continue;
        }

        // B. Validar existencia en el Índice
        t_reg_indice ficha_busqueda;
        ficha_busqueda.dni = nuevo_miembro.dni;

        if (indice_buscar(indice_m, &ficha_busqueda, indice_m->cantidad_elementos_actual, sizeof(t_reg_indice), cmp_miembros_dni) != NO_EXISTE)
        {
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
    while (!sexo_valido)
    {
        printf("Ingrese Sexo (M/F/O): ");
        scanf(" %c", &nuevo_miembro.sexo);
        while(getchar() != '\n');

        if (validar_campo(&nuevo_miembro, validarSexo) == TODO_OK)
        {
            sexo_valido = true;
        }
        else
        {
            printf("Error: Sexo invalido. Solo se permite M, F u O.\n");
        }
    }


    // ---------------------------------------------------------
    // 4. BUCLE DE CUIL
    // ---------------------------------------------------------
    bool cuil_valido = false;
    while (!cuil_valido)
    {
        printf("Ingrese CUIL (formato XX-XXXXXXXX-X): ");
        fgets(nuevo_miembro.CUIL, sizeof(nuevo_miembro.CUIL), stdin);
        nuevo_miembro.CUIL[strcspn(nuevo_miembro.CUIL, "\n")] = 0;

        if (validar_campo(&nuevo_miembro, validarCUIL) == TODO_OK)
        {
            cuil_valido = true;
        }
        else
        {
            printf("Error: El CUIL es invalido o no coincide con su DNI/Sexo.\n");
        }
    }


    // ---------------------------------------------------------
    // 5. BUCLE DE CORREO
    // ---------------------------------------------------------
    bool correo_valido = false;
    while (!correo_valido)
    {
        printf("Ingrese Correo Electronico: ");
        fgets(nuevo_miembro.emailTutor, sizeof(nuevo_miembro.emailTutor), stdin);
        nuevo_miembro.emailTutor[strcspn(nuevo_miembro.emailTutor, "\n")] = 0;

        if (validar_campo(&nuevo_miembro, validarCorreo) == TODO_OK)
        {
            correo_valido = true;
        }
        else
        {
            printf("Error: Formato de correo electronico invalido.\n");
        }
    }


    // ---------------------------------------------------------
    // 6. BUCLE DE PLAN
    // ---------------------------------------------------------
    bool plan_valido = false;
    while (!plan_valido)
    {
        printf("Ingrese Plan (Ej: Basico, Premium): ");
        fgets(nuevo_miembro.plan, sizeof(nuevo_miembro.plan), stdin);
        nuevo_miembro.plan[strcspn(nuevo_miembro.plan, "\n")] = 0;

        if (validar_campo(&nuevo_miembro, validarPlan) == TODO_OK)
        {
            plan_valido = true;
        }
        else
        {
            printf("Error: El plan ingresado no existe en el sistema.\n");
        }
    }


    // ---------------------------------------------------------
    // 7. BUCLE DE ESTADO
    // ---------------------------------------------------------
    bool estado_valido = false;
    while (!estado_valido)
    {
        printf("Ingrese Estado (A para Alta, B para Baja): ");

        // El espacio antes del %c es vital para ignorar saltos de línea previos
        scanf(" %c", &nuevo_miembro.estado);
        while(getchar() != '\n'); // Limpiar el buffer inmediatamente

        if (validar_campo(&nuevo_miembro, validarEstado) == TODO_OK)
        {
            estado_valido = true;
        }
        else
        {
            printf("Error: Estado invalido. Ingrese 'A' o 'B'.\n");
        }
    }


    // =========================================================================
    // 8. GUARDADO DEFINITIVO EN MEMORIA
    // =========================================================================
    // Llegar a esta línea significa que TODOS los bucles fueron superados con éxito.

    // A. Lista Principal
    if (lista_m->cantidad == lista_m->capacidad)
    {
        int nueva_cap = (lista_m->capacidad == 0) ? 10 : lista_m->capacidad * 2;
        miembro *temp = (miembro *)realloc(lista_m->array, nueva_cap * sizeof(miembro));
        if (temp == NULL)
        {
            printf("Error fatal: Memoria insuficiente al guardar.\n");
            return;
        }
        lista_m->array = temp;
        lista_m->capacidad = nueva_cap;
    }

    // B. Índice
    if (indice_m->cantidad_elementos_actual == indice_m->cantidad_elementos_maxima)
    {
        unsigned nueva_cap_idx = (indice_m->cantidad_elementos_maxima == 0) ? 10 : indice_m->cantidad_elementos_maxima * 2;
        void *temp_idx = realloc(indice_m->vindice, nueva_cap_idx * sizeof(t_reg_indice));
        if (temp_idx == NULL)
        {
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

void altaTitulo(t_lista_titulos *lista_t, t_indice *indice_t)
{
    printf("\n--- ALTA DE NUEVO TITULO (PELICULA) ---\n");

    titulo nuevo_titulo;
    memset(&nuevo_titulo, 0, sizeof(titulo));

    // ---------------------------------------------------------
    // 1. GENERACIÓN AUTOMÁTICA DEL ID (Autoincremental)
    // ---------------------------------------------------------
    int id_generado = 1; // Valor por defecto si la lista está vacía

    if (lista_t->cantidad > 0)
    {
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
    while (!genero_valido)
    {
        printf("Ingrese el Genero (Accion, Drama, Comedia, Terror): ");
        fgets(nuevo_titulo.genero, sizeof(nuevo_titulo.genero), stdin);
        nuevo_titulo.genero[strcspn(nuevo_titulo.genero, "\n")] = 0;

        if (validar_campo(&nuevo_titulo, validarGenero) == TODO_OK)
        {
            genero_valido = true;
        }
        else
        {
            printf("Error: Genero invalido. Debe ser una de las categorias permitidas.\n");
        }
    }


    // ---------------------------------------------------------
    // 4. INGRESO Y VALIDACIÓN DE STOCK
    // ---------------------------------------------------------
    printf("Ingrese el Stock disponible (VHS): ");
    while (scanf("%d", &nuevo_titulo.stock) != 1)
    {
        printf("Error: Ingrese un numero valido para el stock: ");
        while(getchar() != '\n');
    }
    while(getchar() != '\n');

    validarStock(&nuevo_titulo.stock);


    // =========================================================================
    // 5. GUARDADO DEFINITIVO EN MEMORIA
    // =========================================================================

    // A. Lista Principal
    if (lista_t->cantidad == lista_t->capacidad)
    {
        int nueva_cap = (lista_t->capacidad == 0) ? 10 : lista_t->capacidad * 2;
        titulo *temp = (titulo *)realloc(lista_t->array, nueva_cap * sizeof(titulo));
        if (temp == NULL)
        {
            printf("Error fatal: Memoria insuficiente.\n");
            return;
        }
        lista_t->array = temp;
        lista_t->capacidad = nueva_cap;
    }

    // B. Índice
    if (indice_t->cantidad_elementos_actual == indice_t->cantidad_elementos_maxima)
    {
        unsigned nueva_cap_idx = (indice_t->cantidad_elementos_maxima == 0) ? 10 : indice_t->cantidad_elementos_maxima * 2;
        void *temp_idx = realloc(indice_t->vindice, nueva_cap_idx * sizeof(t_reg_indice));
        if (temp_idx == NULL)
        {
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

void bajaMiembro(t_lista_miembros *lista_m, t_indice *indice_m)
{
    long dni_baja;
    printf("\n--- BAJA DE MIEMBRO ---\n");
    printf("Ingrese el DNI del miembro a dar de baja: ");

    if (scanf("%ld", &dni_baja) != 1)
    {
        printf("Error: Formato de DNI invalido.\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');

    // 1. BUSCAMOS EN EL ÍNDICE
    t_reg_indice ficha_busqueda;
    ficha_busqueda.dni = dni_baja;

    int pos_en_indice = indice_buscar(
                            indice_m, // <--- SOLO EL STRUCT, COMO PIDE TU FUNCIÓN
                            &ficha_busqueda,
                            indice_m->cantidad_elementos_actual,
                            sizeof(t_reg_indice),
                            cmp_miembros_dni
                        );

    if (pos_en_indice == NO_EXISTE)
    {
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

    if (confirmacion != 'S' && confirmacion != 's')
    {
        printf("-> Operacion cancelada. El estado se mantiene en 'A'.\n");
        return;
    }

    // =========================================================================
    // 4. PROCEDEMOS CON LA BAJA
    // =========================================================================

    // ACCIÓN 1: Baja lógica en la lista principal (Cambiamos el estado a 'B')

    lista_m->array[pos_lista].estado = 'B';

    // ACCIÓN 2: Eliminamos del Índice (Desplazamiento a la izquierda)
    for (unsigned i = pos_en_indice; i < indice_m->cantidad_elementos_actual - 1; i++)
    {
        fichas[i] = fichas[i + 1];
    }

    indice_m->cantidad_elementos_actual--;

    printf("\n-> BAJA EXITOSA: El miembro ha sido dado de baja (Estado 'B').\n");
}

void bajaTitulo(t_lista_titulos *lista_t, t_indice *indice_t)
{
    int id_baja;
    printf("\n--- BAJA DE TITULO ---\n");
    printf("Ingrese el ID del titulo a dar de baja: ");

    if (scanf("%d", &id_baja) != 1)
    {
        printf("Error: Formato de ID invalido.\n");
        while(getchar() != '\n');
        return;
    }
    while(getchar() != '\n');

    // 1. BUSCAMOS EN EL ÍNDICE (Usando el campo .dni como contenedor del ID)
    t_reg_indice ficha_busqueda;
    ficha_busqueda.dni = (long)id_baja;

    int pos_en_indice = indice_buscar(
        indice_t, // <--- SOLO EL STRUCT, COMO PIDE TU FUNCIÓN
        &ficha_busqueda,
        indice_t->cantidad_elementos_actual,
        sizeof(t_reg_indice),
        cmp_miembros_dni
    );

    if (pos_en_indice == NO_EXISTE)
    {
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

    if (confirmacion != 'S' && confirmacion != 's')
    {
        printf("-> Operacion cancelada. El titulo se mantiene activo.\n");
        return;
    }

    // =========================================================================
    // 3. PROCEDEMOS CON LA BAJA (SOLO EN EL ÍNDICE)
    // =========================================================================

    // Eliminamos del Índice pisando la ficha (Desplazamiento a la izquierda)
    for (unsigned i = pos_en_indice; i < indice_t->cantidad_elementos_actual - 1; i++)
    {
        fichas[i] = fichas[i + 1];
    }

    // Achicamos el contador del índice
    indice_t->cantidad_elementos_actual--;

    // Nota: lista_t->array[pos_lista] queda intacto en memoria RAM,
    // pero ya no es accesible a través del buscador.

    printf("\n-> BAJA EXITOSA: El titulo ha sido eliminado del acceso publico.\n");
}

int cmp_miembros_dni(const void *a, const void *b)
{
    const t_reg_indice *regA = (const t_reg_indice *)a;
    const t_reg_indice *regB = (const t_reg_indice *)b;

    if (regA->dni < regB->dni) return -1;
    if (regA->dni > regB->dni) return 1;
    return 0;
}

int cmp_titulos_id(const void *a, const void *b)
{
    const t_reg_indice *regA = (const t_reg_indice *)a;
    const t_reg_indice *regB = (const t_reg_indice *)b;

    // Recuerda que guardamos el ID dentro del campo 'dni' de la ficha
    if (regA->dni < regB->dni) return -1;
    if (regA->dni > regB->dni) return 1;
    return 0;
}

void guardar_datos_sesion(t_lista_miembros *lista_m, t_lista_titulos *lista_t, t_lista_alquileres *lista_a, t_fecha fecha_proceso)
{
    char nombre_archivo[100];

    printf("\n>>> GUARDANDO DATOS DE LA SESION (%02d/%02d/%04d) <<<\n", fecha_proceso.dia, fecha_proceso.mes, fecha_proceso.anio);

    // 1. GUARDAR MIEMBROS
    // Usamos el MISMO formato exacto que en el main: miembros_DDMMYYYY.dat
    sprintf(nombre_archivo, "miembros_%02d%02d%04d.dat", fecha_proceso.dia, fecha_proceso.mes, fecha_proceso.anio);
    FILE *f_miembros = fopen(nombre_archivo, "wb");
    if (f_miembros != NULL && lista_m->cantidad > 0)
    {
        fwrite(lista_m->array, sizeof(miembro), lista_m->cantidad, f_miembros);
        fclose(f_miembros);
        printf("-> Miembros guardados con exito en '%s'.\n", nombre_archivo);
    }

    // 2. GUARDAR TÍTULOS
    sprintf(nombre_archivo, "titulos_%02d%02d%04d.dat", fecha_proceso.dia, fecha_proceso.mes, fecha_proceso.anio);
    FILE *f_titulos = fopen(nombre_archivo, "wb");
    if (f_titulos != NULL && lista_t->cantidad > 0)
    {
        // CORREGIDO: sizeof(titulo)
        fwrite(lista_t->array, sizeof(titulo), lista_t->cantidad, f_titulos);
        fclose(f_titulos);
        printf("-> Titulos guardados con exito en '%s'.\n", nombre_archivo);
    }

    // 3. GUARDAR ALQUILERES
    sprintf(nombre_archivo, "alquileres_%02d%02d%04d.dat", fecha_proceso.dia, fecha_proceso.mes, fecha_proceso.anio);
    FILE *f_alq = fopen(nombre_archivo, "wb");
    if (f_alq != NULL && lista_a->cantidad > 0)
    {
        // CORREGIDO: sizeof(t_alquiler)
        fwrite(lista_a->array, sizeof(t_alquiler), lista_a->cantidad, f_alq);
        fclose(f_alq);
        printf("-> Alquileres guardados con exito en '%s'.\n", nombre_archivo);
    }

}

void cargar_miembros_desde_binario(const char *ruta, t_lista_miembros *lista)
{
    FILE *f = fopen(ruta, "rb");
    if (!f) return;

    // Averiguamos cuánto pesa el archivo para pedir la memoria exacta
    fseek(f, 0, SEEK_END);
    int cantidad = ftell(f) / sizeof(miembro);
    rewind(f);

    if (cantidad > 0)
    {
        lista->array = malloc(cantidad * sizeof(miembro));
        lista->capacidad = cantidad;
        lista->cantidad = fread(lista->array, sizeof(miembro), cantidad, f);
        printf("-> %d miembros cargados desde archivo binario.\n", lista->cantidad);
    }
    fclose(f);
}

void cargar_titulos_desde_binario(const char *ruta, t_lista_titulos *lista)
{
    FILE *f = fopen(ruta, "rb");
    if (!f) return;

    fseek(f, 0, SEEK_END);
    int cantidad = ftell(f) / sizeof(titulo);
    rewind(f);

    if (cantidad > 0)
    {
        lista->array = malloc(cantidad * sizeof(titulo));
        lista->capacidad = cantidad;
        lista->cantidad = fread(lista->array, sizeof(titulo), cantidad, f);
        printf("-> %d titulos cargados desde archivo binario.\n", lista->cantidad);
    }
    fclose(f);
}

void cargar_alquileres_desde_binario(const char *ruta, t_lista_alquileres *lista)
{
    FILE *f = fopen(ruta, "rb");
    if (!f) return;

    fseek(f, 0, SEEK_END);
    int cantidad = ftell(f) / sizeof(t_alquiler); // Asumo que tu struct se llama t_alquiler
    rewind(f);

    if (cantidad > 0)
    {
        lista->array = malloc(cantidad * sizeof(t_alquiler));
        lista->capacidad = cantidad;
        lista->cantidad = fread(lista->array, sizeof(t_alquiler), cantidad, f);
        printf("-> %d alquileres cargados desde archivo binario.\n", lista->cantidad);
    }
    fclose(f);
}

