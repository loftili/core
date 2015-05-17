#ifndef _LOFTILI_NET_GENERIC_COMMAND_H
#define _LOFTILI_NET_GENERIC_COMMAND_H

#include <iostream>
#include "commands/audio/start.h"
#include "commands/audio/stop.h"
#include "net/command.h"

namespace loftili {

class Engine;

namespace net {

class GenericCommand : public loftili::net::Command {
  public:
    GenericCommand();
    GenericCommand(const char*);
    ~GenericCommand();
    void Execute(loftili::Engine*);
    void operator()(loftili::Engine*);
    operator bool();
  private:
    loftili::net::Command* m_cmd;
};

}

}


#endif
