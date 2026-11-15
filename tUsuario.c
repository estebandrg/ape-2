#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tUsuario.h"
#include "tOperacion.h"


typedef struct tUsuario{
  int uid;
  char nombre[20];
  Billetera billetera;
} *Usuario;

//Constructor
Usuario crearUsuario( char nombre[20]){
  Usuario nuevoUsuario = (Usuario)malloc(sizeof(struct tUsuario));
  
  nuevoUsuario->uid = rand() % (UID_MAX + 1);
  strcpy(nuevoUsuario->nombre, nombre);
  nuevoUsuario->billetera = crearBilletera();

  return nuevoUsuario;
}

//Observadoras
int verIdUsuario(Usuario usuario_objetivo){
  return usuario_objetivo->uid;
}
char* verNombreUsuario(Usuario usuario_objetivo){
  return usuario_objetivo->nombre;
}
Billetera verBilleteraUsuario(Usuario usuario_objetivo){
  return usuario_objetivo->billetera;
}

void asignarUsuario(Usuario *usuario_destino, Usuario usuario_fuente){
  if (usuario_destino != NULL && usuario_fuente != NULL) {
    *usuario_destino = usuario_fuente;
  }
}

//Destructoras
void destruirUsuario(Usuario usuario_objetivo){
  if(usuario_objetivo != NULL){
    destruirBilletera(usuario_objetivo->billetera);
    free(usuario_objetivo);
  }
}
