#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "structs.h"
#include "indice.h"


///Realiza la operación de alta del miembro
void altaMiembro(miembro *miembroOficial,t_indice* indice,t_fecha* fechProceso);
int cmpDNI(const void* d1, const void* d2);
void limpiarBuffer();
char iniciarMenu();
char menuConErr(const char *mensaje, const char *opciones);
void menu_operaciones(char opcion);



#endif // MENU_H_INCLUDED
