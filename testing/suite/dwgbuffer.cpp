#include "dwgbuffer.h"

#include <libredwgpp/parser/dwgbuffer.h>
#include <libredwgpp/parser/handle.h>
#include <libredwgpp/parser/version.h>

////////////////////////////////////////////////////////////////

void DWGBuffer::readBit()
{
  for (int offset = 0; offset < 8; ++offset)
  {
    libredwgpp::DWGBuffer buffer1 = prepareBinaryBuffer("0", offset);
    libredwgpp::DWGBuffer buffer2 = prepareBinaryBuffer("1", offset);

    bool b1 = buffer1.readBit();
    bool b2 = buffer2.readBit();
    ASSERT_EQUAL(b1, false);
    ASSERT_EQUAL(b2, true);
  }
}

////////////////////////////////////////////////////////////////

void DWGBuffer::readBit2()
{
  for (int offset = 0; offset < 8; ++offset)
  {
    libredwgpp::DWGBuffer buffer1 = prepareBinaryBuffer("00", offset);
    libredwgpp::DWGBuffer buffer2 = prepareBinaryBuffer("01", offset);
    libredwgpp::DWGBuffer buffer3 = prepareBinaryBuffer("10", offset);
    libredwgpp::DWGBuffer buffer4 = prepareBinaryBuffer("11", offset);

    ASSERT_EQUAL(size_t(buffer1.readBit2()), 0);
    ASSERT_EQUAL(size_t(buffer2.readBit2()), 1);
    ASSERT_EQUAL(size_t(buffer3.readBit2()), 2);
    ASSERT_EQUAL(size_t(buffer4.readBit2()), 3);
  }
}

////////////////////////////////////////////////////////////////

void DWGBuffer::readBit3()
{
  // TODO !!! Not sure what this should be...
  for (int offset = 0; offset < 8; ++offset)
  {
    libredwgpp::DWGBuffer buffer1 = prepareBinaryBuffer("0", offset);
    libredwgpp::DWGBuffer buffer2 = prepareBinaryBuffer("10", offset);
    libredwgpp::DWGBuffer buffer3 = prepareBinaryBuffer("110", offset);
    libredwgpp::DWGBuffer buffer4 = prepareBinaryBuffer("111", offset);

    ASSERT_EQUAL(size_t(buffer1.readBit3()), 0);
    ASSERT_EQUAL(size_t(buffer2.readBit3()), 2);
    ASSERT_EQUAL(size_t(buffer3.readBit3()), 6);
    ASSERT_EQUAL(size_t(buffer4.readBit3()), 7);
  }
}

////////////////////////////////////////////////////////////////

void DWGBuffer::readBit16()
{
  for (int offset = 0; offset < 8; ++offset)
  {
    libredwgpp::DWGBuffer buffer1 = prepareBinaryBuffer("001100011011110100", offset);
    libredwgpp::DWGBuffer buffer2 = prepareBinaryBuffer("0110010111", offset);
    libredwgpp::DWGBuffer buffer3 = prepareBinaryBuffer("10", offset);
    libredwgpp::DWGBuffer buffer4 = prepareBinaryBuffer("11", offset);

    ASSERT_EQUAL(buffer1.readBit16(), 0xF4C6);
    ASSERT_EQUAL(buffer2.readBit16(), 0x97);
    ASSERT_EQUAL(buffer3.readBit16(), 0);
    ASSERT_EQUAL(buffer4.readBit16(), 256);
  }
}

////////////////////////////////////////////////////////////////

void DWGBuffer::readBit32()
{
  for (int offset = 0; offset < 8; ++offset)
  {
    libredwgpp::DWGBuffer buffer1 = prepareBinaryBuffer("0011000110111101001001011110000001", offset);
    libredwgpp::DWGBuffer buffer2 = prepareBinaryBuffer("0110010111", offset);
    libredwgpp::DWGBuffer buffer3 = prepareBinaryBuffer("10", offset);
    libredwgpp::DWGBuffer buffer4 = prepareBinaryBuffer("11", offset);

    ASSERT_EQUAL(buffer1.readBit32(), 0x8197F4C6);
    ASSERT_EQUAL(buffer2.readBit32(), 0x97);
    ASSERT_EQUAL(buffer3.readBit32(), 0);
    ASSERT_THROWING(buffer4.readBit32());
  }
}

////////////////////////////////////////////////////////////////

//void DWGBuffer::readBit64()
//{
//}

////////////////////////////////////////////////////////////////

void DWGBuffer::readBitDouble()
{
  for (int offset = 0; offset < 8; ++offset)
  {
    libredwgpp::DWGBuffer buffer1 = prepareBinaryBuffer("000000000000000000000011011011010101101011101010000000000001000010", offset);
    libredwgpp::DWGBuffer buffer2 = prepareBinaryBuffer("01", offset);
    libredwgpp::DWGBuffer buffer3 = prepareBinaryBuffer("10", offset);
    libredwgpp::DWGBuffer buffer4 = prepareBinaryBuffer("11", offset);

    ASSERT_EQUAL(buffer1.readBitDouble(), 8943138465.625);
    ASSERT_EQUAL(buffer2.readBitDouble(), 1.);
    ASSERT_EQUAL(buffer3.readBitDouble(), 0.);
    ASSERT_THROWING(buffer4.readBitDouble());

    // TODO: read with default value !!!
  }
}

////////////////////////////////////////////////////////////////

void DWGBuffer::readBitExtrusion()
{
  double x, y, z;
  for (int offset = 0; offset < 8; ++offset)
  {
    libredwgpp::DWGBuffer bufferV14 = prepareBinaryBuffer("0000000000000000000000110110110101011010111010100000000000010000100110", offset);
    bufferV14.readBitExtrusion(libredwgpp::Version::R14, x, y, z);
    ASSERT_EQUAL(x, 8943138465.625);
    ASSERT_EQUAL(y, 1.);
    ASSERT_EQUAL(z, 0.);

    libredwgpp::DWGBuffer bufferV2000T = prepareBinaryBuffer("1", offset);
    bufferV2000T.readBitExtrusion(libredwgpp::Version::R2000, x, y, z);
    ASSERT_EQUAL(x, 0.);
    ASSERT_EQUAL(y, 0.);
    ASSERT_EQUAL(z, 1.);

    libredwgpp::DWGBuffer bufferV2000F = prepareBinaryBuffer("01001000000000000000000000011011011010101101011101010000000000001000010", offset);
    bufferV2000F.readBitExtrusion(libredwgpp::Version::R2007, x, y, z);
    ASSERT_EQUAL(x, 0.);
    ASSERT_EQUAL(y, 1.);
    ASSERT_EQUAL(z, 8943138465.625);
  }
}

////////////////////////////////////////////////////////////////

void DWGBuffer::readColour()
{
  libredwgpp::Colour::initialiseIndexMap();

  for (int offset = 0; offset < 8; ++offset)
  {
    libredwgpp::DWGBuffer bufferV14 = prepareBinaryBuffer("0100000001", offset);
    libredwgpp::Colour col14 = bufferV14.readColour(libredwgpp::Version::R14);
    ASSERT_EQUAL(size_t(col14.getR()), 255);
    ASSERT_EQUAL(size_t(col14.getG()), 0);
    ASSERT_EQUAL(size_t(col14.getB()), 0);
    ASSERT_EQUAL(size_t(col14.getA()), 255);

    // TODO: 2004 entity !
//    libredwgpp::DWGBuffer bufferV2004T = prepareBinaryBuffer("1", offset);
//    Colour colEntity = bufferV2004T.readColour(libredwgpp::Version::R2004, true);
//    ASSERT_EQUAL(colEntity.getR(), 255);
//    ASSERT_EQUAL(colEntity.getG(), 0);
//    ASSERT_EQUAL(colEntity.getB(), 0);
//    ASSERT_EQUAL(colEntity.getA(), 255);

    libredwgpp::DWGBuffer bufferV2004F = prepareBinaryBuffer("10000101010101111111100000000000000000000000", offset);
    libredwgpp::Colour col2007 = bufferV2004F.readColour(libredwgpp::Version::R2007, false);
    ASSERT_EQUAL(size_t(col2007.getR()), 128);
    ASSERT_EQUAL(size_t(col2007.getG()), 127);
    ASSERT_EQUAL(size_t(col2007.getB()), 85);
    ASSERT_EQUAL(size_t(col2007.getA()), 255);
  }
}

////////////////////////////////////////////////////////////////

void DWGBuffer::readHandle()
{
  for (int offset = 0; offset < 8; ++offset)
  {
    libredwgpp::DWGBuffer buffer = prepareBinaryBuffer("101100101011010000100011", offset); // Code B, Size 2 : 0x23B4

    libredwgpp::Handle h = buffer.readHandle();

//    ASSERT_EQUAL(h.getCode(), 0xB);
//    ASSERT_EQUAL(h.getSize(), 2);
//    ASSERT_EQUAL(h.getValue(), 0x23B4);
    ASSERT_EQUAL(h.code_, 0xB);
    ASSERT_EQUAL(h.value_, 0xB423);
  }
}

////////////////////////////////////////////////////////////////

void DWGBuffer::readRaw8()
{
  for (int offset = 0; offset < 8; ++offset)
  {
    libredwgpp::DWGBuffer buffer = prepareBinaryBuffer("10100101", offset);
    ASSERT_EQUAL(size_t(buffer.readRaw8()), 0xA5);
  }
}

////////////////////////////////////////////////////////////////

void DWGBuffer::readRaw16()
{
  for (int offset = 0; offset < 8; ++offset)
  {
    libredwgpp::DWGBuffer buffer = prepareBinaryBuffer("1100011011110100", offset);
    ASSERT_EQUAL(buffer.readRaw16(), 0xF4C6);
  }
}

////////////////////////////////////////////////////////////////

void DWGBuffer::readRaw32()
{
  for (int offset = 0; offset < 8; ++offset)
  {
    libredwgpp::DWGBuffer buffer = prepareBinaryBuffer("11000110111101000011110010001101", offset);
    ASSERT_EQUAL(buffer.readRaw32(), 0x8D3CF4C6);
  }
}

////////////////////////////////////////////////////////////////

void DWGBuffer::readRawDouble()
{
  for (int offset = 0; offset < 8; ++offset)
  {
    libredwgpp::DWGBuffer buffer = prepareBinaryBuffer("0000000000000000000011011011010101101011101010000000000001000010", offset);
    ASSERT_EQUAL(buffer.readRawDouble(), 8943138465.625);
  }
}

////////////////////////////////////////////////////////////////

void DWGBuffer::readText()
{
  for (int offset = 0; offset < 8; ++offset)
  {
    libredwgpp::DWGBuffer bufferASCII = prepareBinaryBuffer("010000010001001111011010110010000100000000", offset);
    const UnicodeString strText = bufferASCII.readText(libredwgpp::Version::R2004);
    const UnicodeString strExpected = "Ok!";
    ASSERT_EQUAL(strText.length(), strExpected.length());
    ASSERT_EQUAL(strText, strExpected);
    // TODO: UTF16 (2007+)
  }
}

////////////////////////////////////////////////////////////////

void DWGBuffer::readModularChar()
{
  for (int offset = 0; offset < 8; ++offset)
  {
    libredwgpp::DWGBuffer buffer1 = prepareBinaryBuffer("01011100", offset);
    libredwgpp::DWGBuffer buffer2 = prepareBinaryBuffer("1101110001110100", offset);
    libredwgpp::DWGBuffer buffer3 = prepareBinaryBuffer("110111001111010000011001", offset);
    libredwgpp::DWGBuffer buffer4 = prepareBinaryBuffer("11011100111101001001100101110001", offset);

    int32_t i1 = buffer1.readModularChar();
    int32_t i2 = buffer2.readModularChar();
    int32_t i3 = buffer3.readModularChar();
    int32_t i4 = buffer4.readModularChar();

    ASSERT_EQUAL(i1, -0x1C);
    ASSERT_EQUAL(i2, -0x1A5C);
    ASSERT_EQUAL(i3, 0x67A5C);
    ASSERT_EQUAL(i4, -0x6267A5C);
  }
}

////////////////////////////////////////////////////////////////

void DWGBuffer::readModularShort()
{
  for (int offset = 0; offset < 8; ++offset)
  {
    libredwgpp::DWGBuffer buffer1 = prepareBinaryBuffer("1101110001010111", offset);
    libredwgpp::DWGBuffer buffer2 = prepareBinaryBuffer("11011100110101110110001000110011", offset);

    int32_t i1 = buffer1.readModularShort();
    int32_t i2 = buffer2.readModularShort();

    ASSERT_EQUAL(i1, -0x17DC);
    ASSERT_EQUAL(i2, 0x19B157DC);
  }
}

////////////////////////////////////////////////////////////////

libredwgpp::DWGBuffer DWGBuffer::prepareBinaryBuffer(const UnicodeString& strBits, size_t offset)
{
  core::MemBuffer buffer;
  size_t pos = offset;
  uint8_t c; // Initialised with "random" value is nice to have
  for (int i = 0; i < strBits.length(); ++i)
  {
    if (pos == 8)
    {
      buffer.write(c);
      pos = 0;
    }

    c <<= 1;
    if (strBits[i] == '0')
      c &= 0xFE;
    else
      c |= 0x01;
    ++pos;
  }

  c <<= (8 - pos);
  buffer.write(c);

  libredwgpp::DWGBuffer dwg(buffer);
  for (size_t i = 0; i < offset; ++i)
    dwg.readBit();
  return dwg;
}

////////////////////////////////////////////////////////////////
