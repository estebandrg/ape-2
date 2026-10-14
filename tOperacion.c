#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tFecha.h"
#include "tOperacion.h"

typedef struct tOperacion {
  int id;
  char tipo[8];
  float monto;
  Fecha fechaOp;
  struct tOperacion *sig;
} *Operacion;

//Constructora
Operacion crearOperacion(int id, char tipo[8], float monto, Fecha fechaOp){
  Operacion nuevaOperacion = (Operacion)malloc(sizeof(Operacion));
  
  nuevaOperacion->id = id;
  strcpy(nuevaOperacion->tipo, tipo);
  nuevaOperacion->monto = monto;
  asignarFecha(&(nuevaOperacion->fechaOp),fechaOp);
  
  return nuevaOperacion;
}

//Observadoras
int verIdOperacion(Operacion op_objetivo){
  return op_objetivo->id;
}

float verMontoOperacion(Operacion op_objetivo){
  return op_objetivo->monto;
}

Fecha verFechaOperacion(Operacion op_objetivo){
  return op_objetivo->fechaOp;
}

char* verTipoOperacion(Operacion op_objetivo){
  return op_objetivo->tipo;
}

//Modificadora
void pasarSigOperacion(Operacion *op_objetivo){
  (*op_objetivo) = (*op_objetivo)->sig;
}

void asignarOperacion(Operacion* op_destino, Operacion op_fuente){
  (*op_destino)->id=op_fuente->id;
  strcpy((*op_destino)->tipo, op_fuente->tipo);
  (*op_destino)->monto=op_fuente->monto;
  asignarFecha((*op_destino)->fechaOp, op_fuente->fechaOp);
}

void destruirOperacion(int id);

