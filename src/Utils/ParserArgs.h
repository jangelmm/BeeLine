#ifndef PARSERARGS_H
#define PARSERARGS_H

#include "Parametros.h"

class ParserArgs {
public:
    Parametros parsear(int argc, char* argv[]);
    void mostrarAyuda();
};

#endif // PARSERARGS_H
