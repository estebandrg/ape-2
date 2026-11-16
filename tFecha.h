#ifndef TADFECHA_H
#define TADFECHA_H

typedef struct tFecha *Fecha;

// Constructora:
//Devuelve una fecha valida o invalida (ambas !=NULL)
Fecha crearFecha(int dia, int mes, int anio);

// Observadoras
int obtenerDia(Fecha fecha_objetivo);
int obtenerMes(Fecha fecha_objetivo);
int obtenerAnio(Fecha fecha_objetivo);
int esBisiesto(int anio);
//Devuelve 1 si la fecha es valida o 0 si la misma no corresponde al calendario
int esFechaValida(int dia, int mes, int anio);

// Modificadoras: copia fecha_fuente en *fecha_destino (lo reserva si es NULL)
void asignarFecha(Fecha* fecha_destino, Fecha fecha_fuente);

// Destructora
void destruirFecha(Fecha fecha_objetivo);

#endif
