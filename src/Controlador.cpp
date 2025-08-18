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
