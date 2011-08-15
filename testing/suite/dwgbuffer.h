#pragma once

#include "../utils/unittest.h"

namespace libredwgpp {
  class DWGBuffer;
}

BEGIN_UNITTEST(DWGBuffer)
  BEGIN_REGISTER
    REGISTER(readRaw8)
    REGISTER(readRaw16)
    REGISTER(readRaw32)
    REGISTER(readRawDouble)
    REGISTER(readBit)
    REGISTER(readBit2)
    REGISTER(readBit3)
    REGISTER(readBit16)
    REGISTER(readBit32)
//    REGISTER(readBit64)
    REGISTER(readBitDouble)
    REGISTER(readBitExtrusion)
    REGISTER(readColour)
    REGISTER(readHandle)
    REGISTER(readModularChar)
    REGISTER(readModularShort)
    REGISTER(readText)
  END_REGISTER

  private:
    void readBit();
    void readBit2();
    void readBit3();
    void readBit16();
    void readBit32();
//    void readBit64();
    void readBitDouble();
    void readBitExtrusion();

    void readColour();
    void readHandle();

    void readModularChar();
    void readModularShort();

    void readRaw8();
    void readRaw16();
    void readRaw32();
    void readRawDouble();

    void readText();

  private:
    libredwgpp::DWGBuffer prepareBinaryBuffer(const UnicodeString& strBits, size_t offset);
END_UNITTEST
