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