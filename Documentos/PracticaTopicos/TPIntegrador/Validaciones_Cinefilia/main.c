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
 int formato;

 ///Capturo los datos con sscanf
  formato=sscanf(cuil, "%d-%ld-%d",&tipo,&dni,&digVerif);

 ///Si el dni del Cuil es distinto al del registro, invalido
 if(dni!=dniMiembro || formato==-1)
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

int validarPlan(const char* plan)
{
   char planes[]="BASIC,PREMIUM,VIP,FAMILY";

   if(strstr(planes,plan)==NULL)
        return PLAN_INVALIDO;

  return PLAN_VALIDO;
}

///La edad es un campo calculable,a partir de

int validarCAT(const char* cat,int edad)
{
    if(strcmp(cat,"MENOR")==0){
        if(edad<18)
            return CAT_VALIDO;
      }
       else if(strcmp(cat,"ADULTO")==0){
           if(edad>=18)
              return CAT_VALIDO;
          }

    return CAT_INVALIDO;

}

int esDuplicado(int *ids, int cantidad, int idBuscado) {

    // Recorre el vector desde el primero hasta el último elemento. Si el elemento actual es igual al ID que busco, devuelvo 1
    for (int i = 0; i < cantidad; i++) {
        if (ids[i] == idBuscado)
            return 1;
    }

    return 0;
}

int insertarIdPelicula(int **ids, int *cantidad, int nuevoId) {

    if (esDuplicado(*ids, *cantidad, nuevoId) == 1) // Llamo a la función de arriba para saber si ya existe. Si es duplicado, aviso y salgo sin insertar
        return 1;

    // Si no es duplicado, le pido al sistema operativo un lugar más en memoria para guardar el nuevo ID. (*cantidad + 1) es la nueva cantidad de elementos que necesito
    *ids = realloc(*ids, (*cantidad + 1) * sizeof(int));

    // Guardo el nuevo ID en la última posición del vector y luego aumento la cantidad de elementos en 1
    (*ids)[*cantidad] = nuevoId;
    (*cantidad)++;

    return 0;
}

int obtenerVectorPeliculas(const char *nombreArchivo){
    int cantidad = 0;  // Declaro la cantidad de elementos del vector. Arranca con 0
    int *ids = NULL;   // Declaro el vector de IDs, que arranca vacío, sin memoria asignada todavía

    FILE *archivo = fopen(nombreArchivo, "r"); // Abro el archivo CSV en modo lectura

    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    char linea[256]; // Creo un buffer (espacio temporal con una cantidad de caracteres arbitraria) para guardar cada línea que leo del archivo

    fgets(linea, sizeof(linea), archivo); // Leo la primera línea del CSV (el encabezado) y la descarto

    
    while (fgets(linea, sizeof(linea), archivo) != NULL) {

        // strtok corta la linea cada vez que encuentra una coma ",". La primera vez le paso la línea, y me devuelve el primer campo (el ID)
        char *token = strtok(linea, ",");
        if (token == NULL) continue;
        // atoi convierte el texto del ID al número entero. Si no lo identifica como número, lo convierte en cero
        int id = atoi(token);
        if (id > 0) {

            // Llamo a la función que inserta el ID y guardo el resultado
            int resultado = insertarIdPelicula(&ids, &cantidad, id);
            if (resultado == 1)       // Si devolvió 1, el ID ya existía
                printf("ID %d DUPLICADO\n", id);
        }
        else
            printf("ID %d ES IGUAL A CERO", id);
    }

    fclose(archivo);
    printf("\nIDs únicos encontrados: %d\n", cantidad);
    free(ids);
    return 0;
}

int validarStock(int stock) {
    if (stock >= 1)
        return stock;
    // Si no es mayor o igual a 1, devuelve cero
    return 0;
}