cmake_minimum_required(VERSION 3.16...3.27)

project(glibrary VERSION 1.0
        DESCRIPTION "A set of c++ libraries for general use"
        LANGUAGES CXX)

### add glibrary, check for dependencies
include("${PROJECT_SOURCE_DIR}/cmake/glibrary.cmake")
check_glibrary_dependency("CLHEP;XercesC;Geant4") # XercesC is set in geant4 cmakefiles

### add glibraries
set(GLIBRARIES "guts;goptions;gtouchable;gtranslationTable")

foreach (GLIBRARY IN LISTS GLIBRARIES)
    add_subdirectory(${GLIBRARY})
endforeach()
message("")
