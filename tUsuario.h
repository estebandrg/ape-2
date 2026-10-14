#ifndef TADUSUARIO_H
#define TADUSUARIO_H

#include <tOperacion.h>

//Declaracion del tipo exportado
typedef struct tUsuario *Usuario;

//Constructor
Usuario crearUsuario(int id, char nombre[20], float saldo, Operacion lista);

//Observadoras
int verIdUsuario(Usuario usuario_objetivo);
char* verNombreUsuario(Usuario usuario_objetivo);
float verSaldoUsuario(Usuario usuario_objetivo);
Operacion verOpUsuario(Usuario usuario_objetivo);
Usuario verIzqUsuario(Usuario usuario_objetivo);
Usuario verDerUsuario(Usuario usuario_objetivo);

// Establecedores
void asignarIzqUsuario(Usuario usuario_objetivo, Usuario nuevoIzq);
void asignarDerUsuario(Usuario usuario_objetivo, Usuario nuevoDer);

Operacion buscarOpUsuario(Usuario usuario_objetivo, int id);

//Destructoras
void destruirUsuario(Usuario usuario_objetivo, int id);
#endif
