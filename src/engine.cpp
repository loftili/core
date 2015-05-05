#include "engine.h"

namespace loftili {

Engine::Engine(int argc, char *argv[]) : m_socket(new loftili::net::Socket) {
}

Engine::~Engine() {
  delete m_socket;
}

int Engine::Run() {
  int ok = 0, retries = 0;

  ok = m_socket->Connect(loftili::api::configuration.hostname.c_str(), loftili::api::configuration.port, false);

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

  bool socket_ok = m_socket->Ok();

  while(retries < 100) {

    while(socket_ok) {
      socket_ok = ((*m_socket) >> (*cs)).Ok();

      if(!socket_ok) break;

      loftili::net::GenericCommand cc = ((loftili::net::CommandStream*)cs)->Transform();

      if(!cc) continue;

      cc(this);

      retries = 0;
    }

    sleep(2);
    printf("retrying!\n");
    retries++;
    ok = m_socket->Reconnect();
    socket_ok = Subscribe() >= 0;
  }

  return 0;
};

int Engine::Register() {
  loftili::api::Registration *registration = Get<loftili::api::Registration>();
  int result = registration->Register();

#ifdef HAVE_AUDIO
  if(result) Get<loftili::audio::Playback>()->Initialize(registration);
#endif

  return result;
};

int Engine::Subscribe() {
  std::string r = "GET ";
  r += "/devicestream/open";
  r += " HTTP/1.1\n";
  r += "Connection: Keep-alive\n";
  r += LOFTILI_API_TOKEN_HEADER;
  r += ": " + Get<loftili::api::Registration>()->Credentials().token + "\n";
  r += LOFTILI_API_SERIAL_HEADER;
  r += ": " + loftili::api::configuration.serial + "\n";
  r += "\n";
  return m_socket->Write(r.c_str(), r.length());
}

}
