#ifndef BILLETERA_H
#define BILLETERA_H

typedef struct tBilletera *Billetera;

// Constructor
Billetera crearBilletera();

// Modificadores
void registrarUsuario();
void eliminarUsuario(int id);
void registrarIngreso(int monto);
void registrarEgreso(int monto);

int obtenerCantUsuarios();
Usuario buscarUsuario(int id);


#endif
