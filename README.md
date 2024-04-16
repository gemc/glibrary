# glibrary

various utility libraries for gemc

## Meson Installation

```
meson setup build --native-file=release.ini
cd build
meson configure -Dprefix=$GLIBRARY
meson install
```


## Meson utilities


```
meson setup build --native-file=release.ini --wipe
meson compile 
meson compile -v 
meson compile  --clean
meson test 
meson test -v
```


## Dependencies

Meson will try to use a local installation of these dependencies:

|  [CLHEP](https://proj-clhep.web.cern.ch)   | [XercesC](https://xerces.apache.org) | [Geant4](https://geant4.org) | [Cadmesh](https://github.com/christopherpoole/CADMesh) | [qt5](https://www.qt.io) |
|:------------------------------------------:|:------------------------------------:|:----------------------------:|:------------------------------------------------------:|:------------------------:|



## Validation

The validation performed for the CLAS12 systems includes the following workflows

- Fetch and compile cadmesh and glibrary
- Compile gemc using the fetched glibrary
- Examples tests in sci-g




## Meson Resources
- [The Meson Build system](https://mesonbuild.com/index.html)




[![Compile GLibrary](https://github.com/gemc/glibrary/actions/workflows/build.yml/badge.svg)](https://github.com/gemc/glibrary/actions/workflows/build.yml)
[![Test SciG](https://github.com/gemc/glibrary/actions/workflows/testSciG.yml/badge.svg)](https://github.com/gemc/glibrary/actions/workflows/testSciG.yml)
[![Test CLAS12](https://github.com/gemc/glibrary/actions/workflows/testC12.yml/badge.svg)](https://github.com/gemc/glibrary/actions/workflows/testC12.yml)
