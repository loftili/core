#include "engine.h"

namespace loftili {

Engine::Engine(int argc, char *argv[]) {
  auto lof = spdlog::stdout_logger_mt(LOFTILI_SPDLOG_ID);
  spdlog::set_level(spdlog::level::info);
  lof->info("configuring engine");
  loftili::api::configuration.hostname = "0.0.0.0";
}

int Engine::Run() {
  spdlog::get(LOFTILI_SPDLOG_ID)->info("opening command stream to api server");
  m_socket = std::make_unique<loftili::net::TcpSocket>();

  int ok = m_socket->Connect(loftili::api::configuration.hostname.c_str(), 1337),
      retries = 0;

  if(ok < 0) {
    spdlog::get(LOFTILI_SPDLOG_ID)->critical("unable to connect to server");
    return ok;
  }

  if(Subscribe() < 0) {
    spdlog::get(LOFTILI_SPDLOG_ID)->critical("received invalid response from server during subscription request");
    return -1;
  }

  loftili::net::CommandStream cs;

  while(retries < 100) {
    while(cs << m_socket) {
      std::shared_ptr<loftili::net::GenericCommand> gc = cs.Latest();
      spdlog::get(LOFTILI_SPDLOG_ID)->info("received command, executing command");
      (*gc.get())(this);
      cs.Pop();
    }
    spdlog::get(LOFTILI_SPDLOG_ID)->warn("command stream reached an invalid state, retrying");
    retries++;
  }

  return ok;
};

int Engine::Register() {
  int result = 1;
  spdlog::get(LOFTILI_SPDLOG_ID)->info("beginning registration process...");

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
