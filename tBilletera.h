#ifndef BILLETERA_H
#define BILLETERA_H

#include "tOperacion.h"

#define UID_MAX 2000000

// Billetera de un usuario: identidad (uid, nombre), saldo y lista de operaciones
typedef struct tBilletera *Billetera;

// Constructora:
// Genera un UID aleatorio en [0, UID_MAX], copia el nombre y crea la billetera
// con saldo 0 y sin operaciones. Devuelve una billetera valida (!= NULL).
// El generador (srand) lo inicializa quien llama.
Billetera crearBilletera(char *nombre);

// Observadoras
int verUIDBilletera(Billetera billetera);

char* verNombreBilletera(Billetera billetera);

float verSaldoBilletera(Billetera billetera);

Operacion verOpsBilletera(Billetera billetera);

int obtenerCantOpsBilletera(Billetera billetera);

// Modificadoras
// Crean la operacion correspondiente y la registran (siempre queda registro).
// PRE: billetera != NULL, fecha != NULL y valida, monto > 0.
void ingresarDinero(Billetera billetera, float monto, Fecha fecha);

void egresarDinero(Billetera billetera, float monto, Fecha fecha);

void registrarOperacion(Billetera billetera, Operacion nueva_operacion);

// Destructora: libera la billetera y todas sus operaciones
void destruirBilletera(Billetera billetera);

#endif
