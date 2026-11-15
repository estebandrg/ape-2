#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tBilletera.h"
#include "tOperacion.h"
#include "tFecha.h"
#include "tUsuario.h"

typedef struct nodoUsuario{
    Usuario usuario;
    struct nodoUsuario *izq;
    struct nodoUsuario *der;
} *ArbolUsuario;

#define MAX_INTENTOS_UID 100

//Operaciones principales de la billetera
void mostrarMenu(void);

void mostrarUsuarios(ArbolUsuario raiz);

void registrarUsuario(ArbolUsuario *raiz, char *nombre);

void eliminarUsuario(ArbolUsuario *raiz, int uid);

void consultarSaldoUsuario(ArbolUsuario raiz, int uid);

void registrarIngreso(ArbolUsuario raiz, int uid, float monto, Fecha fecha);

void registrarEgreso(ArbolUsuario raiz, int uid, float monto, Fecha fecha);

// Modulos auxiliares

Usuario buscarUsuario(ArbolUsuario raiz, int uid);

Usuario buscarUsuarioIdMinimo(ArbolUsuario raiz);

void imprimirUsuario(Usuario usuario);

int contarUsuarios(ArbolUsuario raiz);

void destruirUsuarios(ArbolUsuario raiz);


int main(void) {
    srand((unsigned)time(NULL));
    
    ArbolUsuario raiz = NULL;
    char nombre[20];
    int uid;
    float monto;

    Fecha fecha = NULL;

    mostrarMenu();

    int opcion = 0;
    do 
    {
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (contarUsuarios(raiz) == 0){
                    printf("No hay usuarios registrados.\n");
                }
                else {
                printf("Lista de usuarios:\n");
                printf("Total de usuarios: %d\n", contarUsuarios(raiz));
                    mostrarUsuarios(raiz);
                }
                break;

            case 2:
                scanf("%s", nombre);
                registrarUsuario(&raiz, nombre);
                nombre[0] = '\0'; //Limpiar el nombre después de registrar el usuario 
                // Registrar usuario
                break;
            case 3:
                scanf("%d", &uid);
                eliminarUsuario(&raiz, uid);
                // Eliminar usuario
                break;
            case 4:
                scanf("%d", &uid);
                consultarSaldoUsuario(raiz, uid);
                // Consultar saldo de un usuario
                break;
            case 5:
                leerDatosOperacion("ingreso", &uid, &monto, &fecha);
                registrarIngreso(raiz, uid, monto, fecha);
                fecha=NULL;
                // Registrar ingreso
                break;
            case 6:
                leerDatosOperacion("egreso", &uid, &monto, &fecha);
                registrarEgreso(raiz, uid, monto, fecha);
                fecha=NULL;
                //libera a la fecha de proposito, ya que la operacion se apodera de su referencia
                break;
            case 7:
                printf("Saliendo del sistema.\n");
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }
    }
    while (opcion!=7);

    return 0;
}

//Modulos principales de la billetera
void mostrarMenu(void) {
    printf("Bienvenido al sistema de billeteras.\n");
    printf("Menu:\n");
    printf("1. Mostrar lista de usuarios.\n");
    printf("2. Registrar usuario.\n");
    printf("3. Eliminar usuario.\n");
    printf("4. Consultar Saldo de un Usuario.\n");
    printf("5. Registrar ingreso.\n");
    printf("6. Registrar egreso.\n");
    printf("7. Salir\n");
}

void mostrarUsuarios(ArbolUsuario raiz){
    if (raiz != NULL) {

        if (raiz->izq != NULL) {
            mostrarUsuarios(raiz->izq);
        }
        imprimirUsuario(raiz->usuario);
        if (raiz->der != NULL) {
            mostrarUsuarios(raiz->der);
        }
    }
}    

void registrarUsuario(ArbolUsuario *raiz, char* nombre) {

    if (raiz == NULL) {
        *raiz = malloc(sizeof(struct nodoUsuario));
        (*raiz)->usuario = crearUsuario(nombre);
        (*raiz)->izq = NULL;
        (*raiz)->der = NULL;
    } 
    else {
        Usuario nuevo_usuario = crearUsuario(nombre);
        if (verIdUsuario((*raiz)->usuario) < verIdUsuario(nuevo_usuario)) {
            agregarUsuario(&((*raiz)->izq), nuevo_usuario);
        } 
        else {
            agregarUsuario(&((*raiz)->der), nuevo_usuario);
        }
    }
}

void eliminarUsuario(ArbolUsuario *raiz, int uid) {
    
    Usuario usuario_buscado = buscarUsuario(*raiz, uid);
    if (usuario_buscado == NULL) {
        printf("Usuario con ID %d no encontrado.\n", uid);
    }
}

void consultarSaldoUsuario(ArbolUsuario raiz, int uid){
    Usuario usuario_buscado = buscarUsuario(raiz, uid);

    if (usuario_buscado == NULL) {
        printf("Usuario con ID %d no encontrado.\n", uid);
    }
    else {
        printf("Saldo de %s: %.2f\n", 
        verNombreUsuario(usuario_buscado), 
        verSaldoBilletera(verBilleteraUsuario(usuario_buscado)));
    }
}

void registrarIngreso(ArbolUsuario raiz, int uid, float monto, Fecha fecha) {
    Usuario usuario_buscado = buscarUsuario(raiz, uid);
    if (usuario_buscado == NULL) {
        printf("Usuario con ID %d no encontrado.\n", uid);
    } else {
        Operacion nueva_operacion = crearOperacion(uid, "ingreso", monto, fecha);
        registrarOperacion(verBilleteraUsuario(usuario_buscado), nueva_operacion);
    }
}

void registrarEgreso(ArbolUsuario raiz, int uid, float monto, Fecha fecha) {
    Usuario usuario_buscado = buscarUsuario(raiz, uid);
    if (usuario_buscado == NULL) {
        printf("Usuario con ID %d no encontrado.\n", uid);
    } 
    else {
        Operacion nueva_operacion = crearOperacion(uid, "egreso", monto, fecha);
        registrarOperacion(verBilleteraUsuario(usuario_buscado), nueva_operacion);
    }
}


// Modulos auxiliares

void leerFecha(int* dia, int* mes, int* anio){
    printf("    Día: ");
    scanf("%d", &dia);
    printf("    Mes: ");
    scanf("%d", &mes);
    printf("    Año: ");
    scanf("%d", &anio);
}

void leerDatosOperacion(char *tipo, int *uid, float *monto, Fecha *fecha) {
    int dia, mes, anio;
    printf("Ingrese los datos de la operacion de %s: \n", tipo);
    printf("ID del usuario: ");
    scanf("%d", uid);
    printf("Monto: ");
    scanf("%f", monto);
    printf("Fecha actual: ");
    leerFecha(&dia, &mes, &anio);
    *fecha = crearFecha(dia, mes, anio);
}

int contarUsuarios(ArbolUsuario raiz) {
    int contador = 0;
    if (raiz != NULL) {
        contador++;
        if (raiz->izq != NULL) {
            contador += contarUsuarios(raiz->izq);
        }
        if (raiz->der != NULL) {
            contador += contarUsuarios(raiz->der);
        }
    }
    return contador;
}

// Modulo recursivo que agrega un nuevo usuario en las hojas del árbol binario de búsqueda
void agregarUsuario(ArbolUsuario *raiz, Usuario nuevo_usuario) {
    if (*raiz == NULL) {
        *raiz = malloc(sizeof(struct nodoUsuario));
        (*raiz)->usuario = nuevo_usuario;
        (*raiz)->izq = NULL;
        (*raiz)->der = NULL;
    } 
    else {
        if (verIdUsuario(nuevo_usuario) < verIdUsuario((*raiz)->usuario)) {
            agregarUsuario(&((*raiz)->izq), nuevo_usuario);
        } 
        else {
            agregarUsuario(&((*raiz)->der), nuevo_usuario);
        }
    }
}

Usuario buscarUsuario(ArbolUsuario raiz, int uid) {
    Usuario usuario_buscado = NULL;

    if (raiz != NULL) {
        if (verIdUsuario(raiz->usuario) == uid) {
            usuario_buscado = raiz->usuario;
        } 
        else{
            if (uid < verIdUsuario(raiz->usuario) && raiz->izq != NULL) {
                usuario_buscado = buscarUsuario(raiz->izq, uid);
            } 

            else if (uid > verIdUsuario(raiz->usuario) && raiz->der != NULL) {
                usuario_buscado = buscarUsuario(raiz->der, uid);
            }
        }
    }
       
    return usuario_buscado;
}

Usuario buscarUsuarioIdMinimo(ArbolUsuario raiz) {
    Usuario usuario_minimo = NULL;

    if (raiz != NULL) {
        if (raiz->izq == NULL) {
            usuario_minimo = raiz->usuario;
        } 
        else {
            usuario_minimo = buscarUsuarioIdMinimo(raiz->izq);
        }
    }

    return usuario_minimo;
}

//Modulo que muestra la informacion de un usuario en pantalla
void imprimirUsuario(Usuario usuario_objetivo) {
    printf("ID: %d, Nombre: %s, Saldo: %.2f\n, Operaciones realizadas: %d\n", 
        verIdUsuario(usuario_objetivo), 
        verNombreUsuario(usuario_objetivo), 
        verSaldoBilletera(verBilleteraUsuario(usuario_objetivo)),
        obtenerCantOpsBilletera(verBilleteraUsuario(usuario_objetivo)));
}

void destruirUsuarios(ArbolUsuario raiz) {
    if (raiz != NULL) {
        destruirUsuarios(raiz->izq);
        destruirUsuarios(raiz->der);
        destruirUsuario(raiz->usuario);
        free(raiz);
    }
}
