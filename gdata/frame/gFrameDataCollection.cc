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

		GIntegralPayload *gpayload = new GIntegralPayload(crate, slot, channel, charge, verbosity);
		integralPayload->push_back(gpayload);
		
	} else {
		cerr << FATALERRORL << "payload size is not 4 but " << payload.size() << endl;
		gexit(EC__WRONGPAYLOAD);
	}
}
/*
void GFrameDataCollection::make_payload_data(unsigned int slot)
{
  // FADC slot header
  int starting_point = frame_data_.size() - header_offset_;
  frame_data_.push_back(0x80008000 | (crateid_ << 8) | slot);

  bool generating = true;
  int hit_counter = 0;
  std::vector<unsigned int> times(channels_, 0);

  while (generating) {
    for (unsigned int i = 0; i < channels_; ++i) {
      times[i] += 1e9 * time_gen_(gen_);
      if (times[i] > 65536) {
        generating = false;
        break;
      }
      assert((times[i] / 4) < 0x8000 && i < 0x10);
      frame_data_.push_back(1024 | (i << 13) | ((times[i] / 4) << 17));
      ++hit_counter;
    }
  }

  if (hit_counter == 0) {
    frame_data_.pop_back();
  } else {
    ++hit_counter;
  }

  frame_data_[header_offset_ + 1 + slot] =
      ((hit_counter) << 16) | starting_point;
}

void GFrameDataCollection::update_frame_length()
{
  DataFrameHeader& vtph =
      *reinterpret_cast<DataFrameHeader*>(frame_data_.data());
  auto frame_size = frame_data_.size() * sizeof(unsigned int);

  vtph.compressed_length = frame_size - sizeof(DataFrameHeader);
  vtph.payload_length    = vtph.compressed_length;
  vtph.total_length      = frame_size - 4;
}
*/



