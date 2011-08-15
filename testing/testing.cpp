// STL
#include <fstream>
#include <iostream>

// Boost
#include <boost/program_options.hpp>

// Local
#include "utils/unittestsuite.h"

#include <unicode/uclean.h>

#include <core/include/log/coutdisplay.h>
#include <core/include/log/logmanager.h>

int main(int argc, char* argv[])
{
  boost::program_options::options_description desc("Testing options");
  desc.add_options()
      ("help", "display this help message")
      ("unittest,u", boost::program_options::value<std::vector<std::string> >(), "Limit the test to (a) suite(s) or unittest(s)")
      ;

  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
  std::ifstream iFile;
  iFile.open("ProgramOptions.txt");
  boost::program_options::store(boost::program_options::parse_config_file(iFile, desc), vm);
  iFile.close();
  boost::program_options::notify(vm);

  std::vector<std::string> vstrTests;
  std::set<std::string> sstrTests;

  if (vm.count("help"))
  {
      std::cout << desc << "\n";
      return 1;
  }
  if (vm.count("unittest"))
  {
    vstrTests = vm["unittest"].as<std::vector<std::string> >();
  }

  sstrTests.insert(vstrTests.begin(), vstrTests.end());

  ////////////////////////////////

  // Activate trace
  core::gLogManager.activateTrace("autotest.log", core::LogManager::eDebug);

  core::gLogManager.registerDisplay(boost::shared_ptr<core::IDisplay>
    (new core::COutDisplay(core::LogManager::eWarning)));

  ////////////////////////////////

  core::ResultCode rc = core::rcSuccess;

  ////////////////////////////////

  LOG_TRACE("Running suite of tests");

  UnitTestSuite Suite;
  Suite.Run(sstrTests);

  ////////////////////////////////

  // Always good to clean after usage...
  u_cleanup();

  return 0;
}
