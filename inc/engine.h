#ifndef _LOFTILI_ENGINE_H
#define _LOFTILI_ENGINE_H

#include <iostream>
#include <unistd.h>
#include "net/socket.h"
#include "net/command_stream.h"

namespace loftili {

class Engine {
  public:
    Engine();
    ~Engine();
    int Run();

  private:
    int Subscribe();
    loftili::net::Socket* m_socket;
};

}

#endif
