#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "Validaciones.h"
#include <string.h>


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



///Funciones de mostrado de información
void mostrarSocios_DNI(miembro* t_miembro, int cantidad)
{
    ///Llamar a funcion de ordenamiento, o ordenar antes

    // Encabezado con todos los campos encolumnados
    printf("\n%-10s %-13s %-25s %-11s %-4s %-11s %-5s %-11s %-4s %-6s %-25s\n",
           "DNI", "CUIL", "APELLIDO Y NOMBRE", "F. NAC", "SEXO", "F. AFIL", "CAT", "F. ULT CUO", "EST", "PLAN", "EMAIL TUTOR");

    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < cantidad; i++) {
        if ((t_miembro + i)->estado == 'A') {
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

    for (int i = 0; i < cantidad; i++) {
        printf("%-20s ", (t_miembro + i)->apeNom);

        if (strcmp((t_miembro + i)->plan, "BASIC") == 0) {
            printf("%-12ld ", (t_miembro + i)->dni);
        } else {
            printf("%-12s ", "0");
        }

        if (strcmp((t_miembro + i)->plan, "PREMIUM") == 0) {
            printf("%-12ld ", (t_miembro + i)->dni);
        } else {
            printf("%-12s ", "0");
        }

        if (strcmp((t_miembro + i)->plan, "VIP") == 0) {
            printf("%-12ld ", (t_miembro + i)->dni);
        } else {
            printf("%-12s ", "0");
        }

        if (strcmp((t_miembro + i)->plan, "FAMILY") == 0) {
            printf("%-12ld\n", (t_miembro + i)->dni);
        } else {
            printf("%-12s\n", "0");
        }
    }
    printf("-----------------------------------------------------------------------\n");
}












