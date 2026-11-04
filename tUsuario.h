#ifndef TADUSUARIO_H
#define TADUSUARIO_H

#include "tBilletera.h"

#define UID_MAX 2000000

// Nodo de una lista enlazada de usuarios
typedef struct tUsuario *Usuario;

// Constructora: genera un UID aleatorio en [0, UID_MAX] y crea su billetera propia.
// El generador (srand) lo inicializa quien llama. Devuelve NULL si falla la memoria.
Usuario crearUsuario(char *nombre);

// Observadoras
int verIdUsuario(Usuario usuario_objetivo);
char* verNombreUsuario(Usuario usuario_objetivo);
Billetera verBilleteraUsuario(Usuario usuario_objetivo);
Usuario verSigUsuario(Usuario usuario_objetivo);

// Establecedoras
void asignarSigUsuario(Usuario usuario_objetivo, Usuario nuevoSig);

// Destructora: libera el usuario y su billetera (no libera los siguientes)
void destruirUsuario(Usuario usuario_objetivo);

#endif
