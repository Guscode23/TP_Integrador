#include "Validaciones.h"
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
///ValidarDNI (Macro)
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


///Funcion que valida que el sexo del Miembro sea coherente con el tipo de cuil
int validarIgualdadSexo(char* sexoMiembro,int tipoCuil)
{

     switch (tipoCuil) {
          case 20:
            if(*sexoMiembro=='M')
                return CUIL_VALIDO;
            break;

           case 27:
              if(*sexoMiembro=='F')
                return CUIL_VALIDO;
              break;

           case 30:
              if(*sexoMiembro=='O')
                 return CUIL_VALIDO;
              break;
           }
    return CUIL_INVALIDO;
}


int validarCUIL(const char* cuil,long int dniMiembro,char* sexoMiembro)
{
 long int dni;
 int digVerif;
 int tipo;
 int coeficientes[10]={5,4,3,2,7,6,5,4,3,2};
 int *p_coef=coeficientes;
 int formato;
 char dniAux[11];

 ///Capturo los datos con sscanf
  formato=sscanf(cuil, "%d-%ld-%d",&tipo,&dni,&digVerif);

 ///Validación de casos borde
 if(validarIgualdadDNI(dniMiembro,dni) || formato!=3 || validarIgualdadSexo(sexoMiembro,tipo)==-1)
   //if(validarIgualdadDNI(dniMiembro,dni) || formato==-1)
      return CUIL_INVALIDO;
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
                    return CUIL_VALIDO;
                  break;

                case 1:
                   if((tipo==20 && digVerif==9) ||(tipo==27 && digVerif==4))
                      return CUIL_VALIDO;
                    break;

                default:
                  if(digVerif==(11-resto))
                     return CUIL_VALIDO;
                  break;
               }
            }
    return CUIL_INVALIDO;
}

char*  normalizarApel_Nombre(char * nyapel)
{
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

int validarCorreo(const char* correo)
{

   char dom[20];
   int captura=0;
   char dominios[]="gmail,outlook,empresa,yahoo";


   ///Ignora los caracteres hasta el arroba, y del arroba hasta el punto
   captura = sscanf(correo, "%*[^@]@%[^.]", dom); ///Expresión regular

   if(captura<=0)
       return CORREO_INVALIDO;
     else{
         if(strstr(dominios,dom)!=NULL)
             return CORREO_VALIDO;
        }

    return CORREO_INVALIDO;
}

int validarPlan(const char* plan)
{
   char planes[4][15]={"BASIC","PREMIUM","VIP","FAMILY"};

   for(int i=0;i<=3;i++){
      if(strcmp(plan,*(planes+i))==0)
            return PLAN_VALIDO;
      }
   return PLAN_INVALIDO;
}

///La edad es un campo calculable.Por tanto deberemos hacer una funcion que calcule la edad del miembro

int validarCAT(const char* cat,int edad,char* correo)
{
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

}

int validarGenero(const char* genero)
{
   char generos[4][10]={"Accion","Drama","Comedia","Terror"};

   for(int i=0;i<=3;i++){
      if(strcmp(genero,*(generos+i))==0)
            return GENERO_VALIDO;
      }
   return GENERO_INVALIDO;
}

int insertarEnVector(int **ids, int *cantidad, int nuevoItem) {

    if (nuevoItem < 1)
        return -9;
    // Recorre el vector desde el primero hasta el último elemento. Si el elemento actual es igual al ID que busco, devuelvo 1
    for (int i = 0; i < *cantidad; i++) {
        if ((*ids)[i] == nuevoItem)
            return -9;
    }

    // Si no es duplicado, le pido al sistema operativo un lugar más en memoria para guardar el nuevo ID. (*cantidad + 1) es la nueva cantidad de elementos que necesito
    *ids = realloc(*ids, (*cantidad + 1) * sizeof(int));

    // Guardo el nuevo ID en la última posición del vector y luego aumento la cantidad de elementos en 1
    (*ids)[*cantidad] = nuevoItem;
    (*cantidad)++;

    return 9;
}

void validarStock(int stock) {
    // Si es menor a 1, lo convierte en cero
    if (stock < 1)
    {
        printf("Se convierte valor a cero");
        stock = 0;
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
