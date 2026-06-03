#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "structs.h"
#include "indice.h"


///Realiza la operación de alta del miembro
void altaMiembro(miembro *miembroOficial,t_indice* indice,t_fecha* fechProceso);
int cmpDNI(const void* d1, const void* d2);
int cmpID(const void* d1, const void* d2);
void limpiarBuffer();
char iniciarMenu();
char menuConErr(const char *mensaje, const char *opciones);
void menu_operaciones(char opcion);

///Funciones de modificacion
void modificarMiembro(t_lista_miembros *lista_m, t_indice *indice, t_fecha *fechProceso);
void modificarPelicula(t_lista_titulos *lista_t, t_indice *indice, t_fecha *fechProceso);

///Agregado de funciones de muestra
void mostrarMiembro(t_lista_miembros *lista_m, t_indice *indice);
void mostrarSocios_DNI(miembro* t_miembro, int cantidad);
void listarMiembrosPorPlan(miembro* t_miembro, int cantidad);




#endif // MENU_H_INCLUDED
