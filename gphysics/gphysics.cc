// gphysics 
#include "gphysics.h"
#include "gphysicsConventions.h"



// geant4

// From examples/extended/physicslists/extensibleFactory:
// The extensible factory also allows for the extension of lists by adding
// (using "+" as a separator) or replacing (using "_" as a separator)
// specific physics constructors.  These can be specified by
// pre-defining a short name (e.g. RADIO for G4RadioactiveDecayPhysics) or
// providing the full class name.
#include "G4PhysListFactoryAlt.hh"

// allow ourselves to extend the short names for physics ctor addition/replace
// along the same lines as EMX, EMY, etc
#include "G4PhysListRegistry.hh"

// allow ourselves to give the user extra info about available physics constructors (ctors)
#include "G4PhysicsConstructorFactory.hh"


GPhysics::GPhysics(GOptions* opt) : G4VModularPhysicsList() {
	
	G4cout << GPHYSLOGHEADER << " Constructor " << G4endl;

	int verbosity = opt->getInt(GPHYSVERBOSITY);

	printAvailable(verbosity);
	
}

GPhysics::~GPhysics() {}


// calls PrintAvailablePhysLists
// if verbosity is > 0 calls PrintAvailablePhysicsConstructors
void GPhysics::printAvailable(int verbosity) {
	
	G4cout << GPHYSLOGHEADER << " Geant4 Available Modules: " << G4endl;

	g4alt::G4PhysListFactory factory;
	factory.PrintAvailablePhysLists();
	
}



