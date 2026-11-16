#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tUsuario.h"

struct tUsuario{
  int uid;
  char nombre[20];
  Billetera billetera;
};

//Constructor
Usuario crearUsuario(char* nombre){
  Usuario nuevoUsuario= NULL;
  nuevoUsuario = (Usuario)malloc(sizeof(struct tUsuario));
  nuevoUsuario->uid = rand() % (UID_MAX + 1);
  strncpy(nuevoUsuario->nombre, nombre, sizeof(nuevoUsuario->nombre) - 1);
  nuevoUsuario->nombre[sizeof(nuevoUsuario->nombre) - 1] = '\0';  
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
