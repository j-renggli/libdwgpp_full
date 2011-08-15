#pragma once

#include "../utils/unittest.h"

#include "dwgbuffer.h"

class LibreDwgppSuite : public SuiteOfTests
{
  public:
    LibreDwgppSuite()
    {
      Register(new DWGBuffer);
    }
};
