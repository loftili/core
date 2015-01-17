#include "util/cli/parser.h"

namespace loftili {
namespace cli {

Configuration Parser::parse(int argc, char* argv[]) {
  Configuration opts;

  int arg_index = 1;
  for(arg_index; arg_index < argc; arg_index++) {
    char* current = argv[arg_index];
    if(current[0] != '-')
      continue;

    char flag_name = current[1];
    std::string flag_val;

    switch(flag_name) {
      case 'a':
        if(arg_index + 1 < argc) {
          flag_val = argv[arg_index + 1];
          opts.api_host = flag_val;
        }
        break;
      case 'h':
        help();
        opts.help = true;
        return opts;
      case 'n':
        if(arg_index + 1 < argc) {
          flag_val = argv[arg_index + 1];
          opts.devicename = flag_val;
        }
        break;
      case 'u':
        if(arg_index + 1 < argc) {
          flag_val = argv[arg_index + 1];
          opts.username = flag_val;
        }
        break;
      case 'p':
        if(arg_index + 1 < argc) {
          flag_val = argv[arg_index + 1];
          opts.port = std::stoi(flag_val);
        }
        break;
      case 'l':
        if(arg_index + 1 < argc) {
          flag_val = argv[arg_index + 1];
          opts.logfile = std::string(flag_val);
          opts.use_log = true;
          arg_index++;
        }
        break;
      case 'd':
        opts.daemonize = true;
        break;
      case 's':
        opts.standalone = true;
        break;
      default:
        break;
    }
  }

  if((opts.devicename == "" || opts.username == "") && !opts.standalone) {
    help();
    return opts;
  }

  if(opts.port == 0)
    opts.port = LOFTILI_DEFAULT_PORT;
  
  if(!opts.standalone)
    fillPassword(&opts);

  opts.help = false;

  return opts;
}

void Parser::fillPassword(Configuration* opts) {
  printf("enter your loftili password (for %s): \n", opts->username.c_str());
  stdinecho(false);
  std::string password;
  getline(std::cin, password);
  opts->password = password;
  stdinecho(true);
}

void Parser::stdinecho(bool enable) {
  struct termios tty;
  tcgetattr(STDIN_FILENO, &tty);

  if(!enable)
    tty.c_lflag &= ~ECHO;
  else
    tty.c_lflag |= ECHO;

  (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

bool Parser::missing(char param) {
  printf("you are missing the - %c parameter \n", param);
  help();
  return false;
}

void Parser::help() {
  printf("loftili core v%s \n", PACKAGE_VERSION);
  printf("get involved @ %s \n", PACKAGE_URL);
  printf("please send all issues to %s \n\n", PACKAGE_BUGREPORT);
  printf("options: \n");
  printf("   -%s %-*s %s", "p", 15, "PORT", "the port to run the lofiti web server on \n");
  printf("   -%s %-*s %s", "u", 15, "USERNAME", "[required] your username. will be used to connect with the loftili api\n");
  printf("   -%s %-*s %s", "n", 15, "DEVICENAME", "[required] the name this device should be communicating under\n");
  printf("   -%s %-*s %s", "a", 15, "API HOST", "if running the api on your own, use this param\n");
  printf("   -%s %-*s %s", "d", 15, "DAEMONIZE", "run loftili in daemon mode (background)\n");
  printf("   -%s %-*s %s", "l", 15, "LOGFILE", "the file path used for the log file \n");
  printf("   -%s %-*s %s", "h", 15, "", "display this help text \n");
}

}
}
