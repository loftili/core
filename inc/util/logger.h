#ifndef _LOFTILI_LOGGER_H
#define _LOFTILI_LOGGER_H

#include <iostream>
#include <fstream>
#include "util/loggable.h"

namespace loftili {

class Logger {

  public:
    Logger(std::string n);
    Logger(Loggable* loggable);
    ~Logger();

    void fatal(std::string msg);
    void info(std::string msg);

  private:
    void send();
    std::string name;

};

}

#endif
