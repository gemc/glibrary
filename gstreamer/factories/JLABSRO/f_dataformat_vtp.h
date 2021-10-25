#ifndef PACKAGES_DATAFORMATS_F_DATAFORMAT_VTP_HPP
#define PACKAGES_DATAFORMATS_F_DATAFORMAT_VTP_HPP

#include "s_dataformat_vtp.h"
#include <bitset>
#include <chrono>
#include <functional>
#include <ostream>
#include <istream>
#include <sstream>
#include <vector>

auto constexpr deltaTime = 65536;

inline DataFrameHeader* dataframeheader_cast(unsigned char* pointer)
{
  return static_cast<DataFrameHeader*>(static_cast<void*>(pointer));
}

inline const DataFrameHeader* dataframeheader_cast(unsigned char const* pointer)
{
  return static_cast<DataFrameHeader const*>(static_cast<void const*>(pointer));
}

// TODO: Remove them after passing to unsigned char* in the whole TriDAS
inline DataFrameHeader* dataframeheader_cast(char* pointer)
{
  return static_cast<DataFrameHeader*>(static_cast<void*>(pointer));
}

inline const DataFrameHeader* dataframeheader_cast(char const* pointer)
{
  return static_cast<DataFrameHeader const*>(static_cast<void const*>(pointer));
}

inline bool operator==(DataFrameHeader const& first,
                       DataFrameHeader const& second)
{
  return first.source_id == second.source_id
      && first.total_length == second.total_length
      && first.payload_length == second.payload_length
      && first.compressed_length == second.compressed_length
      && first.magic == second.magic
      && first.format_version == second.format_version
      && first.flags == second.flags
      && first.record_counter == second.record_counter
      && first.ts_sec == second.ts_sec && first.ts_nsec == second.ts_nsec;
}

inline std::uint64_t llswap(unsigned long long val)
{
  return (val >> 32) | (val << 32);
}

inline std::uint32_t getDFHSourceID(DataFrameHeader const& header)
{
  return header.source_id;
}

inline std::uint32_t getDFHSampleSize(DataFrameHeader const& header)
{
  return header.total_length;
}

inline std::uint32_t getDFHPayloadSize(DataFrameHeader const& header)
{
  return header.payload_length;
}

inline std::uint32_t getDFHCompressedSize(DataFrameHeader const& header)
{
  return header.compressed_length;
}

inline std::uint32_t getDFHFormatVersion(DataFrameHeader const& header)
{
  return header.format_version;
}

inline std::uint32_t getDFHFlags(DataFrameHeader const& header)
{
  return header.flags;
}

inline bool testDFHSync(DataFrameHeader const& header)
{
  return header.magic == magic;
}

inline std::uint64_t getDFHRecordCounter(DataFrameHeader const& header)
{
  return llswap(header.record_counter);
}

inline std::uint64_t getDFHSec(DataFrameHeader const& header)
{
  return llswap(header.ts_sec);
}

inline std::uint64_t getDFHNanoSec(DataFrameHeader const& header)
{
  return llswap(header.ts_nsec);
}

/*inline fine_time getDFHFullTime(DataFrameHeader const& header)
{
  return std::chrono::nanoseconds(getDFHRecordCounter(header)) * deltaTime;
}*/

inline std::ostream& operator<<(std::ostream& os,
                                DataFrameHeader const& header)
{
  os << "sourceID:       " << header.source_id << '\n'
     << "TotalSize:      " << header.total_length << '\n'
     << "PayloadSize:    " << header.payload_length << '\n'
     << "CompressedSize: " << header.compressed_length << '\n'
     << "Magic:          " << std::hex << header.magic << std::dec << '\n'
     << "Version:        " << header.format_version << '\n'
     << "Flags:          " << header.flags << '\n'
     << "RecordCounter:  " << getDFHRecordCounter(header) << '\n'
     << "TsSec:          " << getDFHSec(header) << '\n'
     << "TsNanosec:      " << getDFHNanoSec(header) << '\n'
     << "\n\n";
  return os;
}

inline std::ostream& operator<<(std::ostream& os,
                                PayloadPrinter const& pp)
{
  if (auto const tag = *pp.payload.first; (tag & 0x8fff8000) != 0x80000000) {
    os << "ERROR: no TAG detected\n";
    return os;
  }

  auto slot_it   = pp.payload.first + 1;
  auto slot_end  = slot_it + pp.nFADC;
  int activeFADC = std::count_if(slot_it, slot_end, [](auto el) {
    auto n = el >> 16;
    return n > 0;
  });

  if (!pp.verbose) {
    os << "Active FADC:    " << activeFADC << "/" << pp.nFADC << "\n\n";
    return os;
  }

  // foreach FADC
  for (int i = 1; slot_it != slot_end; ++i, ++slot_it) {
    int slot_ind = *slot_it & 0xFFFF;
    int slot_len = *slot_it >> 16;

    // print slot index and length
    // clang-format off
    os << "\nFADC-0" << i << ": " << std::bitset<32>(*slot_it)
       << "\n  Slot_index:\t"  << slot_ind
       << "\n  slot_length:\t" << slot_len << "\n";
    // clang-format on

    // print slot hit
    if (slot_len > 0) {
      int type = 0, hit_per_slot = 0, crate_id, slot_id, t, channel_id, q;
      unsigned long long hit_time;

      for (auto hit_it     = pp.payload.first + slot_ind,
                hit_it_end = pp.payload.first + slot_ind + slot_len;
           hit_it != hit_it_end; ++hit_it) {
        // print first word
        if (*hit_it & 0x80000000) {
          type     = (*hit_it >> 15) & 0xFFFF; // bit 30-15
          crate_id = (*hit_it >> 8) & 0x007F;  // bit 14-8
          slot_id  = *hit_it & 0x001F;         // bit 4-0

          // clang-format off
          os << "\n  Slot Header: " << std::bitset<32>(*hit_it)
             << "\n    Type:  "     << type
             << "\n    Crate: "    << crate_id
             << "\n    Slot:  "     << slot_id << "\n";
          // clang-format on

          // print hit
        } else if (type == 0x0001) {
          hit_per_slot++;
          q          = *hit_it & 0x1FFF;               // bit 0-12
          channel_id = (*hit_it >> 13) & 0x000F;       // bit 13-16
          t          = ((*hit_it >> 17) & 0x3FFF) * 4; // bit 17-30
          hit_time   = pp.record_counter * 65536LL + t;

          // clang-format off
          os << "\n  Hit Word: " << std::bitset<32>(*hit_it)
             << "\n    Crate:    " << crate_id
             << "\n    Slot:     " << slot_id
             << "\n    Channel:  " << channel_id
             << "\n    q:        " << q
             << "\n    Hit time: " << hit_time << " (" << t << ")\n";
          // clang-format on

          // print strange word
        } else {
          os << "\n  Word not recognized: " << std::bitset<32>(*hit_it);
        }
      }
    }
  }

  return os;
}

/*inline void parseData(
    std::istream& input, int n_of_frames, unsigned int offset, bool verbose,
    int nFADC,
    std::function<void(DataFrameHeader const&, PayloadPrinter const&)>
        callb)
{
  boost::circular_buffer<std::uint32_t> cbuf(4);
  DataFrameHeader header;

  for (int i = 0; i != 4; i++) {
    std::uint32_t el;
    input.read(reinterpret_cast<char*>(&el), sizeof(std::uint32_t));
    cbuf.push_back(el);
  }

  // magic number search
  while (input) {
    std::uint32_t el;
    input.read(reinterpret_cast<char*>(&el), sizeof(std::uint32_t));
    if (el == magic) {
      header.magic             = el;
      header.compressed_length = cbuf[3];
      header.payload_length    = cbuf[2];
      header.total_length      = cbuf[1];
      header.source_id         = cbuf[0];
      break;
    }
    cbuf.push_back(el);
  }

  assert(testDFHSync(header));

  // header reading (missing fileds)
  input.read(reinterpret_cast<char*>(&header.format_version),
             sizeof(std::uint32_t));
  input.read(reinterpret_cast<char*>(&header.flags), sizeof(std::uint32_t));
  input.read(reinterpret_cast<char*>(&header.record_counter),
             sizeof(std::uint64_t));
  input.read(reinterpret_cast<char*>(&header.ts_sec), sizeof(std::uint64_t));
  input.read(reinterpret_cast<char*>(&header.ts_nsec), sizeof(std::uint64_t));

  // print the result
  Payload payload;
  int counter = 0;
  while (input && counter != n_of_frames) {
    assert(header.payload_length % 4 == 0);
    payload.resize(header.payload_length / 4);
    if (!input.read(reinterpret_cast<char*>(payload.data()),
                    header.payload_length)) {
      break;
    }

    if (!offset) {
      auto payload_printer = PayloadPrinter{
          nFADC, {payload.begin(), payload.end()}, verbose, counter};
      callb(header, payload_printer);
      ++counter;
    } else {
      --offset;
    }

    input.read(reinterpret_cast<char*>(&header), sizeof(header));
    assert(testDFHSync(header));
  }
}*/

#endif
