#pragma once

#include "filebuffer.h"

namespace core {

class TemporaryFileBuffer : virtual public FileReadWriteBuffer
{
  ////////////////////////////////////////////////////////////////
  // Statics
  ////////////////////////////////////////////////////////////////
  public:
    boost::shared_ptr<TemporaryFileBuffer> createTemporaryFile();

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  private:
    boost::filesystem::path pathFile_;

    /// File descriptor
    int fd_;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    TemporaryFileBuffer();

    virtual ~TemporaryFileBuffer();

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    /// Get file name on disk
    const boost::filesystem::path& getPath() const { return pathFile_; }

//    /// Serialise the buffer to the file on disk
//    ResultCode serialise(const boost::filesystem::path& pathFile);
};

}
