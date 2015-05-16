#ifndef _LOFTILI_ENGINE_H
#define _LOFTILI_ENGINE_H

#include <iostream>
#include <unistd.h>
#include "loftili.h"
#include "net/tcp_socket.h"
#include "net/http_request.h"
#include "net/http_client.h"
#include "net/command_stream.h"
#include "net/generic_command.h"

namespace loftili {

class Engine {
  public:
    Engine(int, char* []);
    ~Engine() = default;
    int Run();
    int Register();
    template <class T>
    T* Get() {
      return m_components.Field<T>();
    };

  private:
    int Subscribe();
    loftili::ComponentHierarchy m_components;
    std::unique_ptr<loftili::net::TcpSocket> m_socket;
};

}

#endif
