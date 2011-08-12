#include <include/random/lincong.h>

namespace core {

const uint64_t LinearCongruential::s_uiMod = 0x243AC19B78405BEDULL;

////////////////////////////////////////////////////////////////

LinearCongruential::LinearCongruential(uint64_t uiSeed)
{
  reseed(uiSeed);
}

////////////////////////////////////////////////////////////////

const uint64_t LinearCongruential::getMax() const
{
  return 0xFFFFFFFFFFFFFFFFULL;
}

////////////////////////////////////////////////////////////////

const uint64_t LinearCongruential::getNext()
{
  uiCurrent_ *= s_uiMod;
  return uiCurrent_;
}

////////////////////////////////////////////////////////////////

void LinearCongruential::reseed(uint64_t uiSeed)
{
  uiCurrent_ = std::max(uiSeed, uint64_t(0));
}

////////////////////////////////////////////////////////////////

}
