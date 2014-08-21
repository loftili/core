#ifndef _LOFTILI_OPTIONS_H
#define _LOFTILI_OPTIONS_H

#include "loftili.h"

namespace loftili {

class Options {

  public:
    Options();
    int port;
    bool help;
    char* logfile;
    bool use_log;

};

}

#endif
