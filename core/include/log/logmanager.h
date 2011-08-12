#pragma once

// Local
#include "../../includes.h"
#include "../lock.h"
#include "message.h"

// Util
#define LOG_DEBUG(a) core::gLogManager.startLog(core::LogManager::eDebug, __FILE__, __LINE__) << a; core::gLogManager.stopLog();
#define LOG_TRACE(a) core::gLogManager.startLog(core::LogManager::eTrace, __FILE__, __LINE__) << a; core::gLogManager.stopLog();
#define LOG_PRIVATE(a) core::gLogManager.startLog(core::LogManager::ePrivate, __FILE__, __LINE__) << a; core::gLogManager.stopLog();
#define LOG_NON_FATAL(a) core::gLogManager.startLog(core::LogManager::eNonFatal, __FILE__, __LINE__) << a; core::gLogManager.stopLog();
#define LOG_WARNING(a) core::gLogManager.startLog(core::LogManager::eWarning, __FILE__, __LINE__) << a; core::gLogManager.stopLog();
#define LOG_ERROR(a) core::gLogManager.startLog(core::LogManager::eError, __FILE__, __LINE__) << a; core::gLogManager.stopLog();
#define LOG_ASSERT(a) core::gLogManager.startLog(core::LogManager::eAssert, __FILE__, __LINE__) << a; core::gLogManager.stopLog();

namespace core {

////////////////////////////////////////////////////////////////

class IDisplay;

////////////////////////////////////////////////////////////////

class LogManager
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////
  public:
    enum ELevel
    {
      eDebug    = 0,
      eTrace    = 10,
      ePrivate  = 20,
      eNonFatal = 30,
      eWarning  = 40,
      eError    = 50,
      eAssert   = 60
    };

    typedef boost::shared_ptr<IDisplay> DisplayPtr;

  ////////////////////////////////////////////////////////////////
  // Class members
  ////////////////////////////////////////////////////////////////
  private:
    /// File to output trace to
    //std::ofstream fileTrace_;

    /// Filter for each output
    //std::vector<ELevel> vLevels_;

    /// The message to log
    Message msg_;

    /// All active outputs
    std::vector<DisplayPtr> vDisplays_;

    /// Lock must be shared between two functions...
    core::SimpleLock* pLock_;

    /// Mutex to write to file
    core::Mutex mutex_;

  ////////////////////////////////////////////////////////////////
  // Class Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    LogManager();
    virtual ~LogManager();

  ////////////////////////////////////////////////////////////////
  // Class functions
  ////////////////////////////////////////////////////////////////
  private:
    //void trace(const Message& msg);

  public:
    /// Start logging a message
    /// @return A new write-enabled message.
    /// Do not call this function directly. Use one of the macros instead
    Message& startLog(const ELevel eLevel, const std::string& sFile, int iLine);

    /// Stop logging a message (must be called exactly once after startLog). Makes message write-locked
    /// Do not call this function directly. Use one of the macros instead
    void stopLog();

    /// Register a new display output
    void registerDisplay(const DisplayPtr& ptrDisplay);

    /// Activate basic trace in simple text file
    /// @param pathFile the file to write to
    /// @param eLevelMin the minimal level of write events to be traced
    void activateTrace(const boost::filesystem::path& pathFile, const ELevel eLevelMin);
};

extern LogManager gLogManager;

}
