#ifndef _LOFTILI_ENGINE_H
#define _LOFTILI_ENGINE_H

#include <iostream>
#include <unistd.h>
#include "loftili.h"
#include "spdlog/spdlog.h"
#include "net/tcp_socket.h"
#include "net/http_request.h"
#include "net/http_client.h"
#include "net/command_stream.h"
#include "net/generic_command.h"

namespace loftili {

class Engine {
  public:
    Engine() : m_socket(loftili::net::TcpSocket(false)) { }
    Engine(const Engine&) = default;
    Engine& operator=(const Engine&) = default;
    ~Engine() = default;
    int Initialize(int, char*[]);
    int Run();
    int Register();
    template <class T>
    T* Get() {
      return m_components.Field<T>();
    };

  private:
    int Subscribe();
    int DisplayHelp();
    loftili::ComponentHierarchy m_components;
    loftili::net::TcpSocket m_socket;
};

}

#endif
