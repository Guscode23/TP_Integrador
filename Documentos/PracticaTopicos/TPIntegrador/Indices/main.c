#include "indice.h"
#include <stdlib.h>
#include <string.h>

///Toma memoria para 100 elementos e inicializa la estructura vacía

void indice_crear(t_indice *indice, size_t nmemb, size_t tamanyo)
{

   t_reg_indice* p_indice=(t_reg_indice*)indice->vindice;

   p_indice=(t_reg_indice*)malloc(nmemb*tamanyo);

   if(p_indice==NULL){
      printf("No se pudo crear el indice");
      exit(0);
      }

   indice->cantidad_elementos_actual=0;
   indice->cantidad_elementos_maxima=CANTIDAD_ELEMENTOS;

}

///Redimensiona lo reservado en memoria
void indice_redimensionar(t_indice *indice, size_t nmemb, size_t tamanyo)
{
  t_reg_indice* p_indice=(t_reg_indice*)indice->vindice;

  p_indice=realloc(p_indice,(INCREMENTO*nmemb)*tamanyo);

  if(p_indice==NULL){
    printf("No se pudo redimensionar el indice");
    exit(0);
  }

}

///Es un insertar Ordenado, pero genérico
int indice_insertar(t_indice *indice, const void *registro, size_t tamanyo, int (*cmp)(const void *, const void *))
{

   void* pIndice=indice->vindice;
   void* aux= (char*) pIndice+ (indice->cantidad_elementos_actual)*tamanyo;
   void* insercion;
   int despl=0;


   if(indice->cantidad_elementos_actual<indice->cantidad_elementos_maxima){


       ///Si inserto un número más grande que el último número, hago un reemplazo directo
       if(cmp(aux,registro)<0)
             memcpy((char*)aux+(1*tamanyo),registro,tamanyo);

      while(pIndice<=aux){

           if(cmp(registro,pIndice)<0){
               insercion=pIndice;


           ///Desplazo elementos hacia la derecha
              despl=(aux-insercion)+1;

              for(int i=1;i<=despl;i++){
                memcpy(aux+(1*tamanyo),aux,tamanyo);
                pIndice-=tamanyo;
              }

               ///Reemplazo
                  memcpy(insercion,registro,tamanyo);
             }
             pIndice+=tamanyo;
           }
           indice->cantidad_elementos_actual+=1;
        }
         else{
        return ERROR; ///No se puede insertar elemento
     }

     return OK;
}




