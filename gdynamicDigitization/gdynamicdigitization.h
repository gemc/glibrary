#ifndef  GDYNAMICDIGITIZATION_H
#define  GDYNAMICDIGITIZATION_H 1

// dynamic digitization
#include "greadoutSpecs.h"

// glibrary
#include "gdl.h"
#include "gtouchable.h"
#include "ghit.h"
#include "event/gDigitizedData.h"
#include "event/gTrueInfoData.h"
#include "gtranslationTable.h"

// c++
#include <vector>
#include <bitset>

// geant4
#include "G4Step.hh"

class GTouchableModifiers {

public:
	// abstract destructor
	GTouchableModifiers(vector<string> touchableNames);

private:
	// only one of these maps can be filled with values:
	// the size of the map is used by processGTouchableModifiers

	// vector is pair: (id, weight)
	map<string, vector<double> > modifierWeightsMap;

	// vector is triplet: (id, weight, time)
	map<string, vector<double> > modifierWeightsAndTimesMap;

// api
public:

	// insert new values
	void insertIdAndWeight(string touchableName, int idValue, double weight);
	void insertIdWeightAndTime(string touchableName, int idValue, double weight, double time);

	// normalize a map using totalWeight
	void assignOverallWeight(string touchableName, double totalWeight);

	inline bool isWeightsOnly() {
		return modifierWeightsMap.size() > 0;
	}

	// get vectors from modifierWeightsMap using touchableName
	inline vector<double> getModifierWeightsVector(string touchableName) {
		// this will crash if user request a key not declared in the constructor
		return modifierWeightsMap[touchableName];
	}

	// get vectors from modifierWeightsAndTimesMap using touchableName
	inline vector<double> getModifierWeightsAndTimeVector(string touchableName) {
		// this will crash if user request a key not declared in the constructor
		return modifierWeightsAndTimesMap[touchableName];
	}
};


class GDynamicDigitization {

public:
	// abstract destructor
	virtual ~GDynamicDigitization() = default;

	// change the GTouchable in sensitiveDetector::ProcessHit
	// by default the touchable is not changed
	// this function is loaded by plugin methods
	// notice that this returns a vector of touchables, as one g4step can produce multiple hits
	virtual vector<GTouchable*> processTouchable(GTouchable *gTouchID, G4Step* thisStep) {return { gTouchID } ;}

	vector<GTouchable*> processGTouchableModifiers(GTouchable *gTouchID, GTouchableModifiers gmods);

	// filter true information into GTrueInfoHit
	// this integrates all available information built in GHit::addHitInfosForBitset
	GTrueInfoData *collectTrueInformation(GHit *ghit, size_t hitn);

	// digitize true information into GDigitizedHit
	virtual GDigitizedData *digitizeHit(GHit *ghit, size_t hitn) {return nullptr;}

	// loads the digitization constants
	// return false for failure
	virtual bool loadConstants(int runno, string variation) { return false; }

	// loads the translation table
	// return false for failure
	virtual bool loadTT(int runno, string variation) { return false; }

	// this will set the ghit:
	// - chargeAtElectronics
	// - timeAtElectronics
	// and will update ghit's gtouchable to include the GElectronic using the translation table (hardware address crate/slot/channel)
	// this will exit with error if the TT is not defined
	// notice time is an int (assumed unit: ns)
	void chargeAndTimeAtHardware(int time, int q, GHit *ghit, GDigitizedData *gdata);

	// mandatory initialization of readout specs
	virtual bool defineReadoutSpecs() = 0;

	GReadoutSpecs *readoutSpecs = nullptr;
	GTranslationTable *translationTable = nullptr;

	// method to dynamically load factories
	static GDynamicDigitization* instantiate(const dlhandle handle) {
				
		if (handle == nullptr) return nullptr;

		void *maker = dlsym(handle , "GDynamicDigitizationFactory");

		if (maker == nullptr) return nullptr;

		typedef GDynamicDigitization* (*fptr)();

		// static_cast not allowed here
		// see http://stackoverflow.com/questions/573294/when-to-use-reinterpret-cast
		// need to run the DLL GDynamicFactory function that returns the factory
		fptr func = reinterpret_cast<fptr>(reinterpret_cast<void*>(maker));

		return func();
	}

	// logging: using
	string gdMessageHeader = "   ⎍ ";
	void gDLogMessage(std::string message);

};


#endif
