// g4system
#include "g4systemOptions.h"

// project goption to a system
namespace g4system {

	// returns array of options definitions
	vector<GOption> defineOptions() {

		vector<GOption> goptions;

		json jsonG4WorldVerbosity = {
			{GNAME, "g4systemv"},
			{GDESC, GVERBOSITY_DESCRIPTION},
			{GDFLT, 1}
		};
		goptions.push_back(GOption(jsonG4WorldVerbosity));

		// use this string option to print out informations about this volume at construction time
		json jsonVolumeLogVerbosity = {
			{GNAME, "logVolume"},
			{GDESC, GVERBOSITY_DESCRIPTION},
			{GDFLT, "na"}
		};
		goptions.push_back(GOption(jsonVolumeLogVerbosity));

		// default material to use when a material is not found
		json jsonDefaultMaterial = {
			{GNAME, "defaultMaterial"},
			{GDESC, GVERBOSITY_DESCRIPTION},
			{GDFLT, "G4Galactica"}
		};
		goptions.push_back(GOption(jsonDefaultMaterial));

		// add a "useDefaultMaterial" switch
		goptions.push_back(GOption("useDefaultMaterial", "use Default Material if a volume's material is not defined"));



		return goptions;
	}


}
