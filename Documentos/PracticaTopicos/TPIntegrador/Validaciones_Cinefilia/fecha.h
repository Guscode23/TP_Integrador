#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

///ValdacionFecha
#define FECHA_VALIDA 9
#define FECHA_INVALIDA -9
#define FECH_AFIL_VALIDA 11
#define FECH_AFIL_INVALIDA -11

///ÚLtima cuota paga
#define FALLA_DATO -10
#define DATO_OK 10

///TDA
typedef struct{
    int dia, mes, anio;
}t_fecha;

///MAIN
void ingresar_Fecha_Proceso(t_fecha *f);

///VALIDACION DE FECHA
int es_Fecha_Valida(t_fecha *f);
int cant_Dia_Mes (int mes, int anio);
bool es_Bisiesto(int anio);
///ULTIMA CUOTA PAGA
int validar_UltimaCuota_Paga(t_fecha* fechAfi, t_fecha* fechUltCuot, t_fecha* fProceso);
int compara_Fechas_MenorIgual(t_fecha *fechNac, t_fecha *fechProceso); /// Esta tmbien se podria usar en validar afilacion
int validarFechaAfiliacion(t_fecha* fechAfiliacion,t_fecha* fechNac,t_fecha* fechProceso);

#endif // FECHA_H_INCLUDED



