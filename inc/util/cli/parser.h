#ifndef _LOFTILI_CLI_PARSER_H
#define _LOFTILI_CLI_PARSER_H

#include <iostream>
#include <getopt.h>
#include <termios.h>
#include "util/options.h"

namespace loftili {
namespace cli {

class Parser {

  public:
    static Options parse(int argc, char* argv[]);

  private:
    static void fillPassword(Options* opts);
    static void help();
    static bool missing(char param);
    static void stdinecho(bool enable);

};

}
}

#endif
