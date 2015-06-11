#include "engine.h"

namespace loftili {

int Engine::Initialize(int argc, char* argv[]) {
  int i = 1;
  char *p;

  std::string serial_no, logfile = LOFTILI_LOG_PATH;
  loftili::net::Url api_url;
  bool verbose = false;

  for(; i < argc; i++) {
    p = argv[i];
    // any iteration here should be the start of a flag
    if(*p++ != '-') {
      printf("%s\n", p);
      return DisplayHelp();
    }

    bool f = false;

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

  if(serial_no.size() != 40) {
    printf("\e[0;31minvalid serial number\e[0m\n\n");
    return DisplayHelp();
  }

  if(!verbose) {
    int childpid = 0;
    pid_t pid = 0;
    if((childpid = fork ()) < 0) return false;
    if(childpid > 0) exit(0);
  }

  auto lof = verbose ? spdlog::stdout_logger_mt(LOFTILI_SPDLOG_ID) 
    : spdlog::rotating_logger_mt(LOFTILI_SPDLOG_ID, logfile.c_str(), 1048576 * 5, 3, true);

  if(!verbose) {
    setsid();
    umask(0);

    close(fileno(stderr));
    close(fileno(stdout));
    close(STDIN_FILENO);
  }

  loftili::api::configuration.serial = serial_no;
  spdlog::set_level(spdlog::level::info);

  if(api_url.Host().size() > 5)
    loftili::api::configuration.hostname = api_url.Host();
  else 
    loftili::api::configuration.hostname = "api.loftili.com";

  if(api_url.Protocol() == "http")
    loftili::api::configuration.protocol = "http";
  else
    loftili::api::configuration.protocol = "https";

  loftili::api::configuration.port = api_url.Port() < 0 ? 443 : api_url.Port();

  lof->info("configuring engine - api[{0}:{1}]", loftili::api::configuration.hostname, loftili::api::configuration.port);
  return 1;
}

int Engine::DisplayHelp() {
  printf("\e[4;32mloftili core v%s \e[0m\n", PACKAGE_VERSION);
  printf("get involved @ %s \n", PACKAGE_URL);
  printf("please send all issues to %s \n\n", PACKAGE_BUGREPORT);
  printf("options: \n");
  printf("        -%s %-*s %s", "s", 15, "SERIAL", "\e[0;36m[required]\e[0m the serial number this device was given\n");
  printf("        -%s %-*s %s", "a", 15, "API HOST", "if running the api on your own, use this param (defaults to https://api.loftili.com)\n");
  printf("        -%s %-*s %s", "l", 15, "LOGFILE", "the file path used for the log file. ignored if -v (defaults to loftili.log)\n");
  printf("        -%s %-*s %s", "v", 15, "VERBOSE", "runs loftili core in foreground - log messages to stdout (development mode)\n");
  printf("        -%s %-*s %s", "h", 15, "", "display this help text \n\n");
  return 0;
}

int Engine::Run() {
  spdlog::get(LOFTILI_SPDLOG_ID)->info("telling playback to skip in case we were shut down");
  loftili::audio::Playback *p;
  if((p = Get<loftili::audio::Playback>())) p->Skip();

  spdlog::get(LOFTILI_SPDLOG_ID)->info("opening command stream to api server");

  if(Subscribe() < 0) {
    spdlog::get(LOFTILI_SPDLOG_ID)->critical("received invalid response from server during subscription request");
    return -1;
  }
  spdlog::get(LOFTILI_SPDLOG_ID)->info("socket subscription request complete");

  int retries = 0;
  loftili::net::CommandStream cs;
  spdlog::get(LOFTILI_SPDLOG_ID)->info("subscription finished, attempting to read into command stream");

  while(retries < MAX_ENGINE_RETRIES) {
    while(cs << m_socket) {
      std::shared_ptr<loftili::net::GenericCommand> gc = cs.Latest();
      spdlog::get(LOFTILI_SPDLOG_ID)->info("received command, executing command");
      (*gc.get())(this);
      cs.Pop();
      retries = 0;
    }

    spdlog::get(LOFTILI_SPDLOG_ID)->warn("engine stream reached bad state, retrying in 2 seconds. attempt [{0}]", ++retries);
    sleep(2);
    if(Subscribe() > 0) continue;
    spdlog::get(LOFTILI_SPDLOG_ID)->critical("engine unable to subscribe to api stream, shutting down");
    break;
  }

  spdlog::get(LOFTILI_SPDLOG_ID)->critical("engine stream exited after [{0}] retries", retries);

  return 0;
};

int Engine::Register() {
  spdlog::get(LOFTILI_SPDLOG_ID)->info("beginning registration process...");
  loftili::api::Registration *registration = Get<loftili::api::Registration>();
  return registration->Register();
};

int Engine::Subscribe() {
  m_socket = loftili::net::TcpSocket(loftili::api::configuration.protocol == "https");
  int ok = m_socket.Connect(loftili::api::configuration.hostname.c_str(), loftili::api::configuration.port);
  if(ok < 0) return -1;

  std::stringstream r;
  r << "SUBSCRIBE /sockets/devices HTTP/1.1\n";
  r << "Connection: Keep-alive\n";
  r << "Host: " << loftili::api::configuration.hostname << "\n";
  r << "Content-Length: 0\n";
  r << LOFTILI_API_TOKEN_HEADER << ": " << loftili::api::credentials.token << "\n";
  r << LOFTILI_API_SERIAL_HEADER << ": " << loftili::api::configuration.serial;
  r << "\r\n\r\n";
  std::string subscription_req = r.str();
  return m_socket.Write(subscription_req.c_str(), subscription_req.length());
}

}
