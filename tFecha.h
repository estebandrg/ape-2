#ifndef TADFECHA_H
#define TADFECHA_H

typedef struct tFecha *Fecha;

// Constructora: devuelve NULL si la fecha no es valida
Fecha crearFecha(int dia, int mes, int anio);

// Observadoras
int obtenerDia(Fecha fecha_objetivo);
int obtenerMes(Fecha fecha_objetivo);
int obtenerAnio(Fecha fecha_objetivo);

// Modificadoras: copia fecha_fuente en *fecha_destino (lo reserva si es NULL)
void asignarFecha(Fecha* fecha_destino, Fecha fecha_fuente);

// Destructora
void destruirFecha(Fecha fecha_objetivo);

#endif
