#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define FECHA_VALIDA 9
#define FECHA_INVALIDA -9
#define FECH_AFIL_VALIDA 11
#define FECH_AFIL_INVALIDA -11

#define FALLA_DATO -10
#define DATO_OK 10
#define TODO_OK 1
#define ERROR 0


typedef struct{
    int dia, mes, anio;
}t_fecha;

t_fecha parsearFecha(const char *cadena);

int validar_UltimaCuota_Paga(t_fecha* fechAfi, t_fecha* fechUltCuot, t_fecha* fProceso);
int compara_Fechas_MenorIgual(t_fecha *fechNac, t_fecha *fechProceso);
int validarFechaAfiliacion(t_fecha* fechAfiliacion,t_fecha* fechNac,t_fecha* fechProceso);
int validarFechaNacimiento(t_fecha *fechNac, t_fecha *fechProceso);
int calcularEdad(t_fecha* fechProceso, t_fecha* fechNac);
int es_Fecha_Valida(t_fecha *f);
int cant_Dia_Mes (int mes, int anio);
bool es_Bisiesto(int anio);
void solicitar_Fecha_Proceso(t_fecha *fecha_proceso);

#endif // FECHA_H_INCLUDED

