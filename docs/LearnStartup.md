# **Lean Startup aplicado a BeeLine** 🐝

## **1. Hipótesis**

* **Hipótesis de problema**: Estudiantes y profesionales necesitan resolver problemas básicos de investigación de operaciones (ruta más corta, árbol mínimo, etc.) sin aprender un lenguaje especializado ni usar software costoso.
* **Hipótesis de solución**: Una herramienta open source, en C++, que lea CSV y genere resultados procesados por terminal, será adoptada rápidamente por este público, siempre que sea simple y extensible.

---

## **2. Producto Mínimo Viable (MVP)**

* **Funcionalidad mínima**:

  1. Leer archivo CSV con nodos y aristas.
  2. Ejecutar Dijkstra (ruta más corta) y Kruskal (árbol mínimo).
  3. Exportar resultados a CSV.
* **Experiencia mínima**:

  * Un solo comando:

    ```bash
    beeline input.csv output.csv --algoritmo dijkstra --origen A
    ```
  * Colores y barra de progreso en terminal para feedback.

---

## **3. Métricas de Éxito (MVP)**

* **Cuantitativas**:

  * Número de descargas/repositorios clonados.
  * Cantidad de issues/PRs abiertos en GitHub.
  * Tiempo promedio de uso por usuario (telemetría opcional).
* **Cualitativas**:

  * Feedback positivo de estudiantes/docentes.
  * Solicitudes de nuevos algoritmos o formatos.

---

## **4. Ciclo de Validación**

1. **Construir** → Crear versión mínima con Dijkstra y Kruskal.
2. **Medir** → Compartir en foros de programación, universidades, GitHub.
3. **Aprender** → Decidir si ampliar funciones o simplificar según feedback.

