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
// NULL si no existe una operacion con ese id
Operacion buscarOpBilletera(Billetera billetera, int id);

// Modificadora: agrega la operacion (de tipo "ingreso" o "egreso") al inicio de la lista
// y actualiza el saldo. Devuelve 1 si se registro; 0 si el tipo es invalido, el monto
// no es positivo o un egreso supera el saldo (la operacion no se toma en ese caso).
int registrarOperacion(Billetera billetera, Operacion operacion);

// Destructora: libera la billetera y todas sus operaciones
void destruirBilletera(Billetera billetera);

#endif
