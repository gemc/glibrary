// gtouchable
#include "gtouchable.h"
#include "gtouchableConventions.h"

// glibrary
#include "gutilities.h"
using namespace std;

#include <math.h>       /* fabs */

// contructor from digitization and gidentity strings
// called in GDetectorConstruction::ConstructSDandField
// to register a new gtouchable in the sensitive detector gtouchable map
GTouchable::GTouchable(string digitization, string gidentityString, vector<double> dimensions, bool verb) :
verbosity(verb),
trackId(0),
eMultiplier(1),
timeAtElectronics(0),
detectorDimenions(dimensions) {

	// gtype from digitization
	if ( digitization == FLUXNAME ) {
		gType = flux;
	} else if ( digitization == COUNTERNAME ) {
		gType = particleCounter;
	} else if ( digitization == DOSIMETERNAME ) {
		gType = dosimeter;
	} else {
		gType = readout;
	}

	// the gidentity string is of the form: 'sector: 2, layer: 4, wire; 33'
	// by construction in the sci-g API
	vector<string> identity = gutilities::getStringVectorFromStringWithDelimiter(gidentityString, ",");
	// each identity item is a string of the form 'sector: 2'
	for ( auto& gid: identity) {
		vector<string> identifier = gutilities::getStringVectorFromStringWithDelimiter(gid, ":");

		string idName  = identifier[0];
		int idValue = stoi(identifier[1]);

		gidentity.push_back(GIdentifier(idName, idValue));
	}

}

// copy constructor called in processTouchable
// weight and time can be set by processTouchable
GTouchable::GTouchable(const GTouchable& baseGT, vector<GIdentifier> gid, float weight) :
gidentity(gid),
eMultiplier(weight) {
	gType             = baseGT.gType;
	verbosity         = baseGT.verbosity;
	trackId           = baseGT.trackId;
	timeWindow        = baseGT.timeWindow;
	timeAtElectronics = baseGT.timeAtElectronics;
}

// copy constructor called in processTouchable
// weight and time can be set by processTouchable
GTouchable::GTouchable(const GTouchable& baseGT, vector<GIdentifier> gid, float weight, float t) :
gidentity(gid),
eMultiplier(weight),
timeAtElectronics(t) {
	gType         = baseGT.gType;
	verbosity     = baseGT.verbosity;
	trackId       = baseGT.trackId;
	timeWindow    = baseGT.timeWindow;
}


// todo: optimize the algorithm
bool GTouchable::operator == (const GTouchable& that) const
{

	// first, compare size of identity
	// this should never happen because the same sensitivity should be assigned the same identifier structure
	if (this->gidentity.size() != that.gidentity.size()) {
		if (verbosity) {
			cout << " Touchable sizes are different " << endl;
		}
		return false;
	}

	if (verbosity) {
		cout << " Touchable comparison:  " << endl;
		for (size_t i=0; i<that.gidentity.size(); i++) {
			cout << this->gidentity[i] << " " <<  that.gidentity[i] << endl;
		}
	}

	// now compare that the identity is actuallty the same
	// return false if something is different
	for (size_t i=0; i<that.gidentity.size(); i++) {
		if (this->gidentity[i] != that.gidentity[i]) {
			return false;
		}
	}

	switch (this->gType) {
		case readout:
			return fabs(this->timeAtElectronics - that.timeAtElectronics) < this->timeWindow;
		case flux:
			return this->trackId == that.trackId;
		case dosimeter:
			return this->trackId == that.trackId;
		case particleCounter:
			return true;
	}

	return false;
}

// ostream GTouchable
ostream &operator<<(ostream &stream, GTouchable gtouchable) {

	stream << " GTouchable: " << std::endl;
	stream << "   ・ ";
	for ( auto& gid: gtouchable.gidentity ) {

		stream << gid ;
		if ( gid.getName() != gtouchable.gidentity.back().getName() ) {
			stream << ", ";
		} else {
			stream << std::endl;
		}
	}

	stream << "   ・ energy multiplier: " << gtouchable.eMultiplier << std::endl;
	stream << "   ・ time: " << gtouchable.timeAtElectronics << std::endl;
	stream << "   ・ time window: " << gtouchable.timeWindow << std::endl;
	stream << "   ・ g4 track id: " << gtouchable.trackId << std::endl;
	return stream;
}

// ostream GIdentifier
ostream &operator<<(ostream &stream, GIdentifier gidentifier) {
	stream << gidentifier.idName << ": " <<  gidentifier.idValue ;
	return stream;
}
