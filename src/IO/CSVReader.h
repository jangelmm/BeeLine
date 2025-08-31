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