#include "../../include/buffers/membuffer.h"

#include "../../includes.h"

namespace core {

////////////////////////////////////////////////////////////////

MemBuffer::MemBuffer() :
pBuffer_(NULL),
maxSize_(0),
size_(0),
pos_(0)
{
}

////////////////////////////////////////////////////////////////

MemBuffer::MemBuffer(const IReadBuffer& buffer):
pBuffer_(NULL),
maxSize_(0),
size_(0),
pos_(0)
{
  *this = buffer;
}

////////////////////////////////////////////////////////////////

MemBuffer::MemBuffer(const MemBuffer& buffer):
pBuffer_(NULL),
maxSize_(0),
size_(0),
pos_(0)
{
  *this = buffer;
}

////////////////////////////////////////////////////////////////

MemBuffer::~MemBuffer()
{
  if (pBuffer_!= NULL)
    delete[] pBuffer_;
}

////////////////////////////////////////////////////////////////

MemBuffer& MemBuffer::operator=(const IReadBuffer& buffer)
{
  if (&buffer == this)
    return *this;

  delete pBuffer_;
  pBuffer_ = new Buffer[buffer.getSize()];
  memcpy(pBuffer_, buffer.getBuffer(), buffer.getSize());
  maxSize_ = buffer.getSize();
  size_ = maxSize_;
  pos_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////

MemBuffer& MemBuffer::operator=(const MemBuffer& buffer)
{
  if (&buffer == this)
    return *this;

  delete pBuffer_;
  pBuffer_ = new Buffer[buffer.getSize()];
  memcpy(pBuffer_, buffer.getBuffer(), buffer.getSize());
  maxSize_ = buffer.getSize();
  size_ = maxSize_;
  pos_ = 0;
  return *this;
}

////////////////////////////////////////////////////////////////

void MemBuffer::readData(Buffer* pBuffer, size_t size)
{
  ASSERT(pos_ + size <= size_);

  memcpy(pBuffer, &pBuffer_[pos_], size);
  pos_ += size;
}

////////////////////////////////////////////////////////////////

void MemBuffer::reserve(size_t newSize)
{
  if (newSize > maxSize_)
  {
    // Reallocate
    maxSize_ = newSize * 6 / 5; // Slightly larger
    Buffer* pNewBuffer = new Buffer[maxSize_];
    memcpy(pNewBuffer, pBuffer_, size_);
    delete[] pBuffer_;
    pBuffer_ = pNewBuffer;
  }
}

////////////////////////////////////////////////////////////////

void MemBuffer::resize(size_t newSize)
{
  reserve(newSize);

  size_ = newSize;
}

////////////////////////////////////////////////////////////////

void MemBuffer::setPosition(size_t newPos)
{
  if (newPos > size_)
    pos_ = size_;
  else
    pos_ = newPos;
}

////////////////////////////////////////////////////////////////

void MemBuffer::writeData(const Buffer* pBuffer, size_t size)
{
  resize(pos_ + size);
  memcpy(&pBuffer_[pos_], pBuffer, size);
  pos_ += size;
}

////////////////////////////////////////////////////////////////

}
