#pragma once

#include "../../includes.h"

namespace core {

class VolatileBuffer : virtual public IReadBuffer
{
  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  private:
    /// The volatile buffer
    const Buffer* pBuffer_;

    /// The size of the buffer
    const size_t uiSize_;

    /// The current position
    size_t uiPos_;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    VolatileBuffer(const Buffer* pBuffer, size_t uiSize);
    VolatileBuffer(const IReadBuffer& buffer);
    VolatileBuffer(const VolatileBuffer& buffer);

    virtual ~VolatileBuffer() {}

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    /// Is the buffer empty ?
    /// Return true if size() == 0
    virtual bool isEmpty() const { return uiSize_ == 0; }

    /// Direct access to buffer
    virtual const Buffer* getBuffer() const { return pBuffer_; }

    /// Get the position of the buffer's cursor
    virtual size_t getPosition() const { return uiPos_; }

    /// Read N characters
    virtual void readData(Buffer* pBuffer, size_t uiSize);

    /// Set the position of the buffer's cursor
    /// @param uiNewPos the position; uiSize if uiNewPos >= uiSize
    void setPosition(size_t uiNewPos);

    /// Get the current size of the buffer
    virtual size_t getSize() const { return uiSize_; }
};

}
