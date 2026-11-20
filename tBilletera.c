#include <stdlib.h>
#include <string.h>
#include "tBilletera.h"

struct tBilletera {
    int uid;
    char nombre[20];
    float saldo;
    int cantOps;
    Operacion ops;
};

Billetera crearBilletera(char *nombre) {
    Billetera nueva = malloc(sizeof(struct tBilletera));

    nueva->uid = rand() % (UID_MAX + 1);
    strncpy(nueva->nombre, nombre, sizeof(nueva->nombre) - 1);
    nueva->nombre[sizeof(nueva->nombre) - 1] = '\0';
    nueva->saldo = 0;
    nueva->cantOps = 0;
    nueva->ops = NULL;

    return nueva;
}

int verUIDBilletera(Billetera billetera_objetivo) {
    return billetera_objetivo->uid;
}

char* verNombreBilletera(Billetera billetera_objetivo) {
    return billetera_objetivo->nombre;
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

void ingresarDinero(Billetera billetera_objetivo, float monto, Fecha fecha){
    int id_operacion = 1 + obtenerCantOpsBilletera(billetera_objetivo);
    Operacion nueva_operacion = crearOperacion(id_operacion, "ingreso", monto, fecha);
    registrarOperacion(billetera_objetivo, nueva_operacion);
}

void egresarDinero(Billetera billetera_objetivo, float monto, Fecha fecha){
    int id_operacion = 1 + obtenerCantOpsBilletera(billetera_objetivo);
    Operacion nueva_operacion = crearOperacion(id_operacion, "egreso", monto, fecha);
    registrarOperacion(billetera_objetivo, nueva_operacion);
}

void registrarOperacion(Billetera billetera_objetivo, Operacion nueva_operacion) {
    
    if (billetera_objetivo != NULL && nueva_operacion != NULL) {
        if (strcmp(verTipoOperacion(nueva_operacion), "ingreso") == 0) {
            billetera_objetivo->saldo += verMontoOperacion(nueva_operacion);
        } 
    
        else if (strcmp(verTipoOperacion(nueva_operacion), "egreso") == 0) {
            billetera_objetivo->saldo -= verMontoOperacion(nueva_operacion);
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
