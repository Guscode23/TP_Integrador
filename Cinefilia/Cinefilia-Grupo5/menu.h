#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "structs.h"
#include "indice.h"


///Realiza la operación de alta del miembro
//void altaMiembro(miembro *miembroOficial,t_indice* indice,t_fecha* fechProceso);
//int cmpDNI(const void* d1, const void* d2);
//int cmpID(const void* d1, const void* d2);

void limpiarBuffer();
char iniciarMenu();

//MENU
void guardar_datos_sesion(t_lista_miembros *lista_m, t_lista_titulos *lista_t, t_lista_alquileres *lista_a, t_fecha fecha_proceso); // k. Salir
void menu_operaciones(t_lista_miembros *lista_m, t_indice *indice_m, t_lista_titulos *lista_t, t_indice *indice_t, t_lista_alquileres *lista_a, t_fecha fecha_proceso);

char menuConErr(const char *mensaje, const char *opciones);

//FUNCIONES COMPARADORAS PARA LOS INDICES (qsort y buscar)
int cmp_miembros_dni(const void *a, const void *b);
int cmp_titulos_id(const void *a, const void *b);

//ABM MIEMBROS Y TITULOS
void altaMiembro(t_lista_miembros *lista_m, t_indice *indice_m);
void bajaMiembro(t_lista_miembros *lista_m, t_indice *indice_m);
void modificarMiembro(t_lista_miembros *lista_m, t_indice *indice, t_fecha *fechProceso);

void altaTitulo(t_lista_titulos *lista_t, t_indice *indice_t);
void bajaTitulo(t_lista_titulos *lista_t, t_indice *indice_t);
void modificarPelicula(t_lista_titulos *lista_t, t_indice *indice, t_fecha *fechProceso);

///Agregado de funciones de muestra
void mostrarMiembro(t_lista_miembros *lista_m, t_indice *indice);
void mostrarSocios_DNI(miembro* t_miembro, int cantidad);
void listarMiembrosPorPlan(miembro* t_miembro, int cantidad);


//HABRIA QUE MOVERLAS
void cargar_miembros_desde_binario(const char *ruta, t_lista_miembros *lista);
void cargar_alquileres_desde_binario(const char *ruta, t_lista_alquileres *lista);
void cargar_titulos_desde_binario(const char *ruta, t_lista_titulos *lista);



#endif // MENU_H_INCLUDED
