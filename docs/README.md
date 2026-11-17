# Documentación del Sistema de Billeteras

Los diagramas de esta carpeta se generan con la skill **diagrammer**, del repositorio
[estebandrg/diagrammer-docs](https://github.com/estebandrg/diagrammer-docs). La skill toma una
especificación JSON (`diagrammer.spec.json`) y dibuja cada diagrama como un PNG con fondo
transparente.

## Contenido

| Carpeta | Qué muestra |
| --- | --- |
| `modulos/funciones/` | Módulos de `main.c` que devuelven un valor (`buscarUsuario`, `contarUsuarios`). |
| `modulos/procedimientos/` | Módulos de `main.c` que no devuelven valor (`void`). Los que entregan resultados por puntero, como `op_exitosa`, cuentan como procedimientos. |
| `interfaces/` | La interfaz pública de cada TAD (`IUsuario`, `IBilletera`, `IOperacion`, `IFecha`), tomada de los `.h`. |
| `estructuras/` | Las estructuras tipo nodo: `nodoUsuario` (árbol de usuarios) y `tOperacion` (lista de operaciones). |
| `diagrammer.spec.json` | Especificación de la que salen todas las imágenes. Es la fuente editable. |

Las interfaces `I*` son una representación de las funciones declaradas en cada `.h`; no existen como
tipo en el código C.

## Regenerar las imágenes

La herramienta no analiza código C: la especificación se escribe a mano (o con un agente usando la
skill). Si cambia el código, se edita `diagrammer.spec.json` y se vuelve a renderizar.

```sh
# 1. Clonar e instalar la herramienta (requiere Node.js 20 o superior)
git clone https://github.com/estebandrg/diagrammer-docs
cd diagrammer-docs && npm install && cd ..

# 2. Renderizar (desde la raíz de este proyecto)
node diagrammer-docs/bin/diagrammer.mjs render docs/diagrammer.spec.json \
  -o docs/_tmp --scale 3 --only module,structure --no-uses

# 3. Ordenar en subcarpetas
mkdir -p docs/modulos/funciones docs/modulos/procedimientos docs/interfaces docs/estructuras
mv docs/_tmp/module-buscarUsuario.png docs/_tmp/module-contarUsuarios.png docs/modulos/funciones/
mv docs/_tmp/module-*      docs/modulos/procedimientos/
mv docs/_tmp/structure-I*  docs/interfaces/
mv docs/_tmp/structure-*   docs/estructuras/
rmdir docs/_tmp
```

Opciones útiles: `--theme light` para el tema claro, `--scale 3` para imágenes más nítidas al imprimir.

## Nota sobre el idioma

La versión original de la herramienta dibuja algunos textos en inglés (`no fields`, `no methods`,
`«interface»`, `+N more`, `no inputs`). Estas imágenes se generaron con una copia modificada que los
muestra en español (`«interfaz»`, `«estructura»`, `+N más`, `sin entradas`, `sin salidas`) y oculta
las secciones vacías. Con la versión sin modificar, el resultado puede diferir en esos textos.
