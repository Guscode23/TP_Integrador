#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED

#define CUIL_INVALIDO -1
#define CUIL_VALIDO 1
#define CORREO_VALIDO 2
#define CORREO_INVALIDO -2

///Macros a incluir





///Prototipos
int validarCUIL(const char* cuil,long int dniMiembro);
char* normalizarNombre(char* nyapel);
int validarCorreo(const char* correo);



#endif // VALIDACIONES_H_INCLUDED
