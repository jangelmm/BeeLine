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