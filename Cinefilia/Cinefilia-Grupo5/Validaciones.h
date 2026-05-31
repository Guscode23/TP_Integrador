#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED

#define TODO_OK 1
#define ERROR 0
#define CORREO_VALIDO 2
#define CORREO_INVALIDO -2
#define DNI_VALIDO 3
#define DNI_INVALIDO -3
#define SEXO_VALIDO 4
#define SEXO_INVALIDO -4
#define CAT_VALIDO 5
#define CAT_INVALIDO -5
#define ESTADO_VALIDO 6
#define ESTADO_INVALIDO -6
#define PLAN_VALIDO 7
#define PLAN_INVALIDO -7
#define GENERO_VALIDO 8
#define GENERO_INVALIDO -8
#define INSERCION_VALIDA 9
#define INSERCION_INVALIDA -9
#define INSERCION_DUPLICADA -10


///Macros a incluir
#define validarSEXO(sexo) (sexo=='F' || sexo== 'M' || sexo=='O') ? SEXO_VALIDO: SEXO_INVALIDO
#define validarESTADO(estado) (estado=='A' || estado=='B') ? ESTADO_VALIDO : ESTADO_INVALIDO
#define validarIgualdadDNI(dniMiembro,dniCuil) (dniMiembro != dniCuil)

///Prototipos
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
