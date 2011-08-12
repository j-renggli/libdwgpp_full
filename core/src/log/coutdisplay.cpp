#include "include/log/coutdisplay.h"

#include <iostream>

namespace core {

void COutDisplay::display(const Message& msg)
{
  if (msg.getLevel() < iMinLevel_)
    return;

  if (msg.getLevel() >= 50)
    std::cout << "\x1b[31m\x1b[22m" << msg.getMessage() << " (" << msg.getFile().leaf() << "@" << msg.getLine() << ")\x1b[0m" << std::endl;
  else
    std::cout << msg.getMessage() << " (" << msg.getFile().leaf() << "@" << msg.getLine() << ")" << std::endl;
//  std::cout << msg.getFile().leaf() << " @ " << msg.getLine() << " (" << msg.getLevel() << "): "
//    << msg.getMessage() << std::endl;
}

}
