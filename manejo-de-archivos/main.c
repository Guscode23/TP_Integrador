#include <stdio.h>
#include <stdlib.h>
#include "Structs.h"

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



    /*
        Toda la informacion procesada en memoria debe ser guardada en disco segun corresponda.
        El nombre de los nuevos archivos generados deben incluir la fecha de proceso, teniendo en cuenta que al ejecutar
        nuevamente el programa, si la fecha de proceso corresponda con el nombre de estos archivos el sistema cargara directamente estos datos.
    */



    return 0;
}
