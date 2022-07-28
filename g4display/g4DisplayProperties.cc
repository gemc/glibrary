// g4display 
#include "g4DisplayProperties.h"
#include "g4displayOptions.h"
using namespace g4display;

// glibrary
#include "gutilities.h"
using namespace gutilities;

// c++
using namespace std;

// geant4
#include "G4UImanager.hh"


G4DisplayProperties::G4DisplayProperties(GOptions* gopts)
{
	// PRAGMA TODO: add resolution option, hits options, here?
	// PRAGMA TOOO: if run/beamOn is given (e.g. command line options) then the label needs to be updated!

	// projecting option onto JView
	JView jview = getJView(gopts);
	JCamera jcamera = getJCamera(gopts);
	
	double toDegrees  = 180/3.1415;
	double thetaValue = getG4Number(jcamera.theta)*toDegrees;
	double phiValue   = getG4Number(jcamera.phi)*toDegrees;

	string gemcViewerOption = "/vis/open " + jview.viewer + " " + jview.dimension  + jview.position;
	string gemcCameraOption = "/vis/viewer/set/viewpointThetaPhi " + to_string(thetaValue) + " " + to_string(phiValue);
	
	G4UImanager* UIM = G4UImanager::GetUIpointer();

	if(UIM) {
				
		UIM->ApplyCommand("/vis/scene/create gemc");

		UIM->ApplyCommand(gemcViewerOption);
		UIM->ApplyCommand(gemcCameraOption);

		UIM->ApplyCommand("/vis/initialize");
		
		
		// add gui commands here, remove from gemc


	//	UIM->ApplyCommand("/vis/scene/add/axes 0 0 0 10 cm");

	} else {
		cout << " No UIManager found. " << endl;
	}

	
	
}
