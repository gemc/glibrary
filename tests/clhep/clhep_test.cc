
// CLHEP units
#include "CLHEP/Units/PhysicalConstants.h"
#include "CLHEP/Random/RandGaussT.h"
using namespace CLHEP;

// c++ standard library
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

    cout << " CLHEP include and library tests:" << endl;

    cout << "  - 1 mm = " << 1.0/mm << " mm" << endl;
    cout << "  - pi = " << pi << endl;

    auto rtest =  CLHEP::RandGauss::shoot(0.5, 0.1);
    cout << "  - RandGauss::shoot(0.5, 0.1) = " << rtest << endl;

    return 0;

  }