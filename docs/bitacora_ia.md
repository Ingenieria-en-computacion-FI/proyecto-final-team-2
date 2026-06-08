# Bitácora IA

## Prompt utilizado
"Ajusta el código para cada uno de los archivos dentro de src->memory (coalescence.c, first_fit.c) y src->scheduler (round_robin.c). Además, ayúdame a resolver los errores de compilación con las cabeceras faltantes (-Iinclude), los tipos indefinidos (NULL y malloc), el enlazado de stack.c y la automatización del benchmark en Python para generar las gráficas."

## Respuesta IA
La IA identificó múltiples discrepancias de integración entre el código base y el entorno:
1. Choque de firmas en `mm_free` (esperaba dirección en el test pero PID en el diseño).
2. Ausencia de librerías estándar básicas (`<stdlib.h>` y `<stddef.h>`) en los archivos del directorio `src/`.
3. Error de enlazado debido a un archivo guardado incorrectamente con extensión `.h` en lugar de `.c`.
4. Falta de dependencias en el entorno de Python (`pandas`, `matplotlib`) y de la subcarpeta física `reports/` para almacenar las salidas.
Se proporcionaron las correcciones de código fuente y comandos de consola correspondientes.

## Errores encontrados
1. **Falta de librerías**: Errores `error: 'NULL' undeclared` y advertencias de funciones implícitas de memoria (`malloc`/`free`) en `coalescence.c` y `first_fit.c`.
2. **Error de Enlazador (ld)**: `undefined reference to stack_create` en las pruebas unitarias debido a que el archivo de la pila estaba nombrado como `stack.h` en lugar de `stack.c` en `src/scheduler/`, provocando que el Makefile lo ignorara.
3. **Falta de dependencias del entorno**: `ModuleNotFoundError: No module named 'pandas'` al intentar correr el script de analítica.
4. **Error de ejecución en subproceso**: `FileNotFoundError` al buscar el binario `./bin/main`, ya que el Makefile compilaba por defecto `bin/tests`.
5. **Falta de directorios físicos**: `OSError: Cannot save file into a non-existent directory: 'reports/csv'`.

## Correcciones realizadas
1. Se incorporaron `#include <stdlib.h>` y `#include <stddef.h>` en todas las implementaciones de `src/memory/` y `src/scheduler/`.
2. Se renombró el archivo físico a `src/stack.c`, rellenando la lógica completa de punteros para la estructura lineal LIFO.
3. Se instalaron los paquetes científicos mediante `pip` y se ejecutó un comando manual de `gcc` para enlazar el árbol completo de dependencias en `bin/main`.
4. Se crearon de forma recursiva los directorios mediante `mkdir -p reports/csv reports/graphs` para permitir el almacenamiento local de las métricas.
5. Se modificó `benchmark.py` inyectando código de Matplotlib para automatizar el renderizado visual de la curva de complejidad temporal.

## Validaciones realizadas
Se ejecutó con éxito el comando `make test` y el script de Python de forma secuencial. El compilador enlazó limpiamente todas las dependencias y la terminal arrojó el mensaje de éxito unificado `All tests passed!`. Finalmente, se inspeccionó visualmente el archivo `reports/graphs/benchmark_performance.png`, validando que la gráfica lineal de rendimiento empírico se generó de forma óptima y sin pérdidas de datos.
