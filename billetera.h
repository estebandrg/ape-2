#ifndef BILLETERA_H
#define BILLETERA_H

// Definicion del tipo exportado. Quien usa el TAD no conoce su representacion
typedef struct tBilletera *tBilletera;

// Constructor

// Crea una billetera lista para usarse, con saldo 0 y sin operaciones
tBilletera crearBilletera(void);

// Destructor

// Libera la billetera y todas sus operaciones. Deja el puntero en NULL
// pre-cond: la billetera fue creada con crearBilletera
void destruirBilletera(tBilletera *billetera);

// Modificadoras

// Registra un ingreso y suma el monto al saldo
// pre-cond: monto > 0
void registrarIngreso(tBilletera billetera, int monto);

// Registra un egreso y resta el monto del saldo
// Retorna 1 si se registro, 0 si el saldo no alcanza (no se registra nada)
// pre-cond: monto > 0
int registrarEgreso(tBilletera billetera, int monto);

// Observadoras

// Retorna el saldo actual de la billetera
int verSaldo(tBilletera billetera);

#endif
