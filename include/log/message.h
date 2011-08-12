#pragma once

// Local
#include "../../includes.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace core {

////////////////////////////////////////////////////////////////

class Message
{
  private:
    /// Time of message's creation
    boost::posix_time::ptime msgTime_;

    /// Priority level
    int iLevel_;

    /// Originating file
    boost::filesystem::path pathFile_;

    /// Originating line
    int iLine_;

    /// Message
    std::stringstream ssMsg_;
  
    /// Default flags
    std::ios_base::fmtflags flags_;

  public:
    Message()
    {
      flags_ = ssMsg_.flags();
    }
    
  public:
    /// Reset the message to accept next one
    void reset(int iLevel, const boost::filesystem::path& pathFile, int iLine)
    {
      msgTime_ = boost::posix_time::second_clock::local_time();
      iLevel_ = iLevel;
      pathFile_ = pathFile;
      iLine_ = iLine;
      ssMsg_.str("");
      ssMsg_.flags(flags_);
    }

    const boost::filesystem::path& getFile() const { return pathFile_; }

    const int getLevel() const { return iLevel_; }

    const int getLine() const { return iLine_; }

    const boost::posix_time::ptime& getTime() const { return msgTime_; }

    const std::string getMessage() const { return ssMsg_.str(); }

    /// Add something to the message, return the message for further writing
    template<class T> Message& operator<<(const T& t)
    {
      ssMsg_ << t;
      return *this;
    }

    /// Overloaded operator for booleans
    Message& operator<<(const bool& v)
    {
      if (v)
        ssMsg_ << "TRUE";
      else
        ssMsg_ << "FALSE";
      return *this;
    }

    /// Overloaded operator for result codes
    Message& operator<<(const ResultCode& rc)
    {
      if (rc.isFailure())
        ssMsg_ << "Failure [" << (rc.getValue() & rc.eValueMask) << "]";
      else if (rc.isWarning())
        ssMsg_ << "Warning [" << (rc.getValue() & rc.eValueMask) << "]";
      else if (rc.isSuccess())
        ssMsg_ << "Success";
      else
        ssMsg_ << "Result code [" << rc.getValue() << "]";
      return *this;
    }

    /// Overloaded operator for vectors
    template<class T> Message& operator<<(const std::vector<T>& v)
    {
      ssMsg_ << "[";
      for (size_t i = 0; i < v.size(); ++i)
      {
        if (i > 0)
          ssMsg_ << ", ";
        ssMsg_ << v[i];
      }
      ssMsg_ << "]";
      return *this;
    }
};

////////////////////////////////////////////////////////////////

}
