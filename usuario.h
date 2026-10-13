#ifndef USUARIO_H
#define USUARIO_H

typedef struct Usuario *tUsuario;

tUsuario crearUsuario();

void destruirUsuario(tUsuario *usuario);

#endif
