#include <stdio.h>
#include <stdlib.h>
#include "fecha.h"
#include "Validaciones.h"
#include "Tp.h"



///En este main testearemos las funciones de validación hechas en la librería

int main()
{
  ///Pruebas de funciones del proyecto
  t_datos dato;
  //char cadena[]="12345678;20-12345678-3;Gomez Juan Carlos;15/04/1985;M;10/03/2020;ADULTO;01/05/2026;A;PREMIUM;";
  char cadena[]="12345678;Gomez Juan Carlos;15/04/1985;M;10/03/2020;ADULTO;01/05/2026;A;PREMIUM;";
  int parametros=0;

  ///Captura de datos (A revisar)
  /*parametros=sscanf(cadena,
         "%ld;%60s;%d/%d/%d;%c;%d/%d/%d;%s;%d/%d/%d;%c;%s;",
         &dato.dni,
         //dato.cuil, ///No hace falta pasarle el & ya que el nombre corresponde a la direccion
         dato.apeNom,
         &dato.fechNac.dia,&dato.fechNac.mes,&dato.fechNac.anio,
         &dato.sexo,
         &dato.fechAfil.dia,&dato.fechAfil.mes,&dato.fechAfil.anio,
         dato.cat,
         &dato.fechUltCuot.dia,&dato.fechUltCuot.mes,&dato.fechUltCuot.anio,
         &dato.estado,
         dato.plan);*/

  /******************************************************Pruebas***********************************************************************/

   ///A-Validar DNI
   /*printf("%d\n",validarDNI(999999));///Correcto
   printf("%d\n",validarDNI(dato.dni));///Correcto
   printf("%d\n",validarDNI(100000001));///Correcto
   printf("%d",validarDNI(100000000));///Correcto*/

   ///B-Validar CUIL

   ///1-Prueba Exitosa: Dígito de verificación incorrecto
  /*long int dni=12345678;
  const char cuil[]="20-12345678-3";
  char sexo='M';*/

  ///2-PruebaExitosa
  /*long int dni=12345678;
  const char cuil[]="20-12345678-8";
  char sexo='M';*/

  ///3-Tipo en cuil correspondiente a hombre, sexo femenino:Exitoso
  /*long int dni=12345678;
  const char cuil[]="20-12345678-8";
  char sexo='F';*/

  ///4-Valor de DNI distintos en CUIL y DNI: Exitoso
  /*long int dni=43665940;
  const char cuil[]="20-12345678-8";
  char sexo='F';*/

  ///5-Formato inválido del CUIL:Exitoso
  /*long int dni=43665940;
  const char cuil[]="20-123 45678-8";
  char sexo='M';

  printf("%d",validarCUIL(cuil,dni,&sexo)); ///Debe dar inválido, ya que el dígito de verificación debe ser 8 (Correcto)*/

  ///C-Normalizar Apellido y Nombre (Pruebas exitosas)
  //char nyApel[]="galletA pePE raul"; ///Caso1-Éxito
  //char nyApel[]="galletA erPE   raul"; ///Caso2-Éxito
  //char nyApel[]="  galletA   erPE   raul";//Caso3-Éxito
  //char nyApel[]="GALLETA PEPE    RUAL"; ///Caso 4-Éxito

  //printf("%s",normalizarApel_Nombre(nyApel));



  ///D-Validar Fecha de Nacimiento (Fecha válida y comparar fecha)
  /*t_fecha fecha1;
  t_fecha fecha2;

  fecha1.dia=15;
  fecha1.mes=4;
  fecha1.anio=2025;
  fecha2.dia=23;
  fecha2.mes=5;
  fecha2.anio=2026;

  fecha1.dia=15;
  fecha1.mes=4;
  fecha1.anio=2017;
  fecha2.dia=23;
  fecha2.mes=5;
  fecha2.anio=2026;*/

  //printf("%d",es_Fecha_Valida(&fecha1)); ///Exitoso
  //printf("%d",compara_Fechas_MenorIgual(&fecha1,&fecha2));///Exitoso
  ///printf("%d",compara_Fechas_MenorIgual(&fecha2,&fecha1)); ///Exitoso
  //printf("%d",compara_Fechas_MenorIgual(&fecha1,&fecha2)); ///Exitoso

  ///E-FechaAfiliacion (Prueba pendiente)

  ///F-Validar Categoria-->Se le pasa la edad, por lo que deberemos hacer una funcion para calcular edad

   /*const char cat[]="MAYOR";
   //int edad=13;
   int edad=12;

   printf("%d",validarCAT(cat,edad)); ///Pruebas exitosas*/

   ///G-Ultima cuota paga (Prueba pendiente)


   ///H-Validar PLAN: Pruebas exitosas
   /*const char plan[]="ORO";

   printf("%d",validarPlan(plan));*/

   ///I-Validar EMAIL Tutor-->Pruebas exitosas
   /*const char correo[]="rosalesunlam19@gmail.com";
   //const char correo[]="rosalesunlam19@miempresa.com";
   //const char correo[]="rosalesunlam10@algo.com";
   //const char correo[]="";


   printf("%d",validarCorreo(correo)); ///Prueba exitosa*/

   ///J-Prueba de cálculo de edad:Pruebas exitosas
   /*t_fecha fechaProceso;
   t_fecha fechaNac;

  fechaProceso.dia=22;
  fechaProceso.mes=8;
  fechaProceso.anio=2026;
  fechaNac.dia=23;
  fechaNac.mes=8;
  fechaNac.anio=2001;

  printf("%d",calcularEdad(&fechaProceso,&fechaNac));*/

  ///K-Prueba de Genero
  const char genero[]="Comedias";

  printf("%d",validarGenero(genero));










  return 0;



}
