#include "BeeLine.h"
#include "Controlador.h"

int BeeLine::run(int argc, char* argv[]) {
    Controlador controlador;
    return controlador.ejecutar(argc, argv);
}
