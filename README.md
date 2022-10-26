# glibrary

various utility libraries for gemc




## Build 

By default cmake will try to use a local installation of the dependencies
(turn off by adding `-DUSE_LOCAL_INSTALL=OFF`) using the required environment below:


| Library | List of required environment variables |                Other Assumptions                |
|:-------:|:--------------------------------------:|:-----------------------------------------------:|
|  CLHEP  |               CLHEP_DIR                |                                                 | 
| XercesC |              XERCESCROOT               | XercesC version is the last dir in $XERCESCROOT | 
| Geant4  |               CLHEP_DIR                |                                                 | 
| cadmesh |               CLHEP_DIR                |                                                 | 
|   qt5   |               CLHEP_DIR                |                                                 | 



To configure cmake and compile the libraries using 12 cores:

`cmake -S . -B build`

`cmake --build build -j 12`




## Validation

The validation performed for the CLAS12 systems includes the following workflows

- Fetch and compile cadmesh and glibrary
- Compile gemc using the fetched glibrary
- Examples tests in sci-g


[![Compile GLibrary](https://github.com/gemc/glibrary/actions/workflows/build.yml/badge.svg)](https://github.com/gemc/glibrary/actions/workflows/build.yml)
[![Test SciG](https://github.com/gemc/glibrary/actions/workflows/testSciG.yml/badge.svg)](https://github.com/gemc/glibrary/actions/workflows/testSciG.yml)
[![Test CLAS12](https://github.com/gemc/glibrary/actions/workflows/testC12.yml/badge.svg)](https://github.com/gemc/glibrary/actions/workflows/testC12.yml)
