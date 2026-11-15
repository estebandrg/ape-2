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
Usuario crearUsuario(char* nombre){
  Usuario nuevoUsuario= NULL;

  nuevoUsuario = (Usuario)malloc(sizeof(struct tUsuario));
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

//Destructoras
void destruirUsuario(Usuario usuario_objetivo){
  if(usuario_objetivo != NULL){
    destruirBilletera(usuario_objetivo->billetera);
    free(usuario_objetivo);
  }
}
