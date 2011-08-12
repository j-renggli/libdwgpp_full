#include "../include/iobuffer.h"

#include "../include/string.h"

namespace core {

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(bool& value)
{
  int8_t val = read<int8_t>();
  value = val != 0;
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(u_int8_t& value)
{
  readData(&value, 1);
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(int8_t& value)
{
  readData((u_int8_t*)(&value), 1);
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(u_int16_t& value)
{
  value = 0;
  Buffer buffer[2];
  readData(buffer, 2);
  for (int i = 0; i < 2; ++i)
  {
    value <<= 8;
    value |= buffer[1 - i];
  }
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(int16_t& value)
{
  value = 0;
  Buffer buffer[2];
  readData(buffer, 2);
  for (int i = 0; i < 2; ++i)
  {
    value <<= 8;
    value |= buffer[1 - i];
  }
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(u_int32_t& value)
{
  value = 0;
  Buffer buffer[4];
  readData(buffer, 4);
  for (int i = 0; i < 4; ++i)
  {
    value <<= 8;
    value |= buffer[3 - i];
  }
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(int32_t& value)
{
  value = 0;
  Buffer buffer[4];
  readData(buffer, 4);
  for (int i = 0; i < 4; ++i)
  {
    value <<= 8;
    value |= buffer[3 - i];
  }
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(u_int64_t& value)
{
  value = 0;
  Buffer buffer[8];
  readData(buffer, 8);
  for (int i = 0; i < 8; ++i)
  {
    value <<= 8;
    value |= buffer[7 - i];
  }
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(int64_t& value)
{
  value = 0;
  Buffer buffer[8];
  readData(buffer, 8);
  for (int i = 0; i < 8; ++i)
  {
    value <<= 8;
    value |= buffer[7 - i];
  }
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(float& value)
{
  //TODO : THIS IS NOT SAFE AT ALL !!!
  readData((Buffer*)(&value), sizeof(float));
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(float& value, bool isBigEndian)
{
  readValue(value);
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(double& value)
{
  //TODO : THIS IS NOT SAFE AT ALL !!!
  readData((Buffer*)(&value), sizeof(double));
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(double& value, bool isBigEndian)
{
  readValue(value);
}

////////////////////////////////////////////////////////////////

template <>
void IReadBuffer::readValue(UnicodeString& value)
{
  uint32_t uiLen = read<uint32_t>();
  Buffer* pszBuffer = new Buffer[uiLen];
  readData(pszBuffer, uiLen);
  value = core::String::uncompressFromBuffer(pszBuffer, uiLen);
  delete[] pszBuffer;
}

////////////////////////////////////////////////////////////////
// Write
////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const u_int8_t& value, bool isBigEndian)
{
  writeData(&value, 1);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const int8_t& value, bool isBigEndian)
{
  writeData((u_int8_t*)&value, 1);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const u_int16_t& value, bool isBigEndian)
{
  u_int16_t val = value;

  Buffer buffer[2];
  for (int i = 0; i < 2; ++i)
  {
    buffer[i] = val & 0xFF;
    val >>= 8;
  }

  if (isBigEndian)
    std::swap(buffer[0], buffer[1]);

  writeData(buffer, 2);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const int16_t& value, bool isBigEndian)
{
  int16_t val = value;

  Buffer buffer[2];
  for (int i = 0; i < 2; ++i)
  {
    buffer[i] = val & 0xFF;
    val >>= 8;
  }

  if (isBigEndian)
    std::swap(buffer[0], buffer[1]);

  writeData(buffer, 2);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const u_int32_t& value, bool isBigEndian)
{
  u_int32_t val = value;

  Buffer buffer[4];
  for (int i = 0; i < 4; ++i)
  {
    buffer[i] = val & 0xFF;
    val >>= 8;
  }

  if (isBigEndian)
  {
    std::swap(buffer[0], buffer[3]);
    std::swap(buffer[1], buffer[2]);
  }

  writeData(buffer, 4);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const int32_t& value, bool isBigEndian)
{
  int32_t val = value;

  Buffer buffer[4];
  for (int i = 0; i < 4; ++i)
  {
    buffer[i] = val & 0xFF;
    val >>= 8;
  }

  if (isBigEndian)
  {
    std::swap(buffer[0], buffer[3]);
    std::swap(buffer[1], buffer[2]);
  }

  writeData(buffer, 4);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const u_int64_t& value, bool isBigEndian)
{
  u_int64_t val = value;

  Buffer buffer[8];
  for (int i = 0; i < 8; ++i)
  {
    buffer[i] = val & 0xFF;
    val >>= 8;
  }

  if (isBigEndian)
  {
    std::swap(buffer[0], buffer[7]);
    std::swap(buffer[1], buffer[6]);
    std::swap(buffer[2], buffer[5]);
    std::swap(buffer[3], buffer[4]);
  }

  writeData(buffer, 8);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const int64_t& value, bool isBigEndian)
{
  int64_t val = value;

  Buffer buffer[8];
  for (int i = 0; i < 8; ++i)
  {
    buffer[i] = val & 0xFF;
    val >>= 8;
  }

  if (isBigEndian)
  {
    std::swap(buffer[0], buffer[7]);
    std::swap(buffer[1], buffer[6]);
    std::swap(buffer[2], buffer[5]);
    std::swap(buffer[3], buffer[4]);
  }

  writeData(buffer, 8);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const bool& value, bool isBigEndian)
{
  write<int8_t>(value ? 1 : 0);
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const float& value, bool isBigEndian)
{
  //TODO : THIS IS NOT SAFE AT ALL !!!
  writeData((Buffer*)(&value), sizeof(float));
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const double& value, bool isBigEndian)
{
  //TODO : THIS IS NOT SAFE AT ALL !!!
  writeData((Buffer*)(&value), sizeof(double));
}

////////////////////////////////////////////////////////////////

template <>
void IWriteBuffer::write(const UnicodeString& value, bool isBigEndian)
{
  uint32_t uiLen;
  const core::Buffer* pszText = core::String::compressToBuffer(value, uiLen);
  write(uiLen, isBigEndian);
  writeData(pszText, uiLen);
  core::String::deleteBuffer(pszText);
}

////////////////////////////////////////////////////////////////

}
