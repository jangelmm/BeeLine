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
