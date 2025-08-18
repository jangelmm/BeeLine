# **Product Backlog – BeeLine** 

---

# Historias de Usuario:

## **HU1 – Ejecución desde terminal**

**Historia de Usuario:**
Como usuario, quiero ejecutar BeeLine desde la terminal con parámetros de entrada y salida para resolver un problema específico.

**Criterios de aceptación:**

* BeeLine acepta parámetros como:

  ```bash
  beeline input.csv output.csv --algoritmo dijkstra --origen A
  ```
* Si los parámetros son inválidos, muestra mensaje de ayuda.
* Soporta `--help` para mostrar comandos disponibles.

**Tareas técnicas:**

* Configurar parser de argumentos (ej. `getopt` o `cxxopts`).
* Implementar comando `--help`.
* Validar rutas y existencia de archivos.

---

## **HU2 – Lectura de CSV**

**Historia de Usuario:**
Como usuario, quiero que BeeLine lea datos de un archivo CSV que contenga nodos y aristas para que el programa pueda procesarlos.

**Criterios de aceptación:**

* Soporta CSV con encabezados `origen, destino, peso`.
* Detecta errores de formato y muestra advertencia.
* Soporta separador `,` y `;`.

**Tareas técnicas:**

* Implementar función `leerCSV()`.
* Validar formato y datos numéricos.
* Escribir pruebas unitarias para casos válidos y con errores.

---

## **HU3 – Algoritmo Dijkstra**

**Historia de Usuario:**
Como usuario, quiero calcular la ruta más corta entre un nodo origen y todos los demás usando Dijkstra.

**Criterios de aceptación:**

* Devuelve distancias mínimas desde el nodo origen.
* Si un nodo es inalcanzable, marcar como `INF`.
* Procesa grafos no dirigidos y dirigidos.

**Tareas técnicas:**

* Implementar módulo `dijkstra.cpp`.
* Optimizar con cola de prioridad.
* Pruebas unitarias con grafos de ejemplo.

---

## **HU4 – Algoritmo Kruskal**

**Historia de Usuario:**
Como usuario, quiero calcular el árbol de expansión mínima usando Kruskal.

**Criterios de aceptación:**

* Devuelve lista de aristas del MST y peso total.
* Funciona en grafos no dirigidos.
* Si el grafo no es conexo, devuelve MST por componente.

**Tareas técnicas:**

* Implementar módulo `kruskal.cpp` con Union-Find.
* Validar casos de grafos pequeños y grandes.
* Escribir pruebas unitarias.

---

## **HU5 – Escritura de CSV de resultados**

**Historia de Usuario:**
Como usuario, quiero que BeeLine exporte los resultados a un archivo CSV para poder procesarlos en otras herramientas.

**Criterios de aceptación:**

* Soporta encabezados claros (`nodo, distancia` o `origen, destino, peso`).
* Genera archivo nuevo sin sobrescribir sin confirmación.
* Maneja errores de permisos o disco lleno.

**Tareas técnicas:**

* Implementar función `escribirCSV()`.
* Pruebas unitarias con distintos tamaños de salida.
* Validar codificación UTF-8.

---

## **HU6 – Barra de progreso y colores**

**Historia de Usuario:**
Como usuario, quiero ver una barra de progreso y mensajes en colores para entender el avance.

**Criterios de aceptación:**

* Barra de progreso en porcentaje.
* Colores para advertencias, errores y resultados.
* Compatible con terminales comunes.

**Tareas técnicas:**

* Usar librería como `termcolor` o ANSI codes.
* Implementar barra en funciones largas.
* Pruebas en Windows y Linux.

---

## **HU7 – Pruebas unitarias**

**Historia de Usuario:**
Como desarrollador, quiero tener pruebas unitarias para garantizar que los algoritmos funcionan correctamente.

**Criterios de aceptación:**

* Pruebas para Dijkstra y Kruskal.
* Pruebas para entrada/salida CSV.
* Integración en CI/CD de GitHub Actions.

**Tareas técnicas:**

* Configurar `Catch2` o `GoogleTest`.
* Crear dataset de prueba.
* Integrar pruebas en workflow.

---

## **HU8 – Modo verbose educativo**

**Historia de Usuario:**
Como docente, quiero un modo `--verbose` que muestre paso a paso la ejecución de los algoritmos.

**Criterios de aceptación:**

* Muestra en consola cada iteración del algoritmo.
* Colores para resaltar cambios.
* Se activa con `--verbose`.

**Tareas técnicas:**

* Agregar logs detallados.
* Opcional: ralentizar pasos para visualización.
* Pruebas con ejemplos educativos.

---

## **HU9 – Documentación inicial**

**Historia de Usuario:**
Como usuario, quiero contar con una guía rápida para usar BeeLine.

**Criterios de aceptación:**

* README con ejemplos.
* Instrucciones de compilación e instalación.
* Tabla de algoritmos soportados.

**Tareas técnicas:**

* Escribir README.md.
* Crear ejemplos en carpeta `/examples`.
* Capturas de pantalla de ejecución.

---

```
Título,Descripción,Etiqueta,Prioridad
HU1 – Ejecución desde terminal,"Como usuario, quiero ejecutar BeeLine desde la terminal con parámetros de entrada y salida para resolver un problema específico.",Sprint 1,Alta
HU2 – Lectura de CSV,"Como usuario, quiero que BeeLine lea datos de un archivo CSV que contenga nodos y aristas para que el programa pueda procesarlos.",Sprint 1,Alta
HU3 – Algoritmo Dijkstra,"Como usuario, quiero calcular la ruta más corta entre un nodo origen y todos los demás usando Dijkstra.",Sprint 1,Alta
HU4 – Algoritmo Kruskal,"Como usuario, quiero calcular el árbol de expansión mínima usando Kruskal.",Sprint 2,Alta
HU5 – Escritura de CSV de resultados,"Como usuario, quiero que BeeLine exporte los resultados a un archivo CSV para poder procesarlos en otras herramientas.",Sprint 1,Media
HU6 – Barra de progreso y colores,"Como usuario, quiero ver una barra de progreso y mensajes en colores para entender el avance.",Sprint 2,Media
HU7 – Pruebas unitarias,"Como desarrollador, quiero tener pruebas unitarias para garantizar que los algoritmos funcionan correctamente.",Sprint 1,Alta
HU8 – Modo verbose educativo,"Como docente, quiero un modo --verbose que muestre paso a paso la ejecución de los algoritmos.",Sprint 2,Media
HU9 – Documentación inicial,"Como usuario, quiero contar con una guía rápida para usar BeeLine.",Sprint 1,Media
```


# Historias Épicas

## **E1 - Funcionalidad**
Como usuario, quiero una herramienta completa de Investigación de Operaciones que me permita importar datos, elegir y ejecutar diferentes algoritmos para resolver problemas de grafos, y exportar resultados fácilmente.

HU1 - HU5

## **E2 - Intuitividad**
Como usuario y desarrollador, quiero una experiencia de uso mejorada y herramientas para validar y entender los algoritmos, con mensajes visuales, pruebas unitarias y un modo detallado para seguimiento.

HU6-HU8