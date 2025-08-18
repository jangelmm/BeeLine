# **Design Thinking aplicado a BeeLine**

## **1. Descubrimiento / Empatía / Investigación (Divergencia)**

* **Contexto detectado**: La mayoría de herramientas de investigación de operaciones (IO) para resolver problemas como ruta más corta o árbol mínimo de expansión son:

  * Difíciles de usar para principiantes (requieren aprender un lenguaje específico).
  * Pensadas para entornos académicos avanzados o empresas grandes.
  * En su versión simple y usable, suelen ser de pago.
* **Necesidades de los usuarios**:

  * Estudiantes y docentes que quieren enseñar o aprender algoritmos de IO sin curva de aprendizaje alta.
  * Profesionales que necesitan resolver problemas rápidos desde un archivo, sin instalar software pesado.
  * Comunidad open source interesada en contribuir y expandir funcionalidades.
* **Hallazgos clave**:

  * Escasez de herramientas educativas, open source y con interfaz de línea de comandos (CLI) amigable.
  * Demanda de soluciones simples que trabajen directamente con formatos comunes como CSV.

---

## **2. Definición / Síntesis (Divergencia)**

* **Problema a resolver**:
  *"Actualmente no existe una herramienta de investigación de operaciones que sea gratuita, open source, fácil de usar desde terminal, que procese datos en formato CSV y devuelva resultados de forma directa, orientada tanto a la educación como a casos prácticos simples."*
* **Oportunidad de mercado**:

  * Crear una solución minimalista pero extensible, que sirva como introducción a IO y como herramienta práctica.
  * Enfocarse en una experiencia de uso rápida: `beeline input.csv output.csv algoritmo=...`
  * Crecer modularmente (scrum) para ir incorporando más algoritmos y funcionalidades.

---

## **3. Ideación (Divergencia y Convergencia)**

* **Lluvia de ideas de funciones iniciales**:

  * Algoritmos de ruta más corta (Dijkstra, Bellman-Ford, Floyd-Warshall).
  * Árbol mínimo de expansión (Kruskal, Prim).
  * Entrada y salida en CSV sin pasos intermedios.
  * Modo educativo con explicaciones paso a paso.
  * Código limpio en C++ y documentado para fomentar contribuciones.
  * Soporte para datos con etiquetas de texto, no solo índices numéricos.
* **Selección para primera versión**:

  * CLI minimalista con colores y progreso (para dar feedback visual en terminal).
  * Implementar primero Dijkstra y Kruskal.
  * Documentación clara con ejemplos de uso.

---

## **4. Implementación / Construcción (Divergencia y Convergencia)**

* **Primera iteración (v0.1)**:

  * Lectura de CSV de nodos y aristas.
  * Ejecución de algoritmo seleccionado desde argumentos de línea de comandos.
  * Exportación de resultados a CSV con ruta y costo.
* **Pruebas y feedback**:

  * Compartir prototipo con estudiantes y docentes de IO.
  * Ajustar comandos y formatos según comentarios.
* **Iteraciones siguientes**:

  * Agregar más algoritmos (Floyd-Warshall, flujo máximo, asignación).
  * Modo “verbose” educativo para explicar cada paso.
  * Optimización de rendimiento y soporte para datasets más grandes.

