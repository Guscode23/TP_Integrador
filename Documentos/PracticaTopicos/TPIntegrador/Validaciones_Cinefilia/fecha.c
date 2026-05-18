#include "fecha.h"

void ingresar_Fecha_Proceso(t_fecha *f){
    printf("Bienvenido/a.\nIngrese fecha de proceso (DD/MM/AAAA): ");
    scanf("%d / %d / %d", &f->dia, &f->mes, &f->anio);

    while(es_Fecha_Valida(f) != TODO_OK){

        printf("Fecha invalida.\nIngrese nuevamente (DD/MM/AAAA): ");
        scanf("%d / %d / %d", &f->dia, &f->mes, &f->anio);
    }
}
/**************** Validación Fecha **************************/

int es_Fecha_Valida(const t_fecha *f){
    if(f->anio >= 1600){
        if(f->mes >= 1 && f->mes <= 12){
            if(f->dia >= 1 && f->dia <= cant_Dia_Mes(f->mes, f->anio)){
                return TODO_OK;
            }
        }
    }
    return ERROR;
}

int cant_Dia_Mes (int mes, int anio){
    int diaMes [13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

    if(mes == 2 && es_Bisiesto(anio)){
        return 29;
    }

    return diaMes[mes];
}

bool es_Bisiesto(int anio) {
    return ((anio%4 == 0 && anio%100 != 0) || anio%400 == 0);
}

//FECHA ULTIMA CUOTA PAGA
///usa ese ERROR para saber si el orden lógico de las fechas se rompió.
// fechAfi  <=  fechUltCuot  <=  fProceso

int validar_UltimaCuota_Paga(t_fecha* fechAfi,t_fecha* fechUltCuot, t_fecha* fProceso){
     ///Verifica que fechAfi <= fechUltCuot

    if(compara_Fechas_MenorIgual(fechAfi, fechUltCuot) == ERROR)
        return FALLA_DATO; //La afiliación es POSTERIOR a la última cuota , no tiene sentido

      //Verifica que fechUltCuot <= fProceso
    if(comparaFechasMenorIgual(fechUltCuot, fProceso) == ERROR)
        return FALLA_DATO; ///La última cuota es POSTERIOR a hoy , no tiene sentido

    return DATO_OK;

}

int compara_Fechas_Meno_rIgual(t_fecha *fechA, t_fecha *fechB)
{
    //Verifica que fechA <= fechB
    ///detecta cuando A > B para devolver ERROR

    if (fechA->anio > fechB->anio)
        return ERROR;
    if (fechA->anio == fechB->anio)   /////Si el año de A ya es mayor, no hace falta seguir comparando.
    {
        if (fechA->mes > fechB->mes)
            return ERROR;
        if (fechA->mes == fechB->mes)
        {
            if (fechA->dia > fechB->dia)
                return ERROR;
        }
    }
    return TODO_OK; /// fechA <= fechB
}








