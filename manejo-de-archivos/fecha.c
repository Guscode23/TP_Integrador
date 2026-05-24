#include "fecha.h"

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
