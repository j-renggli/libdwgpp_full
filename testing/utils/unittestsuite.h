#pragma once

// STL
#include <map>
#include <set>
#include <string>
#include <vector>

// Boost
#include <boost/shared_ptr.hpp>

class SuiteOfTests;
class UnitTest;

class UnitTestSuite
{
  private:
    typedef std::map<const std::string, boost::shared_ptr<UnitTest> > UnitTestMap;

  private:
    UnitTestMap mUnitTests_;

  public:
    UnitTestSuite();

    virtual ~UnitTestSuite();

  private:
    void Register(SuiteOfTests* pSuite);

  public:
    void Run(const std::set<std::string>& vstrTests);
};
