#ifndef BILLETERA_H
#define BILLETERA_H

#include <tUsuario.h>

typedef struct Billetera *tBilletera;

// Constructor
tBilletera crearBilletera();

// Metodos
void registrarUsuario();
void eliminarUsuario(int id);
void registrarIngreso(int monto);
void registrarEgreso(int monto);

Usuario buscarUsuario(int id);


#endif
