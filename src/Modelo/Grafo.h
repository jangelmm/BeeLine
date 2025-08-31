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