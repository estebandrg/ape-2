#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tUsuario.h"
#include "tBilletera.h"
#include "tOperacion.h"
#include "tFecha.h"

#define MAX_INTENTOS_UID 100

/* Coleccion de usuarios: lista enlazada */

Usuario buscarUsuario(Usuario cabeza, int uid) {
    while (cabeza != NULL && verIdUsuario(cabeza) != uid) {
        cabeza = verSigUsuario(cabeza);
    }
    return cabeza;
}

/* Crea un usuario con UID unico y lo agrega al inicio. NULL si no consigue un UID libre. */
Usuario agregarUsuario(Usuario *cabeza, const char *nombre) {
    for (int intento = 0; intento < MAX_INTENTOS_UID; intento++) {
        Usuario nuevo = crearUsuario(nombre);
        if (nuevo == NULL) {
            return NULL;
        }
        if (buscarUsuario(*cabeza, verIdUsuario(nuevo)) == NULL) {
            asignarSigUsuario(nuevo, *cabeza);
            *cabeza = nuevo;
            return nuevo;
        }
        destruirUsuario(nuevo);
    }
    return NULL;
}

/* Devuelve 1 si elimino al usuario, 0 si no existe. */
int eliminarUsuario(Usuario *cabeza, int uid) {
    Usuario previo = NULL;
    Usuario actual = *cabeza;
    while (actual != NULL && verIdUsuario(actual) != uid) {
        previo = actual;
        actual = verSigUsuario(actual);
    }
    if (actual == NULL) {
        return 0;
    }
    if (previo == NULL) {
        *cabeza = verSigUsuario(actual);
    } else {
        asignarSigUsuario(previo, verSigUsuario(actual));
    }
    destruirUsuario(actual);
    return 1;
}

int contarUsuarios(Usuario cabeza) {
    int n = 0;
    for (; cabeza != NULL; cabeza = verSigUsuario(cabeza)) {
        n++;
    }
    return n;
}

void destruirUsuarios(Usuario cabeza) {
    while (cabeza != NULL) {
        Usuario siguiente = verSigUsuario(cabeza);
        destruirUsuario(cabeza);
        cabeza = siguiente;
    }
}

/* Debug */

void imprimirUsuarios(Usuario cabeza) {
    printf("%-8s %-20s %12s %5s\n", "UID", "Nombre", "Saldo", "Ops");
    for (; cabeza != NULL; cabeza = verSigUsuario(cabeza)) {
        Billetera b = verBilleteraUsuario(cabeza);
        printf("%-8d %-20s %12.2f %5d\n", verIdUsuario(cabeza), verNombreUsuario(cabeza),
               verSaldoBilletera(b), obtenerCantOpsBilletera(b));
    }
}

void imprimirOperaciones(Usuario usuario) {
    printf("Operaciones de %s (UID %d):\n", verNombreUsuario(usuario), verIdUsuario(usuario));
    for (Operacion op = verOpsBilletera(verBilleteraUsuario(usuario)); op != NULL;
         op = verSigOperacion(op)) {
        Fecha f = verFechaOperacion(op);
        printf("  #%d %-8s %10.2f %02d/%02d/%04d\n", verIdOperacion(op), verTipoOperacion(op),
               verMontoOperacion(op), obtenerDia(f), obtenerMes(f), obtenerAnio(f));
    }
}

int registrarEnUsuario(Usuario usuario, int idOp, const char *tipo, float monto, Fecha fecha) {
    Operacion op = crearOperacion(idOp, tipo, monto, fecha);
    if (op == NULL) {
        return 0;
    }
    if (!registrarOperacion(verBilleteraUsuario(usuario), op)) {
        destruirOperacion(op);
        return 0;
    }
    return 1;
}

int main(void) {
    srand((unsigned)time(NULL));
    Usuario usuarios = NULL;

    Usuario ana = agregarUsuario(&usuarios, "Ana");
    Usuario beto = agregarUsuario(&usuarios, "Beto");
    agregarUsuario(&usuarios, "Carla");
    printf("Usuarios registrados: %d\n", contarUsuarios(usuarios));

    Fecha fecha = crearFecha(4, 11, 2026);
    printf("Ingreso 500 valido: %d\n", registrarEnUsuario(ana, 1, "ingreso", 500, fecha));
    printf("Egreso 120 valido: %d\n", registrarEnUsuario(ana, 2, "egreso", 120, fecha));
    printf("Egreso 900 rechazado: %d\n", !registrarEnUsuario(ana, 3, "egreso", 900, fecha));
    printf("Tipo invalido rechazado: %d\n", !registrarEnUsuario(ana, 4, "otro", 10, fecha));
    destruirFecha(fecha);

    imprimirUsuarios(usuarios);
    imprimirOperaciones(ana);

    printf("Eliminar a Beto: %d\n", eliminarUsuario(&usuarios, verIdUsuario(beto)));
    printf("Eliminar inexistente: %d\n", eliminarUsuario(&usuarios, -1));
    printf("Usuarios registrados: %d\n", contarUsuarios(usuarios));

    destruirUsuarios(usuarios);
    return 0;
}
