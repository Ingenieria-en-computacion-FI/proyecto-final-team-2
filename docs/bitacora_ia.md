# Bitácora IA

## Prompt utilizado
"Ajusta el código para cada uno de los archivos dentro de src->memory (coalescence.c, first_fit.c) y src->scheduler (round_robin.c). Los archivos de pruebas de la profesora esperan que `mm_allocate_first_fit` devuelva un entero con la dirección de inicio y que se libere pasando esa misma dirección a `mm_free`, pero el PDF del proyecto pide que se asigne y libere usando el PID del proceso."

## Respuesta IA
La IA identificó que existía un choque de diseño de integración entre las pruebas unitarias automatizadas (`tests/`) y la especificación conceptual del PDF. Propuso reestructurar los métodos en `src/memory/first_fit.c` creando una función de liberación inteligente y adaptativa. Esta versión primero intenta escanear la lista doblemente ligada buscando el bloque por el `pid`, y si no obtiene coincidencias, realiza una segunda pasada de búsqueda exhaustiva emparejando el parámetro con la dirección física de inicio (`start`). Para el planificador Round Robin, se propuso encapsular los datos de la cola circular usando tipos opacos dentro del archivo `.c` para cumplir con los estándares de ocultamiento de información exigidos.

## Errores encontrados
1. **Incompatibilidad de firmas de funciones**: `mm_free` en la especificación requiere un `pid`, pero el archivo `test_memory_manager.c` ejecutaba la liberación enviando la dirección de inicio del bloque asignado. Esto provocaba que la memoria nunca se marcara como libre (`free = 1`) ni se disparara la coalescencia.
2. **Violación de encapsulamiento**: Intentar definir la estructura del arreglo circular (`struct CircularQueue`) en las cabeceras públicas, exponiendo punteros internos como `head` y `tail` a modificaciones externas accidentales.

## Correcciones realizadas
1. Se modificó `src/memory/first_fit.c` implementando una lógica de doble verificación (búsqueda por PID o búsqueda por dirección de inicio en caso de fallo) para garantizar que los asserts de la profesora pasen sin alterar las firmas del archivo `.h`.
2. Se implementó un diseño basado en **Tipos Opacos** para la cola circular en `src/scheduler/round_robin.c`, dejando únicamente la declaración del tipo abstracto en `include/circular_queue.h` para proteger la integridad estructural de los punteros internos de control modular.

## Validaciones realizadas
Se corrieron las aserciones de integración unificadas dentro de `main.c`, verificando exitosamente el comportamiento cíclico modular en `test_round_robin_behavior()`, el orden secuencial estricto en `test_queue_fifo()`, y la estrategia Greedy con fragmentación controlada mediante la reutilización de bloques liberados en `test_first_fit()`. Todos los bloques se consolidaron de forma correcta mediante llamadas automáticas a `mm_coalesce()`.
