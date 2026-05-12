int esFechaValida(const t_fecha *f){
    if(f->anio >= 1600){
        if(f->mes >= 1 && f->mes <= 12){
            if(f->dia >= 1 && f->dia <= cantDiaMes(f->mes, f->anio)){
                return TODO_OK;
            }
        }
    }
    return ERROR;
}

int cantDiaMes (int mes, int anio){
    int diaMes [13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

    if(mes == 2 && esBisiesto(anio)){
        return 29;
    }

    return diaMes[mes];
}

bool esBisiesto(int anio) {
    return ((anio%4 == 0 && anio%100 != 0) || anio%400 == 0);
}
