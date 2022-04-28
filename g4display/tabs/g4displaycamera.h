#ifndef  G4DISPLAYCAMERA_H
#define  G4DISPLAYCAMERA_H 1

// qt
#include <QtWidgets>

// glibrary
#include "goptions.h"

// geant4 headers
#include "G4UImanager.hh"

class G4DisplayCamera: public QWidget {

	// metaobject required for non-qt slots
	Q_OBJECT

public:
	G4DisplayCamera(GOptions* gopts, QWidget* parent = Q_NULLPTR);

	~G4DisplayCamera() {
		delete cameraTheta;
		delete cameraPhi;
		delete lightTheta;
		delete lightPhi;
	}

private:
	QSlider *cameraTheta;
	QSlider *cameraPhi;
	QSlider *lightTheta;
	QSlider *lightPhi;

private slots:
	void changeCameraDirection();
	void changeLightDirection();

};


#endif
