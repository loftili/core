#include "util/logger.h"

namespace loftili {

Logger::Logger(std::string n) {
  name = n;
}

Logger::Logger(Loggable* loggable) { 
  name = loggable->logName();
}

Logger::~Logger() { 
}

void Logger::info(std::string msg) {
  std::cout << "[" << name << "][info] - " << msg << std::endl;
}

void Logger::fatal(std::string msg) {
  std::cout << "[" << name << "][fatal] - " << msg << std::endl;
}

}
