#ifndef TADFECHA_H
#define TADFECHA_H

typedef struct tFecha *Fecha;
//Constructura
//Crea una nueva fecha lista para usarse
Fecha crearFecha(int dia, int mes, int anio);
//Observadoras
int obtenerDia(Fecha fecha_objetivo);
int obtenerMes(Fecha fecha_objetivo);
int obtenerAnio(Fecha fecha_objetivo);
//Modificadoras
void asignarFecha(Fecha* fecha_destino, Fecha fecha_fuente);

#endif

