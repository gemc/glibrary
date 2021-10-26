#ifndef  GFRAMEHEADER_H
#define  GFRAMEHEADER_H  1

// gdata
#include "gutsConventions.h"

// glibrary
#include "goptions.h"         // GVERBOSITY
#include "gutsConventions.h"  // gLogClassConstruct

//VTP
#include "f_dataformat_vtp.h"

// c++
#include <iostream>
#include <vector>

using std::to_string;

class GFrameDataCollectionHeader
{
	static constexpr int header_offset_ = sizeof(DataFrameHeader) / 4;
	std::vector<unsigned int> frame_data_;

	void init_header(unsigned int counter);
	void update_frame_length();

public:
	GFrameDataCollectionHeader(long int fid, float fd, vector<unsigned int> frameDef, int v = 0) : frame_data_(header_offset_, 0), verbosity(v), frameID(fid), frameDuration(fd)  {

		if ( verbosity >= GVERBOSITY_DETAILS ) {
			string log = "GFrameHeader id " + to_string(frameID) + ", time: " + to_string(time_ns()) + "ns";
			gLogClassConstruct(log);
		}
	}

	~GFrameDataCollectionHeader() {
		if ( verbosity >= GVERBOSITY_DETAILS) {
			string log = "GFrameHeader id " + to_string(frameID);
			gLogDestruct(log);
		}
	}

	// getters
	inline long int const getFrameID() const { return frameID; }
	DataFrameHeader const& get_header() const;
	std::vector<unsigned int> const& get_frame_data() const;


private:

	int verbosity;

	long int frameID;
	float frameDuration;

	long int time_ns() const;

};






#endif
