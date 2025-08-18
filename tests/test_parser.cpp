#include <gtest/gtest.h>
#include "Utils/ParserArgs.h"

TEST(ParserArgsTest, DetectaInputOutput) {
    char* argv[] = { (char*)"beeline", (char*)"in.csv", (char*)"out.csv" };
    ParserArgs parser;
    Parametros params = parser.parsear(3, argv);
    EXPECT_EQ(params.input, "in.csv");
    EXPECT_EQ(params.output, "out.csv");
    EXPECT_FALSE(params.help);
}

TEST(ParserArgsTest, DetectaAlgoritmoYOrigen) {
    char* argv[] = { (char*)"beeline", (char*)"in.csv", (char*)"out.csv", (char*)"--algoritmo", (char*)"dijkstra", (char*)"--origen", (char*)"A" };
    ParserArgs parser;
    Parametros params = parser.parsear(7, argv);
    EXPECT_EQ(params.algoritmo, "dijkstra");
    EXPECT_EQ(params.origen, "A");
}

TEST(ParserArgsTest, DetectaHelp) {
    char* argv[] = { (char*)"beeline", (char*)"--help" };
    ParserArgs parser;
    Parametros params = parser.parsear(2, argv);
    EXPECT_TRUE(params.help);
}

TEST(ParserArgsTest, ParametrosIncompletos) {
    char* argv[] = { (char*)"beeline", (char*)"in.csv" };
    ParserArgs parser;
    Parametros params = parser.parsear(2, argv);
    EXPECT_TRUE(params.help); // Debe mostrar ayuda si falta output
}
