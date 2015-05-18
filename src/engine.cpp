#include "engine.h"

namespace loftili {

int Engine::Initialize(int argc, char* argv[]) {
  int i = 1;
  char *p;

  std::string serial_no, logfile = LOFTILI_LOG_PATH;
  bool verbose = false;

  for(; i < argc; i++) {
    p = argv[i];
    // any iteration here should be the start of a flag
    if(*p++ != '-') {
      printf("%s\n", p);
      return DisplayHelp();
    }

    bool f = false;
    loftili::net::Url api_url;

    while(*p && f == false) {
      switch(*p++) {
        case 'h':
          return DisplayHelp();
        case 'v':
          verbose = true;
          break;
        case 'a':
          api_url = *p ? p : (argv[++i] ? argv[i] : "");
          if(api_url.Host().size() < 5) {
            printf("invalid api host argument [%s]\n", api_url.Host().c_str());
            return DisplayHelp();
          }
          f = true;
          continue;
        case 'l':
          if(*p) {
            logfile = p;
            f = true;
            continue;
          }
          if(argv[++i]) {
            logfile = argv[i];
            f = true;
            continue;
          }
          break;
        case 's':
          if(*p) {
            serial_no = p;
            f = true;
            continue;
          }
          if(argv[++i]) {
            serial_no = argv[i];
            f = true;
            continue;
          }
          break;
        default:
          printf("unrecognized option (%s)\n", --p);
          return DisplayHelp();
      }
    }
  }

  auto lof = verbose ? spdlog::stdout_logger_mt(LOFTILI_SPDLOG_ID) 
    : spdlog::rotating_logger_mt(LOFTILI_SPDLOG_ID, logfile.c_str(), 1048576 * 5, 3);

  spdlog::set_level(spdlog::level::info);
  lof->info("configuring engine");
  loftili::api::configuration.hostname = "0.0.0.0";
  return 1;
}

int Engine::DisplayHelp() {
  printf("loftili core v%s \n", PACKAGE_VERSION);
  printf("get involved @ %s \n", PACKAGE_URL);
  printf("please send all issues to %s \n\n", PACKAGE_BUGREPORT);
  printf("options: \n");
  printf("   -%s %-*s %s", "s", 15, "SERIAL", "[required] the serial number this device was given\n");
  printf("   -%s %-*s %s", "a", 15, "API HOST", "if running the api on your own, use this param\n");
  printf("   -%s %-*s %s", "d", 15, "DAEMONIZE", "run loftili in daemon mode (background)\n");
  printf("   -%s %-*s %s", "l", 15, "LOGFILE", "the file path used for the log file. ignored unless daemonize (-d)\n");
  printf("   -%s %-*s %s", "v", 15, "VERBOSE", "log messages to stdout (development mode)\n");
  printf("   -%s %-*s %s", "h", 15, "", "display this help text \n");
  return 0;
}

int Engine::Run() {

  spdlog::get(LOFTILI_SPDLOG_ID)->info("opening command stream to api server");
  m_socket = std::unique_ptr<loftili::net::TcpSocket>(new loftili::net::TcpSocket());

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
