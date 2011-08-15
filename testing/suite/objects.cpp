#include "objects.h"

#include <libredwgpp/parser/objects/face3d.h>
#include <libredwgpp/parser/sections/classes.h>
#include <libredwgpp/parser/sections/objects.h>

#include "schemas/schemaface3d.h"

////////////////////////////////////////////////////////////////

void Objects::parseFace3D()
{
  SchemaFace3D schema;
  parse(schema);
}

////////////////////////////////////////////////////////////////

void Objects::parse(NoOpSchema& schema)
{
  std::vector<libredwgpp::Version> vVersions;
  vVersions.push_back(libredwgpp::Version::R13);
  vVersions.push_back(libredwgpp::Version::R14);
  vVersions.push_back(libredwgpp::Version::R2000);
  vVersions.push_back(libredwgpp::Version::R2004);
  vVersions.push_back(libredwgpp::Version::R2007);
  vVersions.push_back(libredwgpp::Version::R2010);

  libredwgpp::ClassesParser classes(vVersions[0]);

  for (size_t i = 0; i < vVersions.size(); ++i)
  {
    const UnicodeString strHex = schema.getVersion(vVersions[i]);
    if (!strHex.isEmpty())
    {
      libredwgpp::DWGBuffer buffer = prepareHexBuffer(strHex);

      libredwgpp::ObjectsParser parser(vVersions[i]);
      ASSERT_SUCCESS(parser.restoreObject(schema, buffer, classes));
//    core::ResultCode restoreObject(ISchema& schema, DWGBuffer& buffer, const ClassesParser& classes);
//      ASSERT_SUCCESS(object.restore(schema, buffer, vVersions[i]));
    }
  }
}

////////////////////////////////////////////////////////////////

libredwgpp::DWGBuffer Objects::prepareHexBuffer(const UnicodeString& strHexs)
{
  core::MemBuffer buffer;
  uint8_t last = 0xF0;
  for (int i = 0; i < strHexs.length(); ++i)
  {
    uint8_t current = 0xF0;
    if (strHexs[i] == ' ')
    {
      continue;
    } else if (strHexs[i] >= '0' && strHexs[i] <= '9') {
      current = strHexs[i] - '0';
    } else if (strHexs[i] >= 'A' && strHexs[i] <= 'F') {
      current = 10 + strHexs[i] - 'A';
    } else if (strHexs[i] >= 'a' && strHexs[i] <= 'f') {
      current = 10 + strHexs[i] - 'a';
    } else {
      ASSERT_MESSAGE(false, strHexs[i]);
    }

    if (last >= 0x10)
    {
      last = current;
    } else {
      current |= (last <<= 4);
      last = 0xF0;
      buffer.write(current);
    }
  }

  return libredwgpp::DWGBuffer(buffer);
}

////////////////////////////////////////////////////////////////
