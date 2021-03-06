#pragma once

#include "../includes.h"

#include "face3d.h"

namespace libredwgpp {

class ISchema
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////
  public:

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  private:

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    virtual ~ISchema() {}

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////
  private:

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    virtual void addFace3d(const Face3d& face) = 0;

//    virtual const std::vector<Face3d>& getFaces3d() const = 0;
};

////////////////////////////////////////////////////////////////

}
