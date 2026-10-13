#include <stdio.h>
#include <stdlib.h>
#include "tFecha.h"

typedef struct tFecha {
  int dia;
  int mes;
  int anio;
} *Fecha;

//Constructora
Fecha crearFecha(int dia, int mes, int anio){
  Fecha nuevaFecha=NULL;
  if (esFechaValida(dia, mes, anio)){
  
    nuevaFecha=(Fecha)malloc(sizeof(Fecha));
    nuevaFecha->dia= dia;
    nuevaFecha->mes= mes;
    nuevaFecha->anio= anio;
  }

  return nuevaFecha;
}
//Observadoras
int obtenerDia(Fecha fecha_objetivo) {
  int dia_solicitado;
  dia_solicitado= fecha_objetivo->dia;
  
  return dia_solicitado;
}

int obtenerMes(Fecha fecha_objetivo){
  int mes_solicitado;
  mes_solicitado= fecha_objetivo->mes;

  return mes_solicitado;
}

int obtenerAnio(Fecha fecha_objetivo){
  int anio_solicitado;
  anio_solicitado= fecha_objetivo->anio;
  
  return anio_solicitado;
}

//Modificadoras
void asignarFecha(Fecha* fecha_destino, Fecha fecha_fuente){
  (*fecha_destino)->dia=fecha_fuente->dia;
  (*fecha_destino)->mes=fecha_fuente->mes;
  (*fecha_destino)->anio=fecha_fuente->anio;
}

//Auxiliares internas
int esFechaValida(int dia, int mes, int anio){
  int res=0;
  if(anio>0&&anio<2027){
    if((mes==4||mes==6||mes==9||mes==11)&&(dia>0&&dia<=30)){
      res=1;
    }
    else if((mes==2)&&(dia>0&&dia<=28)){
      res=1;
    }
  }
  return res;
}
