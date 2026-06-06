#include "Validaciones.h"
#include "structs.h"
#include "fecha.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


int validar_campo(void *dato, int (*funcion_validadora)(void *)) {
    return funcion_validadora(dato);
}

int validarDNI(void *dato) {
    miembro *m = (miembro *)dato;

    if (m->dni > 1000000 && m->dni < 100000000) {
        return TODO_OK;
    }
    return ERROR;
}

int validarIgualdadSexo(char* sexoMiembro,int tipoCuil){

     switch (tipoCuil) {
          case 20:
            if(*sexoMiembro=='M')
                return TODO_OK;
            break;

           case 27:
              if(*sexoMiembro=='F')
                return TODO_OK;
              break;

           case 30:
              if(*sexoMiembro=='O')
                 return TODO_OK;
              break;
           }
    return ERROR;
}

int validarCUIL(void *dato){

    miembro *m = (miembro *)dato;

    long int dni;
    int digVerif;
    int tipo;
    int coeficientes[10]={5,4,3,2,7,6,5,4,3,2};
    int *p_coef=coeficientes;
    int formato;
    char tipoydniAux[11];

    formato=sscanf(m->CUIL, "%d-%ld-%d",&tipo,&dni,&digVerif);

    if(validarIgualdadDNI(m->dni,dni) || formato!=3 || validarIgualdadSexo(&m->sexo,tipo)==0){
          return ERROR;
    }
    else{

            int result=0;
            int prod=0;
            int resto=0;

             sprintf(tipoydniAux, "%d%ld", tipo, dni);

            for(int i=0;i<=strlen(tipoydniAux)-1;i++){
                prod = (*(tipoydniAux + i) - '0') * (*(p_coef + i));
                result+=prod;
              }
              resto=result-((result/11)*11);

                 switch (resto) {
                   case 0:
                      if(digVerif==0)
                        return TODO_OK;
                      break;

                    case 1:
                       if((tipo==20 && digVerif==9) ||(tipo==27 && digVerif==4))
                          return TODO_OK;
                        break;

                    default:
                      if(digVerif==(11-resto))
                         return TODO_OK;
                      break;
                }
            }
    return ERROR;
}

char* normalizarApel_Nombre(char * nyapel){

    char * lect = nyapel, * esc =nyapel;
    int primeraLetraPalabra;
    int posicionPalabra = 0;
    while(*lect)
    {
        while(*lect && (isspace(*lect) || *lect == ','))
            lect++;
        if(*lect)
        {
            posicionPalabra++;
            if(posicionPalabra == 2){
                *esc = ',';
                esc++;
            }
            else if(posicionPalabra > 2){
                *esc = ' ';
                esc++;
            }
            primeraLetraPalabra = 1;

            while(*lect && !isspace(*lect) && *lect != ',')
            {
                *esc = primeraLetraPalabra ? toupper(*lect) : tolower(*lect);
                primeraLetraPalabra = 0;
                esc++;
                lect++;
            }
        }
    }
    *esc = '\0';
    return nyapel;
}

int validarSexo(void *dato) {
    miembro *m = (miembro *)dato;
    if (m->sexo=='F' || m->sexo== 'M' || m->sexo=='O'){
        return TODO_OK;
    }
    return ERROR;
}

int validarEstado(void *dato) {
    miembro *m = (miembro *)dato;
    if (m->estado=='A' || m->estado=='B') {
        return TODO_OK;
    }
    return ERROR;
}

int validarCorreo(void *dato){
    miembro *m = (miembro *)dato;

   char dom[20];
   int captura=0;
   char dominios[]="gmail,outlook,empresa,yahoo";

   captura = sscanf(m->emailTutor, "%*[^@]@%[^.]", dom);

   if(captura<=0)
       return ERROR;
     else{
         if(strstr(dominios,dom)!=NULL)
             return TODO_OK;
        }

    return ERROR;
}

int validarPlan(void *dato){
    miembro *m = (miembro *)dato;
    char planes[4][15]={"BASIC","PREMIUM","VIP","FAMILY"};

    for(int i=0;i<=3;i++){
        if(strcmp(m->plan,*(planes+i))==0)
        return TODO_OK;
    }
    return ERROR;
}

int validarCAT(const char* cat,int edad){
    if(strcmp(cat,"MENOR")==0){
        if(edad<18)
            return TODO_OK;
      }
       else if(strcmp(cat,"ADULTO")==0){
           if(edad>=18)
              return TODO_OK;
          }
    return ERROR;
}

int validarGenero(void *dato) {
    titulo *p = (titulo *)dato;

    char generos[4][10]={"Accion","Drama","Comedia","Terror"};

    for(int i=0;i<=3;i++){
            if(strcmp(p->genero,*(generos+i))==0)
            return TODO_OK;
      }
   return ERROR;
}

int insertarEnVector(int **ids, int *cantidad, int nuevoItem) {

    if (nuevoItem < 1)
        return INSERCION_INVALIDA;
    for (int i = 0; i < *cantidad; i++) {
        if ((*ids)[i] == nuevoItem)
            return INSERCION_DUPLICADA;
    }

    *ids = realloc(*ids, (*cantidad + 1) * sizeof(int));

    (*ids)[*cantidad] = nuevoItem;
    (*cantidad)++;

    return TODO_OK;
}

void validarStock(int *stock) {
    if (*stock < 0)
    {
        *stock = 0;
    }
}

char*  normalizarTitulo(char * titulo){
    char * lect = titulo, * esc = titulo;
    int primeraLetraPalabra;
    int posicionPalabra = 0;
    while(*lect)
    {
        while(*lect && (isspace(*lect) || *lect == ','))
            lect++;
        if(*lect)
        {
            posicionPalabra++;
            if(posicionPalabra > 1){
                *esc = ' ';
                esc++;
            }
            primeraLetraPalabra = 1;
            while(*lect && !isspace(*lect) && *lect != ',')
            {
                *esc = primeraLetraPalabra ? toupper(*lect) : tolower(*lect);
                primeraLetraPalabra = 0;
                esc++;
                lect++;
            }
        }
    }
    *esc = '\0';
    return titulo;
}
