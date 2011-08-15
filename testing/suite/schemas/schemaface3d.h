#pragma once

#include "schemanoop.h"

class SchemaFace3D : public NoOpSchema
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
    virtual ~SchemaFace3D() {}

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////
  private:

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    virtual void addFace3d(const Face3d& face)
    {
      const Colour col = face.getColour();
      ASSERT_EQUAL(col.getR(), 0);
      ASSERT_EQUAL(col.getG(), 0);
      ASSERT_EQUAL(col.getB(), 0);
      ASSERT_EQUAL(col.getA(), 0);

      for (int i = 0; i < 4; ++i)
      {
        const Vertex3d& corner = face.getCorner(i);
        for (int j = 0; j < 3; ++j)
        {
          ASSERT_MEQ(corner.get(j), 0.);
          ASSERT_LEQ(corner.get(j), 10.);
        }
      }
    }

    virtual UnicodeString getVersion(libredwgpp::Version version) const
    {
      if (version.isAtLeast(libredwgpp::Version::R2000))
      {
        return "";
      } else {
        return "50 00 47 00 78 E3 18 10 00 05 7B 06 54 B1 62 D9 BA E4 28 00 02 01 84 E7 8E 80\
12 04 4F 73 C2 29 98 53 12 20 16 8C 3C B6 E3 69 E2 08 10 14 77 8D 5D FA 52 4C 80 50 0B 36 A4 30\
F0 FF 1F C5 51 57 68 85 48 51 12 00 40 84 CA FB AF DF EC 7F 46 0A 21 FA 1A A6";
      }
    }
};
