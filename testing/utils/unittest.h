#pragma once

// STL
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <boost/shared_ptr.hpp>
#include <unicode/unistr.h>

class UnitTestException
{
  private:
    std::stringstream ssMsg_;

  public:
    UnitTestException(int iLine, std::string strMsg)
    {
      ssMsg_ << "Assert failed on line " << iLine << " : " << strMsg;
    }

    UnitTestException(const UnitTestException& ute)
    {
      ssMsg_ << ute.ssMsg_.str();
    }

    ~UnitTestException() {}

    std::string what() const
    {
      return ssMsg_.str();
    }
};

class UnitTest
{
  private:
    const std::string strName_;

  protected:
    UnitTest(const std::string strName) : strName_(strName) {}
  public:
    virtual ~UnitTest() {}

  public:
    virtual void Run(const std::set<std::string>&) = 0;

    const std::string& GetName() { return strName_; }
};

class SuiteOfTests
{
  private:
    typedef std::map<const std::string, boost::shared_ptr<UnitTest> > UnitTestMap;

  private:
    UnitTestMap mUnitTests_;

  protected:
    void Register(UnitTest* pTest)
    {
      assert(mUnitTests_.find(pTest->GetName()) == mUnitTests_.end());

      mUnitTests_[pTest->GetName()] = boost::shared_ptr<UnitTest>(pTest);
    }

  public:
    const UnitTestMap& getAllTests() const { return mUnitTests_; }
};

#define BEGIN_UNITTEST(a) class a : public UnitTest {\
  public:\
    a() : UnitTest(#a) {}\
  private:\
    void Run(const std::set<std::string>& sstrTests) {\
      std::cout << "Starting tests on suite \x1b[1m\x1b[33m" << #a << "\x1b[0m" << std::endl;\
      int iSuccess = 0;\
      int iFailure = 0;

#define BEGIN_REGISTER

#define REGISTER(a)\
if (sstrTests.empty() || sstrTests.find(#a) != sstrTests.end()) {\
  try {\
    std::cout << "> Starting test \x1b[36m" << #a << "\x1b[0m" << std::endl;\
    a();\
    ++iSuccess;\
  }\
  catch(UnitTestException& e)\
  {\
    std::cout << "\x1b[31m\x1b[1m" << #a << " failed: \x1b[22m" << e.what() << "\x1b[0m" << std::endl;\
    ++iFailure;\
  }\
}

#define END_REGISTER\
  if (iFailure)\
  {\
    std::cout << "\x1b[1m\x1b[31m" << iFailure << " tests failed, \x1b[32m" << iSuccess << " succeeded\x1b[0m" << std::endl;\
    throw std::runtime_error("Some tests failed");\
  }\
  else\
  {\
    std::cout << "\x1b[1m\x1b[32mAll tests succeeded (" << iSuccess << ") !\x1b[0m" << std::endl;\
  }\
}

#define END_UNITTEST };

#define ASSERT_TRUE(expr)\
if (!(expr)) {\
  std::stringstream ssExpr;\
  ssExpr << #expr << " expected true";\
  throw UnitTestException(__LINE__, ssExpr.str());\
};

#define ASSERT_MESSAGE(expr, msg)\
if (!(expr)) {\
  std::stringstream ssExpr;\
  ssExpr << "Failed with message: " << msg;\
  throw UnitTestException(__LINE__, ssExpr.str());\
};

#define ASSERT_FALSE(a)\
if (a) {\
  std::stringstream ssExpr;\
  ssExpr << #a << " expected false";\
  throw UnitTestException(__LINE__, ssExpr.str());\
};

#define ASSERT_EQUAL(a, b)\
if (!((a) == (b))) {\
  std::stringstream ssExpr;\
  ssExpr << "\nGot      [" << a << "] (" << #a << ")";\
  ssExpr << "\nExpected [" << b << "] (" << #b << ")";\
  throw UnitTestException(__LINE__, ssExpr.str());\
};

#define ASSERT_NOT_EQUAL(a, b)\
if (!((a) != (b))) {\
  std::stringstream ssExpr;\
  ssExpr << #a << " expected different than " << #b << " (" << b << ")";\
  throw UnitTestException(__LINE__, ssExpr.str());\
};

#define ASSERT_SOFT_EQUAL(a, b, c)\
if (!(((a) - (b)) <= c) || !(((a) - (b)) >= -c)) {\
  std::stringstream ssExpr;\
  ssExpr << "\nGot        [" << a << "] (" << #a << ")";\
  ssExpr << "\nExpected   [" << b << " \U000000B1 " << c << "] (" << #b << ")";\
  ssExpr << "\nDifference [" << ((a) - (b)) << "]";\
  throw UnitTestException(__LINE__, ssExpr.str());\
};

#define ASSERT_LESS(a, b)\
if (!((a) < (b))) {\
  std::stringstream ssExpr;\
  ssExpr << "\nGot        [ " << a << "] (" << #a << ")";\
  ssExpr << "\nExpected   [<" << b << "] (" << #b << ")";\
  throw UnitTestException(__LINE__, ssExpr.str());\
};

#define ASSERT_LEQ(a, b)\
if (!((a) <= (b))) {\
  std::stringstream ssExpr;\
  ssExpr << "\nGot        [ " << a << "] (" << #a << ")";\
  ssExpr << "\nExpected   [\U00002264" << b << "] (" << #b << ")";\
  throw UnitTestException(__LINE__, ssExpr.str());\
};

#define ASSERT_MORE(a, b)\
if (!((a) > (b))) {\
  std::stringstream ssExpr;\
  ssExpr << "\nGot        [ " << a << "] (" << #a << ")";\
  ssExpr << "\nExpected   [>" << b << "] (" << #b << ")";\
  throw UnitTestException(__LINE__, ssExpr.str());\
};

#define ASSERT_MEQ(a, b)\
if (!((a) >= (b))) {\
  std::stringstream ssExpr;\
  ssExpr << "\nGot        [ " << a << "] (" << #a << ")";\
  ssExpr << "\nExpected   [\U00002265" << b << "] (" << #b << ")";\
  throw UnitTestException(__LINE__, ssExpr.str());\
};

#define ASSERT_NON_NULL(a)\
if (a == NULL) {\
  throw UnitTestException(__LINE__, "\nNULL pointer exception !");\
};

#define ASSERT_SUCCESS(expr)\
{\
  core::ResultCode exprrc = expr;\
  if (exprrc.isFailure()) {\
    std::stringstream ssExpr;\
    ssExpr << "\nFailed with code [0x" << std::hex << exprrc.getValue() << "]";\
    throw UnitTestException(__LINE__, ssExpr.str());\
  };\
}

#define ASSERT_FAILURE(expr)\
{\
  core::ResultCode exprrc = expr;\
  if (exprrc.isSuccess()) {\
    std::stringstream ssExpr;\
    ssExpr << "\nSuccess not expected: code [0x" << std::hex << exprrc.getValue() << "]";\
    throw UnitTestException(__LINE__, ssExpr.str());\
  };\
}

#define ASSERT_THROWING(expr)\
{\
  try {\
    expr;\
    std::stringstream ssExpr;\
    ssExpr << "\nException expected";\
    throw UnitTestException(__LINE__, ssExpr.str());\
  } catch (const std::exception&) {\
  }\
}
