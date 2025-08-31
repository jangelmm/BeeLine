#include <gtest/gtest.h>
#include "../src/IO/CSVReader.h"
#include "../src/Modelo/Grafo.h"


TEST(CSVReaderTest, LeeCSVValido) {
    Grafo grafo;
    bool resultado = CSVReader::leerCSV("../data/test_valido.csv", grafo);
    
    EXPECT_TRUE(resultado);
    EXPECT_EQ(grafo.obtenerNodos().size(), 3);
    EXPECT_EQ(grafo.obtenerAristas().size(), 3);
}

TEST(CSVReaderTest, ManejaCSVInvalido) {
    Grafo grafo;
    bool resultado = CSVReader::leerCSV("../data/test_invalido.csv", grafo);
    
    // Debería fallar silenciosamente pero continuar
    EXPECT_TRUE(resultado);
}

TEST(CSVReaderTest, SoportaDiferentesSeparadores) {
    Grafo grafo;
    bool resultado = CSVReader::leerCSV("../data/test_semicolon.csv", grafo);
    
    EXPECT_TRUE(resultado);
    EXPECT_GT(grafo.obtenerAristas().size(), 0);
}