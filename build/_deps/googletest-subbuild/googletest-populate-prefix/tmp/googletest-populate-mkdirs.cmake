# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/media/Files/Documentos/Proyectos/BeeLine/build/_deps/googletest-src"
  "/media/Files/Documentos/Proyectos/BeeLine/build/_deps/googletest-build"
  "/media/Files/Documentos/Proyectos/BeeLine/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "/media/Files/Documentos/Proyectos/BeeLine/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/media/Files/Documentos/Proyectos/BeeLine/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/media/Files/Documentos/Proyectos/BeeLine/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/media/Files/Documentos/Proyectos/BeeLine/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/media/Files/Documentos/Proyectos/BeeLine/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/media/Files/Documentos/Proyectos/BeeLine/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
