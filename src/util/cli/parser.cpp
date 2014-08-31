#include "util/cli/parser.h"

namespace loftili {
namespace cli {

Options Parser::parse(int argc, char* argv[]) {
  Options opts;

  int c;
  opterr = 0;
  while((c = getopt (argc, argv, "l::p::u::n::a::h:")) != -1) {
    switch(c) {
      case 'a':
        opts.api_host = optarg;
        break;
      case 'p':
        opts.port = atoi(optarg);
        break;
      case 'l':
        opts.logfile = optarg;
        opts.use_log = true;
        break;
      case 'h':
        help();
        opts.help = true;
        return opts;
      case 'u':
         opts.username = optarg;
         break;
      case 'n':
         opts.devicename = optarg;
         break;
      case '?':
        opts.help = true;
        missing(optopt);
        return opts;
      default:
        break;
    }
  }

  if(opts.devicename == "" || opts.username == "") {
    help();
    return opts;
  }

  printf("enter your loftili password (for %s): \n", opts.username.c_str());
  stdinecho(false);
  std::string password;
  getline(std::cin, password);
  opts.password = password;
  stdinecho(true);

  opts.help = false;

  return opts;
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
  printf("   -%s %-*s %s", "h", 15, "", "display this help text \n");
}

}
}
