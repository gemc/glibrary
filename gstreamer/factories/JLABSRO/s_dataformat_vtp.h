#ifndef PACKAGES_DATAFORMATS_S_DATAFORMAT_VTP_HPP
#define PACKAGES_DATAFORMATS_S_DATAFORMAT_VTP_HPP

#include <cstdint>
#include <vector>

auto constexpr magic = 0xC0DA2019;

#pragma pack(push, 1)
struct DataFrameHeader
{
  std::uint32_t source_id;
  std::uint32_t total_length;
  std::uint32_t payload_length;
  std::uint32_t compressed_length;
  std::uint32_t magic;
  std::uint32_t format_version;
  std::uint32_t flags;
  std::uint64_t record_counter;
  std::uint64_t ts_sec;
  std::uint64_t ts_nsec;
};
#pragma pack(pop)

class Payload : public std::vector<unsigned int>
{
  using std::vector<unsigned int>::vector;
};

struct PayloadPrinter {
  int nFADC;
  std::pair<Payload::const_iterator, Payload::const_iterator> payload;
  bool verbose;
  int record_counter;
};

#endif
