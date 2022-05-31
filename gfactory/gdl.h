#ifndef  GDYNAMICLIB_H
#define  GDYNAMICLIB_H  1

// gutilities conventions
#include "gutsConventions.h"

// c++ plugin loading functions
#include <dlfcn.h>

// c++
#include <sys/stat.h> // to check if file exists
#include <string>
#include <iostream>

typedef void* dlhandle;

static dlhandle load_lib(const std::string& path);
static void close_lib(dlhandle handle);

#define DLLOGITEM  " ⁍"

// exit codes: 1000s
#define EC__DLNOTFOUND       1001
#define EC__FACTORYNOTFOUND  1002


/**
 * @struct DynamicLib
 * @brief  Structure to load dynamically symbols from a shared library
 */
struct DynamicLib {

private:
	std::string   dlFileName;  ///< dynamic library file
	int verbosity = 0;

	bool doesFileExists(const std::string& name) {
		struct stat buffer;
		return (stat (name.c_str(), &buffer) == 0);
	}


public:
	// default constructor
	DynamicLib() = default;
	dlhandle handle = nullptr;   ///< posix handle of the dynamic library

	DynamicLib(std::string path, int v = 0) : dlFileName(path), verbosity(v), handle(nullptr) {

		if(doesFileExists(dlFileName)) {
			if ( verbosity ) {
				std::cout << DLLOGITEM <<  " Loading Dynamic Library " << dlFileName << std::endl;
			}
			handle = load_lib(dlFileName);
			if(handle == nullptr) {
				std::cerr << FATALERRORL  << "File " << YELLOWHHL << dlFileName << RSTHHR "found, but could not be loaded" << std::endl;
				gexit(EC__DLNOTFOUND);
			}

		} else {
			std::cerr << FATALERRORL  << "couldn't load " << YELLOWHHL << dlFileName << RSTHHR  << std::endl;
			gexit(EC__DLNOTFOUND);
		}
	}

	~DynamicLib() {
		if (handle != nullptr) {
			close_lib(handle);
			if ( verbosity ) {
				std::cout << DLLOGITEM << " Closing DL " << dlFileName << std::endl;
			}
		}
	}


};


static dlhandle load_lib(const std::string& path) {

	return dlopen(path.data(), RTLD_NOW);
	// get a handle to the lib, may be nullptr.
	// RTLD_NOW ensures that all the symbols are resolved immediately:
	// if a symbol cannot be found, the program will crash now instead of later.
}

static void close_lib(dlhandle handle) {
	dlclose(handle);
}

#endif
