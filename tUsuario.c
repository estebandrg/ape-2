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







