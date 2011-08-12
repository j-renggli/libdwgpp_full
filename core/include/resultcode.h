#pragma once

#include <sys/types.h>

namespace core {

class ResultCode
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////
  public:
    enum ELevel
    {
      eFatal      = 0x60000000,
      eException  = 0x50000000,
      eError      = 0x40000000,
      eWarning    = 0x08000000,

      eErrorMask  = 0x78000000,
      eValueMask  = 0x00FFFFFF,

      eSuccess    = 0x00
    };

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  private:
    /// Value
    int32_t iValue_;

    /// Explanatory text
    //UnicodeString strText_;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    ResultCode(const ResultCode& rC) : iValue_(rC.iValue_) {}
    ResultCode(int32_t iValue) : iValue_(iValue) {}
    ResultCode(const ELevel level, int32_t value) : iValue_(level | value) {}

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////
  public:
    /// Chain, remembering worst value
    ResultCode& operator&=(const ResultCode& rC) { iValue_ |= (rC.iValue_ & eErrorMask); return *this; }

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    int32_t getValue() const { return iValue_; }
    bool isSuccess() const { return !(iValue_ & eError); }
    bool isFailure() const { return (iValue_ & eError); }
    bool isWarning() const { return (iValue_ & eWarning); }
};

extern ResultCode rcFailure;
extern ResultCode rcSuccess;

}
