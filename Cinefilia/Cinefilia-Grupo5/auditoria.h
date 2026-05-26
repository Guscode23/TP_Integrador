#ifndef AUDITORIA_H_INCLUDED
#define AUDITORIA_H_INCLUDED

#include "archivos.h"
#include "structs.h"

void generar_reporte_auditoria(const char *ruta_txt, t_auditoria *arreglo_auditorias, int cant_tipos_error);


#endif // AUDITORIA_H_INCLUDED
