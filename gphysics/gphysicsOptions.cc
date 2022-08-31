// gphysics
#include "gphysicsConventions.h"
#include "gphysicsOptions.h"

// namespace to define options
namespace gphysics {

// returns array of options definitions
vector<GOption> defineOptions() {
	
	vector<GOption> goptions;
	
	json jsonGPhysVerbosity = {
		{GNAME, GPHYSVERBOSITY},
		{GDESC, GVERBOSITY_DESCRIPTION},
		{GDFLT, 1}
	};
	goptions.push_back(GOption(jsonGPhysVerbosity));
	
	string physicsListHelp = "Geant4 Physics List.\n";
	physicsListHelp += string(HELPFILLSPACE) + "Possibles values are:\n";
	physicsListHelp += string(HELPFILLSPACE) + " - 0 (default): no check.\n";
	physicsListHelp += string(HELPFILLSPACE) + " - 1: check for overlaps at physical volume construction.\n";
	json jsonGPhysList = {
		{GNAME, "physicsList"},
		{GDESC, physicsListHelp},
		{GDFLT, 0}
	};
	goptions.push_back(GOption(jsonGPhysList));
	
	// log available physics constructors
	goptions.push_back(GOption("showAvailablePhysics",  "Show Geant4 Physics Modules that can be used with the \"physicsList\" option."));

	return goptions;
}


}
