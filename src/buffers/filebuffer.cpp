#include "../../includes.h"

namespace core {

////////////////////////////////////////////////////////////////

FileReadBuffer::FileReadBuffer() :
pBuffer_(NULL),
uiSize_(0),
uiPos_(0)
{
}

////////////////////////////////////////////////////////////////

FileReadBuffer::~FileReadBuffer()
{
  if (pBuffer_ != NULL)
    delete[] pBuffer_;
}

////////////////////////////////////////////////////////////////

void FileReadBuffer::readData(Buffer* pBuffer, size_t uiSize)
{
  ASSERT(uiPos_ + uiSize <= uiSize_);
  if (uiPos_ + uiSize > uiSize_)
    throw std::domain_error("Reading too far in the file");

  memcpy(pBuffer, &pBuffer_[uiPos_], uiSize);
  uiPos_ += uiSize;
}

////////////////////////////////////////////////////////////////

ResultCode FileReadBuffer::restore(const boost::filesystem::path& pathFile)
{
  if (!exists(pathFile) || !is_regular(pathFile))
  {
    return rcFailure;
  }

  std::ifstream fileIn(pathFile.native_file_string().c_str(), std::ios::binary);
  if (!fileIn)
  {
    return rcFailure;
  }
  uiPos_ = 0;
  uiSize_ = 4096;
  char pTemp[4096];
  while (true)
  {
    fileIn.read(pTemp, uiSize_);
    if (fileIn.bad())
    {
      return rcFailure;
    }

    size_t uiCount = fileIn.gcount();
    if (uiCount == 0)
      break;
    Buffer* pNewBuffer = new Buffer[uiPos_ + uiCount];
    memcpy(pNewBuffer, pBuffer_, uiPos_);
    memcpy(pNewBuffer+uiPos_, pTemp, uiCount);
    delete[] pBuffer_;
    pBuffer_ = pNewBuffer;
    uiPos_ += uiCount;

    if (uiCount < uiSize_)
      break;
  }

  uiSize_ = uiPos_;
  uiPos_ = 0;

  fileIn.close();

  return rcSuccess;
}

////////////////////////////////////////////////////////////////

void FileReadBuffer::setPosition(size_t uiNewPos)
{
  if (uiNewPos > uiSize_)
    uiPos_ = uiSize_;
  else
    uiPos_ = uiNewPos;
}

////////////////////////////////////////////////////////////////
// File read & write
////////////////////////////////////////////////////////////////

FileReadWriteBuffer::FileReadWriteBuffer(const boost::filesystem::path& filePath) :
MemBuffer(),
pathFile_(filePath)
{
}

////////////////////////////////////////////////////////////////

ResultCode FileReadWriteBuffer::changePath(const boost::filesystem::path& filePath)
{
  pathFile_ = filePath;

  return rcSuccess;
}

////////////////////////////////////////////////////////////////

ResultCode FileReadWriteBuffer::restore()
{
  if (!exists(pathFile_) || !is_regular(pathFile_))
  {
    return rcFailure;
  }

  std::ifstream fileIn(pathFile_.native_file_string().c_str(), std::ios::binary);
  if (!fileIn)
  {
    return rcFailure;
  }

  setPosition(0);
  const size_t size = 4096;
  resize(size);

  char pTemp[size];
  while (true)
  {
    fileIn.read(pTemp, size);
    if (fileIn.bad())
    {
      return rcFailure;
    }

    size_t uiCount = fileIn.gcount();
    if (uiCount == 0)
      break;

    writeData((const Buffer*)pTemp, uiCount);

    if (uiCount < size)
      break;
  }

  setPosition(0);

  fileIn.close();

  return rcSuccess;
}

////////////////////////////////////////////////////////////////

ResultCode FileReadWriteBuffer::serialise()
{
  std::ofstream fileOut(pathFile_.native_file_string().c_str(), std::ios::binary);
  if (!fileOut)
  {
    return rcFailure;
  }

  fileOut.write((const char*)getBuffer(), getSize());

  fileOut.close();

  return rcSuccess;
}

////////////////////////////////////////////////////////////////

}
