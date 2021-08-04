// g4display
#include "g4controls.h"
#include "tabs/gcamera.h"
#include "tabs/gslice.h"

G4Controls::G4Controls(GOptions* gopt, QWidget* parent) : QTabWidget(parent)
{
	setStyleSheet("QTabBar::tab       { background-color: #ACB6B6;}"
					  "QTabBar::tab:focus { color: #000011; }");

	addTab(new G4DisplayCamera(gopt, this), "Camera");
	addTab(new G4DisplaySlice(gopt, this),  "View Slice");
	addTab(new QWidget(),"Display Options");
}
