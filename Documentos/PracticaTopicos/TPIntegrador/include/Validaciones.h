#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED

#define CUIL_INVALIDO -1
#define CUIL_VALIDO 1
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


///Macros a incluir
#define validarDNI(dni) (dni>=1000000 && dni<=100000000) ? DNI_VALIDO : DNI_INVALIDO
#define validarSEXO(sexo) (sexo=='F' || sexo== 'M' || sexo=='O') ? SEXO_VALIDO: SEXO_INVALIDO
#define validarEstado(estado) (estado=='A' || estado=='B') ? ESTADO_VALIDO : ESTADO_INVALIDO
//#define validarGenero(genero) (genero=="Accion" || genero=='Drama' || genero=='Comedia' || genero=='Terror') ? GENERO_VALIDO : GENERO_INVALIDO
#define validarIgualdadDNI(dniMiembro,dniCuil) (dniMiembro != dniCuil)

///Prototipos
int validarCUIL(const char* cuil,long int dniMiembro,char* sexoMiembro);
int validarCAT(const char* cat,int edad,char* correo);
char*  normalizarApel_Nombre(char * nyapel);
int validarCorreo(const char* correo);
int validarPlan(const char* plan);
int validarGenero(const char* genero);
int esDuplicado(int *ids, int cantidad, int idBuscado);
int insertarEnVector(int **ids, int *cantidad, int nuevoId);
int obtenerVectorPeliculas(const char *nombreArchivo);
int validarStock(int stock);
int validarIgualdadSexo(char* sexoMiembro,int tipoCuil);

#endif // VALIDACIONES_H_INCLUDED
