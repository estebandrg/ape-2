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

    nueva->saldo = 0;
    nueva->cantOps = 0;
    nueva->ops = NULL;

    return nueva;
}

float verSaldoBilletera(Billetera billetera_objetivo) { 
    return billetera_objetivo->saldo; 
}

Operacion verOpsBilletera(Billetera billetera_objetivo) { 
    return billetera_objetivo->ops; 
}

int obtenerCantOpsBilletera(Billetera billetera_objetivo) { 
    return billetera_objetivo->cantOps; 
}

void ingresarDinero(Billetera billetera_objetivo, float monto){
    billetera_objetivo->saldo += monto;
}

void egresarDinero(Billetera billetera_objetivo, float monto){
    billetera_objetivo->saldo -= monto;
}

void registrarOperacion(Billetera billetera_objetivo, Operacion nueva_operacion) {
    
    if (billetera_objetivo != NULL && nueva_operacion != NULL) {
        if (strcmp(verTipoOperacion(nueva_operacion), "ingreso") == 0) {
            ingresarDinero(billetera_objetivo, verMontoOperacion(nueva_operacion));
        } 
    
        else if (strcmp(verTipoOperacion(nueva_operacion), "egreso") == 0) {
            egresarDinero(billetera_objetivo, verMontoOperacion(nueva_operacion));
        }

        asignarSigOperacion(nueva_operacion, billetera_objetivo->ops);
        billetera_objetivo->ops = nueva_operacion;
        billetera_objetivo->cantOps++;
    }
    
}

void destruirBilletera(Billetera billetera_objetivo) {
    if (billetera_objetivo != NULL) {
        Operacion actual = billetera_objetivo->ops;
        while (actual != NULL) {
            Operacion siguiente = verSigOperacion(actual);
            destruirOperacion(actual);
            actual = siguiente;
        }
        free(billetera_objetivo);
    }
}
