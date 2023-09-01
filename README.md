# glibrary

various utility libraries for gemc

### CMake


## Dependencies

By default, cmake will try to use a local installation of these dependencies:

| [CLHEP](https://proj-clhep.web.cern.ch/proj-clhep/) | [XercesC](https://xerces.apache.org) | [Geant4](https://geant4.web.cern.ch) | [Cadmesh](https://github.com/christopherpoole/CADMesh) | [qt5](https://www.qt.io) |
|:---------------------------------------------------:|:------------------------------------:|:------------------------------------:|:------------------------------------------------------:|:------------------------:|

If a dependency is not found cmake will try to build it.

## Build Glibrary

To configure cmake and compile the libraries using 12 cores:

```
cmake -S . -B build
cmake --build build -j 12 --target install
```

### Options:

Add the `-L` option to list all the available options:

```
PRINT_ALL_VARS:BOOL=OFF
RUN_TESTS:BOOL=OFF
```

### CTests

To run the tests using 12 cores:

`ctest --test-dir build -j 12`

## Clion setup

Loaded from ~/clion.setup, created by:

```
export -p > ~/clion.setup
```


## Validation

The validation performed for the CLAS12 systems includes the following workflows

- Fetch and compile cadmesh and glibrary
- Compile gemc using the fetched glibrary
- Examples tests in sci-g




## Modern CMake Resources
- [Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
- [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)




[![Compile GLibrary](https://github.com/gemc/glibrary/actions/workflows/build.yml/badge.svg)](https://github.com/gemc/glibrary/actions/workflows/build.yml)
[![Test SciG](https://github.com/gemc/glibrary/actions/workflows/testSciG.yml/badge.svg)](https://github.com/gemc/glibrary/actions/workflows/testSciG.yml)
[![Test CLAS12](https://github.com/gemc/glibrary/actions/workflows/testC12.yml/badge.svg)](https://github.com/gemc/glibrary/actions/workflows/testC12.yml)
