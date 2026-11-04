#include <stdlib.h>
#include <string.h>
#include "tBilletera.h"

struct tBilletera {
    float saldo;
    int cantOps;
    Operacion ops;
};

Billetera crearBilletera(void) {
    Billetera nueva = malloc(sizeof(struct tBilletera));
    if (nueva != NULL) {
        nueva->saldo = 0;
        nueva->cantOps = 0;
        nueva->ops = NULL;
    }
    return nueva;
}

float verSaldoBilletera(Billetera billetera) { return billetera->saldo; }
Operacion verOpsBilletera(Billetera billetera) { return billetera->ops; }
int obtenerCantOpsBilletera(Billetera billetera) { return billetera->cantOps; }

Operacion buscarOpBilletera(Billetera billetera, int id) {
    Operacion actual = billetera->ops;
    while (actual != NULL && verIdOperacion(actual) != id) {
        actual = verSigOperacion(actual);
    }
    return actual;
}

int registrarOperacion(Billetera billetera, Operacion operacion) {
    float monto = verMontoOperacion(operacion);
    float saldo = billetera->saldo;

    if (monto <= 0) {
        return 0;
    }
    if (strcmp(verTipoOperacion(operacion), "ingreso") == 0) {
        saldo += monto;
    } else if (strcmp(verTipoOperacion(operacion), "egreso") == 0) {
        if (monto > saldo) {
            return 0;
        }
        saldo -= monto;
    } else {
        return 0;
    }

    asignarSigOperacion(operacion, billetera->ops);
    billetera->ops = operacion;
    billetera->saldo = saldo;
    billetera->cantOps++;
    return 1;
}

void destruirBilletera(Billetera billetera) {
    Operacion actual = billetera->ops;
    while (actual != NULL) {
        Operacion siguiente = verSigOperacion(actual);
        destruirOperacion(actual);
        actual = siguiente;
    }
    free(billetera);
}
