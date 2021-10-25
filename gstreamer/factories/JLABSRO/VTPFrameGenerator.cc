#include "VTPFrameGenerator.h"

// c++
#include <cassert>
#include <functional>
#include <random>

FrameGenerator::FrameGenerator(unsigned int crateid,
						unsigned int slots,
						unsigned int channels,
						double hit_rate)
	: frame_data_(header_offset_, 0)
	, crateid_{crateid}
	, slots_{slots}
	, channels_{channels}
	, gen_(crateid * 10 + 100 + slots)
	    , time_gen_{hit_rate}
{
	assert(crateid < 0xFF && slots < 0x3F && channels < 0x3F);
}

void FrameGenerator::generate_data(unsigned int counter)
{
	// init header
	init_header(counter);

	// init payload
	frame_data_.resize(header_offset_);
	frame_data_.push_back(0x80000000);
	frame_data_.insert(frame_data_.end(), slots_, 0);

	// make data
	for (unsigned int i = 0; i < slots_; ++i) {
	 make_payload_data(i);
	 }

	// update frame length
	update_frame_length();
}

void FrameGenerator::init_header(unsigned int counter)
{
	DataFrameHeader& vtph =	*reinterpret_cast<DataFrameHeader*>(frame_data_.data());

	vtph.source_id      = 0;
	vtph.magic          = magic;
	vtph.format_version = 257;
	vtph.flags          = 0;
	vtph.record_counter = llswap(counter);

	vtph.ts_sec  = 0;//llswap((counter * 65536) / static_cast<int>(1e9));
	vtph.ts_nsec = 0;//llswap((counter * 65536) % static_cast<int>(1e9));

	update_frame_length();
}

void FrameGenerator::make_payload_data(unsigned int slot)
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

void FrameGenerator::update_frame_length()
{
  DataFrameHeader& vtph =
      *reinterpret_cast<DataFrameHeader*>(frame_data_.data());
  auto frame_size = frame_data_.size() * sizeof(unsigned int);

  vtph.compressed_length = frame_size - sizeof(DataFrameHeader);
  vtph.payload_length    = vtph.compressed_length;
  vtph.total_length      = frame_size - 4;
}

void FrameGenerator::update_counter(unsigned int counter)
{
  DataFrameHeader& vtph =
      *reinterpret_cast<DataFrameHeader*>(frame_data_.data());
  vtph.record_counter = llswap(counter);
  vtph.ts_sec         = llswap((counter * 65536) / static_cast<int>(1e9));
  vtph.ts_nsec        = llswap((counter * 65536) % static_cast<int>(1e9));
}

DataFrameHeader const& FrameGenerator::get_header() const
{
  return *reinterpret_cast<DataFrameHeader const*>(frame_data_.data());
}

std::vector<unsigned int> const& FrameGenerator::get_frame_data() const
{
  return frame_data_;
}

PayloadPrinter FrameGenerator::payload_printer(int nFADC, bool verbose,
                                               int rc) const
{
  PayloadPrinter result;

  result.nFADC          = nFADC;
  result.payload.first  = frame_data_.begin() + header_offset_;
  result.payload.second = frame_data_.end();
  result.verbose        = verbose;
  result.record_counter = rc;

  return result;
}
