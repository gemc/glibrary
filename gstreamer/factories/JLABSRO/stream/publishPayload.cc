// gstreamer
#include "gstreamerJLABSROFactory.h"

bool GstreamerJSROFactory::publishPayload(const vector<GIntegralPayload*> *payload)
{
	if(ofile == nullptr) return false;

	ofile->write(reinterpret_cast<const char*>(payload->data()),
					 sizeof(unsigned int) * payload->size());

	return true;
}


