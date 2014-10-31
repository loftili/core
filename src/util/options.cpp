#include "util/options.h"

namespace loftili {

Options::Options() : password(""), devicename(""), username(""), api_host("") { 
  port = LOFTILI_DEFAULT_PORT;
  help = true;
  logfile = "loftili.log";
  use_log = false;
  standalone = false;
  daemonize = false;
}

Options::~Options() {
}

}
