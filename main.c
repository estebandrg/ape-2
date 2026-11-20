#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tBilletera.h"
#include "tOperacion.h"
#include "tFecha.h"

typedef struct nodoBilletera{
    Billetera billetera;
    struct nodoBilletera *izq;
    struct nodoBilletera *der;
} *ArbolBilletera;

#define MAX_INTENTOS_UID 100

//Operaciones principales de la billetera
void mostrarMenu();

void mostrarBilleteras(ArbolBilletera raiz);

void listarBilleterasConSaldoSuperior(ArbolBilletera raiz, float monto, int *cantidad_coincidencias);

void registrarBilletera(ArbolBilletera *raiz, char *nombre, int *op_exitosa, int *uid_asignado);

void eliminarBilletera(ArbolBilletera *raiz, int uid, int *op_exitosa);

void consultarSaldoBilletera(ArbolBilletera raiz, int uid);

void registrarIngreso(ArbolBilletera raiz, int uid, float monto, Fecha fecha, int *op_exitosa);

void registrarEgreso(ArbolBilletera raiz, int uid, float monto, Fecha fecha, int *op_exitosa);

// Modulos auxiliares

void leerFecha(int* dia, int* mes, int* anio);

void leerDatosOperacion(char *tipo, int *uid, float *monto, Fecha *fecha);

void agregarBilletera(ArbolBilletera *raiz, ArbolBilletera nueva_billetera, int *op_exitosa);

void buscarSucesor(ArbolBilletera raiz, ArbolBilletera *padre_sucesor, ArbolBilletera *sucesor);

Billetera buscarBilletera(ArbolBilletera raiz, int uid);

void imprimirBilletera(Billetera billetera);

int contarBilleteras(ArbolBilletera raiz);

void destruirBilleteras(ArbolBilletera raiz);


int main() {
    srand((unsigned)time(NULL));
    //Variables de proposito temporal
    ArbolBilletera raiz = NULL;
    int cantidad_billeteras = 0;
    int cantidad_coincidencias = 0;
    int uid_asignado = 0;
    char nombre[20]={0};
    int uid=0;
    float monto=0.0;
    Fecha fecha = NULL;
    int op_exitosa = 0;

    //Variable de control de operaciones
    int opcion = 0;
    do 
    {   
        mostrarMenu();
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: //Mostrar billeteras en lista
                cantidad_billeteras = contarBilleteras(raiz);
                if (cantidad_billeteras == 0){
                    printf("->No hay usuarios registrados.\n");
                }
                else {
                printf("->Lista de usuarios:\n");
                printf("->Total de usuarios: %d\n", cantidad_billeteras);
                    mostrarBilleteras(raiz);
                }
                break;

            case 2: // Registrar usuario
                printf("->Ingrese el nombre del usuario a registrar: ");
                scanf("%19s", nombre);
                registrarBilletera(&raiz, nombre, &op_exitosa, &uid_asignado);
                if (op_exitosa) {
                    printf("->Usuario '%s' registrado exitosamente con UID %d.\n", nombre, uid_asignado);
                } else {
                    printf("->Error al registrar el usuario '%s'.\n", nombre);
                }
                op_exitosa = 0; // Reiniciar el indicador de éxito para la próxima operación
                break;
            case 3:
                printf("->Ingrese el ID del usuario a eliminar: ");
                scanf("%d", &uid);
                eliminarBilletera(&raiz, uid, &op_exitosa);
                if (op_exitosa) {
                        printf("->Usuario con ID %d eliminado exitosamente.\n", uid);
                } else {
                        printf("->Usuario con ID %d no encontrado.\n", uid);
                    }
                op_exitosa = 0; // Reiniciar el indicador de éxito para la próxima operación
                // Eliminar usuario
                break;
            case 4:// Consultar saldo de un usuario
                printf("->Ingrese el ID del usuario para consultar su saldo: ");
                scanf("%d", &uid);
                consultarSaldoBilletera(raiz, uid);
                
                break;
            case 5:// Registrar ingreso
                leerDatosOperacion("ingreso", &uid, &monto, &fecha);
                registrarIngreso(raiz, uid, monto, fecha, &op_exitosa);
                if (op_exitosa) {
                    printf("Ingreso registrado exitosamente para el usuario con ID %d.\n", uid);
                } else {
                    printf("Error al registrar el ingreso para el usuario con ID %d.\n", uid);
                }
                destruirFecha(fecha); // Liberar la memoria de la fecha después de registrar la operación
                break;
            case 6:// Registrar egreso
                leerDatosOperacion("egreso", &uid, &monto, &fecha);
                registrarEgreso(raiz, uid, monto, fecha, &op_exitosa);
                if (op_exitosa) {
                    printf("->Egreso registrado exitosamente para el usuario con ID %d.\n", uid);
                } else {
                    printf("->Error al registrar el egreso para el usuario con ID %d.\n", uid);
                }
                destruirFecha(fecha); // Liberar la memoria de la fecha después de registrar la operación
                break;
            case 7: // Listar billeteras con saldo superior a un monto
                printf("->Ingrese el monto minimo de saldo: ");
                scanf("%f", &monto);
                cantidad_coincidencias = 0;
                listarBilleterasConSaldoSuperior(raiz, monto, &cantidad_coincidencias);
                if (cantidad_coincidencias == 0) {
                    printf("->No hay usuarios con saldo superior a %.2f.\n", monto);
                } else {
                    printf("->Total de usuarios listados: %d\n", cantidad_coincidencias);
                }
                break;
            case 8:
                printf("->Saliendo del sistema.\n");
                break;
            default:
                printf("->Opcion invalida. Intente nuevamente.\n");
        }
    }
    while (opcion != 8);

    destruirBilleteras(raiz);

    return 0;
}

//Modulos principales de la billetera
void mostrarMenu() {
    printf("--------------------------------------------------\n");
    printf("Bienvenido al sistema de billeteras.\n");
    printf("Menu:\n");
    printf("1. Mostrar lista de usuarios.\n");
    printf("2. Registrar usuario.\n");
    printf("3. Eliminar usuario.\n");
    printf("4. Consultar Saldo de un Usuario.\n");
    printf("5. Registrar ingreso.\n");
    printf("6. Registrar egreso.\n");
    printf("7. Listar usuarios con saldo superior a un monto.\n");
    printf("8. Salir\n");
    printf("-------------------------------------------------\n");

}

void mostrarBilleteras(ArbolBilletera raiz){

     if (raiz->izq != NULL) {
        mostrarBilleteras(raiz->izq);
    }
    imprimirBilletera(raiz->billetera);
            if (raiz->der != NULL) {
        mostrarBilleteras(raiz->der);
    }
}    

// Recorre el arbol en orden de UID e imprime las billeteras con saldo estrictamente mayor a monto.
// Escribe en *cantidad_coincidencias la cantidad de billeteras listadas.
void listarBilleterasConSaldoSuperior(ArbolBilletera raiz, float monto, int *cantidad_coincidencias) {
    if (raiz != NULL) {
        listarBilleterasConSaldoSuperior(raiz->izq, monto, cantidad_coincidencias);
        if (verSaldoBilletera(raiz->billetera) > monto) {
            imprimirBilletera(raiz->billetera);
            (*cantidad_coincidencias)++;
        }
        listarBilleterasConSaldoSuperior(raiz->der, monto, cantidad_coincidencias);
    }
}

void registrarBilletera(ArbolBilletera *raiz, char *nombre, int *op_exitosa, int *uid_asignado) {
    *op_exitosa = 0;
    *uid_asignado = 0;

    Billetera nuevaBilletera = NULL;
    int intentos = 0;

    while (nuevaBilletera == NULL && intentos < MAX_INTENTOS_UID) {
        nuevaBilletera = crearBilletera(nombre);
        if (nuevaBilletera != NULL &&
            buscarBilletera(*raiz, verIdBilletera(nuevaBilletera)) != NULL) {
            destruirBilletera(nuevaBilletera);
            nuevaBilletera = NULL;
        }
        intentos++;
    }

    if (nuevaBilletera != NULL) {         // se logró una billetera con UID único
        *uid_asignado = verIdBilletera(nuevaBilletera);
        ArbolBilletera nuevoNodo = malloc(sizeof(struct nodoBilletera));

        if (nuevoNodo != NULL) {
            nuevoNodo->billetera = nuevaBilletera;
            nuevoNodo->izq = NULL;
            nuevoNodo->der = NULL;
            agregarBilletera(raiz, nuevoNodo, op_exitosa);
        } else {
            destruirBilletera(nuevaBilletera);  // falló el malloc: liberar la billetera
        }
    }
}

void eliminarBilletera(ArbolBilletera *raiz, int uid, int *op_exitosa) {
    *op_exitosa=0;

    if (*raiz != NULL) {
        if (uid < verIdBilletera((*raiz)->billetera)) {
            eliminarBilletera(&( (*raiz)->izq ), uid, op_exitosa);
        } 
        else if (uid > verIdBilletera((*raiz)->billetera)) {
            eliminarBilletera(&( (*raiz)->der ), uid, op_exitosa);
        } 
        else {
            // ¡Nodo encontrado!
            ArbolBilletera temp = *raiz; // Guardamos el nodo actual

            if (temp->izq == NULL) {
                *raiz = temp->der; // Modificamos directamente el puntero original
                destruirBilletera(temp->billetera); // Liberamos la memoria de la billetera
                free(temp);
                *op_exitosa = 1; // Indicar que la operación fue exitosa
            } 
            else if (temp->der == NULL) {
                *raiz = temp->izq; // Modificamos directamente el puntero original
                destruirBilletera(temp->billetera); // Liberamos la memoria de la billetera
                free(temp);
                *op_exitosa = 1; // Indicar que la operación fue exitosa

            } 
            else {
                Billetera billetera_eliminada = temp->billetera;
                ArbolBilletera padre_sucesor = temp;
                ArbolBilletera sucesor = NULL;

                buscarSucesor(temp->der, &padre_sucesor, &sucesor);

                temp->billetera = sucesor->billetera;

                if (padre_sucesor == temp) {
                    padre_sucesor->der = sucesor->der;
                } 
                else {
                    padre_sucesor->izq = sucesor->der;
                }

                free(sucesor);                 // solo el nodo: la billetera ya se movió
                destruirBilletera(billetera_eliminada);
                *op_exitosa = 1;
                }
        }
    }
}

void consultarSaldoBilletera(ArbolBilletera raiz, int uid){
    Billetera billetera_buscada = buscarBilletera(raiz, uid);

    if (billetera_buscada == NULL) {
        printf("->Usuario con ID %d no encontrado.\n", uid);
    }
    else {
        printf("->Saldo de %s: %.2f\n", 
        verNombreBilletera(billetera_buscada), 
        verSaldoBilletera(billetera_buscada));
    }
}

void registrarIngreso(ArbolBilletera raiz, int uid, float monto, Fecha fecha, int *op_exitosa) {
    Billetera billetera_buscada = buscarBilletera(raiz, uid);
    if (billetera_buscada == NULL) {
        *op_exitosa = 0;
    } else {
        ingresarDinero(billetera_buscada, monto, fecha);
        *op_exitosa = 1;
    }
}

void registrarEgreso(ArbolBilletera raiz, int uid, float monto, Fecha fecha, int *op_exitosa) {
    Billetera billetera_buscada = buscarBilletera(raiz, uid);

    if (billetera_buscada == NULL) {
        *op_exitosa = 0;
    } 
    else if(verSaldoBilletera(billetera_buscada) < monto) {
        *op_exitosa = 0;
    }
    else {
        egresarDinero(billetera_buscada, monto, fecha);
        *op_exitosa = 1;
    }
}


// Modulos auxiliares de funcionamiento

void leerFecha(int* dia, int* mes, int* anio){
    printf("-->Día: ");
    scanf("%d", dia);
    printf("-->Mes: ");
    scanf("%d", mes);
    printf("-->Año: ");
    scanf("%d", anio);
}

void leerDatosOperacion(char *tipo, int *uid, float *monto, Fecha *fecha) {
    int dia=0;
    int mes=0; 
    int anio=0;
    *fecha = NULL;

    printf("->Ingrese los datos de la operacion de %s: \n", tipo);
    printf("-->ID del usuario: ");
    scanf("%d", uid);

    do {
        printf("-->Monto: ");
        scanf("%f", monto);
    } while (*monto <= 0);

    do {
        printf("-->Fecha de la operación:\n");
        leerFecha(&dia, &mes, &anio);
        if (!esFechaValida(dia, mes, anio)) {
            printf("-->Fecha invalida. Intente nuevamente.\n");
        } else{
            *fecha = crearFecha(dia, mes, anio);
        }
        
    } while (*fecha == NULL);
}

int contarBilleteras(ArbolBilletera raiz) {
    int contador = 0;
    if (raiz != NULL) {
        contador++;
        if (raiz->izq != NULL) {
            contador += contarBilleteras(raiz->izq);
        }
        if (raiz->der != NULL) {
            contador += contarBilleteras(raiz->der);
        }
    }
    return contador;
}

void agregarBilletera(ArbolBilletera *raiz, ArbolBilletera nueva_billetera, int *op_exitosa) {
    if (*raiz == NULL) {
        *raiz = nueva_billetera;
        *op_exitosa = 1;
    } 
    else if (verIdBilletera(nueva_billetera->billetera) < verIdBilletera((*raiz)->billetera)) {
        agregarBilletera(&((*raiz)->izq), nueva_billetera, op_exitosa);
    } 
    else {
        agregarBilletera(&((*raiz)->der), nueva_billetera, op_exitosa);
    }
}

Billetera buscarBilletera(ArbolBilletera raiz, int uid) {
    Billetera billetera_buscada = NULL;

    if (raiz != NULL) {
        if (verIdBilletera(raiz->billetera) == uid) {
            billetera_buscada = raiz->billetera;
        } 
        else{
            if (uid < verIdBilletera(raiz->billetera) && raiz->izq != NULL) {
                billetera_buscada = buscarBilletera(raiz->izq, uid);
            } 

            else if (uid > verIdBilletera(raiz->billetera) && raiz->der != NULL) {
                billetera_buscada = buscarBilletera(raiz->der, uid);
            }
        }
    }
       
    return billetera_buscada;
}

// Busca recursivamente el minimo del subarbol (sucesor in-orden) y su padre.
void buscarSucesor(ArbolBilletera raiz, ArbolBilletera *padre_sucesor, ArbolBilletera *sucesor) {
    if (raiz->izq == NULL) {
        *sucesor = raiz;
    } 
    else {
        *padre_sucesor = raiz;
        buscarSucesor(raiz->izq, padre_sucesor, sucesor);
    }
}
//Modulo que muestra la informacion de una billetera en pantalla
void imprimirBilletera(Billetera billetera_objetivo) {
    printf("->ID: %d, Nombre: %s, Saldo: %.2f, Operaciones realizadas: %d\n", 
        verIdBilletera(billetera_objetivo), 
        verNombreBilletera(billetera_objetivo), 
        verSaldoBilletera(billetera_objetivo),
        obtenerCantOpsBilletera(billetera_objetivo));
}

void destruirBilleteras(ArbolBilletera raiz) {
    if (raiz != NULL) {
        destruirBilleteras(raiz->izq);
        destruirBilleteras(raiz->der);
        destruirBilletera(raiz->billetera);
        free(raiz);
    }
}
