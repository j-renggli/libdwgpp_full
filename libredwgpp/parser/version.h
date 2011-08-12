#pragma once

#include <includes.h>

namespace libredwg2 {

class Version
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////
  public:
    enum Release {
      R13,
      R14,
      R2000,
      R2004,
      R2007,
      R2010,

      Unknown
    };

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  private:
    Release release_;

    size_t version_;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    Version();

    Version(Release release, size_t maintenance = 0);

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    bool equals(Release release) const;

    bool isAtLeast(Release release, size_t maintenance = 0) const;

    bool isBetween(Release min, Release max) const;

    bool isGreaterThan(Release release, size_t maintenance = 0) const;

    void setMaintenance(size_t maintenance);

    void setRelease(Release release);
};

////////////////////////////////////////////////////////////////

}
