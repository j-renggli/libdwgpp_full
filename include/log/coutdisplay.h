#pragma once

#include "display.h"
#include "message.h"

namespace core {

class COutDisplay : public IDisplay
{
  private:
    int iMinLevel_;

  public:
    COutDisplay(int iMinLevel) : iMinLevel_(iMinLevel) {}

    ~COutDisplay() {}

  public:
    virtual void display(const Message& msg);
};

}
