#include <stdio.h>
#include <stdlib.h>
#include "Structs.h"
#include "archivos.h"

int main()
{
    printf("CINEFILIA: Bienvenido\n");

    /* Se solicita y se valida la fecha de proceso.

    - Si el usuario presiona Enter sin ingresar nada, el programa toma la fecha actual del sistema.

    */

    /* El programa comienza a leer los datos de los archivos .csv (;) de miembros y titulos.

       Por cada LINEA/REGISTRO leida/o se extraen campo a campo y se validan.

       Ante el primer campo de un registro que de error, se descarta el registro completo
       guardandolo en una estructura para auditoria (Audit_Miembros,Audit_Titulos)

       Si un registro pasa todas las validaciones, entonces se procede a guardar en memoria,
       supongo que en un array de struct (Miembro o Titulo)

    */


    FILE *archivo1 = fopen("Lotes prueba/miembros.csv", "r");
    if (archivo1 == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return 1;
    } // Se podria hacer todo en una funcion?

    char buffer[MAX_LINEA_CSV];
    char *columnas[11]; // Preparado para leer hasta 11 columnas por fila

    fgets(buffer, sizeof(buffer), archivo1); // Descartar encabezado

    while (csv_leer_fila(archivo1, ';', columnas, 11, buffer, MAX_LINEA_CSV) > 0)
    {

        printf("DNI: %s | Nombre: %s\n", columnas[0], columnas[2]); // Solo para prueba

    }

    fclose(archivo1);


    FILE *archivo2 = fopen("Lotes prueba/titulos.csv", "r");
    if (archivo2 == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return 1;
    } // Se podria hacer todo en una funcion?

    char *columnas2[4]; // Preparado para leer hasta 4 columnas por fila

    fgets(buffer, sizeof(buffer), archivo2); // Descartar encabezado

    while (csv_leer_fila(archivo2, ';', columnas2, 11, buffer, MAX_LINEA_CSV) > 0)
    {

        printf("ID: %s | Genero: %s | Titulo: %s\n", columnas2[0], columnas2[2],columnas2[1]); // Solo para prueba

    }

    fclose(archivo2);


    /*
        Toda la informacion procesada en memoria debe ser guardada en disco segun corresponda.
        El nombre de los nuevos archivos generados deben incluir la fecha de proceso, teniendo en cuenta que al ejecutar
        nuevamente el programa, si la fecha de proceso corresponda con el nombre de estos archivos el sistema cargara directamente estos datos.
    */



    return 0;
}

