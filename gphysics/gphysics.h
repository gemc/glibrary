#ifndef  GPHYSICS_H
#define  GPHYSICS_H  1

// glibrary
#include "goptions.h"

// geant4
#include "G4VModularPhysicsList.hh"

class  GPhysics : public G4VModularPhysicsList
{
public:
	
	GPhysics(GOptions* gopts);
	~GPhysics();

private:
	// logs physics modules and constructors
	void printAvailable();

};


#endif
