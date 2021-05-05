#ifndef  GSYSTEM_H
#define  GSYSTEM_H 1


// gvolume
#include "gvolume.h"

// glibrary
//#include "goptions.h"
//#include "gfactory.h"

#define GSETUPLOGHEADER " ⎚ gvolume ▸"
#define GWORLDNAME     "world"

// c++
#include <map>
#include "dirent.h" // for directory access to DIR object
using std::ifstream;
using std::map;

class GSystem
{
	
public:
	// constructor, from command line or jcard
	GSystem(string n, string f, string v, int r, int dr, int verbosity);

private:
	string      name;               // System name, with path to it
	string   factory;               // Factory that builds the detector
	string variation = "default";   // Variation of the detector. Default is "default"
	int    runNumber = 1;           // Run Number selected for this detector. Default is 1

	// map containing the volumes
	// the key is system + volume name;
	// the names must be unique in each system
	// each system name must be unique
	map<string, GVolume*> gvolumesMap;

	string formVolumeKey(string detectorName) {
		return name + detectorName;
	}



public:
//	string getFactory() const { return factory; }
//	string getName() const    { return name; }
	
	// returns the file stream, checking all possible directories.
	// this should be in some general utility library? gstrings?
	//ifstream* gSystemFile(int which, vector<string> locations, int verbosity);  // 0: material. 1: geometry
	
	// returns a vector of import files, checking all possible directories.
	// this should be in some general utility library? gstrings?
	// vector<string> gImportFiles(vector<string> locations, int verbosity, vector<string> possibleExtensions);

	// load all names in the directory matching extension
	// this should be in some general utility library? gstrings?
	// vector<string> loadImportFilesInDir(string path, DIR* directory, vector<string> withExtension);


	void addGVolume(vector<string> pars, int verbosity);
	// void addGImportedVolume(string importType, string filename, int verbosity);

	// need to filter system name from key
	GVolume* getGVolume(string detectorName) {

		string key = formVolumeKey(detectorName);

		if(gvolumesMap.find(key) != gvolumesMap.end()) {
			return gvolumesMap[key];
		} else {
			return nullptr;
		}
	}
	
	map<string, GVolume*> getGVolumesMap() const {return gvolumesMap;}

//	vector<string> getAllVolumeNames() const;
//	string getSystemPath();
	
};



#endif
