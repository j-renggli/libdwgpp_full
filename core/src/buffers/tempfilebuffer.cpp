#include "../../include/buffers/tempfilebuffer.h"

namespace core {

////////////////////////////////////////////////////////////////

boost::shared_ptr<TemporaryFileBuffer> TemporaryFileBuffer::createTemporaryFile()
{
  try
  {
    boost::shared_ptr<TemporaryFileBuffer> ptrFile(new TemporaryFileBuffer);
    return ptrFile;
  }
  catch (const std::exception&)
  {
    return boost::shared_ptr<TemporaryFileBuffer>();
  }
}

////////////////////////////////////////////////////////////////

TemporaryFileBuffer::TemporaryFileBuffer()
{
  char pszName[16] = "/tmp/lphiXXXXXX";
  fd_ = mkstemp(pszName);

  pathFile_ = pszName;
}

////////////////////////////////////////////////////////////////

TemporaryFileBuffer::~TemporaryFileBuffer()
{
  close(fd_);
  remove(pathFile_);
}

////////////////////////////////////////////////////////////////

}
