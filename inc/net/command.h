#ifndef _LOFTILI_NET_COMMAND_H
#define _LOFTILI_NET_COMMAND_H

#include <iostream>
#include "commands/audio/start.h"
#include "lib/command.h"

namespace loftili {

namespace net {

class Command {
  public:
    Command();
    Command(const char*);
    ~Command();
    void Execute();
    operator bool();
  private:
    loftili::lib::Command* m_cmd;
};

}

}


#endif
