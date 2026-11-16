#ifndef TADUSUARIO_H
#define TADUSUARIO_H

#include "tBilletera.h"

#define UID_MAX 2000000

typedef struct tUsuario *Usuario;

// Constructora: genera un UID aleatorio en [0, UID_MAX] y crea su billetera propia.
// El generador (srand) lo inicializa quien llama. Devuelve un usuario valido
Usuario crearUsuario(char *nombre);

// Observadoras
int verIdUsuario(Usuario usuario_objetivo);

char* verNombreUsuario(Usuario usuario_objetivo);

Billetera verBilleteraUsuario(Usuario usuario_objetivo);

// Destructora
void destruirUsuario(Usuario usuario_objetivo);

#endif
