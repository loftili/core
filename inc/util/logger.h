#ifndef _LOFTILI_LOGGER_H
#define _LOFTILI_LOGGER_H

#include <iostream>
#include <fstream>

namespace loftili {

class Logger {

public:
  Logger();
  Logger(std::string n);
  ~Logger();

  void fatal(std::string msg);
  void info(std::string msg);

private:
  void send();
  std::string name;

};

}

#endif
