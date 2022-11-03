# glibrary

various utility libraries for gemc




## Build 

By default, cmake will try to use a local installation of the dependencies 
using the required environment below:


| [CLHEP](https://proj-clhep.web.cern.ch/proj-clhep/) | [XercesC](https://xerces.apache.org) | [Geant4](https://geant4.web.cern.ch) | [Cadmesh](https://github.com/christopherpoole/CADMesh) | [qt5](https://www.qt.io) |
|:---------------------------------------------------:|:------------------------------------:|:------------------------------------:|:------------------------------------------------------:|:------------------------:|
 

To configure cmake and compile the libraries using 12 cores:

`cmake -S . -B build`

`cmake --build build -j 12`

### CTests


To run the tests using 12 cores:

`ctest --test-dir build -j 12`





## Validation

The validation performed for the CLAS12 systems includes the following workflows

- Fetch and compile cadmesh and glibrary
- Compile gemc using the fetched glibrary
- Examples tests in sci-g


[![Compile GLibrary](https://github.com/gemc/glibrary/actions/workflows/build.yml/badge.svg)](https://github.com/gemc/glibrary/actions/workflows/build.yml)
[![Test SciG](https://github.com/gemc/glibrary/actions/workflows/testSciG.yml/badge.svg)](https://github.com/gemc/glibrary/actions/workflows/testSciG.yml)
[![Test CLAS12](https://github.com/gemc/glibrary/actions/workflows/testC12.yml/badge.svg)](https://github.com/gemc/glibrary/actions/workflows/testC12.yml)
