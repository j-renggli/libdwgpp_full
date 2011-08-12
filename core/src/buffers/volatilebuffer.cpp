#include "../../include/buffers/volatilebuffer.h"

#include "../../includes.h"

namespace core {

////////////////////////////////////////////////////////////////

VolatileBuffer::VolatileBuffer(const Buffer* pBuffer, size_t uiSize) :
pBuffer_(pBuffer), uiSize_(uiSize), uiPos_(0)
{
  ASSERT(pBuffer_ != NULL || uiSize_ == 0);
}

////////////////////////////////////////////////////////////////

VolatileBuffer::VolatileBuffer(const IReadBuffer& buffer) :
pBuffer_(buffer.getBuffer()), uiSize_(buffer.getSize()), uiPos_(0)
{
  ASSERT(pBuffer_ != NULL || uiSize_ == 0);
}

////////////////////////////////////////////////////////////////

VolatileBuffer::VolatileBuffer(const VolatileBuffer& buffer) :
pBuffer_(buffer.getBuffer()), uiSize_(buffer.getSize()), uiPos_(0)
{
  ASSERT(pBuffer_ != NULL || uiSize_ == 0);
}

////////////////////////////////////////////////////////////////

void VolatileBuffer::readData(Buffer* pBuffer, size_t uiSize)
{
  ASSERT(uiPos_ + uiSize <= uiSize_);

  memcpy(pBuffer, &pBuffer_[uiPos_], uiSize);
  uiPos_ += uiSize;
}

////////////////////////////////////////////////////////////////

void VolatileBuffer::setPosition(size_t uiNewPos)
{
  if (uiNewPos > uiSize_)
    uiPos_ = uiSize_;
  else
    uiPos_ = uiNewPos;
}

////////////////////////////////////////////////////////////////

}
