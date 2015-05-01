#ifndef _LOFTILI_NET_COMMAND_H
#define _LOFTILI_NET_COMMAND_H

#include "lib/command.h"

namespace loftili {

class Engine;

namespace net {

class Command : public loftili::lib::Command {
  public:
    virtual ~Command() { };
    void Execute() { };
    virtual void Execute(Engine*) = 0;
    virtual void operator ()(Engine*) = 0;
};

}

}

#endif
