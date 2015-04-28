#include "loftili.h"
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <sstream>
#include <memory>

#include "net/socket.h"
#include "net/command_stream.h"

namespace loftili {

class Request {
  public:
    Request(std::string method="GET", std::string path="/sk") : m_method(method), m_path(path) {
      Format();
    };

    int Length() {
      return m_content.length();
    };

    Request& operator=(const Request& other) {
      m_method = other.m_method;
      m_path = other.m_path;
      return *this;
    };

    operator const char*() {
      return m_content.c_str();
    };

  private:
    void Format() {
      m_content =  m_method + " " + m_path + " HTTP/1.1\n";
      m_content += "Connection: keep-alive\n\n";
    }

    std::string m_content;
    std::string m_method;
    std::string m_path;
};

class Engine {
  public:
    Engine() : m_socket(new loftili::net::Socket) {
    };

    ~Engine() {
      delete m_socket;
    };

    int Run() {
      int ok = 0;

      ok = m_socket->Connect("127.0.0.1", 1337, false);

      if(ok < 0) {
        printf("failed connecting\n");
        return -1;
      }

      Request r("GET", "/devicestream/open?sn=aasdasdasdasdasdasdasdasdasdasdasdasdasd");

      ok = m_socket->Write(r, r.Length());

      if(ok < 0) {
        printf("failed writing\n");
        return -1;
      }

      loftili::lib::Stream *cs = new loftili::net::CommandStream();

      while(m_socket->Ok()) {
        (*m_socket) >> (*cs);
        if(((loftili::net::CommandStream*)cs)->LastCommand()) printf("has command\n");
      }

      return 0;
    };

  private:
    loftili::net::Socket* m_socket;
};

}

int main(int argc, char* argv[]) {
  std::unique_ptr<loftili::Engine> p1(new loftili::Engine);
  return p1->Run();
}
