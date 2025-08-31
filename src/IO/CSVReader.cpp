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