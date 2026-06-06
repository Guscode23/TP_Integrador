#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#define TAM_APE_NOM 60
#define TAM_CAT 10
#define TAM_PLAN 10
#define TAM_EMAIL_TUT 30
#define TAM_CUIL 15
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

typedef struct {
    char tipo_error[50];
    int cantidad_incidencias;
    long identificadores_rechazados[100];
} t_auditoria;

typedef struct {
    miembro *array;
    int cantidad;
    int capacidad;
} t_lista_miembros;

typedef struct {
    titulo *array;
    int cantidad;
    int capacidad;
} t_lista_titulos;

typedef struct {
    long dni;
    int idPelicula;
    char estado;
    int cantAlquileres;
} t_alquiler;

typedef struct {
    t_alquiler *array;
    int cantidad;
    int capacidad;
} t_lista_alquileres;

int cmp_miembros_dni(const void *a, const void *b);
int cmp_titulos_id(const void *a, const void *b);

#endif // STRUCTS_H_INCLUDED
