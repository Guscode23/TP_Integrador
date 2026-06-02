#include "fecha.h"
#include "string.h"

/**************** Validación Fecha **************************/

t_fecha parsearFecha(const char *cadena) {
    t_fecha fecha;
    fecha.dia = 0;
    fecha.mes = 0;
    fecha.anio = 0;

    // Copiamos la cadena porque strtok la modifica
    char copia[11];
    strncpy(copia, cadena, sizeof(copia));
    copia[10] = '\0'; // Nos aseguramos que termine en null

    char *token = strtok(copia, "/");
    if (token == NULL) return fecha;
    fecha.dia = atoi(token);

    token = strtok(NULL, "/");
    if (token == NULL) return fecha;
    fecha.mes = atoi(token);

    token = strtok(NULL, "/");
    if (token == NULL) return fecha;
    fecha.anio = atoi(token);

    return fecha;
}

int es_Fecha_Valida(t_fecha *f){
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

int validarFechaNacimiento(t_fecha *fechNac, t_fecha *fechProceso){
    if ((fechProceso->anio-fechNac->anio)<10)
        return ERROR;
    if ((fechProceso->anio-fechNac->anio)==10){
        if (fechNac->mes > fechProceso->mes)
            return ERROR;
        if (fechNac->mes == fechProceso->mes){
            if (fechNac->dia > fechProceso->dia)
                return ERROR;
        }
    }
    return TODO_OK;
}

int compara_Fechas_MenorIgual(t_fecha *fechMenorIgual, t_fecha *fechMayor){
    //Verifica que fechA <= fechB
    ///detecta cuando A > B para devolver ERROR

    ///Se agrega una validación extra respecto a la diferencia de años, aclarado en la consigna
    if (fechMenorIgual->anio > fechMayor->anio)
        return ERROR;
      if (fechMenorIgual->anio == fechMayor->anio){
             if (fechMenorIgual->mes > fechMayor->mes)
                 return ERROR;
                  if (fechMenorIgual->mes == fechMayor->mes){
                      if (fechMenorIgual->dia > fechMayor->dia)
                           return ERROR;
                       }
                  }
    return TODO_OK; /// fechA <= fechB
}

int validarFechaAfiliacion(t_fecha* fechAfil,t_fecha* fechNac,t_fecha* fechProceso){
     int cmp1=compara_Fechas_MenorIgual(fechNac,fechAfil);
     int cmp2=compara_Fechas_MenorIgual(fechAfil,fechProceso);

       if(cmp1==TODO_OK && cmp2 ==TODO_OK)
           return TODO_OK;

    return ERROR;
}

//FECHA ULTIMA CUOTA PAGA
///usa ese ERROR para saber si el orden lógico de las fechas se rompió.
// fechAfi  <=  fechUltCuot  <=  fProceso

int validar_UltimaCuota_Paga(t_fecha* fechAfi,t_fecha* fechUltCuot, t_fecha* fProceso){
     ///Verifica que fechAfi <= fechUltCuot

    if(compara_Fechas_MenorIgual(fechAfi, fechUltCuot) == ERROR)
        return ERROR; //La afiliación es POSTERIOR a la última cuota , no tiene sentido

      //Verifica que fechUltCuot <= fProceso
    if(compara_Fechas_MenorIgual(fechUltCuot, fProceso) == ERROR)
        return ERROR; ///La última cuota es POSTERIOR a hoy , no tiene sentido

    return TODO_OK;
}

int calcularEdad(t_fecha* fechProceso, t_fecha* fechNac){
   int edad=fechProceso->anio-fechNac->anio;

    if(fechProceso->mes < fechNac->mes)
        edad-=1;
      else if(fechProceso->mes == fechNac->mes)
              if(fechProceso->dia < fechNac->dia)
                    edad-=1;

    return edad;
}

void solicitar_Fecha_Proceso(t_fecha *fecha_proceso) {
    char entrada[20];
    bool fechaValida = false;

    while(!fechaValida)
    {
        printf("Ingrese la fecha de proceso (DD MM AAAA) o presione Enter para la actual: \n");

        if(fgets(entrada, sizeof(entrada), stdin) != NULL)
        {
            // CASO 1 : EL USUARIO PRESIONA ENTER
            if (entrada[0] == '\n')
            {
                time_t t = time(NULL);
                struct tm *tm_info = localtime(&t);

                // Usamos -> porque fecha_proceso es un puntero
                fecha_proceso->dia = tm_info->tm_mday;
                fecha_proceso->mes = tm_info->tm_mon + 1;
                fecha_proceso->anio = tm_info->tm_year + 1900;

                printf("Se tomara la fecha actual del sistema: %02d/%02d/%04d\n",
                       fecha_proceso->dia, fecha_proceso->mes, fecha_proceso->anio);
                fechaValida = true;
            }
            // CASO 2: EL USUARIO INGRESA TEXTO
            else
            {
                // Extraemos a las direcciones de memoria de los campos (nota el & antes)
                if (sscanf(entrada, "%d %d %d", &fecha_proceso->dia, &fecha_proceso->mes, &fecha_proceso->anio) == 3)
                {
                    // fecha_proceso YA es un puntero, así que lo pasamos directamente sin el &
                    if (es_Fecha_Valida(fecha_proceso) == TODO_OK) {
                        printf("Fecha de proceso establecida: %02d/%02d/%04d\n",
                               fecha_proceso->dia, fecha_proceso->mes, fecha_proceso->anio);

                        fechaValida = true;
                    } else {
                        printf("\nFecha invalida. Por favor use el formato DD MM AAAA.\n\n");
                    }
                }
                else {
                    printf("\nFormato invalido. Por favor use el formato DD MM AAAA.\n\n");
                }
            }
        }
    }
}
