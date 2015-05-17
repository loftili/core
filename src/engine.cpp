#include "engine.h"

namespace loftili {

Engine::Engine(int argc, char *argv[]) {
}

int Engine::Run() {
  m_socket = std::make_unique<loftili::net::TcpSocket>();

  int ok = m_socket->Connect(loftili::api::configuration.hostname.c_str(), 1337),
      retries = 0;

  if(ok < 0) return ok;

  if(Subscribe() < 0) return -1;

  loftili::net::CommandStream cs;

  while(retries < 100) {
    while(cs << m_socket) {
      std::shared_ptr<loftili::net::GenericCommand> gc = cs.Latest();
      (*gc.get())(this);
      cs.Pop();
    }
    retries++;
  }

  return ok;
};

int Engine::Register() {
  int result = 1;

  loftili::api::Registration *registration = Get<loftili::api::Registration>();

  result = registration->Register();

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
