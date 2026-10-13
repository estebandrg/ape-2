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
  int id_solicitado=op_objetivo->id;
  return id_solicitado;
}

float verMontoOperacion(Operacion op_objetivo){
  float monto_solicitado=op_objetivo->monto;
  return monto_solicitado;
}

Fecha verFechaOperacion(Operacion op_objetivo){
  Fecha fecha_solicitada;
  asignarFecha(&fecha_solicitada, op_objetivo->fechaOp);

  return fecha_solicitada;
}

char* verTipoOperacion(Operacion op_objetivo){
  char tipo_solicitado[8];
  strcpy(tipo_solicitado, op_objetivo->tipo);

  return tipo_solicitado;
}

//Modificadora
void asignarOperacion(Operacion* op_destino, Operacion op_fuente){
    (*op_destino)->id=op_fuente->id;
    strcpy((*op_destino)->tipo, op_fuente->tipo);
    (*op_destino)->monto=op_fuente->monto;
    asignarFecha((*op_destino)->fechaOp, op_fuente->fechaOp);
}

void destruirOperacion(int id);

