#include "fecha.h"

void ingresar_Fecha_Proceso(t_fecha *f){
    printf("Bienvenido/a.\nIngrese fecha de proceso (DD/MM/AAAA): ");
    scanf("%d / %d / %d", &f->dia, &f->mes, &f->anio);

    while(es_Fecha_Valida(f) != FECHA_VALIDA){

        printf("Fecha invalida.\nIngrese nuevamente (DD/MM/AAAA): ");
        scanf("%d / %d / %d", &f->dia, &f->mes, &f->anio);
    }
}
/**************** Validación Fecha **************************/

int es_Fecha_Valida(t_fecha *f){
    if(f->anio >= 1600){
        if(f->mes >= 1 && f->mes <= 12){
            if(f->dia >= 1 && f->dia <= cant_Dia_Mes(f->mes, f->anio)){
                return FECHA_VALIDA;
            }
        }
    }
    return FECHA_INVALIDA;
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

int compara_Fechas_MenorIgual(t_fecha *fechNac, t_fecha *fechProceso)
{
    //Verifica que fechA <= fechB
    ///detecta cuando A > B para devolver ERROR

    ///Se agrega una validación extra respecto a la diferencia de años, aclarado en la consigna
    if (fechNac->anio > fechProceso->anio || (fechProceso->anio-fechNac->anio)<10)
        return FECHA_INVALIDA;
      if (fechNac->anio == fechProceso->anio){  /////Si el año de A ya es mayor, no hace falta seguir comparando.
             if (fechNac->mes > fechProceso->mes)
                 return FECHA_INVALIDA;
                  if (fechNac->mes == fechProceso->mes){
                      if (fechNac->dia > fechProceso->dia)
                           return FECHA_INVALIDA;
                       }
                  }
    return FECHA_VALIDA; /// fechA <= fechB
}

int validarFechaAfiliacion(t_fecha* fechAfil,t_fecha* fechNac,t_fecha* fechProceso)
{
     int cmp1=compara_Fechas_MenorIgual(fechNac,fechAfil);
     int cmp2=compara_Fechas_MenorIgual(fechAfil,fechProceso);

       if(cmp1==FECHA_VALIDA &&cmp2 ==FECHA_VALIDA)
           return FECH_AFIL_VALIDA;

    return FECH_AFIL_INVALIDA;


}

//FECHA ULTIMA CUOTA PAGA
///usa ese ERROR para saber si el orden lógico de las fechas se rompió.
// fechAfi  <=  fechUltCuot  <=  fProceso

int validar_UltimaCuota_Paga(t_fecha* fechAfi,t_fecha* fechUltCuot, t_fecha* fProceso){
     ///Verifica que fechAfi <= fechUltCuot

    if(compara_Fechas_MenorIgual(fechAfi, fechUltCuot) == FECHA_INVALIDA)
        return FALLA_DATO; //La afiliación es POSTERIOR a la última cuota , no tiene sentido

      //Verifica que fechUltCuot <= fProceso
    if(compara_Fechas_MenorIgual(fechUltCuot, fProceso) == FECHA_INVALIDA)
        return FALLA_DATO; ///La última cuota es POSTERIOR a hoy , no tiene sentido

    return DATO_OK;

}

int calcularEdad(t_fecha* fechProceso, t_fecha* fechNac)
{
   int edad=fechProceso->anio-fechNac->anio;

    if(fechProceso->mes < fechNac->mes)
        edad-=1;
      else if(fechProceso->mes == fechNac->mes)
              if(fechProceso->dia < fechNac->dia)
                    edad-=1;

    return edad;
}










