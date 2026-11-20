#include <stdlib.h>
#include <string.h>
#include "tFecha.h"
#include "tOperacion.h"

struct tOperacion {
  int id;
  char tipo[8];
  float monto;
  Fecha fechaOp;
  struct tOperacion *sig;
};

// Constructora: copia la fecha recibida, fecha != NULL
Operacion crearOperacion(int id, char *tipo, float monto, Fecha fechaOp) {
    Operacion nuevaOperacion = malloc(sizeof(struct tOperacion));
    
    nuevaOperacion->id = id;
    strncpy(nuevaOperacion->tipo, tipo, 7);
    nuevaOperacion->tipo[7] = '\0';
    nuevaOperacion->monto = monto;
    nuevaOperacion->fechaOp = NULL;
    asignarFecha(&(nuevaOperacion->fechaOp), fechaOp);
    nuevaOperacion->sig = NULL;
      
    return nuevaOperacion;
}

// Observadoras
int verIdOperacion(Operacion op_objetivo) { 
  return op_objetivo->id; 
}

float verMontoOperacion(Operacion op_objetivo) {
   return op_objetivo->monto; 
}

Fecha verFechaOperacion(Operacion op_objetivo) {
   return op_objetivo->fechaOp; 
}

char* verTipoOperacion(Operacion op_objetivo) { 
  return op_objetivo->tipo; 
}

Operacion verSigOperacion(Operacion op_objetivo) {
   return op_objetivo->sig; 
}

// Modificadoras
void asignarSigOperacion(Operacion op_objetivo, Operacion nuevaSig) {
  op_objetivo->sig = nuevaSig;
}

// Destructora: libera solo esta operacion (no las siguientes)
void destruirOperacion(Operacion op_objetivo) {
  if (op_objetivo != NULL) {
    destruirFecha(op_objetivo->fechaOp);
    free(op_objetivo);
  }
}
