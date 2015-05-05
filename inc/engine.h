#ifndef _LOFTILI_ENGINE_H
#define _LOFTILI_ENGINE_H

#include <iostream>
#include <unistd.h>
#include "loftili.h"
#include "net/socket.h"
#include "net/request.h"
#include "net/response_stream.h"
#include "net/command_stream.h"
#include "net/generic_command.h"

namespace loftili {

class Engine {
  public:
    Engine(int, char* []);
    ~Engine();
    int Run();
    int Register();
    template <class T>
    T* Get() {
      return m_components.Field<T>();
    };

  private:
    int Subscribe();
    loftili::ComponentHierarchy m_components;
    loftili::net::Socket* m_socket;
};

}

#endif
