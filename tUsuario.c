#include <stdlib.h>
#include <string.h>
#include "tUsuario.h"

struct tUsuario {
  int id;
  char nombre[20];
  Billetera billetera;
  struct tUsuario* sig;
};

Usuario crearUsuario(const char *nombre) {
  Usuario nuevo = malloc(sizeof(struct tUsuario));
  if (nuevo == NULL) {
    return NULL;
  }
  nuevo->billetera = crearBilletera();
  if (nuevo->billetera == NULL) {
    free(nuevo);
    return NULL;
  }
  nuevo->id = rand() % (UID_MAX + 1);
  strncpy(nuevo->nombre, nombre, 19);
  nuevo->nombre[19] = '\0';
  nuevo->sig = NULL;
  return nuevo;
}

int verIdUsuario(Usuario u) { return u->id; }
char* verNombreUsuario(Usuario u) { return u->nombre; }
Billetera verBilleteraUsuario(Usuario u) { return u->billetera; }
Usuario verSigUsuario(Usuario u) { return u->sig; }

void asignarSigUsuario(Usuario u, Usuario nuevoSig) { u->sig = nuevoSig; }

void destruirUsuario(Usuario u) {
  destruirBilletera(u->billetera);
  free(u);
}
