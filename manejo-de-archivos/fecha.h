#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define TODO_OK 1
#define ERROR 0

///TDA
typedef struct{
    int dia, mes, anio;
}t_fecha;


///VALIDACION DE FECHA
int es_Fecha_Valida(const t_fecha *f);
int cant_Dia_Mes (int mes, int anio);
bool es_Bisiesto(int anio);

void solicitar_Fecha_Proceso(t_fecha *fecha_proceso);


