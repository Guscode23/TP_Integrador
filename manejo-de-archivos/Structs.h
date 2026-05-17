#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED
#include "fecha.h"

#define TAM_APE_NOM 60
#define TAM_CAT 10
#define TAM_PLAN 10
#define TAM_EMAIL_TUT 30
#define TAM_CUIL 13
#define TAM_TITULO 61
#define TAM_GENERO 21
#define TAM_FAIL 21

typedef struct{
    long dni;
    char CUIL [TAM_CUIL];
    char apeNom[TAM_APE_NOM];
    t_fecha fechNac;
    char sexo;
    t_fecha fechAfil;
    char cat[TAM_CAT];
    t_fecha fechUltCuot;
    char estado;
    char plan[TAM_PLAN];
    char emailTutor[TAM_EMAIL_TUT];
}miembro;

typedef struct{
    int ID;
    char titulo [TAM_TITULO];
    char genero [TAM_GENERO];
    int stock;
}titulo;

typedef struct{
    char validacion_fallida [TAM_FAIL];
    int incidencias;
    long DNI;
}AUDIT_miembro;

typedef struct{
    char validacion_fallida [TAM_FAIL];
    int incidencias;
    int ID;
}AUDIT_titulo;

#endif // STRUCTS_H_INCLUDED
