#include "Validaciones.h"
#include "structs.h"
#include "fecha.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/*******************************************/
///Validaciones de Miembros
/******************************************/
///ValidarCUIL (Gus)
///NormalizarNombre (Gus)
///ValidarCorreo (Gus)
///ValidarDNI (Genérica)
//ValidarFecha_Nacimiento (Avanzado)
///ValidarSexo (Macro)
//ValidarFecha_Afiliacion (Avanzado)
///ValidarCategoría
//ValidarFechaUltimaCuota (Avanzado)
///ValidarEstado(Macro)
///ValidarPlan
///Tenemos que agregar una función más que detecte los DNIS duplicados, ya que DNI es clave

/********************************************/
///Validaciones de Titulos Películas
/*********************************************/
///ValidarID_Pelicula
///ValidarTitulo
///ValidarGenero
///ValidarStock


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

///Funcion que valida que el sexo del Miembro sea coherente con el tipo de cuil
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
    char dniAux[11];

    ///Capturo los datos con sscanf
    formato=sscanf(m->CUIL, "%d-%ld-%d",&tipo,&dni,&digVerif);

    ///Validación de casos borde
    if(validarIgualdadDNI(m->dni,dni) || formato!=3 || validarIgualdadSexo(&m->sexo,tipo)==-1)
          return ERROR;
            else{

            int result=0;
            int prod=0;
            int resto=0;

             ///Almacena un entero dentro de una cadena y debería devolver un int
             sprintf(dniAux, "%ld", dni);

            ///Multiplico todos los valores
            for(int i=0;i<=strlen(dniAux)-1;i++){
                prod = (*(dniAux + i) - '0') * (*(p_coef + i));
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
        ///Eliminar espacios iniciales
        while(*lect && (isspace(*lect) || *lect == ','))
            lect++;
        if(*lect)
        {
            posicionPalabra++;
            ///En caso de corresponder a la segunda palabra
            if(posicionPalabra == 2){
                *esc = ',';
                esc++;
            }
            ///En caso de corresponder al resto
            else if(posicionPalabra > 2){
                *esc = ' ';
                esc++;
            }

            ///Bandera que indica primera letra de la palabra
            primeraLetraPalabra = 1;

            ///Normalizar palabra
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


   ///Ignora los caracteres hasta el arroba, y del arroba hasta el punto
   captura = sscanf(m->emailTutor, "%*[^@]@%[^.]", dom); ///Expresión regular

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

///VALIDACION ANTERIOR DE CAT
/*int validarCAT(const char* cat,int edad,char* correo){
    if(strcmp(cat,"MENOR")==0){
        ///Como es menor, validar que el correo no esté vacío
        if(edad<18 && *(correo)!='\0')
            return CAT_VALIDO;
      }
       else if(strcmp(cat,"ADULTO")==0){
           if(edad>=18)
              return CAT_VALIDO;
          }

    return CAT_INVALIDO;

}*/

int validarCAT(const char* cat,int edad){
    if(strcmp(cat,"MENOR")==0){
        //Como es menor, validar que el correo no esté vacío
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
    pelicula *p = (pelicula *)dato;

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
    // Recorre el vector desde el primero hasta el último elemento. Si el elemento actual es igual al ID que busco, devuelvo 1
    for (int i = 0; i < *cantidad; i++) {
        if ((*ids)[i] == nuevoItem)
            return INSERCION_DUPLICADA;
    }

    // Si no es duplicado, le pido al sistema operativo un lugar más en memoria para guardar el nuevo ID. (*cantidad + 1) es la nueva cantidad de elementos que necesito
    *ids = realloc(*ids, (*cantidad + 1) * sizeof(int));

    // Guardo el nuevo ID en la última posición del vector y luego aumento la cantidad de elementos en 1
    (*ids)[*cantidad] = nuevoItem;
    (*cantidad)++;

    return TODO_OK;
}

void validarStock(int *stock) {
    // Si es menor a 1, lo convierte en cero
    if (*stock < 0)
    {
        printf("Se convierte valor a cero\n");
        *stock = 0;
    }
}

char*  normalizarTitulo(char * titulo){
    char * lect = titulo, * esc = titulo;
    int primeraLetraPalabra;
    int posicionPalabra = 0;
    while(*lect)
    {
        ///Eliminar espacios iniciales
        while(*lect && (isspace(*lect) || *lect == ','))
            lect++;
        if(*lect)
        {
            posicionPalabra++;
            ///En caso de corresponder a la segunda palabra
            if(posicionPalabra > 1){
                *esc = ' ';
                esc++;
            }

            ///Bandera que indica primera letra de la palabra
            primeraLetraPalabra = 1;

            ///Normalizar palabra
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
