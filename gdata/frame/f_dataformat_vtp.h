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
inline std::uint64_t llswap(unsigned long long val)
{
  return (val >> 32) | (val << 32);
}

#endif
