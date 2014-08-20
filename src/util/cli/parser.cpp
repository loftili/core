#include "util/cli/parser.h"

namespace loftili {
namespace cli {

Options Parser::parse(int argc, char* argv[]) {
  Options opts;

  int port = 0;
  int c = 0;

  while(read(argc, argv, &c)) {
    switch(c) {
      case 'p':
        port = atoi(optarg);
        break;
      case 'h':
        help();
        break;
      default:
        break;
    }
  }

  return opts;
}

bool Parser::read(int argc, char* argv[], int* out) {
  opterr = 0;

  *out = getopt(argc, argv, "p:h::");

  if(*out == '?')
    return missing(optopt);
  else if(*out == -1) {
    help();
    return false;
  }

  return true;
}

bool Parser::missing(char param) {
  printf("you are missing the - %c parameter \n", param);
  help();
  return false;
}

void Parser::help() {
  printf("Loftili core v%s \n", PACKAGE_VERSION);
  printf("options: \n");
  printf("   -%-*s %s", 5, "p", "the port to run the lofiti web server on \n");
  printf("   -%-*s %s", 5, "u", "your username. will be used to connect with the loftili api \n");
  printf("   -%-*s %s", 5, "h", "display this help text \n");
}

}
}
