#ifndef _LOFTILI_CLI_PARSER_H
#define _LOFTILI_CLI_PARSER_H

#include <iostream>
#include <getopt.h>
#include <termios.h>
#include "loftili.h"

namespace loftili {
namespace cli {

class Parser {

  public:
    static Configuration parse(int argc, char* argv[]);

  private:
    static void fillPassword(Configuration* config);
    static void help();
    static bool missing(char param);
    static void stdinecho(bool enable);

};

}
}

#endif
