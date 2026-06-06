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
void menu_operaciones(t_lista_miembros *lista_m, t_indice *indice_m, t_lista_titulos *lista_t, t_indice *indice_t, t_lista_alquileres *lista_a, t_fecha *fecha_proceso);

char menuConErr(const char *mensaje, const char *opciones);

//ABM MIEMBROS Y TITULOS
void altaMiembro(t_lista_miembros *lista_m, t_indice *indice_m, t_fecha fecha_proceso);
void bajaMiembro(t_lista_miembros *lista_m, t_indice *indice_m);
void modificarMiembro(t_lista_miembros *lista_m, t_indice *indice, t_fecha *fechProceso);

void altaTitulo(t_lista_titulos *lista_t, t_indice *indice_t);
void bajaTitulo(t_lista_titulos *lista_t, t_indice *indice_t);
void modificarTitulo(t_lista_titulos *lista_t, t_indice *indice, t_fecha *fechProceso);

///CARGAR ALQUILER
void registrarAlquiler(t_lista_alquileres *lista_a, t_lista_miembros *lista_m, t_lista_titulos *lista_t, t_indice *indice_m, t_indice *indice_t);

///Agregado de funciones de muestra
void mostrarMiembro(t_lista_miembros *lista_m, t_indice *indice);
void listar_miembros_por_dni(t_lista_miembros *lista_m, t_indice *indice_m);
void listarMiembrosPorPlan(t_lista_miembros *lista_m, t_indice *indice_m);


//HABRIA QUE MOVERLAS
void cargar_miembros_desde_binario(const char *ruta, t_lista_miembros *lista);
void cargar_alquileres_desde_binario(const char *ruta, t_lista_alquileres *lista);
void cargar_titulos_desde_binario(const char *ruta, t_lista_titulos *lista);



#endif // MENU_H_INCLUDED
