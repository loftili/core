#include "engine.h"

namespace loftili {

Engine::Engine() : m_socket(new loftili::net::Socket) { 
}

Engine::~Engine() {
  delete m_socket;
}

int Engine::Run() {
  int ok = 0, retries = 0;

  ok = m_socket->Connect("127.0.0.1", 1337, false);

  if(ok < 0) {
    printf("failed connecting\n");
    return -1;
  }

  ok = Subscribe();

  if(ok < 0) {
    printf("failed writing\n");
    return -1;
  }

  loftili::lib::Stream *cs = new loftili::net::CommandStream();
  loftili::net::Command cc;

  bool socket_ok = m_socket->Ok();
  while(retries < 100) {

    while(socket_ok) {
      socket_ok = ((*m_socket) >> (*cs)).Ok();

      printf("received: %d\n", socket_ok);

      if(socket_ok)
        cc = ((loftili::net::CommandStream*)cs)->Transform();

      if(!cc) continue;

      cc.Execute();
    }

    sleep(2);
    printf("retrying!\n");
    retries++;
    ok = m_socket->Reconnect();
    socket_ok = Subscribe() >= 0;
  }

  return 0;
};

int Engine::Subscribe() {
  std::string r = "GET ";
  r += "/devicestream/open?sn=aasdasdasdasdasdasdasdasdasdasdasdasdasd ";
  r += "HTTP/1.1\n";
  r += "Connection: Keep-alive\n\n";
  return m_socket->Write(r.c_str(), r.length());
}

}
