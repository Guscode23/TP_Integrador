#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TODO_OK 1
#define ERROR 0
#define FALLA_DATO 1
#define DATO_OK 0

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
///ULTIMA CUOTA PAGA
int validar_UltimaCuota_Paga(t_fecha* fechAfi, t_fecha* fechUltCuot, t_fecha* fProceso);
int compara_Fechas_Meno_rIgual(t_fecha *fechA, t_fecha *fechB); /// Esta tmbien se podria usar en validar afilacion

#endif // FECHA_H_INCLUDED



