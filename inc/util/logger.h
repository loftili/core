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

using namespace std;

class Logger {

  public:
    Logger(string n);
    Logger(Loggable* loggable);
    ~Logger();

    void fatal(string msg);
    void info(string msg);
    void info(string a, string b);

  private:
    void send(string msg, string level);
    void send(string a, string b, string level);
    string timestr();
    string name;
    time_t timer;

  public:
    static LOG_STATE use(string file_name);
    static void close();

  private:
    static bool use_file;
    static ofstream log_stream;

};

}

#endif
