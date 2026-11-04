#ifndef TADOPERACION_H
#define TADOPERACION_H
#include "tFecha.h"

typedef struct tOperacion *Operacion;

// Constructora (copia la fecha). tipo: "ingreso" o "egreso"
Operacion crearOperacion(int id, char *tipo, float monto, Fecha fechaOp);

// Observadoras
int verIdOperacion(Operacion op_objetivo);
float verMontoOperacion(Operacion op_objetivo);
Fecha verFechaOperacion(Operacion op_objetivo);
char* verTipoOperacion(Operacion op_objetivo);
Operacion verSigOperacion(Operacion op_objetivo);

// Modificadoras
void asignarSigOperacion(Operacion op_objetivo, Operacion nuevaSig);
void pasarSigOperacion(Operacion* op_objetivo);
void asignarOperacion(Operacion* op_destino, Operacion op_fuente);

// Destructora (solo esta operacion)
void destruirOperacion(Operacion op_objetivo);

#endif
