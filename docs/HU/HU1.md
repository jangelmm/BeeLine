# Codificación
## **1. src/main.cpp**

```cpp
#include "BeeLine.h"

int main(int argc, char* argv[]) {
    BeeLine app;
    return app.run(argc, argv);
}
```

---

## **2. src/BeeLine.h**

```cpp
#ifndef BEELINE_H
#define BEELINE_H

class BeeLine {
public:
    int run(int argc, char* argv[]);
};

#endif // BEELINE_H
```

---

## **3. src/BeeLine.cpp**

```cpp
#include "BeeLine.h"
#include "Controlador.h"

int BeeLine::run(int argc, char* argv[]) {
    Controlador controlador;
    return controlador.ejecutar(argc, argv);
}
```

---

## **4. src/Controlador.h**

```cpp
#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <string>
#include "Utils/ParserArgs.h"

class Controlador {
public:
    int ejecutar(int argc, char* argv[]);
};

#endif // CONTROLADOR_H
```

---

## **5. src/Controlador.cpp**

```cpp
#include "Controlador.h"
#include <iostream>

int Controlador::ejecutar(int argc, char* argv[]) {
    ParserArgs parser;
    Parametros params = parser.parsear(argc, argv);

    if (params.help) {
        parser.mostrarAyuda();
        return 0;
    }

    // Validación mínima
    if (params.input.empty() || params.output.empty()) {
        std::cerr << "Error: Debe especificar archivo de entrada y salida.\n";
        parser.mostrarAyuda();
        return 1;
    }

    std::cout << "Input file: " << params.input << "\n";
    std::cout << "Output file: " << params.output << "\n";
    std::cout << "Algorithm: " << params.algoritmo << "\n";
    std::cout << "Origin node: " << params.origen << "\n";
    std::cout << "BeeLine ready to run!\n";

    // Aquí más adelante se llamaría a los algoritmos y CSVWriter
    return 0;
}
```

---

## **6. src/Utils/Parametros.h**

```cpp
#ifndef PARAMETROS_H
#define PARAMETROS_H

#include <string>

struct Parametros {
    std::string input;
    std::string output;
    std::string algoritmo;
    std::string origen;
    std::string destino;
    bool help = false;
};

#endif // PARAMETROS_H
```

---

## **7. src/Utils/ParserArgs.h**

```cpp
#ifndef PARSERARGS_H
#define PARSERARGS_H

#include "Parametros.h"

class ParserArgs {
public:
    Parametros parsear(int argc, char* argv[]);
    void mostrarAyuda();
};

#endif // PARSERARGS_H
```

---

## **8. src/Utils/ParserArgs.cpp**

```cpp
#include "ParserArgs.h"
#include <iostream>
#include <string>

Parametros ParserArgs::parsear(int argc, char* argv[]) {
    Parametros params;

    if (argc < 3) {
        params.help = true;
        return params;
    }

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--help") {
            params.help = true;
        } else if (params.input.empty()) {
            params.input = arg;
        } else if (params.output.empty()) {
            params.output = arg;
        } else if (arg == "--algoritmo" && i + 1 < argc) {
            params.algoritmo = argv[++i];
        } else if (arg == "--origen" && i + 1 < argc) {
            params.origen = argv[++i];
        } else if (arg == "--destino" && i + 1 < argc) {
            params.destino = argv[++i];
        }
    }

    return params;
}

void ParserArgs::mostrarAyuda() {
    std::cout << "Uso: beeline <input.csv> <output.csv> --algoritmo <dijkstra|kruskal> --origen <nodo> [--destino <nodo>] [--help]\n";
}
```

---

✅ **Resultado esperado al ejecutar HU1:**

```bash
$ ./beeline data/input.csv data/output.csv --algoritmo dijkstra --origen A
Input file: data/input.csv
Output file: data/output.csv
Algorithm: dijkstra
Origin node: A
BeeLine ready to run!
```

Si se pasan parámetros inválidos o `--help`, mostrará la guía de uso.

# Compilación
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

Si quieres, puedo también añadir **Google Test** al CMake para que la carpeta `tests/` se compile con un comando `make test`.
¿Quieres que lo deje listo para TDD también?

# Pruebas

## 1️⃣ ¿Qué probar en HU1?

La HU1 se centra en **ejecución desde terminal y parseo de parámetros**. Por tanto, los tests pueden enfocarse en:

1. **Parser de argumentos (`ParserArgs`)**

   * Detecta correctamente input/output.
   * Detecta correctamente algoritmo, origen y destino.
   * Detecta `--help` aunque venga solo o con otros parámetros.
   * Comportamiento con parámetros incompletos o inválidos.

2. **Controlador (`Controlador`)**

   * Devuelve 0 si los parámetros son correctos.
   * Devuelve 1 si falta input/output.
   * Muestra ayuda si corresponde (`--help` o parámetros inválidos).

> En esta HU **no probamos algoritmos ni CSV**, solo que el flujo de ejecución y validación de parámetros funciona.

---

## 2️⃣ Estructura de tests

Crea en tu carpeta `tests/` un archivo `test_parser.cpp`:

```cpp
#include <gtest/gtest.h>
#include "Utils/ParserArgs.h"

TEST(ParserArgsTest, DetectaInputOutput) {
    char* argv[] = { (char*)"beeline", (char*)"in.csv", (char*)"out.csv" };
    ParserArgs parser;
    Parametros params = parser.parsear(3, argv);
    EXPECT_EQ(params.input, "in.csv");
    EXPECT_EQ(params.output, "out.csv");
    EXPECT_FALSE(params.help);
}

TEST(ParserArgsTest, DetectaAlgoritmoYOrigen) {
    char* argv[] = { (char*)"beeline", (char*)"in.csv", (char*)"out.csv", (char*)"--algoritmo", (char*)"dijkstra", (char*)"--origen", (char*)"A" };
    ParserArgs parser;
    Parametros params = parser.parsear(7, argv);
    EXPECT_EQ(params.algoritmo, "dijkstra");
    EXPECT_EQ(params.origen, "A");
}

TEST(ParserArgsTest, DetectaHelp) {
    char* argv[] = { (char*)"beeline", (char*)"--help" };
    ParserArgs parser;
    Parametros params = parser.parsear(2, argv);
    EXPECT_TRUE(params.help);
}

TEST(ParserArgsTest, ParametrosIncompletos) {
    char* argv[] = { (char*)"beeline", (char*)"in.csv" };
    ParserArgs parser;
    Parametros params = parser.parsear(2, argv);
    EXPECT_TRUE(params.help); // Debe mostrar ayuda si falta output
}
```

---

## 3️⃣ Configuración de CMake para tests

En tu `CMakeLists.txt` agrega al final:

```cmake
# -------------------------
# Tests con Google Test
# -------------------------
enable_testing()

# Descarga e incluye Google Test automáticamente
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(tests
    tests/test_parser.cpp
)

target_link_libraries(tests gtest_main)

target_include_directories(tests PRIVATE
    ${SRC_DIR}
)

include(GoogleTest)
gtest_discover_tests(tests)
```

Luego en terminal:

```bash
cd build
cmake ..
make
ctest --output-on-failure
```

---

✅ Con esto:

* Probamos que el parser de argumentos funciona correctamente.
* Podemos agregar más tests fácilmente cuando implementemos CSVReader, Grafo, algoritmos, etc.
* Mantienes tu HU1 validada antes de avanzar a HU2.

---

Si quieres, puedo armar un **esqueleto de tests también para `Controlador`**, simulando llamadas con parámetros y verificando códigos de retorno y mensajes de ayuda.

¿Quieres que haga eso?

---

¡Ah! Este error ya es bastante claro y muy común al usar Google Test:

```
undefined reference to `ParserArgs::parsear(int, char**)'
```

Eso significa que **el compilador encuentra la declaración de la clase `ParserArgs`**, pero al momento de **enlazar (link)** no puede encontrar la implementación de `parsear(...)`. En otras palabras, **no estás compilando el archivo `ParserArgs.cpp` dentro del ejecutable de tests**.

---

### 1️⃣ Por qué pasa

En tu `CMakeLists.txt` tienes:

```cmake
add_executable(tests
    tests/test_parser.cpp
)
```

Pero **`tests` solo incluye tu archivo de test**, no los `.cpp` de tu código fuente (`src/Utils/ParserArgs.cpp`, etc.). Por eso, el linker falla cuando intenta usar funciones definidas allí.

---

### 2️⃣ Cómo solucionarlo

Debes **linkear los archivos `.cpp` de tu proyecto también al ejecutable de tests**. Tienes varias formas:

#### Opción A: Añadir los `.cpp` directamente

```cmake
add_executable(tests
    tests/test_parser.cpp
    ${SRC_DIR}/Utils/ParserArgs.cpp
    ${SRC_DIR}/Utils/Parametros.cpp
)
```

> Aquí agregamos los archivos que el test necesita. Para tests más grandes, puedes añadir todo `src/**/*.cpp` si quieres.

#### Opción B: Reutilizar los mismos archivos que `beeline`

Como ya tienes:

```cmake
file(GLOB_RECURSE SOURCES
    "${SRC_DIR}/*.cpp"
)
add_executable(beeline ${SOURCES})
```

Puedes hacer algo como:

```cmake
add_executable(tests
    tests/test_parser.cpp
    ${SOURCES}  # Incluye todos los cpp del proyecto
)
```

> Esto asegura que el ejecutable de tests pueda llamar cualquier función de tu proyecto.

---

### 3️⃣ Recomendación

* Para **proyectos grandes**, normalmente se crea una **librería estática** con tu código (`libBeeLine.a`) y luego el ejecutable principal y los tests simplemente linkean esa librería.
* Pero para **proyectos pequeños** como este, agregar `${SOURCES}` al ejecutable de tests es rápido y funciona perfecto.

---

### 4️⃣ Pasos después de arreglarlo

1. Modifica el `CMakeLists.txt` de tests como se indicó.
2. Borra `build/` y recompila todo:

```bash
rm -rf build
mkdir build
cd build
cmake ..
make
ctest --output-on-failure
```

Si todo va bien, ahora `ctest` debería **ejecutar los tests sin errores de linker**.

---

Si quieres, puedo escribir la **versión final de tu `CMakeLists.txt` lista para compilar `beeline` y los tests con Google Test sin errores**.

¿Quieres que haga eso?

---

¡Perfecto! 🎉

Ahora todo funciona correctamente:

* El ejecutable `beeline` se compiló sin errores.
* Los tests se compilaron y **todos pasaron**.
* `ctest` muestra que tus cuatro tests de `ParserArgs` fueron exitosos:

```
100% tests passed, 0 tests failed out of 4
```

Eso significa que tu **configuración de Google Test** y la vinculación con tus archivos `.cpp` ya está correcta. ✅

Si quieres, puedo ayudarte a **limpiar y optimizar tu `CMakeLists.txt`** para que los tests y el ejecutable principal compartan código sin duplicaciones y quede más profesional.

¿Quieres que haga eso?

