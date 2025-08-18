# Crear un Archivo de Compilación CMake
Perfecto 👍
Te armo un **CMakeLists.txt** que compile tu proyecto completo y lo deje en `build/` con el ejecutable llamado `beeline`.

Como la estructura tiene subcarpetas (`Modelo/`, `Algoritmos/`, `IO/`, etc.), vamos a usar `file(GLOB_RECURSE ...)` para incluir automáticamente todos los `.cpp` dentro de `src/`.

Aquí va:

```cmake
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto y lenguaje
project(BeeLine LANGUAGES CXX)

# Estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Carpeta de código fuente
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

# Buscar todos los .cpp dentro de src y subcarpetas
file(GLOB_RECURSE SOURCES
    "${SRC_DIR}/*.cpp"
)

# Crear ejecutable
add_executable(beeline ${SOURCES})

# Incluir directorios de cabeceras
target_include_directories(beeline PRIVATE
    ${SRC_DIR}
    ${SRC_DIR}/Modelo
    ${SRC_DIR}/Algoritmos
    ${SRC_DIR}/IO
    ${SRC_DIR}/Vista
    ${SRC_DIR}/Utils
)

# Opcional: Warnings para desarrollo
target_compile_options(beeline PRIVATE -Wall -Wextra -pedantic)
```

---

## 📌 Cómo usarlo

1. Desde la raíz de tu proyecto:

   ```bash
   mkdir -p build
   cd build
   ```

2. Generar y compilar:

   ```bash
   cmake ..
   make
   ```

3. Ejecutar:

   ```bash
   ./beeline data/input.csv data/output.csv --algoritmo dijkstra --origen A
   ```

---

Este CMakeLists:

* Compila **todo lo que esté en `src/` y subcarpetas**.
* Te ahorra tener que listar cada `.cpp`.
* Configura C++17.
* Activa warnings útiles.

---


# Realizacion de un HU
En términos generales de **metodología ágil y desarrollo de software**, la realización de una HU (Historia de Usuario) suele cubrir más que solo codificación, compilación y pruebas. Lo que tú hiciste entra en esas categorías, pero normalmente se contempla así:

---

## 1️⃣ Análisis y comprensión

Antes de codificar, necesitas:

* **Definir claramente la HU**: qué quiere el usuario y cuál es el resultado esperado.
* **Identificar criterios de aceptación**: qué debe cumplirse para que la HU se considere terminada.
* **Diseño inicial o esquema de solución**: diagramas, clases, funciones, flujo de datos, etc.

En tu caso, esto se tradujo en definir `ParserArgs`, `Controlador`, `BeeLine` y los parámetros esperados.

---

## 2️⃣ Codificación

Implementas la solución siguiendo el diseño y cumpliendo los criterios de aceptación.

* Creación de clases, funciones, estructuras.
* Implementación del flujo de ejecución.
* Validaciones mínimas.

Tú hiciste: `BeeLine.cpp`, `Controlador.cpp`, `ParserArgs.cpp`, etc.

---

## 3️⃣ Compilación y construcción

Asegurarte de que tu código:

* Se compila sin errores.
* Produce ejecutables o librerías según lo esperado.
* Se integra correctamente con dependencias externas (como Google Test).

Tu paso con CMake y `make` cumple esto.

---

## 4️⃣ Pruebas

Validar que la HU funciona según los criterios de aceptación:

* **Tests unitarios**: verificar funciones o clases individuales (`ParserArgsTest`).
* **Tests de integración**: comprobar que varias partes funcionan juntas si aplica.
* **Tests funcionales**: ejecutar el flujo completo desde terminal, asegurarte de que el resultado es el esperado.

Tú ejecutaste `ctest` y verificaste que todo pasaba.

---

## 5️⃣ Documentación y cierre de HU

Aunque no es obligatorio en todos los equipos, es recomendable:

* Documentar la HU: qué hace, cómo se usa, ejemplos de ejecución.
* Marcarla como **completada** en el backlog.
* Revisar que los criterios de aceptación estén todos cumplidos.

---

### ✅ Resumen

Sí, **Codificación + Compilación + Pruebas** son esenciales, pero para una HU completa también conviene incluir:

1. **Análisis y diseño** (antes de codificar).
2. **Documentación y cierre** (después de probar).


