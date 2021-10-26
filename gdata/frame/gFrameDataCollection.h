#ifndef  GFRAMEDATA_H
#define  GFRAMEDATA_H  1

// gdata
#include "gFrameDataCollectionHeader.h"
#include "gIntegralPayload.h"
#include "gdataConventions.h"

// c++
#include <vector>
#include <random>

using std::vector;

class GFrameDataCollection
{
public:
	// construct event data using a GEventHeader
	GFrameDataCollection(GFrameDataCollectionHeader* header, int v = 0 ) : verbosity(v), gheader(header) {
		if ( verbosity >= GVERBOSITY_DETAILS) {
			gLogClassConstruct("GFrameDataCollection");
		}
		integralPayload = new vector<GIntegralPayload*>();
	}

	~GFrameDataCollection() {

		if ( verbosity >= GVERBOSITY_DETAILS) {
			gLogDestruct("GFrameDataCollection");
		}

		delete gheader;

		for ( auto* payload: *integralPayload )  { delete payload; }
		delete integralPayload;
	}

public:

	// integral payload: integrated quantity
	void addIntegralPayload(vector<int> payload, int verbosity);
	void addEvent(int evn);
	bool const shouldWriteFrame() const;

	// getters
	inline const GFrameDataCollectionHeader* getHeader()         const { return gheader; }
	inline const vector<GIntegralPayload*>* getIntegralPayload() const { return integralPayload; }
	inline const long int getFrameID()                           const { return gheader->getFrameID(); }
	void make_payload_data(unsigned int slot);
	void update_frame_length();

	
	std::default_random_engine gen_;
        std::exponential_distribution<> time_gen_;


private:
	int verbosity;

	GFrameDataCollectionHeader *gheader = nullptr;

	vector<GIntegralPayload*> *integralPayload;


};


#endif

