#include "util/cli/parser.h"

namespace loftili {
namespace cli {

Options Parser::parse(int argc, char* argv[]) {
  Options opts;

  int port = 0;
  int c = 0;
  opterr = 0;

  while((c = getopt (argc, argv, "p::hun:")) != -1) {
    switch(c) {
      case 'p':
        opts.port = atoi(optarg);
        break;
      case 'h':
        help();
        opts.help = true;
        return opts;
      case '?':
        opts.help = true;
        missing(optopt);
        return opts;
      default:
        break;
    }
  }

  opts.help = false;

  return opts;
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
  printf("   -%s %-*s %s", "u", 15, "USERNAME", "your username. will be used to connect with the loftili api \n");
  printf("   -%s %-*s %s", "n", 15, "DEVICENAME", "the name this device should be communicating under \n");
  printf("   -%s %-*s %s", "h", 15, "", "display this help text \n");
}

}
}
