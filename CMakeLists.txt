cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto y lenguaje
project(BeeLine LANGUAGES CXX)

# Estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Carpeta de código fuente
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

# Buscar todos los .cpp dentro de src y subcarpetas
file(GLOB_RECURSE SOURCES
    "${SRC_DIR}/*.cpp"
)

# Crear ejecutable
add_executable(beeline ${SOURCES})

# Incluir directorios de cabeceras
target_include_directories(beeline PRIVATE
    ${SRC_DIR}
    ${SRC_DIR}/Modelo
    ${SRC_DIR}/Algoritmos
    ${SRC_DIR}/IO
    ${SRC_DIR}/Vista
    ${SRC_DIR}/Utils
)

# Opcional: Warnings para desarrollo
target_compile_options(beeline PRIVATE -Wall -Wextra -pedantic)

# -------------------------
# Tests con Google Test
# -------------------------
enable_testing()

# Descarga e incluye Google Test automáticamente
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(tests
    tests/test_parser.cpp
    ${SRC_DIR}/Utils/ParserArgs.cpp
    ${SRC_DIR}/Utils/Parametros.cpp
)



target_link_libraries(tests gtest_main)

target_include_directories(tests PRIVATE
    ${SRC_DIR}
)

include(GoogleTest)
gtest_discover_tests(tests)
