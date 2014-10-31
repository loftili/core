#ifndef _LOFTILI_LOGGER_H
#define _LOFTILI_LOGGER_H

#include <iostream>
#include <fstream>
#include <time.h>
#include "util/loggable.h"

enum LOG_STATE {
  LOG_STATE_READY,
  LOG_STATE_BAD
};

namespace loftili {

class Logger {

  public:
    Logger(std::string n);
    Logger(Loggable* loggable);
    ~Logger();

    void fatal(std::string msg);
    void info(std::string msg);

  private:
    void send(std::string msg, std::string level);
    std::string name;
    time_t timer;

  public:
    static LOG_STATE use(std::string file_name);
    static void close();

  private:
    static bool use_file;
    static std::ofstream log_stream;

};

}

#endif
