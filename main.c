#include <stdio.h>
#include <stdlib.h>
#include "billetera.h"

// Usuario: struct simple que contiene su propia billetera (TAD)
typedef struct Usuario {
    int id;
    char nombre[20];
    tBilletera billetera;
    struct Usuario *sig;
} Usuario;

// Agrega un usuario al principio de la lista, con una billetera nueva
void agregarUsuario(Usuario **lista, int id, const char *nombre) {
    Usuario *nuevo = malloc(sizeof(Usuario));
    nuevo->id = id;
    int i = 0;
    while (nombre[i] != '\0' && i < 19) {
        nuevo->nombre[i] = nombre[i];
        i++;
    }
    nuevo->nombre[i] = '\0';
    nuevo->billetera = crearBilletera();
    nuevo->sig = *lista;
    *lista = nuevo;
}

// Busca un usuario por id. Retorna NULL si no existe
Usuario *buscarUsuario(Usuario *lista, int id) {
    Usuario *actual = lista;

    while (actual != NULL && actual->id != id) {
        actual = actual->sig;
    }

    return actual;
}

// Libera cada billetera y cada usuario de la lista
void liberarUsuarios(Usuario **lista) {
    Usuario *actual = *lista;

    while (actual != NULL) {
        Usuario *siguiente = actual->sig;
        destruirBilletera(&actual->billetera);
        free(actual);
        actual = siguiente;
    }

    *lista = NULL;
}

int main(void) {
    Usuario *usuarios = NULL;

    agregarUsuario(&usuarios, 1, "Ana");
    agregarUsuario(&usuarios, 2, "Beto");

    Usuario *ana = buscarUsuario(usuarios, 1);
    registrarIngreso(ana->billetera, 1000);
    registrarEgreso(ana->billetera, 250);

    printf("Operaciones de %s:\n", ana->nombre);
    listarOperaciones(ana->billetera);
    printf("Saldo de %s: $%d\n\n", ana->nombre, verSaldo(ana->billetera));

    Usuario *beto = buscarUsuario(usuarios, 2);
    registrarIngreso(beto->billetera, 500);
    if (!registrarEgreso(beto->billetera, 800)) {
        printf("%s no tiene saldo suficiente para el egreso de $800\n", beto->nombre);
    }
    printf("Saldo de %s: $%d\n", beto->nombre, verSaldo(beto->billetera));

    liberarUsuarios(&usuarios);

    return 0;
}
