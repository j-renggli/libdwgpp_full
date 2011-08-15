#pragma once

#include "../utils/unittest.h"

#include "dwgbuffer.h"
#include "objects.h"

class LibreDwgppSuite : public SuiteOfTests
{
  public:
    LibreDwgppSuite()
    {
      Register(new DWGBuffer);
      Register(new Objects);
    }
};
