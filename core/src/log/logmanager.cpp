#include "include/log/logmanager.h"

#include "include/log/simplefiledisplay.h"

namespace core {

////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
// Log manager
////////////////////////////////////////////////////////////////

LogManager gLogManager;

////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////

LogManager::LogManager() :
pLock_(NULL)
{
  //ctor
}

////////////////////////////////////////////////////////////////

LogManager::~LogManager()
{
}

////////////////////////////////////////////////////////////////

void LogManager::activateTrace(const boost::filesystem::path& pathFile, const ELevel eLevelMin)
{
  boost::shared_ptr<IDisplay> ptrTrace(new SimpleFileDisplay(pathFile, eLevelMin));

  registerDisplay(ptrTrace);
  // Trace functions calls into a file
  LOG_DEBUG("Starting trace...");
}

////////////////////////////////////////////////////////////////

void LogManager::registerDisplay(const DisplayPtr& ptrDisplay)
{
  if (ptrDisplay == NULL)
    return;

  core::SimpleLock lock(mutex_);

  vDisplays_.push_back(ptrDisplay);
}

////////////////////////////////////////////////////////////////

Message& LogManager::startLog(ELevel eLevel, const std::string& strFile, int iLine)
{
  core::SimpleLock* pLock = new core::SimpleLock(mutex_);
  assert(pLock_ == NULL); // Can't use ASSERT here
  pLock_ = pLock;

  msg_.reset(eLevel, strFile, iLine);
  return msg_;
}

////////////////////////////////////////////////////////////////

void LogManager::stopLog()
{
  if (pLock_ == NULL)
    return;

//  assert(vfctDisplay_.size() == vLevels_.size());
  for (size_t iDisplay = 0; iDisplay < vDisplays_.size(); ++iDisplay)
  {
    assert(vDisplays_[iDisplay]!= NULL); // Can't use ASSERT here
    vDisplays_[iDisplay]->display(msg_);
  }

  core::SimpleLock* pLock = pLock_;
  pLock_ = NULL;
  delete pLock;
}

////////////////////////////////////////////////////////////////

}
