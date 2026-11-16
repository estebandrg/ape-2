#include <stdlib.h>
#include "tFecha.h"

#define ANIO_MAXIMO 2100 

struct tFecha {
  int dia;
  int mes;
  int anio;
};

int esBisiesto(int anio) {
  int anioEsBisiesto = 0;

  if (anio % 400 == 0) {
    anioEsBisiesto = 1;
  } 
  else if (anio % 100 == 0) {
    anioEsBisiesto = 0;
  } 
  else if (anio % 4 == 0) {
    anioEsBisiesto = 1;
  }

  return anioEsBisiesto;
}

int esFechaValida(int dia, int mes, int anio) {
  int diasPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int fechaValida = 0;
  int maxDia = 0;

  if (anio > 0 && anio < ANIO_MAXIMO && mes >= 1 && mes <= 12 && dia >= 1) {
    maxDia = diasPorMes[mes - 1];

    if (mes == 2 && esBisiesto(anio)) {
      maxDia = 29;
    }

    if (dia <= maxDia) {
      fechaValida = 1;
    }
  }

  return fechaValida;
}

//Funcionalidades de la Intefaz de Fecha
Fecha crearFecha(int dia, int mes, int anio) {
    Fecha nuevaFecha = NULL;
    nuevaFecha = malloc(sizeof(struct tFecha));
    nuevaFecha->dia = dia;
    nuevaFecha->mes = mes;
    nuevaFecha->anio = anio;
    return nuevaFecha;
}

int obtenerDia(Fecha fecha_objetivo) { 
  return fecha_objetivo->dia;
}

int obtenerMes(Fecha fecha_objetivo) {
   return fecha_objetivo->mes; 
}

int obtenerAnio(Fecha fecha_objetivo) {
   return fecha_objetivo->anio; 
}

void asignarFecha(Fecha *fecha_destino, Fecha fecha_fuente) {
    if (fecha_destino != NULL && fecha_fuente != NULL) {
        if (*fecha_destino == NULL) {
            *fecha_destino = malloc(sizeof(struct tFecha));
        }
        if (*fecha_destino != NULL) {
            **fecha_destino = *fecha_fuente;
        }
    }
}
void destruirFecha(Fecha fecha_objetivo) {
  if (fecha_objetivo != NULL) {
    free(fecha_objetivo);
  } 
}
