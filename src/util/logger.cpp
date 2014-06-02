#include "util/logger.h"

namespace loftili {

Logger::Logger(std::string n) {
  std::cout << "creating a logger for: " << n << std::endl;
  name = n;
}

Logger::Logger(Loggable* loggable) { 
  std::cout << "creating a logger for: " << loggable->logName() << std::endl;
  name = loggable->logName();
}
Logger::~Logger() { }

void Logger::info(std::string msg) {
  std::cout << msg << std::endl;
}

void Logger::fatal(std::string msg) {
  std::cout << msg << std::endl;
}

}
