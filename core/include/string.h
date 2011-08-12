#ifndef CORE_INCLUDE_STRING_H
#define CORE_INCLUDE_STRING_H

#include "../includes.h"

namespace core {

class String
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////
  // Statics
  ////////////////////////////////////////////////////////////////
  public:
    static void deleteUTF8(const u_int8_t* pszText);
    static const uint8_t* newUTF8(const UnicodeString& strText);

    static void deleteBuffer(const Buffer* pBuffer);
    static const Buffer* compressToBuffer(const UnicodeString& strText, u_int32_t& uiLength);
    static UnicodeString uncompressFromBuffer(const Buffer* pBuffer, u_int32_t uiLength);
};

}

#endif
