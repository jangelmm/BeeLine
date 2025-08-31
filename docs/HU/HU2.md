## HU2

1. Crear `CSVReader` para leer archivos CSV
2. Implementar validación de formato y datos
3. Integrar con el `Controlador`
4. Crear pruebas unitarias

---

### 1. Primero, crea los archivos para CSVReader:

**src/IO/CSVReader.h**
```cpp
#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <vector>
#include "../Modelo/Grafo.h"


class CSVReader {
public:
    static bool leerCSV(const std::string& filename, Grafo& grafo);
    
private:
    static bool validarLinea(const std::vector<std::string>& campos);
    static double convertirPeso(const std::string& strPeso);
};

#endif // CSVREADER_H
```

**src/IO/CSVReader.cpp**
```cpp

#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

bool CSVReader::leerCSV(const string& filename, Grafo& grafo) {
    ifstream archivo(filename);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << filename << endl;
        return false;
    }

    string linea;
    int numLinea = 0;
    bool tieneEncabezados = false;

    while (getline(archivo, linea)) {
        numLinea++;
        
        // Saltar líneas vacías
        if (linea.empty()) continue;

        // Reemplazar ; por , para soportar ambos separadores
        replace(linea.begin(), linea.end(), ';', ',');
        
        vector<string> campos;
        stringstream ss(linea);
        string campo;

        while (getline(ss, campo, ',')) {
            // Eliminar espacios en blanco
            campo.erase(remove_if(campo.begin(), campo.end(), ::isspace), campo.end());
            if (!campo.empty()) {
                campos.push_back(campo);
            }
        }

        // Saltar encabezados si existen
        if (numLinea == 1 && campos.size() >= 3) {
            if (campos[0] == "origen" && campos[1] == "destino" && campos[2] == "peso") {
                tieneEncabezados = true;
                continue;
            }
        }

        if (!validarLinea(campos)) {
            cerr << "Error en línea " << numLinea << ": Formato inválido" << endl;
            continue;
        }

        string origen = campos[0];
        string destino = campos[1];
        double peso = convertirPeso(campos[2]);

        if (peso < 0) {
            cerr << "Error en línea " << numLinea << ": Peso negativo no permitido" << endl;
            continue;
        }

        // Agregar nodos y arista al grafo
        grafo.agregarNodo(origen);
        grafo.agregarNodo(destino);
        grafo.agregarArista(origen, destino, peso);
    }

    archivo.close();
    return true;
}

bool CSVReader::validarLinea(const vector<string>& campos) {
    if (campos.size() != 3) {
        return false;
    }
    return true;
}

double CSVReader::convertirPeso(const string& strPeso) {
    try {
        return stod(strPeso);
    } catch (const exception&) {
        cerr << "Error: Peso no numérico - " << strPeso << endl;
        return -1;
    }
}

```

---

### 2. Ahora actualiza el Grafo para soportar nodos y aristas:

**src/Modelo/Grafo.h**
```cpp
#ifndef GRAFO_H
#define GRAFO_H

#include <string>
#include <vector>
#include <map>
#include "Arista.h"

class Grafo {
public:
    void agregarNodo(const std::string& id);
    void agregarArista(const std::string& origen, const std::string& destino, double peso);
    const std::vector<Arista>& obtenerAristas() const;
    const std::vector<std::string>& obtenerNodos() const;
    
private:
    std::vector<std::string> nodos;
    std::vector<Arista> aristas;
    std::map<std::string, int> indicesNodos;
};

#endif // GRAFO_H
```

**src/Modelo/Grafo.cpp**
```cpp
#include "Grafo.h"
#include <string>

void Grafo::agregarNodo(const std::string& id) {
    if (indicesNodos.find(id) == indicesNodos.end()) {
        indicesNodos[id] = nodos.size();
        nodos.push_back(id);
    }
}
void Grafo::agregarArista(const std::string& origen, const std::string& destino, double peso) {
    aristas.push_back({origen, destino, peso});
}

const std::vector<Arista>& Grafo::obtenerAristas() const {
    return aristas;
}

const std::vector<std::string>& Grafo::obtenerNodos() const {
    return nodos;
}   
```

**src/Modelo/Arista.h** (nuevo archivo)
```cpp
#ifndef ARISTA_H
#define ARISTA_H

#include <string>

struct Arista {
    std::string origen;
    std::string destino;
    double peso;
};

#endif // ARISTA_H
```

---

### 3. Actualiza el Controlador para usar CSVReader:

**src/Controlador.cpp**
```cpp
#include "Controlador.h"
#include "IO/CSVReader.h"
#include <iostream>

int Controlador::ejecutar(int argc, char* argv[]) {
    ParserArgs parser;
    Parametros params = parser.parsear(argc, argv);

    if (params.help) {
        parser.mostrarAyuda();
        return 0;
    }

    if (params.input.empty() || params.output.empty()) {
        std::cerr << "Error: Debe especificar archivo de entrada y salida.\n";
        parser.mostrarAyuda();
        return 1;
    }

    // Crear grafo y leer CSV
    Grafo grafo;
    if (!CSVReader::leerCSV(params.input, grafo)) {
        std::cerr << "Error al leer el archivo CSV.\n";
        return 1;
    }

    std::cout << "Grafo cargado con " << grafo.obtenerNodos().size() 
              << " nodos y " << grafo.obtenerAristas().size() 
              << " aristas.\n";

    // Aquí más adelante se llamaría a los algoritmos
    return 0;
}
```

---

### 4. Crea pruebas unitarias para CSVReader:

**tests/test_csv.cpp**
```cpp
#include <gtest/gtest.h>
#include "../src/IO/CSVReader.h"
#include "../src/Modelo/Grafo.h"


TEST(CSVReaderTest, LeeCSVValido) {
    Grafo grafo;
    bool resultado = CSVReader::leerCSV("../data/test_valido.csv", grafo);
    
    EXPECT_TRUE(resultado);
    EXPECT_EQ(grafo.obtenerNodos().size(), 3);
    EXPECT_EQ(grafo.obtenerAristas().size(), 3);
}

TEST(CSVReaderTest, ManejaCSVInvalido) {
    Grafo grafo;
    bool resultado = CSVReader::leerCSV("../data/test_invalido.csv", grafo);
    
    // Debería fallar silenciosamente pero continuar
    EXPECT_TRUE(resultado);
}

TEST(CSVReaderTest, SoportaDiferentesSeparadores) {
    Grafo grafo;
    bool resultado = CSVReader::leerCSV("../data/test_semicolon.csv", grafo);
    
    EXPECT_TRUE(resultado);
    EXPECT_GT(grafo.obtenerAristas().size(), 0);
}
```

---

### 5. Crea archivos de prueba en `data/`:

**data/test_valido.csv**
```csv
origen,destino,peso
A,B,5
B,C,3
A,C,10
```

**data/test_invalido.csv**
```csv
origen,destino,peso
A,B,cinco  # Peso no numérico
C,D        # Faltan campos
E,F,7      # Esta línea sí es válida
```

**data/test_semicolon.csv**
```csv
origen;destino;peso
A;B;5
B;C;3
```

---

### 6. Actualiza CMakeLists.txt para incluir los nuevos archivos:

```cmake
# Asegúrate de que todos los archivos .cpp estén incluidos
file(GLOB_RECURSE SOURCES
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/Modelo/*.cpp"
    "${SRC_DIR}/IO/*.cpp"
    "${SRC_DIR}/Utils/*.cpp"
)

# ... resto del CMakeLists.txt existente ...
```

---

### 7. Ejecuta las pruebas:

```bash
rm -rf build
cd build
cmake ..
make
./beeline data/test_valido.csv output.csv --algoritmo dijkstra --origen A
```

Deberías ver:
```
Grafo cargado con 3 nodos y 3 aristas.
```

Para ejecutar las pruebas:
```bash
ctest --output-on-failure
```

---

```
🐧 angel 10:16:50 PM 08/30/25   2-hu2-lectura-de-csv U:36 ?:8  /media/Files/Documentos/Proyectos/BeeLine  ✅  rm -rf build/
 🐧 angel 10:36:05 PM 08/30/25   2-hu2-lectura-de-csv U:445 ?:5  /media/Files/Documentos/Proyectos/BeeLine  ✅  mkdir build
mkdir: created directory 'build'
 🐧 angel 10:36:10 PM 08/30/25   2-hu2-lectura-de-csv U:445 ?:5  /media/Files/Documentos/Proyectos/BeeLine  ✅  cd build/
/media/Files/Documentos/Proyectos/BeeLine/build
 🐧 angel 10:36:14 PM 08/30/25   2-hu2-lectura-de-csv U:445 ?:5  /media/Files/Documentos/Proyectos/BeeLine/build  ✅  cmake ..
-- The CXX compiler identification is GNU 13.3.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
CMake Warning (dev) at /usr/share/cmake-3.28/Modules/FetchContent.cmake:1331 (message):
  The DOWNLOAD_EXTRACT_TIMESTAMP option was not given and policy CMP0135 is
  not set.  The policy's OLD behavior will be used.  When using a URL
  download, the timestamps of extracted files should preferably be that of
  the time of extraction, otherwise code that depends on the extracted
  contents might not be rebuilt if the URL changes.  The OLD behavior
  preserves the timestamps from the archive instead, but this is usually not
  what you want.  Update your project to the NEW behavior or specify the
  DOWNLOAD_EXTRACT_TIMESTAMP option with a value of true to avoid this
  robustness issue.
Call Stack (most recent call first):
  CMakeLists.txt:41 (FetchContent_Declare)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- The C compiler identification is GNU 13.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE  
-- Configuring done (5.8s)
-- Generating done (0.1s)
-- Build files have been written to: /media/Files/Documentos/Proyectos/BeeLine/build
 🐧 angel 10:36:28 PM 08/30/25   2-hu2-lectura-de-csv U:63 ?:5  /media/Files/Documentos/Proyectos/BeeLine/build  ✅  make
[  3%] Building CXX object CMakeFiles/beeline.dir/src/Algoritmos/Dijkstra.cpp.o
[  7%] Building CXX object CMakeFiles/beeline.dir/src/Algoritmos/Kruskal.cpp.o
[ 11%] Building CXX object CMakeFiles/beeline.dir/src/BeeLine.cpp.o
[ 15%] Building CXX object CMakeFiles/beeline.dir/src/Controlador.cpp.o
[ 19%] Building CXX object CMakeFiles/beeline.dir/src/IO/CSVReader.cpp.o
/media/Files/Documentos/Proyectos/BeeLine/src/IO/CSVReader.cpp: In static member function ‘static bool CSVReader::leerCSV(const std::string&, Grafo&)’:
/media/Files/Documentos/Proyectos/BeeLine/src/IO/CSVReader.cpp:19:10: warning: variable ‘tieneEncabezados’ set but not used [-Wunused-but-set-variable]
   19 |     bool tieneEncabezados = false;
      |          ^~~~~~~~~~~~~~~~
[ 23%] Building CXX object CMakeFiles/beeline.dir/src/IO/CSVWriter.cpp.o
[ 26%] Building CXX object CMakeFiles/beeline.dir/src/Modelo/Grafo.cpp.o
[ 30%] Building CXX object CMakeFiles/beeline.dir/src/Modelo/Nodo.cpp.o
[ 34%] Building CXX object CMakeFiles/beeline.dir/src/Modelo/Resultado.cpp.o
[ 38%] Building CXX object CMakeFiles/beeline.dir/src/Utils/Parametros.cpp.o
[ 42%] Building CXX object CMakeFiles/beeline.dir/src/Utils/ParserArgs.cpp.o
[ 46%] Building CXX object CMakeFiles/beeline.dir/src/Vista/VistaCLI.cpp.o
[ 50%] Building CXX object CMakeFiles/beeline.dir/src/main.cpp.o
[ 53%] Linking CXX executable beeline
[ 53%] Built target beeline
[ 57%] Building CXX object _deps/googletest-build/googletest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
[ 61%] Linking CXX static library ../../../lib/libgtest.a
[ 61%] Built target gtest
[ 65%] Building CXX object _deps/googletest-build/googletest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
[ 69%] Linking CXX static library ../../../lib/libgtest_main.a
[ 69%] Built target gtest_main
[ 73%] Building CXX object CMakeFiles/tests.dir/tests/test_parser.cpp.o
[ 76%] Building CXX object CMakeFiles/tests.dir/src/Utils/ParserArgs.cpp.o
[ 80%] Building CXX object CMakeFiles/tests.dir/src/Utils/Parametros.cpp.o
[ 84%] Linking CXX executable tests
[ 84%] Built target tests
[ 88%] Building CXX object _deps/googletest-build/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
[ 92%] Linking CXX static library ../../../lib/libgmock.a
[ 92%] Built target gmock
[ 96%] Building CXX object _deps/googletest-build/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
[100%] Linking CXX static library ../../../lib/libgmock_main.a
[100%] Built target gmock_main
 🐧 angel 10:36:51 PM 08/30/25   2-hu2-lectura-de-csv U:23 ?:5  /media/Files/Documentos/Proyectos/BeeLine/build  ✅  ./beeline data/test_valido.csv output.csv --algoritmo dijkstra --origen A
Error: No se pudo abrir el archivo data/test_valido.csv
Error al leer el archivo CSV.
 🐧 angel 10:37:08 PM 08/30/25   2-hu2-lectura-de-csv U:23 ?:5  /media/Files/Documentos/Proyectos/BeeLine/build  ❌1  ./beeline ../data/test_valido.csv output.csv --algoritmo dijkstra --origen 
A
Grafo cargado con 3 nodos y 3 aristas.
```
