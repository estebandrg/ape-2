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

void registrarUsuario(ArbolUsuario *raiz, char *nombre, int *op_exitosa);

void eliminarUsuario(ArbolUsuario *raiz, int uid, int *op_exitosa);

void consultarSaldoUsuario(ArbolUsuario raiz, int uid);

void registrarIngreso(ArbolUsuario raiz, int uid, float monto, Fecha fecha);

void registrarEgreso(ArbolUsuario raiz, int uid, float monto, Fecha fecha);

// Modulos auxiliares

void leerFecha(int* dia, int* mes, int* anio);

void leerDatosOperacion(char *tipo, int *uid, float *monto, Fecha *fecha);

void agregarUsuario(ArbolUsuario *raiz, ArbolUsuario nuevo_usuario, int *op_exitosa);

Usuario buscarUsuario(ArbolUsuario raiz, int uid);

ArbolUsuario buscarUsuarioIdMinimo(ArbolUsuario raiz);

void imprimirUsuario(Usuario usuario);

int contarUsuarios(ArbolUsuario raiz);

void destruirUsuarios(ArbolUsuario raiz);


int main(void) {
    srand((unsigned)time(NULL));
    
    ArbolUsuario raiz = NULL;
    int cantidad_usuarios = 0;
    char nombre[20];
    int uid;
    float monto;
    Fecha fecha = NULL;

    int op_exitosa = 0;

    mostrarMenu();

    int opcion = 0;
    do 
    {
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                cantidad_usuarios = contarUsuarios(raiz);
                if (cantidad_usuarios == 0){
                    printf("No hay usuarios registrados.\n");
                }
                else {
                printf("Lista de usuarios:\n");
                printf("Total de usuarios: %d\n", cantidad_usuarios);
                    mostrarUsuarios(raiz);
                }
                break;

            case 2:
                printf("Ingrese el nombre del usuario a registrar: ");
                scanf("%s", nombre);
                registrarUsuario(&raiz, nombre, &op_exitosa);
                if (op_exitosa) {
                    printf("Usuario '%s' registrado exitosamente.\n", nombre);
                } else {
                    printf("Error al registrar el usuario '%s'.\n", nombre);
                }
                op_exitosa = 0; // Reiniciar el indicador de éxito para la próxima operación
                // Registrar usuario
                break;
            case 3:
                printf("Ingrese el ID del usuario a eliminar: ");
                scanf("%d", &uid);
                eliminarUsuario(&raiz, uid, &op_exitosa);
                if (op_exitosa) {
                        printf("Usuario con ID %d eliminado exitosamente.\n", uid);
                } else {
                        printf("Usuario con ID %d no encontrado.\n", uid);
                    }
                op_exitosa = 0; // Reiniciar el indicador de éxito para la próxima operación
                // Eliminar usuario
                break;
            case 4:
                printf("Ingrese el ID del usuario para consultar su saldo: ");
                scanf("%d", &uid);
                consultarSaldoUsuario(raiz, uid);
                // Consultar saldo de un usuario
                break;
            case 5:
                leerDatosOperacion("ingreso", &uid, &monto, &fecha);
                registrarIngreso(raiz, uid, monto, fecha);
                destruirFecha(fecha); // Liberar la memoria de la fecha después de registrar la operación
                fecha=NULL;
                // Registrar ingreso
                break;
            case 6:
                leerDatosOperacion("egreso", &uid, &monto, &fecha);
                registrarEgreso(raiz, uid, monto, fecha);
                destruirFecha(fecha); // Liberar la memoria de la fecha después de registrar la operación
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

    destruirUsuarios(raiz);

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

void registrarUsuario(ArbolUsuario *raiz, char* nombre, int *op_exitosa) {
    ArbolUsuario nuevoNodo = malloc(sizeof(struct nodoUsuario));

    Usuario nuevoUsuario = NULL;
    int intentos = 0;

    while (nuevoUsuario == NULL && intentos < MAX_INTENTOS_UID) {
        nuevoUsuario = crearUsuario(nombre);
        if (nuevoUsuario != NULL && buscarUsuario(*raiz, verIdUsuario(nuevoUsuario)) != NULL) {
            destruirUsuario(nuevoUsuario);
            nuevoUsuario = NULL;
        }
        intentos++;
    }
    
    if (intentos != MAX_INTENTOS_UID){
        nuevoNodo->usuario = nuevoUsuario;

        nuevoNodo->izq = NULL;
        nuevoNodo->der = NULL;

        if (*raiz == NULL) {
            *raiz = nuevoNodo;
            *op_exitosa = 1; // Indicar que la operación fue exitosa
        } 
        else {
            if (verIdUsuario(nuevoNodo->usuario) < verIdUsuario((*raiz)->usuario)) {
                agregarUsuario(&((*raiz)->izq), nuevoNodo, op_exitosa);
            } else {
                agregarUsuario(&((*raiz)->der), nuevoNodo, op_exitosa);
            }
        }
    }

}

void eliminarUsuario(ArbolUsuario *raiz, int uid, int *op_exitosa) {

    if (*raiz != NULL) {
        if (uid < verIdUsuario((*raiz)->usuario)) {
            eliminarUsuario(&( (*raiz)->izq ), uid, op_exitosa);
        } 
        else if (uid > verIdUsuario((*raiz)->usuario)) {
            eliminarUsuario(&( (*raiz)->der ), uid, op_exitosa);
        } 
        else {
            // ¡Nodo encontrado!
            ArbolUsuario temp = *raiz; // Guardamos el nodo actual

            if (temp->izq == NULL) {
                *raiz = temp->der; // Modificamos directamente el puntero original
                destruirUsuario(temp->usuario); // Liberamos la memoria del usuario
                free(temp);
                *op_exitosa = 1; // Indicar que la operación fue exitosa
            } 
            else if (temp->der == NULL) {
                *raiz = temp->izq; // Modificamos directamente el puntero original
                destruirUsuario(temp->usuario); // Liberamos la memoria del usuario
                free(temp);
                *op_exitosa = 1; // Indicar que la operación fue exitosa

            } 
            else {
                Usuario usuario_eliminado = temp->usuario;
                ArbolUsuario padre_sucesor = temp;
                ArbolUsuario sucesor = temp->der;

                while (sucesor->izq != NULL) {
                    padre_sucesor = sucesor;
                    sucesor = sucesor->izq;
                }

                temp->usuario = sucesor->usuario;

                if (padre_sucesor == temp) {
                    padre_sucesor->der = sucesor->der;
                } 
                else {
                    padre_sucesor->izq = sucesor->der;
                }

                free(sucesor);                 // solo el nodo: el usuario ya se movió
                destruirUsuario(usuario_eliminado);
                *op_exitosa = 1;
                }
        }
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
    scanf("%d", dia);
    printf("    Mes: ");
    scanf("%d", mes);
    printf("    Año: ");
    scanf("%d", anio);
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

void agregarUsuario(ArbolUsuario *raiz, ArbolUsuario nuevo_usuario, int *op_exitosa) {
    if (*raiz == NULL) {
        *raiz = nuevo_usuario;
        *op_exitosa = 1;
    } 
    else if (verIdUsuario(nuevo_usuario->usuario) < verIdUsuario((*raiz)->usuario)) {
        agregarUsuario(&((*raiz)->izq), nuevo_usuario, op_exitosa);
    } 
    else {
        agregarUsuario(&((*raiz)->der), nuevo_usuario, op_exitosa);
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

ArbolUsuario buscarUsuarioIdMinimo(ArbolUsuario raiz) {
    ArbolUsuario usuario_minimo = NULL;

    if (raiz != NULL) {
        if (raiz->izq == NULL) {
            usuario_minimo = raiz;
        } 
        else {
            usuario_minimo = buscarUsuarioIdMinimo(raiz->izq);
        }
    }

    return usuario_minimo;
}

//Modulo que muestra la informacion de un usuario en pantalla
void imprimirUsuario(Usuario usuario_objetivo) {
    printf("ID: %d, Nombre: %s, Saldo: %.2f, Operaciones realizadas: %d\n", 
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
