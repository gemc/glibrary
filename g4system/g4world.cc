// glibrary
#include "gfactory.h"

// g4system
#include "g4world.h"
#include "g4systemFactories/g4systemFactory.h"
#include "g4systemFactories/g4native/g4NativeSystemFactory.h"
#include "g4systemFactories/cad/cadSystemFactory.h"



G4World::G4World(GWorld *gworld, GOptions* opt) {

	// instantiating gSystemManager
	int verbosity = opt->getInt("g4systemv");
	GManager g4SystemManager("G4World", verbosity);

	map<string, G4SystemFactory*> g4systemFactory;

	// registering factories in the manager
	// and adding them to g4systemFactory
	for(auto &s : gworld->getSystemsMap()) {
		string factory = s.second->getFactory();

		// text
		// ----
		if(factory == "text") {
			// if factory not found, registering it in the manager and loading it into the map
			if(g4systemFactory.find(factory) == g4systemFactory.end()) {
				g4SystemManager.RegisterObjectFactory<G4NativeSystemFactory>("G4NativeSystemFactory");
				g4systemFactory[factory] = g4SystemManager.CreateObject<G4SystemFactory>("G4NativeSystemFactory");
			}
		} else if(factory == "cad") {
			// if factory not found, registering it in the manager and loading it into the map
			if(g4systemFactory.find(factory) == g4systemFactory.end()) {
				g4SystemManager.RegisterObjectFactory<G4CadSystemFactory>("G4CadSystemFactory");
				g4systemFactory[factory] = g4SystemManager.CreateObject<G4SystemFactory>("G4CadSystemFactory");
			}
		}
	}

	g4SystemManager.clearDLMap();

	// build root volume first
	// buildRootVolume(gworld, verbosity);

	// now building geant4 objects
	// every volume that is not built (due to dependencies) increments remainingVolumes
	int thisIterationRemainingVolumes;
	int allRemainingVolumes = 0;
	do {
		thisIterationRemainingVolumes = 0;
		// looping over system in the gsystemsMap
		for(auto &system : gworld->getSystemsMap()) {
			string systemName = system.first;
			string factory = system.second->getFactory();
			// looping over v = gvolumes in that system
			for(auto &gvolume : *system.second->getGVolumesMap()) {
				if(g4systemFactory.find(factory) != g4systemFactory.end()) {

					// getting or instantiating a new g4system, and getting its g4volumesMap
					auto g4volumesMapForThisSystem = getOrCreateG4System(systemName, factory, verbosity)->getg4volumesMap();

					// calling loadG4System
					// if a new cannot be loaded, false is returned and thisIterationRemainingVolumes increases by 1
					if(g4systemFactory[factory]->loadG4System(opt, gvolume.second, g4volumesMapForThisSystem) == false) {
						thisIterationRemainingVolumes += 1;
					}
				} else {
					cerr << FATALERRORL << "g4setupactory factory <" << factory << "> not found." << endl;
					exit(0);
				}
			}
			if(verbosity == GVERBOSITY_SUMMARY) {
				cout << G4SYSTEMLOGHEADER << " " << system.first << " remaining g4volumes to be built: " << thisIterationRemainingVolumes << endl;
			}
		}
		if(allRemainingVolumes != 0 && thisIterationRemainingVolumes != 0) {
			if(allRemainingVolumes >= thisIterationRemainingVolumes) {
				cerr << FATALERRORL << "dependencies are not being resolved: their number should diminish." << endl;
				gexit(EC__DEPENDENCIESNOTSOLVED);
			}
		} else {
			allRemainingVolumes = thisIterationRemainingVolumes;
		}
	} while (thisIterationRemainingVolumes > 0);


}


// return system pointer if exist, otherwise create a new one, add it to the map
// then return that one.
G4System* G4World::getOrCreateG4System(string sname, string factory, int verbosity) {

	// check if g4s already exists
	if(g4systemsMap.find(sname) != g4systemsMap.end()) {
		return g4systemsMap[sname];
	} else {
		// adding volume to the map
		g4systemsMap[sname] = new G4System(sname, factory, verbosity);
		return g4systemsMap[sname];
	}

}
