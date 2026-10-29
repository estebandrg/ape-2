#include <stdio.h>
#include <stdlib.h>
#include "billetera.h"

// Usuario: struct simple que contiene su propia billetera (TAD)
typedef struct Usuario {
    int id;
    char nombre[20];
    tBilletera billetera;
    struct Usuario *izq;
    struct Usuario *der;
} Usuario;

// Agrega un usuario al arbol (ordenado por id), con una billetera nueva
void agregarUsuario(Usuario **raiz, int id, const char *nombre) {
    while (*raiz != NULL) {
        if (id < (*raiz)->id) {
            raiz = &(*raiz)->izq;
        } else {
            raiz = &(*raiz)->der;
        }
    }

    Usuario *nuevo = malloc(sizeof(Usuario));

    // Copiar caracter por caracter el nombre
    nuevo->id = id;
    int i = 0;
    while (nombre[i] != '\0' && i < 19) {
        nuevo->nombre[i] = nombre[i];
        i++;
    }
    nuevo->nombre[i] = '\0';
    nuevo->billetera = crearBilletera();
    nuevo->izq = NULL;
    nuevo->der = NULL;
    *raiz = nuevo;
}

// Busca un usuario por id. Retorna NULL si no existe
Usuario *buscarUsuario(Usuario *raiz, int id) {
    while (raiz != NULL && raiz->id != id) {
        if (id < raiz->id) {
            raiz = raiz->izq;
        } else {
            raiz = raiz->der;
        }
    }

    return raiz;
}

// Muestra los usuarios cuyo saldo supera el monto, ordenados por id
void listarUsuariosConSaldoMayorA(Usuario *raiz, int monto) {
    if (raiz != NULL) {
        listarUsuariosConSaldoMayorA(raiz->izq, monto);
        if (verSaldo(raiz->billetera) > monto) {
            printf("Usuario %d: %s, saldo $%d\n", raiz->id, raiz->nombre, verSaldo(raiz->billetera));
        }
        listarUsuariosConSaldoMayorA(raiz->der, monto);
    }
}

// Libera cada billetera y cada usuario del arbol
void liberarUsuarios(Usuario **raiz) {
    if (*raiz != NULL) {
        liberarUsuarios(&(*raiz)->izq);
        liberarUsuarios(&(*raiz)->der);
        destruirBilletera(&(*raiz)->billetera);
        free(*raiz);
        *raiz = NULL;
    }
}

int main(void) {
    Usuario *usuarios = NULL;

    agregarUsuario(&usuarios, 1, "Ana");
    agregarUsuario(&usuarios, 2, "Beto");

    Usuario *ana = buscarUsuario(usuarios, 1);
    registrarIngreso(ana->billetera, 1000);
    registrarEgreso(ana->billetera, 250);

    printf("Saldo de %s: $%d\n\n", ana->nombre, verSaldo(ana->billetera));

    Usuario *beto = buscarUsuario(usuarios, 2);
    registrarIngreso(beto->billetera, 500);
    if (!registrarEgreso(beto->billetera, 800)) {
        printf("%s no tiene saldo suficiente para el egreso de $800\n", beto->nombre);
    }
    printf("Saldo de %s: $%d\n", beto->nombre, verSaldo(beto->billetera));

    printf("\nUsuarios con saldo mayor a $600:\n");
    listarUsuariosConSaldoMayorA(usuarios, 600);

    liberarUsuarios(&usuarios);

    return 0;
}
