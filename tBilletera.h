#ifndef BILLETERA_H
#define BILLETERA_H

#include "tOperacion.h"

// Billetera exclusiva de un usuario: saldo + lista enlazada de operaciones
typedef struct tBilletera *Billetera;

// Constructora: saldo inicial 0, sin operaciones
Billetera crearBilletera(void);

// Observadoras
float verSaldoBilletera(Billetera billetera);

Operacion verOpsBilletera(Billetera billetera);

int obtenerCantOpsBilletera(Billetera billetera);

// Modificadoras
void ingresarDinero(Billetera billetera, float monto);

void egresarDinero(Billetera billetera, float monto);

void registrarOperacion(Billetera billetera, Operacion nueva_operacion);

// Destructora: libera la billetera y todas sus operaciones
void destruirBilletera(Billetera billetera);

#endif
