#include <stdio.h>
#include <stdlib.h>

#include "tUsuario.h"
#include "tBilletera.h"

typedef struct Billetera {
    int cantidadUsuarios;
    Usuario *usuarios;
} *Billetera;

//  Constructor
Billetera crearBilletera() {
    Billetera nuevaBilletera = malloc(sizeof(Billetera));
    nuevaBilletera->cantidadUsuarios = 0;

    return nuevaBilletera;
}

// Funcionalidades privadas
void _insertarUsuario(Usuario *actual, Usuario nuevoUsuario) {
    
    // Catch de erroriño
    if(*actual == NULL){
        *actual = nuevoUsuario;
    } else {

        if(verIdUsuario(nuevoUsuario) < verIdUsuario(*actual)){
            Usuario izq = verIzqUsuario(*actual);
            insertarUsuarioABB(&izq, nuevoUsuario);
            asignarIzqUsuario(*actual, izq);
        } else {
            Usuario der = verDerUsuario(*actual);
            insertarUsuarioABB(&der, nuevoUsuario);
            asignarDerUsuario(*actual, der);
        }
    }
};

Usuario _buscarUsuario(Usuario actual, int id){
    if(actual == NULL){
        return NULL;
    }
    if(verIdUsuario(actual) == id){
        return actual;
    }
    if(id < verIdUsuario(actual)){
        return _buscarUsuario(verIzqUsuario(actual), id);
    } else {
        return _buscarUsuario(verDerUsuario(actual), id);
    }
}

// Funcionalidades publicas

void registrarUsuario(Billetera billetera, Usuario usuarioNuevo) {
    if(billetera->usuarios=NULL){
        billetera->usuarios = usuarioNuevo;
    } else {
        insertarUsuario(billetera->usuarios, usuarioNuevo);
    }
}


void registrarOperacion(Billetera Billetera, Usuario usuario, Operacion operacion) {

}
// esto deberia recibir una operacion, la cual en base a su tipo, determinamos si es egreso o ingreso.
// debatimos mañana, concluimos en crear registrarOperacion.
void registrarIngreso() {

};

void registrarEgreso() {

}

void eliminarUsuario(int id);

int obtenerCantUsuarios(Billetera billetera) {
    return billetera->cantidadUsuarios;
}

