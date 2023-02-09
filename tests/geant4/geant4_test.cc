
// geant4
#include "G4RunManagerFactory.hh"
#include "G4UIExecutive.hh"


int main(int argc,char** argv)
{
    G4String session = "Qt";

    // Detect interactive mode (if no macro provided) and define UI session
    G4UIExecutive* ui = new G4UIExecutive(argc, argv, session);

    auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

    delete runManager;
    delete ui;

}

