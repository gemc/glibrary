// gsystem
#include "gmaterial.h"

// c++
#include <iostream>
#include <sstream>
using namespace std;


GMaterial::GMaterial(string s, vector<string> pars) : system(s)
{
	if( pars.size() != GMATERIALNUMBEROFPARS) {
		cerr << FATALERRORL << "incorrect number of material parameters (" << pars.size() << ") for " << pars[0] ;
		cerr << " It should be " << GMATERIALNUMBEROFPARS << endl;
		gexit(EC__GWRONGNUMBEROFPARS);
	} else {
		// size is already checked in addVolume, the only interface to volume
		int i=0;
		
		name         = trimSpacesFromString(pars[i++]);
		description  = pars[i++];
		density      = stod(trimSpacesFromString(pars[i++]));

		// sets components and amounts
		setComponentsFromString(pars[i++]);

		getMaterialPropertyFromString(pars[i++], "photonEnergy");
		getMaterialPropertyFromString(pars[i++], "indexOfRefraction");
		getMaterialPropertyFromString(pars[i++], "absorptionLength");
		getMaterialPropertyFromString(pars[i++], "reflectivity");
		getMaterialPropertyFromString(pars[i++], "efficiency");
		getMaterialPropertyFromString(pars[i++], "fastcomponent");
		getMaterialPropertyFromString(pars[i++], "slowcomponent");

		scintillationyield = stod(trimSpacesFromString(pars[i++]));
		resolutionscale    = stod(trimSpacesFromString(pars[i++]));
		fasttimeconstant   = stod(trimSpacesFromString(pars[i++]));
		slowtimeconstant   = stod(trimSpacesFromString(pars[i++]));
		yieldratio         = stod(trimSpacesFromString(pars[i++]));
		birkConstant       = stod(trimSpacesFromString(pars[i++]));

		getMaterialPropertyFromString(pars[i++], "rayleigh");

	}
}


ostream &operator<<(ostream &stream, GMaterial gMat)
{

	stream  << endl;
	//	stream << "   - Name:            "    << gMat.name     << "  -  " <<  gMat.description << endl;
	//	stream << "   - Mother:          "    << gMat.mother      << endl;
	//	stream << "   - Type:            "    << gMat.type        << endl;
	//	stream << "   - Parameters:      "    << gMat.parameters  << endl;
	//	stream << "   - Material:        "    << gMat.material << endl;
	//	stream << "   - E.M. Field:      "    << gMat.emfield << endl;
	//	stream << "   - Positions:       "    << gMat.pos << endl;
	//	stream << "   - Rotation(s):     "    << gMat.rot << endl;
	//	stream << "   - Digitization:    "    << gMat.digitization << endl;
	//	stream << "   - GIdentity:       "    << gMat.gidentity << endl;

	return stream;
}


// sets components and amounts
void GMaterial::setComponentsFromString(string composition) {

	vector<string> allComponents = getStringVectorFromString(composition);

	for( int e=0; e < allComponents.size()/2; e++ ) {
		components.push_back(allComponents[e*2]);
		amounts.push_back(stod(allComponents[e*2+1]));
	}

}


// load property from DB entry based on its name
void GMaterial::getMaterialPropertyFromString(string parameter, string propertyName) {

	// nothing to do if the parameter is not assigned
	if ( trimSpacesFromString(parameter) == GMATERIALNOTASSIGNEDPROPERTYSTRING ) {
		return;
	}

	stringstream parameterComponents(parameter);

	while(!parameterComponents.eof()) {
		string component;
		parameterComponents >> component ;

		// removing whitespaces
		string trimmedComponent = trimSpacesFromString(component);

		if( propertyName == "photonEnergy" ) {
			photonEnergy.push_back(getG4Number(trimmedComponent));
		} else if( propertyName == "indexOfRefraction" ) {
			indexOfRefraction.push_back(getG4Number(trimmedComponent));
		} else if(propertyName == "absorptionLength") {
			absorptionLength.push_back(getG4Number(trimmedComponent));
		} else if(propertyName == "reflectivity") {
			reflectivity.push_back(getG4Number(trimmedComponent));
		} else if(propertyName == "efficiency") {
			efficiency.push_back(getG4Number(trimmedComponent));
		} else if(propertyName == "fastcomponent") {
			fastcomponent.push_back(getG4Number(trimmedComponent));
		} else if(propertyName == "slowcomponent") {
			slowcomponent.push_back(getG4Number(trimmedComponent));
		} else if(propertyName == "scintillationyield") {
			scintillationyield = getG4Number(trimmedComponent);
		} else if(propertyName == "resolutionscale") {
			resolutionscale = getG4Number(trimmedComponent);
		} else if(propertyName == "fasttimeconstant") {
			fasttimeconstant = getG4Number(trimmedComponent);
		} else if(propertyName == "slowtimeconstant") {
			slowtimeconstant = getG4Number(trimmedComponent);
		} else if(propertyName == "yieldratio") {
			yieldratio = getG4Number(trimmedComponent);
		} else if(propertyName == "rayleigh") {
			rayleigh.push_back(getG4Number(trimmedComponent));
		} else if(propertyName == "birkConstant") {
			birkConstant = getG4Number(trimmedComponent);
		}


		if(propertyName == "rayleigh") {
			// rayleigh is the last quantity to be loaded
			// now we can check the vector sizes for comparison
			// if they do match, behaviour is unknown, we need to exit

			if ( indexOfRefraction.size() > 0 &&  indexOfRefraction.size() != photonEnergy.size() ) {
				cerr << FATALERRORL << "indexOfRefraction size " << indexOfRefraction.size() << " mismatch: photonEnergy has size " << photonEnergy.size() << endl;
				gexit(EC__GMATERIALOPTICALPROPERTYMISMATCH);
			}
			if ( absorptionLength.size() > 0 &&  absorptionLength.size() != photonEnergy.size() ) {
				cerr << FATALERRORL << "absorptionLength size " << absorptionLength.size()   << " mismatch: photonEnergy has size " << photonEnergy.size() << endl;
				gexit(EC__GMATERIALOPTICALPROPERTYMISMATCH);
			}
			if ( reflectivity.size() > 0 &&  reflectivity.size() != photonEnergy.size() ) {
				cerr << FATALERRORL << "reflectivity size " << reflectivity.size()           << " mismatch: photonEnergy has size " << photonEnergy.size() << endl;
				gexit(EC__GMATERIALOPTICALPROPERTYMISMATCH);
			}
			if ( efficiency.size() > 0 &&  efficiency.size() != photonEnergy.size() ) {
				cerr << FATALERRORL << "efficiency size " << efficiency.size()               << " mismatch: photonEnergy has size " << photonEnergy.size() << endl;
				gexit(EC__GMATERIALOPTICALPROPERTYMISMATCH);
			}
			if ( fastcomponent.size() > 0 &&  fastcomponent.size() != photonEnergy.size() ) {
				cerr << FATALERRORL << "fastcomponent size " << fastcomponent.size()         << " mismatch: photonEnergy has size " << photonEnergy.size() << endl;
				gexit(EC__GMATERIALOPTICALPROPERTYMISMATCH);
			}
			if ( slowcomponent.size() > 0 &&  slowcomponent.size() != photonEnergy.size() ) {
				cerr << FATALERRORL << "slowcomponent size " << slowcomponent.size()         << " mismatch: photonEnergy has size " << photonEnergy.size() << endl;
				gexit(EC__GMATERIALOPTICALPROPERTYMISMATCH);
			}
			if ( rayleigh.size() > 0 &&  rayleigh.size() != photonEnergy.size() ) {
				cerr << FATALERRORL << "rayleigh size " << rayleigh.size()                   << " mismatch: photonEnergy has size " << photonEnergy.size() << endl;
				gexit(EC__GMATERIALOPTICALPROPERTYMISMATCH);
			}

		}



	}
}