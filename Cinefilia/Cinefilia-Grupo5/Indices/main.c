#include "indice.h"
#include <stdlib.h>
#include <string.h>

///Toma memoria para 100 elementos e inicializa la estructura vacía

void indice_crear(t_indice *indice, size_t nmemb, size_t tamanyo)
{
   indice->vindice=malloc(nmemb*tamanyo);

   if(indice->vindice==NULL){
      printf("No se pudo crear el indice");
      exit(0);
      }

   indice->cantidad_elementos_actual=0;
   indice->cantidad_elementos_maxima=nmemb;

}

///Redimensiona lo reservado en memoria
void indice_redimensionar(t_indice *indice, size_t nmemb, size_t tamanyo)
{

  indice->vindice=realloc(indice->vindice,(INCREMENTO*nmemb)*tamanyo);

  if(indice->vindice==NULL){
    printf("No se pudo redimensionar el indice");
    exit(0);
  }

}

///Es un insertar Ordenado, pero genérico
int indice_insertar(t_indice *indice, const void *registro, size_t tamanyo, int (*cmp)(const void *, const void *))
{

   void* pIndice=indice->vindice;
   void* aux = ((char*)pIndice + (indice->cantidad_elementos_actual) * tamanyo);
   void* insercion;
   int despl=0;


   if(indice->cantidad_elementos_actual==0){
         memcpy(aux,registro,tamanyo); ///Reemplazo directo cuando el indice inicialmente está vacío
         indice->cantidad_elementos_actual+=1;
         return OK;
      }else if(indice->cantidad_elementos_actual>=1)
              aux-=tamanyo;


    if(indice->cantidad_elementos_actual<indice->cantidad_elementos_maxima){


       ///Si inserto un número más grande que el último número, hago un reemplazo directo
       if(cmp(aux,registro)<0)
             memcpy(aux + tamanyo,registro,tamanyo);

      while(pIndice<=aux){

           if(cmp(registro,pIndice)<0){
               insercion=pIndice;


           ///Desplazo elementos hacia la derecha
              despl=((char*)aux - (char*)insercion) / tamanyo;

              for(int i=0;i<=despl;i++){
                memcpy(aux+tamanyo,aux,tamanyo);
                aux = (indice->cantidad_elementos_actual == 1) ? pIndice : (aux - tamanyo);

              }

               ///Reemplazo
               memcpy(insercion,registro,tamanyo);
               break;
             }
             pIndice = (char*)pIndice + tamanyo;
           }
           indice->cantidad_elementos_actual+=1;
        }
         else{
        return ERROR; ///No se puede insertar elemento
     }

     return OK;
}

int indice_cargar(const char* path, t_indice* indice, void *vreg_ind, size_t tamanyo, int (*cmp)(const void *, const void *))
{
   char linea[256];
    t_reg_indice idx;
    unsigned nro_reg = 0;

    FILE* pf = fopen(path, "rt");
    if(!pf)
        return ERROR;

    /// Ignoro el encabezado
    fgets(linea, sizeof(linea), pf);

    while(fgets(linea, sizeof(linea), pf) != NULL) {
        ///Traigo el primer campo de la linea
        if (sscanf(linea, "%ld", &idx.dni) == 1) {

            idx.nro_reg = nro_reg;
            if(indice_insertar(indice, &idx, tamanyo, cmp) == OK) {
                nro_reg++;
            } else {
                fclose(pf);
                return ERROR;
            }
        } else {
            fclose(pf);
            return ERROR;
        }
    }

    /// Cierre de Archivo
    fclose(pf);
    return OK;



}

///En esta función es conveniente utilizar búsqueda binaria

int indice_buscar (const t_indice *indice, const void *registro, size_t nmemb, size_t tamanyo, int (*cmp)(const void *, const void *))
{
    void* base=indice->vindice;
    void* ini=indice->vindice;
    void* fin= (char*)ini + ((indice->cantidad_elementos_actual)-1)*tamanyo;
    int pos=0;

    while(ini<=fin){

        int medio=(((fin - ini) / tamanyo) + 1) / 2;
        char* P_medio = (medio==0) ? fin : (char*)ini + ((medio)-1)*tamanyo;

         if(cmp(registro,(const void*)P_medio)==0){
                pos=((char*)P_medio - (char*)base) / tamanyo;
                return pos;

          }else if(cmp(registro,(const void*)P_medio)<0)
                fin=P_medio-tamanyo;
            else
                ini=P_medio+tamanyo;
        }

        return NO_EXISTE;
}


int indice_eliminar(t_indice *indice, const void *registro, size_t tamanyo, int (*cmp)(const void *, const void *))
{
    void* i=indice->vindice;
    void* ult=i+(indice->cantidad_elementos_actual-1)*tamanyo;
    size_t bytes;

    while(i<=ult && cmp(registro,i)>0)
        i+=tamanyo;
    if(i>ult || cmp(registro,i)<0)
        return ERROR;

    bytes=(size_t)(ult-i);
    if (bytes>0)
        memmove(i,i+tamanyo,bytes);

    indice->cantidad_elementos_actual--;

    return OK;
}

int indice_vacio(const t_indice *indice) {
    return (!indice || indice->cantidad_elementos_actual == 0) ? OK : ERROR;
}

int indice_lleno(const t_indice *indice) {
    if (!indice) return 0;
    return (indice->cantidad_elementos_actual >= indice->cantidad_elementos_maxima) ? OK : ERROR;
}

void indice_vaciar(t_indice* indice) {
    if (!indice) return;
    indice->cantidad_elementos_actual = 0;
    free(indice->vindice);
}




