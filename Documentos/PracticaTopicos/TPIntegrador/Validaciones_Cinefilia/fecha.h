#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TODO_OK 1
#define ERROR 0

///TDA
typedef struct{
    int dia, mes, anio;
}t_fecha;

///MAIN
void ingresar_Fecha_Proceso(t_fecha *f);

///VALIDACION DE FECHA
int es_Fecha_Valida(const t_fecha *f);
int cant_Dia_Mes (int mes, int anio);
bool es_Bisiesto(int anio);
