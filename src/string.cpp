#include <include/string.h>

#include <unicode/ucnv.h>
#include <unicode/ucnv_err.h>

////////////////////////////////////////////////////////////////

namespace core {

////////////////////////////////////////////////////////////////

void String::deleteUTF8(const u_int8_t* pszText)
{
  delete[] pszText;
}

////////////////////////////////////////////////////////////////

const uint8_t* String::newUTF8(const UnicodeString& strText)
{
  int iSize = 2 * strText.length() + 1;
  u_int8_t* pszText;
  int32_t length = 0;

  pszText = new u_int8_t[iSize];

  UErrorCode status = U_ZERO_ERROR;
  UConverter* conv = ucnv_open("UTF-8", &status);
  if (U_FAILURE(status))
  {
    pszText[0] = '\0';
    return pszText;
  }

  length = ucnv_fromUChars(conv, (char*)pszText, iSize, strText.getBuffer(), strText.length(), &status);
  if (U_SUCCESS(status))
  {
    ucnv_close(conv);
    return pszText;
  }

  delete[] pszText;
  iSize = length + 1;
  pszText = new u_int8_t[iSize];

  status = U_ZERO_ERROR;
  ucnv_reset(conv);
  length = ucnv_fromUChars(conv, (char*)pszText, iSize, strText.getBuffer(), strText.length(), &status);
  ucnv_close(conv);
  if (U_SUCCESS(status))
  {
    return pszText;
  }
  delete[] pszText;

  pszText = NULL;
  return pszText;
}

////////////////////////////////////////////////////////////////

void String::deleteBuffer(const Buffer* pBuffer)
{
  delete[] pBuffer;
}

////////////////////////////////////////////////////////////////

const Buffer* String::compressToBuffer(const UnicodeString& strText, u_int32_t& uiLength)
{
  int iSize = 2 * strText.length() + 1;
  Buffer* pszText;
  uiLength = 0;
//  int32_t length = 0;
//
  pszText = new Buffer[iSize];

  UErrorCode status = U_ZERO_ERROR;
  UConverter* conv = ucnv_open("SCSU", &status);
  if (U_FAILURE(status))
  {
    pszText[0] = '\0';
    return pszText;
  }

  uiLength = ucnv_fromUChars(conv, (char*)pszText, iSize, strText.getBuffer(), strText.length(), &status);
  if (U_SUCCESS(status))
  {
    ucnv_close(conv);
    return pszText;
  }

  delete[] pszText;
  iSize = uiLength + 1;
  pszText = new u_int8_t[iSize];
  status = U_ZERO_ERROR;
  ucnv_reset(conv);
  uiLength = ucnv_fromUChars(conv, (char*)pszText, iSize, strText.getBuffer(), strText.length(), &status);
  ucnv_close(conv);
  if (U_SUCCESS(status))
  {
    return pszText;
  }
  delete[] pszText;

  pszText = NULL;
  return pszText;
}

////////////////////////////////////////////////////////////////

UnicodeString String::uncompressFromBuffer(const Buffer* pBuffer, u_int32_t uiLength)
{
  UErrorCode status = U_ZERO_ERROR;
  UConverter *conv = ucnv_open("SCSU", &status);
  if (U_FAILURE(status))
    return "";

  UChar* pTarget = new UChar[uiLength+1];
  UnicodeString strVal;
  /*int iLen =*/ ucnv_toUChars(conv, pTarget, uiLength, (char*)pBuffer, uiLength, &status);
  ucnv_close(conv);
  if (U_SUCCESS(status))
  {
    pTarget[uiLength] = 0x00;
    strVal = pTarget;
  }

  delete[] pTarget;
  return strVal;
}

////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////
