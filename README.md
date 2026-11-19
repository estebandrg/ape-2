# Billetera Virtual

Programa en C para gestionar billeteras de usuarios (alta, baja, ingresos, egresos y consultas).

## Compilar y ejecutar con el Makefile

Requisitos: `gcc` y `make`. Los comandos se corren desde la carpeta del proyecto.

| Comando | Qué hace |
| --- | --- |
| `make` | Compila el programa y genera el ejecutable `billetera`. |
| `make run` | Compila si hace falta y ejecuta el programa. |
| `make out` | Genera el ejecutable `out` (mismo programa, otro nombre). |
| `make clean` | Borra los ejecutables y los archivos `.o`. |

`make` solo recompila lo que cambió, así que volver a correrlo es rápido.

### Uso típico

```sh
make run
```

Si querés ejecutarlo a mano después de compilar:

```sh
make
./billetera
```

## Menú del programa

1. Mostrar lista de usuarios.
2. Registrar usuario.
3. Eliminar usuario.
4. Consultar saldo de un usuario.
5. Registrar ingreso.
6. Registrar egreso.
7. Listar usuarios con saldo superior a un monto.
8. Salir.