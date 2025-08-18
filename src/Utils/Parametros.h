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
