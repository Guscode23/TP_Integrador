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
///ValidarDNI (puede ser Macro o no.Es una función simple)
///ValidarFecha_Nacimiento
///ValidarSexo (Macro/Funcion)
///ValidarFecha_Afiliacion
///ValidarCategoría
///ValidarFechaUltimaCuota
///ValidarEstado
///ValidarPlan

/********************************************/
///Validaciones de Titulos Películas
/*********************************************/
///ValidarID_Pelicula
///ValidarTitulo
///ValidarGenero
///ValidarStock

int validarCUIL(const char* cuil,long int dniMiembro){

 long int dni;
 int digVerif;
 int tipo;
 int coeficientes[10]={5,4,3,2,7,6,5,4,3,2};
 int *p_coef=coeficientes;

 ///Capturo los datos con sscanf
 sscanf(cuil, "%d-%ld-%d",&tipo,&dni,&digVerif);


 ///Si el dni del Cuil es distinto al del registro, invalido
 if(dni!=dniMiembro)
      return CUIL_INVALIDO;
    else{

        int result=0;
        int prod=0;
        int resto=0;

        ///Imprimo todos los valores
        for(int i=0;i<=9;i++){
            prod = (*(cuil + i) - '0') * (*(p_coef + i));
            result+=prod;
          }
          resto=result-((result/11)*11);

          if(tipo==20 || tipo==27 || tipo ==30){
             switch (resto) {
               case 0:

               if(digVerif==0)
                   return CUIL_VALIDO;
               break;

               case 1:
               ///Hombre o Mujer
                if((tipo==20 && digVerif==9) ||(tipo==27 && digVerif==4))
                   return CUIL_VALIDO;
                  else
                     return CUIL_INVALIDO;
                break;

                default:
                  if(digVerif==(11-resto))
                     return CUIL_VALIDO;
                break;
            }
              } else
                  return CUIL_INVALIDO;
            }


    return 0;
}

char* normalizarNombre(char* nyapel)
{
  char* ini;
  char* aux;
  char* pcad=nyapel;
  char* fin=nyapel+(strlen(nyapel)-1);
  char* cont;
  char* coma;


  ///Eliminar espacios iniciales
  while(!isalpha(*pcad)){
        pcad++;
   }
    ini=pcad;
   *ini=toupper(*ini);

  ///Eliminar espacios finales
  while(!isalpha(*fin)){
        *fin='\0';
        fin--;
  }

  pcad+=1;
  ///Normalizar la primera palabra
  while(*pcad!=' '){
        *pcad=tolower(*pcad);
         pcad++;
    }

  ///Una vez que tomamos el apellido, buscamos existencia de la coma
  coma=strchr(nyapel,',');

    if(coma==NULL)
      *pcad=',';



  ///Variable auxiiar para el resto de las palabras
  aux=ini;

  ///Ubicarnos dentro de cada palabra para que la letra inicial sea mayuscula
  while((aux=strchr(aux,' '))!=NULL){
     *(aux+1)=toupper(*(aux+1));
       cont=aux+2;

       while(*cont != ' ' && *cont != '\0') {
          *cont = tolower(*cont);
           cont++;
          }
           aux=cont;
        }


    return ini;
}

int validarCorreo(const char* correo)
{

   char dom[20]="";
   int captura=0;
   char dominios[]="gmail,outlook,empresa,yahoo";

   captura=sscanf(correo, "%*s@%s.com.%*s",dom);

   if(captura==-1)
       return CORREO_INVALIDO;
     else{
         if(strstr(dominios,dom)!=NULL)
             return CORREO_VALIDO;
        }

    return CORREO_INVALIDO;
}



