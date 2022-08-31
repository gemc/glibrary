#ifndef  GPHYSICS_H
#define  GPHYSICS_H  1

// glibrary
#include "goptions.h"

// geant4
#include "G4VModularPhysicsList.hh"

class  GPhysics : public G4VModularPhysicsList
{
public:
	
	GPhysics(GOptions* opt);
	~GPhysics();

private:
	// calls PrintAvailablePhysLists
	// if verbosity is > 0 calls PrintAvailablePhysicsConstructors
	void printAvailable(int verbosity);

};


#endif
