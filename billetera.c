#include <stdio.h>
#include <stdlib.h>

#include <tUsuario.h>;
#include <billetera.h>;

typedef struct Billetera {
    int cantidadUsuarios;
    tUsuario usuarios;
} Billetera;

//  Constructor
Billetera* crearBilletera() {
    Billetera *objeto = malloc(sizeof(Billetera));
    objeto->cantidadUsuarios = 0;

    return objeto;
}


void insertarUsuario(tUsuario *actual, tUsuario nuevoUsuario) {
    // nuevoUsuario tiene salod menor
    if (actual.id > nuevoUsuario.id) {
        
        // tiene un hijo izquierda?
        if (actual.izq != NULL) {
            insertarUsuario(actual.izq, nuevoUsuario)

            // si no tiene hijo izquierda
        } else {
            actual->izq = nuevoUsuario
        }

    // nuevoUsuario tiene id mayor
    } (actual.id < nuevoUsuario.id) {

        // tiene un hijo derecho?
        if (actual.der != NULL) {
            insertarUsuario(actual.der, nuevoUsuario)

            // si no tiene hijo izquierda
        } else {
            actual->der = nuevoUsuario
        }
    }
};

void _obtenerUsuario() {
    
}

tUsuario* buscarUsuario(Billetera, *billetera, int id) {
    if (Billetera->usuarios != NULL) {

    } else {

        
    }
}

// Procedimiento recursivo
void registrarUsuario(Billetera *billetera, tUsuario usuarioNuevo) {

    if(billetera->usuarios=NULL){
        billetera->usuarios = usuarioNuevo;
    } else {
        insertarUsuario(billetera->usuarios, usuarioNuevo);
    }
}



usuario = crearUsuario()

agregarUsuario(billetera, usuario)