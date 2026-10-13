#ifndef BILLETERA_H
#define BILLETERA_H

#include <usuario.h>

typedef struct Billetera *tBilletera;

// Constructor
tBilletera crearBilletera();

// Metodos
void registrarUsuario();
void eliminarUsuario(int id);
void registrarIngreso(int monto);
void registrarEgreso(int monto);

tUsuario buscarUsuario(int id);

#endif
