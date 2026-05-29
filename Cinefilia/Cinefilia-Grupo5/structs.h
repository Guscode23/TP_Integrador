#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#define TAM_APE_NOM 60
#define TAM_CAT 10
#define TAM_PLAN 10
#define TAM_EMAIL_TUT 30
#define TAM_CUIL 13
#define TAM_TITULO 61
#define TAM_GENERO 21
#define TAM_FAIL 21

#include "fecha.h"

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

// Estructura de auditoría de doble entrada
typedef struct {
    char tipo_error[50];
    int cantidad_incidencias;
    long dnis_rechazados[100];
} t_auditoria;

#endif // STRUCTS_H_INCLUDED
