# glibrary

various utility libraries for gemc




## Build 

By default, cmake will try to use a local installation of the dependencies 
using the required environment below:


| Library | List of required environment variables |                     Assumptions                      |
|:-------:|:--------------------------------------:|:----------------------------------------------------:|
|  CLHEP  |               CLHEP_DIR                |                                                      | 
| XercesC |              XERCESCROOT               | Version (i.e. 3.2.3) is the last dir in $XERCESCROOT | 
| Geant4  |               CLHEP_DIR                |                                                      | 
| cadmesh |               CLHEP_DIR                |                                                      | 
|   qt5   |               CLHEP_DIR                |                                                      | 

(turn off by adding `-DUSE_LOCAL_INSTALL=OFF`)

To configure cmake and compile the libraries using 12 cores:

`cmake -S . -B build`

`cmake --build build -j 12`

### CTests

If some dependencies are not found, the corresponding tests will be disabled - re-run cmake to enable them.

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
