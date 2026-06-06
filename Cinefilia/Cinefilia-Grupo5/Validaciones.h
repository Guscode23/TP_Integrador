#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED

#define TODO_OK 1
#define ERROR 0
#define INSERCION_VALIDA 9
#define INSERCION_INVALIDA -9
#define INSERCION_DUPLICADA -10

#define validarIgualdadDNI(dniMiembro,dniCuil) (dniMiembro != dniCuil)

int validar_campo(void *dato, int (*funcion_validadora)(void *));
int validarDNI(void *dato);
int validarGenero(void *dato);
int validarCUIL(void *dato);
char*  normalizarApel_Nombre(char * nyapel);
int validarSexo(void *dato);
int validarEstado(void *dato);
int validarCorreo(void *dato);
int validarPlan(void *dato);
int insertarEnVector(int **ids, int *cantidad, int nuevoItem);
void validarStock(int *stock);
int validarIgualdadSexo(char* sexoMiembro,int tipoCuil);
int validarCAT(const char* cat,int edad);
char* normalizarTitulo(char * titulo);

#endif // VALIDACIONES_H_INCLUDED
