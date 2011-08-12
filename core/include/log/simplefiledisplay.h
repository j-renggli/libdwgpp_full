#pragma once

#include "display.h"
#include "message.h"

#include <fstream>

namespace core {

//class Message;

class SimpleFileDisplay : public IDisplay
{
  private:
    int iMinLevel_;

    std::ofstream file_;

  public:
    SimpleFileDisplay(const boost::filesystem::path& pathFile, int iMinLevel) : iMinLevel_(iMinLevel)
    {
      file_.open(pathFile.native_file_string().c_str());
    }

    ~SimpleFileDisplay()
    {
      if (file_.is_open())
        file_.close();
    }

  public:
    void display(const Message& msg)
    {
      if (msg.getLevel() < iMinLevel_)
        return;

      file_  << msg.getTime() << " @ " << msg.getFile().leaf() << " line " << msg.getLine()
             << " (" << msg.getLevel() << "): " << msg.getMessage() << std::endl;
    }
};

}
