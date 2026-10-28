#include <stdio.h>
#include <stdlib.h>
#include "billetera.h"

// Representacion privada de una operacion (ingreso o egreso)
typedef struct {
    int uid;
    char tipo;      // 'I' ingreso, 'E' egreso
    int monto;
} Operacion;

// Nodo del arbol de operaciones, ordenado por uid
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

Operacion crearOperacion(int uid, int esIngreso, int monto) {
    Operacion nueva;
    nueva.uid = uid;
    if (esIngreso) {
        nueva.tipo = 'I';
    } else {
        nueva.tipo = 'E';
    }
    nueva.monto = monto;

    return nueva;
}

// Funcion recursiva: inserta la operacion manteniendo el orden por uid
NodoOperacion *insertarOperacion(NodoOperacion *raiz, Operacion operacion) {
    if (raiz == NULL) {
        NodoOperacion *nuevo = malloc(sizeof(NodoOperacion));
        nuevo->operacion = operacion;
        nuevo->izq = NULL;
        nuevo->der = NULL;

        return nuevo;
    }

    if (operacion.uid < raiz->operacion.uid) {
        raiz->izq = insertarOperacion(raiz->izq, operacion);
    } else {
        raiz->der = insertarOperacion(raiz->der, operacion);
    }

    return raiz;
}

// Recorrido en orden: muestra las operaciones de menor a mayor uid
void mostrarOperaciones(NodoOperacion *raiz) {
    if (raiz != NULL) {
        mostrarOperaciones(raiz->izq);
        if (raiz->operacion.tipo == 'I') {
            printf("  [%d] ingreso $%d\n", raiz->operacion.uid, raiz->operacion.monto);
        } else {
            printf("  [%d] egreso  $%d\n", raiz->operacion.uid, raiz->operacion.monto);
        }
        mostrarOperaciones(raiz->der);
    }
}

void liberarOperaciones(NodoOperacion *raiz) {
    if (raiz != NULL) {
        liberarOperaciones(raiz->izq);
        liberarOperaciones(raiz->der);
        free(raiz);
    }
}

// Crea una operacion con el siguiente uid y la agrega a la coleccion
void agregarOperacion(tBilletera billetera, int esIngreso, int monto) {
    billetera->ultimoUid++;
    Operacion operacion = crearOperacion(billetera->ultimoUid, esIngreso, monto);
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
    agregarOperacion(billetera, 1, monto);
    billetera->saldo += monto;
}

int registrarEgreso(tBilletera billetera, int monto) {
    int alcanza = monto <= billetera->saldo;

    if (alcanza) {
        agregarOperacion(billetera, 0, monto);
        billetera->saldo -= monto;
    }

    return alcanza;
}

void listarOperaciones(tBilletera billetera) {
    mostrarOperaciones(billetera->operaciones);
}

int verSaldo(tBilletera billetera) {
    return billetera->saldo;
}
