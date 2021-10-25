// gstreamer
#include "gstreamerJLABSROFactory.h"
#include "VTPFrameGenerator.h"


bool GstreamerJSROFactory::startStream(const GFrameDataCollection* frameRunData)
{
	if(ofile == nullptr) return false;

        double hit_rate = 30000;
        unsigned int channels = 16;
        unsigned int slots = 8;
        unsigned int crates = 1;

        FrameGenerator vtpf(crates, slots, channels, hit_rate);
        vtpf.generate_data(0);


	return true;
}




bool GstreamerJSROFactory::endStream(const GFrameDataCollection* frameRunData)
{
	if(ofile == nullptr) return false;


	return true;
}
