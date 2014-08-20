#ifndef _LOFTILI_CLI_PARSER_H
#define _LOFTILI_CLI_PARSER_H

#include <iostream>
#include <getopt.h>
#include "util/options.h"

namespace loftili {
namespace cli {

class Parser {

public:
  static Options parse(int argc, char* argv[]);

private:
  static void help();
  static bool read(int argc, char* argv[], int* out);
  static bool missing(char param);

};

}
}

#endif
