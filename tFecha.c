#include <stdlib.h>
#include "tFecha.h"

struct tFecha {
  int dia;
  int mes;
  int anio;
};

static int esBisiesto(int anio) {
  return (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
}

static int esFechaValida(int dia, int mes, int anio) {
  static const int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (anio <= 0 || anio >= 2027 || mes < 1 || mes > 12 || dia < 1) {
    return 0;
  }
  int maxDia = diasPorMes[mes - 1];
  if (mes == 2 && esBisiesto(anio)) {
    maxDia = 29;
  }
  return dia <= maxDia;
}

Fecha crearFecha(int dia, int mes, int anio) {
  Fecha nuevaFecha = NULL;
  if (esFechaValida(dia, mes, anio)) {
    nuevaFecha = malloc(sizeof(struct tFecha));
    if (nuevaFecha != NULL) {
      nuevaFecha->dia = dia;
      nuevaFecha->mes = mes;
      nuevaFecha->anio = anio;
    }
  }
  return nuevaFecha;
}

int obtenerDia(Fecha fecha_objetivo) { return fecha_objetivo->dia; }
int obtenerMes(Fecha fecha_objetivo) { return fecha_objetivo->mes; }
int obtenerAnio(Fecha fecha_objetivo) { return fecha_objetivo->anio; }

void asignarFecha(Fecha* fecha_destino, Fecha fecha_fuente) {
  if (*fecha_destino == NULL) {
    *fecha_destino = malloc(sizeof(struct tFecha));
  }
  **fecha_destino = *fecha_fuente;
}

void destruirFecha(Fecha fecha_objetivo) {
  free(fecha_objetivo);
}
