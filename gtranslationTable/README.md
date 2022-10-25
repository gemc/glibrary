# gtranslationTable






## CMake

By default cmake will try to use a local installation of the dependencies.
This can be turned off with the cmake configuration option `-DUSE_LOCAL_INSTALL=OFF`.

To configure cmake and compile the libraries using 12 cores:

`cmake -S . -B build`

`cmake --build build -j 12`



