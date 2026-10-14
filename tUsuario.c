#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tUsuario.h"
#include "tOperacion.h"

typedef struct tUsuario{
  int id;
  char nombre[20];
  float saldo;
  Operacion lista;
  struct tUsuario* hizq;
  struct tUsuario* hder;
} *Usuario;

//Constructor
Usuario crearUsuario(int id, char nombre[20], float saldo, Operacion lista){
  Usuario nuevoUsuario = (Usuario)malloc(sizeof(Usuario));
  
  nuevoUsuario->id = id;
  strcpy(nuevoUsuario->nombre, nombre);
  nuevoUsuario->saldo = saldo;
  nuevoUsuario->lista = lista;
  nuevoUsuario->hizq = NULL;
  nuevoUsuario->hder = NULL;

  return nuevoUsuario;
}

//Observadoras
int verIdUsuario(Usuario usuario_objetivo){
  return usuario_objetivo->id;
}
char* verNombreUsuario(Usuario usuario_objetivo){
  return usuario_objetivo->nombre;
}
float verSaldoUsuario(Usuario usuario_objetivo){
  return usuario_objetivo->saldo;
}
Operacion verOpUsuario(Usuario usuario_objetivo){
  return usuario_objetivo->lista;
}

Usuario verIzqUsuario(Usuario usuario_objetivo){
  Usuario hijoIzq = usuario_objetivo->hizq;
  return hijoIzq;
}
Usuario verDerUsuario(Usuario usuario_objetivo){
  Usuario hijoDer = usuario_objetivo->hder;
  return hijoDer;
}

Operacion buscarOpUsuario(Usuario *usuario_objetivo, int id){
  Operacion buscado = NULL;
  if ((*usuario_objetivo)->lista != NULL) {
    if (verIdOperacion((*usuario_objetivo)->lista) == id) {
      buscado = (*usuario_objetivo)->lista;
    } else {
      buscado = buscarOpUsuario((*usuario_objetivo)->lista, id); 
    }
  }
  return buscado;
}

//Destructoras
void destruirUsuario(Usuario usuario_objetivo, int id);




