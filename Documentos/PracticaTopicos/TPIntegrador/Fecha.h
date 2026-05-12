#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

///TDA
typedef struct{
    int dia, mes, anio;
}t_fecha;

///VALIDACION DE FECHA
int es_Fecha_Valida(const t_fecha *f);
int cant_Dia_Mes (int mes, int anio);
bool es_Bisiesto(int anio);
