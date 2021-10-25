// gdata
#include "gFrameDataCollectionHeader.h"


long int GFrameDataCollectionHeader::time_ns() const {return frameID*frameDuration;}

void GFrameDataCollectionHeader::init_header(unsigned int counter)
{
  DataFrameHeader& vtph =
      *reinterpret_cast<DataFrameHeader*>(frame_data_.data());
  vtph.source_id      = 0;
  vtph.magic          = magic;
  vtph.format_version = 257;
  vtph.flags          = 0;
  vtph.record_counter = llswap(counter);

  vtph.ts_sec  = llswap((counter * 65536) / static_cast<int>(1e9));
  vtph.ts_nsec = llswap((counter * 65536) % static_cast<int>(1e9));

  update_frame_length();
}

void GFrameDataCollectionHeader::update_frame_length()
{
  DataFrameHeader& vtph =
      *reinterpret_cast<DataFrameHeader*>(frame_data_.data());
  auto frame_size = frame_data_.size() * sizeof(unsigned int);

  vtph.compressed_length = frame_size - sizeof(DataFrameHeader);
  vtph.payload_length    = vtph.compressed_length;
  vtph.total_length      = frame_size - 4;
}

DataFrameHeader const& GFrameDataCollectionHeader::get_header() const
{
  return *reinterpret_cast<DataFrameHeader const*>(frame_data_.data());
}

std::vector<unsigned int> const& GFrameDataCollectionHeader::get_frame_data() const
{
  return frame_data_;
}


