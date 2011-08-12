#pragma once

#include "object.h"

namespace libredwg2 {

namespace parserobject {

class Layer : public parserobject::Object
{
  public:
    ~Layer() {}

  public:
    virtual core::ResultCode restoreFull(Schema& schema, DWGBuffer& buffer, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
