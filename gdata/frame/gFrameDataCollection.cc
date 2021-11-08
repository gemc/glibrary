// gdata
#include "gFrameDataCollection.h"

// c++
using namespace std;

void GFrameDataCollection::addIntegralPayload(vector<int> payload, int verbosity) {

	if (payload.size() == 4 ) {
		int crate   = payload[0];
		int slot    = payload[1];
		int channel = payload[2];
		int charge  = payload[3];
		int time    = payload[4];

		GIntegralPayload *gpayload = new GIntegralPayload(crate, slot, channel, charge, time, verbosity);
		integralPayload->push_back(gpayload);
		
	} else {
		cerr << FATALERRORL << "payload size is not 4 but " << payload.size() << endl;
		gexit(EC__WRONGPAYLOAD);
	}

}


