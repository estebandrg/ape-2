#include <stdlib.h>
#include "billetera.h"

// Representacion privada de una operacion (ingreso o egreso)
typedef struct {
    int uid;
    char tipo;      // 'I' ingreso, 'E' egreso
    int monto;
    int saldo;      // saldo de la billetera luego de la operacion
} Operacion;

// Nodo del arbol de operaciones, ordenado por saldo
typedef struct nodoOperacion {
    Operacion operacion;
    struct nodoOperacion *izq;
    struct nodoOperacion *der;
} NodoOperacion;

// Implementacion privada de la billetera
struct tBilletera {
    int saldo;
    int ultimoUid;
    NodoOperacion *operaciones;
};

// Funcionalidades privadas

Operacion crearOperacion(int uid, int esIngreso, int monto, int saldo) {
    Operacion nueva;
    nueva.uid = uid;
    if (esIngreso) {
        nueva.tipo = 'I';
    } else {
        nueva.tipo = 'E';
    }
    nueva.monto = monto;
    nueva.saldo = saldo;

    return nueva;
}

// Funcion recursiva: inserta la operacion manteniendo el orden por saldo
NodoOperacion *insertarOperacion(NodoOperacion *raiz, Operacion operacion) {
    if (raiz == NULL) {
        NodoOperacion *nuevo = malloc(sizeof(NodoOperacion));
        nuevo->operacion = operacion;
        nuevo->izq = NULL;
        nuevo->der = NULL;

        return nuevo;
    }

    if (operacion.saldo < raiz->operacion.saldo) {
        raiz->izq = insertarOperacion(raiz->izq, operacion);
    } else {
        raiz->der = insertarOperacion(raiz->der, operacion);
    }

    return raiz;
}

void liberarOperaciones(NodoOperacion *raiz) {
    if (raiz != NULL) {
        liberarOperaciones(raiz->izq);
        liberarOperaciones(raiz->der);
        free(raiz);
    }
}

// Crea una operacion con el siguiente uid y el saldo ya actualizado, y la agrega a la coleccion
void agregarOperacion(tBilletera billetera, int esIngreso, int monto) {
    billetera->ultimoUid++;
    Operacion operacion = crearOperacion(billetera->ultimoUid, esIngreso, monto, billetera->saldo);
    billetera->operaciones = insertarOperacion(billetera->operaciones, operacion);
}

// Funcionalidades publicas

tBilletera crearBilletera(void) {
    tBilletera nueva = malloc(sizeof(struct tBilletera));
    nueva->saldo = 0;
    nueva->ultimoUid = 0;
    nueva->operaciones = NULL;

    return nueva;
}

void destruirBilletera(tBilletera *billetera) {
    liberarOperaciones((*billetera)->operaciones);
    free(*billetera);
    *billetera = NULL;
}

void registrarIngreso(tBilletera billetera, int monto) {
    billetera->saldo += monto;
    agregarOperacion(billetera, 1, monto);
}

int registrarEgreso(tBilletera billetera, int monto) {
    int alcanza = monto <= billetera->saldo;

    if (alcanza) {
        billetera->saldo -= monto;
        agregarOperacion(billetera, 0, monto);
    }

    return alcanza;
}

int verSaldo(tBilletera billetera) {
    return billetera->saldo;
}
