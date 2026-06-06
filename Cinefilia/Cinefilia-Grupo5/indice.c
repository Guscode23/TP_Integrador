#include "indice.h"
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void indice_crear(t_indice *indice, size_t nmemb, size_t tamanyo) {
    size_t capacidad_inicial = (nmemb == 0) ? 100 : nmemb;

    indice->vindice = malloc(capacidad_inicial * tamanyo);

    if (indice->vindice != NULL) {
        indice->cantidad_elementos_maxima = capacidad_inicial;
        indice->cantidad_elementos_actual = 0;
    } else {
        indice->cantidad_elementos_maxima = 0;
        indice->cantidad_elementos_actual = 0;
    }
}

void indice_redimensionar(t_indice *indice, size_t nmemb, size_t tamanyo){
  indice->vindice=realloc(indice->vindice,(INCREMENTO*nmemb)*tamanyo);

  if(indice->vindice==NULL){
    printf("No se pudo redimensionar el indice");
    exit(0);
  }

}

int indice_insertar(t_indice *indice, const void *registro, size_t tamanyo, int (*cmp)(const void *, const void *)) {

    if (indice->cantidad_elementos_actual == indice->cantidad_elementos_maxima) {
        size_t nueva_capacidad = indice->cantidad_elementos_maxima + (indice->cantidad_elementos_maxima * 30 / 100);
        if (nueva_capacidad == indice->cantidad_elementos_maxima) nueva_capacidad += 10;

        void *temp = realloc(indice->vindice, nueva_capacidad * tamanyo);
        if (temp == NULL) return ERROR;

        indice->vindice = temp;
        indice->cantidad_elementos_maxima = nueva_capacidad;
    }

    char *base = (char *)indice->vindice;
    int i = indice->cantidad_elementos_actual - 1;

    while (i >= 0 && cmp(registro, base + (i * tamanyo)) < 0) {
        memcpy(base + ((i + 1) * tamanyo), base + (i * tamanyo), tamanyo);
        i--;
    }

    memcpy(base + ((i + 1) * tamanyo), registro, tamanyo);
    indice->cantidad_elementos_actual++;

    return TODO_OK;
}

int indice_cargar(const char* path, t_indice* indice, void *vreg_ind, size_t tamanyo, int (*cmp)(const void *, const void *)){
   char linea[256];
    t_reg_indice idx;
    unsigned nro_reg = 0;

    FILE* pf = fopen(path, "rt");
    if(!pf)
        return ERROR;

    fgets(linea, sizeof(linea), pf);

    while(fgets(linea, sizeof(linea), pf) != NULL) {
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
    fclose(pf);
    return OK;
}

int indice_buscar (const t_indice *indice, const void *registro, size_t nmemb, size_t tamanyo, int (*cmp)(const void *, const void *)){
    if (indice->cantidad_elementos_actual == 0 || indice->vindice == NULL) {
        return NO_EXISTE;
    }

    void* base = indice->vindice;
    void* ini = indice->vindice;
    void* fin = (char*)ini + ((indice->cantidad_elementos_actual)-1)*tamanyo;
    int pos = 0;

    while(ini <= fin) {

        int medio = (((fin - ini) / tamanyo) + 1) / 2;
        char* P_medio = (medio == 0) ? fin : (char*)ini + ((medio)-1)*tamanyo;

        if (cmp(registro, (const void*)P_medio) == 0) {
            pos = ((char*)P_medio - (char*)base) / tamanyo;
            return pos;

        } else if (cmp(registro, (const void*)P_medio) < 0) {
            fin = P_medio - tamanyo;
        } else {
            ini = P_medio + tamanyo;
        }
    }
    return NO_EXISTE;
}

int indice_eliminar(t_indice *indice, const void *registro, size_t tamanyo, int (*cmp)(const void *, const void *)){
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

void generar_indice_miembros(t_lista_miembros *lista_original, t_indice *admin_indice) {

    indice_crear(admin_indice, lista_original->cantidad, sizeof(t_reg_indice));
    if (admin_indice->vindice == NULL) return;

    for (unsigned i = 0; i < lista_original->cantidad; i++) {

        if (lista_original->array[i].estado == 'A') {
            t_reg_indice ficha_nueva;
            ficha_nueva.dni = lista_original->array[i].dni;
            ficha_nueva.nro_reg = i;
            indice_insertar(admin_indice,
                            &ficha_nueva,
                            sizeof(t_reg_indice),
                            cmp_miembros_dni);
        }
    }
}

void generar_indice_titulos(t_lista_titulos *lista_original, t_indice *admin_indice) {

    indice_crear(admin_indice, lista_original->cantidad, sizeof(t_reg_indice));
    if (admin_indice->vindice == NULL) return;

    for (unsigned i = 0; i < lista_original->cantidad; i++) {

        if (lista_original->array[i].ID > 0) {

            t_reg_indice ficha_nueva;
            ficha_nueva.dni = (long)lista_original->array[i].ID;
            ficha_nueva.nro_reg = i;
            indice_insertar(admin_indice,
                            &ficha_nueva,
                            sizeof(t_reg_indice),
                            cmp_titulos_id);
        }
    }
}
