#pragma once

#include "../utils/unittest.h"

class NoOpSchema;

namespace libredwgpp {
  class DWGBuffer;
  class Object;
}

BEGIN_UNITTEST(Objects)
  BEGIN_REGISTER
    REGISTER(parseFace3D)
  END_REGISTER

  private:
    void parseFace3D();

  private:
    void parse(NoOpSchema& schema);

    libredwgpp::DWGBuffer prepareHexBuffer(const UnicodeString& strHexs);
END_UNITTEST
