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

int indice_cargar(const char* path, t_indice* indice, void *vreg_ind, size_t tamanyo, int (*cmp)(const void *, const void *))
{
    FILE* pf = fopen(path, "rb");
    if(!pf)
        return ERROR;

    vreg_ind = malloc(sizeof(miembro));
    if(!vreg_ind)
    {
        fclose(pf);
        return ERROR;
    }

    t_reg_indice idx;
    unsigned nro_reg = 0;

    fread(vreg_ind, sizeof(miembro), 1, pf);
    while(!feof(pf))
    {

        idx.dni = ((miembro*)vreg_ind)->dni;
        idx.nro_reg = nro_reg;
        nro_reg++;


        if(indice_insertar(indice, &idx, tamanyo, cmp) == OK) {
            fread(vreg_ind, sizeof(miembro), 1, pf);
        }
        else
        {
            free(vreg_ind);
            fclose(pf);
            return ERROR;
        }
    }

    free(vreg_ind);
    fclose(pf);
    return nro_reg;
}

int indice_vacio(const t_indice *indice) {
    return (!indice || indice->cantidad_elementos_actual == 0) ? OK : 0;
}

int indice_lleno(const t_indice *indice) {
    if (!indice) return 0;
    return (indice->cantidad_elementos_actual >= indice->cantidad_elementos_maxima) ? OK : 0;
}

/**************************************************************************
 * Vaciar: deja el índice sin elementos (conserva la memoria)
 **************************************************************************/
void indice_vaciar(t_indice* indice) {
    if (!indice) return;
    indice->cantidad_elementos_actual = 0;
}




