#pragma once

#include "../iobuffer.h"

namespace core {

class MemBuffer : virtual public IReadWriteBuffer
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////
  public:
    typedef uint8_t Buffer;

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  private:
    /// The buffer
    Buffer* pBuffer_;

    /// The maximum size of the buffer
    size_t maxSize_;

    /// The current size of the buffer
    size_t size_;

    /// The current position
    size_t pos_;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    MemBuffer();
    MemBuffer(const IReadBuffer& buffer);
    MemBuffer(const MemBuffer& buffer);

    virtual ~MemBuffer();

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////
  public:
    // Assignment
    MemBuffer& operator=(const IReadBuffer& buffer);
    MemBuffer& operator=(const MemBuffer& buffer);

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    /// Clear the buffer
    void clear() { size_ = 0; pos_ = 0; }

    /// Is the buffer empty ?
    virtual bool isEmpty() const { return size_ == 0; }

    /// Direct access to buffer
    Buffer* getBuffer() { return pBuffer_; }
    const Buffer* getBuffer() const { return pBuffer_; }

    /// Get the position of the buffer's cursor
    virtual size_t getPosition() const { return pos_; }

    /// Read N characters
    virtual void readData(Buffer* pBuffer, size_t size);

    /// Reserve enough space for the buffer without resizing it
    virtual void reserve(size_t newSize);

    /// Resize the buffer : max size might be larger to avoid too many reallocations
    void resize(size_t newSize);

    /// Set the position of the buffer's cursor
    /// @param uiNewPos the position; uiSize if uiNewPos >= uiSize
    void setPosition(size_t newPos);

    /// Get the current size of the buffer
    virtual size_t getSize() const { return size_; }

    /// Write N characters
    virtual void writeData(const Buffer* pBuffer, size_t size);
};

}
