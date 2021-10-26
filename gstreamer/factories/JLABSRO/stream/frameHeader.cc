// gstreamer
#include "gstreamerJLABSROFactory.h"
//#include "VTPFrameGenerator.h"
#include "f_dataformat_vtp.h"
#include "Configuration.h"

// c++
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

bool GstreamerJSROFactory::publishFrameHeader(const GFrameDataCollectionHeader *gframeHeader) 
{
	if(ofile == nullptr) return false;


	*ofile << GTAB << "Frame Header  {" << endl;
//	*ofile << GTABTAB << " frameID: " << gframeHeader->getFrameID() << endl;
	*ofile << GTAB << "}" << endl;	
/*
	vector<std::uint32_t> const super_magic = {0xC0DA2019, 0XC0DA0001};

	ofile->write(reinterpret_cast<const char*>(super_magic.data()), sizeof(std::uint32_t) * 2);

	vector<unsigned int> const& frame = gframeHeader->get_frame_data();
	ofile->write(reinterpret_cast<const char*>(frame.data()),
					 sizeof(unsigned int) * frame.size());
*/

	return true;


}


