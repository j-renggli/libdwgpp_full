#include "unittestsuite.h"

#include <iostream>

#include <core/includes.h>

#include "../suite/suite.h"

////////////////////////////////////////////////////////////////

UnitTestSuite::UnitTestSuite()
{
  Register(new LibreDwgppSuite);
}

////////////////////////////////////////////////////////////////

UnitTestSuite::~UnitTestSuite()
{
  //dtor
}

////////////////////////////////////////////////////////////////

void UnitTestSuite::Register(SuiteOfTests* pSuite)
{
//  boost::shared_ptr<SuiteOfTests> ptrSuite(pSuite);

  const UnitTestMap& all = pSuite->getAllTests();

  for (UnitTestMap::const_iterator it = all.begin(); it != all.end(); ++it)
  {
    assert(mUnitTests_.find(it->first) == mUnitTests_.end());

    mUnitTests_[it->first] = it->second;
  }
}

////////////////////////////////////////////////////////////////

void UnitTestSuite::Run(const std::set<std::string>& sstrTests)
{
  int iTotal = 0;
  int iFailed = 0;
  int iNotFound = 0;
  if (sstrTests.empty())
  {
    // Use an empty vector
    std::set<std::string> sstrEmpty;
    LOG_TRACE("Running without options");

    // Test everything
    for (UnitTestMap::iterator m_it = mUnitTests_.begin(); m_it != mUnitTests_.end(); ++m_it)
    {
      ++iTotal;
      try
      {
        m_it->second->Run(sstrEmpty);
      }
      catch (std::exception& e)
      {
        std::cout << "UnitTest " << m_it->first << " failed : " << e.what() << std::endl;
        ++iFailed;
      }
    }
  }
  else
  {
    for (std::set<std::string>::const_iterator it = sstrTests.begin(); it != sstrTests.end(); ++it)
    {
      ++iTotal;

      std::string strSuite = *it;
      std::string strTest;
      size_t iDouble = it->find("::");
      if (iDouble != it->npos)
      {
        strSuite = it->substr(0, iDouble);
        std::string strTest = it->substr(iDouble + 2);
      }

      // Find suite
      UnitTestMap::iterator m_it = mUnitTests_.find(strSuite);
      if (m_it == mUnitTests_.end())
      {
        std::cout << "UnitTest " << strSuite << " not found (not registered ?) !" << std::endl;
        ++iNotFound;
        return;
      }

      // Use an empty vector if more than one test
      std::set<std::string> sstrSelection;
      if (!strTest.empty())
        sstrSelection.insert(strTest);

      try
      {
        m_it->second->Run(sstrSelection);
      }
      catch (std::exception& e)
      {
        std::cout << *it << " failed : " << e.what() << std::endl;
        ++iFailed;
      }
    }
  }

  std::cout << "Overall: "
            << iTotal << " test units; "
            << iNotFound << " not found, "
            << iFailed << " failed" << std::endl;
}

////////////////////////////////////////////////////////////////
