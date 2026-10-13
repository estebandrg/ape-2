#ifndef TADOPERACION_H
#define TADOPERACION_H
#include "tFecha.h"

typedef struct tOperacion *Operacion;
//Constructora
Operacion crearOperacion(int id, char tipo[8], float monto, Fecha fechaOp);

//Modificadoras
int verIdOperacion(Operacion op_objetivo);

float verMontoOperacion(Operacion op_objetivo);

Fecha verFechaOperacion(Operacion op_objetivo);

char* verTipoOperacion(Operacion op_objetivo);

void asignarOperacion(Operacion* op_destino, Operacion op_fuente);
//Destructora
void destruirOperacion(int id);

#endif
